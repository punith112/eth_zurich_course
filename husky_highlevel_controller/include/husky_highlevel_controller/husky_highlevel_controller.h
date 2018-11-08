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

namespace husky_highlevel_controller
{
    class HuskyHighLevelController
    {
        public:

            /*
            * Constructor
            * @param nodeHandle the ROS handle
            */
            HuskyHighLevelController(ros::NodeHandle &nodeHandle);

            /*
            * Destructor
            */
            virtual ~HuskyHighLevelController();

        private:

            /*
            * ROS topic callback method
            * @param msg the received message
            */
            void scanMessageReceived(const sensor_msgs::LaserScan& msg);

            // ROS node handle
            ros::NodeHandle& nodeHandle_;

            // ROS topic subscriber_
            ros::Subscriber sub;

            std::string topic_name_;
            int topic_size_queue_;

    }; /* class */
} /* namespace */

#endif  // this closes the header-include trick...ALWAYS need one of these to match #ifndef