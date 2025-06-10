#include "SymbolFileReader.hpp"

// #Qt
#include <QFile>
#include <QString>

// #Kernel
#include "Types\ByteArray.hpp"
#include "Types\DataStream.hpp"

// #FileHandler
#include "SymbolFile.hpp"


std::shared_ptr<File::COFF::SymbolFile> File::COFF::ReadSymbolFile (const QString& fileName)
{
	QFile file (fileName);
	file.open (QIODevice::OpenModeFlag::ReadOnly);
	ByteArray byteArray = file.readAll ();

	DataStream is (byteArray);
	is.setByteOrder (DataStream::ByteOrder::LittleEndian);

	auto symbolFile = std::make_shared<SymbolFile> (ForDeserialization, byteArray);
	symbolFile->Read (is);
	return symbolFile;
}
