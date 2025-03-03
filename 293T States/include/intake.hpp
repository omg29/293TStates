#include "main.h"
#include "pros/motor_group.hpp"

extern pros::Motor bottomIntake;

extern pros::Motor upperIntake;

extern pros::MotorGroup intake;

extern const int RED;
extern const int BLUE;
extern const int NEUTRAL;

extern int allianceColor;

extern void setIntake(int speed);

extern void cycleAllianceColor();

extern void toggleAntiJam();

extern void asyncIntakeControl(void * param);
