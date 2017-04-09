#include "heading_widget.h"
#include <QPainter>
#include <QBitmap>
#include <math.h>

heading_widget::heading_widget(QWidget *parent) : QWidget(parent)
{
    backImage.load(":/images/heading_background.png");
    headingRing.load(":/images/heading_wheel.png");
    airplaneImage.load(":/images/heading_aircraft.png");

    QBitmap mask;

    mask = backImage.createMaskFromColor(QColor(255, 255, 0));
    backImage.setMask(mask);

    mask = headingRing.createMaskFromColor(QColor(255, 255, 0));
    headingRing.setMask(mask);

    mask = airplaneImage.createMaskFromColor(QColor(255, 255, 0));
    airplaneImage.setMask(mask);

    headingAngle = 0;
}

QSize heading_widget::minimumSizeHint() const
{
    return QSize(30, 30);
}

QSize heading_widget::sizeHint() const
{
    return QSize(70, 70);
}

void heading_widget::setHeading(float f)
{
    f = roundf(f);
    if (headingAngle != f) {
        headingAngle = f;
        update();
    }
}


void heading_widget::paintEvent(QPaintEvent *event)
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

    QTransform trans;
    trans.translate(centerX, centerY);
    trans.scale(xScale, yScale);
    trans.rotate(-headingAngle);
    trans.translate(-137, -137);

    painter.setTransform(trans);
    painter.drawPixmap(0, 0, headingRing);

    painter.resetTransform();
    painter.translate(xOffset, yOffset);
    painter.scale(xScale, yScale);
    painter.drawPixmap(70, 40, airplaneImage);
}
