#include <iostream>
#include <opencv2/opencv.hpp>

cv::Point2f pointCamToImg(const cv::Mat &K, const cv::Mat &R, const cv::Mat &t, const cv::Mat &P_cam) {
    // 转换为齐次坐标
    cv::Mat P_cam_homo(4, 1, CV_64F);
    P_cam_homo.at<double>(0, 0) = P_cam.at<double>(0, 0);
    P_cam_homo.at<double>(1, 0) = P_cam.at<double>(1, 0);
    P_cam_homo.at<double>(2, 0) = P_cam.at<double>(2, 0);
    P_cam_homo.at<double>(3, 0) = 1.0;

    // 构建[R|t]矩阵
    cv::Mat Rt(3, 4, CV_64F);
    R.copyTo(Rt(cv::Rect(0, 0, 3, 3)));
    t.copyTo(Rt(cv::Rect(3, 0, 1, 3)));

    // 计算图像坐标系下的点（齐次坐标）
    cv::Mat P_img_homo = K * Rt * P_cam_homo;

    // 转换为非齐次坐标
    float u = P_img_homo.at<double>(0, 0) / P_img_homo.at<double>(2, 0);
    float v = P_img_homo.at<double>(1, 0) / P_img_homo.at<double>(2, 0);

    return cv::Point2f(u, v);
}

int main() {
    cv::Mat K = (cv::Mat_<double>(3, 3) << 700, 0, 300, 0, 700, 200, 0, 0, 1);
    cv::Mat R = (cv::Mat_<double>(3, 3) << 0.866, -0.5, 0, 0.5, 0.866, 0, 0, 0, 1);
    cv::Mat t = (cv::Mat_<double>(3, 1) << 0, 0, 5);
    cv::Mat P_cam = (cv::Mat_<double>(3, 1) << 1, 1, 10);

    cv::Point2f P_img = pointCamToImg(K, R, t, P_cam);
    std::cout << "转换后的图像坐标为: (" << P_img.x << ", " << P_img.y << ")" << std::endl;

    return 0;
}
