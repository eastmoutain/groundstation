#include "horizon_widget.h"
#include <QPainter>
#include <QBitmap>
#include <math.h>

horizon_widget::horizon_widget(QWidget *parent) : QWidget(parent)
{
    horizonImage.load(":/images/horizon_groundsky.png");
    foreImage.load(":/images/horizon_background.png");

    foreMask = foreImage.createMaskFromColor(QColor(255, 255, 0));
    foreImage.setMask(foreMask);

    rollAngle = pitchAngle = 0.0f;
}

QSize horizon_widget::minimumSizeHint() const
{
    return QSize(30, 30);
}

QSize horizon_widget::sizeHint() const
{
    return QSize(70, 70);
}

void horizon_widget::setAngle(float roll, float pitch)
{
    roll = roundf(roll);
    pitch = roundf(pitch);

    if (rollAngle != roll || pitchAngle != pitch) {
        rollAngle = roll;
        pitchAngle = pitch;
        update();
    }
}

void horizon_widget::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter painter(this);

    int controlWidth = this->width();
    int controlHeight = this->height();
    int centerX = controlWidth / 2;
    int centerY = controlHeight / 2;

    int drawSize = controlWidth < controlHeight? controlWidth: controlHeight;
    int xOffset = centerX - (drawSize/2);
    int yOffset = centerY - (drawSize/2);

    float xScale = (float)drawSize/(float)foreImage.width();
    float yScale = (float)drawSize / (float)foreImage.height();

    painter.setClipRect(centerX - drawSize/2 + 10, centerY - drawSize/2 + 10, drawSize - 20, drawSize - 20);
    painter.setClipping(true);

    QTransform trans;
    trans.translate(xOffset + 150 * xScale, yOffset + 150 * yScale);
    trans.scale(xScale, yScale);
    trans.rotate(rollAngle);
    trans.translate(-125, -360 + (pitchAngle * 4));

    painter.setTransform(trans);
    painter.drawPixmap(0, 0, horizonImage);

    painter.setClipping(false);
    painter.resetTransform();
    painter.translate(xOffset, yOffset);
    painter.scale(xScale, yScale);
    painter.drawPixmap(0, 0, foreImage);
}
