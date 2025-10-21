#pragma once

#include <iostream>
#include <memory>

#include "model.h"
#include "view.h"
#include "rect.h"
#include "circle.h"

class Controller {
public:
    Controller(Model &m, View &v) : model(m), view(v) {}

    void AddRect() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        auto rect = std::make_unique<Rect>(10, 10, 100, 50, 100);
        model.AddFigure(std::move(rect));            
    }; 

    void AddCircle() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        auto circle = std::make_unique<Circle>(200, 150 , 40, 100);
        model.AddFigure(std::move(circle));
    }

    void RemoveLastFigure() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        model.RemoveLastFigure();
    }

    void ImportDoc(const std::string &filename) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if(!model.SaveToFile(filename))
            std::cout << "Error open file " << filename << std::endl;
    }

    void ExportDoc(const std::string &filename) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if (!model.LoadFromFile(filename))
            std::cout << "Error open file " << filename << std::endl;
    }
    void CreateNewDoc() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        model.CreateNew();
    }

private : 
    Model &model;
    View &view;
};