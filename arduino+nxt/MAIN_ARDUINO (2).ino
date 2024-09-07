#include "GyverTimer.h"
GTimer myTimer(MS);
#include <Multiservo.h>

#include <Servo.h>
// библиотека для работы с модулями по интерфейсу SPI
#include <SPI.h>
// библиотека для работы со сборкой силовых ключей
#include <AmperkaFET.h>
// пин выбора устройства на шине SPI
#define PIN_CS  A0 /// не используемый пин - оставил для совместимости использования библиотеи от амперки
#define NFET1_ON_PIN  A8 /// пин включения для силовых сборок Amperka nFET модуль 1
#define NFET2_ON_PIN  A9 /// пин включения для силовых сборок Amperka nFET модуль 2
////////////////////////////////////////////////////////////////
#define t_start 2  // кнопка старта для робота 
#define wait_s 10
/////////////////////////////////////////////////////////////////
Multiservo  L1;
Multiservo  L2;
Multiservo  L3;
Multiservo  L4;
Multiservo  oct;
Multiservo  Ld;

Multiservo  R1;
Multiservo  R2;
Multiservo  R3;
Multiservo  R4;
Multiservo  Rb;


Servo  headr;
Servo  headl;

/////////////////////////////////////////////////////////////////


///////////////////////////////////////////
#define min_L1 52
#define min_L2 35
#define min_L3 50
#define min_L4 36
#define min_oct 100
#define min_Ld 160 

#define min_R1 10
#define min_R2 30
#define min_R3 55
#define min_R4 170 
#define min_Rb 10 

#define max_L1 52 + 60
#define max_L2 35 + 60
#define max_L3 50 + 60
#define max_L4 36 + 70
#define max_oct 40
#define max_Ld  130

#define max_R1 10 + 60
#define max_R2 30 + 60
#define max_R3 55 + 60
#define max_R4 145 
#define max_Rb 30

/////////////////////////////////////////////////////////
int headr_start  = 110; // голова ровно 
int headl_start  = 61;
int random_neck_move_pause = 2500;

#define headr_pos_start 110

#define headr_pos_play 138 // прижимается к саксафону 
//#define headl_play 61-30

#define headr_pos_p 120 // рядом с саксафонон (типо клапан)
//#define headl_p 31 -  5
#define klapan_1 4 // 
#define klapan_2 4// 
#define klapan 4


int flag_flag = 0;
int h = 0;

int L1_s = 0;// не нажаты//  L1.write(min_L1);
int L2_s = 0;// не нажаты//  L2.write(min_L2);
int L3_s = 0;// не нажаты//  L3.write(min_L3);
int L4_s = 0;// не нажаты//  L4.write(min_L4);
int oct_s = 0;// не нажаты// oct.write(min_oct);
int Ld_s = 0;// не нажаты//  Ld.write(min_Ld);

int R1_s = 0;// не нажаты// R1.write(min_R1);
int R2_s = 0;// не нажаты// R2.write(min_R2);
int R3_s = 0;// не нажаты// R3.write(min_R3);
int R4_s = 0;// не нажаты// R4.write(min_R4);
int Rb_s = 0;// не нажаты// Rb.write(min_Rb);



int L = 0; 
int pos_now = 0;
int k = 0;
int polo_head_r = headr_start;
int polo_head_l = headl_start;

///////////////////////////////////////////////////

void servo_position(int servo_numer, int p){  // номер сервы и ее положение:( нажата 1 или расслабленна 0)
   switch (servo_numer) {
    case 1:
      if(p == 1)
      {
         if (L1_s == 0)
         {
           L1.write(max_L1);
         }
      }
      else
      {
         if (L1_s == 1)
         {
           L1.write(min_L1);
         }
      }
      break;
    case 2:
      if(p == 1)
      {
         if (L2_s == 0)
         {
           L2.write(max_L2);
         }
      }
      else
      {
         if (L2_s == 1)
         {
           L2.write(min_L2);
         }
      }
      break;
    case 3:
      if(p == 1)
      {
         if (L3_s == 0)
         {
           L3.write(max_L3);
         }
      }
      else
      {
         if (L3_s == 1)
         {
           L3.write(min_L3);
         }
      }
      break;
    case 4:
      if(p == 1)
      {
         if (L4_s == 0)
         {
           L4.write(max_L4);
         }
      }
      else
      {
         if (L4_s == 1)
         {
           L4.write(min_L4);
         }
      }
      break;
   case 5:
      if(p == 1)
      {
         if (oct_s == 0)
         {
           oct.write(max_oct);
         }
      }
      else
      {
         if (oct_s == 1)
         {
           oct.write(min_oct);
         }
      }
      break;
      
    case 6:
      if(p == 1)
      {
         if (Ld_s == 0)
         {
           Ld.write(max_Ld);
         }
      }
      else
      {
         if (Ld_s == 1)
         {
           Ld.write(min_Ld);
         }
      }
      break;
      
   case 7:
      if(p == 1)
      {
         if (R1_s == 0)
         {
           R1.write(max_R1);
         }
      }
      else
      {
         if (R1_s == 1)
         {
           R1.write(min_R1);
         }
      }
      break;

     case 8:
      if(p == 1)
      {
         if (R2_s == 0)
         {
           R2.write(max_R2);
         }
         else
         {
           R2.write(max_R2);
         }
      }
      else
      {
         if (R2_s == 1)
         {
           R2.write(min_R2);
         }
         else
         {
           R2.write(min_R2);
         }
      }
      break;

      case 9:
      if(p == 1)
      {
         if (R3_s == 0)
         {
           R3.write(max_R3);
         }
      }
      else
      {
         if (R3_s == 1)
         {
           R3.write(min_R3);
         }
      }
      break;

     case 10:
      if(p == 1)
      {
         if (R4_s == 0)
         {
           R4.write(max_R4);
         }
      }
      else
      {
         if (R4_s == 1)
         {
           R4.write(min_R4);
         }
      }
      break;
    case 11:
      if(p == 1)
      {
         if (Rb_s == 0)
         {
           Rb.write(max_Rb);
         }
      }
      else
      {
         if (Rb_s == 1)
         {
           Rb.write(min_Rb);
         }
      }
      break;
      
}
delay(1);//задержка обязательна 
}

