#include "main.h"
#include "pros/rotation.h"

extern void liftControl();
extern void nextState();
extern void hangingFunc();

extern void lbAsyncControl(void * param);

//Motor & Sensor
extern pros::Motor lb;
extern pros::Rotation rotationSensor;