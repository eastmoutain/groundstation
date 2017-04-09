#ifndef HEADING_WIDGET_H
#define HEADING_WIDGET_H

#include <QWidget>

class heading_widget : public QWidget
{
    Q_OBJECT
public:
    explicit heading_widget(QWidget *parent = 0);
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint()const Q_DECL_OVERRIDE;

signals:

public slots:
    void setHeading(float f);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    float headingAngle;

    QPixmap backImage;
    QPixmap headingRing;
    QPixmap airplaneImage;
};

#endif // HEADING_WIDGET_H
