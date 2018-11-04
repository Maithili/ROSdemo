// %Tag(FULLTEXT)%
#include <random_walk.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "random_walk");
  ros::NodeHandle n;
  geometry_msgs::Twist velocity;

  RandomWalk *random_walk_object = new RandomWalk(n);
  random_walk_object->danger_ = false;

  ros::Subscriber sub = n.subscribe("/base_scan", 1000, &RandomWalk::ObstacleCallback, random_walk_object);
  ros::Publisher walk = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  
  float omega = 0.1;
  float speed = 1.0;
  if (random_walk_object->danger_)
  {
    ROS_INFO("Turning!!!");
    velocity.angular.z = omega;
    velocity.linear.x = 0.0;
    walk.publish(velocity);
    sleep(rand()*0.03);
    velocity.angular.z = 0.0;
    walk.publish(velocity);
  }
  else
  {
    ROS_INFO("Moving!!!");
    velocity.linear.x = speed;
    walk.publish(velocity);
  }
  ros::spin();
  return 0;
}