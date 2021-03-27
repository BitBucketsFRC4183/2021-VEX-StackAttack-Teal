#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LeftDriveSmart = motor(PORT1, ratio18_1, false);
motor RightDriveSmart = motor(PORT10, ratio18_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 292.1, 165.1, mm, 1);
motor ClawMotor = motor(PORT2, ratio18_1, false);
motor ArmMotor = motor(PORT9, ratio18_1, false);
motor SecondArmMotor = motor(PORT4, ratio18_1, false);
/*vex-vision-config:begin*/
vision::signature Vision3__SIG_1 (1, 0, 0, 0, 0, 0, 0, 2.500, 0);
vision::signature Vision3__SIG_2 (2, 0, 0, 0, 0, 0, 0, 2.500, 0);
vision::signature Vision3__SIG_3 (3, -6003, -1311, -3657, -1065, 1185, 60, 0.800, 0);
vision::signature Vision3__SIG_4 (4, 0, 0, 0, 0, 0, 0, 2.500, 0);
vision::signature Vision3__SIG_5 (5, 0, 0, 0, 0, 0, 0, 2.500, 0);
vision::signature Vision3__SIG_6 (6, 0, 0, 0, 0, 0, 0, 2.500, 0);
vision::signature Vision3__SIG_7 (7, 0, 0, 0, 0, 0, 0, 2.500, 0);
vision Vision3 = vision ( vex::PORT3, 50, Vision3__SIG_1, Vision3__SIG_2, Vision3__SIG_3, Vision3__SIG_4, Vision3__SIG_5, Vision3__SIG_6, Vision3__SIG_7 );
/*vex-vision-config:end*/

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}