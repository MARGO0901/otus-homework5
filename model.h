#pragma once

#include "include/nlohmann/json.hpp"
#include <iostream>
#include <memory>
#include <vector>

#include "figure.h"

class Model {
public:
    Model();
    void AddFigure(std::unique_ptr<Figure> figure);
    void RemoveLastFigure();
    bool SaveToFile(const std::string &filename);
    bool LoadFromFile(const std::string &fileName);
    void CreateNew();

    std::vector<std::unique_ptr<Figure>> figures;
};