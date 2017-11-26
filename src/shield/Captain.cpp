#include "Captain.h"
#include "scarlet/TextView.h"
#include "scarlet/LinearLayout.h"
#include "scarlet/FixedView.h"
#include "SHIELD.h"
#include <hawkeye/HawkeyeView.h>
#include <hawkeye/Camera.h>

void avenger::scarlet::Captain::onCreate(SkCanvas *canvas) {
    std::vector<std::shared_ptr<View>> children;

    auto title = std::make_shared<TextView>("Captain");
    title->setFontSize(24);
    title->setFont("Product Sans");
    title->setColor(SK_ColorDKGRAY);

    children.push_back(title);
    auto fixedView = std::make_shared<FixedView>();
    fixedView->setColor(SK_ColorTRANSPARENT);
    fixedView->setRect(SkRect::MakeWH(100, 10));
    children.push_back(fixedView);

    children.push_back(camera);

    auto linearLayout = std::make_shared<LinearLayout>();
    linearLayout->addChildren(children);
    linearLayout->setDirection(LinearLayout::Direction::kVertical);
    linearLayout->setWidth(getDimensions().width());
    setRootView(linearLayout);
}

avenger::scarlet::Captain::Captain() {
    SHIELD::Init();
    camera = std::make_shared<avenger::hawkeye::HawkeyeView>();
    camera->getLayoutParams()->setHeight(720);
    camera->getLayoutParams()->setWidth(1280);
    avenger::hawkeye::Camera::AddListener(camera.get());
}

avenger::scarlet::Captain::~Captain() {
    SHIELD::Destroy();
}