///=================================================================================================================================================================
///===  ФУНКЦИЯ НОТ ===///
///=================================================================================================================================================================
void zero(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,0); //L1
    delay(100);
    servo_position(2,0); //L2
    delay(100);
    servo_position(3,0); //L3
    delay(100);
    servo_position(4,0); //L4
    delay(100);
    servo_position(5,0); //oct
    delay(100);
    servo_position(6,0); //
     delay(100);
    servo_position(7,0); //R1
    delay(100);
    servo_position(8,0); //R2
    delay(100);
    servo_position(9,0); //R3
    delay(100);
    servo_position(10,0); //R4
    delay(100);
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 0;
  L2_s = 0;
  L3_s = 0;
  L4_s = 0;
  oct_s = 0;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}
void F_1(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,1); //L3
    servo_position(4,0); //L4
    servo_position(5,0); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,1); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 1;
  L4_s = 0;
  oct_s = 0;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 1;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}
void G1(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,1); //L3
    servo_position(4,0); //L4
    servo_position(5,0); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 1;
  L4_s = 0;
  oct_s = 0;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}
void G_1(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,1); //L3
    servo_position(4,1); //L4
    servo_position(5,0); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 1;
  L4_s = 1;
  oct_s = 0;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}
void a1(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,0); //L3
    servo_position(4,0); //L4
    servo_position(5,0); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 0;
  L4_s = 0;
  oct_s = 0;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}

void a_1(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,0); //L3
    servo_position(4,0); //L4
    servo_position(5,0); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,1); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 0;
  L4_s = 0;
  oct_s = 0;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 1;
  myTimer.stop();
  Serial.println("Time");
}

void H1(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,0); //L2
    servo_position(3,0); //L3
    servo_position(4,0); //L4
    servo_position(5,0); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 0;
  L3_s = 0;
  L4_s = 0;
  oct_s = 0;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}
void C2(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,0); //L1
    servo_position(2,1); //L2
    servo_position(3,0); //L3
    servo_position(4,0); //L4
    servo_position(5,0); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 0;
  L2_s = 1;
  L3_s = 0;
  L4_s = 0;
  oct_s = 0;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}

void C_2(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,0); //L1
    servo_position(2,0); //L2
    servo_position(3,0); //L3
    servo_position(4,0); //L4
    servo_position(5,0); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 0;
  L2_s = 0;
  L3_s = 0;
  L4_s = 0;
  oct_s = 0;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}
void d2(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,1); //L3
    servo_position(4,0); //L4
    servo_position(5,1); //oct
    servo_position(6,0); //Ld
    servo_position(7,1); //R1
    servo_position(8,1); //R2
    servo_position(9,1); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 1;
  L4_s = 0;
  oct_s = 1;
  Ld_s = 0;
  
  R1_s = 1;
  R2_s = 1;
  R3_s = 1;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}

void d_2(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,1); //L3
    servo_position(4,0); //L4
    servo_position(5,1); //oct
    servo_position(6,0); //Ld
    servo_position(7,1); //R1
    servo_position(8,1); //R2
    servo_position(9,1); //R3
    servo_position(10,1); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 1;
  L4_s = 0;
  oct_s = 1;
  Ld_s = 0;
  
  R1_s = 1;
  R2_s = 1;
  R3_s = 1;
  R4_s = 1;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}
void E2(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,1); //L3
    servo_position(4,0); //L4
    servo_position(5,1); //oct
    servo_position(6,0); //Ld
    servo_position(7,1); //R1
    servo_position(8,1); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 1;
  L4_s = 0;
  oct_s = 1;
  Ld_s = 0;
  
  R1_s = 1;
  R2_s = 1;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}

void F2(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,1); //L3
    servo_position(4,0); //L4
    servo_position(5,1); //oct
    servo_position(6,0); //Ld
    servo_position(7,1); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 1;
  L4_s = 0;
  oct_s = 1;
  Ld_s = 0;
  
  R1_s = 1;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}
void F_2(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,1); //L3
    servo_position(4,0); //L4
    servo_position(5,1); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,1); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 1;
  L4_s = 0;
  oct_s = 1;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 1;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}
void G2(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,1); //L3
    servo_position(4,0); //L4
    servo_position(5,1); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 1;
  L4_s = 0;
  oct_s = 1;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}
void G_2(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,1); //L3
    servo_position(4,1); //L4
    servo_position(5,1); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 1;
  L4_s = 1;
  oct_s = 1;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}

void a2(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,0); //L3
    servo_position(4,0); //L4
    servo_position(5,1); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 0;
  L4_s = 0;
  oct_s = 1;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}
void a_2(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,0); //L3
    servo_position(4,0); //L4
    servo_position(5,1); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,1); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 0;
  L4_s = 0;
  oct_s = 1;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 1;
  myTimer.stop();
  Serial.println("Time");
}

void H2(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,0); //L2
    servo_position(3,0); //L3
    servo_position(4,0); //L4
    servo_position(5,1); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 0;
  L3_s = 0;
  L4_s = 0;
  oct_s = 1;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}
void C3(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,0); //L1
    servo_position(2,1); //L2
    servo_position(3,0); //L3
    servo_position(4,0); //L4
    servo_position(5,1); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 0;
  L2_s = 1;
  L3_s = 0;
  L4_s = 0;
  oct_s = 1;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}

void C_3(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,0); //L1
    servo_position(2,0); //L2
    servo_position(3,0); //L3
    servo_position(4,0); //L4
    servo_position(5,1); //oct
    servo_position(6,0); //Ld
    servo_position(7,0); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 0;
  L2_s = 0;
  L3_s = 0;
  L4_s = 0;
  oct_s = 1;
  Ld_s = 0;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}

void d1(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,1); //L3
    servo_position(4,0); //L4
    servo_position(5,0); //oct
    servo_position(6,0); //Ld
    servo_position(7,1); //R1
    servo_position(8,1); //R2
    servo_position(9,1); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 1;
  L4_s = 0;
  oct_s = 0;
  Ld_s = 0;
  
  R1_s = 1;
  R2_s = 1;
  R3_s = 1;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}


