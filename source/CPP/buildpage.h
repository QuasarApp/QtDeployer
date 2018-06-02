#ifndef BUILDPAGE_H
#define BUILDPAGE_H

#include <QWidget>

namespace Ui {
class BuildPage;
}

class BuildPage : public QWidget
{
    Q_OBJECT

public:
    explicit BuildPage(QWidget *parent = 0);
    ~BuildPage();

public slots:
    void log(QString);
private:
    Ui::BuildPage *ui;

    void checkPathes();
private slots:
    void chooseQtDir();
    void chooseProjectDir();
    void buildClick();
    void chooseChanged(QString);
signals:
    void build(QString qt, QString pro);
};

#endif // BUILDPAGE_H
