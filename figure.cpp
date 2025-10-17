#include "figure.h"

#include "rect.h"
#include "circle.h"

std::unique_ptr<Figure> Figure::fromJson(const json &obj) {
    std::string type = obj["type"].get<std::string>();
    if (type == "rect") {
        int x = obj["x"].get<int>();
        int y = obj["y"].get<int>();
        int h = obj["h"].get<int>();
        int w = obj["w"].get<int>();
        int c = obj["c"].get<int>();
        return std::unique_ptr<Figure>(new Rect(x, y, h, w, c));
    }
    else if (type == "circle") {
        int x = obj["cx"].get<int>();
        int y = obj["cy"].get<int>();
        int r = obj["r"].get<int>();
        int c = obj["c"].get<int>();
        return std::unique_ptr<Figure>(new Circle(x, y, r, c));
    }
    return nullptr;
}
