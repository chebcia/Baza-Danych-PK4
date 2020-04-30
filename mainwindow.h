#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginPushButton_clicked();

    void on_adminLogoutPushButton_clicked();

    void on_sellerLogoutPushButton_clicked();

    void on_deleteUserPushButton_clicked();

    void on_addUserPushButton_clicked();

    void on_findMedicinesPushButton_clicked();

    void on_findMedicinePushButton_clicked();

    void on_sellMedicinePushButton_clicked();

    void on_findReplacementPushButton_clicked();

    void on_addMedicinePushButton_clicked();

    void on_deleteMedicinePushButton_clicked();

    void on_refillMedicinePushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
