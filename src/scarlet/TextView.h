//
// Created by malcolm on 25/11/17.
//

#ifndef HELLOWORLD_TEXTVIEW_H
#define HELLOWORLD_TEXTVIEW_H

#include "View.h"

#include <string>
#include <SkColor.h>
#include <SkPaint.h>
#include <SkFontStyle.h>

namespace avenger {
namespace scarlet {

struct FontMetadata;

class TextViewData {
  friend class TextView;

 public:
  explicit TextViewData(const std::string& text_);

  ~TextViewData();

  void setText(const std::string& text_);

  void setFont(const std::string& fontName, const SkFontStyle &style);

  void setFontSize(SkScalar scalar);

  SkRect getBounds();

 private:
  std::string text_;
  FontMetadata* metadata_;
};

// simple TextView class to
class TextView : public View {
 public:
  TextView();
  explicit TextView(const std::string& text);

  void setText(const std::string& text);

  void onCreate(SkCanvas* canvas) override;

  void setFont(const std::string& fontName);

  void setColor(SkColor color);

  void setPaint(SkPaint paint);

  void setFontSize(SkScalar scalar);

  void setFont(const std::string &fontName, const SkFontStyle &style);
 private:
  void updateLayoutParams();

  TextViewData data_;
};
}
}

#endif  // HELLOWORLD_TEXTVIEW_H
