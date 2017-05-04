#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "syntaxhighlighter.h"
#include "lex.h"
#include "brainfktoc.h"
#include "answer.h"

//Global var
int errorFree = 1;
boolean darkMode = false;
QByteArray progA;
QByteArray inputA;
QString prog;
QString input;

/**
 * Creates the main window for the program
 * @param parent parent frame (widget)
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();

    ui->textEdit->setAutoFillBackground(true);
    ui->textEdit->setStyleSheet("color: QColor(255, 0, 0, 25); background-color:white; font: 12pt;");
    ui->textEdit->show();

    highlighter = new Highlighter(ui->textEdit->document());
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Paste command
 */
void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

/**
 * Delete command
 */
void MainWindow::on_actionDelete_triggered()
{
    ui->textEdit->clear();
}

/**
 * Select all command
 */
void MainWindow::on_actionSelect_All_triggered()
{
    ui->textEdit->selectAll();
}

/**
 * Change background to white
 */
void MainWindow::on_actionDefault_Mode_triggered()
{

    ui->textEdit->setAutoFillBackground(true);
    ui->textEdit->selectAll();
    ui->textEdit->setTextBackgroundColor(Qt::white);
     ui->textEdit->setStyleSheet("color: QColor(255, 0, 0, 25); background-color:white; font: 12pt;");
    ui->textEdit->show();

    darkMode = false;
}

/**
 * Change background to gray
 */
void MainWindow::on_actionDark_Mode_triggered()
{
    ui->textEdit->setAutoFillBackground(true);
    ui->textEdit->selectAll();
    ui->textEdit->setTextBackgroundColor(QColor(128,128,128,255));
    ui->textEdit->setStyleSheet("color: QColor(255, 0, 0, 25); background-color:rgb(128,128,128);font: 12pt;");
    ui->textEdit->show();

    darkMode = true;
}

/**
 * Undo command
 */
void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

/**
 * Create a new file
 */
void MainWindow::on_actionNew_triggered()
{
    mFilename = "";
    ui->textEdit->setPlainText("");
}

/**
 * Open file
 */
void MainWindow::on_actionOpen_triggered(){
    QString file = QFileDialog::getOpenFileName(this, "Open a file");

    if(!file.isEmpty()){
        QFile sFile(file);
        if(sFile.open(QFile::ReadOnly | QFile::Text)){
            mFilename = file;
            QTextStream in(&sFile);
            QString text = in.readAll();
            sFile.close();

            ui->textEdit->setPlainText(text);
        }
    }
}

/**
 * Save file
 */
void MainWindow::on_actionSave_triggered()
{
    if(mFilename == ""){
        on_actionSave_As_triggered();
        return;
    }

    QFile sFile(mFilename);
    if(sFile.open(QFile::WriteOnly | QFile::Text)){
        QTextStream out(&sFile);

        out << ui->textEdit->toPlainText();

        sFile.flush();
        sFile.close();
    }
}

/**
 * File save as
 */
void MainWindow::on_actionSave_As_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Open a file");

    if(!file.isEmpty()){
        mFilename = file;
        on_actionSave_triggered();
    }
}

/**
 * Exit
 */
void MainWindow::on_actionExit_triggered()
{
    exit(errno);
}

/**
 * Copy file
 */
void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

/**
 * Cut function
 */
void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

/**
 * Redo function
 */
void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

/**
 * Opens "about" dialog
 */
void MainWindow::on_actionAbout_triggered()
{


    QDialog *about = new QDialog(0,0);
    about = new AboutDialog(this);
    about->show();
}

/**
 * Changes background to black
 */
void MainWindow::on_actionComment_Code_triggered()
{
    ui->textEdit->setAutoFillBackground(true);
     ui->textEdit->selectAll();
     ui->textEdit->setTextBackgroundColor(Qt::black);
    ui->textEdit->setStyleSheet("color: white; background-color:black;font: 12pt;");
    ui->textEdit->show();
}

/**
 * Interprets the code
 */
void MainWindow::on_actionInterperet_triggered()
{
    ui->textEditConsole->clear();
    on_actionParse_triggered();
    if(errorFree>0){
    char data[30000];
    char *d = data;
    char *program;
    int bal = 0;

    prog = ui->textEdit->toPlainText();
    progA = prog.toLatin1();
    program = progA.data();

    for(int k = 0; k<30000; k++){
        d[k] = 0;
    }
    while(*program){
        switch(*program){
        case '>':
          d++;
          break;
        case '<':
          d--;
          break;
        case '+':
          (*d)++;
          break;
        case '-':
          (*d)--;
          break;
        case '.':
            ui->textEditConsole->insertPlainText(QString(QChar::fromLatin1(*d)));
          break;
        case ',':
            answer.exec();
            input = answer.returnAnswer();
            inputA = input.toLatin1();
            *d = inputA.data()[0];
          break;
        case '[':
            bal = 1;
            if(*d == '\0'){
                do{
                    program++;
                    if(*program == '[')
                        bal++;
                    else if(*program == ']')
                        bal--;
                }while(bal !=0);
            };
          break;
        case ']':
            bal = 0;
                do{
                    if(*program == '[')
                        bal++;
                    else if(*program == ']')
                        bal--;
                    program--;
                }while(bal !=0);
          break;
          }
         program++;
        }
}
}

/**
 * Parse the code
 * @return any errors that occurred
 */
int* MainWindow::on_actionParse_triggered()
{
    int begin;

    int* errors;
    errorFree = 1;
    QFile sFile("parse.txt");
    if(sFile.open(QFile::WriteOnly | QFile::Text)){
        QTextStream out(&sFile);
        out << ui->textEdit->toPlainText();
        sFile.flush();
        sFile.close();
    }
    lex.resetErrors();
    lex.parse("parse.txt");
    errors=lex.getErrors();

    QTextCharFormat fmt;
    fmt.setBackground(Qt::blue);
    QTextCursor cursor(ui->textEdit->document());

    ui->textEdit->selectAll();
    if(darkMode){
        ui->textEdit->setTextBackgroundColor(Qt::gray);
    }else{
        ui->textEdit->setTextBackgroundColor(Qt::white);
    }
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);

    for(int i = 0; i < 500; i++){
        begin = 0;
        if(errors[i] != -1){
            begin = errors[i];
            errorFree = 0;
            cursor.setPosition(begin-1, QTextCursor::MoveAnchor);
            cursor.setPosition(begin, QTextCursor::KeepAnchor);
            cursor.setCharFormat(fmt);
        }
    }
    string line = lex.getLine();
    QString qLine = QString::fromStdString(line);
    ui->textEditConsole->setPlainText(qLine);

    return errors;
}

/**
 * Convert the code to C
 */
void MainWindow::on_actionConvert_triggered()
{
   int *errorsL = on_actionParse_triggered();

   if(errorFree>0){
   int *tokenStorage = lex.getTokens();

   Converter.convertToC(errorsL, tokenStorage);

       QFile sFile("BrainFile.c");
       if(sFile.open(QFile::ReadOnly | QFile::Text)){
           QTextStream in(&sFile);
           QString text = in.readAll();
           sFile.close();

           ui->textEditConsole->setPlainText(text);
       }
   }

}
