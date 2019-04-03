#ifndef VIDEO_SUB_H
#define VIDEO_SUB_H

#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <std_msgs/String.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_datatypes.h>


//像素坐标转机体坐标
void callbacklater(const sensor_msgs::ImageConstPtr& msg);
void detect_HSV(cv::Mat &fra);
bool biggerSort(std::vector<cv::Point> v1, std::vector<cv::Point> v2);
cv::Mat frame;                        //当前帧
cv::Mat bw;                          //二值图像
cv::Rect rt;                          //目标外接框、生成结构元素（用于连接断开的小目标）
ros::Publisher xypixelPublisher;
ros::Publisher visible_image_publisher;
sensor_msgs::CompressedImage compress_image_msg;


#endif // VIDEO_SUB_H
