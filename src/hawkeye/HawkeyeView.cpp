#include "HawkeyeView.h"
#include <SkCanvas.h>

void convertMatToBitmap(BitmapRef *bitmapCache, SkBitmap &bitmap, cv::Mat &mat) {
    auto info = SkImageInfo::Make(mat.cols, mat.rows,
                                  SkColorType::kRGBA_8888_SkColorType,
                                  SkAlphaType::kPremul_SkAlphaType);
    MatToBitmapConvertor convertor;

    convertor.convertToBitmap(bitmapCache, mat);

    SkPixmap pixmap(info, bitmapCache->data.data(), mat.cols * 4);
    bitmap.allocPixels(info);
    bitmap.installPixels(pixmap);
}

void avenger::hawkeye::HawkeyeView::onCreate(SkCanvas *canvas) {
    SkBitmap actualImage;
    avenger::scarlet::LayoutParams *layoutParams = getLayoutParams();

    auto info = SkImageInfo::MakeN32Premul(
            SkScalarRoundToInt(layoutParams->getWidth()),
            SkScalarRoundToInt(layoutParams->getHeight()));
    actualImage.allocPixels(info);

    SkCanvas imageCanvas(actualImage);
    SkMatrix matrix;
    matrix.setScale(layoutParams->getWidth() / currentFrame_->cols,
                    layoutParams->getHeight() / currentFrame_->rows);
    imageCanvas.setMatrix(matrix);
    imageCanvas.drawBitmap(store_, 0, 0);
    canvas->drawBitmap(actualImage, layoutParams->getX(), layoutParams->getY());
}

void avenger::hawkeye::HawkeyeView::onCapture(avenger::hawkeye::FrameCaptureEvent *event) {
    std::lock_guard<std::mutex> guard(lock_);
    *currentFrame_ = *event->getCapturedFrame();
    convertMatToBitmap(&bitmapCache_, store_, *currentFrame_);
}

avenger::hawkeye::HawkeyeView::HawkeyeView()
    : currentFrame_{std::make_shared<cv::Mat>()} {

}
