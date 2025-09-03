#include "main.h"

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller con(pros::E_CONTROLLER_MASTER);
/**
 * ports 1 + 2 are the left side group
 * ports 3 + 4 are the right side group
 * port 5 is cage door controls
 */
	pros::Motor tL (-1, pros::MotorGears::red);
	pros::Motor tR (-3, pros::MotorGears::red);
	pros::Motor bL (2, pros::MotorGears::red);
	pros::Motor bR (4, pros::MotorGears::red);
	pros::Motor cage (5, pros::MotorGears::green);

	while (true) {
		int left = con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int right = con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		if (con.get_digital(DIGITAL_R1)) {
      		cage.move_velocity(100); // This is 100 because it's a 100rpm motor
    	}
		if (con.get_digital(DIGITAL_R2)) {
	  		cage.move_velocity(-100); // This is -100 because it's a 100rpm motor
		}
		tL.move(left);
		bL.move(left);

		tR.move(right);
		bR.move(right);


	}
}