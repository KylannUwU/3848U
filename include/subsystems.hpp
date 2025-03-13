#pragma once

#include "api.h"
#include "pros/optical.hpp"


inline pros::Motor intake(-8);
inline pros::Motor ladybrown(11);
inline pros::ADIDigitalOut mobile('C');
inline pros::ADIDigitalOut doinker('B');
inline pros::Rotation rotationSensor(10);
inline pros::Imu inertialSensor(7);
inline pros::Optical opt1(8);
inline pros::Optical opt2(4);


// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');