void d3(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,0); //L1
    servo_position(2,0); //L2
    servo_position(3,0); //L3
    servo_position(4,0); //L4
    servo_position(5,1); //oct
    servo_position(6,1); //Ld
    servo_position(7,0); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 0;
  L2_s = 0;
  L3_s = 0;
  L4_s = 0;
  oct_s = 1;
  Ld_s = 1;
  
  R1_s = 0;
  R2_s = 0;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}
void d_1(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,1); //L3
    servo_position(4,0); //L4
    servo_position(5,0); //oct
    servo_position(6,0); //Ld
    servo_position(7,1); //R1
    servo_position(8,1); //R2
    servo_position(9,1); //R3
    servo_position(10,1); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 1;
  L4_s = 0;
  oct_s = 0;
  Ld_s = 0;
  
  R1_s = 1;
  R2_s = 1;
  R3_s = 1;
  R4_s = 1;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}

void E1(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,1); //L3
    servo_position(4,0); //L4
    servo_position(5,0); //oct
    servo_position(6,0); //Ld
    servo_position(7,1); //R1
    servo_position(8,1); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 1;
  L4_s = 0;
  oct_s = 0;
  Ld_s = 0;
  
  R1_s = 1;
  R2_s = 1;
  R3_s = 0;
  R4_s = 0;
  Rb_s = 0;
  myTimer.stop();
  Serial.println("Time");
}

void F1(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,1); //L3
    servo_position(4,0); //L4
    servo_position(5,0); //oct
    servo_position(6,0); //Ld
    servo_position(7,1); //R1
    servo_position(8,0); //R2
    servo_position(9,0); //R3
    servo_position(10,0); //R4
    servo_position(11,0); //Rb
    ////////////////////////
}
void TEST_ALL(int TIME){
  myTimer.setInterval(TIME);   // запуск в режиме интервала time_to_long_ms мс
  myTimer.start();
  Serial.println("Time");
    servo_position(1,1); //L1
    servo_position(2,1); //L2
    servo_position(3,1); //L3
    servo_position(4,1); //L4
    servo_position(5,1); //oct
    servo_position(6,1); //Lds
    servo_position(7,1); //R1
    servo_position(8,1); //R2
    servo_position(9,1); //R3
    servo_position(10,1); //R4
    servo_position(11,1); //Rb
    ////////////////////////
  while(myTimer.isReady() == false){
  }
  L1_s = 1;
  L2_s = 1;
  L3_s = 1;
  L4_s = 1;
  oct_s = 1;
  Ld_s = 1;
  
  R1_s = 1;
  R2_s = 1;
  R3_s = 1;
  R4_s = 1;
  Rb_s = 1;
  myTimer.stop();
  Serial.println("Time");
  zero(100);
}

///==============================================================================
///==============================================================================
/// Amperka NFET секция - все что имеет отношение к силовым ключам ниже
///==============================================================================
///==============================================================================
// создаём объект mosfet для работы со сборкой силовых ключей
// передаём номер пина выбора устройства на шине SPI для совместимости - выбран не используемый фактически пин.
FET mosfet(PIN_CS);

//// переменные для работы с силовыми ключами
byte nfet1_current_state[8]; ///текущее состояние ключей на плате 1
byte nfet2_current_state[8]; /// текущее состояние ключей на плате 2 
byte impulse_time_for_nfet_on=1; // длительность импульса для включения ключей из регистров in ms


///==============================================================================
///  Функция включения выбранной сборки ключей. Из программы не используется. Нужна для
///  вызова из функции управления пинами сборки ключей.
//// Берется текущее состояние из памяти  и выставляются все ключи сразу на указанном модуле
//// в конце в буфера обоих сборок записываются нули на всякий случай, если пройдет
//// фантомный импульс включения на какую-то сборку - то она просто погасит все светодиоды и выключит транзисторы
void nfet_on(byte device_number) { /// device_number - номер сборки 1 или 2
switch (device_number) {
  case 1:
     for(int i = 0; i < 8; i++ ) {
     // передаем по очереди каждый ключ для 1 модуля на оба модуля
      mosfet.digitalWrite(i, nfet1_current_state[i]);
     }
      //delay(impulse_time_for_nfet_on);
      digitalWrite(NFET1_ON_PIN, HIGH); // включаем только нужный модуль
      delay(impulse_time_for_nfet_on);
      digitalWrite(NFET1_ON_PIN, LOW); /// сбрасываем сигнал включения 1 модуля.
      //delay(impulse_time_for_nfet_on);
      //delay(impulse_time_for_nfet_on);
  break;
  case 2:
     for(int i = 0; i < 8; i++ ) {
     // передаем по очереди каждый ключ для 1 модуля на оба модуля
      mosfet.digitalWrite(i, nfet2_current_state[i]);
     }
      //delay(impulse_time_for_nfet_on);
      digitalWrite(NFET2_ON_PIN, HIGH); // включаем только нужный модуль
      delay(impulse_time_for_nfet_on);
      digitalWrite(NFET2_ON_PIN, LOW); /// сбрасываем сигнал включения 1 модуля.
      //delay(impulse_time_for_nfet_on);
      //delay(impulse_time_for_nfet_on);
  break;

  /// установка на обоих модулях nfet 0 во всех выходах, на случай самосработки импульса включения
  //// но никакой модуль не включаем, на нем сейчас уже включены нужные транзисторы
  for(int i = 0; i < 8; i++ ) {
      mosfet.digitalWrite(i, LOW);
  }    
  //delay(impulse_time_for_nfet_on);
}  
}

