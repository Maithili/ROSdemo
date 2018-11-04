#ifndef RANDOM_WALK_H
#define RANDOM_WALK_H
#include <ros/ros.h>

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <algorithm>

// namespace random_walk
// {
class RandomWalk
{
	public:
		bool danger_;
		ros::NodeHandle n;
		void ObstacleCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
		{
			float thresh = 0.1;
  			for (int i=0; i<sizeof(scan->ranges); i++)
  			{
  			if((scan->ranges[i])<thresh)
			  {
			    ROS_INFO("Too close to obstacle!!!");
			    danger_ =  true;
			    break;
			  }
			  danger_ = false; 
			}
		};
		RandomWalk(ros::NodeHandle n){};
		~RandomWalk(){};
};
// }

#endif
