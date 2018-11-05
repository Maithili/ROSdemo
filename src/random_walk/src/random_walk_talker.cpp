// %Tag(FULLTEXT)%
#include <random_walk.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "random_walk_talker");
  ros::NodeHandle nh;
  geometry_msgs::Twist velocity;

  bool d;

  ros::Publisher walk = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 100);

  float omega = 0.3;
  float speed = 1.0;

  ros::Rate loop_rate(10); 

  while (ros::ok())
  {
    nh.getParam("danger",d);
    if (d)
    {
      ROS_INFO("Turning!!!");
      velocity.angular.z = omega;
      velocity.linear.x = 0.0;
      walk.publish(velocity);
      ros::Rate delayrate(rand()*0.1+50); 
      delayrate.sleep();
      // velocity.angular.z = 0.0;
      // walk.publish(velocity);
    }
    else
    {
      ROS_INFO("Moving!!!");
      velocity.linear.x = speed;
      velocity.angular.z = 0.0;
      walk.publish(velocity);
    }
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}