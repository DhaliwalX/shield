#ifndef HELLOWORLD_MATTOBITMAPCONVERTOR_H
#define HELLOWORLD_MATTOBITMAPCONVERTOR_H

#include <vector>
#include <cstdint>
#include <opencv2/core/mat.hpp>
#include <iostream>
#include <SkColor.h>

class BitmapRef {
 public:
  ~BitmapRef() { dealloc(); }

  void alloc(int size) {
    if (this->size == size) {
      return;
    }
    data.resize(static_cast<unsigned long>(size), 0);
    this->size = size;
  }

  void dealloc() { size = 0; }

  std::vector<uint8_t> data;
  int size = 0;
};

class MatToBitmapConvertor {
 public:
  void convertToBitmap(BitmapRef* ref, const cv::Mat& mat) {
    ref->alloc(mat.cols * mat.rows * 4 * 4);
    int i = 0;
    for (int n = 0; n < mat.rows; n++)
      for (int j = 0; j < mat.cols; j++) {
        ref->data[i++] = mat.at<cv::Vec3b>(n, j)[2];
        ref->data[i++] = mat.at<cv::Vec3b>(n, j)[1];
        ref->data[i++] = mat.at<cv::Vec3b>(n, j)[0];
        ref->data[i++] = 255;
      }
  }
};

#endif  // HELLOWORLD_MATTOBITMAPCONVERTOR_H
