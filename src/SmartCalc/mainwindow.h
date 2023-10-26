#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void trig_digits();
    void trig_operat();
    void trig_trigonom();
    void trig_bracket();
    void init_flags_digit();
    void on_pushButton_comma_clicked();

    void trig_equals();
    void on_pushButton_AC_clicked();
    void on_pushButton_plotting_clicked();
    void on_pushButton_Credit_clicked();
    void on_pushButton_Deposit_clicked();
    int check_label();
};

#endif // MAINWINDOW_H
