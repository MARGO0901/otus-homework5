#include "controller.h"

int main() {
    Model model;
    View view;
    Controller controller(model, view);

    controller.AddRect();
    controller.AddCircle();
    controller.RemoveLastFigure();
    controller.ImportDoc("figures.json");
    controller.ExportDoc("figures.json");

    view.DrawScene(model);

    controller.CreateNewDoc();

    return 0;
}