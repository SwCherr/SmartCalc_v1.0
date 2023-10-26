#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QDialog>

namespace Ui {
class DepositWindow;
}

class DepositWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DepositWindow(QWidget *parent = nullptr);
    ~DepositWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DepositWindow *ui;
};

#endif // DEPOSITWINDOW_H
