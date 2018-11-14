#include <ros/ros.h>
#include "husky_highlevel_controller/husky_highlevel_controller.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "husky_highlevel_controller");

    
    // create a private namespace nodeHandle
    ros::NodeHandle nh("~"); // ("~") is because we are accessing Private Parameters

    //ros::NodeHandle nh;

    //ros::Rate rate(2);

    husky_highlevel_controller::HuskyHighLevelController huskyHighlevelController(&nh);


    //huskyHighlevelController.hit_the_pillar();

   	ros::spin();
   	//rate.sleep();


    return 0;
}