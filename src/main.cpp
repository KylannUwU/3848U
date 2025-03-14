#include "main.h"
#include <cmath>
#include "EZ-Template/util.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "subsystems.hpp"
using pros::E_MOTOR_BRAKE_HOLD;


//#define RED 1



ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {
        -10,
        -11s,
        -13,
    },  // Left Chassis Ports (negative port will reverse it!)
    {
        18,
        19,
        20,
    },  // Right Chassis Ports (negative port will reverse it!)

    1,     // IMU Port
    3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    480);  // Wheel RPM

bool mobileToggle = false;
bool doinkerToggle = false;
bool flagMode = false;
bool autonStarted = false;
bool autonIsDone = false;
unsigned long toggleStartTime = 0;

const double KpLB = 5.0; // Ganancia proporcional
const double KiLB = 0.0; // Ganancia integral
const double KdLB = 0.0; // Ganancia derivativa

double integralValueLB = 0.0; 
double previousErrorLB = 0.0;
int targetValueLB = 4000; 

void controlMotor() 
{
    int encoderValue = rotationSensor.get_position(); 
    double error = targetValueLB - encoderValue;
    integralValueLB += error;
    double derivative = error - previousErrorLB;
    double output = KpLB * error + KiLB * integralValueLB + KdLB * derivative;
    if (output > 12000) output = 12000;
    else if (output < -12000) output = -12000;
    ladybrown.move_voltage(static_cast<int>(output));
    previousErrorLB = error;
}

void myTaskFunction() 
{
    while (true)
     {
        controlMotor();
        pros::delay(20);
    }
}



