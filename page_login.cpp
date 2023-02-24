#include "page_login.h"
#include "ui_page_login.h"

Page_Login::Page_Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_Login)
{
    ui->setupUi(this);
}

Page_Login::~Page_Login()
{
    delete ui;
}

void Page_Login::on_btn_login_clicked()
{
    //数据库查找用户名和密码

    //如果失败就提示

    //成功进入主界面
    emit sendLoginSuccess();
}

//退出
void Page_Login::on_btn_exit_clicked()
{
    exit(0);
}

