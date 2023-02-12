#ifndef PROJECTCFG_H
#define PROJECTCFG_H

#include <QWidget>

namespace Ui {
class projectCfg;
}

class projectCfg : public QWidget
{
    Q_OBJECT

public:
    explicit projectCfg(QWidget *parent = nullptr);
    ~projectCfg();

private:
    Ui::projectCfg *ui;
};

#endif // PROJECTCFG_H
