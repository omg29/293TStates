#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "pros/adi.hpp"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

//clamp
inline pros::adi::Pneumatics clamp1('A', false);

//doinkers
inline pros::adi::Pneumatics leftDoinker('B', false);
inline pros::adi::Pneumatics rightDoinker('F', false);

