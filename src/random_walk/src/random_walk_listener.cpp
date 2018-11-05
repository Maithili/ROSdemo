// %Tag(FULLTEXT)%
#include <random_walk.h>
void ObstacleCallback(const sensor_msgs::LaserScan::ConstPtr& scan);

void ObstacleCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
    {
      ros::NodeHandle n;
      float thresh = 1.5;
      for (int i=0; i<330; i++)
      {
        if((scan->ranges[i])<thresh)
        {
          ROS_INFO("Too close to obstacle!!!");
          n.setParam("danger",true);
          return;
        }
      }
      ROS_INFO("Safe");
      n.setParam("danger",false);
    }

int main(int argc, char **argv)
{
  ros::init(argc, argv, "random_walk_listener");
  ros::NodeHandle n;
  bool d;
  n.param("danger",d,false);
  ros::Subscriber sub = n.subscribe("/base_scan", 1, ObstacleCallback);
  ros::spin();
  return 0;
}