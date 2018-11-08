#include "husky_highlevel_controller/husky_highlevel_controller.h"


namespace husky_highlevel_controller
{
    HuskyHighLevelController::HuskyHighLevelController(ros::NodeHandle *nodeHandle) : nh_(*nodeHandle)
    {

        //check if the parameters exist, and if not exist send a error message and shutdown
        if (!(nh_.getParam("scan_topic_name", topic_name_) && nh_.getParam("scan_topic_queue_size", topic_size_queue_)))
        {
            ROS_ERROR("Could NOT read the parameters.");
            //ros::requestShutdown();
        }

        // create the subscriber to the topic name
        sub = nh_.subscribe(topic_name_, topic_size_queue_, &HuskyHighLevelController::scanMessageReceived, this);

        ROS_INFO("Successfully launched the node.");

    }
    HuskyHighLevelController::~HuskyHighLevelController(){}

    void HuskyHighLevelController::scanMessageReceived(const sensor_msgs::LaserScan &msg)
    {
        if (msg.ranges.size() > 0)
        {
            float smallest_value = msg.ranges[0];
            for (int i = 1; i < msg.ranges.size(); i++)
            {
                if (smallest_value > msg.ranges[i])
                {
                    smallest_value = msg.ranges[i];
                }
                
            }
            // display the ming value
            ROS_INFO_STREAM(std::setprecision(2) << std::fixed << "Min range: " << smallest_value);
        }

    }
    



    
} /* namespace */