#ifndef ALTIMETER_WIDGET_H
#define ALTIMETER_WIDGET_H

#include <QWidget>

class altimeter_widget : public QWidget
{
    Q_OBJECT
public:
    explicit altimeter_widget(QWidget *parent = 0);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

public slots:
    void setAltitude(float f);
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void ScrollCounter(QPainter &painter, float counterValue, float xOfs, float yOfs, float xScale, float yScale);
signals:

public slots:

private:
    float altitude;
    QPixmap foreImage;
    QPixmap numbersImage;
    QPixmap smallNeedle;
    QPixmap largeNeedle;
};

#endif // ALTIMETER_WIDGET_H
