#ifndef RECT_H
#define RECT_H

#include "figure.h"

class Rect : public Figure
{
public:
    Rect(int x, int y, int h, int w, int c) : x_(x), y_(y), height_(h), width_(w), color_(c) {};
    void Draw() const override;
    json toJson() const override;

private:
    int x_, y_;
    int height_, width_;
    int color_;
};

#endif // RECT_H
