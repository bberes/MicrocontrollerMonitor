#include "SymbolsWidget.hpp"

// #QtUI
#include "ui_SymbolsWidget.h"

// #Qt
#include <QClipboard>
#include <QContextMenuEvent>
#include <QCryptographicHash>
#include <QFile>
#include <QMenu>
#include <QShortcut>

// #Kernel
#include "Types\HashTable.hpp"

// #FileHandler
#include "FileFormats\COFF\Utilities\SymbolTree.hpp"
#include "FileFormats\COFF\Utilities\TreeNodes.hpp"
#include "FileFormats\COFF\SymbolFileReader.hpp"

// #MicrocontrollerMonitor
#include "Data\Environment.hpp"
#include "Data\WatchWindowTableModel.hpp"


static const QString configFileName (".RuntimeCache\\SymbolCache.cfg");


class SymbolsWidget::Data final {
public:
	bool			IsEmpty		() const;
	void			Enumerate	(const std::function<void (const QString&)>&) const;
	const Entry&	Get			(const QString& key) const;
	void			Add			(const QString& key, const Entry& entry);
	void			Clear		();

	void			Load		(DataStream& ds);
	void			Store		(DataStream& ds) const;

private:
	using Entries	= std::vector<Entry>;
	using EntryMap	= HashTable<QString, size_t>;
	using Keys		= std::vector<QString>;

	Entries		entries;
	EntryMap	entryMap;
	Keys		keys;
};


struct SymbolsWidget::Entry final {
	Entry () = default;

	explicit Entry (const File::COFF::Object& object)
		: name		(QString::fromStdString (object.GetFullName	()))
		, address	(QString::fromStdString (object.GetAddress	()))
		, typeName	(QString::fromStdString (object.GetType		()))
	{}

	void Load  (DataStream& ds)       { ds >> name >> address >> typeName; }
	void Store (DataStream& ds) const { ds << name << address << typeName; }

	QString name;
	QString address;
	QString typeName;
};


static void OverrideCopyShortcutOn (QListWidget* listWidget)
{
	QShortcut* copyShortcut = new QShortcut (QKeySequence::Copy, listWidget);
    QObject::connect (copyShortcut, &QShortcut::activated, [listWidget] () {
        QStringList selectedTexts;
        for (QListWidgetItem* item : listWidget->selectedItems ()) {
            selectedTexts << item->text ();
        }
        QApplication::clipboard ()->setText (selectedTexts.join ("\n"));
    });
}


SymbolsWidget::SymbolsWidget (Environment& environment, QWidget* parent/* = nullptr*/)
	: ToggleableWidget	(parent)
	, ui				(std::make_unique<Ui::SymbolsWidgetClass> ())
	, data				(std::make_unique<Data> ())
	, wwTableModel		(environment.GetWWTableModel ())
{
	ui->setupUi (this);

	ui->listWidget->setSelectionMode (QAbstractItemView::ExtendedSelection);
	OverrideCopyShortcutOn (ui->listWidget);

	QObject::connect (ui->lineEdit, SIGNAL (textChanged (const QString&)), this, SLOT (RefreshList ()));
}


SymbolsWidget::~SymbolsWidget () = default;


static QString GetCacheFilePath (const QString& fileName)
{
	QCryptographicHash hash (QCryptographicHash::Sha256);
	ByteArray bytes = fileName.toUtf8 ();
	hash.addData (bytes);

	QFile file (fileName);
	if (!file.open (QIODevice::ReadOnly) || !hash.addData (&file)) {
		return {};
	}

	QString name (hash.result ().toHex ());
	return QString ("Logs\\") + name + ".bin"; // #ToDo: these paths should be handled better
}


static bool IsCached (const QString& fileName)
{
	QString cacheFile = GetCacheFilePath (fileName);
	QFile file (cacheFile);
	return file.open (QIODevice::ReadOnly);
}


static void StoreConfig (const QString& fileName)
{
	// #TODO ?
	QFile config (configFileName);
	if (!config.open (QIODevice::WriteOnly)) {
		return;
	}

	DataStream cs (&config);
	cs << GetCacheFilePath (fileName);
}


void SymbolsWidget::Load (const QString& fileName)
{
	static bool enableCaching = false; // #ToDo
	if (enableCaching && IsCached (fileName) && LoadFromCache (fileName)) {
		StoreConfig (fileName);
		return;
	}

	LoadFromFile (fileName);
	if (!enableCaching || !CacheEntries (fileName)) {
		return;
	}

	StoreConfig (fileName);
}


