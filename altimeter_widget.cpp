#include "altimeter_widget.h"
#include <QPainter>
#include <QBitmap>
#include <math.h>

altimeter_widget::altimeter_widget(QWidget *parent) : QWidget(parent)
{
    foreImage.load(":/images/altimeter_background.png");
    numbersImage.load(":/images/altimeter_numbers.png");
    smallNeedle.load(":/images/altimeter_smallneedle.png");
    largeNeedle.load(":/images/altimeter_longneedle.png");

    QBitmap mask;

    mask = foreImage.createMaskFromColor(QColor(255, 255, 0));
    foreImage.setMask(mask);

    mask = smallNeedle.createMaskFromColor(QColor(255, 255, 0));
    smallNeedle.setMask(mask);

    mask = largeNeedle.createMaskFromColor(QColor(255, 255, 0));
    largeNeedle.setMask(mask);

    altitude = 0.0;
}

QSize altimeter_widget::minimumSizeHint() const
{
    return QSize(30, 30);
}

QSize altimeter_widget::sizeHint() const
{
    return QSize(70, 70);
}

void altimeter_widget::setAltitude(float f)
{
    if (altitude != f) {
        altitude = f;
        update();
    }
}

const float PI = 3.141592654f;

static float InterpolPhyToAngle(float phyVal, float minPhy, float maxPhy, float minAngle, float maxAngle)
{
    float a, b, x, y;

    if (phyVal < minPhy) {
        return minAngle;
    } else if (phyVal > maxPhy) {
        return maxAngle;
    } else {
        x = phyVal;
        a = (maxAngle - minAngle) / (maxPhy - minPhy);
        b = 0.5f * (maxAngle + minAngle - a *(maxPhy + minPhy));
        y = a * x + b;

        return y;
    }
}

void altimeter_widget::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    int controlWidth = this->width();
    int controlHeight = this->height();
    int centerX = controlWidth / 2;
    int centerY = controlHeight / 2;

    int drawSize = controlWidth < controlHeight? controlWidth: controlHeight;
    int xOffset = centerX - (drawSize/2);
    int yOffset = centerY - (drawSize/2);

    float xScale = (float)drawSize / (float)foreImage.width();
    float yScale = (float)drawSize / (float)foreImage.height();


    painter.setClipRect(centerX - drawSize/2 + 10, centerY - drawSize/2 + 10, drawSize - 20, drawSize -20);
    painter.setClipping(true);

    ScrollCounter(painter, altitude, xOffset, yOffset, xScale, yScale);

    painter.resetTransform();
    painter.setClipRect(0, 0, this->width(), this->height());

    painter.translate(xOffset, yOffset);
    painter.scale(xScale, yScale);
    painter.drawPixmap(0, 0, foreImage);

    float alphaSmallNeedle;
    float altiTemp = altitude;
    if (altitude >= 0.0) {
        altiTemp = 10000.0f - altitude;
    }

    alphaSmallNeedle = InterpolPhyToAngle(altiTemp, 0.0f, 10000.0f, 0.0f, 359.0f);

    float altiFraction = altiTemp - floorf(altiTemp / 1000.0f) * 1000.0f;
    float alphaLongNeedle = InterpolPhyToAngle(altiFraction, 0.0f, 1000.0f, 0.0f, 359.0f);

    QTransform trans;
    trans.translate(centerX, centerY);
    trans.scale(xScale, yScale);
    trans.rotate(alphaSmallNeedle);
    trans.translate(-14, -111);
    painter.setTransform(trans);

    painter.drawPixmap(0, 0, smallNeedle); // display small needle

    trans.reset();
    trans.translate(width()/2, height()/2);
    trans.scale(xScale, yScale);
    trans.rotate(alphaLongNeedle);
    trans.translate(-14, -111);
    painter.setTransform(trans);

    painter.drawPixmap(0, 0, largeNeedle);
}

void altimeter_widget::ScrollCounter(QPainter &painter, float counterValue, float xOfs, float yOfs, float xScale, float yScale)
{
   int indexDigit = 0;
   int digitBoxHeight = (int)(numbersImage.height()/12);
   int digitBoxWidth = numbersImage.width();
   const int nbOfDigits = 5;

   bool IsNegative = counterValue < 0;
   if (IsNegative) {
       counterValue = -counterValue;
   }

   for (indexDigit = 0; indexDigit < nbOfDigits; indexDigit++) {
       int currentDigit;
       int prevDigit;
       int xOffset;
       int yOffset;
       float fader;

       if (IsNegative && indexDigit == (nbOfDigits - 1)) {
           currentDigit = 11;
       } else {
           currentDigit = (int)(counterValue / powf(10.f, indexDigit)) % 10;
       }

       fader = 0.0f;
       if (indexDigit == 0) {
           fader = counterValue - floor(counterValue);
       }

       if (indexDigit == 0 || currentDigit == 11) {
           prevDigit = 0;
       } else {
           prevDigit = (int)(counterValue/powf(10.f, indexDigit - 1)) % 10;
       }

       xOffset = (int)(digitBoxWidth * (nbOfDigits - indexDigit - 1));

       if (prevDigit == 9) {
           float temp = (float)(counterValue / powf(10.0f, (indexDigit - 1)));
           fader = temp - floor(temp);
           yOffset = (int)(-((fader + currentDigit) * digitBoxHeight));
       } else {
           yOffset = (int)(-((fader + currentDigit) * digitBoxHeight));
       }

       painter.resetTransform();
       painter.translate(xOfs, yOfs);
       painter.scale(xScale, yScale);
       painter.drawPixmap(35 + xOffset, 135 + yOffset, numbersImage);
   }
}


