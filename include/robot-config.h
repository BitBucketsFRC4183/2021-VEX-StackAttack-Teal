using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor LeftDriveSmart;
extern motor RightDriveSmart;
extern drivetrain Drivetrain;
extern motor ClawMotor;
extern motor ArmMotor;
extern motor SecondArmMotor;
extern motor IntakeWheel1Motor;
extern motor IntakeWheel2Motor;
extern signature Vision3__SIG_1;
extern signature Vision3__SIG_2;
extern signature Vision3__SIG_3;
extern signature Vision3__SIG_4;
extern signature Vision3__SIG_5;
extern signature Vision3__SIG_6;
extern signature Vision3__SIG_7;
extern vision Vision3;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );