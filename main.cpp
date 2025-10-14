#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <memory.h>
#include <fstream>
#include <iostream>

#include "figure.h"
#include "circle.h"
#include "rect.h"

class Canvas : public QWidget {
    Q_OBJECT
public:
    // Добавить фигуру
    void AddFigure(std::unique_ptr<Figure> fig) {
        figures.push_back(std::move(fig));
        update();
    }
    // Удалить последний
    void RemoveLastFigure() {
        if (!figures.empty()) {
            figures.pop_back();
            update();
        }
    }
    //Сохранить в файл
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
            file << rootObj.dump(4);    //отступ для читаемости
        } catch (const std::exception &e) {
            std::cerr << "Exception while parsing JSON: " << e.what() << std::endl;
            return false;
        }
        file.close();
        return true;
    }
    //Выгрузить из файла
    bool loadFromFile(const std::string &fileName) {
        std::ifstream file(fileName);
        if (!file.is_open())
            return false;

        json rootObj;
        try {
            file >> rootObj;
        }
        catch (const std::exception &e) {
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

        update();
        return true;
    }
    //Создать новый
    void CreateNew() {
        figures.clear();
        count = 0;

        QPainter painter(this);
        painter.fillRect(rect(), Qt::white);

        update();
    }

    int count = 0;

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter painter(this);
        painter.fillRect(rect(), Qt::white);

        for (const auto& fig : figures) {
            fig->Draw(painter);
        }
    }

private:
    std::vector<std::unique_ptr<Figure>> figures;

};



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Графический редактор");
    QVBoxLayout* layout = new QVBoxLayout(&window);

    QPushButton* saveJSON= new QPushButton("Сохранить", &window);
    QPushButton* openJSON= new QPushButton("Открыть", &window);
    QPushButton* createNew= new QPushButton("Создать новый", &window);
    layout->addWidget(createNew);
    layout->addWidget(openJSON);
    layout->addWidget(saveJSON);



    Canvas* canvas = new Canvas;
    canvas->setFixedSize(500, 300);
    layout->addWidget(canvas);

    QPushButton* addRect = new QPushButton("Добавить прямоугольник", &window);
    QPushButton* addCircle = new QPushButton("Добавить круг", &window);
    QPushButton* deleteFigure = new QPushButton("Удалить последний", &window);

    layout->addWidget(addRect);
    layout->addWidget(addCircle);
    layout->addWidget(deleteFigure);


    // Соединяем сигналы кнопок с нашими слотами
    QObject::connect(addRect, &QPushButton::clicked, [canvas]() {
        QRect rect(10 + canvas->count * 20, 10 + canvas->count * 15, 100, 50);
        canvas->AddFigure(std::unique_ptr<Figure>(std::make_unique<Rect>(rect, Qt::red).release()));
        canvas->count++;
    });

    QObject::connect(addCircle, &QPushButton::clicked, [canvas]() {
        canvas->AddFigure(std::unique_ptr<Figure>(std::make_unique<Circle>(QPoint(200 + canvas->count*20, 150 + canvas->count*20), 40, Qt::blue).release()));
        canvas->count++;
    });
    QObject::connect(deleteFigure, &QPushButton::clicked, [canvas]() {canvas->RemoveLastFigure();});

    QObject::connect(saveJSON, &QPushButton::clicked, [canvas]() {canvas->SaveToFile("figures.json");});
    QObject::connect(openJSON, &QPushButton::clicked, [canvas]() {canvas->loadFromFile("figures.json");});
    QObject::connect(createNew, &QPushButton::clicked, [canvas]() {canvas->CreateNew();});


    window.show();

    return app.exec();
}

#include "main.moc"
