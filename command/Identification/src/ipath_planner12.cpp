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
ros::Publisher iwaypointPublisher2;
ros::Publisher iwaypointPublisher3;
ros::Publisher iwaypointPublisher4;

double ux[TARGAT_NUM];
double uy[TARGAT_NUM];
double tx[TARGAT_NUM];
double ty[TARGAT_NUM];
double tz[TARGAT_NUM];
int task_result[TARGAT_NUM];
int c = 0;
int r1,r2,r3;

bool is_not_add(double x, double y)
{
	int i;
	//no point is added
	if(c == 0) return true;
	for(i = 0; i < c; i++)
	{
		if((fabs(tx[i] - x) + fabs(ty[i] - y)) < 16) return false;
	}
	return true;
}

int get_3min(double x,double y,double z)
{
	double min = x;
	int index = 0;
	if(y<min) {min = y; index = 1;}
	if(z<min) {min = z; index = 2;}
	return index;
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
	double dist[3][3];
	int i, j;
	if(c==1)
    {for(i=0;i<3;i++)
    dist[i][0] = sqrt(pow(ux[i]-tx[0],2) + pow(uy[i]-ty[0],2));
    r1 = get_3min(dist[0][0],dist[1][0],dist[2][0]);
    task_result[0] = r1;
    }

    if(c==2)
      {for(i=0;i<3;i++)
    dist[i][1]= sqrt(pow(ux[i]-tx[1],2) + pow(uy[i]-ty[1],2));
    dist[r1][1]=99999;
    r2 = get_3min(dist[0][1],dist[1][1],dist[2][1]);
    task_result[1] = r2;
     }

    if(c==3)
    {for(i=0;i<3;i++)
    dist[i][2]= sqrt(pow(ux[i]-tx[2],2) + pow(uy[i]-ty[2],2));
    dist[r1][2]=99999;
    dist[r2][2]=99999;
    r3 = get_3min(dist[0][2],dist[1][2],dist[2][2]);
    task_result[2] = r3;
     }

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
    if(is_not_add(n_x, n_y))
    {
    	tx[c] = n_x;
    	ty[c] = n_y;
    	tz[c] = n_z;
    	c++;
    	printf("The index %d target.\n", c-1);
    }
    //Targets have been collected and task assignment is not executed never
        
   
 		//task_assignment();
 		
       //  if(c==1)
            task_assignment();
 			inew_waypoint.w[0]=tx[c-1];
   			inew_waypoint.w[1]=ty[c-1];
   			inew_waypoint.w[2]=tz[c-1];
   			inew_waypoint.lat = 0;
   			inew_waypoint.lon = 0;
   			inew_waypoint.chi_d = 0;
   			inew_waypoint.chi_valid = false;
   			inew_waypoint.Va_d = 3;
   			inew_waypoint.set_current =true;
   			inew_waypoint.landing =false;
   			inew_waypoint.takeoff =false;
   			inew_waypoint.clear_wp_list = false;
      if(task_result[c-1]==0)
      iwaypointPublisher2.publish(inew_waypoint);
      if(task_result[c-1]==1)
        iwaypointPublisher3.publish(inew_waypoint);
       if(task_result[c-1]==2)
         iwaypointPublisher4.publish(inew_waypoint);

   		//	switch(task_result[c-1]){
   		//		case 0:
   		//			iwaypointPublisher2.publish(inew_waypoint); break;
   		//		case 1:
   		//			iwaypointPublisher3.publish(inew_waypoint); break;
   		//		case 2:
   		//			iwaypointPublisher4.publish(inew_waypoint);  break;
   			
          //     } 
 		
    

} 


int main(int argc, char **argv)
{
	ros::init(argc, argv, "irosplane_path_manager");
	ros::NodeHandle nh_;
	iwaypoint_sub2 = nh_.subscribe("/bebop_2/ground_truth/state",10, iwaypoint_path_Callback2);
	iwaypoint_sub3 = nh_.subscribe("/bebop_3/ground_truth/state",10, iwaypoint_path_Callback3);
	iwaypoint_sub4 = nh_.subscribe("/bebop_4/ground_truth/state",10, iwaypoint_path_Callback4);
	iwaypoint_sub1 = nh_.subscribe("/bebop_1/objection_xyz",10, iwaypoint_path_Callback);
	ros::spin();
	return 0;
}