///==============================================================================
///  Функция включения указанного пина в выбранной сборке ключей. 
///  сначала меняется текущее состояние в памяти для указанной сборки
///  потом все новое состояние  (все 8 пинов) включаются на указанной сборке.
/// device_number - номер сборки 1 или 2
/// pin_number - номер нужного пина на сборке от 1 до 8.
/// pin_state - состояние которое надо установить 0 - выключено, >0 - включено.
void set_nfet(byte device_number, byte pin_number, byte pin_state) {

switch (device_number) { /// выбираем нужный модуль
  case 1:
       switch (pin_number) { //// выбираем нужный пин - образ состояния пина в памяти - переменную отражающую текущее состояние пина модуля
         case 1:
           if (pin_state==0) {nfet1_current_state[0] = 0;} else {nfet1_current_state[0] = 1;} //// записываем в переменную 1 или 0
         break;
         case 2:
           if (pin_state==0) {nfet1_current_state[1] = 0;} else {nfet1_current_state[1] = 1;}
         break;
         case 3:
           if (pin_state==0) {nfet1_current_state[2] = 0;} else {nfet1_current_state[2] = 1;}
         break;
         case 4:
           if (pin_state==0) {nfet1_current_state[3] = 0;} else {nfet1_current_state[3] = 1;}
         break;
         case 5:
           if (pin_state==0) {nfet1_current_state[4] = 0;} else {nfet1_current_state[4] = 1;}
         break;
         case 6:
           if (pin_state==0) {nfet1_current_state[5] = 0;} else {nfet1_current_state[5] = 1;}
         break;
         case 7:
           if (pin_state==0) {nfet1_current_state[6] = 0;} else {nfet1_current_state[6] = 1;}
         break;
         case 8:
           if (pin_state==0) {nfet1_current_state[7] = 0;} else {nfet1_current_state[7] = 1;}
         break;
       } 
       nfet_on(1); //// записываем все переменные отражающие состояние пинов в модуль 1 и включаем его.
    break;
  case 2:
       switch (pin_number) {
         case 1:
           if (pin_state==0) {nfet2_current_state[0] = 0;} else {nfet2_current_state[0] = 1;}
         break;
         case 2:
           if (pin_state==0) {nfet2_current_state[1] = 0;} else {nfet2_current_state[1] = 1;}
         break;
         case 3:
           if (pin_state==0) {nfet2_current_state[2] = 0;} else {nfet2_current_state[2] = 1;}
         break;
         case 4:
           if (pin_state==0) {nfet2_current_state[3] = 0;} else {nfet2_current_state[3] = 1;}
         break;
         case 5:
           if (pin_state==0) {nfet2_current_state[4] = 0;} else {nfet2_current_state[4] = 1;}
         break;
         case 6:
           if (pin_state==0) {nfet2_current_state[5] = 0;} else {nfet2_current_state[5] = 1;}
         break;
         case 7:
           if (pin_state==0) {nfet2_current_state[6] = 0;} else {nfet2_current_state[6] = 1;}
         break;
         case 8:
           if (pin_state==0) {nfet2_current_state[7] = 0;} else {nfet2_current_state[7] = 1;}
         break;
       } 
       nfet_on(2); //// записываем все переменные отражающие состояние пинов в модуль 2 и включаем его.
    break;
}
}

///==============================================================================
///  Функция инициализации сборок силовых ключей Amperka nfet.
//// Вызывается один раз из setup();
void nfet_init() {
  // начало работы с силовыми ключами
  mosfet.begin();

  //// настраиваем пины включения модулей
  pinMode(NFET1_ON_PIN, OUTPUT); 
  pinMode(NFET2_ON_PIN, OUTPUT); 

 /// сразу на них выставляем ноль
 digitalWrite(NFET1_ON_PIN, LOW);
 digitalWrite(NFET2_ON_PIN, LOW);
  
 /// выключаем все транзисторы на обоих модулях
 /// в переменных состояния сборок устанаввливаем все биты в ноль
  for(int i = 0; i < 8; i++ ) {
    nfet1_current_state[i]=0;
    nfet2_current_state[i]=0;
  }
 /// записываем текущее состояние(все нули) и включаем оба модуля. 
 nfet_on(1);
 nfet_on(2);
}



///==============================================================================
///==============================================================================
/// BT секция - все что имеет отношение к BT ниже
///==============================================================================
///==============================================================================

///==============================================================================
//BT Recieve variables
byte bt_recieve_byte; /// данные из сообщения от NXT - 1 байт
byte bt_led = 0; /// индикация приема от нхт
byte bt_recieve_on_once = 0; //// служебная переменная
long int number_recieved = 0; /// количество принятых байт от nxt
bool Bt_rcv_refresh = false; /// принимает значение true когда пришел новый байт

///==============================================================================
//// BT send variables
byte bt_send_start = 0; /// если присвоить 1 то посылка байта стартует на nxt немедленно
byte bt_send_byte = 0; /// байт для посылки на nxt
byte bt_send_on_once = 0; /// флаг для выполнения команды только один раз при старте чтения из порта, служебная переменная
int auto_send_time = 1000; /// время автопосылки данных на NXT
long int number_sended = 0; /// количество посланных на nxt байт


///==============================================================================
///==============================================================================
/// основные функии работы с BT
///==============================================================================
void bt_send_command(byte data1) /// послать 1 байт на NXT;
{
     bt_send_byte = data1; /// переменной для послыки на nxt присваивается значение аргумента функции 
     reset_bt_send_pause_timer(); /// сброс таймера автопослыки, чтобы не пересекся с данной посылкой
     bt_send_start = 1; /// даем разрешение на немедленную посылку одного байта
     BT_send(1); /// пвызывем функцию посылки по  bt  и она следуя разрешению немедленной посылки сразу посылает байт на nxt
}


int bt_recieve_byte_() //// функия возвращающая значение _нового_ принятого байта от NXT или -1.
{
  BT_recieve(1); ////вызывается фунция проверки что что-то пришло по bt от nxt
  if (Bt_rcv_refresh == true){ //если пришел новый байт
    return bt_recieve_byte; /// возвращаем этот байт
  }
  return -1; /// нового байта нет - возвпащаем -1.
}

///==============================================================================
///==============================================================================
/// ФУНКЦИИ РАБОТЫ С BT
///======================================================================

//// функция проверки пришло ли что-то от бт модуля.
//// вызывается с параметром 1 или 0.

