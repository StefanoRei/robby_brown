
#include "GyverTimer.h"
GTimer myTimer(MS);
#include <Multiservo.h>
#include <Servo.h>
#include "GyverTimer.h"
// библиотека для работы с модулями по интерфейсу SPI
#include <SPI.h>
// библиотека для работы со сборкой силовых ключей
#include <AmperkaFET.h>
// пин выбора сборки устройств на шине SPI
#define PIN_CS  A0
 // и количество устройств подключённых в цепочке
FET mosfet(PIN_CS, 2);
 
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


/*


/*
/*
///////////////////////////////ДЛЯ ФУНКЦИИ: servo_position/////////////////////////////
#define L1 1
#define L2 2
#define L3 3
#define L4 4
#define oct 5
#define Ld 6

#define R1 7
#define R2 8
#define R3 90
#define R4 10
#define Rb 11
//////////////////////////////////////////////////////////////////////////
*/
#define t_start 2  // кнопка старта для робота 
#define wait_s 10
////////////////////////////////// min = расслабленны/////////////////////////////////////////////////
#define min_L1 0
#define min_L2 0
#define min_L3 0
#define min_L4 40
#define min_oct 100
#define min_Ld 160 

#define min_R1 30
#define min_R2 0
#define min_R3 10
#define min_R4 180 
#define min_Rb 10 

#define max_L1 0 + 70
#define max_L2 0 + 70
#define max_L3 0 + 70
#define max_L4 40 + 70
#define max_oct 40
#define max_Ld  130

#define max_R1 30 + 90
#define max_R2 0 + 90
#define max_R3 10 + 90
#define max_R4 150 
#define max_Rb 30



int headr_start  = 110; // голова ровно 
int headl_start  = 61;
int random_neck_move_pause = 2500;

#define headr_pos_start 110

#define headr_pos_play 137 // прижимается к саксафону 
//#define headl_play 61-30

#define headr_pos_p 120 // рядом с саксафонон (типо клапан)
//#define headl_p 31 -  5
#define klapan_1 4
#define klapan_2 4
#define klapan 4





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


///=================================================================================================================================================================
///=================================================================================================================================================================
///=================================================================================================================================================================
///=================================================================================================================================================================
///=================================================================================================================================================================
///=================================================================================================================================================================
///========================================================НАЧАЛО ОПИСАНИЯ ФУНКЦИЙ ДЛЯ РАБОТЫ ОСНОВНОГО ЦИКЛА ПРОГРАММЫ ============================================
///=================================================================================================================================================================
///=================================================================================================================================================================
///=================================================================================================================================================================
///=================================================================================================================================================================
///=================================================================================================================================================================
///=================================================================================================================================================================
///=================================================================================================================================================================



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
/*
void polo_start_had(){
  for (int i = 1; i < 40; i++){
    
     headl.write(min_headl - i);
     headr.write(min_headr + i);
     delay(80);  
     head_r = min_headr + i;
     head_l = min_headl - i;
    }
   
 }
*/
///=================================================================================================================================================================
///=================================================================================================================================================================
///=================================================================================================================================================================
///===  ФУНКЦИИ ВСЕГО РОБОТА ( ПЕРЕДАЧА СИГНАЛОВ )  ===///
///=================================================================================================================================================================
///=================================================================================================================================================================
///=================================================================================================================================================================


///============================================
// === ДВИЖЕНИЕ САКСОФОНА === //
///============================================
void move_motors_zero(){
  mosfet.digitalWrite(1, 7, LOW);
  mosfet.digitalWrite(1, 6, HIGH);
  mosfet.digitalWrite(1, 5, HIGH);
  mosfet.digitalWrite(1, 4, HIGH);
  delay(wait_s);
}
void move_motors_2(){
  mosfet.digitalWrite(1, 7, HIGH);
  mosfet.digitalWrite(1, 6, LOW);
  mosfet.digitalWrite(1, 5, HIGH);
  mosfet.digitalWrite(1, 4, HIGH);
  delay(wait_s);
}
void move_motors_3(){
  mosfet.digitalWrite(1, 7, HIGH);
  mosfet.digitalWrite(1, 6, HIGH);
  mosfet.digitalWrite(1, 5, LOW);
  mosfet.digitalWrite(1, 4, HIGH);
  delay(wait_s);
}

