#include "autons.hpp"
#include <string>
#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////


#define RED true
#define BLUE false

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

bool side = RED;

bool killtask = true;


void IntakeCS()
{
    static int hue_detect_pos = 0;
    static bool is_paused = false;
    int desiredHue = 0;

    
    if(side == RED)
      desiredHue = 125;
    else
      desiredHue = 30;
    bool RingHue = false;

    while(!autonIsDone)
    {
      int current_pos = intake.get_position();
      
      if(side == RED)
        RingHue = opt1.get_hue() > desiredHue || opt2.get_hue() > desiredHue;

      else
        RingHue = opt1.get_hue() < desiredHue || opt2.get_hue() < desiredHue;
       

      

      if (RingHue) 
      { 
        if (hue_detect_pos == 0) 
          hue_detect_pos = current_pos;
          

        if (current_pos - hue_detect_pos <= 290) 
            intake.move_voltage(12000); 
        

        else 
        {
            intake.move_voltage(0); 
            pros::delay(200);
            intake.move_voltage(-12000); 
            pros::delay(100);
            hue_detect_pos = 0;
        }
      } 
      
      else 
      {
        hue_detect_pos = 0;
        is_paused = false;
        intake.move_voltage(12000); 
      }
      pros::delay(20);
    }  
}


void IntakeDetector()
{
  while((opt1.get_proximity() > 255 || opt1.get_proximity() < 50) && !autonIsDone )
  {
    intake.move_voltage(12000);
    pros::delay(20);
  }
  killtask = false;
  intake.move_voltage(0);
}



void IntakeTest()
{
  mobile.set_value(true);
  pros::Task IntakeTesting(IntakeCS);
  while(1)
    pros::delay(20);
}

#pragma region Skills




