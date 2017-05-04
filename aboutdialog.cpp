#include "aboutdialog.h"
#include "ui_aboutdialog.h"

/**
 * Displays the about dialog
 * @param parent window
 */
AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

/**
 * On click, will close the window
 */
void AboutDialog::on_OK_clicked()
{
    close();
}
