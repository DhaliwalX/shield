//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_TELEMATICSVIEW_H
#define HELLOWORLD_TELEMATICSVIEW_H

#include <scarlet/View.h>
#include <shield/Bot.h>
#include <scarlet/App.h>
#include "TelematicsEvent.h"

namespace avenger {
namespace reed {

class TelematicsView : public scarlet::App, public TelematicsEventListener {
 public:
  explicit TelematicsView(std::shared_ptr<Bot> bot);

  void onCreate(SkCanvas *canvas) override;

  void onUpdate(std::shared_ptr<TelematicsEvent> event) override;

  std::shared_ptr<Bot> bot() override { return bot_; }

  void setWidth(Scalar width);
  void setHeight(Scalar height);

  void updateView();
 private:
  std::shared_ptr<Bot> bot_;
  BotTelematics telematics_{};
};

}
}

#endif //HELLOWORLD_TELEMATICSVIEW_H