void Skills2()
{

  // ALLIANCE WS
  chassis.pid_drive_constants_set(14, 0.0009, 230);///9/70
  targetValueLB = 9000;
  pros::delay(400);
  targetValueLB = 4000;
  pros::delay(400);

  // SWING TO MOGO 
  chassis.pid_swing_set(ez::RIGHT_SWING, 90_deg, 110, -12 );
  pros::delay(650);
  chassis.pid_drive_set(-14_in, 120);
  pros::delay(570);
  mobile.set_value(true);
  pros::delay(200);

  // 5 RINGS ROUTE
  chassis.pid_turn_set(180_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(17_in, 120);
  chassis.pid_wait_until(4_in);
  intake.move_voltage(12000);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(270_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(16_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(360_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(17_in, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(10_in, 90);
  // chassis.pid_wait_quick_chain();
  pros::delay(900);
  chassis.pid_turn_set(225_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(14_in, 120);
  //chassis.pid_wait_quick_chain();
  pros::delay(1000);
  chassis.pid_drive_set(-3_in, 120);
  chassis.pid_wait_quick_chain();
  
  // DROP MOGO
  chassis.pid_turn_set(135_deg, 90);
  chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(-8_in, 120);
  // chassis.pid_wait_quick_chain();
  chassis.drive_set(-50,-50);
  pros::delay(600);
  chassis.drive_set(0,0);
  pros::delay(100);
  mobile.set_value(false);
  intake.move_voltage(-6000);

  // GO TO N WALL STAKE 
  chassis.pid_swing_set(ez::LEFT_SWING, 180_deg, 110, -35 );
  chassis.pid_wait_quick_chain();
  targetValueLB = 5700;
  pros::delay(300);
  intake.move_voltage(12000);
  chassis.pid_drive_set(48_in, 120);
  // chassis.pid_wait_quick();
  pros::delay(1700);
  chassis.pid_drive_set(-3_in, 120);
  chassis.pid_wait_quick();
  chassis.pid_turn_set(270_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(5_in, 120);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(-1500);
  targetValueLB = 16500;
  pros::delay(700);
  chassis.drive_set(90,90);
  pros::delay(300);
  chassis.drive_set(0,0);
  pros::delay(200);
  targetValueLB = 4000;
  pros::delay(700);
 
  // GO TO MOGO 2
  chassis.pid_drive_set(-8_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(225_deg, 70);
  chassis.pid_wait();
  chassis.pid_drive_set(-48_in, 120);
  // chassis.pid_wait_quick_chain();
  pros::delay(1650);
  chassis.pid_turn_set(270_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-19_in, 120);
  // chassis.pid_wait_quick_chain();
  pros::delay(1300);
  mobile.set_value(true);

  // 5 RINGS ROUTE 
  chassis.pid_turn_set(180_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(15_in, 120);
  chassis.pid_wait_until(4_in);
  intake.move_voltage(12000);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(90_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(16_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(0_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(17_in, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(10_in, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(135_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(14_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-6_in, 120);
  chassis.pid_wait_quick_chain();
 
  // DROP MOGO
  chassis.pid_turn_set(225_deg, 90);
  chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(-8_in, 120);
  // chassis.pid_wait_quick_chain();
  chassis.drive_set(-60,-60);
  pros::delay(650);
  chassis.drive_set(0,0);
  pros::delay(100);
  mobile.set_value(false);
  intake.move_voltage(-12000);
  pros::delay(100);

  // N WALL STAKE 2 RINGS
  chassis.pid_swing_set(ez::RIGHT_SWING, 180_deg, 110, 40 );
  chassis.pid_wait_quick_chain();
  targetValueLB = 5700;
  pros::delay(300);
  intake.move_voltage(12000);
  chassis.pid_drive_set(55_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-17_in, 120);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(-1500);
  pros::delay(300);
  targetValueLB = 7000;
  pros::delay(300);
  chassis.pid_turn_set(90_deg, 90);
  chassis.pid_wait_quick_chain();
  pros::Task IntakeDetector1(IntakeDetector);
  chassis.pid_drive_set(12_in, 120);
  chassis.pid_wait_quick_chain();
  pros::delay(400);
  targetValueLB = 16500;
  pros::delay(700);
  chassis.drive_set(90,90);
  pros::delay(300);
  chassis.drive_set(0,0);
  pros::delay(200);
  targetValueLB =5700;
  pros::delay(700);
  if(killtask)
  {
    IntakeDetector1.remove();
    killtask = false;
    pros::delay(20);
  }
  intake.move_voltage(12000);
  pros::delay(900);
  intake.move_voltage(-1500);
  targetValueLB = 16500;
  pros::delay(700);
  chassis.drive_set(90,90);
  pros::delay(300);
  chassis.drive_set(0,0);
  pros::delay(200);
  targetValueLB =4000;
  pros::delay(700);



  // GO TO MOGO 3
  chassis.pid_drive_set(-10_in, 120);
  chassis.pid_wait_quick_chain(); 
  chassis.pid_turn_set(20_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-25_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::RIGHT_SWING, 90_deg, 90, 0);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-18_in, 120);
  chassis.pid_wait_quick_chain();
  mobile.set_value(true);

  // 6 RINGS ROUTE
  
  //CORNER RING
  chassis.pid_turn_set(45_deg, 90);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(12000);
  chassis.pid_drive_set(25_in, 120);
  chassis.pid_wait_quick_chain();
  // MID RING
  chassis.pid_turn_set(-45_deg, 90);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(0);
  chassis.pid_drive_set(25_in, 120);
  chassis.pid_wait_until(16_in);
  intake.move_voltage(12000);
  chassis.pid_wait_quick_chain();
  // CORNER RING
  chassis.pid_turn_set(-135_deg, 90);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(0);
  chassis.pid_drive_set(25_in, 120);
  chassis.pid_wait_until(16_in);
  intake.move_voltage(12000);
  chassis.pid_wait_quick_chain();
  // LAST ONLY1 RING
  chassis.pid_turn_set(-90_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(18_in, 120);
  chassis.pid_wait_quick_chain();
  //STACKED RING 1
  chassis.pid_turn_set(-180_deg, 50);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(13_in, 50);
  chassis.pid_wait_quick_chain();
  //STACKED RING 2
  chassis.pid_turn_set(-90_deg, 50);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(12_in, 50);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-5_in, 50);
  chassis.pid_wait_quick_chain();
  //RELEASE MOGO
  chassis.pid_turn_set(45_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-12_in, 120);
  chassis.pid_wait_quick_chain();
  mobile.set_value(false);
  intake.move_voltage(-6000);
  pros::delay(50);


  //GO TO MOGO 4
  chassis.pid_drive_set(5_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-75_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-85_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-45_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(45_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(135_deg, 90);
  chassis.pid_wait_quick_chain();
  



  

}




void Skills3()
{
  // FIRST RING ALLIANCE WALLSTAKE
  targetValueLB = 8000;
  pros::delay(700);
  targetValueLB = 4000;
  pros::delay(500);
  // MOGO 1: 4 RINGS AND CORNER
  chassis.pid_swing_set(ez::RIGHT_SWING, 90_deg, 80, 0 );
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-18_in, 120);
  pros::delay(750);
  mobile.set_value(true);
  pros::delay(200);
  chassis.pid_swing_set(ez::LEFT_SWING, 180_deg, 90, -40);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(12000);
  chassis.pid_drive_set(10_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::LEFT_SWING, 270_deg, 90, 0);
  chassis.pid_wait_quick_chain();
  pros::delay(250);
  chassis.pid_drive_set(7_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::LEFT_SWING, 360_deg, 90, 0);
  chassis.pid_wait_quick_chain();
  pros::delay(200);
  chassis.pid_drive_set(26_in, 90);
  chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(9_in, 110);
  // chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-5_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(135_deg,90);
  chassis.pid_wait();
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-15_in, 60);
  pros::delay(700);
  intake.move_voltage(-1000);
  mobile.set_value(false);
  pros::delay(200);

  
  // OTW TO MOGO 2
  // chassis.pid_drive_set(10_in,90);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_turn_set(270_deg,90);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-53_in, 110,true,true);
  // chassis.pid_wait_quick();
  // mobile.set_value(true);

  chassis.pid_swing_set(ez::RIGHT_SWING, 90, 90, 50);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(37_in, 110);
  // chassis.pid_wait_quick_chain();
  pros::delay(1500);
  chassis.pid_turn_set(270_deg,90);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, 110);
  pros::delay(1100);
  // chassis.pid_wait_quick_chain();
  mobile.set_value(true);


  // MOGO 2: 4 RINGS AND CORNER
  pros::delay(200);
  chassis.pid_swing_set(ez::RIGHT_SWING, 180_deg, 90, -40);
  intake.move_voltage(120000);
  chassis.pid_wait_quick_chain();
  pros::delay(200);
  chassis.pid_drive_set(10_in, 100);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::RIGHT_SWING, 90_deg, 90, 0);
  chassis.pid_wait_quick_chain();
  pros::delay(300);
  chassis.pid_drive_set(8_in, 100);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, 90, 0);
  chassis.pid_wait_quick_chain();
  pros::delay(300);
  chassis.pid_drive_set(26_in, 80);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-5_in, 100);
  chassis.pid_wait_quick_chain();   
  chassis.pid_turn_set(-135_deg, 90);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(-10_in, 110);
  chassis.pid_wait_quick_chain();
  mobile.set_value(false);
  intake.move_voltage(-1200);
  pros::delay(200);
  
  // NWALLSTAKE 1 
  chassis.pid_drive_set(5_in, 110);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-180_deg, 90);
  chassis.pid_wait_quick_chain();
  targetValueLB = 5700;
  intake.move_voltage(0);
  pros::delay(400);
  chassis.pid_drive_set(44_in, 110);
  // chassis.pid_wait_quick_chain();
  pros::delay(1700);
  intake.move_voltage(12000);
  chassis.pid_turn_set(-270_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.drive_set(40,40);
  pros::delay(1000);
  chassis.drive_set(0,0);
  pros::delay(500);
  intake.move_voltage(-600);
  pros::delay(200);
  targetValueLB = 16500;
  pros::delay(1100);
  chassis.drive_set(90,90);
  pros::delay(300);
  chassis.pid_drive_set(-5_in,90);
  pros::delay(600);
  targetValueLB = 4000;
  pros::delay(600);

  // MOGO 3: PLACE ON CORNER
  chassis.pid_swing_set(ez::LEFT_SWING,-360, 90, 25);
  pros::delay(950);
  chassis.pid_drive_set(-15_in,110);
  pros::delay(900);
  chassis.pid_swing_set(ez::RIGHT_SWING,-325, 90, 40);
  pros::delay(750);
  //chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-15_in,110);
  //chassis.pid_wait_quick_chain();
  pros::delay(1300);
  mobile.set_value(true);
  pros::delay(200);
  chassis.pid_turn_set(-50,90);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(-25_in,90);
  //chassis.pid_wait_quick_chain();
  pros::delay(1900);
  mobile.set_value(false);
  intake.move_voltage(-12000);
  pros::delay(200);

  // MOGO 4 RING AND PLACE ON CORNER

  chassis.pid_swing_set(ez::LEFT_SWING,90, 70, -15);
  chassis.pid_wait_until(-20_deg);
  pros::Task IntakeDt(IntakeDetector);
  chassis.pid_wait_quick_chain();
  // chassis.pid_swing_set(ez::RIGHT_SWING,-90, 90, 65);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_turn_set(90_deg, 90);
  // chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(5_in, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-50_in, 110);
  //chassis.pid_wait_quick_chain();
  pros::delay(2100);
  mobile.set_value(true);
  intake.move_voltage(12000);
  chassis.pid_swing_set(ez::RIGHT_SWING,135, 90, 20);
  //chassis.pid_wait_quick_chain();
  pros::delay(700);
  chassis.pid_drive_set(-12_in, 90);
  //chassis.pid_wait_quick_chain();
  pros::delay(800);
  chassis.pid_swing_set(ez::LEFT_SWING,25, 90, 30);
  //chassis.pid_wait_quick_chain();
  pros::delay(1200);
  chassis.pid_drive_set(-20_in, 90);
  //chassis.pid_wait_quick_chain();
  pros::delay(1500);
  intake.move_voltage(-5000);
  mobile.set_value(false);
  pros::delay(100);
  chassis.pid_drive_set(10_in, 90);
  chassis.pid_wait_quick_chain();
  // chassis.pid_turn_set(40_deg, 90);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_swing_set(ez::LEFT_SWING,60, 90, 30);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(5_in, 90);
  // chassis.pid_wait_quick_chain();
  

  intake.move_voltage(12000);
  targetValueLB = 5700;
  pros::delay(300);
  chassis.pid_turn_set(0_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(32_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-4_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-90_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(15_in, 120);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(-12000);
  targetValueLB = 16500;
  pros::delay(700);
  chassis.drive_set(50, 50);
  pros::delay(500);
  targetValueLB = 12000;
  pros::delay(500);
  intake.move_voltage(0);
  chassis.pid_swing_set(ez::LEFT_SWING, -135_deg, 110, 40 );
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, 50, 20 );
  chassis.pid_wait_quick_chain();
  chassis.drive_set(0, 0);
  pros::delay(500);
  
  
  // // ALLIANCE WS 2

  // // chassis.pid_wait_until(10_in);
  // pros::Task IntakeDt2(IntakeDetector);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_turn_set(-45_deg, 90);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_swing_set(ez::RIGHT_SWING,0, 80, 57);
  // chassis.pid_wait_quick_chain();
  // // chassis.pid_drive_set(-5_in, 100);
  // // chassis.pid_wait_quick_chain();
  // chassis.drive_set(-40, -40);
  // pros::delay(900);
  // chassis.drive_set(0, 0);
  // pros::delay(200);
  // intake.move_voltage(12000);
  // pros::delay(400);
  // chassis.pid_swing_set(ez::RIGHT_SWING, -45,90,50);
  // chassis.pid_wait_quick_chain();

  // // NWALLSTAKE 2
  // if(IntakeDt2.get_state() == pros::task_state_e_t::E_TASK_STATE_RUNNING)
  //   IntakeDt2.remove();
  // intake.move_voltage(12000);  
  // targetValueLB = 5500;
  // pros::delay(300);
  // chassis.pid_drive_set(43_in, 110);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_turn_set(-90_deg, 90);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(12_in, 110);
  // chassis.pid_wait_quick();
  // intake.move_voltage(12000);
  // chassis.drive_set(40, 40);
  // pros::delay(1000);
  // intake.move_voltage(-1000);
  // pros::delay(300);
  // chassis.drive_set(0, 0);
  // pros::delay(300);
  // targetValueLB = 16500;
  // pros::delay(800);
  // chassis.drive_set(40, 40);
  // pros::delay(300);
  // chassis.pid_drive_set(-10_in, 110);
  // chassis.pid_wait_quick();
}



///
// Constants
///
void Skills()
{
  targetValueLB = 8000;
  pros::delay(700);
  chassis.pid_drive_set(-8_in, 100);
  pros::delay(600);
  targetValueLB = 4000;
  pros::delay(500);
  chassis.pid_turn_set(90_deg, 90); 
  pros::delay(900);
  chassis.pid_drive_set(-20_in, 100);
  pros::delay(700);
  mobile.set_value(true);
  pros::delay(100);
    chassis.pid_turn_set(180_deg, 90); 
  chassis.pid_wait();
  intake.move_voltage(12000);
    chassis.pid_drive_set(25_in, 100);
  chassis.pid_wait();
  chassis.pid_turn_set(203_deg, 90); // ANGULO PARA AGARRAR ANILLO
  chassis.pid_wait();
  chassis.pid_drive_set(50_in, 100);
  chassis.pid_wait();
  targetValueLB = 5650;
  chassis.pid_turn_set(-20_deg, 90); ////////////////////////aqui
  chassis.pid_wait();


  chassis.pid_drive_set(23_in, 100);//25
  chassis.pid_wait();





  chassis.pid_turn_set(-63_deg, 90); ////////////angulo wall -60
  chassis.pid_wait();
  chassis.pid_drive_set(3_in, 100);//////////AVANCE WALL
  chassis.pid_wait();
  chassis.pid_turn_set(-63_deg, 90); ////////////angulo wall



  chassis.pid_wait();
  intake.move_voltage(-2000);
  targetValueLB = 18000;
  pros::delay(1000);
  chassis.drive_set(127, 127);
  pros::delay(100);
  chassis.drive_set(-127, -127);
  pros::delay(100);
  chassis.drive_set(0, 0);
  targetValueLB = 12000;

  chassis.pid_drive_set(-10_in, 100);/// 8 
  chassis.pid_wait();
  chassis.pid_turn_set(0_deg, 90); /////////////////////////////////////////////////////////////
  chassis.pid_wait();
  intake.move_voltage(12000);
  chassis.pid_drive_set(25_in, 100);
  chassis.pid_wait();
 /* chassis.pid_turn_set(0_deg, 90); 
  chassis.pid_wait();*/
  chassis.pid_drive_set(26_in, 100);   
  chassis.pid_wait();
  pros::delay(500);
    chassis.pid_drive_set(10_in, 100);//////////////////////////   7
  chassis.pid_wait();
  intake.move_voltage(0);
    chassis.pid_turn_set(-140_deg, 90); //   100
  chassis.pid_wait();
  intake.move_voltage(12000);
      chassis.pid_drive_set(7_in, 100);
  chassis.pid_wait();
      chassis.pid_turn_set(-210_deg, 90); 
  chassis.pid_wait();
        chassis.pid_drive_set(-10_in, 100);
  chassis.pid_wait();
  intake.move_voltage(-12000);
  pros::delay(200);
  intake.move_voltage(0);
    mobile.set_value(false);
  pros::delay(100);
  chassis.pid_drive_set(10_in, 100);
  chassis.pid_wait();
  chassis.pid_turn_set(-90_deg, 90); 
  chassis.pid_wait();


  chassis.pid_drive_constants_set(40, 0.001, 50);//230
  chassis.pid_heading_constants_set(6, 0, 0);//15

  ////////////////////////////////////////////////////////////////// 2nd MOBILE
  chassis.pid_drive_set(-68_in, 100);
  chassis.pid_wait(); 
  mobile.set_value(true);
  pros::delay(100);


  chassis.pid_drive_constants_set(14, 0.001, 230);


  chassis.pid_turn_set(90_deg, 90); 
  chassis.pid_wait();
   intake.move_voltage(12000);

  chassis.pid_drive_set(17_in, 100);
  chassis.pid_wait();
   chassis.pid_drive_set(10_in, 100);
  chassis.pid_wait();
    chassis.pid_turn_set(-140_deg, 90); //140
  chassis.pid_wait(); 
  chassis.pid_drive_set(-10_in, 100);
  chassis.pid_wait();
  intake.move_voltage(-12000);
  pros::delay(200);
  intake.move_voltage(0);
  mobile.set_value(false);
  pros::delay(100);


  chassis.pid_drive_set(10_in, 100);   /// 7
  chassis.pid_wait();



  chassis.pid_turn_set(-180_deg, 90); 
  chassis.pid_wait(); 
   intake.move_voltage(12000);
  targetValueLB = 5650;
  chassis.pid_drive_set(33_in, 100);
  chassis.pid_wait();

  chassis.pid_turn_set(-235_deg, 90); /////////////// 238
  chassis.pid_wait(); 


    chassis.pid_drive_set(15_in, 100);
  chassis.pid_wait();


  intake.move_voltage(-2000);
  targetValueLB = 18000;
  pros::delay(1000);
  chassis.drive_set(127, 127);
  pros::delay(100);
  chassis.drive_set(-127, -127);
  pros::delay(100);
  chassis.drive_set(0, 0);
  targetValueLB = 12000;

  chassis.pid_drive_set(-10_in, 100);/// 8 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-140_deg, 90); ///////////////
  chassis.pid_wait(); 
    intake.move_voltage(12000);


   chassis.pid_drive_set(37_in, 100);
  chassis.pid_wait();   

  
//pros::delay(200);
  intake.move_voltage(0);
  chassis.pid_turn_set(50_deg, 90); ///////////////40
  chassis.pid_wait(); 
    chassis.pid_drive_set(-35_in, 100);
  chassis.pid_wait();   
  mobile.set_value(true);
  pros::delay(100);
intake.move_voltage(12000);
 pros::delay(1000);
 intake.move_voltage(0);
chassis.pid_turn_set(180_deg, 90); ///////////////
  chassis.pid_wait(); 
    mobile.set_value(false);
  pros::delay(100);
     chassis.pid_drive_set(7_in,   100);
  chassis.pid_wait();   
  chassis.pid_turn_set(90_deg, 90); ///////////////
  chassis.pid_wait(); 
  chassis.pid_drive_set(60_in, 100);
  chassis.pid_wait(); 
  chassis.pid_turn_set(90_deg, 90); ///////////////
  chassis.pid_wait(); 
  chassis.pid_drive_constants_set(40, 0.001, 50);//230
  chassis.pid_heading_constants_set(6, 0, 0);//15

   chassis.pid_drive_set(-100_in, 100);
  chassis.pid_wait(); 
    chassis.drive_set(127, 127);
  pros::delay(300);
    chassis.drive_set(0, 0);
   pros::delay(300);
  chassis.drive_set(-127, -127);
  pros::delay(1000);
  chassis.drive_set(0, 0);
    chassis.drive_set(60, 60);
  pros::delay(300); 
  chassis.drive_set(0, 0);




  //chassis.pid_drive_constants_set(14, 0.001, 230);



}


#pragma endregion Skills
#pragma region soloAWP

void soloAWP_LeftSide()
{
targetValueLB = 5000;

// Cambia el tipo de swing a RIGHT_SWING y ajusta el ángulo
chassis.pid_swing_set(ez::RIGHT_SWING, -30_deg, 90, 5);
chassis.pid_wait();

intake.move_voltage(12000);
pros::delay(2000);
intake.move_voltage(0);

// Cambia el ángulo de giro a positivo
chassis.pid_turn_set(70_deg, 90); 
chassis.pid_wait();

// Mantén los movimientos lineales iguales
chassis.pid_drive_set(6_in, 100);
chassis.pid_wait();

targetValueLB = 16000;
pros::delay(500);

targetValueLB = 4000;

// Cambia el ángulo de giro a positivo
chassis.pid_turn_set(60_deg, 90);
chassis.pid_wait();

chassis.pid_drive_set(-40_in, 100);
chassis.pid_wait();

mobile.set_value(true);
pros::delay(100);

// Cambia el giro a -180 para lado izquierdo
chassis.pid_turn_set(-180_deg, 90);
chassis.pid_wait();

intake.move_voltage(12000);

// Ajusta la distancia a reflejar el lado izquierdo
chassis.pid_drive_set(17_in, 70);
chassis.pid_wait();

pros::delay(1500);

// Ajusta el sensor al lado izquierdo
chassis.drive_sensor_reset();
pros::delay(20);

// Ajusta la condición del sensor y las velocidades para lado izquierdo
while (chassis.drive_sensor_left() > -25.0) {
    chassis.drive_set(-80, -50); // Invierte las velocidades
    pros::delay(20);
}

chassis.drive_set(0, 0);
intake.move_voltage(0);


}
void soloAWP_RightSide()
{
  targetValueLB = 5000;
  chassis.pid_swing_set(ez::LEFT_SWING, 30_deg, 90, 5);
  chassis.pid_wait();
  intake.move_voltage(12000);
  pros::delay(2000);
  intake.move_voltage(0);
  chassis.pid_turn_set(-72_deg, 90);/////////////////////
  chassis.pid_wait();
   chassis.pid_drive_set(6_in, 100);///9
  chassis.pid_wait();
  targetValueLB = 16000;
  pros::delay(500);
 // chassis.pid_drive_set(4_in, 100);
  //chassis.pid_wait();

  targetValueLB = 4000;
  chassis.pid_turn_set(-60_deg, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(-40_in, 100);
  chassis.pid_wait(); 
  mobile.set_value(true);
  pros::delay(100);
  chassis.pid_turn_set(180_deg, 90);
  chassis.pid_wait();
  intake.move_voltage(12000);
  chassis.pid_drive_set(17_in, 70);//20
  chassis.pid_wait();
/*
   pros::delay(1500);
  chassis.pid_wait();
    pros::delay(1000);
  chassis.pid_turn_set(-120_deg, 90);
  chassis.pid_wait();
    pros::delay(1000);
  chassis.pid_turn_set(-120_deg, 90);
  chassis.pid_drive_set(5_in,70);
  chassis.pid_wait();
    pros::delay(1000);
  chassis.pid_turn_set(-120_deg, 90);
  chassis.pid_turn_set(180_deg,90);
  */
   /*chassis.drive_sensor_reset();
  pros::delay(20);

  while( chassis.drive_sensor_right() > -34.0)
  {
    chassis.drive_set(-50,-80);
    pros::delay(20);
  }
  chassis.drive_set(0,0);
  intake.move_voltage(0);
  */

}
void soloAWP_Blue_NEW()
{
  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, 90,0);
  //chassis.pid_wait_quick_chain();
  pros::delay(300);
  targetValueLB = 10000;
  pros::delay(300);
  targetValueLB = 4000;
  pros::delay(300);
  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, 90,0);
  //chassis.pid_wait_quick_chain();
  pros::delay(350);
  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, 90,15);
  //chassis.pid_wait_quick_chain();
  pros::delay(350);
  intake.move_voltage(-12000);
  pros::delay(100);
  intake.move_voltage(0);
  pros::delay(400);
  pros::Task IntakeDTAWP(IntakeDetector);
  pros::delay(800);
  chassis.pid_turn_set(-55_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-28_in, 110);
  // chassis.pid_wait_quick_chain();
  pros::delay(1200);
  mobile.set_value(true);
  pros::delay(150);
  chassis.pid_turn_set(-180_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(18_in, 110);
  chassis.pid_wait_until(3_in);
  intake.move_voltage(12000);
  //chassis.pid_wait_quick_chain();
  pros::delay(800);

  chassis.pid_turn_set(-270_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(7.5_in, 110);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(12000);
  chassis.pid_swing_set(ez::RIGHT_SWING, -360_deg, 90,-30);
  //chassis.pid_wait_quick();
  pros::delay(700);
  chassis.pid_swing_set(ez::RIGHT_SWING, -405_deg, 90,15);
  //chassis.pid_wait_quick_chain();
  pros::delay(700);
  chassis.pid_drive_set(38_in, 110);
  //chassis.pid_wait_quick_chain();
  pros::delay(1400);
  mobile.set_value(false);
  chassis.pid_turn_set(-135_deg, 90);
  //chassis.pid_wait_quick_chain();
  pros::delay(1200);
  chassis.pid_drive_set(-24_in, 110);
  //chassis.pid_wait_quick_chain();
  pros::delay(1100);
  mobile.set_value(true);
  pros::delay(100);
  chassis.pid_turn_set(0_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(17_in, 110);
  chassis.pid_wait_quick_chain();
  pros::delay(100);
  chassis.pid_swing_set(ez::LEFT_SWING, -45_deg, 110,65);
  chassis.pid_wait_until(-15_deg);
  targetValueLB = 5500;
  chassis.pid_wait_quick_chain();
  chassis.drive_set(-20,-20);
  pros::delay(300);

  
  
}

void soloAWP_Red_NEW()
{
  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, 90,0); // chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, 90,0);
  pros::delay(300);
  targetValueLB = 10000;
  pros::delay(300);
  targetValueLB = 4000;
  pros::delay(300);
  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, 90,0); // chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, 90,0);
  pros::delay(370);
  chassis.pid_swing_set(ez::RIGHT_SWING, -50_deg, 95,15); // chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, 90,15);
  pros::delay(370);
  intake.move_voltage(-12000);
  pros::delay(100);
  intake.move_voltage(0);
  pros::delay(400);
  pros::Task IntakeDTAWP(IntakeDetector);
  pros::delay(800);
  chassis.pid_turn_set(60_deg, 90); // chassis.pid_turn_set(-55_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-27_in, 120);
  pros::delay(1000);
  mobile.set_value(true);
  pros::delay(100);
  chassis.pid_turn_set(180_deg, 90); // chassis.pid_turn_set(-180_deg, 90);
  pros::delay(700);
  //chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(20_in, 120);
  chassis.pid_wait_until(3_in);
  intake.move_voltage(12000);
  pros::delay(670);

  chassis.pid_turn_set(270_deg, 90); // chassis.pid_turn_set(-270_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.drive_set(90, 90);
  //chassis.pid_wait_quick_chain();
  pros::delay(230);
  chassis.drive_set(0, 0);
  //chassis.pid_wait_quick_chain();
  pros::delay(50);
  pros::Task IntakeCS1(IntakeCS);
  chassis.pid_swing_set(ez::LEFT_SWING, 360_deg, 120,-40); // chassis.pid_swing_set(ez::RIGHT_SWING, -360_deg, 90,-30);
  pros::delay(530);
  chassis.pid_swing_set(ez::LEFT_SWING, 400_deg, 120,20); // chassis.pid_swing_set(ez::RIGHT_SWING, -405_deg, 90,15);
  pros::delay(530);
  chassis.pid_drive_set(38_in, 120);
  pros::delay(1300);
  mobile.set_value(false);
  chassis.pid_turn_set(142_deg, 90); // chassis.pid_turn_set(-135_deg, 90);
  pros::delay(1200);
  chassis.pid_drive_set(-26_in, 120);
  pros::delay(1160);
  mobile.set_value(true);
  pros::delay(100);
  chassis.pid_turn_set(0_deg, 90);
  //chassis.pid_wait_quick_chain();
  pros::delay(750);
  chassis.pid_drive_set(19_in, 127);
//  chassis.pid_wait_quick_chain();
  pros::delay(950);
  
  chassis.pid_swing_set(ez::RIGHT_SWING, 50_deg, 120,63); // chassis.pid_swing_set(ez::LEFT_SWING, -45_deg, 110,65);
  chassis.pid_wait_until(15_deg); // chassis.pid_wait_until(-15_deg);
  targetValueLB = 5500;
  chassis.pid_wait_quick_chain();
  chassis.drive_set(-20,-20);
  pros::delay(300);

  
}

#pragma endregion soloAWP
#pragma region Elims


void Ellims_5rings_Blue() /// NUEVO ES DERECHO OJOOO
{
  targetValueLB = 5500;
  chassis.pid_swing_set(ez::LEFT_SWING, 30_deg, 90, 5);
  chassis.pid_wait();
  intake.move_voltage(12000);
  pros::delay(1000);
  intake.move_voltage(0);
  chassis.pid_turn_set(-72_deg, 90);/////////////////////70
  chassis.pid_wait();
  chassis.pid_drive_set(6_in, 100);///9
  chassis.pid_wait();
  targetValueLB = 16000;
  pros::delay(500);
  targetValueLB = 4000;
  chassis.pid_turn_set(-60_deg, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(-40_in, 100);
  chassis.pid_wait(); 
  mobile.set_value(true);
  pros::delay(100);
  chassis.pid_turn_set(180_deg, 90);
  chassis.pid_wait();
  intake.move_voltage(12000);
  chassis.pid_drive_set(17_in, 70);//20
  chassis.pid_wait();
  chassis.pid_drive_set(-17_in, 70);//20
  chassis.pid_wait();
  chassis.pid_turn_set(135_deg, 90);
  chassis.pid_wait(); 
  chassis.pid_drive_set(18_in, 70);//20
  chassis.pid_wait();
  chassis.pid_swing_set(ez::LEFT_SWING, 180_deg, 90, 5);
  chassis.pid_wait();
  chassis.pid_drive_set(13_in, 70);//20
  chassis.pid_wait();
  pros::delay(500);
  intake.move_voltage(0);
  chassis.drive_set(-127, -20);
  pros::delay(400);
  chassis.drive_set(0, 0);
  pros::delay(200);
  chassis.drive_set(-70, -127);
  pros::delay(800); //1700 IT WAS
  chassis.drive_set(0, 0);

}
void Ellims_5rings_Red()
{
  targetValueLB = 5500;

  // Change swing to RIGHT_SWING and adjust the angle for the left side
  chassis.pid_swing_set(ez::RIGHT_SWING, -30_deg, 90, 5); 
  chassis.pid_wait();

  intake.move_voltage(12000); // Activate intake
  pros::delay(1000);          // Wait for intake to process objects
  intake.move_voltage(0);     // Stop intake

  // Change turn angle to positive for the left side
  chassis.pid_turn_set(70_deg, 90); 
  chassis.pid_wait();

  chassis.pid_drive_set(6_in, 100); // Move forward 6 inches
  chassis.pid_wait();

  targetValueLB = 16000; // Adjust motor target value
  pros::delay(500);

  targetValueLB = 4000; // Reduce motor target value

  // Change turn angle to positive for the left side
  chassis.pid_turn_set(60_deg, 90); 
  chassis.pid_wait();

  chassis.pid_drive_set(-40_in, 100); // Move backward 40 inches
  chassis.pid_wait();

  mobile.set_value(true); // Activate mobile goal mechanism
  pros::delay(100);

  // Change turn angle to -180 for the left side
  chassis.pid_turn_set(-180_deg, 90); 
  chassis.pid_wait();

  intake.move_voltage(12000); // Activate intake
  chassis.pid_drive_set(17_in, 70); // Move forward 17 inches
  chassis.pid_wait();

  chassis.pid_drive_set(-17_in, 70); // Move backward 17 inches
  chassis.pid_wait();

  // Change turn angle to -135 for the left side
  chassis.pid_turn_set(-135_deg, 90); 
  chassis.pid_wait();

  chassis.pid_drive_set(18_in, 70); // Move forward 18 inches
  chassis.pid_wait();

  // Change swing to RIGHT_SWING and adjust the angle for the left side
  chassis.pid_swing_set(ez::RIGHT_SWING, -180_deg, 90, 5); 
  chassis.pid_wait();

  chassis.pid_drive_set(11_in, 70); // Move forward 13 inches
  chassis.pid_wait();

  pros::delay(500); // Wait to stabilize

  intake.move_voltage(0); // Stop intake

  // Adjust drive commands for the left side
  chassis.drive_set(-20, -127); // Turn left while reversing
  pros::delay(400);             
  chassis.drive_set(0, 0);      // Stop robot

  pros::delay(200); // Short pause

  chassis.drive_set(-127, -70); // Turn left with a sharper turn
  pros::delay(800);             
  chassis.drive_set(0, 0);      // Stop robot
}

void Elims_6rings_BLUE()
{
  // TAKE MOGO
  chassis.pid_drive_set(-23_in, 120);
  pros::delay(1100);  
  mobile.set_value(true);
  pros::delay(150);

  // AUTON LINE RINGS
  chassis.pid_turn_set(-130_deg, 90);
  chassis.pid_wait();
  intake.move_voltage(120000);
  // chassis.pid_drive_set(12_in,110);
  chassis.pid_drive_set(19_in,110);
  chassis.pid_wait_quick_chain();
  // chassis.pid_swing_set(ez::LEFT_SWING, -90_deg, 80, 0);
  // chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::LEFT_SWING, -90_deg, 80, -30);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(2_in,70);
  chassis.pid_wait_quick_chain();
  
  // MID RING
  chassis.pid_swing_set(ez::LEFT_SWING, 32_deg, 80, -35);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(36_in, 120);
  chassis.pid_wait_until(5_in);
  intake.move_voltage(0);
  chassis.pid_wait_until(17_in);
  side = BLUE;
  pros::Task intakeControl2(IntakeCS);
  pros::delay(500);
  chassis.pid_swing_set(ez::LEFT_SWING, -42_deg, 90, 0);
  chassis.pid_wait_quick();
 
  //CORNER RINGS
  chassis.drive_set(70, 70);
  pros::delay(1400);
  for(int i = 0; i < 3; i++)
  {
    chassis.pid_drive_set(-2.5_in,35);
    chassis.pid_wait_quick_chain();
    pros::delay(400);
    chassis.drive_set(60, 60);
    pros::delay(800);
    chassis.drive_set(0, 0);
    pros::delay(200);
  }
  chassis.pid_drive_set(-3_in,35);
  chassis.pid_wait_quick_chain();  
  intakeControl2.remove();
  intake.move_voltage(0);
}

void Elims_6rings_RED()
{
  // TAKE MOGO
  chassis.pid_drive_set(-23_in, 120);
  pros::delay(1100);  
  mobile.set_value(true);
  pros::delay(150);

  // AUTON LINE RINGS
  // chassis.pid_turn_set(-130_deg, 90);
  chassis.pid_turn_set(135_deg, 90); // Mirrored turn
  chassis.pid_wait();
  intake.move_voltage(120000);
  // chassis.pid_drive_set(12_in,110);
  chassis.pid_drive_set(13_in,110);
  chassis.pid_wait_quick_chain();
  // chassis.pid_swing_set(ez::LEFT_SWING, -90_deg, 80, 0);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_swing_set(ez::LEFT_SWING, -90_deg, 80, -30);
  chassis.pid_swing_set(ez::RIGHT_SWING, 90_deg, 80, -30); // Mirrored swing
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(2_in,70);
  chassis.pid_wait_quick_chain();
  
  // MID RING
  // chassis.pid_swing_set(ez::LEFT_SWING, 32_deg, 80, -35);
  chassis.pid_swing_set(ez::RIGHT_SWING, -32_deg, 80, -35); // Mirrored swing
  chassis.pid_wait_quick();
  chassis.pid_drive_set(36_in, 120);
  chassis.pid_wait_until(5_in);
  intake.move_voltage(0);
  chassis.pid_wait_until(17_in);
  // side = BLUE;
  pros::Task intakeControl2(IntakeCS);
  pros::delay(500);
  // chassis.pid_swing_set(ez::LEFT_SWING, -42_deg, 90, 0);
  chassis.pid_swing_set(ez::RIGHT_SWING, 42_deg, 90, 0); // Mirrored swing
  chassis.pid_wait_quick();
 
  //CORNER RINGS
  chassis.drive_set(70, 70);
  pros::delay(1400);
  for(int i = 0; i < 3; i++)
  {
    chassis.pid_drive_set(-2.5_in,35);
    chassis.pid_wait_quick_chain();
    pros::delay(400);
    chassis.drive_set(60, 60);
    pros::delay(800);
    chassis.drive_set(0, 0);
    pros::delay(200);
  }
  chassis.pid_drive_set(-3_in,35);
  chassis.pid_wait_quick_chain();  
  intakeControl2.remove();
  intake.move_voltage(0);
}



#pragma endregion Elims
#pragma region JustInCase

void JustInCaseLeft()
{
  targetValueLB = 16000;
  chassis.pid_drive_set(-15_in, 80);
  chassis.pid_wait();
  chassis.pid_turn_set(45_deg, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(-18_in, 80);///
  chassis.pid_wait();
  mobile.set_value(true);
  pros::delay(300);
  chassis.pid_turn_set(90_deg, 90);
  chassis.pid_wait(); 
  intake.move_voltage(12000);
  chassis.pid_drive_set(20_in, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(130_deg, 90);//
  chassis.pid_wait(); 
  chassis.pid_drive_set(25_in, 110);
  chassis.pid_wait();
  targetValueLB = 18300;
  pros::delay(500);
  chassis.drive_set(-50, -50);
  pros::delay(500);
  chassis.drive_set(0, 0);
  targetValueLB = 4000;
  pros::delay(500);
  intake.move_voltage(0);

}
void JustInCaseRight()
{
 targetValueLB = 16000;
chassis.pid_drive_set(-15_in, 80);
chassis.pid_wait();

// Cambia el ángulo de giro a -45 grados para girar a la derecha
chassis.pid_turn_set(-45_deg, 90);
chassis.pid_wait();

chassis.pid_drive_set(-18_in, 80);
chassis.pid_wait();
mobile.set_value(true);
pros::delay(300);

// Cambia el ángulo de giro a -90 grados para girar a la derecha
chassis.pid_turn_set(-90_deg, 90);
chassis.pid_wait();

intake.move_voltage(12000);
chassis.pid_drive_set(20_in, 110);
chassis.pid_wait();

// Cambia el ángulo de giro a -125 grados para girar a la derecha
chassis.pid_turn_set(-130_deg, 90); //-123 ///////////
chassis.pid_wait();

chassis.pid_drive_set(25_in, 110);
chassis.pid_wait();
targetValueLB = 18300;
pros::delay(500);
chassis.drive_set(-50, -50);
pros::delay(500);
chassis.drive_set(0, 0);
targetValueLB = 4000;
pros::delay(500);
intake.move_voltage(0);
}


#pragma endregion JustInCase
#pragma region Constants


void default_constants() {

  chassis.pid_heading_constants_set(12, 0, 20);
  chassis.pid_drive_constants_set(14, 0.001, 230);///9/70
  chassis.pid_drive_constants_backward_set(14, 0.001 , 230);
  chassis.pid_turn_constants_set(4.5, 0.02, 40);//2.30 /0.04 //20
  chassis.pid_swing_constants_set(5.8, 0, 68);//

  chassis.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(80_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(4_in);

  chassis.slew_drive_constants_set(7_in, 80);
}



void Testing()
{
  chassis.pid_drive_set(48_in, 110);
  chassis.pid_wait_quick();
  chassis.pid_turn_set(180_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(48_in, 110);
  chassis.pid_wait_quick();
  chassis.pid_turn_set(0_deg, 90);
  chassis.pid_wait_quick_chain();

}

#pragma endregion Constants
#pragma region examples

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  /*chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();*/

  chassis.pid_drive_set(-24_in, DRIVE_SPEED);
  chassis.pid_wait();
/*
  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();*/
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at


  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .'


#pragma endregion examples