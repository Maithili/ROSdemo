#ifndef RANDOM_WALK_H
#define RANDOM_WALK_H
#include <ros/ros.h>

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <algorithm>
#include <ros/callback_queue.h>
// namespace random_walk
// {
class RandomWalk
{
	public:
		bool danger_;
		ros::NodeHandle n;
		void ObstacleCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
		{
			float thresh = 0.5;
  			for (int i=0; i<sizeof(scan->ranges); i++)
  			{
  			if((scan->ranges[i])<thresh)
			  {
			    ROS_INFO("Too close to obstacle!!!");
			    this->danger_ =  true;
			    break;
			  }
			  ROS_INFO("Safe");
			  this->danger_ = false; 
			}
		};
		RandomWalk(ros::NodeHandle n){};
		~RandomWalk(){};
};
// }

#endif
