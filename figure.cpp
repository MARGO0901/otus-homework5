#include "figure.h"

#include "rect.h"
#include "circle.h"

std::unique_ptr<Figure> Figure::fromJson(const json &obj) {
    std::string type = obj["type"].get<std::string>();
    if (type == "rect") {
        int x = obj["x"].get<int>();
        int y = obj["y"].get<int>();
        int w = obj["w"].get<int>();
        int h = obj["h"].get<int>();
        std::string c_str = obj["c"].get<std::string>();
        QColor c(c_str.c_str());
        return std::unique_ptr<Figure>(new Rect(QRect(x, y, w, h), c));
    }
    else if (type == "circle") {
        int cx = obj["cx"].get<int>();
        int cy = obj["cy"].get<int>();
        int r = obj["r"].get<int>();
        std::string c_str = obj["c"].get<std::string>();
        QColor c(c_str.c_str());
        return std::unique_ptr<Figure>(new Circle(QPoint(cx, cy), r, c));
    }
    return nullptr;
}
