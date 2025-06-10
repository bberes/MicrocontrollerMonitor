#include "CrashReportDialog.hpp"

// #Qt
#include <QVBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>


CrashReportDialog::CrashReportDialog (QWidget* parent/* = nullptr*/)
	: QDialog (parent)
{
	setWindowTitle ("Application Error Report");

	QVBoxLayout* layout = new QVBoxLayout (this);

	QLabel* label = new QLabel (
		"The application has encountered an unexpected error and needs to close.\n"
		"Please describe the steps you took before the crash occurred.\n"
		"This information will help us identify and fix the problem.",
		this
	);
	layout->addWidget (label);

	DEBUG_ONLY (debugLabel = new QLabel (this));
	DEBUG_ONLY (debugLabel->setTextInteractionFlags (Qt::TextInteractionFlag::TextSelectableByMouse));
	DEBUG_ONLY (layout->addWidget (debugLabel));

	inputBox = new QPlainTextEdit (this);
	layout->addWidget (inputBox);

	QPushButton* sendButton = new QPushButton ("Submit", this);
	layout->addWidget (sendButton);

	connect (sendButton, &QPushButton::clicked, this, &CrashReportDialog::accept);
}


QString CrashReportDialog::GetUserInput () const
{
	return inputBox->toPlainText ();
}


DEBUG_ONLY (void CrashReportDialog::SetDebugText (const QString& text) { debugLabel->setText (text); })