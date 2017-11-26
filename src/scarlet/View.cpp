//
// Created by malcolm on 25/11/17.
//

#include <memory>
#include "View.h"

void avenger::scarlet::View::onDestroy() {

}

avenger::scarlet::LayoutParams *avenger::scarlet::View::getLayoutParams() {
    return layoutParams_.get();
}

void avenger::scarlet::View::setLayoutParams(std::unique_ptr<avenger::scarlet::LayoutParams> params) {
    layoutParams_ = std::move(params);
}

avenger::scarlet::View::View()
: layoutParams_{ std::make_unique<LayoutParams>() }, dirty_{ true }
{}

void avenger::scarlet::View::draw(SkCanvas *canvas) {
    onCreate(canvas);
}

bool avenger::scarlet::View::isDirty() {
    return dirty_;
}

void avenger::scarlet::View::setDirty(bool dirty) {
    dirty_ = dirty;
}

std::unique_ptr<avenger::scarlet::LayoutParams> avenger::scarlet::LayoutParams::MakeSkRect(const SkRect &rect) {
    std::unique_ptr<LayoutParams> params = std::make_unique<avenger::scarlet::LayoutParams>();
    params->setBounds(rect);
}

std::unique_ptr<avenger::scarlet::LayoutParams> avenger::scarlet::LayoutParams::MakeDefault() {
    return std::make_unique<avenger::scarlet::LayoutParams>();
}

void avenger::scarlet::LayoutParams::patchWH(const SkRect &rect) {
    bounds_.setWH(rect.width(), rect.height());
}

SkScalar avenger::scarlet::LayoutParams::getHeight() {
    return bounds_.height();
}

SkScalar avenger::scarlet::LayoutParams::getWidth() {
    return bounds_.width();
}

SkScalar avenger::scarlet::LayoutParams::getX() {
    return bounds_.x();
}

SkScalar avenger::scarlet::LayoutParams::getY() {
    return bounds_.y();
}

void avenger::scarlet::LayoutParams::setHeight(SkScalar height) {
    bounds_.setXYWH(bounds_.x(), bounds_.y(), bounds_.width(), height);
}

void avenger::scarlet::LayoutParams::setWidth(SkScalar width) {
    bounds_.setXYWH(bounds_.x(), bounds_.y(), width, bounds_.height());
}

void avenger::scarlet::LayoutParams::setX(SkScalar x) {
    bounds_.setXYWH(x, bounds_.y(), bounds_.width(), bounds_.height());
}

void avenger::scarlet::LayoutParams::setY(SkScalar y) {
    bounds_.setXYWH(bounds_.x(), y, bounds_.width(), bounds_.height());
}

void avenger::scarlet::LayoutParams::setPadding(SkRect padding) {
    padding_ = padding;
}

void avenger::scarlet::LayoutParams::setMargin(SkRect margin) {
    margin_ = margin;
}

SkRect avenger::scarlet::LayoutParams::getPadding() {
    return padding_;
}

SkRect avenger::scarlet::LayoutParams::getMargin() {
    return margin_;
}
