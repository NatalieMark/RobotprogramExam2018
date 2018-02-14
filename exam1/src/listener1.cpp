#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "std_msgs/String.h"
#include <iostream>
#include <sstream>

using namespace std;

ros::Publisher pub;	//declaring a publisher
ros::Publisher pub1;	//declaring a publisher
ros::Subscriber pose_subscriber;  //declaring a Subscriber
ros::Subscriber UI_sub;//declaring a Subscriber

const double PI = 3.14159265359; // sets a constant for PI

int xr;	// x coordinate of the turtle in turtlesim
int yr;	// y coordinate of the turtle in turtlesim
int dr;	// looking direction of the turtle in turtlesim
string answer;

void randomwalk();//prototyping the function
void circle();//prototyping the function
void square();//prototyping the function

// publishes on the topic "Done" and uses the std_msgs::String msg
void needNew(){
	std_msgs::String msg;
	stringstream ss;
	ss << "I'am ready for your command";
	msg.data = ss.str();
	pub1.publish(msg);
	ros::spinOnce();
}

// publishes on the topic "Done" and uses the std_msgs::String msg
void moving(){
	std_msgs::String msg;
	stringstream ss;
	ss << "I'am moving";
	msg.data = ss.str();
	pub1.publish(msg);
	ros::spinOnce();
}

//subscribes to the topic "/turtle1/pose" and updates xr,yr,dr
//every time a new msg is published
void poseCallback(const turtlesim::Pose::ConstPtr& msg){
	xr = msg->x;
	yr = msg->y;
	dr = ((msg->theta * 180)/PI) * 100;
  	ROS_INFO("x: [%i], y: [%i] looking: [%i]", xr, yr, dr);
}

//subscribes to the topic "Done" and updates xr,yr,dr
//every time a new msg is published
void chatterCallback(const std_msgs::String::ConstPtr& data){
	answer = data->data;
  //ROS_INFO("I heard:[%s]", answer);
}

int main(int argc, char** argv){

	ros::init(argc, argv, "Mover");

	ros::NodeHandle n;

	UI_sub = n.subscribe("Commands", 1000, chatterCallback); // (subscribing to, queue space, "update from publisher" - everytime something is published to the topics commands it will be written to the chatterCallback function)
  	pose_subscriber = n.subscribe("/turtle1/pose", 100, poseCallback);
  	pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1); // advertizing <What is pubished to>(the topic, queue size)
  	pub1 = n.advertise<std_msgs::String>("Done", 1); // advertizing <What is pubished to>(the topic, queue size)

	ros::Rate rate(10); // the Rate instance will attempt to keep the loop at 10hz by accounting for the time used by the work done during the loop.

	while(ros::ok()){
		moving();
		if(answer == "1") {
			moving();
			circle();
			ros::spinOnce();
			answer = "hej";
		}
		else if(answer == "2"){
			moving();
		  	square();
			ros::spinOnce();
			answer = "hej";
		}
		else if(answer == "3"){
			moving();
			randomwalk();
			ros::spinOnce();
			answer = "hej";
		}
		else
			needNew();
			
		ros::spinOnce();
	}
	rate.sleep();
	return 0;
};

void circle(){
	ros::Rate rate(1);
 	while (dr < 35900)
	{
		ros::Rate rate(1);
			geometry_msgs::Twist msg;
			msg.linear.x = 1;
			msg.angular.z = 1;
			pub.publish(msg);
			ros::spinOnce();
	}
	rate.sleep();
};

void square(){
	ros::Rate rate(1);
	while(xr != 10) {
		geometry_msgs::Twist msg;
		msg.linear.x = 1;
		pub.publish(msg);
		ros::spinOnce();
	}
	while(dr <= 9000)  {
		geometry_msgs::Twist msg;
		msg.angular.z = 0.3;
		pub.publish(msg);
		ros::spinOnce();
	}
	while(yr != 10) {
		geometry_msgs::Twist msg;
		msg.linear.x = 1;
		pub.publish(msg);
		ros::spinOnce();
	}
	while(dr <= 18000)  {
		geometry_msgs::Twist msg;
		msg.angular.z = 0.3;
		pub.publish(msg);
		ros::spinOnce();
	}
	while(xr != 2) {
		geometry_msgs::Twist msg;
		msg.linear.x = 1;
		pub.publish(msg);
		ros::spinOnce();
	}
	while(dr <= 27000)  {
		geometry_msgs::Twist msg;
		msg.angular.z = 0.3;
		pub.publish(msg);
		ros::spinOnce();
	}
	while(yr != 2) {
		geometry_msgs::Twist msg;
		msg.linear.x = 1;
		pub.publish(msg);
		ros::spinOnce();
	}
	while(dr <= 35979)  {
		geometry_msgs::Twist msg;
		msg.angular.z = 0.2;
		pub.publish(msg);
		ros::spinOnce();
	}
	while(xr != 10) {
		geometry_msgs::Twist msg;
		msg.linear.x = 1;
		pub.publish(msg);
		ros::spinOnce();
	}
	while(dr < 8990 || dr > 9020)  {
		geometry_msgs::Twist msg;
		msg.angular.z = 0.3;
		pub.publish(msg);
		ros::spinOnce();
	}
	while(yr <= 5)  {
		geometry_msgs::Twist msg;
		msg.linear.x = 1;
		pub.publish(msg);
		ros::spinOnce();
	}
	rate.sleep();
};

void randomwalk(){
	ros::Rate rate(1);
	int count = 0;
	srand(time(NULL));
	while(count < 20){
		geometry_msgs::Twist msg;
		msg.linear.x = (double)(rand() % 10 + 1)/4.0;
		msg.angular.z = (double)(rand() % 10 - 5)/2.0;
		pub.publish(msg);
		ros::spinOnce();
		count++;
	}
	rate.sleep();
};
