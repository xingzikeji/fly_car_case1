#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include<cv_bridge/cv_bridge.h>
#include<image_transport/image_transport.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "video_pub");
  ros::NodeHandle nh;
  sensor_msgs::ImagePtr msg;
  cv::Mat frame;
  cv::VideoCapture cap(0);
//  cap.set(CV_CAP_PROP_FRAME_WIDTH,1600); // 1600x1200,960x720,640x480,320x240
//  cap.set(CV_CAP_PROP_FRAME_HEIGHT,1200);
  ROS_INFO("Hello world!");


  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub=it.advertise("video",1);
  if(!cap.isOpened())
  {
    std::cout<<" can not open video devide \n"<<std::endl;
    return -1;
  }
  ros::Rate loop_rate(10);
  while (nh.ok()) {
    cap>>frame;
    if(!frame.empty()){
      //实现图片消息的转化
      msg=cv_bridge::CvImage(std_msgs::Header(),"bgr8",frame).toImageMsg();
      
      pub.publish(msg);
    }
    ros::spinOnce();
    loop_rate.sleep();

  }
}
