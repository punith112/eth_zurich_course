#include <ros/ros.h>
#include "husky_highlevel_controller/husky_highlevel_controller.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "husky_highlevel_controller");

    
    // create a private namespace nodeHandle
    ros::NodeHandle nh("~"); // ("~") is because we are accessing Private Parameters. nh's namespace is /my_node_name = husky_highlevel_controller

    husky_highlevel_controller::HuskyHighLevelController huskyHighlevelController(&nh);


    //huskyHighlevelController.hit_the_pillar();

   	ros::spin();

    return 0;
}