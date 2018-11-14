/*
    TODO

    SOLUTION 1: 



    SOLUTION 2

*/



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
        

        // TODO verify write
        //pub_vel = nh_.advertise<geometry_msgs::Twist>("cmd_vel",1000);

        initializeSubscribers(); // package up the messy work of creating subscribers; do this overhead in constructor
        initializePublishers();

        hit_the_pillar();

        ROS_INFO("Successfully launched the node.");

    }

    HuskyHighLevelController::~HuskyHighLevelController(){}

    

    void HuskyHighLevelController::initializeSubscribers()
    {
        ROS_INFO("Initializing Subscribers");
        sub = nh_.subscribe(topic_name_, topic_size_queue_, &HuskyHighLevelController::scanMessageReceived, this);
    }


    void HuskyHighLevelController::initializePublishers()
    {
        ROS_INFO("Initializing Publishers");
        //pub_vel = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1000, true);
        pub_vel = nh_.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 1000, true);

        

    }

    void HuskyHighLevelController::scanMessageReceived(const sensor_msgs::LaserScan &msg)
    {
        if (msg.ranges.size() > 0)
        {
            angle_increment = msg.angle_increment;
            angle_minimum = msg.angle_min;
            smallest_value = msg.ranges[0];
            smallest_value_index = 0;
            for (int i = 1; i < msg.ranges.size(); i++)
            {
                if (smallest_value > msg.ranges[i])
                {
                    smallest_value = msg.ranges[i];
                    smallest_value_index = i;
                }
                
            }
            // display the ming value
            ROS_INFO_STREAM(std::setprecision(2) << std::fixed << "Min range: " << smallest_value);
        }

    }

    void HuskyHighLevelController::hit_the_pillar()
    {    

        ros::Rate rate(5);

        
        while(nh_.ok() && )

        {

        //ROS_INFO("CHECK");
        geometry_msgs::Twist vel_msg;
        vel_msg.linear.x = 5.0;
        pub_vel.publish(vel_msg);

        rate.sleep();
        ros::spinOnce();

        }
    }

    
} /* namespace */