void initialize() 
{
    //AutonSelector auton_selector;
    //pros::Task controltask(controller_navigation);
  ez::ez_template_print();
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  opt1.set_led_pwm(100);
  opt2.set_led_pwm(100);

  pros::delay(500);
  chassis.opcontrol_curve_buttons_toggle(true);  // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0);    // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(0, 0);     // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)
  
  // Set the drive to your own constants from autons.cpp!
  default_constants();
  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
      //Auton("2stk SOLO AWP RED\n\nSOLO AWP RED", soloAWP_Red_2Stakes),
      //Auton("2stk SOLO AWP BLUE\n\nSOLO AWP BLUE", soloAWP_Blue_2Stakes),
 
      // Auton("SOLO AWP RED\n\nSOLO AWP RED", soloAWP_Red_NEW),
      // Auton("SOLO AWP BLUE\n\nSOLO AWP BLUE", soloAWP_Blue_NEW),
      //Auton("Elim6R \n\n BLUE", Elims_6rings_BLUE),      
      Auton("Elim6R \n\n RED", Elims_6rings_RED),
      Auton("SKILLS \n\n SkillAuton", Skills2),
      Auton("SOLO AWP Left\n\nSOLO AWP Left", soloAWP_LeftSide),
      Auton("SOLO AWP Right\n\nSOLO AWP Right", soloAWP_RightSide),
      Auton("Ellims 5 RED \n\nRED SIDE", Ellims_5rings_Red),
      Auton("Ellims 5 BLUE\n\nBLUE SIDE", Ellims_5rings_Blue),
      Auton("JustInCase Left\n\n 2 Rings", JustInCaseLeft),
      Auton("JustInCase Right\n\n 2 Rings", JustInCaseRight),
      Auton("SKILLS \n\n SkillAuton", Skills),
      Auton("Example Drive\n\nDrive forward and come back.", drive_example),
      Auton("Example Turn\n\nTurn 3 times.", turn_example),
      Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
      Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
      Auton("Swing Example\n\nSwing in an 'S' curve", swing_example),
      Auton("Motion Chaining\n\nDrive forward, turn, and come back, but blend everything together :D", motion_chaining),
      Auton("Combine all 3 movements", combining_movements),
      Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();

  master.rumble(".");
    
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() 
{

}


void competition_initialize() 
{
  
  // . . .
}

void autonomous() 
{
  autonStarted = true;
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.drive_brake_set(pros ::E_MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency
  ladybrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  pros::Task myTask(myTaskFunction);
  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
  myTask.remove();
}



void opcontrol() 
{

  
  if(autonStarted)
    autonIsDone = true;
  pros::motor_brake_mode_e_t driver_preference_brake = MOTOR_BRAKE_COAST;
  chassis.drive_brake_set(driver_preference_brake);
  ladybrown.set_brake_mode(E_MOTOR_BRAKE_HOLD);
 // intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
 // opt1.set_led_pwm(100);
 // opt2.set_led_pwm(100);
 // pros::delay(300);
  static int last_stop_time = 0;
  static int hue_detect_time = 0;
  static bool is_paused = false;
  while (true) 
  {

    pros::lcd::clear_line(0);
    pros::lcd::clear_line(1);
    pros::lcd::clear_line(2);
    //master.clear_line(1);

    if(!mobileToggle)
      master.print(1, 0, "MOBILE    ");
    else
      master.print(1, 0, "NOTHING    ");
    

    //master.clear_line(1);
    pros::lcd::print(0, "COLOR LEFT: %.2f ",  opt1.get_hue());
    pros::lcd::print(1, "COLOR RIGHT: %.2f ",  opt2.get_hue());
    //pros::lcd::print(2, "Chassis %.2f ",  chassis.get));

    if (!pros::competition::is_connected()) 
    {
      if (master.get_digital_new_press(DIGITAL_X))
        chassis.pid_tuner_toggle();

      if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) 
      {
        autonomous();
        chassis.drive_brake_set(driver_preference_brake);
      }

      chassis.pid_tuner_iterate();  // Allow PID Tuner to iterate
    }

    chassis.opcontrol_tank();  // Tank control
    
    if(master.get_digital(DIGITAL_R1) && master.get_digital(DIGITAL_R2))
      intake.move_voltage(-12000); // -8000

    
    
    
    
    
    
    
    
    else if(master.get_digital(DIGITAL_R1) &&  !master.get_digital(DIGITAL_R2) )
    {
         int current_time = pros::millis();

    
    #ifdef RED
    if (opt1.get_hue() > 150.0 || opt2.get_hue() > 150.0)  // No Blues Detect: 100.0* // 200.0 // **150.0
    #else
    if (opt1.get_hue() < 30.0 || opt2.get_hue() < 30.0)  // No Reds Detect: 30.0* // 45.0 
    #endif
    {
      // Si el motor no está en pausa, configurar el inicio del temporizador
        if (hue_detect_time == 0) {
            hue_detect_time = current_time;
        }

        // Primera etapa: mantener el motor encendido durante 100 ms
        if (!is_paused && current_time - hue_detect_time <= 100) { // 70 // *100
            intake.move_voltage(12000); // Motor activo
        }
        // Segunda etapa: detener el motor por 300 ms
        else if (current_time - hue_detect_time <= 200) {
            intake.move_voltage(0); // *0
            
            // wait pause just for intake and flip these two and test as well

          //  intake.move_voltage(-12000); // *iniyan added
          // intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);// Motor detenido
            is_paused = true; // Activar el estado de pausa
        }
        // Reiniciar después de la pausa
        else {
            hue_detect_time = 0; // Reiniciar el temporizador
            is_paused = false; // Salir de pausa
        }
    } else {
        // Si el HUE no es menor que 10, reiniciar todo
        hue_detect_time = 0;
        is_paused = false;
        intake.move_voltage(12000); // Motor sigue funcionando normalmente
    }
      flagMode = false;
    }








    else if(master.get_digital(DIGITAL_R2)  && !master.get_digital(DIGITAL_R1) )
    {
      intake.move_voltage(12000);
      flagMode = true;
    }
    else if(master.get_digital(DIGITAL_L1) && flagMode == true)	
      intake.move_voltage(-2000);
    else
      intake.move_voltage(0);

    if(flagMode == true)
      targetValueLB = 5650;
    else
      targetValueLB = 4000;

    if(master.get_digital(DIGITAL_L1) && rotationSensor.get_position() < 16500 && flagMode == true)
      ladybrown.move_voltage(8000); 
    else if((master.get_digital(DIGITAL_R2)  || master.get_digital(DIGITAL_L2))  && flagMode == true)
      controlMotor();
    else
    { 
      if( flagMode == false)
        controlMotor();
      else
        ladybrown.move_voltage(0); 
    }


    if(master.get_digital_new_press(DIGITAL_L1)  && flagMode == false)
      mobileToggle = !mobileToggle;
    if(mobileToggle)
      mobile.set_value(false);
    else if(!mobileToggle) 
      mobile.set_value(true); 




    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) // && !flagMode)
    {
        doinkerToggle = !doinkerToggle;
        toggleStartTime = pros::millis(); 
    }
    if (doinkerToggle && pros::millis() - toggleStartTime > 5000) 
        doinkerToggle = false; 

    if(doinkerToggle)
      doinker.set_value(true);
    else if(!doinkerToggle) 
      doinker.set_value(false); 

    pros::delay(ez::util::DELAY_TIME);
  }
}