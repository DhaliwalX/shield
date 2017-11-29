//
// Created by malcolm on 28/11/17.
//

#include "BotPollDetector.h"
#include <opencv2/opencv.hpp>

using namespace cv;

bool hasMaxOfRed(cv::Mat &mat) {
  std::vector<cv::Mat> channels;

  split(mat, channels);

  Mat red;

  threshold(channels[0], red, 11, 55, THRESH_BINARY);

  double imageSize = mat.cols * mat.rows;
  double percentage = (double)countNonZero(red) / imageSize;

  std::cout << percentage << std::endl;
  if (percentage < 0.5) {
    std::cout << "Red and red only" << std::endl;
    return true;
  }

  return false;
}

int keepInLimits(int start, int end, int val) {
  if (val < start)
    return start;
  if (val > end)
    return end;

  return val;
}

std::vector<avenger::reed::DetectorResult>
avenger::reed::BotPollDetector::runOn(cv::Mat &mat) {
  std::vector<DetectorResult> results;
  cv::Mat color;

  if (color.empty())
    return {};

  cv::Mat canny;

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
    int radius = cvRound(i[2]);

    Rect2d region;
    region.x = keepInLimits(0, color.cols, i[0] - radius);
    region.y = keepInLimits(0, color.rows, i[1] - radius);
    region.width = MIN(region.x + 2 * radius, color.cols) - region.x;
    region.height = MIN(region.y + 2 * radius, color.rows) - region.y;
    cv::Mat bot = color(region);

    if (hasMaxOfRed(bot)) {
      results.emplace_back(center, radius);
    }
  }

  return results;
}
