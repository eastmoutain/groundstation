#include "radiostick_widget.h"
#include <QPainter>
#include <QBitmap>

const int StickDiam = 30;

radiostick_widget::radiostick_widget(QWidget *parent) : QWidget(parent)
{
    backImage.load(":/images/radiostick_background.png");

    QBitmap mask = backImage.createMaskFromColor(QColor(255, 255, 0));
    backImage.setMask(mask);

    stickPen.setWidth(StickDiam *2 / 3);
    stickPen.setCapStyle(Qt::RoundCap);
    stickPen.setColor(QColor::fromRgb(128, 128, 128));

    tipBrush = QBrush(QColor::fromRgb(160, 160, 160));

    xValue = yValue = 0.0f;
}

QSize radiostick_widget::minimumSizeHint() const
{
    return QSize(30, 30);
}

QSize radiostick_widget::sizeHint() const
{
    return QSize(70, 70);
}

void radiostick_widget::setValues(float x, float y)
{
    if (xValue != x || yValue != y) {
        xValue = x;
        yValue = y;
        update();
    }
}

void radiostick_widget::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    int controlWidth = this->width();
    int controlHeight = this->height();
    int centerX = controlWidth / 2;
    int centerY = controlHeight / 2;

    int drawSize = controlWidth < controlHeight? controlWidth: controlHeight;
    int xOffset = centerX - (drawSize / 2);
    int yOffset = centerY - (drawSize / 2);

    float xScale = (float)drawSize / (float)backImage.width();
    float yScale = (float)drawSize / (float)backImage.height();

    painter.translate(xOffset, yOffset);
    painter.scale(xScale, yScale);
    painter.drawPixmap(0, 0, backImage);

    // display radio stick
    float _centerX = (float)backImage.width() * 0.5f;
    float _centerY = (float)backImage.height() * 0.5;

    float radius = qMin(_centerX, _centerY) * 0.6f;
    float range = 1024.0f;

    float xtemp, ytemp;

    if (xValue <= -range) {
        xtemp = -range;
    } else if (xValue >= range) {
        xtemp = range;
    } else {
        xtemp = xValue;
    }

    if (yValue <= -range) {
        ytemp = -range;
    } else if (yValue >= range) {
        ytemp = range;
    } else {
        ytemp = yValue;
    }

    xtemp = (xtemp / range) * radius;
    ytemp = (ytemp / range) * radius;

    float px = centerX + xtemp;
    float py = centerY - ytemp;

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(stickPen);

    painter.drawLine(centerX, centerY, px, py);

    int diam = StickDiam;
    painter.setBrush(tipBrush);
    painter.setPen(QPen(QColor::fromRgb(0,0,0)));
    painter.drawEllipse(px - diam / 2, py - diam / 2, diam, diam);
}
