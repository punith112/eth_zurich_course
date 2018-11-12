#include "PID.h"


using namespace std;
using Eigen::VectorXd;


/*
* TODO: Complete the PID class.
*/

PID::PID() 
{
	//previous_cte = 0;
	is_initialized_ = false;
	previous_cte_avg = 0;
	VectorXd dK(3);
	VectorXd K(3);
	control_K = 0;
	control_stage = 0;
	cte_avg = 0;
	current_cte_avg = 0;
	previous_cte = 0;
}

PID::~PID() {}

// Steering PID Control
void PID::Init(double Kp, double Kd, double Ki) 
{
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
}



void PID::UpdateError(double cte, double dt) 
{
	/*
		Update the PID error variables given cross track error.
	*/


	if (!is_initialized_)
	{
		d_error = 0;
		i_error = 0;
		is_initialized_ = true;
	}
	else
	{
		// Time difference
		//dt = double(clock() - previous_time)/CLOCKS_PER_SEC;
		cout << "dt: " << dt  << endl;
		
		// differential error

		d_error = (cte - previous_cte);///dt;
		cout << "d_error: " << d_error  << endl;

		  // Integral error
	  	if (fabs(cte) < 0.01 || fabs(cte) > 1)
	  		i_error = 0;
	  	else
			i_error += cte*dt;
		cout << "i_error: " << i_error  << endl;
		
	}

	// Proportional Error
  	p_error = cte;

	previous_cte = cte;


}

void PID::MyCounter(double cte)
{
	cte_avg += cte;

	if (counter == (N_it - 1))
	{
		loop_number++;
		if (loop_number >= 2)
			previous_cte_avg = current_cte_avg;

		current_cte_avg = cte_avg/N_it;
		cte_avg = 0;

	}

	
}




double PID::TotalError() 
{
	double totalError = p_error * Kp + d_error * Kd + i_error * Ki;
	if (totalError > 1)
		totalError = 1;
	if (totalError <-1)
		totalError = -1;
	return -totalError;
}