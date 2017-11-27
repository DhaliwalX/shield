#ifndef HELLOWORLD_VIEW_H
#define HELLOWORLD_VIEW_H

#include <SkRect.h>
#include <memory>

class SkCanvas;
namespace avenger {
namespace scarlet {
class LayoutParams {
 public:
  static std::unique_ptr<LayoutParams> MakeDefault();

  static std::unique_ptr<LayoutParams> MakeSkRect(const SkRect& rect);

  LayoutParams() = default;
  virtual ~LayoutParams() = default;

  virtual void setBounds(SkRect bounds) { bounds_ = bounds; }

  virtual SkRect& getBounds() { return bounds_; }

  void setHeight(SkScalar height);

  void setWidth(SkScalar width);

  void setX(SkScalar x);

  void setY(SkScalar y);

  void setPadding(SkRect padding);

  void setMargin(SkRect margin);

  SkRect getPadding();

  SkRect getMargin();

  virtual void patchWH(const SkRect& rect);

  virtual const SkRect& getBounds() const { return bounds_; }

  SkScalar getHeight();
  SkScalar getWidth();
  SkScalar getX();
  SkScalar getY();

 private:
  SkRect bounds_{};
  SkRect padding_{};
  SkRect margin_{};
};

class View {
 protected:
  View();

 public:
  virtual ~View() = default;

  virtual void onCreate(SkCanvas* canvas) = 0;

  virtual void onDestroy();

  virtual LayoutParams* getLayoutParams();

  virtual void draw(SkCanvas* canvas);

  bool isDirty();
 protected:
  virtual void setLayoutParams(std::unique_ptr<LayoutParams> params);

  void setDirty(bool dirty);

 public:
  std::unique_ptr<LayoutParams> layoutParams_;

 private:
  bool dirty_;
};
}
}

#endif  // HELLOWORLD_VIEW_H
