#include "logolabel.h"

LogoLabel::LogoLabel(QWidget *parent)
    : QLabel(parent), m_fadeFraction(0) {
    m_oldLogo.load(":/menu/sprites/menu/oldLogo.png");
    m_newLogo.load(":/menu/sprites/menu/logo.png");
}

float LogoLabel::fadeFraction() const {
    return m_fadeFraction;
}

void LogoLabel::setFadeFraction(float fraction) {
    m_fadeFraction = fraction;
    update(); // This will cause a repaint
}

void LogoLabel::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_oldLogo);
    QLinearGradient gradient(0, height(), 0, 0);
    gradient.setColorAt(0, QColor(255, 255, 255, 0));
    gradient.setColorAt(m_fadeFraction, QColor(255, 255, 255, 255));
    painter.setBrush(gradient);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(0, 0, m_newLogo);
}