///============================================
// === ДВИЖЕНИЕ ШЕИ (ПОВОРОТ ГОЛОВЫ) === //
///============================================
void move_Central_head_position(){
  mosfet.digitalWrite(0, 7, HIGH);
  mosfet.digitalWrite(0, 6, HIGH); 
  delay(wait_s);
}
void move_head_povorot_random(){
  mosfet.digitalWrite(0, 7, LOW);
  mosfet.digitalWrite(0, 6, LOW); 
  delay(wait_s);
}
void move_left_head_position(){
  mosfet.digitalWrite(0, 7, LOW);
  mosfet.digitalWrite(0, 6, HIGH); 
  delay(wait_s);
}
void move_right_head_position(){
  mosfet.digitalWrite(0, 7, HIGH);
  mosfet.digitalWrite(0, 6, LOW); 
  delay(wait_s);
}

///============================================
// === ДВИЖЕНИЕ УЛЫБКИ === //
///============================================
void move_smile_close(){
  mosfet.digitalWrite(0, 5, LOW);
  mosfet.digitalWrite(0, 4, LOW); 
  delay(wait_s);
}

void move_smile_open(){
  mosfet.digitalWrite(0, 5, HIGH);
  mosfet.digitalWrite(0, 4, HIGH); 
  delay(wait_s);
}

void move_smile_middle1(){
  mosfet.digitalWrite(0, 5, LOW);
  mosfet.digitalWrite(0, 4, HIGH); 
  delay(wait_s);
}

