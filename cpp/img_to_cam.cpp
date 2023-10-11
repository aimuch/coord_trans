#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat pointImgToCam(const cv::Mat &K, const cv::Mat &R, const cv::Mat &t, const cv::Point2f &P_img, double Z) {
    // 构建[R|t]矩阵
    cv::Mat Rt(3, 4, CV_64F);
    R.copyTo(Rt(cv::Rect(0, 0, 3, 3)));
    t.copyTo(Rt(cv::Rect(3, 0, 1, 3)));

    // 计算[R|t]和K的逆矩阵
    cv::Mat K_inv = K.inv();
    cv::Mat Rt_inv;
    cv::invert(Rt(cv::Rect(0, 0, 3, 3)), Rt_inv);  // 仅取旋转矩阵部分求逆

    // 构建图像坐标的齐次坐标
    cv::Mat P_img_homo = (cv::Mat_<double>(3, 1) << P_img.x * Z, P_img.y * Z, Z);

    // 计算相机坐标系下的坐标
    cv::Mat P_cam = Rt_inv * (K_inv * P_img_homo - Rt(cv::Rect(3, 0, 1, 3)));
    
    return P_cam;
}

int main() {
    cv::Mat K = (cv::Mat_<double>(3, 3) << 700, 0, 300, 0, 700, 200, 0, 0, 1);
    cv::Mat R = (cv::Mat_<double>(3, 3) << 0.866, -0.5, 0, 0.5, 0.866, 0, 0, 0, 1);
    cv::Mat t = (cv::Mat_<double>(3, 1) << 0, 0, 5);
    cv::Point2f P_img(317.08, 263.75);
    double Z = 10.0;

    cv::Mat P_cam = pointImgToCam(K, R, t, P_img, Z);
    std::cout << "转换后的相机坐标为: (" << P_cam.at<double>(0, 0) << ", " << P_cam.at<double>(1, 0) << ", " << P_cam.at<double>(2, 0) << ")" << std::endl;

    return 0;
}
