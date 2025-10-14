#include "circle.h"

#include <QPainter>

void Circle::Draw(QPainter &painter) const {
    painter.setBrush(color_);
    painter.drawEllipse(center_, radius_, radius_);
}

json Circle::toJson() const {
    int x = center_.x();
    int y = center_.y();
    int rad = radius_;

    std::ostringstream col;
    // Получение цвета RGB
    unsigned r = color_.red();
    unsigned g = color_.green();
    unsigned b = color_.blue();

    col << "#" << std::hex << std::uppercase << std::setfill('0')
        << std::setw(2) << r
        << std::setw(2) << g
        << std::setw(2) << b;
    return json{
        {"type", "circle"},
        {"cx", x},
        {"cy", y},
        {"r", rad},
        {"c", col.str()}
    };
}
