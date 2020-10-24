#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>

QString MainWindow::ReadStream(QString file_name){

    QString expression = "";
    QFile file(file_name);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        expression = in.readAll();

    }else
    {
       QMessageBox::warning(this,"ERROR","can not read file stream '" + file_name + "' " ,QMessageBox::Ok);
    }

    return expression;
}

void MainWindow::currentTokenChanged(Token *token)
{
    if(token){
        ui->lab_currtoken->setText(token->toString());

        if(token->getBackToken())
            ui->lab_backtoken->setText(token->getBackToken()->toString());
        else
            ui->lab_backtoken->setText("NULL");

        if(token->getNextToken())
            ui->lab_nexttoken->setText(token->getNextToken()->toString());
        else
            ui->lab_nexttoken->setText("NULL");
    }else{
        ui->lab_currtoken->setText("NULL");
        ui->lab_backtoken->setText("NULL");
        ui->lab_nexttoken->setText("NULL");
    }
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_loadcontent_clicked()
{
    ui->txtedt_contentstream->setText(this->ReadStream(ui->lineedit_filepath->text()));
}

void MainWindow::on_btn_back_clicked()
{
    try{
        Token * token = lexicalAnalyser.BackToken();
        currentTokenChanged(token);

        if(token){
            ui->btn_back->setEnabled(true);
        }else{
            ui->btn_back->setEnabled(false);
            ui->btn_next->setEnabled(true);
        }

    }catch(LexicalError error)
    {
        QMessageBox::warning(this,"ERROR",error.toString());
    }
}

void MainWindow::on_btn_next_clicked()
{
    try{
        Token * token = lexicalAnalyser.NextToken();
        currentTokenChanged(token);

        if(token){
            ui->btn_next->setEnabled(true);
            ui->btn_back->setEnabled(true);
        }else{
            ui->btn_next->setEnabled(false);
        }

    }catch(LexicalError error)
    {
        QMessageBox::warning(this,"ERROR",error.toString());
    }
}

void MainWindow::on_btn_begin_clicked()
{
    lexicalAnalyser.setStream(ui->txtedt_contentstream->toPlainText());
    ui->btn_back->setEnabled(true);
    ui->btn_next->setEnabled(true);
    ui->lab_backtoken->clear();
    ui->lab_currtoken->clear();
    ui->lab_nexttoken->clear();
}
