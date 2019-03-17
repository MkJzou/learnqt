#include "titlebar.h"

#include <QHBoxLayout>
#include <QEvent>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QMouseEvent>
#include <qdebug.h>


TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
    , m_isPressed(false)
{
    this->uiInit();
}

void TitleBar::uiInit()
{
    setFixedHeight(32);

    m_pIconLabel = new QLabel(this);
    m_pTitleLabel = new QLabel(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

    m_pIconLabel->setFixedSize(20, 20);
    m_pIconLabel->setScaledContents(true);
    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pMinimizeButton->setFixedSize(27, 22);
    m_pCloseButton->setFixedSize(27, 22);
    m_pMinimizeButton->setToolTip("最小化");
    m_pCloseButton->setToolTip("关闭");

    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_pIconLabel);
    pLayout->addSpacing(5);
    pLayout->addWidget(m_pTitleLabel);
    pLayout->addWidget(m_pMinimizeButton);
    pLayout->addWidget(m_pCloseButton);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(5, 0, 5, 0);
    setLayout(pLayout);

    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isPressed = true;
        m_pressedPoint = event->pos();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPressed)
    {
        window()->move(event->pos() - m_pressedPoint + window()->pos());
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_isPressed = false;
}

void TitleBar::onClicked()
{
    if (window()->isTopLevel())
    {
        if (sender() == m_pMinimizeButton)
        {
            window()->showMinimized();
        }
        else if (sender() == m_pCloseButton)
        {
            window()->close();
        }
    }
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::WindowTitleChange:
        if (obj)
        {
            qDebug("%p %p\n", obj, this);
            m_pTitleLabel->setText(
                        qobject_cast<QWidget*>(obj)->windowTitle());
            return true;
        }
    case QEvent::WindowIconChange:
        if (obj)
        {
            m_pIconLabel->setPixmap(
                        qobject_cast<QWidget*>(obj)->windowIcon().pixmap(
                            m_pIconLabel->size()));
            return true;
        }
    }

    return QWidget::eventFilter(obj, event);
}
