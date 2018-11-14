// include this file in "husky_highlevel_controller.cpp"

// here's a good trick--should always do this with header files:
// create a unique mnemonic for this header file, so it will get included if needed,
// but will not get included multiple times
#ifndef HUSKY_HIGHLEVEL_CONTROLLER_
#define HUSKY_HIGHLEVEL_CONTROLLER_

//some generically useful stuff to include...
#include <vector>
#include <iomanip>

#include <ros/ros.h> //ALWAYS need to include this
#include <sensor_msgs/LaserScan.h>

#include <geometry_msgs/Twist.h>

#include "pid.h"

namespace husky_highlevel_controller
{
    class HuskyHighLevelController
    {
        public:
            float smallest_value;
            int smallest_value_index;
            float angle_increment;
            float angle_minimum;
            float cte;

            /*
            * Constructor
            * @param nodeHandle the ROS handle
            */
            HuskyHighLevelController(ros::NodeHandle* nodeHandle);

            /*
            * Destructor
            */
            virtual ~HuskyHighLevelController();

            void hit_the_pillar();
            ros::NodeHandle nh_;


        private:

            /*
            * ROS topic callback method
            * @param msg the received message
            */

            // ROS node handle
            //ros::NodeHandle nh_;

            // callback
            void scanMessageReceived(const sensor_msgs::LaserScan& msg);

            ros::Subscriber sub; //these will be set up within the class constructor, hiding these ugly details
            ros::Publisher pub_vel;

            // member methods as well:
            void initializeSubscribers(); // we will define some helper methods to encapsulate the gory details of initializing subscribers, publishers and services
            void initializePublishers();  

            std::string topic_name_;
            
            int topic_size_queue_;


    }; /* class */
} /* namespace */

#endif  // this closes the header-include trick...ALWAYS need one of these to match #ifndef