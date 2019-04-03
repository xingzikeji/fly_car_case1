#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>  //cmd_vel的消息类型

ros::Subscriber iwaypoint_sub;
ros::Publisher iwaypointPublisher;
double x,y,z;
int n=0;



void iwaypoint_path_Callback(const nav_msgs::Odometry::ConstPtr &msg)
{   
    nav_msgs::Odometry bebop_state;
    bebop_state = *msg;
    x=bebop_state.pose.pose.position.x;
    y=bebop_state.pose.pose.position.y;
    z=bebop_state.pose.pose.position.z;
    geometry_msgs::Twist cmd_vel;
    ros::NodeHandle nh2;

iwaypointPublisher = nh2.advertise<geometry_msgs::Twist>("cmd_vel", 10);

  if(z<3)
  {
    cmd_vel.linear.x=0;
    cmd_vel.linear.y=0;
    cmd_vel.linear.z=1;
  iwaypointPublisher.publish(cmd_vel);
  }

  if(z>=10 && n==0)
  { 
      cmd_vel.linear.x=1;
      cmd_vel.linear.y=1;
      cmd_vel.linear.z=0;
      iwaypointPublisher.publish(cmd_vel);
    n=1;
  }

//if(z>=8 && n==1)
//{ 
//    cmd_vel.linear.x=-1;
//    cmd_vel.linear.y=1;
//    cmd_vel.linear.z=0;
//  iwaypointPublisher.publish(cmd_vel);
//  n=2;
//}
   
}




int main(int argc, char **argv)
{
ros::init(argc, argv, "irosplane_path_manager");
ros::NodeHandle nh_;
iwaypoint_sub = nh_.subscribe("ground_truth/state",10, iwaypoint_path_Callback);
ros::spin();
return 0;
}              
