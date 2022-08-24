#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "ros/ros.h"
#include "nav_msgs/Path.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Point.h"

using namespace std;

struct PointSt{
   int x,y;
};

PointSt point;
std::vector<PointSt> points;
nav_msgs::Odometry actualOdom;
double x_location, y_location, theta_location;

bool state = false;
bool direction = true;

void odometryCallback(const boost::shared_ptr<nav_msgs::Odometry const>& msg){


	actualOdom = *msg;
	x_location = actualOdom.pose.pose.position.x;
	y_location = actualOdom.pose.pose.position.y;

	std::cout << "X: " << x_location << "\t Y: " << y_location << std::endl;

}

nav_msgs::Path my_path_waypoint(){

	nav_msgs::Path msg;
	geometry_msgs::PoseStamped pose;
	std::vector<geometry_msgs::PoseStamped> poses;

	srand (time(NULL));

	if(!state){
		point.x = 0;
		point.y = 0;
		points.push_back(point);

		for(int i=1; i<10; i++){
	   		point.x = ((rand() % 10 + 3)*2);
			point.y = i*5;
			if(points[i-1].x == point.x && points[i-1].y == point.y){
				i--;
				continue;
			}
			points.push_back(point);
		}

		state = true;
	}

	for (int i = 0; i <10 ; ++i)
	{
		pose.pose.position.x = points[i].x;
		pose.pose.position.y = points[i].y;
		poses.push_back(pose);
	}
	
	msg.poses = poses;
	return msg;
}

int main(int argc, char **argv){

	ros::init(argc, argv, "randomWaypoinstPub");
	ros::NodeHandle n;

	ros::Publisher path_pub = n.advertise<nav_msgs::Path>("/waypoints_input",1000);
	ros::Subscriber odom_sub = n.subscribe("/absolute_pose", 1000, odometryCallback); 
	ros::Rate loop_rate(20);

	
	nav_msgs::Path path;
	
	
while(ros::ok()){
	path.poses.clear();
	path = my_path_waypoint();

	path_pub.publish(path);
	ros::spinOnce();
	loop_rate.sleep();
}
	return 0;

}