void move_smile_middle2(){
  mosfet.digitalWrite(0, 5, HIGH);
  mosfet.digitalWrite(0, 4, LOW); 
  delay(wait_s);
}
///============================================
// === ДВИЖЕНИЕ ГЛАЗ === //
///============================================
void move_eyes_blink_off(){
  mosfet.digitalWrite(0, 3, HIGH);
  delay(wait_s);
}
void move_eyes_blink_on(){
  mosfet.digitalWrite(0, 3, LOW);
  delay(wait_s);
}
///============================////
void move_eyes_random(){
  mosfet.digitalWrite(0, 0, LOW);
  mosfet.digitalWrite(0, 1, LOW);
  mosfet.digitalWrite(0, 2, LOW);
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
void move_eyes_to_center_and_up_veko(){
  mosfet.digitalWrite(0, 0, LOW);
  mosfet.digitalWrite(0, 1, LOW);
  mosfet.digitalWrite(0, 2, HIGH);
 /*
     eyes_blink = 0;
     eyes_random = 0;
     eyes_up_veko = 1;
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
void move_eyes_to_center_and_down_veko(){
  mosfet.digitalWrite(0, 0, HIGH);
  mosfet.digitalWrite(0, 1, HIGH);
  mosfet.digitalWrite(0, 2, LOW);
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
  mosfet.digitalWrite(0, 0, HIGH);
  mosfet.digitalWrite(0, 1, LOW);
  mosfet.digitalWrite(0, 2, LOW);
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
  mosfet.digitalWrite(0, 0, HIGH);
  mosfet.digitalWrite(0, 1, HIGH);
  mosfet.digitalWrite(0, 2, HIGH);
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
  mosfet.digitalWrite(0, 0, HIGH);
  mosfet.digitalWrite(0, 1, LOW);
  mosfet.digitalWrite(0, 2, LOW);
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
  mosfet.digitalWrite(0, 0, HIGH);
  mosfet.digitalWrite(0, 1, LOW);
  mosfet.digitalWrite(0, 2, HIGH);
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
  mosfet.digitalWrite(0, 0, LOW);
  mosfet.digitalWrite(0, 1, LOW);
  mosfet.digitalWrite(0, 2, HIGH);
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
  mosfet.digitalWrite(0, 0, LOW);
  mosfet.digitalWrite(0, 1, HIGH);
  mosfet.digitalWrite(0, 2, LOW);
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
      mosfet.digitalWrite(1, 3, LOW);
      mosfet.digitalWrite(1, 2, LOW);
      mosfet.digitalWrite(1, 1, LOW);
      mosfet.digitalWrite(1, 0, LOW); 
    break;
    case 1:
      mosfet.digitalWrite(1, 3, LOW);
      mosfet.digitalWrite(1, 2, HIGH);
      mosfet.digitalWrite(1, 1, HIGH);
      mosfet.digitalWrite(1, 0, HIGH);    
      break;
    case 2:
      mosfet.digitalWrite(1, 3, HIGH);
      mosfet.digitalWrite(1, 2, LOW);
      mosfet.digitalWrite(1, 1, HIGH);
      mosfet.digitalWrite(1, 0, HIGH); 
      break;
    case 3:
      mosfet.digitalWrite(1, 3, HIGH);
      mosfet.digitalWrite(1, 2, HIGH);
      mosfet.digitalWrite(1, 1, LOW);
      mosfet.digitalWrite(1, 0, HIGH); 
      break;
    case 4:
      mosfet.digitalWrite(1, 3, HIGH);
      mosfet.digitalWrite(1, 2, HIGH);
      mosfet.digitalWrite(1, 1, HIGH);
      mosfet.digitalWrite(1, 0, LOW); 
      break;
      ///////////////----------------/////////////////
     case 5:
      mosfet.digitalWrite(1, 3, LOW);
      mosfet.digitalWrite(1, 2, LOW);
      mosfet.digitalWrite(1, 1, HIGH);
      mosfet.digitalWrite(1, 0, HIGH); 
      break;
     case 6:
      mosfet.digitalWrite(1, 3, HIGH);
      mosfet.digitalWrite(1, 2, LOW);
      mosfet.digitalWrite(1, 1, LOW);
      mosfet.digitalWrite(1, 0, HIGH);
      break;
     case 7:
      mosfet.digitalWrite(1, 3, HIGH);
      mosfet.digitalWrite(1, 2, HIGH);
      mosfet.digitalWrite(1, 1, LOW);
      mosfet.digitalWrite(1, 0, LOW);
      break;
     case 8:
      mosfet.digitalWrite(1, 3, LOW);
      mosfet.digitalWrite(1, 2, HIGH);
      mosfet.digitalWrite(1, 1, LOW);
      mosfet.digitalWrite(1, 0, HIGH);
      break;
     case 9:
      mosfet.digitalWrite(1, 3, LOW);
      mosfet.digitalWrite(1, 2, HIGH);
      mosfet.digitalWrite(1, 1, HIGH);
      mosfet.digitalWrite(1, 0, LOW);
      break;
     case 10:
      mosfet.digitalWrite(1, 3, HIGH);
      mosfet.digitalWrite(1, 2, LOW);
      mosfet.digitalWrite(1, 1, HIGH);
      mosfet.digitalWrite(1, 0, LOW);     
      break;
      ////////////--------------------//////////////
     case 250:
      mosfet.digitalWrite(1, 3, LOW);
      mosfet.digitalWrite(1, 2, LOW);
      mosfet.digitalWrite(1, 1, LOW);
      mosfet.digitalWrite(1, 0, HIGH);      
      break;
     case 12:
      mosfet.digitalWrite(1, 3, LOW);
      mosfet.digitalWrite(1, 2, LOW);
      mosfet.digitalWrite(1, 1, HIGH);
      mosfet.digitalWrite(1, 0, LOW);      
      break;
     case 13:
      mosfet.digitalWrite(1, 3, LOW);
      mosfet.digitalWrite(1, 2, HIGH);
      mosfet.digitalWrite(1, 1, LOW);
      mosfet.digitalWrite(1, 0, LOW);     
      break;
     case 14:
      mosfet.digitalWrite(1, 3, HIGH);
      mosfet.digitalWrite(1, 2, LOW);
      mosfet.digitalWrite(1, 1, LOW);
      mosfet.digitalWrite(1, 0, LOW);    
      break;
//    case 100:
//      mosfet.digitalWrite(1, 3, LOW);
//      mosfet.digitalWrite(1, 2, LOW);
//      mosfet.digitalWrite(1, 1, LOW);
//      mosfet.digitalWrite(1, 0, LOW); 
     default :
       mosfet.digitalWrite(1, 0, LOW);
       mosfet.digitalWrite(1, 1, LOW);
       mosfet.digitalWrite(1, 2, LOW);
       mosfet.digitalWrite(1, 3, LOW); 
     break; 

  delay(wait_s);
  }
 }
unsigned long pause_timer1 = 0;
void reset_pause_timer1() {
    pause_timer1 = millis();   // current millis value
}
//=======================================================================================================
/// таймер для случайного поворота
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

///=================================================================================================================================================================
///===  НАЧАЛЬНыЕ НАСТРОЙКИ     ===
///=================================================================================================================================================================
void setup() {
  Serial.begin(9600);
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
 
  
   
 ////////////////////////
 

  delay(2000);//задержка обязательна 
 ///////////////////////////////////////////////// 
  
  mosfet.begin();
    
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


  pinMode(t_start , INPUT_PULLUP);
  
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

mosfet.digitalWrite(0, 0, LOW);
mosfet.digitalWrite(0, 1, LOW);
mosfet.digitalWrite(0, 2, LOW);
mosfet.digitalWrite(0, 3, LOW);
mosfet.digitalWrite(0, 4, LOW);
mosfet.digitalWrite(0, 5, LOW);
mosfet.digitalWrite(0, 6, LOW);
mosfet.digitalWrite(0, 7, LOW);
mosfet.digitalWrite(1, 0, LOW);
mosfet.digitalWrite(1, 1, LOW);
mosfet.digitalWrite(1, 2, LOW);
mosfet.digitalWrite(1, 3, LOW);
mosfet.digitalWrite(1, 4, LOW);
mosfet.digitalWrite(1, 5, LOW);
mosfet.digitalWrite(1, 6, LOW);
mosfet.digitalWrite(1, 7, LOW);

/*
 * 
 vacum_motor(1);
 delay(1000);
 vacum_motor(2);
 delay(1000);
 vacum_motor(3);
 delay(1000);
 vacum_motor(4);
 delay(1000);
 vacum_motor(5);
 delay(1000);
 vacum_motor(6);
 delay(1000);
 vacum_motor(7);
 delay(1000);
 vacum_motor(8);
 delay(1000);
 vacum_motor(9);
 delay(1000);
 vacum_motor(10);
 delay(1000);
 vacum_motor(11);
 delay(1000);
 vacum_motor(12);
 delay(1000);
 vacum_motor(13);
 delay(1000);
 vacum_motor(14);
*/

  
 
}

void loop() {
 move_eyes_random();
  move_eyes_blink_on();
  move_smile_close();
  vacum_motor(100);
  //mosfet.digitalWrite(0, 7, LOW);
  //while (true);
 while(digitalRead(t_start) == 1){
   head_neck_random();  
 }
 
 move_Central_head_position();
 move_smile_close();
 move_motors_zero();
 delay(3000);
 servo_head_move(headr_pos_play, 60, 0);

 vacum_motor(5);
 delay(1000);
 servo_head_move(headr_pos_play, 10,  0);
 delay(1000);
 servo_head_move(headr_pos_play+klapan, 5, 0);
  ///////////========================/////////////


//////Место для мелодии//////

///Go down, Moses///
  vacum_motor(4);
  delay(5000);
  
/*
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 G1(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d_2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d_2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);
 
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);
 
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 d_2(300);
 vacum_motor(2);
 servo_head_move(headr_pos_play-klapan_2,5, 0);
 d_2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 1500);

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
 
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 d_2(300);
 vacum_motor(2);
 servo_head_move(headr_pos_play-klapan_2,5, 0);
 d_2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 1500);



 vacum_motor(4);
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(4500);
 servo_head_move(headr_pos_play+klapan_1, 5, 300);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 2100);
 
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 F2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 300);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 F2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 2100);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 G2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 1200);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 G2(50);
 
  vacum_motor(3);
  
 servo_head_move(headr_pos_play+klapan_1, 5, 900);
 
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 F2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 300);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 G2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 F2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 vacum_motor(3);
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d_2(50);
 
 servo_head_move(headr_pos_play+klapan_1, 5, 600);
 
 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 d_2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 300);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 2100);

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

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 G1(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

  servo_head_move(headr_pos_play-klapan_2, 5, 0);
 H1(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 300);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 H1(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 600);

 servo_head_move(headr_pos_play-klapan_2, 5, 0);
 C2(50);
 servo_head_move(headr_pos_play+klapan_1, 5, 1350);

//////Конец места для мелодии//////
*/


 ///////////========================/////////////
delay(1500);
vacum_motor(0);

move_motors_3();
C_2(100);
delay(400);
servo_head_move(headr_pos_start, 60,  0);
delay(500);
delay(2000);

mosfet.digitalWrite(0, 0, LOW);
mosfet.digitalWrite(0, 1, LOW);
mosfet.digitalWrite(0, 2, LOW);
mosfet.digitalWrite(0, 3, LOW);
mosfet.digitalWrite(0, 4, LOW);
mosfet.digitalWrite(0, 5, LOW);
mosfet.digitalWrite(0, 6, LOW);
mosfet.digitalWrite(0, 7, LOW);
mosfet.digitalWrite(1, 0, LOW);
mosfet.digitalWrite(1, 1, LOW);
mosfet.digitalWrite(1, 2, LOW);
mosfet.digitalWrite(1, 3, LOW);
mosfet.digitalWrite(1, 4, LOW);
mosfet.digitalWrite(1, 5, LOW);
mosfet.digitalWrite(1, 6, LOW);
mosfet.digitalWrite(1, 7, LOW);
delay(1000);

mosfet.digitalWrite(0, 0, LOW);
mosfet.digitalWrite(0, 1, LOW);
mosfet.digitalWrite(0, 2, LOW);
mosfet.digitalWrite(0, 3, LOW);
mosfet.digitalWrite(0, 4, LOW);
mosfet.digitalWrite(0, 5, LOW);
mosfet.digitalWrite(0, 6, HIGH);
mosfet.digitalWrite(0, 7, LOW);
mosfet.digitalWrite(1, 0, LOW);
mosfet.digitalWrite(1, 1, LOW);
mosfet.digitalWrite(1, 2, LOW);
mosfet.digitalWrite(1, 3, LOW);
mosfet.digitalWrite(1, 4, HIGH);
mosfet.digitalWrite(1, 5, LOW);
mosfet.digitalWrite(1, 6, HIGH);
mosfet.digitalWrite(1, 7, HIGH);

delay(5000);
/*
mosfet.digitalWrite(0, 0, HIGH);
mosfet.digitalWrite(1, 0, HIGH);
delay(1000);
mosfet.digitalWrite(0, 0, LOW);
mosfet.digitalWrite(1, 0, LOW);
delay(1000);
mosfet.digitalWrite(0, 1, HIGH);
mosfet.digitalWrite(1, 1, HIGH);
delay(1000);
mosfet.digitalWrite(0, 1, LOW);
mosfet.digitalWrite(1, 1, LOW);
delay(1000);
mosfet.digitalWrite(0, 2, HIGH);
mosfet.digitalWrite(1, 2, HIGH);
delay(1000);
mosfet.digitalWrite(0, 2, LOW);
mosfet.digitalWrite(1, 2, LOW);
delay(1000);
mosfet.digitalWrite(0, 3, HIGH);
mosfet.digitalWrite(1, 3, HIGH);
delay(1000);
mosfet.digitalWrite(0, 3, LOW);
mosfet.digitalWrite(1, 3, LOW);
delay(1000);
mosfet.digitalWrite(0, 4, HIGH);
mosfet.digitalWrite(1, 4, HIGH);
delay(1000);
mosfet.digitalWrite(0, 4, LOW);
mosfet.digitalWrite(1, 4, LOW);
delay(1000);
mosfet.digitalWrite(0, 5, HIGH);
mosfet.digitalWrite(1, 5, HIGH);
delay(1000);
mosfet.digitalWrite(0, 5, LOW);
mosfet.digitalWrite(1, 5, LOW);
delay(1000);
mosfet.digitalWrite(0, 6, HIGH);
mosfet.digitalWrite(1, 6, HIGH);
delay(1000);
mosfet.digitalWrite(0, 6, LOW);
mosfet.digitalWrite(1, 6, LOW);
delay(1000);
mosfet.digitalWrite(0, 7, HIGH);
mosfet.digitalWrite(1, 7, HIGH);
delay(1000);
mosfet.digitalWrite(0, 7, LOW);
mosfet.digitalWrite(1, 7, LOW);
delay(1000);

mosfet.digitalWrite(0, 0, LOW);
mosfet.digitalWrite(0, 1, LOW);
mosfet.digitalWrite(0, 2, LOW);
mosfet.digitalWrite(0, 3, LOW);
mosfet.digitalWrite(0, 4, LOW);
mosfet.digitalWrite(0, 5, LOW);
mosfet.digitalWrite(0, 6, LOW);
mosfet.digitalWrite(0, 7, LOW);
mosfet.digitalWrite(1, 0, LOW);
mosfet.digitalWrite(1, 1, LOW);
mosfet.digitalWrite(1, 2, LOW);
mosfet.digitalWrite(1, 3, LOW);
mosfet.digitalWrite(1, 4, LOW);
mosfet.digitalWrite(1, 5, LOW);
mosfet.digitalWrite(1, 6, LOW);
mosfet.digitalWrite(1, 7, LOW);


mosfet.digitalWrite(0, 0, HIGH);
delay(1000);
mosfet.digitalWrite(0, 0, LOW);
delay(1000);
mosfet.digitalWrite(0, 1, HIGH);
delay(1000);
mosfet.digitalWrite(0, 1, LOW);
delay(1000);
mosfet.digitalWrite(0, 2, HIGH);
delay(1000);
mosfet.digitalWrite(0, 2, LOW);
delay(1000);
mosfet.digitalWrite(0, 3, HIGH);
delay(1000);
mosfet.digitalWrite(0, 3, LOW);
delay(1000);
mosfet.digitalWrite(0, 4, HIGH);
delay(1000);
mosfet.digitalWrite(0, 4, LOW);
delay(1000);
mosfet.digitalWrite(0, 5, HIGH);
delay(1000);
mosfet.digitalWrite(0, 5, LOW);
delay(1000);
mosfet.digitalWrite(0, 6, HIGH);
delay(1000);
mosfet.digitalWrite(0, 6, LOW);
delay(1000);
mosfet.digitalWrite(0, 7, HIGH);
delay(1000);
mosfet.digitalWrite(0, 7, LOW);
delay(1000);



mosfet.digitalWrite(1, 0, HIGH);
delay(1000);
mosfet.digitalWrite(1, 0, LOW);
delay(1000);
mosfet.digitalWrite(1, 1, HIGH);
delay(1000);
mosfet.digitalWrite(1, 1, LOW);
delay(1000);
mosfet.digitalWrite(1, 2, HIGH);
delay(1000);
mosfet.digitalWrite(1, 2, LOW);
delay(1000);
mosfet.digitalWrite(1, 3, HIGH);
delay(1000);
mosfet.digitalWrite(1, 3, LOW);
delay(1000);
mosfet.digitalWrite(1, 4, HIGH);
delay(1000);
mosfet.digitalWrite(1, 4, LOW);
delay(1000);
mosfet.digitalWrite(1, 5, HIGH);
delay(1000);
mosfet.digitalWrite(1, 5, LOW);
delay(1000);
mosfet.digitalWrite(1, 6, HIGH);
delay(1000);
mosfet.digitalWrite(1, 6, LOW);
delay(1000);
mosfet.digitalWrite(1, 7, HIGH);
delay(1000);
mosfet.digitalWrite(1, 7, LOW);
delay(1000);

mosfet.digitalWrite(0, 0, LOW);
mosfet.digitalWrite(0, 1, LOW);
mosfet.digitalWrite(0, 2, LOW);
mosfet.digitalWrite(0, 3, LOW);
mosfet.digitalWrite(0, 4, LOW);
mosfet.digitalWrite(0, 5, LOW);
mosfet.digitalWrite(0, 6, LOW);
mosfet.digitalWrite(0, 7, LOW);
*/
//move_right_head_position(){
///move_Central_head_position();
//move_head_povorot_random();
//move_random_head_position();
//move_left_head_position();

//delay(2000);
 
//move_smile_open();

//delay(3000);

//move_smile_close();

//vacum_motor(0);

while(true){};
 ///////////========================/////////////
 /*
E1(1600);
 F1(800);
 E1(800);
 a1(1600);
 H1(800);
 a1(800);
 C2(3200);
 E1(1600);
 a1(800);
 C2(800);
 E2(1600);
 F2(800);
 E2(800);
 H1(3200);
 E1(1600);
 F2(800);
 E1(800);
 G_1(2400);
 a1(800);
 H1(3200);
 E1(1600);
 G_1(800);
 H1(800);
 d2(1600);
 F2(800);
 E2(800);
 a1(3200);
 
 E2(1600);
 d2(1600);
 C2(1600);
 d2(800);
 E2(800);
 F2(3200);
 
 E2(200);
 F2(1400);
 E2(1600);
 d2(1600);
 C2(800);
 d2(800);
 E2(3200);

 F2(200);
 E2(1400);
 d2(1600);
 C2(1600);
 H1(800);
 C2(800);
 d2(3200);

 E2(200);
 d2(1400);
 C2(1600);
 H1(1600);
 C2(800);
 H1(800);
 a1(3200);
 */
  /*
 

  
  /*
  ///10**6 АЛЫХ РОЗ///
 E1(1600);
 F1(800);
 E1(800);
 a1(1600);
 H1(800);
 a1(800);
 C2(3200);
 E1(1600);
 a1(800);
 C2(800);
 E2(1600);
 F2(800);
 E2(800);
 H1(3200);
 E1(1600);
 F2(800);
 E1(800);
 G_1(2400);
 a1(800);
 H1(3200);
 E1(1600);
 G_1(800);
 H1(800);
 d2(1600);
 F2(800);
 E2(800);
 a1(3200);
 
 E2(1600);
 d2(1600);
 C2(1600);
 d2(800);
 E2(800);
 F2(3200);
 
 E2(200);
 F2(1400);
 E2(1600);
 d2(1600);
 C2(800);
 d2(800);
 E2(3200);

 F2(200);
 E2(1400);
 d2(1600);
 C2(1600);
 H1(800);
 C2(800);
 d2(3200);

 E2(200);
 d2(1400);
 C2(1600);
 H1(1600);
 C2(800);
 H1(800);
 a1(3200);
 */
  /*
//Ornithology//
H1(100);
E2(200);
F_2(100);
G_2(200);
a2(100);
H2(200);
G_2(100);
a2(200);
H2(100);
G_2(200);
E2(900);
///zero(800);///
H1(100);
E2(200);
F_2(100);
G2(200);
a2(100);
H2(200);
C3(300);
d3(300);
E2(100);
F_2(200);
G2(600);
H2(100);
a2(200);
F_2(300);
d2(100);
G2(200);
F2(100);
F_2(200);
d2(1200);
///zero(1100);///
F2(400);
E2(200);
d2(100);
C_2(200);
E2(100);
d2(200);
a1(100);
d2(300);
C2(200);
H1(600);
///zero(500);///
a_2(400);
a2(200);
G2(100);
F_2(200);
a2(100);
G2(200);
E2(100);
F_2(300);
E2(200);
d_2(600);
///zero(500);///
H1(100);
F_2(200);
E2(100);
H1(200);
G1(100);
d2(200);
H1(100);
C2(200);
H1(300);
F_2(100);
d_2(100);
E2(100);
F_2(100);
d_2(100);
E2(100);
F_2(100);
d_2(100);
E2(100);
F_2(100);
H2(6600);
///zero(6300);///
*/

  
 
 
}
