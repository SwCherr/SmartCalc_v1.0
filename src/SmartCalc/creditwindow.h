#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>

namespace Ui {
class Creditwindow;
}

class Creditwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Creditwindow(QWidget *parent = nullptr);
    ~Creditwindow();

private slots:
    void on_calculate_clicked();

private:
    Ui::Creditwindow *ui;
};

#endif // CREDITWINDOW_H
