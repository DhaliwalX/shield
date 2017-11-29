#include "Captain.h"
#include "scarlet/TextView.h"
#include "scarlet/LinearLayout.h"
#include "scarlet/FixedView.h"
#include "SHIELD.h"
#include "Bot.h"
#include <hawkeye/HawkeyeView.h>
#include <hawkeye/Camera.h>
#include <reed/TelematicsView.h>

void avenger::scarlet::Captain::onCreate(SkCanvas* canvas) {

}

avenger::scarlet::Captain::Captain() {
  SHIELD::Init();

  camera = std::make_shared<avenger::hawkeye::HawkeyeView>();
  camera->getLayoutParams()->setHeight(720);
  camera->getLayoutParams()->setWidth(1280);
  avenger::hawkeye::Camera::AddListener(camera.get());

  auto bot = avenger::Bot::Create(nullptr);
  telematics = std::make_shared<avenger::reed::TelematicsView>(bot);
  telematics->setWidth(1855 - 1280);
  telematics->setHeight(1056);

  std::vector<std::shared_ptr<View>> children;

  auto fixedView = std::make_shared<FixedView>();
  fixedView->setColor(SK_ColorTRANSPARENT);
  fixedView->setRect(SkRect::MakeWH(100, 20));

  auto title = std::make_shared<TextView>("Captain");
  title->setFontSize(32);
  title->setFont("Product Sans");
  title->setColor(SK_ColorDKGRAY);

  children.push_back(fixedView);
  children.push_back(title);
  children.push_back(fixedView);

  children.push_back(camera);

  auto leftView = std::make_shared<LinearLayout>();
  leftView->addChildren(children);
  leftView->setDirection(LinearLayout::Direction::kVertical);
  leftView->setWidth(1280);

  auto horizontalLayout = std::make_shared<LinearLayout>();
  horizontalLayout->setDirection(LinearLayout::Direction::kHorizontal);
  horizontalLayout->setHeight(1056);


  auto rightView = std::make_shared<LinearLayout>();
  rightView->setDirection(LinearLayout::Direction::kVertical);
  rightView->setWidth(1855 - 1220);
  rightView->addChild(telematics);

  auto margin = std::make_shared<FixedView>();
  margin->setColor(SK_ColorTRANSPARENT);
  margin->setRect(SkRect::MakeWH(20, 10));

  horizontalLayout->addChild(margin);
  horizontalLayout->addChild(leftView);
  horizontalLayout->addChild(margin);
  horizontalLayout->addChild(rightView);
  horizontalLayout->addChild(margin);
  setRootView(telematics);

  updateThread();
}

avenger::scarlet::Captain::~Captain() {
  SHIELD::Destroy();
  shouldStop = true;
  teleThread->join();
}

void avenger::scarlet::Captain::updateThread() {
}
