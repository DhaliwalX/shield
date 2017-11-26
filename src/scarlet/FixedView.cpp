//
// Created by malcolm on 25/11/17.
//
#include "FixedView.h"

#include <SkPaint.h>
#include <SkCanvas.h>

void avenger::scarlet::FixedView::onCreate(SkCanvas *canvas) {
    SkRect rect = rect_;
    SkPaint paint;
    paint.setColor(SK_ColorTRANSPARENT);
    paint.setStrokeWidth(10);
    paint.setColor(color_);
    rect.offset(getLayoutParams()->getX(), getLayoutParams()->getY());
    canvas->drawRect(rect, paint);
}

void avenger::scarlet::FixedView::setRect(SkRect rect) {
    rect_ = rect;
    getLayoutParams()->setBounds(rect);
}

void avenger::scarlet::FixedView::setColor(SkColor color) {
    color_ = color;
}
