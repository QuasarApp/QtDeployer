#include "about.h"
#include "ui_about.h"
#include <QPixmap>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    this->setModal(true);

    ui->logo->setText("<img align=middle height=100 width=110 src='://icon' />");
    QString text = QString("<p style='text-align: left;'>&nbsp;</p>"
                          "<p style='text-align: left;'>%0<br />%1 <a href='https://github.com/ShahriarSS/QtLinuxDeployer' target='_blank' rel='noopener'><span style='color: #00ff00;'>QtLinuxDeployer</span></a></p>"
                          "<p style='text-align: left;'><br /><span style='color: #00ff00;'>%2</span><br />* %3 <span style='color: #00ff00;'>%4</span>.<br />* %5<span style='color: #00ff00;'> %6</span>.</p>"
                          "<p style='text-align: left;'>%7</p>"
                          "<p style='text-align: left;'>%8<a href='https://github.com/EndrII' target='_blank' rel='noopener'><span style='color: #00ff00;'> EndrII </span></a><br /> Copyright (C) 12 Mar 2018 - Apr 10, 2018"
                          " <span style='color: #00ff00;'>ShahriarSS</span>.<br /> Copyright (C) Apr 10, 2018<span style='color: #00ff00;'>QuasarApp</span>.</p>").
            arg(
                tr("This application forked by ShahriarSS"),
                tr("Page of original soft:"),
                tr("Developers of fork:"),
                tr("Programmer:"),
                tr("Yankovich Andrei"),
                tr("Designer:"),
                tr("Bakovets Alina"),
                tr("This application is distributed under the LGPLv3 license."),
                tr("Contact:"));
    ui->text->setText(text);
}
About::~About()
{
    delete ui;
}
