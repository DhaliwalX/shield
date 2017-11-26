//
// Created by malcolm on 22/11/17.
//

#ifndef HELLOWORLD_GLCONTEXT_H
#define HELLOWORLD_GLCONTEXT_H

#include <SkCanvas.h>
#include "NativeWindow.h"
namespace avenger {

namespace scarlet {
class ScreenDesc {
 public:
  ScreenDesc(uint16_t width, uint16_t height)
      : width_{width}, height_{height} {}

  const uint16_t& getWidth() const { return width_; }

  const uint16_t& getHeight() const { return height_; }

  void setHeight(uint16_t height) { this->height_ = height; }

  void setWidth(uint16_t width) { this->width_ = width; }

 private:
  uint16_t width_;
  uint16_t height_;
};

class NativeWindowFactory;

class GlContext {
 public:
  void printDebugInfo(NativeWindow* window);

  explicit GlContext(const ScreenDesc& desc, NativeWindowFactory* factory)
      : screenDesc{desc}, windowFactory_{factory} {}

 public:
  static std::shared_ptr<GlContext> Make(int* argc, char** argv);

  std::shared_ptr<NativeWindow> makeWindow(uint16_t width,
                                           uint16_t height,
                                           uint16_t x,
                                           uint16_t y);

  std::shared_ptr<NativeWindow> makeWindow();

  ~GlContext();

  void swapBuffers(int windowId);

  void resizeWindow(NativeWindow* window, int w, int h);

 private:
  ScreenDesc screenDesc;

  // keeps the implmentation of native window independent of platform
  NativeWindowFactory* windowFactory_;
};

}  // ui
}

#endif  // HELLOWORLD_GLCONTEXT_H
