#ifndef RADIOSTICK_WIDGET_H
#define RADIOSTICK_WIDGET_H

#include <QWidget>
#include <QBitmap>
#include <QPen>

class radiostick_widget : public QWidget
{
    Q_OBJECT
public:
    explicit radiostick_widget(QWidget *parent = 0);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
signals:

public slots:
    void setValues(float x, float y);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    float xValue, yValue;

    QPixmap backImage;
    QPen stickPen;
    QBrush tipBrush;
};

#endif // RADIOSTICK_WIDGET_H
