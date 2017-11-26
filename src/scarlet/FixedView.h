//
// Created by malcolm on 25/11/17.
//

#ifndef HELLOWORLD_FIXEDVIEW_H
#define HELLOWORLD_FIXEDVIEW_H

#include <SkColor.h>
#include "View.h"

namespace avenger {
namespace scarlet {

// provides a simple colored rectangle for testing
class FixedView : public View {
 public:
  FixedView() : rect_{}, color_{} {}

  void onCreate(SkCanvas* canvas) override;

  void setColor(SkColor color);
  void setRect(SkRect rect);

 private:
  SkRect rect_;
  SkColor color_;
};
}
}

#endif  // HELLOWORLD_FIXEDVIEW_H
