#pragma once

#include "api.h"
#include "pros/optical.hpp"


inline pros::Motor intake(-2);
inline pros::Motor ladybrown(9);
inline pros::ADIDigitalOut mobile('A');
inline pros::ADIDigitalOut doinker('B');
inline pros::Rotation rotationSensor(10);
inline pros::Imu inertialSensor(1);
inline pros::Optical opt1(8);
inline pros::Optical opt2(4);


// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');





