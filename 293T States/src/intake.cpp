#include "main.h"
#include "intake.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/screen.hpp"
#include "subsystems.hpp"

//intake motors
pros::Motor bottomIntake(-18);
pros::Motor upperIntake(19);

pros::MotorGroup intake{-18, 19};

//color sensor
pros::Optical colorSensor(10);

//color sort
const int RED = 0;
const int BLUE = 1;
const int NEUTRAL = 2;

int allianceColor = 0;

const int redLowThreshold = 340;
const int redHighThreshhold = 20;

const int blueLowThreshold = 30;
const int blueHighThreshold = 60;

int intakeSpeed;

std::string seenColor = "NO RING DETECTED";
int seenHue;

std::string colorSortStates[3] = {"RED", "BLUE", "NEUTRAL"};

bool antiJam = true;

void setIntake(int speed){
    intakeSpeed = speed;
}

void setAllianceColor(int color){
    allianceColor = color;
}

void cycleAllianceColor(){
    allianceColor += 1;
    if (allianceColor == 3){
        allianceColor = 0;
    }
    setAllianceColor(allianceColor);
}

void toggleAntiJam(){
    //antiJam = !antiJam;
    if(antiJam){
        antiJam = false;
    }
    else{
        antiJam = true;
        //controller.rumble("_");
    }
}

bool ringEjected = false;

void asyncIntakeControl(void * param){
    bool wrongRing = false;
    int elapsedTime = 0;
    int ejectTreshold = 9;

    while(true){
        //run intake
        intake.move(intakeSpeed);


        //antiJam
        /*
        if(antiJam){
            if((intakeSpeed > 150) && (upperIntake.get_actual_velocity() < 10)){
                intake.move(-127);
                pros::delay(300);
            }
        }*/        

        //color sort code
        seenHue = colorSensor.get_hue();
        if (seenHue > redLowThreshold || seenHue < redHighThreshhold){
            seenColor = "RED";
        }
        else if(seenHue > blueLowThreshold && seenHue < blueHighThreshold){
            seenColor = "BLUE";
        }
        else{
            seenColor = "NO RING DETECTED";
        }

        //print on brain
        printf("Hue value: %lf \n", colorSensor.get_hue());
        printf("Seen COlor: %lf \n", allianceColor);

        if(!wrongRing){
            if(allianceColor == 0 && seenColor == "BLUE"){
                wrongRing = true;
                elapsedTime = 0;
            }
            else if(allianceColor == 1 && seenColor == "RED"){
                wrongRing = true;
                elapsedTime = 0;
            }
            else if(allianceColor == 2){
                wrongRing = false;
            }
        }

        //eject
        /*
        if(elapsedTime > ejectTreshold && wrongRing){
            upperIntake.move(0);
            pros::delay(300);
            wrongRing = false;
        }*/
    /*
       if(wrongRing){
        ringEjected = false;
        upperIntake.set_zero_position_all(0);
        upperIntake.move_absolute(950, -127);
        while(!ringEjected){
            if(upperIntake.get_position() < 950){
                pros::delay(20);
            }
            else{
                ringEjected = true;
                upperIntake.move(0);
                pros::delay(3000);
            }
        }
        wrongRing = false;
       }*/

        //delay
        pros::delay(20);
        elapsedTime += 1; //idk if it should be +20 or +1

    }
}