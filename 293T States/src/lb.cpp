#include "lb.hpp"
#include "main.h"


//lb
pros::Motor lb(-20);
pros::Rotation rotationSensor(9);

const int numStates = 4;
int states[numStates] = {0, 29, 100, 150};
int currState = 0;
int target = 0;

void nextState() {
    currState += 1;
    if (currState == numStates) {
        currState = 0;
    }
    target = states[currState];
}

void liftControl() {
    double kp = 1.4;
    double error = target - (rotationSensor.get_position()/100);
    double velocity = kp * error;
    lb.move(velocity/5);
}

void lbAsyncControl(void * param){
    while(true){
      liftControl();
      pros::delay(10);
    }
}

/*
//lb
pros::Motor lb(-20);
pros::Rotation rotationSensor(9);

const int numStates = 4;
int states[numStates] = {0, 29, 100, 150};
int currState = 0;
int target = 0;

//hang lb control
bool hanging = false;

void hangingFunc() {
    hanging = true;
}

void nextState() {
    currState += 1;
    if (currState == numStates) {
        currState = 0;
    }
    target = states[currState];
    if(hanging){
        target = 80;
    }
}

void liftControl() {
    double kp = 1.4;
    double error = target - (rotationSensor.get_position()/100);
    double velocity = kp * error;
    if(hanging){
        lb.move(velocity/5);
    }
    else{
        lb.move(velocity);
    }
}

void lbAsyncControl(void * param){
    while(true){
      liftControl();
      pros::delay(10);
    }
}*/

/*
#include "lb.hpp"
#include "main.h"


//lb
pros::Motor lb(-20);
pros::Rotation rotationSensor(9);

const int numStates = 4;
int states[numStates] = {0, 29, 100, 150};
int currState = 0;
int target = 0;

void nextState() {
    currState += 1;
    if (currState == numStates) {
        currState = 0;
    }
    target = states[currState];
}

void liftControl() {
    double kp = 1.4;
    double error = target - (rotationSensor.get_position()/100);
    double velocity = kp * error;
    lb.move(velocity/5);
}

void lbAsyncControl(void * param){
    while(true){
      liftControl();
      pros::delay(10);
    }
}*/