//
// Created by malcolm on 27/11/17.
//

#include "TelematicsView.h"

#include <string>
#include <utility>
#include <SkPaint.h>
#include <SkPath.h>
#include <SkCanvas.h>
#include <scarlet/LinearLayout.h>
#include <scarlet/TextView.h>
#include <scarlet/FixedView.h>
#include <SkFontStyle.h>

namespace avenger {
namespace reed {

std::shared_ptr<scarlet::TextView> makeText(std::string title) {
  auto textView = std::make_shared<scarlet::TextView>(title);
  textView->setFont("Product Sans", SkFontStyle::Bold());
  textView->setColor(SK_ColorGRAY);
  return textView;
}

std::shared_ptr<scarlet::FixedView> makeMargin(int size) {
  auto view = std::make_shared<scarlet::FixedView>();
  view->setColor(SK_ColorTRANSPARENT);
  view->setRect(SkRect::MakeWH(1, size));
  return view;
}

TelematicsView::TelematicsView(std::shared_ptr<Bot> b)
  : bot_{std::move(b)}, telematics_{}
{
  updateView();
}

void TelematicsView::onCreate(SkCanvas *canvas) {

}

void TelematicsView::onUpdate(std::shared_ptr<TelematicsEvent> event) {
  telematics_ = event->telematics();
  setDirty(true);
}

void TelematicsView::updateView() {
  auto verticalMargin = makeMargin(20);
  auto smallMargin = makeMargin(10);
  auto linearLayout = std::make_shared<scarlet::LinearLayout>();
  linearLayout->setDirection(scarlet::LinearLayout::Direction::kVertical);
  linearLayout->setWidth(1855 - 1220);

  auto title = makeText("Telematics");
  title->setColor(SK_ColorDKGRAY);
  title->setFontSize(24);

  auto subtitle = makeText(std::string("Bot ") + std::to_string(bot()->getId()));
  subtitle->setFontSize(18);

  linearLayout->addChild(verticalMargin);
  linearLayout->addChild(title);
  linearLayout->addChild(verticalMargin);
  linearLayout->addChild(subtitle);
  linearLayout->addChild(smallMargin);

  auto positionText = makeText(std::string("Position: (")
                                   + std::to_string(telematics_.location.x)
                                   + ", " + std::to_string(telematics_.location.y)
                                   + ")");
  positionText->setFontSize(15);
  linearLayout->addChild(positionText);
  linearLayout->getLayoutParams()->setX(getLayoutParams()->getX());
  linearLayout->getLayoutParams()->setY(getLayoutParams()->getY());
  linearLayout->updateLayout();

  getLayoutParams()->setWidth(linearLayout->getLayoutParams()->getWidth());
  getLayoutParams()->setHeight(linearLayout->getLayoutParams()->getHeight());
  setRootView(linearLayout);
}

void TelematicsView::setWidth(Scalar width) {
  getLayoutParams()->setWidth(width);
  updateView();
}

void TelematicsView::setHeight(Scalar height) {
  getLayoutParams()->setHeight(height);
  updateView();
}

}
}