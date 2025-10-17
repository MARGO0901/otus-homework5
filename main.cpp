
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "figure.h"
#include "rect.h"
#include "circle.h"

class Canvas {
public:
    void AddFigure(std::unique_ptr<Figure> fig) {
        figures.push_back(std::move(fig));
        Update();
    }
    void RemoveLastFigure() {
      if (!figures.empty()) {
        figures.pop_back();
        Update();
      }
    }
    // Сохранить в файл
    bool SaveToFile(const std::string &filename) {
      json jsonArray = json::array();
      for (auto &fig : figures) {
        jsonArray.push_back(fig->toJson());
      }

      json rootObj;
      rootObj["figures"] = jsonArray;

      std::ofstream file(filename);
      if (!file.is_open()) {
        return false;
      }
      try {
        file << rootObj.dump(4); // отступ для читаемости
      } catch (const std::exception &e) {
        std::cerr << "Exception while parsing JSON: " << e.what() << std::endl;
        return false;
      }
      file.close();
      return true;
    }
    // Выгрузить из файла
    bool LoadFromFile(const std::string &fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cout << "File is not found" << std::endl;
            return false;
        }

        json rootObj;
        try {
            file >> rootObj;
        } catch (const std::exception &e) {
            return false;
        }

        if (!rootObj.contains("figures") || !rootObj["figures"].is_array()) {
            return false;
        }
        figures.clear();
        count = 0;

        for (const auto val : rootObj["figures"]) {
            if (val.is_object()) {
            auto fig = Figure::fromJson(val);
            if (fig)
                figures.push_back(std::move(fig));
            }
        }
        Update();
        return true;
    }
    // Создать новый
    void CreateNew() {
        figures.clear();
        count = 0;

        Update();
    }
    //счетчик фигур, чтобы изменять координаты новой
    int count = 0;
protected:
    void Update() {
      for (const auto &fig : figures) {
        fig->Draw();
      }
    }
private: 
    std::vector<std::unique_ptr<Figure>> figures;
};


void AddRect(Canvas &canvas) {
    Rect rect(10 + canvas.count * 20, 10 + canvas.count * 15, 100, 50, 100);
    canvas.AddFigure(std::unique_ptr<Figure>(
        std::make_unique<Rect>(rect).release()));
    canvas.count++;
}


void AddCircle(Canvas &canvas) {
    Circle circle(200 + canvas.count * 20, 150 + canvas.count * 20, 40, 100);
    canvas.AddFigure(
        std::unique_ptr<Figure>(std::make_unique<Circle>(circle).release()));
    canvas.count++;
}


int main()
{
    std::cout << __PRETTY_FUNCTION__ << " Graph editor started" << std::endl;

    Canvas canvas;

    std::cout << __PRETTY_FUNCTION__ << " Add rect:" << canvas.count + 1 << std::endl;
    AddRect(canvas);
    std::cout << __PRETTY_FUNCTION__ << " Add rect:" << canvas.count + 1 << std::endl;
    AddRect(canvas);

    std::cout << __PRETTY_FUNCTION__ << " Add circle:" << canvas.count + 1 << std::endl;
    AddCircle(canvas);
    std::cout << __PRETTY_FUNCTION__ << " Add circle:" << canvas.count + 1 << std::endl;
    AddCircle(canvas);

    std::cout << __PRETTY_FUNCTION__ << " Delete last figure:" << std::endl;
    canvas.RemoveLastFigure();

    std::cout << __PRETTY_FUNCTION__ << " Save to figures.json" << std::endl;
    canvas.SaveToFile("figures.json");

    std::cout << __PRETTY_FUNCTION__ << " Load from figures.json" << std::endl;
    canvas.LoadFromFile("figures.json");

    std::cout << __PRETTY_FUNCTION__ << " Create new canvas" << std::endl;
    canvas.CreateNew();

    return 0;
}

