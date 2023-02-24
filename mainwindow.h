#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "stusql.h"
#include <QMainWindow>
#include "page_login.h"
#include "dlg_addstu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual void keyPressEvent(QKeyEvent *event);
    ~MainWindow();

private slots:
    void on_btn_exit_clicked();

    void on_btn_simulation_clicked();

    void on_btn_add_clicked();

    void on_btn_clear_clicked();

    void on_btn_delete_clicked();

    void on_btn_update_clicked();

    void on_btn_search_clicked();

private:
    void updateTable();

private:
    Ui::MainWindow *ui;
    Page_Login m_dlgLogin;
    stusql *m_ptrStusql;

    QStringList m_lNames;
    Dlg_AddStu m_dlgAddStu;
};
#endif // MAINWINDOW_H
