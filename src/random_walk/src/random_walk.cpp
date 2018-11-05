// %Tag(FULLTEXT)%
#include <random_walk.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "random_walk");
  ros::NodeHandle n;
  geometry_msgs::Twist velocity;

  RandomWalk *random_walk_object = new RandomWalk(n);
  random_walk_object->danger_ = true;
  ros::Subscriber sub = n.subscribe("/base_scan", 100, &RandomWalk::ObstacleCallback, random_walk_object);
  ros::Publisher walk = n.advertise<geometry_msgs::Twist>("/cmd_vel", 100);

  float omega = 0.3;
  float speed = 1.0;
  ros::CallbackQueue my_callback_queue;
  n.setCallbackQueue(&my_callback_queue);
  ros::Rate loop_rate(10);   

  while (ros::ok())
  {
    if (random_walk_object->danger_)
    {
      ROS_INFO("Turning!!!");
      velocity.angular.z = omega;
      velocity.linear.x = 0.0;
      walk.publish(velocity);
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
    // ros::spin();
    // my_callback_queue.callOne(ros::WallDuration());
  }

  ros::spin();
  return 0;
}