#ifndef HELLOWORLD_LINEARLAYOUT_H
#define HELLOWORLD_LINEARLAYOUT_H

#include <vector>
#include "View.h"
#include <SkBitmap.h>

namespace avenger {
namespace scarlet {

class LinearLayout : public View {
 public:
  enum class Direction { kHorizontal, kVertical };

  LinearLayout();

  void addChild(std::shared_ptr<View> view);

  void addChildren(std::vector<std::shared_ptr<View>> children);

  void setDirection(Direction direction);

  void onCreate(SkCanvas* canvas) override;

  void setHeight(SkScalar height);

  void setWidth(SkScalar width);

  void updateLayout();
 private:
  std::unique_ptr<SkCanvas> allocCanvas();

  Direction direction_;

  std::vector<std::shared_ptr<View>> children_;

  // this bitmap will store all the information
  std::unique_ptr<SkBitmap> bitmap_;

  SkScalar getHeight();

  SkScalar getWidth();

  SkRect calculateDimensions();
};
}
}

#endif  // HELLOWORLD_LINEARLAYOUT_H
