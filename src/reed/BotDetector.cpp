//
// Created by malcolm on 27/11/17.
//

#include "BotDetector.h"
#include <opencv2/opencv.hpp>

std::vector<avenger::reed::DetectorResult>
avenger::reed::BotDetector::runOn(cv::Mat &mat) {
  cv::Mat &color = mat;
  cv::Mat canny;

  std::vector<DetectorResult> result;
  cv::Mat gray;
  /// Convert it to gray
  cv::cvtColor(color, gray, CV_BGR2GRAY);

  // compute canny (don't blur with that image quality!!)
  cv::Canny(gray, canny, 200, 20);

  std::vector<cv::Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  cv::HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, 100, 200, 20, 20, 50);

  /// Draw the circles detected
  for (auto &i : circles) {
    Point center(cvRound(i[0]), cvRound(i[1]));
    auto radius = (i[2]);
    result.emplace_back(center, radius);

    cv::circle(color, cv::Point(cvRound(i[0]), cvRound(i[1])), radius, cv::Vec3d(255, 0, 0));
  }

  cv::imshow("Live", color);

  cv::waitKey(1);

  return result;
}
