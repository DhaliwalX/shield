#ifndef HELLOWORLD_MAINAPP_H
#define HELLOWORLD_MAINAPP_H

#include <reed/TelematicsView.h>
#include <scarlet/LinearLayout.h>
#include "../scarlet/App.h"

#include "hawkeye/HawkeyeView.h"

namespace avenger {
namespace scarlet {

class Captain : public App {
 public:
  using TelematicsPointer = std::shared_ptr<avenger::reed::TelematicsView>;
  Captain();

  ~Captain();

  void onCreate(SkCanvas* canvas) override;

 private:
  std::shared_ptr<avenger::hawkeye::HawkeyeView> camera;
  std::shared_ptr<LinearLayout> telematicsLayout;
  TelematicsPointer telematics;
};
}
}

#endif  // HELLOWORLD_MAINAPP_H
