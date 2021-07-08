#include "ros/ros.h"
#include "tf/transform_listener.h"
#include "tf/message_filter.h"
#include "message_filters/subscriber.h"
#include "sensor_msgs/LaserScan.h"

class tinySlam
{
public:
  tinySlam() : tf_()
  {
    scan_filter_sub_ = new message_filters::Subscriber<sensor_msgs::LaserScan>(node_, "scan", 5);
    scan_filter_ = new tf::MessageFilter<sensor_msgs::LaserScan>(*scan_filter_sub_, tf_, "odom", 5);
    scan_filter_->registerCallback(boost::bind(&tinySlam::msgCallback, this, _1));
    ROS_INFO("HVU registerCallback");
  } ;

private:
  ros::NodeHandle node_;
  tf::TransformListener tf_;
  message_filters::Subscriber<sensor_msgs::LaserScan>* scan_filter_sub_;
  tf::MessageFilter<sensor_msgs::LaserScan>* scan_filter_;

  //  Callback to register with tf::MessageFilter to be called when transforms are available
  void msgCallback(const sensor_msgs::LaserScan::ConstPtr& scan) 
  {
    ROS_INFO("HVU callback");
  };

};


int main(int argc, char ** argv)
{
  ros::init(argc, argv, "tinySlam"); //Init ROS
  tinySlam tS; //Construct class
  ros::spin(); // Run until interupted 
};