////    1-проверить что пришло, если пришло, считать и записать в глобальную переменную, установить флажок что пришли новые данные.
////       если не пришло - ничего не делать, установить флажок что ничего нового не пришло.
////    0-отключить проверку приема от модуля бт.    
void BT_recieve(byte on_off) { 
  //// получение данных через BT переменная on_off сообщает функции надо ли читать порт модуля или не надо
  /// при необходимости можно вызывать функцию с отключением чтения из модуля - заготовка для основной программы управления роботом
  /// без пауз от распберри
  byte uart2_input; /// байт для чтения из модуля bt

  /// управление светодиодом ардуины только когда функция 
  /// работает  и получаются данные из бт модуля
  /// переменна bt_led меняет свое значение каждый раз когда байт приходит от модуля
  //// соответственно смена состояния светодиода - один принятый байт от nxt 
  if (bt_led==0)  {
    digitalWrite(LED_BUILTIN, LOW);
    } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }

  if (on_off==1) { /// функция вызвана в режиме чтения из модуля бт
     if (bt_recieve_on_once == 0) { 
        /// если перед этим функция вызывалась с отключением чтения из модуля бт, то это значит, что за время пока она была выключена
        /// в модуль бт могло наприходить много байтов и они накопились в буфере. Они нам не нужны - нужен последний байт. NXT шлет их автоматом
        /// каждую секунду, поэтому обнуляем буфер при переключении на прием и при получении новых байтов в следующем вызове этой функции читаем их
         
        while (Serial1.available()) Serial1.read(); // очистка буфера приема bt
        bt_recieve_on_once = 1;
     }

    if (Serial1.available()) // проверяем, поступают ли какие-то байты из BT, если буфер очищен, то конечно их нет.
      { /// если байт пришел
        uart2_input=Serial1.read(); /// читаем его

        /// это для отладки - посмjтреть в мониторе порта ардуино что пришло
        //Serial.print(uart2_input);
        //Serial.println();

        bt_recieve_byte  = uart2_input; /// записываем в глобальную переменную что пришло. 
        if (bt_led==0) {bt_led=1;} else {bt_led=0;}  ///меняем состояние светодиода индикации приема 
        number_recieved++; ///добавляем 1 в количество принятых байтов
        Bt_rcv_refresh = true; ///// выставлем флаг что что-то новое пришло.
       } else {
        ///в случае отсутсвтия байт в модуле бт
        /// или после очистки буфера приема бт
        /// вновь принятых байтов нет 
        Bt_rcv_refresh = false; /// выставляем флаг отсутствия новых данных и завершаем функцию
       }
 } else { /// если фунция вызывается с командой отключения приема, то следующее включение начнется с чистки буфера приема модуля бт
   bt_recieve_on_once = 0;
   Bt_rcv_refresh = false;
 }
}

//// 
unsigned long bt_send_pause_timer = 0;
/// =======================================================================================================
/// пауза меду автоматической посылкой данных на NXT  
void reset_bt_send_pause_timer() {
    bt_send_pause_timer = millis();   // current millis value
}
/// 
//=======================================================================================================
/// пауза меду автоматической посылкой данных на NXT  
byte is_bt_send_pause_timer(uint16_t p_t) {
  if (millis() - bt_send_pause_timer >= p_t) 
  {
   return 1;
  }
  else 
  {
   return 0;
  }
}


/// 
//=======================================================================================================
/// Функция передачи данных на NXT через BT
void BT_send(byte on_off) { //// отправка данных на NXT
 if (on_off==1) {

      ///автоматическая посылка байта через бт каждый интервал в фоне при вызове функции
     if (is_bt_send_pause_timer(auto_send_time)==1) {
         reset_bt_send_pause_timer();
         bt_send_start=1;
        }

  
      if (bt_send_start==1) {

        ///ждем что порт свободен для записи в него данных
        while (Serial.availableForWrite()<1) {
          //Serial.println("wait bt comport for write");
          delay(1);
         }; 

         bt_send_on_once = 1;
         
         Serial1.write(bt_send_byte);

         bt_send_start=0;
         
         //Serial.print("Send ");
         //Serial.print(bt_send_byte);
         //Serial.println(" done!");
         number_sended++;
         
         //Serial.print("Sended number =");
         //Serial.print(number_sended);
         //Serial.println();

      }     

 } else {
         bt_send_start=0;
         bt_send_on_once = 0;
         reset_bt_send_pause_timer();
         //Serial.println("Command number end");
         //Serial.print(bt_send_command_number);
         //Serial.println();
     }
}

/// =======================================================================================================
/// =======================================================================================================
/// КОНЕЦ ФУНКЦИЙ РАБОТЫ С BT
/// =======================================================================================================


byte a = 0; ///переменная для примера работы бт
///=================================================================================================================================================================
///===  ФУНКЦИЯ СЕРВЫ ШЕИ ===///
///=================================================================================================================================================================
void servo_head_move(int pos_head_end, int speed_head, int wait){
  L = pos_head_end - (headr.read());    
  if (L>0){
   for (int i = 1; i < L; i++){
     polo_head_r = headr_start + i;
     polo_head_l = headl_start - i;
     headr.write(polo_head_r); 
     headl.write(polo_head_l); 
     delay(speed_head);  
    }        
    headr_start = polo_head_r;
    headl_start = polo_head_l;
  }
  if (L<0){
   L = abs(L);
   for (int i = 1; i < L; i++){
     polo_head_r = headr_start - i;
     polo_head_l = headl_start + i;
     headr.write(polo_head_r); 
     headl.write(polo_head_l); 
     delay(speed_head);  
    }
    headr_start = polo_head_r;
    headl_start = polo_head_l;
  }
  delay(wait);
}
////////////////////////////////////////////////////
///=================================================================================================================================================================
///=================================================================================================================================================================
///=================================================================================================================================================================
///===  ФУНКЦИИ ВСЕГО РОБОТА ( ПЕРЕДАЧА СИГНАЛОВ )  ===///
///=================================================================================================================================================================
///=================================================================================================================================================================
///=================================================================================================================================================================
/// таймер для случайного поворота
unsigned long pause_timer1 = 0;
void reset_pause_timer1(){
      pause_timer1 = millis();   // current millis value
}
    
byte is_pause_timer1(uint16_t p_t) {
  if (millis() - pause_timer1 >= p_t) 
  {
   return 1;
  }
  else 
  {
   return 0;
  }
}
void head_neck_random(){
     if (is_pause_timer1(random_neck_move_pause) == 1) {
             reset_pause_timer1();         
             servo_head_move(10*random(1, 4) + 100, 50,0);
      }
         
}

