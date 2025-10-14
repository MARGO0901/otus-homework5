#ifndef CIRCLE_H
#define CIRCLE_H

#include <QPointer>
#include <QColor>
#include <qpoint.h>

#include "figure.h"

class Circle : public Figure
{
public:
    Circle(const QPoint& center, int radius, const QColor& color) :
        center_(center), radius_(radius), color_(color) {}
    void Draw(QPainter &painter) const override;
    json toJson() const override;
private:
    QPoint center_;
    int radius_;
    QColor color_;
};

#endif // CIRCLE_H
