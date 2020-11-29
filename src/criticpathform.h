#ifndef CRITICPATHFORM_H
#define CRITICPATHFORM_H

#include <QMainWindow>

namespace Ui {
class CriticPathForm;
}

class CriticPathForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit CriticPathForm(QWidget *parent = nullptr);
    ~CriticPathForm();

private slots:
    void on_btnAddRow_clicked();

    void on_btnConfirm_clicked();

    void on_btnRemoveRow_clicked();

private:
    Ui::CriticPathForm *ui;
};

#endif // CRITICPATHFORM_H
