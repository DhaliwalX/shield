//
// Created by malcolm on 22/11/17.
//

#include "App.h"

void avenger::scarlet::App::setRootView(std::shared_ptr<avenger::scarlet::View> view) {
    this->root = view;
}

void avenger::scarlet::App::draw(SkCanvas *canvas) {
    this->onCreate(canvas);
    if (canvas != nullptr && root) {
        canvas->clear(SK_ColorLTGRAY);
        root->draw(canvas);
    }
}

void avenger::scarlet::App::setDimensions(const SkRect &rect) {
    dimensions = rect;
}

SkRect &avenger::scarlet::App::getDimensions() {
    return dimensions;
}
