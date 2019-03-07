#include "ros/ros.h"
#include "std_msgs/String.h"
#include "beginner_tutorials/Num.h"


void chatterCallback(const beginner_tutorials::Num::ConstPtr& msg)
{
  std::cout<<"Loop COunter : "<< msg->num  << " First Name :" << msg->first_name << " Last Name :" << msg->last_name   <<std::endl;
}




int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  std::cout<<"Hello FRom CLent";

  ros::spin();


  return 0;
}
