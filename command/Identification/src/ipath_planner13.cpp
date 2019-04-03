#include<stdio.h>
#include<math.h>
#include <ros/ros.h>
#include <commond_msgs/Waypoint.h>
#include <nav_msgs/Odometry.h>
#define TARGAT_NUM 3

ros::Subscriber iwaypoint_sub1;
ros::Subscriber iwaypoint_sub2;
ros::Subscriber iwaypoint_sub3;
ros::Subscriber iwaypoint_sub4;
ros::Subscriber iwaypoint_sub0;
ros::Publisher iwaypointPublisher2;
ros::Publisher iwaypointPublisher3;
ros::Publisher iwaypointPublisher4;
//Position of three UAVs
//double a2,a3,b2,b3,a4,b4;
double ux[TARGAT_NUM];
double uy[TARGAT_NUM];
double tx[TARGAT_NUM] = {0.0,0.0,0.0};
double ty[TARGAT_NUM] = {0.0,0.0,0.0};
double tz[TARGAT_NUM] = {0.0,0.0,0.0};
double bebop1_hight;
int task_result[TARGAT_NUM];
int loc_c[TARGAT_NUM] = {0,0,0};
//Mark if the target assignment has been executed
int flag = 0;

void add_position(double x, double y, double z)
{
	int i;
	for(i = 0;i < TARGAT_NUM;i++)
	{
		if((loc_c[i] != 0) && ((fabs(tx[i]/loc_c[i] - x) + fabs(ty[i]/loc_c[i] - y)) < 2))
		{
			tx[i] = tx[i] + x;
			ty[i] = ty[i] + y;
			tz[i] = z;
			loc_c[i]++;
			break;
		}
		if(loc_c[i] == 0)
		{
			tx[i] = x;
			ty[i] = y;
			tz[i] = z;
			loc_c[i]++;
			break;
		}
	}
}
int get_3min(double x,double y,double z)
{
	double min = x;
	int index = 0;
	if(y<min) {min = y; index = 1;}
	if(z<min) {min = z; index = 2;}
	return index;
}
void iwaypoint_path_Callback0(const nav_msgs::Odometry::ConstPtr &msg0)
{   
	nav_msgs::Odometry bebop_state;
    bebop_state = *msg0;
  //  bebop1_hight = bebop_state.pose.pose.position.z;
 //   if(bebop1_hight>13 && flag == 0){
  //  	flag = 1;
  //  }
}
void iwaypoint_path_Callback2(const nav_msgs::Odometry::ConstPtr &msg2)
{   
	nav_msgs::Odometry bebop_state;
    bebop_state = *msg2;
    ux[0]=bebop_state.pose.pose.position.x;
    uy[0]=bebop_state.pose.pose.position.y;
}
void iwaypoint_path_Callback3(const nav_msgs::Odometry::ConstPtr &msg3)
{   
	nav_msgs::Odometry bebop_state;
    bebop_state = *msg3;
    ux[1]=bebop_state.pose.pose.position.x;
    uy[1]=bebop_state.pose.pose.position.y;
}
void iwaypoint_path_Callback4(const nav_msgs::Odometry::ConstPtr &msg4)
{   
	nav_msgs::Odometry bebop_state;
    bebop_state = *msg4;
    ux[2]=bebop_state.pose.pose.position.x;
    uy[2]=bebop_state.pose.pose.position.y;
}

void task_assignment()
{
	double dis[3][3];
	int i, j;
	int r1,r2,r3;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			dis[i][j] = sqrt(pow(ux[i]-(tx[j]/loc_c[i]),2) + pow(uy[i]-(ty[j]/loc_c[i]),2));
	//For UAV1
	r1 = get_3min(dis[0][0],dis[0][1],dis[0][2]);
	task_result[0] = r1;
	//For UAV2
	dis[1][r1] = 9999999;
	r2 = get_3min(dis[1][0],dis[1][1],dis[1][2]);
	task_result[1] = r2;
	//For UAV3
	dis[2][r1] = 9999999;
	dis[2][r2] = 9999999;
	r3 = get_3min(dis[2][0],dis[2][1],dis[2][2]);
	task_result[2] = r3;
}

void iwaypoint_path_Callback(const nav_msgs::Odometry::ConstPtr &msg)
{
	double n_x,n_y,n_z;
	int j;
	ros::NodeHandle nh;
    iwaypointPublisher2 = nh.advertise<commond_msgs::Waypoint>("/bebop_2/waypoint_path", 10);
	iwaypointPublisher3 = nh.advertise<commond_msgs::Waypoint>("/bebop_3/waypoint_path", 10);
	iwaypointPublisher4 = nh.advertise<commond_msgs::Waypoint>("/bebop_4/waypoint_path", 10);
    commond_msgs::Waypoint inew_waypoint;
    nav_msgs::Odometry bebop_state;
    bebop_state = *msg;
    n_x = bebop_state.pose.pose.position.x;
    n_y = bebop_state.pose.pose.position.y;
    n_z = bebop_state.pose.pose.position.z;
    //Add target that has not been added
    add_position(n_x, n_y, n_z);
    //Targets have been collected and task assignment is not executed never
    if(loc_c[0]>0&&loc_c[1]>0&&loc_c[2]>0 &&flag == 0)
    {
 		//task assignment
 		task_assignment();
 		for(j=0;j<3;j++)
 		{
 			inew_waypoint.w[0]=tx[task_result[j]]/loc_c[task_result[j]];
   			inew_waypoint.w[1]=ty[task_result[j]]/loc_c[task_result[j]];
   			inew_waypoint.w[2]=tz[task_result[j]];
   			inew_waypoint.lat = 0;
   			inew_waypoint.lon = 0;
   			inew_waypoint.chi_d = 0;
   			inew_waypoint.chi_valid = false;
   			inew_waypoint.Va_d = 3;
   			inew_waypoint.set_current =true;
   			inew_waypoint.landing =false;
   			inew_waypoint.takeoff =false;
   			inew_waypoint.clear_wp_list = false;
   			switch(j){
   				case 0:
   					iwaypointPublisher2.publish(inew_waypoint);
   				case 1:
   					iwaypointPublisher3.publish(inew_waypoint);
   				case 2:
   					iwaypointPublisher4.publish(inew_waypoint);
   			}
 		}
    }
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "irosplane_path_manager");
	ros::NodeHandle nh_;
	iwaypoint_sub2 = nh_.subscribe("/bebop_2/ground_truth/state",10, iwaypoint_path_Callback2);
	iwaypoint_sub3 = nh_.subscribe("/bebop_3/ground_truth/state",10, iwaypoint_path_Callback3);
	iwaypoint_sub4 = nh_.subscribe("/bebop_4/ground_truth/state",10, iwaypoint_path_Callback4);
	iwaypoint_sub1 = nh_.subscribe("/bebop_1/objection_xyz",10, iwaypoint_path_Callback);
	iwaypoint_sub0 = nh_.subscribe("/bebop_1/ground_truth/state",10, iwaypoint_path_Callback0);
	ros::spin();
	return 0;
}
