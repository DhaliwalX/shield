#ifndef HELLOWORLD_MAINAPP_H
#define HELLOWORLD_MAINAPP_H

#include "../scarlet/App.h"

#include "hawkeye/HawkeyeView.h"

namespace avenger {
    namespace scarlet {

        class Captain : public App {
        public:
            Captain();

            ~Captain();

            void onCreate(SkCanvas *canvas) override;

        private:
            std::shared_ptr<avenger::hawkeye::HawkeyeView> camera;
        };
    }
}

#endif //HELLOWORLD_MAINAPP_H
