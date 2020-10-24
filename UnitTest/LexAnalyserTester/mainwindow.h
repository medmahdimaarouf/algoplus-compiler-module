#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<lexicalanalyser.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_loadcontent_clicked();

    void on_btn_back_clicked();

    void on_btn_next_clicked();

    void on_btn_begin_clicked();



private:
    Ui::MainWindow *ui;
    LexicalAnalyser lexicalAnalyser ;
    QString ReadStream(QString file_name);

    void currentTokenChanged(Token * token);
};

#endif // MAINWINDOW_H
