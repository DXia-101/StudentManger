#include "dlg_addstu.h"
#include "ui_dlg_addstu.h"
#include "stusql.h"
#include <QMessageBox>

Dlg_AddStu::Dlg_AddStu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_AddStu)
{
    ui->setupUi(this);
}

Dlg_AddStu::~Dlg_AddStu()
{
    delete ui;
}

void Dlg_AddStu::setType(bool isAdd,StuInfo info)
{
    m_isAdd = isAdd;
    m_id = info.id;
    ui->le_name->setText(info.name);
    ui->sb_age->setValue(info.age);
    ui->le_class->setText(QString::number(info.uiclass));
    ui->le_grade->setText(QString::number(info.grade));
    ui->le_phone->setText(info.phone);
    ui->le_wechat->setText(info.wechat);
}

void Dlg_AddStu::on_btn_save_clicked()
{
    StuInfo info;
    auto ptr = stusql::getinstance();
    info.id = m_id;
    info.name = ui->le_name->text();
    info.age = ui->sb_age->text().toInt();
    info.uiclass = ui->le_class->text().toInt();
    info.grade = ui->le_grade->text().toInt();
    info.phone = ui->le_phone->text();
    info.wechat = ui->le_wechat->text();
    if(m_isAdd){
        ptr->addStu(info);
    }
    else{
        ptr->UpdateStuInfo(info);
    }
    QMessageBox::information(this,"信息","存储成功");
    this->hide();
}

void Dlg_AddStu::on_btn_cancel_clicked()
{
    this->hide();
}

