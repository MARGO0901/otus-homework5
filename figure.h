#ifndef FIGURE_H
#define FIGURE_H

//#include <QJsonObject>
//#include <QPainter>
#include <memory>

#include <iostream>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;


class Rect;
class Circle;

class Figure
{
public:
    virtual ~Figure() = default;
    virtual void Draw() const = 0;

    virtual json toJson() const = 0;
    static std::unique_ptr<Figure> fromJson(const json &obj);
};

#endif // FIGURE_H
