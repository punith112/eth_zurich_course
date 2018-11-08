#include <ros/ros.h>
#include "husky_highlevel_controller/husky_highlevel_controller.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "husky_highlevel_controller");

    // create a private namespace nodeHandle
    ros::NodeHandle nh("~"); // ("~") is because we are accessing Private Parameters

    husky_highlevel_controller::HuskyHighLevelController huskyHighlevelController(&nh);

    ros::spin();
    return 0;
}