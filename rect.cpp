#include "rect.h"

#include <QPainter>
#include <iomanip>

void Rect::Draw(QPainter &painter) const {
    painter.setBrush(color_);
    painter.drawRect(rect_);
}

json Rect::toJson() const {
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
        {"type", "rect"},
        {"x", rect_.x()},
        {"y", rect_.y()},
        {"w", rect_.width()},
        {"h", rect_.height()},
        {"c", col.str()}
    };
}
