#include "widget.h"

#include <QVBoxLayout>
#include <qdebug.h>

#include "titlebar.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    TitleBar *pTitleBar = new TitleBar(this);
    QVBoxLayout *pVBoxLayout = new QVBoxLayout(this);

    pVBoxLayout->addWidget(pTitleBar);
    pVBoxLayout->addStretch();
    pVBoxLayout->setSpacing(0);
    pVBoxLayout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(pVBoxLayout);
    this->installEventFilter(pTitleBar);

    this->setWindowTitle("1234");
}

Widget::~Widget()
{

}
