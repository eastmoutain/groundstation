#ifndef HORIZON_WIDGET_H
#define HORIZON_WIDGET_H

#include <QWidget>
#include <QWidget>
#include <QBitmap>

class horizon_widget : public QWidget
{
    Q_OBJECT
public:
    explicit horizon_widget(QWidget *parent = 0);
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

signals:

public slots:
    void setAngle(float roll, float pitch);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    float rollAngle, pitchAngle;

    QPixmap horizonImage;
    QPixmap foreImage;

    QBitmap foreMask;
};

#endif // HORIZON_WIDGET_H
