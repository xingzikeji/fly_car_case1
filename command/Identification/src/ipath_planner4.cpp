#include <ros/ros.h>
#include <commond_msgs/Waypoint.h>
#include <commond_msgs/IWaypoint.h> 
#include <observe_msgs/xypixel.h>
#include <observe_msgs/xypixelStamped.h>
#include <geometry_msgs/PointStamped.h>
#include <nav_msgs/Odometry.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <boost/bind.hpp>
ros::Publisher iwaypointPublisher1;
ros::Publisher iwaypointPublisher2;
//ros::NodeHandle nh_;

void state_callback(const nav_msgs::Odometry::ConstPtr &msg1, const observe_msgs::xypixelStamped::ConstPtr &msg2)
{
  ros::NodeHandle nh;
//nav_msgs::Odometry bebop_state;
//observe_msgs::xypixelStamped bel;
//float a, b,c;
//bebop_state = *msg1;
//bel=*msg2;
//a = bebop_state.pose.pose.position.x;
//b = bebop_state.pose.pose.position.y;
//c=bel.xypixel.w[0];
//if(c!=0 && a>10 && a<20 && b>-5 && b<5 )
//{
  iwaypointPublisher1 = nh.advertise<commond_msgs::Waypoint>("/bebop_2/waypoint_path", 10);
  iwaypointPublisher2 = nh.advertise<commond_msgs::Waypoint>("/bebop_3/waypoint_path", 10);
  commond_msgs::Waypoint inew_waypoint;
  inew_waypoint.w[0]=15.0;
  inew_waypoint.w[1]=0.0;
  inew_waypoint.w[2]=-3.0;
  inew_waypoint.lat = 0;
  inew_waypoint.lon = 0;
  inew_waypoint.chi_d = 0;
  inew_waypoint.chi_valid = false;
  inew_waypoint.Va_d = 3;
  inew_waypoint.set_current =true;
  inew_waypoint.landing =false;
  inew_waypoint.takeoff =false;
  inew_waypoint.clear_wp_list = false;
  iwaypointPublisher1.publish(inew_waypoint);
//}

//if(c!=0 && a>25 && a<35 && b>-5 && b<5)
//{ 
//   inew_waypoint.w[0]=30.0;
//   inew_waypoint.w[1]=0.0;
//   inew_waypoint.w[2]=-3.0;
//   inew_waypoint.lat = 0;
//   inew_waypoint.lon = 0;
//   inew_waypoint.chi_d = 0;
//   inew_waypoint.chi_valid = false;
//   inew_waypoint.Va_d = 3;
//   inew_waypoint.set_current =true;
//   inew_waypoint.landing =false;
//   inew_waypoint.takeoff =false;
 //  inew_waypoint.clear_wp_list = false;
//  iwaypointPublisher2.publish(inew_waypoint);
//}
}



int main(int argc, char **argv)
{
ros::init(argc, argv, "irosplane_path_manager");
ros::NodeHandle nh_;
message_filters::Subscriber<nav_msgs::Odometry> bebop1_sub(nh_, "/bebop_1/ground_truth/state", 1);       // topic1 输入
message_filters::Subscriber< observe_msgs::xypixelStamped> bebop2_sub(nh_, "/xypixel", 1);       // topic2 输
message_filters::TimeSynchronizer<nav_msgs::Odometry,  observe_msgs::xypixelStamped> sync(bebop1_sub, bebop2_sub, 10); // 同步
sync.registerCallback(boost::bind(&state_callback, _1, _2));
ros::spin();
return 0;

}
