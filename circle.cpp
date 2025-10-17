#include "circle.h"


void Circle::Draw() const {
    std::cout << "Draw circle x = " << x_ << " y = " << y_ << 
                " radius = " << radius_ << " color = " << color_ << std::endl;
}

json Circle::toJson() const {
    return json{
        {"type", "circle"},
        {"cx", x_},
        {"cy", y_},
        {"r", radius_},
        {"c", color_}
    };
}
