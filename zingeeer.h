#ifndef ZINGEEER_H
#define ZINGEEER_H
#include"drake.h"
#include <QDialog>

namespace Ui {
class zingeeer;
}

class zingeeer : public QDialog
{
    Q_OBJECT

public:
    explicit zingeeer(QWidget *parent = nullptr);
    ~zingeeer();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::zingeeer *ui;
    drake tmpdrake;
};

#endif // ZINGEEER_H