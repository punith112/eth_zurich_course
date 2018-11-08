#include "husky_highlevel_controller/husky_highlevel_controller.h"


namespace husky_highlevel_controller
{
    HuskyHighLevelController::HuskyHighLevelController(ros::NodeHandle &nodeHandle)
        : nodeHandle_(nodeHandle)
    {
        //topic_name_  = "scan";
        //topic_size_queue_ = 100;
        //check if the parameters exist, and if not exist send a error message and shutdown
        //if (!(nodeHandle.getParam("scan_topic_name", topic_name_) && nodeHandle.getParam("scan_topic_queue_size", topic_size_queue_)))
        //{
            //ROS_ERROR("Could NOT read the parameters.");
            //ros::requestShutdown();
        //}

        // create the subscriber to the topic name
        //sub = nodeHandle_.subscribe(topic_name_, topic_size_queue_, &HuskyHighLevelController::scanMessageReceived, this);
        sub = nodeHandle_.subscribe("scan", 1000, &HuskyHighLevelController::scanMessageReceived, this);

        ROS_INFO("Successfully launched the node.");

    }
    HuskyHighLevelController::~HuskyHighLevelController(){}

    void HuskyHighLevelController::scanMessageReceived(const sensor_msgs::LaserScan &msg)
    {
        if (msg.ranges.size() > 0)
        {
            ROS_INFO_STREAM(msg.ranges[1]);
        }
        
        /*std::vector<float> data = msg.ranges;
        float smallest_value = data[0];
        for (int i = 1; i < data.size(); i++)
        {
            if (smallest_value > data[i])
            {
                smallest_value = data[i];
            }
                
        }
        */

        // display the ming value
        //ROS_INFO_STREAM(std::setprecision(2) << std::fixed << "Min range: " << smallest_value);
    }
    



    
} /* namespace */