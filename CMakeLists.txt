cmake_minimum_required(VERSION 3.8)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/FindFontConfig.cmake)
include(cmake/FindWebP.cmake)

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(SDL2 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)
find_package(WebP REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

set(SKIA_DIRECTORY "/home/malcolm/source/repos/skia")
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${SKIA_DIRECTORY}/include/core
        ${SKIA_DIRECTORY}/include/config
        ${SKIA_DIRECTORY}/include/effects
        ${SKIA_DIRECTORY}/include/ports
        ${SKIA_DIRECTORY}/include/utils
        ${SKIA_DIRECTORY}/include/svg
        ${SKIA_DIRECTORY}/include/pathops
        ${SKIA_DIRECTORY}/include/gpu
        ${SKIA_DIRECTORY}/include/privates
        ${SKIA_DIRECTORY}/src/gpu
        ${SKIA_DIRECTORY}/src/core
        ${SKIA_DIRECTORY}/src/views
        ${SKIA_DIRECTORY}/src/effects
        ${SKIA_DIRECTORY}/src/
        ${SKIA_DIRECTORY}/include/views
        )
set(SOURCE_FILES src/shield/main.cpp src/scarlet/App.cpp src/scarlet/App.h src/scarlet/GlContext.cpp src/scarlet/GlContext.h src/scarlet/NativeWindow.cpp src/scarlet/NativeWindow.h src/spidey/MatToBitmapConvertor.h src/scarlet/View.cpp src/scarlet/View.h src/shield/events/Event.cpp src/shield/events/Event.h src/scarlet/TextView.cpp src/scarlet/TextView.h src/shield/Captain.cpp src/shield/Captain.h src/scarlet/LinearLayout.cpp src/scarlet/LinearLayout.h src/scarlet/FixedView.cpp src/scarlet/FixedView.h src/scarlet/FlexView.cpp src/scarlet/FlexView.h src/shield/events/EventListener.h src/hawkeye/Camera.cpp src/hawkeye/Camera.h src/spidey/CircularQueue.cpp src/spidey/CircularQueue.h src/shield/CameraView.cpp src/shield/CameraView.h src/shield/events/TaskQueue.cpp src/shield/events/TaskQueue.h src/shield/SHIELD.cpp src/shield/SHIELD.h src/hawkeye/FrameCaptureEvent.cpp src/hawkeye/FrameCaptureEvent.h src/hawkeye/FrameCaptureEventListener.h src/shield/events/dispatcher.cpp src/shield/events/dispatcher.h src/hawkeye/HawkeyeView.cpp src/hawkeye/HawkeyeView.h src/shield/events/Processor.cpp src/shield/events/Processor.h src/hawkeye/FrameCaptureEventListener.cpp src/strange/IOService.cpp src/strange/IOService.h src/strange/Server.cpp src/strange/Server.h src/strange/TCPConnection.cpp src/strange/TCPConnection.h src/strange/ConnectionEvent.cpp src/strange/ConnectionEvent.h src/strange/ConnectionEventListener.cpp src/strange/ConnectionEventListener.h)
add_executable(Avengers ${SOURCE_FILES})
target_link_libraries(Avengers ${OpenCV_LIBS}
        ${SKIA_DIRECTORY}/out/Static/libskia.a
        ${GLUT_LIBRARIES}
        ${SDL2_LIBRARIES}
        Threads::Threads
        ${FREETYPE_LIBRARIES}
        ${CMAKE_DL_LIBS}
        ${FONTCONFIG_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${ZLIB_LIBRARIES}
        ${PNG_LIBRARIES}
        ${JPEG_LIBRARIES}
        ${Boost_LIBRARIES}
        libwebp.a
        )