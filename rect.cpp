#include "rect.h"

void Rect::Draw() const {
    std::cout << "Draw rect: x = " << x_ << " y = " << y_ << 
                " height = " << height_ << " width = " << width_ << " color = " << color_ << std::endl;
}

json Rect::toJson() const {
    return json{
        {"type", "rect"},
        {"x", x_},
        {"y", y_},
        {"h", height_},
        {"w", width_},
        {"c", color_}
    };
}
