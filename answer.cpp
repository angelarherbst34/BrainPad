#include "answer.h"
#include "ui_answer.h"

/**
 * Opens the dialog to accept input from the user
 */
QString answer;
Answer::Answer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Answer)
{
    ui->setupUi(this);
    ui->AnswerInput->show();
    ui->Enter->show();
}

Answer::~Answer()
{
    delete ui;
}

/**
 * On "enter", text will be inputted, and then the dialog will close
 */
void Answer::on_Enter_clicked()
{
    answer = ui->AnswerInput->text();
    this->close();
}

/**
 * Returns what the user inputted
 * @return the user input
 */
QString Answer:: returnAnswer(){
    return answer;
}
