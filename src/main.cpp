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
/* Port List:
 * - Port 1: Transmitter
 * - Port 3: claw
 * - Ports 4-5: Back Left, Back Right
 * - Ports 6-7: Forward Left, Forward Right
 * 
 */
	pros::Motor tL (4, pros::MotorGears::green);
	pros::Motor bL (-7, pros::MotorGears::green);

	pros::Motor bR (-3, pros::MotorGears::green);
	pros::Motor tR (-6, pros::MotorGears::green);

	pros::Motor aL (-10, pros::MotorGears::red);
	pros::Motor aR (9, pros::MotorGears::red);

	pros::Motor claw (5, pros::MotorGears::green);

	claw.tare_position();
	claw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	aL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	aR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	int arm_speed = 75;
	int claw_speed = 100;
	int speedMult = 1;

	while (true) {
		int left = con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int right = con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		
		if (con.get_digital(DIGITAL_R1)) {
			claw.move_velocity(-1*claw_speed);
			pros::delay(100);
			claw.brake();
		}
		if (con.get_digital(DIGITAL_R2)) {
	  		claw.move_velocity(claw_speed);
			pros::delay(100);
			claw.brake();
		}

		if (con.get_digital(DIGITAL_L1)) {
			aL.move_velocity(arm_speed);
			aR.move_velocity(arm_speed);
			pros::delay(50);
			aL.brake();
			aR.brake();
		}

		if (con.get_digital(DIGITAL_L2)) {
			aL.move_velocity(-1*arm_speed);
			aR.move_velocity(-1*arm_speed);
			pros::delay(50);
			aL.brake();
			aR.brake();
		}

		tL.move(left * speedMult);
		bL.move(left * speedMult);

		tR.move(right * speedMult);
		bR.move(right * speedMult);


	}
}