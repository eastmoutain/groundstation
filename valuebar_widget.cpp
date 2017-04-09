#include "valuebar_widget.h"
#include <QPainter>
#include <QBitmap>

valuebar_widget::valuebar_widget(QWidget *parent) : QWidget(parent)
{
    valMin = -1024;
    valMax = 1024;
    value = 0;
    fromLeft = true;
    buffer = 2;

    setBarColor(QColor::fromRgb(128, 255, 128));

    lightPen = QColor::fromRgb(255, 255, 255);
    grayPen = QColor::fromRgb(160, 160, 160);
    blackPen = QColor::fromRgb(0, 0, 0);
}


QSize valuebar_widget::minimumSizeHint() const
{
    return QSize(30, 10);
}

QSize valuebar_widget::sizeHint() const
{
    return QSize(60, 10);
}

void valuebar_widget::setValue(float v)
{
    if (v != value) {
        value = v;
        update();
    }
}

void valuebar_widget::setMinMax(float vMin, float vMax)
{
    valMin = vMin;
    valMax = vMax;
    update();
}

/*
 * set left label
 */
void valuebar_widget::setLeftLabel(const QString str)
{
    if (leftLabel.compare(str)) {
        leftLabel = str;
        update();
    }
}

void valuebar_widget::setLeftLabel(int labelVal)
{
    setLeftLabel(QString::number(labelVal));
}

void valuebar_widget::setLeftLabel(const char *charStr)
{
    setLeftLabel(QString(charStr));
}


/*
 * set right label
 */
void valuebar_widget::setRightLabel(const QString str)
{
    if (rightLabel.compare(str)) {
        rightLabel = str;
        update();
    }
}

void valuebar_widget::setRightLabel(int labelVal)
{
    setRightLabel(QString::number(labelVal));
}

void valuebar_widget::setRightLabel(const char *charStr)
{
    setRightLabel(QString(charStr));
}


void valuebar_widget::setFromLeft(bool bVal)
{
    fromLeft = bVal;
    update();
}

void valuebar_widget::setBarColor(const QColor &col)
{
    barColor = col;
    barBrush = QBrush(barColor);
}

static int clamp(int v, int mn, int mx)
{
    if (v < mn)
        return mn;

    if (v > mn)
        return mx;

    return v;
}

void valuebar_widget::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter painter(this);

    int scale = width() - buffer * 2;
    float l;

    int clampedVal = clamp(value, valMin, valMax);

    float fHeight = height();
    float fWidth = (clampedVal - valMin) * scale / (valMax - valMin);

    if (fromLeft) {
        l = buffer;
    } else {
        l = (width() - buffer) - fWidth;
    }

    // draw the boarder and fill the background
    painter.setRenderHint(QPainter::Antialiasing, false);

    painter.setBrush(painter.background());
    painter.setPen(lightPen);
    painter.drawRect(1, 1, width() - 2, height() - 2);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(grayPen);
    painter.drawRect(0, 0, width() - 2, height() - 2);

    painter.setRenderHint(QPainter::Antialiasing, true);

    // fill the bar
    painter.setBrush(barBrush);
    painter.setPen(Qt::NoPen);
    painter.drawRect(l, buffer, fWidth - 1, fHeight - (buffer * 2) - 1);

    painter.setPen(blackPen);
    painter.setFont(font());

    // draw the left label
    painter.drawText(buffer + 2, 0, width() - (buffer + 2) * 2, height() - 2, Qt::AlignLeft | Qt::AlignCenter, leftLabel);

    // draw the right label
    painter.drawText(buffer + 2, 0, width() - (buffer + 2) * 2, height() - 2, Qt::AlignRight | Qt::AlignCenter, rightLabel);

}



