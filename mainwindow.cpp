#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Logowanie.h"
#include "Admin.h"
#include "Manager.h"
#include <QLineEdit>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->adminFrame->hide();
    ui->sellerFrame->hide();
    ui->managerFrame->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginPushButton_clicked()
{
    std::string login = ui->loginLineEdit->text().toStdString();
    std::string password = ui->passwordLineEdit->text().toStdString();
    if (Logowanie::sprawdzDane(login, password))
    {
        std::string role = Logowanie::zalogujSie(login, password);
        ui->loginFrame->hide();
        if (role == "admin")
            ui->adminFrame->show();
        else if (role == "sprzedawca")
            ui->sellerFrame->show();
        else if (role == "manager")
        {
            ui->sellerFrame->show();
            ui->managerFrame->show();
        }
        else
            ui->loginFrame->show();
    }
    else
        QMessageBox::critical(this, tr("BazyDanych"), tr("login i haslo nie spelnia wymagan:"));
}

void MainWindow::on_adminLogoutPushButton_clicked()
{
    ui->loginFrame->show();
    ui->adminFrame->hide();
}

void MainWindow::on_sellerLogoutPushButton_clicked()
{
    ui->loginFrame->show();
    ui->sellerFrame->hide();
    ui->managerFrame->hide();
}

void MainWindow::on_deleteUserPushButton_clicked()
{
    Admin::usunUzytkownika(ui->userNameLineEdit->text().toStdString());
}

void MainWindow::on_addUserPushButton_clicked()
{
    Admin::dodawaniedopliku(ui->userNameLineEdit->text().toStdString(),
                            ui->userPasswordLineEdit->text().toStdString(),
                            ui->roleLineEdit->text().toStdString());
}

void MainWindow::on_findMedicinesPushButton_clicked()
{
    Sprzedawca::znajdzlekarstwa();
}

void MainWindow::on_findMedicinePushButton_clicked()
{
    Sprzedawca::znajdzlek(ui->medicineNameLineEdit->text().toStdString(),
                          ui->medicineTypeLineEdit->text().toStdString());
}

void MainWindow::on_sellMedicinePushButton_clicked()
{
    Sprzedawca::sprzedajLek(ui->medicineNameLineEdit->text().toStdString(),
                            ui->medicineTypeLineEdit->text().toStdString());
}

void MainWindow::on_findReplacementPushButton_clicked()
{
    Sprzedawca::znajdzZamiennik(ui->sicknessLineEdit->text().toStdString());
}

void MainWindow::on_addMedicinePushButton_clicked()
{
    Manager::dodajLek(ui->medicineNameLineEdit->text().toStdString(),
                      ui->medicineTypeLineEdit->text().toStdString());
}

void MainWindow::on_deleteMedicinePushButton_clicked()
{
    Manager::usunLek(ui->medicineNameLineEdit->text().toStdString(),
                     ui->medicineTypeLineEdit->text().toStdString());
}

void MainWindow::on_refillMedicinePushButton_clicked()
{
    Manager::uzupelnijLek(ui->medicineNameLineEdit->text().toStdString(),
                          ui->medicineTypeLineEdit->text().toStdString(),
                          ui->medicineCountLineEdit->text().toInt());
}
