#ifndef LOGOLABEL_H
#define LOGOLABEL_H

#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QLinearGradient>

class LogoLabel : public QLabel {
    Q_OBJECT
    Q_PROPERTY(float fadeFraction READ fadeFraction WRITE setFadeFraction)

public:
    LogoLabel(QWidget *parent = nullptr);

    float fadeFraction() const;
    void setFadeFraction(float fraction);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_oldLogo;
    QPixmap m_newLogo;
    float m_fadeFraction;
};

#endif // LOGOLABEL_H
