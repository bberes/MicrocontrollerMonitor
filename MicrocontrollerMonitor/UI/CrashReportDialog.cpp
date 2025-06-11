#include "CrashReportDialog.hpp"

// #Qt
#include <QVBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>

// #MicrocontrollerMonitor
#include "Utilities.hpp"


CrashReportDialog::CrashReportDialog (QWidget* parent/* = nullptr*/)
	: QDialog (parent)
{
	setWindowTitle ("Application Error Report");

	QVBoxLayout* layout = MakeChild<QVBoxLayout> (*this);

	QLabel* label = MakeChild<QLabel> (*this);
	label->setText (
		"The application has encountered an unexpected error and needs to close.\n"
		"Please describe the steps you took before the crash occurred.\n"
		"This information will help us identify and fix the problem."
	);
	layout->addWidget (label);

	DEBUG_ONLY (debugLabel = MakeChild<QLabel> (*this));
	DEBUG_ONLY (debugLabel->setTextInteractionFlags (Qt::TextInteractionFlag::TextSelectableByMouse));
	DEBUG_ONLY (layout->addWidget (debugLabel));

	inputBox = MakeChild<QPlainTextEdit> (*this);
	layout->addWidget (inputBox);

	QPushButton* sendButton = MakeChild<QPushButton> (*this);
	sendButton->setText ("Submit");
	layout->addWidget (sendButton);

	connect (sendButton, &QPushButton::clicked, this, &CrashReportDialog::accept);
}


QString CrashReportDialog::GetUserInput () const
{
	return inputBox->toPlainText ();
}


DEBUG_ONLY (void CrashReportDialog::SetDebugText (const QString& text) { debugLabel->setText (text); })