///============================================
// === ДВИЖЕНИЕ САКСОФОНА === //
///============================================
/*
void move_motor_start(){
  set_nfet(1,8,1);//A1
  set_nfet(1,7,1);//A1
}
////////////////////////////////////////////////
void move_motor_finish(){
  set_nfet(1,8,0);
  set_nfet(1,7,1);
}

//////////////////////////////////////////////////
void move_motor_3_centre(){
  set_nfet(1,6,1);
  set_nfet(1,5,1);
}
void move_motor_3_min(){
  set_nfet(1,6,1);
  set_nfet(1,5,0);
}
void move_motor_3_max(){
  set_nfet(1,6,0);
  set_nfet(1,5,1);
}

*/


void move_motors_zero(){
  set_nfet(1,8,0);//A1
  set_nfet(1,7,1);//A2
  set_nfet(1,6,1);//A3
  set_nfet(1,5,1);//A4
  
}
void move_motors_2(){
  set_nfet(1,8,1);
  set_nfet(1,7,0);
  set_nfet(1,6,1);
  set_nfet(1,5,1);
 
}
void move_motors_3(){
  set_nfet(1,8,1);
  set_nfet(1,7,1);
  set_nfet(1,6,0);
  set_nfet(1,5,1);
}
///////////////////////  ///////////////////////////   ///////////////////////////////
void body_move_left(){
  set_nfet(1,8,1);
  set_nfet(1,7,1);
  set_nfet(1,6,1);
  set_nfet(1,5,0);
  ////////min
}
void body_move_right(){
  set_nfet(1,8,1);
  set_nfet(1,7,1);
  set_nfet(1,6,0);
  set_nfet(1,5,0);
  ////////max
}
void body_move_centre(){
  set_nfet(1,8,1);
  set_nfet(1,7,0);
  set_nfet(1,6,0);
  set_nfet(1,5,0);
}

///////////////////////  ///////////////////////////   ///////////////////////////////
///============================================
// === ДВИЖЕНИЕ ШЕИ (ПОВОРОТ ГОЛОВЫ) === //
///============================================
void move_Central_head_position(){
  set_nfet(2,8,1);
  set_nfet(2,7,1);
  delay(wait_s);
}
void move_head_povorot_random(){
  set_nfet(2,8,0);
  set_nfet(2,7,0);
  delay(wait_s);
}
void move_right_head_position(){
  set_nfet(2,8,0);
  set_nfet(2,7,1);
  delay(wait_s);
}
void move_left_head_position(){
  set_nfet(2,8,1);
  set_nfet(2,7,0);
  delay(wait_s);
}
///============================================
// === ДВИЖЕНИЕ УЛЫБКИ === //
///============================================
void move_smile_close(){
  set_nfet(2,6,0);
  set_nfet(2,5,0);
  delay(wait_s);
}

void move_smile_open(){
  set_nfet(2,6,1);
  set_nfet(2,5,1);
  delay(wait_s);
}

void move_smile_middle1(){
  set_nfet(2,6,0);
  set_nfet(2,5,1);
  delay(wait_s);
}

