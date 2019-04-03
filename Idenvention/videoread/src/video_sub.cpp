#include "videoread/video_sub.h"
#include <videoread/xypixel.h>


cv::VideoWriter writer,writer1;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "video_sub");
  ros::NodeHandle nh, nh1;

  //  writer.open("/home/fanduoduo/桌面/ky work/observe/OriginalVideo_100.avi",CV_FOURCC('M', 'J', 'P', 'G'), 5, cv::Size(1920,1080),true);
  //  writer1.open("/home/fanduoduo/桌面/ky work/observe/dectetedVideo_100.avi",CV_FOURCC('M', 'J', 'P', 'G'), 5, cv::Size(1920,1080),true);
  image_transport::ImageTransport it(nh);

  //订阅了图像的数据
  image_transport::Subscriber sub=it.subscribe("/bebop_1/front_cam/camera/image",1,callbacklater);
 
  xypixelPublisher = nh.advertise<videoread::xypixel>("/xypixel",10);
  
  visible_image_publisher=nh1.advertise<sensor_msgs::CompressedImage>("/image_result_compressed",20);
  //image_transport::Subscriber sub=it.subscribe("video",1,callbacklater);
  // image_result_compressed 是图片的结果压缩

  ros::spin();

  //  writer.release();
  //  writer1.release();

  return 0;
}



//订阅相机图像消息
void callbacklater(const sensor_msgs::ImageConstPtr& msg)
{
  //  try {
  frame=cv_bridge::toCvShare(msg,"bgr8")->image;
  // 实现图像的展示，弹出来一个窗口
  cv::imshow("original image",frame);
  detect_HSV(frame);
  cv::waitKey(30);
}
void detect_HSV(cv::Mat &fra)
{
  fra.copyTo(bw);

  int iLowH = 0;
  int iHighH =180;

  int iLowS = 200 ;
  int iHighS = 255;

  int iLowV =000;
  int iHighV =255;

  cv::Mat imgHSV;
  std::vector<cv::Mat> HSVchannel;

  cv::Mat imgThresholded;
  std::vector<std::vector<cv::Point> >contours;

  //目标检测
  cv::cvtColor(bw, imgHSV, cv::COLOR_BGR2HSV);//转为HSV
  // cv::split(imgHSV,HSVchannel);
  // cv::equalizeHist(HSVchannel[1],HSVchannel[1]);
  cv::inRange(imgHSV, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
 
  cv::Mat element=cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3));
  cv::Mat element1=cv::getStructuringElement(cv::MORPH_RECT,cv::Size(2,2));
  
  // cv::morphologyEx是形态学转化函数
  cv::morphologyEx(imgThresholded,imgThresholded,cv::MORPH_DILATE,element);
  cv::morphologyEx(imgThresholded,imgThresholded,cv::MORPH_ELLIPSE,element1);
  // cv::findContours 图像轮廓查找与绘制
  cv::findContours( imgThresholded, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

  std::sort(contours.begin(),contours.end(), biggerSort);

  if (contours.size()>0)
  {  
    //cv::boundingRect矩形边框（Bounding Rectangle）是说，用一个最小的矩形，把找到的形状包起来。还有一个带旋转的矩形，面积会更小， 
    rt=cv::boundingRect(cv::Mat(contours[0]));
    cv::rectangle(bw, rt, cv::Scalar(0,255,0,0), 2);

    //目标质心计算
    std::vector<cv::Moments> mu(contours.size());

    for(int i=0; i<contours.size();i++)
    {
      mu[i]=cv::moments(contours[i],false);
    }
    std::vector<cv::Point2f> mc(contours.size());
    for (int i=0; i<1;i++)
    {
      mc[i]=cv::Point2f(mu[i].m10/mu[i].m00,mu[i].m01/mu[i].m00);
      cv::circle(bw, mc[i], 4, cv::Scalar(0, 255, 0),-1);
    }
    cv::imshow("detected image",bw);

    float centx = bw.cols / 2;
    float centy = bw.rows / 2;
    videoread::xypixel xymsg;

    xymsg.x1 = -(mc[0].x - centx) / centx;
    xymsg.y1 = -(mc[0].y - centy) / centy;
    std::cout<< xymsg.x1<<std::endl;
    xypixelPublisher.publish(xymsg);

    // Draw frame by frame, written by Zunlin Fan
    cv_bridge::CvImage cvi;
    cvi.header.frame_id = "image";
    cvi.encoding = "bgr8";
    bw.copyTo(cvi.image);
    cvi.toCompressedImageMsg(compress_image_msg);
    cv::imencode(".jpg", bw, compress_image_msg.data);
    if (!bw.empty())
    {
      visible_image_publisher.publish(compress_image_msg);
    }

  }
}


//选取面积最大的轮廓
bool biggerSort(std::vector<cv::Point> v1, std::vector<cv::Point> v2)
{
  return cv::contourArea(v1)>cv::contourArea(v2);
}


