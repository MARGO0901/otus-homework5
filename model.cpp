#include "model.h"

#include <fstream>

Model::Model() {}

void Model::AddFigure(std::unique_ptr<Figure> figure) {
    std::cout << __PRETTY_FUNCTION__ << std:: endl;
    figures.push_back(std::move(figure));
}

void Model::RemoveLastFigure() {
  if (!figures.empty()) {
    figures.pop_back();
  }
}


bool Model::SaveToFile(const std::string &filename) {
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

bool Model::LoadFromFile(const std::string &fileName) {
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

    for (const auto val : rootObj["figures"]) {
        if (val.is_object()) {
        auto fig = Figure::fromJson(val);
        if (fig)
            figures.push_back(std::move(fig));
        }
    }
    return true;
}

// Создать новый
void Model::CreateNew() {
    figures.clear();
}