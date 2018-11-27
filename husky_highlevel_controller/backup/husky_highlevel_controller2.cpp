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

        pillar_found = false;
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
        double front_angle1_value;
        double front_angle2_value;
        double front_angle3_value;

        double left_angle;
        double center_angle;
        double right_angle;


        if (msg.ranges.size() > 0)
        {
            //ROS_INFO_STREAM(" LaserScan Message Size: " << msg.ranges.size()); 
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

                    front_angle1_value = msg.ranges[355];
                    front_angle2_value = msg.ranges[356];
                    front_angle3_value  = msg.ranges[357];



                        //ROS_INFO_STREAM(" PILLAR FOUND"); 
                    //if (front_angle1_value < 3 && front_angle2_value < 3 && front_angle3_value < 3)
                    //{
                        pillar_found = true;
                        //ROS_INFO_STREAM(" PILLAR FOUND"); 
                        //ROS_INFO_STREAM(front_angle3_value); 

                   // }
                }
                
            }
            left_angle = (345*angle_increment + angle_minimum)*180/3.14159265359;
            center_angle = (360*angle_increment + angle_minimum)*180/3.14159265359;
            right_angle = (375*angle_increment + angle_minimum)*180/3.14159265359;

            angle_minimum = angle_minimum*180/3.14159265359;
            ROS_INFO_STREAM("Left angle: " << left_angle);
            ROS_INFO_STREAM("Center angle: " << center_angle);
            ROS_INFO_STREAM("Right angle: " << right_angle);

            //ROS_INFO_STREAM("Angle minimum: " << angle_minimum);
            std::cout << "" << std::endl;

            //center_angle = smallest_value_index*angle_increment*180/3.14159265359;
            //ROS_INFO_STREAM("Center angle by index: " << center_angle);

            //ROS_INFO_STREAM(" Smallest valur INDEX: " << smallest_value_index);



            // display the ming value
            //ROS_INFO_STREAM(std::setprecision(2) << std::fixed << "Min range: " << smallest_value);
        }

    }

    void HuskyHighLevelController::hit_the_pillar()
    {    
        
        ros::Rate rate(10);
        geometry_msgs::Twist vel_msg;

        ros::Duration delta_t;
        double delta_t_sec;
 
        bool is_init = false;
        while(nh_.ok())
        {
            rate.sleep(); // wait the correct time from the master be published

            if (is_init == false)
            {
                start_time = ros::Time::now();
                is_init = true;
            }



            if (pillar_found == false)
            {
                delta_t = ros::Time::now() - start_time;
                delta_t_sec = delta_t.toSec();

                // Husky search for the pillar
                if (delta_t_sec < 10.0)
                {
                    //vel_msg.angular.z = 0.5;
                    //pub_vel.publish(vel_msg);    
                    //ROS_INFO_STREAM(" Rotate Husky!!!" << " Time delta t sec " << delta_t_sec); 

                }
            }
            else
            {
                //vel_msg.angular.z = 0.0;
                //vel_msg.linear.x = 1.0;
                pub_vel.publish(vel_msg);

                // TODO: Controller
            }


            //rate.sleep();
            ros::spinOnce();

        }        
        vel_msg.angular.z = 0.0;
        pub_vel.publish(vel_msg);
    }
   
} /* namespace */