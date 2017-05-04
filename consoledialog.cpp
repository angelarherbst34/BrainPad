#include "consoledialog.h"
#include "ui_consoledialog.h"

/**
 * Console
 * @param parent window
 */
ConsoleDialog::ConsoleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConsoleDialog)
{
    ui->setupUi(this);

    ui->textEditConsole->setAutoFillBackground(true);
    ui->textEditConsole->setStyleSheet("font:12pt;");
    ui->textEditConsole->show();
}

ConsoleDialog::~ConsoleDialog()
{
    delete ui;
}

/**
 * Read from console
 * @param info
 */
void ConsoleDialog::readInfo(QString info){
    ui->textEditConsole->setPlainText(info);
}