void move_smile_middle2(){
  set_nfet(2,6,1);
  set_nfet(2,5,0);
  delay(wait_s);
}
///============================================
// === ДВИЖЕНИЕ ГЛАЗ === //
///============================================
void move_eyes_blink_off(){
  
  set_nfet(2,4,1);
  delay(wait_s);
}
void move_eyes_blink_on(){
  
  set_nfet(2,4,0);
  delay(wait_s);
}
///============================////
void move_eyes_random(){
 
  set_nfet(2,1,0);
  set_nfet(2,2,0);
  set_nfet(2,3,0);
/*
    eyes_random = 1;
    eyes_up_veko = 0;
    eyes_down_veko = 0;
    eyes_close = 0;
    eyes_to_left = 0;
    eyes_to_right = 0;
    eyes_to_center = 0;
    eyes_to_up = 0;
    */
  delay(wait_s);
}
///============================////
/*
void move_eyes_to_center_and_up_veko(){
  mosfet.digitalWrite(0, 0, LOW);
  mosfet.digitalWrite(0, 1, LOW);
  mosfet.digitalWrite(0, 2, HIGH);
  set_nfet(2,1,0);
  set_nfet(2,2,0);
  set_nfet(2,3,1);
 
     eyes_blink = 0;
     eyes_random = 0;
     eyes_up_veko = 1;
     eyes_down_veko = 0;
     eyes_close = 0;
     eyes_to_left = 0;
     eyes_to_right = 0;
     eyes_to_center = 1;
     eyes_to_up = 0;

  delay(wait_s);
}

///////////////  по причине,что совпадает с командой просто глаза прямо 
*/
///============================////
void move_eyes_to_center_and_down_veko(){

  set_nfet(2,1,1);
  set_nfet(2,2,1);
  set_nfet(2,3,0);
 /*
     eyes_blink = 0;
     eyes_random = 0;
     eyes_up_veko = 0;
     eyes_down_veko = 1;
     eyes_close = 0;
     eyes_to_left = 0;
     eyes_to_right = 0;
     eyes_to_center = 1;
     eyes_to_up = 0;
 */
 delay(wait_s);
}
///============================////
void move_eyes_to_center_and_eyes_close(){

  set_nfet(2,1,1);
  set_nfet(2,2,0);
  set_nfet(2,3,0);
 /*
     eyes_blink = 0;
     eyes_random = 0;
     eyes_up_veko = 0;
     eyes_down_veko = 0;
     eyes_close = 1;
     eyes_to_left = 0;
     eyes_to_right = 0;
     eyes_to_center = 1;
     eyes_to_up = 0;
 */
 delay(wait_s);
}
///============================////
void move_eyes_to_Center_and_eyes_close(){

  set_nfet(2,1,1);
  set_nfet(2,2,1);
  set_nfet(2,3,1);
 /*
     eyes_blink = 0;
     eyes_random = 0;
     eyes_up_veko = 0;
     eyes_down_veko = 0;
     eyes_close = 1;
     eyes_to_left = 0;
     eyes_to_right = 0;
     eyes_to_center = 1;
     eyes_to_up = 0;
 */
 delay(wait_s);
}
///============================////
void move_eyes_to_left(){

  set_nfet(2,1,1);
  set_nfet(2,2,0);
  set_nfet(2,3,0);
 /*
     eyes_random = 0;
     eyes_up_veko = 0;
     eyes_down_veko = 0;
     eyes_close = 0;
     eyes_to_left = 1;
     eyes_to_right = 0;
     eyes_to_center = 0;
     eyes_to_up = 0;
 */
 delay(wait_s);
}
///============================////
void move_eyes_to_right(){

  set_nfet(2,1,1);
  set_nfet(2,2,0);
  set_nfet(2,3,1);
 /*
     eyes_random = 0;
     eyes_up_veko = 0;
     eyes_down_veko = 0;
     eyes_close = 0;
     eyes_to_left = 0;
     eyes_to_right = 1;
     eyes_to_center = 0;
     eyes_to_up = 0;
 */
 delay(wait_s);
}
///============================////
void move_eyes_to_center(){

  set_nfet(2,1,0);
  set_nfet(2,2,0);
  set_nfet(2,3,1);
 /*
     eyes_random = 0;
     eyes_up_veko = 0;
     eyes_down_veko = 0;
     eyes_close = 0;
     eyes_to_left = 0;
     eyes_to_right = 0;
     eyes_to_center = 1;
     eyes_to_up = 0;
 */
 delay(wait_s);
}
///============================////
void move_eyes_to_center_and_eyes_to_up(){

  set_nfet(2,1,0);
  set_nfet(2,2,1);
  set_nfet(2,3,0);
 /*
     eyes_random = 0;
     eyes_up_veko = 0;
     eyes_down_veko = 0;
     eyes_close = 0;
     eyes_to_left = 0;
     eyes_to_right = 0;
     eyes_to_center = 1;
     eyes_to_up = 1;
     
 */
 delay(wait_s);
}
// ============== СКОРОСТЬ МОТОРА ============== //
void vacum_motor(int vacum_motor_speed){

    switch (vacum_motor_speed) {
    case 0: 
      set_nfet(1,4,0);
      set_nfet(1,3,0);
      set_nfet(1,2,0);
      set_nfet(1,1,0);
    break;
    case 1:
      set_nfet(1,4,0);
      set_nfet(1,3,1);
      set_nfet(1,2,1);
      set_nfet(1,1,1);   
      break;
    case 2:
      set_nfet(1,4,1);
      set_nfet(1,3,0);
      set_nfet(1,2,1);
      set_nfet(1,1,1); 
      break;
    case 3:
      set_nfet(1,4,1);
      set_nfet(1,3,1);
      set_nfet(1,2,0);
      set_nfet(1,1,1);
      break;
    case 4:
      set_nfet(1,4,1);
      set_nfet(1,3,1);
      set_nfet(1,2,1);
      set_nfet(1,1,0);
      break;
      ///////////////----------------/////////////////
     case 5:
      set_nfet(1,4,0);
      set_nfet(1,3,0);
      set_nfet(1,2,1);
      set_nfet(1,1,1);
      break;
     case 6:
      set_nfet(1,4,1);
      set_nfet(1,3,0);
      set_nfet(1,2,0);
      set_nfet(1,1,1);
      break;
     case 7:
      set_nfet(1,4,1);
      set_nfet(1,3,1);
      set_nfet(1,2,0);
      set_nfet(1,1,0);
      break;
     case 8:
      set_nfet(1,4,0);
      set_nfet(1,3,1);
      set_nfet(1,2,0);
      set_nfet(1,1,1);
      break;
     case 9:
      set_nfet(1,4,0);
      set_nfet(1,3,1);
      set_nfet(1,2,1);
      set_nfet(1,1,0);
      break;
     case 10:   
      set_nfet(1,4,1);
      set_nfet(1,3,0);
      set_nfet(1,2,1);
      set_nfet(1,1,0);  
      break;
      ////////////--------------------//////////////
     case 11: 
      set_nfet(1,4,0);
      set_nfet(1,3,0);
      set_nfet(1,2,0);
      set_nfet(1,1,1);   
      break;
     case 12:
      set_nfet(1,4,0);
      set_nfet(1,3,0);
      set_nfet(1,2,1);
      set_nfet(1,1,0);    
      break;
     case 13: 
      set_nfet(1,4,0);
      set_nfet(1,3,1);
      set_nfet(1,2,0);
      set_nfet(1,1,0);  
      break;
     case 14:
      set_nfet(1,4,1);
      set_nfet(1,3,0);
      set_nfet(1,2,0);
      set_nfet(1,1,0); 
      break;

     default :
       set_nfet(1,4,0);
       set_nfet(1,3,0);
       set_nfet(1,2,0);
       set_nfet(1,1,0);
     break; 

  delay(wait_s);
  }
 }

///// инициализация котроллера
void setup() {
   pinMode(A5,INPUT);
   pinMode(t_start , INPUT_PULLUP);

   
  L1.attach(11);
  L2.attach(10);
  L3.attach(9);
  L4.attach(8);
  oct.attach(7);
  Ld.attach(6);
  

 
  R1.attach(4);
  R2.attach(3);
  R3.attach(2);
  R4.attach(1);
  Rb.attach(0);
  
  headr.attach(6);
  headl.attach(5);
  
  headl.write(headl_start);
  headr.write(headr_start);
 // delay(2000);//задержка обязательна 
  
  L1.write(min_L1);
  L2.write(min_L2);
  L3.write(min_L3);
  L4.write(min_L4);
  oct.write(min_oct);
  Ld.write(min_Ld);

  R1.write(min_R1);
  R2.write(min_R2);
  R3.write(min_R3);
  R4.write(min_R4);
  Rb.write(min_Rb);
  

int L1_s = 0;// не нажаты//  L1.write(min_L1);
int L2_s = 0;// не нажаты//  L2.write(min_L2);
int L3_s = 0;// не нажаты//  L3.write(min_L3);
int L4_s = 0;// не нажаты//  L4.write(min_L4);
int oct_s = 0;// не нажаты// oct.write(min_oct);
int Ld_s = 0;// не нажаты//  Ld.write(min_Ld);

int R1_s = 0;// не нажаты// R1.write(min_R1);
int R2_s = 0;// не нажаты// R2.write(min_R2);
int R3_s = 0;// не нажаты// R3.write(min_R3);
int R4_s = 0;// не нажаты// R4.write(min_R4);
int Rb_s = 0;// не нажаты// Rb.write(min_Rb);


  nfet_init(); /// вызов функции инициализации модулей коючей от амперки
  Serial.begin(115200); /// порт для связи с компьютером
  Serial.setTimeout(5);
  Serial.println("Hello Computer"); ///обозначаем что прошивка запустилась
  
  Serial1.begin(9600);  // подключаем последовательный порт для связи с бт модулем
  Serial1.setTimeout(50);

  //Serial1.begin(38400);  // подключаем последовательный порт - другой бт модуль
  //Serial1.setTimeout(50);

  reset_bt_send_pause_timer(); ///сброс таймера для автопосылки байта на nxt 

  pinMode(LED_BUILTIN, OUTPUT); 
  bt_led =0;

  delay(1000);
  
}