void SymbolsWidget::Clear ()
{
	ui->listWidget->clear ();
	data->Clear ();
}


void SymbolsWidget::LoadFromFile (const QString& fileName)
{
	Clear ();

	auto file = File::COFF::ReadSymbolFile (fileName);
	File::COFF::SymbolTree tree (*file);

	tree.EnumerateLeaves ([this] (auto& object) {
		auto s = QString::fromStdString (object.CalcSymbol ());
		ui->listWidget->addItem (s);
		data->Add (s, Entry (object));
	});
}


bool SymbolsWidget::LoadFromCache (const QString& fileName)
{
	Clear ();

	QFile file (GetCacheFilePath (fileName));
	if (!file.open (QIODevice::ReadOnly)) {
		TODO;	// #ToDo: invalid state, e.g. throw InvalidState,
				// Add macro: ASSERT/INSPECT/INVALID
				//  - beta build should log and crash
				//  - release/user build should avoid crash (return false)
	}

	DataStream ds (&file);
	if (!LoadFromCache (ds)) {
		Clear ();
		return false;
	}

	return true;
}


bool SymbolsWidget::LoadFromCache (DataStream& ds)
{
	data->Load (ds);

	data->Enumerate ([this] (const QString& key) {
		ui->listWidget->addItem (key);
	});

	return ds.status () == DataStream::Status::Ok;
}


bool SymbolsWidget::CacheEntries (const QString& fileName) const
{
	QString cacheFile = GetCacheFilePath (fileName);
	QFile file (cacheFile);
	if (cacheFile.isEmpty () || !file.open (QIODevice::WriteOnly)) {
		return false;
	}

	DataStream ds (&file);
	data->Store (ds);

	return ds.status () == DataStream::Status::Ok;
}


void SymbolsWidget::OnShowEvent ()
{
	if (!data->IsEmpty ()) {
		return;
	}

	// #ToDo: extract method
	QFile config (configFileName);
	if (!config.open (QIODevice::ReadOnly)) {
		return;
	}

	DataStream cs (&config);
	QString cachePath;
	cs >> cachePath;

	QFile symbolCache (cachePath);
	if (cachePath.isEmpty () || !symbolCache.open (QIODevice::ReadOnly)) {
		return;
	}

	DataStream ds (&symbolCache);
	if (!LoadFromCache (ds)) {
		Clear ();
	}
}

#ifndef QT_NO_CONTEXTMENU
void SymbolsWidget::contextMenuEvent (QContextMenuEvent* event)
{
	QMenu menu (this);
	menu.addAction ("Add selected item(s) to Watch Window", this, SLOT (AddSelectedToWatch ()));
	menu.exec (event->globalPos ());
}
#endif

void SymbolsWidget::RefreshList ()
{
	auto filter = ui->lineEdit->text ().toLower ();
	for (int i = 0; i < ui->listWidget->count (); ++i) {
		auto item = ui->listWidget->item (i);
		bool show = item->text ().toLower ().contains (filter);
		item->setHidden (!show);
	}
}


void SymbolsWidget::AddSelectedToWatch ()
{
	const auto& selectedItems = ui->listWidget->selectedItems ();
	for (auto& item : selectedItems) {
		const Entry& entry = data->Get (item->text ());
		wwTableModel.AddVariable (entry.name, entry.address, entry.typeName);
	}
}


bool SymbolsWidget::Data::IsEmpty () const
{
	return entries.empty ();
}


void SymbolsWidget::Data::Enumerate (const std::function<void (const QString&)>& process) const
{
	for (auto& key : keys) {
		process (key);
	}
}


const SymbolsWidget::Entry& SymbolsWidget::Data::Get (const QString& key) const
{
	return entries[entryMap.at (key)];
}


void SymbolsWidget::Data::Add (const QString& key, const Entry& entry)
{
	entryMap[key] = entries.size ();
	entries.push_back (entry);
	keys.push_back (key);
}


void SymbolsWidget::Data::Clear ()
{
	entryMap.clear ();
	entries.clear ();
	keys.clear ();
}


void SymbolsWidget::Data::Load (DataStream& ds)
{
	Clear ();

	size_t size = 0u;
	ds >> size;

	for (size_t i = 0u; i < size; ++i) {
		QString key;
		ds >> key;

		Entry entry;
		entry.Load (ds);

		Add (key, entry);
	}
}


void SymbolsWidget::Data::Store (DataStream& ds) const
{
	ds << keys.size ();
	for (auto& key : keys) {
		ds << key;
		Get (key).Store (ds);
	}
}