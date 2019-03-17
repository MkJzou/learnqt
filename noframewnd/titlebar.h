#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>


class QLabel;
class QPushButton;
class QPoint;

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual bool eventFilter(QObject *obj, QEvent *event) override;

signals:


public slots:
    void onClicked();

private:
    void uiInit();

private:
    QLabel *m_pIconLabel;
    QLabel *m_pTitleLabel;
    QPushButton *m_pMinimizeButton;
    QPushButton *m_pCloseButton;

    bool m_isPressed;
    QPoint m_pressedPoint;
};

#endif // TITLEBAR_H
