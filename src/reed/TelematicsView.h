//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_TELEMATICSVIEW_H
#define HELLOWORLD_TELEMATICSVIEW_H

#include <scarlet/View.h>
#include <shield/Bot.h>
#include <scarlet/App.h>
#include "TelematicsEvent.h"
#include "PyBot.h"

namespace avenger {
namespace reed {

class TelematicsView : public scarlet::App {
 public:
  explicit TelematicsView(std::shared_ptr<Bot> bot);

  void onCreate(SkCanvas *canvas) override;

  void setWidth(Scalar width);
  void setHeight(Scalar height);

  void updateView();
};

}
}

#endif //HELLOWORLD_TELEMATICSVIEW_H
