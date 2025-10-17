#ifndef CIRCLE_H
#define CIRCLE_H

#include "figure.h"

class Circle : public Figure
{
public:
    Circle(int x, int y, int radius, int color) :
        x_(x), y_(y), radius_(radius), color_(color) {}
    void Draw() const override;
    json toJson() const override;
private:
    int x_, y_;
    int radius_;
    int color_;
};

#endif // CIRCLE_H
