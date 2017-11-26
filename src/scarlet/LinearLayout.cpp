#include <SkImageInfo.h>
#include <SkBitmap.h>
#include <SkCanvas.h>
#include <algorithm>
#include "LinearLayout.h"

namespace avenger {
namespace scarlet {

LinearLayout::LinearLayout() : children_{}, direction_{Direction::kVertical} {}

void LinearLayout::addChild(std::shared_ptr<View> view) {
  children_.push_back(view);
  setDirty(true);
}

void LinearLayout::setDirection(LinearLayout::Direction direction) {
  direction_ = direction;
  setDirty(true);
}

std::unique_ptr<SkCanvas> LinearLayout::allocCanvas() {
  auto params = getLayoutParams();
  auto height = params->getHeight();
  auto width = params->getWidth();
  auto info = SkImageInfo::MakeN32Premul(SkScalarRoundToInt(width),
                                         SkScalarRoundToInt(height));

  if (!bitmap_) {
    bitmap_ = std::make_unique<SkBitmap>();
    bitmap_->allocPixels(info);
  }

  bitmap_->eraseColor(SK_ColorWHITE);

  std::unique_ptr<SkCanvas> canvas = std::make_unique<SkCanvas>(*bitmap_);
  return canvas;
}

void LinearLayout::onCreate(SkCanvas* can) {
  if (!isDirty()) {
    can->drawBitmap(*bitmap_, getLayoutParams()->getX(),
                    getLayoutParams()->getY());
    return;
  }

  updateLayout();
  auto canHandle = allocCanvas();
  auto canvas = canHandle.get();
  SkScalar x = 0, y = 0;
  for (auto& child : children_) {
    auto bounds = child->getLayoutParams();

    switch (direction_) {
      case Direction::kHorizontal:
        bounds->setX(x);
        break;

      case Direction::kVertical:
        bounds->setY(y);
        break;
    }

    child->draw(canvas);

    // update the x,y and current dimensions of this structure
    switch (direction_) {
      case Direction::kHorizontal:
        x += bounds->getWidth();
        break;

      case Direction::kVertical:
        y += bounds->getHeight();
        break;
    }
  }

  can->drawBitmap(*bitmap_, getLayoutParams()->getX(),
                  getLayoutParams()->getY());
}

void LinearLayout::setHeight(SkScalar height) {
  setDirty(true);
  getLayoutParams()->setHeight(height);
}

SkScalar LinearLayout::getHeight() {
  return getLayoutParams()->getHeight();
}

void LinearLayout::setWidth(SkScalar width) {
  setDirty(true);
  getLayoutParams()->setWidth(width);
}

SkScalar LinearLayout::getWidth() {
  return getLayoutParams()->getWidth();
}

SkRect LinearLayout::calculateDimensions() {
  int width = 0, height = 0;

  for (auto& child : children_) {
    width += child->getLayoutParams()->getWidth();
    height += child->getLayoutParams()->getHeight();
  }

  return SkRect::MakeWH(width, height);
}

void LinearLayout::updateLayout() {
  SkRect rect = calculateDimensions();
  switch (direction_) {
    case Direction::kHorizontal:
      setWidth(rect.width());
      break;

    case Direction::kVertical:
      setHeight(rect.height());
      break;
  }
}

void LinearLayout::addChildren(std::vector<std::shared_ptr<View>> children) {
  setDirty(true);
  auto insertor = std::back_inserter(children_);
  std::copy(children.begin(), children.end(), insertor);
}
}
}