/// пример приема и посылки по бт и одновременно работы модуля с ключами от амперки
/// работает совместно с тестовой программой на nxt потому что nxt должен каждую секунду слать число из nxt и менять его циклически последовательно от 1 до 253 

void loop() {
   move_eyes_random();
  move_eyes_blink_on();
  move_smile_close();
  vacum_motor(0);
  head_neck_random(); 

  while(digitalRead(t_start) == 1){
    //тут будет жест 
  }
  bt_send_command(1);

 servo_head_move(headr_pos_play, 50, 0);
 delay(500);
 servo_head_move(headr_pos_p, 50, 0);


while(analogRead(A5) < 900){   
   head_neck_random(); 
   delay(500);
   //Serial.println(analogRead(A7)); // выводим значение датчика на монитор
 }
 ////////////////////////////////////////======
//while (bt_recieve_byte_()!=52) {};

  //bt_send_command(52);
  /*
  bt_send_command(1);
  delay(2500);
  bt_send_command(2);
   delay(2500);
  bt_send_command(3);
  delay(2500);
  bt_send_command(4);
  */

  
//while (bt_recieve_byte_()!=5) {};

///////////////////////////////////////////================
move_right_head_position();
delay(3500);
move_Central_head_position();
 move_smile_close();
 
  
move_motors_zero();
 delay(3000);
 servo_head_move(headr_pos_play, 60, 0);
 vacum_motor(4);
 delay(1000);
 servo_head_move(headr_pos_play, 10,  0);
 delay(1000);
 servo_head_move(headr_pos_play+klapan, 5, 0);
 
 //настройка//
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 2000);
 servo_head_move(headr_pos_play-klapan_2, 5, 4000);
 C2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 2000);

 servo_head_move(headr_pos_play-klapan_2, 5, 4500);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///Go down, Moses///
  bt_send_command(2);
  vacum_motor(4);
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 G1(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d_2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);
 
  body_move_left();//////////////////////////////////////////////////////////////////
  
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d_2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);
 bt_send_command(2);
 
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);
 
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

bt_send_command(3);
 d_2(300);
 vacum_motor(2);
 servo_head_move(headr_pos_play-klapan_2,5, 0);
 d_2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 1500);
 
 bt_send_command(3);
  
 bt_send_command(2);
  vacum_motor(4);
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 G1(4500);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d_2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);
 

 
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d_2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);
 
 bt_send_command(2);
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);


 bt_send_command(3);
 d_2(300);
 vacum_motor(2);
 servo_head_move(headr_pos_play-klapan_2,5, 0);
 d_2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);
 
body_move_right();//////////////////////////////////////////////////////////////////
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 1500);

 bt_send_command(3);

 vacum_motor(4);
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(4500);
 servo_head_move(headr_pos_play+klapan_1, 5, 300);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 2100);
 bt_send_command(2);
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 F2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 300);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 F2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 2100);
 bt_send_command(3);
//body_move_right();//////////////////////////////////////////////////////////////////
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 G2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 1200);
 bt_send_command(2);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 G2(50);
 bt_send_command(2);
 

 
  vacum_motor(3);
  
 servo_head_move(headr_pos_play+klapan_1, 5, 900);
 
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 F2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 300);

 bt_send_command(3);
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 G2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 F2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);
 
 bt_send_command(3);
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d_2(50);
 
 servo_head_move(headr_pos_play+klapan_1, 5, 600);
 
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);
 bt_send_command(2);
 bt_send_command(3);
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d_2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 300);
 
body_move_left();//////////////////////////////////////////////////////////////////

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 2100);
 bt_send_command(2);
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d_2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 300);

 vacum_motor(2);
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 2100);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 G1(300);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);
 vacum_motor(3);
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 G1(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);
 body_move_centre();//////////////////////////////////////////////////////////////////  
  servo_head_move(headr_pos_play-klapan_2, 5, 0);
 H1(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 300);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 H1(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 1350);
 bt_send_command(4);

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
 servo_head_move(headr_pos_start, 60, 0); 
  vacum_motor(0); 
delay(2000);

// move_motor_finish();
// move_motors_2();
 move_motors_2();
 delay(300);
 //servo_head_move(headr_pos_start, 60, 0);
 C_2(50);
 //move_left_head_position();
 delay(3500);
// move_Central_head_position();
while (bt_recieve_byte_()!=52) {};
 
 body_move_left();
 delay(3000);
 move_smile_open();
 move_right_head_position();
 delay(3000);
 move_left_head_position();
  delay(3000);
 move_smile_close();

/*
   while ((bt_recieve()%3)!=0) { /// повторяем цикл пока число пришедшее от nxt делится на 3 с остатком
      if (bt_led==0)  { /// при этом пока принимаем числа делящиеся на 3 с остатком, выставляем на первом модуле ключей пин 5 с состяние такое же как светодиод показывающий прием байта по бт
        set_nfet(1, 5, 0);
      } else {
        set_nfet(1, 5, 1);
      }
    }
    ///если число пришедшее от nxt делится на 3 без остатка - цикл выше заканчивается и мы шлем свое число в nxt
     bt_send_command(a);
     a++;
     if (a>253) a=0;    
   /// потом возвращаемся в начало и снова ждем число от nxt которое делится на 3 без остатка
*/
}
