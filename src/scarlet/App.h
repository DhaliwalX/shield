//
// Created by malcolm on 22/11/17.
//

#ifndef HELLOWORLD_APP_H
#define HELLOWORLD_APP_H

#include "GlContext.h"
#include "View.h"

namespace avenger {
namespace scarlet {
class App : public View {
 public:
  App() : root{nullptr}, dimensions{} {}

  ~App() override {}
  void onCreate(SkCanvas* canvas) override = 0;

  virtual void onForceUpdate(GlContext* context){};

  void setRootView(std::shared_ptr<View> view);

  void setDimensions(const SkRect& rect);
  SkRect& getDimensions();

  void draw(SkCanvas* canvas) override;

 private:
  std::shared_ptr<View> root;
  SkRect dimensions;
};
}
}

#endif  // HELLOWORLD_APP_H
