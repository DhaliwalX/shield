//
// Created by malcolm on 25/11/17.
//

#include "TextView.h"

#include <SkPaint.h>
#include <SkTypeface.h>
#include <SkCanvas.h>
#include <SkBitmap.h>

namespace avenger {
namespace scarlet {

struct FontMetadata {
  SkPaint paint;
};

TextViewData::TextViewData(const std::string& text)
    : text_{text}, metadata_{new FontMetadata} {
  metadata_->paint.setAntiAlias(true);
}

TextViewData::~TextViewData() {
  delete metadata_;
}

SkRect TextViewData::getBounds() {
  SkRect result{};
  metadata_->paint.measureText(text_.c_str(), text_.size(), &result);
  return result;
}

void TextViewData::setText(const std::string& text) {
  text_ = text;
}

void TextViewData::setFontSize(SkScalar scalar) {
  metadata_->paint.setTextSize(scalar);
}

void TextViewData::setFont(const std::string& fontName) {
  auto typeface =
      SkTypeface::MakeFromName(fontName.c_str(), SkFontStyle::Normal());
  metadata_->paint.setTypeface(typeface);
}

void TextView::onCreate(SkCanvas* canvas) {
  auto dimensions = data_.getBounds();
  canvas->drawText(
      data_.text_.c_str(), data_.text_.length(), getLayoutParams()->getX(),
      getLayoutParams()->getY() + dimensions.height(), data_.metadata_->paint);
}

TextView::TextView() : data_{TextViewData("")} {
  updateLayoutParams();
}

void TextView::updateLayoutParams() {
  auto dimensions = data_.getBounds();
  layoutParams_->patchWH(dimensions);
}

void TextView::setText(const std::string& text) {
  // doesn't update the layout params
  data_.setText(text);
}

TextView::TextView(const std::string& text) : data_{TextViewData(text)} {
  updateLayoutParams();
}

void TextView::setFont(const std::string& fontName) {
  data_.setFont(fontName);
}

void TextView::setColor(SkColor color) {
  data_.metadata_->paint.setColor(color);
}

void TextView::setFontSize(SkScalar scalar) {
  data_.setFontSize(scalar);
  updateLayoutParams();
}
}
}
