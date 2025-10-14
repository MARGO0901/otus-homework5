#ifndef RECT_H
#define RECT_H

#include "figure.h"

#include <QRect>
#include <QColor>
#include <QPainter>

class Rect : public Figure
{
public:
    Rect(const QRect &rect, const QColor &color) : rect_(rect), color_(color) {};
    void Draw(QPainter &painter) const override;
    json toJson() const override;

private:
    QRect rect_;
    QColor color_;
};

#endif // RECT_H
