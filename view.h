#pragma once

#include <iostream>

#include "model.h"

class View {

public:
    void DrawScene(const Model &model) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        for (const auto &fig : model.figures) {
            fig->Draw();
        }
    }
};