#include <Multiservo.h>
//#include <Servo.h>

#define Input_pin1 2 
#define Input_pin2 3
#define Input_pin3 4
#define Input_pin4 5
#define Input_pin5 6
#define Input_pin6 7
#define Input_pin7 8
#define Input_pin8 9

#define number_read_iterations 3 /// количество поледовательных чтений входов для вычисления среднего
#define read_state_time 1 //пауза между чтениями входов в мс

///входы у нас pullup поэтому по умолчанию значения на входах=1
byte input_state_pin1 = 1 ;
byte input_state_pin2 = 1 ;
byte input_state_pin3 = 1 ;
byte input_state_pin4 = 1 ;
byte input_state_pin5 = 1 ;
byte input_state_pin6 = 1 ;
byte input_state_pin7 = 1 ;
byte input_state_pin8 = 1 ;

byte drive_via_comport = 0; /// если =1 то функция чтения входов не работает, управление осуществляется командами через
                           /// компорт 


// Задаём количество сервоприводов
constexpr uint8_t MULTI_SERVO_COUNT = 10; /// нужно 8 - 2 запасные на будущее

// Создаём массив объектов для работы с сервомоторами
Multiservo multiservo[MULTI_SERVO_COUNT];

///Соответсвие номеров сервы их названию
byte Smile_servo = 0;
byte Head_Povorot_servo = 1;
byte Right_eye_x = 2;
byte Right_eye_y = 3;
byte Left_eye_x = 4;
byte Left_eye_y = 5;
byte veko_up = 6;
byte veko_down = 7;


// Переменные для хранения текущей позиции каждого сервомотора
// установка значений в эти массивы в функции setup
int current_servo_position[MULTI_SERVO_COUNT]; /// текущее положение сервы
int setpoint_servo_position[MULTI_SERVO_COUNT]; /// целевое значение положения куда повернуться серве
int speed_servo_rotating[MULTI_SERVO_COUNT]; /// пауза между поворотами сервы на 1 градус в мс
int max_servo_position[MULTI_SERVO_COUNT]; //// максимально возможный угол поворота для каждой сервы
int min_servo_position[MULTI_SERVO_COUNT]; //// минимально возможный угол поворота для каждой сервы 
int initial_servo_position[MULTI_SERVO_COUNT]; //// начальное положение сервы при старте программы контроллера


////  ============================================================
//// начальные и граничные значения для серв и скорости их вращения
//// здесь можно править вручную чтобы поменялись начальные значения при старте программы

//// вращение головы
int Left_head_position = 60;
int Right_head_position = 125;
int Central_head_position = 88; 
int random_head_move_pause = 7000; /// пауза между поворотами головы в случайом режиме в мс
int Head_speed_=40; /// пауза между поворотами сервы на 1 градус в мс

//// улыбка
int smile_close = 100;
int smile_open = 53;
int smile_middle1 = 87;
int smile_middle2 = 75;
int smile_speed_ = 40; /// пауза между поворотами сервы на 1 градус в мс

//// глаза
int eye_r_x_zero=97;
int eye_l_x_zero=85;
int eye_r_y_zero=110;
int eye_l_y_zero=72;
int eye_v_u_zero=80;
int eye_v_d_zero=100;//106

int eye_r_x_max=100;  // в правую сторону 
int eye_r_x_min=70 ; // в левую сторону 

int eye_r_y_max=110;  //
int eye_r_y_min=70;  //  

int eye_l_y_max=110;  //
int eye_l_y_min=70;  // 

int eye_l_x_max=110;  // в правую сторону 
int eye_l_x_min=80;  // в левую сторону 

int eye_v_u_max=80;  // веко  - октрыто
int eye_v_u_min=55;  // закрыто
int eye_v_u_middle1=40;  // полузаурыто 1   76
int eye_v_u_middle2=40;  // полузаурыто 1   66

int eye_v_d_max=80;  // веко открыто
int eye_v_d_min=80;  // закрыто  //80
int eye_v_d_middle=83; // полузакрыто //83

int eye_veko_speed=15;  // скорость перемещение серв век - пауза между поворотами сервы на 1 градус в мс
int eye_x_speed=50;  // скорость перемещение серв глаз в плоскости х - пауза между поворотами сервы на 1 градус в мс
int eye_y_speed=50;  // скорость перемещение серв глаз в плоскости у - пауза между поворотами сервы на 1 градус в мс
int eye_blink_pause = 3000;  // пауза сколько глаза закрытые между морганиями в мс
int eye_blink_pause1 = 5000; /// пауза сколько глаза открытые между движением век при моргании в мс
int eye_random_move_pause = 2500;  //пауза между движением глаз в рандоме в мс


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



///=================================================================================================================================================================
///===  ФУНКЦИЯ установки крайних и начальных значений в массивы для серв вызывается из setup ===
///=================================================================================================================================================================
void init_servo_min_max() {
  
speed_servo_rotating[Smile_servo]=smile_speed_;
if (smile_close <= smile_open) {
  max_servo_position[Smile_servo] = smile_open;
  min_servo_position[Smile_servo] = smile_close;
} else {
  max_servo_position[Smile_servo] = smile_close;
  min_servo_position[Smile_servo] = smile_open;
}
initial_servo_position[Smile_servo] = smile_close;


speed_servo_rotating[Head_Povorot_servo]=Head_speed_;
if (Left_head_position <= Right_head_position) {
  max_servo_position[Head_Povorot_servo] = Right_head_position;
  min_servo_position[Head_Povorot_servo] = Left_head_position;
} else {
  max_servo_position[Head_Povorot_servo] = Left_head_position;
  min_servo_position[Head_Povorot_servo] = Right_head_position;
}
initial_servo_position[Head_Povorot_servo] = Central_head_position;


speed_servo_rotating[veko_up]=eye_veko_speed;
if (eye_v_u_min <= eye_v_u_max) {
  max_servo_position[veko_up] = eye_v_u_max;
  min_servo_position[veko_up] = eye_v_u_min;
} else {
  max_servo_position[veko_up] = eye_v_u_min;
  min_servo_position[veko_up] = eye_v_u_max;
}
initial_servo_position[veko_up] = eye_v_u_zero;


speed_servo_rotating[veko_down]=eye_veko_speed;
if (eye_v_d_min <= eye_v_d_max) {
  max_servo_position[veko_down] = eye_v_d_max;
  min_servo_position[veko_down] = eye_v_d_min;
} else {
  max_servo_position[veko_down] = eye_v_d_min;
  min_servo_position[veko_down] = eye_v_d_max;
}
initial_servo_position[veko_down] = eye_v_d_zero;


speed_servo_rotating[Right_eye_x]=eye_x_speed;
if (eye_r_x_min <= eye_r_x_max) {
  max_servo_position[Right_eye_x] = eye_r_x_max;
  min_servo_position[Right_eye_x] = eye_r_x_min;
} else {
  max_servo_position[Right_eye_x] = eye_r_x_min;
  min_servo_position[Right_eye_x] = eye_r_x_max;
}
initial_servo_position[Right_eye_x] = eye_r_x_zero;


speed_servo_rotating[Left_eye_x]=eye_x_speed;
if (eye_l_x_min <= eye_l_x_max) {
  max_servo_position[Left_eye_x] = eye_l_x_max;
  min_servo_position[Left_eye_x] = eye_l_x_min;
} else {
  max_servo_position[Left_eye_x] = eye_l_x_min;
  min_servo_position[Left_eye_x] = eye_l_x_max;
}
initial_servo_position[Left_eye_x] = eye_l_x_zero;


speed_servo_rotating[Right_eye_y]=eye_y_speed;
if (eye_r_y_min <= eye_r_y_max) {
  max_servo_position[Right_eye_y] = eye_r_y_max;
  min_servo_position[Right_eye_y] = eye_r_y_min;
} else {
  max_servo_position[Right_eye_y] = eye_r_y_min;
  min_servo_position[Right_eye_y] = eye_r_y_max;
}
initial_servo_position[Right_eye_y] = eye_r_y_zero;


speed_servo_rotating[Left_eye_y]=eye_y_speed;
if (eye_l_y_min <= eye_l_y_max) {
  max_servo_position[Left_eye_y] = eye_l_y_max;
  min_servo_position[Left_eye_y] = eye_l_y_min;
} else {
  max_servo_position[Left_eye_y] = eye_l_y_min;
  min_servo_position[Left_eye_y] = eye_l_y_max;
}
initial_servo_position[Left_eye_y] = eye_l_y_zero;

  
}


///=================================================================================================================================================================
///===  ФУНКЦИЯ физической установки серв в начальные значения при старте программы вызывается из setup ===
///=================================================================================================================================================================
void init_servo_positions() {

///smile servo
multiservo[Smile_servo].write(initial_servo_position[Smile_servo]);
current_servo_position[Smile_servo] = initial_servo_position[Smile_servo];
setpoint_servo_position[Smile_servo] = initial_servo_position[Smile_servo];
delay(15);

///Head povorot servo
multiservo[Head_Povorot_servo].write(initial_servo_position[Head_Povorot_servo]);
current_servo_position[Head_Povorot_servo] = initial_servo_position[Head_Povorot_servo];
setpoint_servo_position[Head_Povorot_servo] = initial_servo_position[Head_Povorot_servo];
delay(15);

///veko up servo
multiservo[veko_up].write(initial_servo_position[veko_up]);
current_servo_position[veko_up] = initial_servo_position[veko_up];
setpoint_servo_position[veko_up] = initial_servo_position[veko_up];
delay(15);

///veko up servo
multiservo[veko_down].write(initial_servo_position[veko_down]);
current_servo_position[veko_down] = initial_servo_position[veko_down];
setpoint_servo_position[veko_down] = initial_servo_position[veko_down];
delay(15);
  
///Right_eye_x servo
multiservo[Right_eye_x].write(initial_servo_position[Right_eye_x]);
current_servo_position[Right_eye_x] = initial_servo_position[Right_eye_x];
setpoint_servo_position[Right_eye_x] = initial_servo_position[Right_eye_x];
delay(15);

///Right_eye_y servo
multiservo[Right_eye_y].write(initial_servo_position[Right_eye_y]);
current_servo_position[Right_eye_y] = initial_servo_position[Right_eye_y];
setpoint_servo_position[Right_eye_y] = initial_servo_position[Right_eye_y];
delay(15);

///Left_eye_x servo
multiservo[Left_eye_x].write(initial_servo_position[Left_eye_x]);
current_servo_position[Left_eye_x] = initial_servo_position[Left_eye_x];
setpoint_servo_position[Left_eye_x] = initial_servo_position[Left_eye_x];
delay(15);

///Left_eye_y servo
multiservo[Left_eye_y].write(initial_servo_position[Left_eye_y]);
current_servo_position[Left_eye_y] = initial_servo_position[Left_eye_y];
setpoint_servo_position[Left_eye_y] = initial_servo_position[Left_eye_y];

delay(2000); // time to servo moving
}



///=================================================================================================================================================================
///===  ФУНКЦИИ ПОВОРОТА ГОЛОВЫ     ===
///=================================================================================================================================================================

unsigned long pause_timer = 0;
/// =======================================================================================================
/// таймер для регулировки скорости поворота
void reset_pause_timer() {
    pause_timer = millis();   // current millis value
}
/// 
//=======================================================================================================
/// таймер для регулировки скорости поворота
byte is_pause_timer(uint16_t p_t) {
  if (millis() - pause_timer >= p_t) 
  {
   return 1;
  }
  else 
  {
   return 0;
  }
}
//=======================================================================================================
// Функция поворота головы
/// поворачивает от текущего положения current_servo_position[Head_Povorot_servo] в положение setpoint_servo_position[Head_Povorot_servo] со скоростью speed_servo_rotating[Head_Povorot_servo] 
/// после достижения целевого положения ничего не делает
/// встроена проверка возможных границ поворота
/// эта функция вызывается в главном цикле непрерывно всегда, управляется изменением цифр в соответсвующих массивах (setpoint_servo_position и speed_servo_rotating).
void head_povorot_loop(){
   if (is_pause_timer(speed_servo_rotating[Head_Povorot_servo])==1) {
     reset_pause_timer();   
     if (current_servo_position[Head_Povorot_servo] < setpoint_servo_position[Head_Povorot_servo]) {
         if ((current_servo_position[Head_Povorot_servo] + 1) <= max_servo_position[Head_Povorot_servo]) {
           current_servo_position[Head_Povorot_servo] = current_servo_position[Head_Povorot_servo] + 1;
           multiservo[Head_Povorot_servo].write(current_servo_position[Head_Povorot_servo]);
           delayMicroseconds(1000);
           //delay(1); /// pause for servo set
         }
     } else {
         if (current_servo_position[Head_Povorot_servo] > setpoint_servo_position[Head_Povorot_servo]) {
            if ((current_servo_position[Head_Povorot_servo] - 1) >= min_servo_position[Head_Povorot_servo]) {
               current_servo_position[Head_Povorot_servo] = current_servo_position[Head_Povorot_servo] - 1;
               multiservo[Head_Povorot_servo].write(current_servo_position[Head_Povorot_servo]);
               delay(1); /// pause for servo set
            }
         }    
     }
   }
}
//=======================================================================================================
// Функция поворота головы - обертка для управления значениями setpoint_servo_position[Head_Povorot_servo] и speed_servo_rotating[Head_Povorot_servo] 
/// вызывается из основной программы когда нужно повернуть куда-то голову в конкретное положение с конкретной скоростью
/// функция не блокирующая, она только задает целевые значения, поворот начинается сразу в другой функции работающей непрерывно
/// встроена проверка на допустимые значения
/// move_speed - время в мс между поворотом сервы на 1 градус.
void head_povorot_set(int set_pos, int move_speed){

 if (set_pos > max_servo_position[Head_Povorot_servo]) set_pos = max_servo_position[Head_Povorot_servo];
 if (set_pos < min_servo_position[Head_Povorot_servo]) set_pos = min_servo_position[Head_Povorot_servo];

 if (move_speed < 0) move_speed = 0;  
 if (move_speed > 10000) move_speed = 10000;  

 setpoint_servo_position[Head_Povorot_servo] = set_pos;
 speed_servo_rotating[Head_Povorot_servo] = move_speed; 
}
/// 
//=======================================================================================================
/// таймер для случайного поворота
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
//=======================================================================================================
// Функция случайного поворота головы
/// вызывается только в соответсвующем состоянии головы
/// изменяет setpoint_servo_position для головы
void head_povorot_random(){
     if (is_pause_timer1(random_head_move_pause) == 1) {
             reset_pause_timer1();         
             head_povorot_set(10*random(0, 10) + 53, speed_servo_rotating[Head_Povorot_servo]);
      }
         
}

//=======================================================================================================
// Функция переключения режимов поворота в зависимости от входных команд 
//// 
void Set_head_rotate(){
   if((input_state_pin1 == 0) && (input_state_pin2 == 0)){
     head_povorot_set(Central_head_position, speed_servo_rotating[Head_Povorot_servo]);
   }
   
   if((input_state_pin1 == 1) && (input_state_pin2 == 1)){
    head_povorot_random();
   }
   
   if((input_state_pin1 == 1) && (input_state_pin2 == 0)){
     head_povorot_set(Left_head_position, speed_servo_rotating[Head_Povorot_servo]);
   }

   if((input_state_pin1 == 0) && (input_state_pin2 == 1)){
     head_povorot_set(Right_head_position, speed_servo_rotating[Head_Povorot_servo]);
   }
}


///=================================================================================================================================================================
///===  ФУНКЦИИ УЛЫБКИ      ===
///=================================================================================================================================================================
///===  Таймер улыбки      ===
unsigned long timer_smile = 0;
void reset_timer_smile() {
    timer_smile = millis();   // current millis value
}
///===  Таймеры улыбки      ===
byte is_timer_smile(uint16_t p_t) {
  if (millis() - timer_smile >= p_t) 
  {
   return 1;
  }
  else 
  {
   return 0;
  }
}
//=======================================================================================================
// Функция управления сервой улыбки
/// поворачивает от текущего положения current_servo_position[Smile_servo] в положение setpoint_servo_position[Smile_servo] со скоростью speed_servo_rotating[Smile_servo] 
/// после достижения целевого положения ничего не делает
/// встроена проверка возможных границ поворота
/// эта функция вызывается в главном цикле непрерывно всегда, управляется изменением цифр в соответсвующих массивах (setpoint_servo_position и speed_servo_rotating).

void smile_loop(){ /// 
   if (is_timer_smile(speed_servo_rotating[Smile_servo])==1) {
     reset_timer_smile();   
     if (current_servo_position[Smile_servo] < setpoint_servo_position[Smile_servo]) {
       if ((current_servo_position[Smile_servo] + 1) <= max_servo_position[Smile_servo]){
          current_servo_position[Smile_servo] = current_servo_position[Smile_servo] + 1;
          multiservo[Smile_servo].write(current_servo_position[Smile_servo]);
          delay(1); /// pause for servo set
       }   
     } else {
       if (current_servo_position[Smile_servo] > setpoint_servo_position[Smile_servo]) {
          if ((current_servo_position[Smile_servo] - 1) >= min_servo_position[Smile_servo]) {
             current_servo_position[Smile_servo] = current_servo_position[Smile_servo] - 1;
             multiservo[Smile_servo].write(current_servo_position[Smile_servo]);
             delay(1); /// pause for servo set
          }   
       }    
     }
   }
}

//=======================================================================================================
// Функция записи значения куда двигать серву улыбки и с какой скоростью
// в массивы для реального ее движения
// Реализована проверка возможных значений
void Set_servo_smile(int set_pos, int move_speed){
 
 if (set_pos > max_servo_position[Smile_servo]) set_pos = max_servo_position[Smile_servo];
 if (set_pos < min_servo_position[Smile_servo]) set_pos = min_servo_position[Smile_servo];

 if (move_speed < 0) move_speed = 0;  
 if (move_speed > 10000) move_speed = 10000;  

 setpoint_servo_position[Smile_servo] = set_pos;
 speed_servo_rotating[Smile_servo] = move_speed; 
}

//=======================================================================================================
// Функция переключения режимов улыбки в зависимости от входных команд 
// вызывается постоянно в цикле
void Set_smile(){
   if((input_state_pin3 == 1) && (input_state_pin4 == 1)){
     Set_servo_smile(smile_close, speed_servo_rotating[Smile_servo]);
   }
   
   if((input_state_pin3 == 0) && (input_state_pin4 == 0)){
     Set_servo_smile(smile_open, speed_servo_rotating[Smile_servo]);
   }
   
   if((input_state_pin3 == 1) && (input_state_pin4 == 0)){
     Set_servo_smile(smile_middle1, speed_servo_rotating[Smile_servo]);
   }

   if((input_state_pin3 == 0) && (input_state_pin4 == 1)){
     Set_servo_smile(smile_middle2, speed_servo_rotating[Smile_servo]);
   }
}

///=================================================================================================================================================================
///===  ФУНКЦИИ управления глазами      ===
///=================================================================================================================================================================
/// =======================================================================================================
/// таймер для глаз серва 1
unsigned long eyes_timer1 = 0;
void reset_eyes_timer1() {
    eyes_timer1 = millis();   // current millis value
}
/// 
//=======================================================================================================
/// таймер для глаз серва 1
byte is_eyes_timer1(uint16_t p_t) {
  if (millis() - eyes_timer1 >= p_t) 
  {
   return 1;
  }
  else 
  {
   return 0;
  }
}
/// =======================================================================================================
/// таймер для глаз серва 2
unsigned long eyes_timer2 = 0;
void reset_eyes_timer2() {
    eyes_timer2 = millis();   // current millis value
}
/// 
//=======================================================================================================
/// таймер для глаз серва 2
byte is_eyes_timer2(uint16_t p_t) {
  if (millis() - eyes_timer2 >= p_t) 
  {
   return 1;
  }
  else 
  {
   return 0;
  }
}
/// =======================================================================================================
/// таймер для глаз серва 3
unsigned long eyes_timer3 = 0;
void reset_eyes_timer3() {
    eyes_timer3 = millis();   // current millis value
}
/// 
//=======================================================================================================
/// таймер для глаз серва 3
byte is_eyes_timer3(uint16_t p_t) {
  if (millis() - eyes_timer3 >= p_t) 
  {
   return 1;
  }
  else 
  {
   return 0;
  }
}
/// =======================================================================================================
/// таймер для глаз серва 4
unsigned long eyes_timer4 = 0;
void reset_eyes_timer4() {
    eyes_timer4 = millis();   // current millis value
}
/// 
//=======================================================================================================
/// таймер для глаз серва 4
byte is_eyes_timer4(uint16_t p_t) {
  if (millis() - eyes_timer4 >= p_t) 
  {
   return 1;
  }
  else 
  {
   return 0;
  }
}
/// =======================================================================================================
/// таймер для глаз серва 5
//unsigned long eyes_timer5 = 0;
//void reset_eyes_timer5() {
//    eyes_timer5 = millis();   // current millis value
//}
/// 
//=======================================================================================================
/// таймер для глаз серва 5
//byte is_eyes_timer5(uint16_t p_t) {
 // if (millis() - eyes_timer5 >= p_t) 
//  {
//   return 1;
// }
 // else 
 // {
//   return 0;
//  }
//}
/// =======================================================================================================
/// таймер для глаз серва 6
///unsigned long eyes_timer6 = 0;
///void reset_eyes_timer6() {
///    eyes_timer6 = millis();   // current millis value
///}
/// 
//=======================================================================================================
/// таймер для глаз серва 6
//byte is_eyes_timer6(uint16_t p_t) {
//  if (millis() - eyes_timer6 >= p_t) 
//  {
//   return 1;
//  }
//  else 
//  {
//   return 0;
//  }
//}
//=======================================================================================================
// Функция управления сервамий глаз
/// поворачивает от текущего положения current_servo_position[] каждой сервы в положение setpoint_servo_position[] со скоростью speed_servo_rotating[] для этой сервы.
/// после достижения целевого положения каждой сервы ничего не делает
/// встроена проверка возможных границ поворота
/// эта функция вызывается в главном цикле непрерывно всегда, управляется изменением цифр в соответсвующих массивах (setpoint_servo_position и speed_servo_rotating).

void eyes_loop(){ /// 

 //// глаза серва верхнее веко
  if (is_eyes_timer1(speed_servo_rotating[veko_up])==1) {
   reset_eyes_timer1();   
 
     if (setpoint_servo_position[veko_up] > current_servo_position[veko_up]) {
       if ((current_servo_position[veko_up] + 1) <= max_servo_position[veko_up]) {
          current_servo_position[veko_up] = current_servo_position[veko_up] + 1;
          multiservo[veko_up].write(current_servo_position[veko_up]);
          delay(1); /// pause for servo set
       }  
     } else {
       if (setpoint_servo_position[veko_up] < current_servo_position[veko_up]) {
          if ((current_servo_position[veko_up] - 1) >= min_servo_position[veko_up]) {
             current_servo_position[veko_up] = current_servo_position[veko_up] - 1;
             multiservo[veko_up].write(current_servo_position[veko_up]);
             delay(1); /// pause for servo set
          }
        }  
     }    
   
  }


 //// глаза серва нижнее веко
  if (is_eyes_timer2(speed_servo_rotating[veko_down])==1) {
   reset_eyes_timer2();   
 
     if (setpoint_servo_position[veko_down] > current_servo_position[veko_down]) {
       if ((current_servo_position[veko_down] + 1) <= max_servo_position[veko_down]) { 
          current_servo_position[veko_down] = current_servo_position[veko_down] + 1;
          multiservo[veko_down].write(current_servo_position[veko_down]);
          delay(1); /// pause for servo set
       }  
     } else {
      if (setpoint_servo_position[veko_down] < current_servo_position[veko_down]) {
          if ( (current_servo_position[veko_down] - 1) >= min_servo_position[veko_down])  {
             current_servo_position[veko_down] = current_servo_position[veko_down] - 1;
             multiservo[veko_down].write(current_servo_position[veko_down]);
             delay(1); /// pause for servo set
           }   
       }    
     }
  } 

 //// левый и правый глаз серва горизонтальное движение  движутся с одинаковой скоростью - используется один таймер, чтобы не было рассинхрона
 //// 
  if (is_eyes_timer3(speed_servo_rotating[Right_eye_x])==1) {
     reset_eyes_timer3();   

     /// правый глаз
    
     if (setpoint_servo_position[Right_eye_x] > current_servo_position[Right_eye_x]) {
       if ((current_servo_position[Right_eye_x] + 1) <= max_servo_position[Right_eye_x])  {
           current_servo_position[Right_eye_x] = current_servo_position[Right_eye_x] + 1;
           multiservo[Right_eye_x].write(current_servo_position[Right_eye_x]);
           delay(1); /// pause for servo set
       }
     } else {
      if (setpoint_servo_position[Right_eye_x] < current_servo_position[Right_eye_x]) {
         if ((current_servo_position[Right_eye_x] - 1) >= min_servo_position[Right_eye_x])  {
             current_servo_position[Right_eye_x] = current_servo_position[Right_eye_x] - 1;
             multiservo[Right_eye_x].write(current_servo_position[Right_eye_x]);
             delay(1); /// pause for servo set
         }
      }
     }
  
        
     /// левый глаз
     if (setpoint_servo_position[Left_eye_x] > current_servo_position[Left_eye_x]) {
       if ((current_servo_position[Left_eye_x] + 1) <= max_servo_position[Left_eye_x]) {
           current_servo_position[Left_eye_x] = current_servo_position[Left_eye_x] + 1;
           multiservo[Left_eye_x].write(current_servo_position[Left_eye_x]);
          delay(1); /// pause for servo set
       }
     } else {
      if (setpoint_servo_position[Left_eye_x] < current_servo_position[Left_eye_x]) {
        if ((current_servo_position[Left_eye_x] - 1) >= min_servo_position[Left_eye_x]) {
            current_servo_position[Left_eye_x] = current_servo_position[Left_eye_x] - 1;
            multiservo[Left_eye_x].write(current_servo_position[Left_eye_x]);
            delay(1); /// pause for servo set
        }
      }    
     }
  
  }

 //// левый и правый глаз серва вертикальное движение,  движутся с одинаковой скоростью - используется один таймер, чтобы не было рассинхрона
 //// 

  if (is_eyes_timer4(speed_servo_rotating[Right_eye_y])==1) {
     reset_eyes_timer4();   

     /// правый глаз
    
     if (setpoint_servo_position[Right_eye_y] > current_servo_position[Right_eye_y]) {
       if ((current_servo_position[Right_eye_y] + 1) <= max_servo_position[Right_eye_y])  {
           current_servo_position[Right_eye_y] = current_servo_position[Right_eye_y] + 1;
           multiservo[Right_eye_y].write(current_servo_position[Right_eye_y]);
          delay(1); /// pause for servo set
       }
     } else {
      if (setpoint_servo_position[Right_eye_y] < current_servo_position[Right_eye_y]) {
         if ((current_servo_position[Right_eye_y] - 1) >= min_servo_position[Right_eye_y])  {
             current_servo_position[Right_eye_y] = current_servo_position[Right_eye_y] - 1;
             multiservo[Right_eye_y].write(current_servo_position[Right_eye_y]);
             delay(1); /// pause for servo set
          }
      }
     }
       
     /// левый глаз
     if (setpoint_servo_position[Left_eye_y] > current_servo_position[Left_eye_y]) {
       if ((current_servo_position[Left_eye_y] + 1) <= max_servo_position[Left_eye_y]) {
           current_servo_position[Left_eye_y] = current_servo_position[Left_eye_y] + 1;
           multiservo[Left_eye_y].write(current_servo_position[Left_eye_y]);
           delay(1); /// pause for servo set
       }
     } else {
      if (setpoint_servo_position[Left_eye_y] < current_servo_position[Left_eye_y]) {
        if ((current_servo_position[Left_eye_y] - 1) >= min_servo_position[Left_eye_y])  {
           current_servo_position[Left_eye_y] = current_servo_position[Left_eye_y] - 1;
           multiservo[Left_eye_y].write(current_servo_position[Left_eye_y]);
           delay(1); /// pause for servo set
        }
      }    
     }
  }
   
}

//=======================================================================================================
// Функция управления сервамий глаз
/// Моргание - вызывается пока нужно моргание
/// =======================================================================================================
/// таймер для глаз моргание основной
unsigned long eyes_timer_blink = 0;
void reset_eyes_timer_blink() {
    eyes_timer_blink = millis();   // current millis value
}
/// 
//=======================================================================================================
/// таймер для глаз моргание основной
byte is_eyes_timer_blink(uint16_t p_t) {
  if (millis() - eyes_timer_blink >= p_t) 
  {
   return 1;
  }
  else 
  {
   return 0;
  }
}
/// таймер для глаз моргание дополнительный - пауза закрытые/открытые глаза во время моргания 
unsigned long eyes_timer_blink1 = 0;
void reset_eyes_timer_blink1() {
    eyes_timer_blink1 = millis();   // current millis value
}
/// 
//=======================================================================================================
/// таймер для глаз моргание дополнительный - пауза закрытые/открытые глаза во время моргания
byte is_eyes_timer_blink1(uint16_t p_t) {
  if (millis() - eyes_timer_blink1 >= p_t) 
  {
   return 1;
  }
  else 
  {
   return 0;
  }
}

byte blink_open_set = 0;
byte blink_close_set = 0;

/// 
//=======================================================================================================
/// Моргание
//// при state == 1 происходит моргание с паузой. Нужно учитывать что движение век является частью паузы. если поставить паузу слишком маленькой 
//// моргание не будет полным - серва не успеет отработать и начнет двигаться в обратном направлении.
//// движение сервы по умолчанию проходит на 1 градус за 15мс
//// при state == 0 серва века устанавливается в открытое положение
void set_eyes_blink(int state){ 

speed_servo_rotating[veko_up] = eye_veko_speed; /// установка скорости движения век    

if (state == 1) {/// если моргание включено

 if ((current_servo_position[veko_up]==eye_v_u_min) && (blink_close_set == 0)) {
      reset_eyes_timer_blink();
      blink_close_set = 1;
      blink_open_set = 0;
   } 

 if ((blink_close_set==1) && (is_eyes_timer_blink(eye_blink_pause)==1)){
     setpoint_servo_position[veko_up] =  eye_v_u_max; /// open
 }
   
 if ((current_servo_position[veko_up]==eye_v_u_max) && (blink_open_set == 0)) {
      reset_eyes_timer_blink1();
      blink_close_set = 0;
      blink_open_set = 1;
   } 

 if ((blink_open_set==1) && (is_eyes_timer_blink1(eye_blink_pause1)==1)){
     setpoint_servo_position[veko_up] =  eye_v_u_min; /// close
 }

  if ( (setpoint_servo_position[veko_up] != eye_v_u_min) && (setpoint_servo_position[veko_up] != eye_v_u_max)) {
      setpoint_servo_position[veko_up] =  eye_v_u_max; /// open
      blink_close_set = 0;
      blink_open_set = 0;
 }
  
} else {
    setpoint_servo_position[veko_up] =  eye_v_u_max; //open
}

/*
 
if (is_eyes_timer_blink(eye_blink_pause)==1) { //// если сработал таймер между морганием
  if (setpoint_servo_position[veko_up] != eye_v_u_max) { /// если веко находится НЕ в открытой позиции
    if (is_eyes_timer_blink1(eye_blink_pause1)==1) { /// если сработал таймер паузы в крайнем положении
       setpoint_servo_position[veko_up] =  eye_v_u_max; /// open - открываем глаза
       reset_eyes_timer_blink1(); ///сбрасываем таймер паузы в крайнем положении век
       reset_eyes_timer_blink(); /// сбрасываем таймер между морганиями только в открытом положении глаз
    }
  } else {
    if (is_eyes_timer_blink1(eye_blink_pause1)==1) { /// если глаза открыты и сработал таймер паузы в крайнем положении глаз
       setpoint_servo_position[veko_up] =  eye_v_u_middle2; /// close - закрываем глаза
       reset_eyes_timer_blink1();//// сбрасываем только таймер паузы в крайнем положении, таймер паузы между морганиями сбрасываем только в открытом положении
    }
  }  
}

} else { //// при выключеном моргании нужно открыть глаза
        setpoint_servo_position[veko_up] =  eye_v_u_max; //open
}*/
}

//=======================================================================================================
// Функция управления сервамий глаз
/// случайный поворот глаз
/// =======================================================================================================
/// таймер для глаз случайный поворот глаз
unsigned long eyes_timer_random_position = 0;
void reset_eyes_random_position() {
    eyes_timer_random_position = millis();   // current millis value
}
/// 
//=======================================================================================================
/// таймер для глаз случайный поворот глаз
byte is_eyes_timer_random_position(uint16_t p_t) {
  if (millis() - eyes_timer_random_position >= p_t) 
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
/// установка случайной позиции глаз
int set_pos = 100;

void set_random_eyes_position() {

  if (is_eyes_timer_random_position(eye_random_move_pause)==1) {
      
     reset_eyes_random_position();  
      
      speed_servo_rotating[Right_eye_x]=eye_x_speed;
      speed_servo_rotating[Left_eye_x]=eye_x_speed;
      speed_servo_rotating[Right_eye_y]=eye_y_speed;
      speed_servo_rotating[Left_eye_y]=eye_y_speed;

      set_pos = random(7, 12)*10;

      ////if (set_pos == 100) set_pos=50; else set_pos=100;

      if (set_pos > max_servo_position[Right_eye_x]) set_pos = max_servo_position[Right_eye_x];
      if (set_pos < min_servo_position[Right_eye_x]) set_pos = min_servo_position[Right_eye_x];

      if (set_pos > max_servo_position[Left_eye_x]) set_pos = max_servo_position[Left_eye_x];
      if (set_pos < min_servo_position[Left_eye_x]) set_pos = min_servo_position[Left_eye_x];
      
      setpoint_servo_position[Right_eye_x] = set_pos;
      setpoint_servo_position[Left_eye_x] = set_pos;

      ///setpoint_servo_position[Right_eye_y] = eye_r_y_zero;
      ///setpoint_servo_position[Left_eye_y] = eye_l_y_zero;
  }
}


//=======================================================================================================
// Функция управления сервами глаз
/// Поврот влево
/// =======================================================================================================
void set_eyes_to_left() {
      speed_servo_rotating[Right_eye_x]=eye_x_speed;
      speed_servo_rotating[Left_eye_x]=eye_x_speed;
      speed_servo_rotating[Right_eye_y]=eye_y_speed;
      speed_servo_rotating[Left_eye_y]=eye_y_speed;

      setpoint_servo_position[Right_eye_x] = eye_r_x_min; /// left position
      setpoint_servo_position[Left_eye_x] = eye_l_x_min; /// left position
      setpoint_servo_position[Right_eye_y] = eye_r_y_zero; /// central position
      setpoint_servo_position[Left_eye_y] = eye_l_y_zero; /// central position
}

//=======================================================================================================
// Функция управления сервамий глаз
/// Поврот направо
/// =======================================================================================================
void set_eyes_to_right() {
      speed_servo_rotating[Right_eye_x]=eye_x_speed;
      speed_servo_rotating[Left_eye_x]=eye_x_speed;
      speed_servo_rotating[Right_eye_y]=eye_y_speed;
      speed_servo_rotating[Left_eye_y]=eye_y_speed;

      setpoint_servo_position[Right_eye_x] = eye_r_x_max; /// right position
      setpoint_servo_position[Left_eye_x] = eye_l_x_max; /// right position
      setpoint_servo_position[Right_eye_y] = eye_r_y_zero; /// central position
      setpoint_servo_position[Left_eye_y] = eye_l_y_zero; /// central position
}

//=======================================================================================================
// Функция управления сервамий глаз
/// Поврот в центр
/// =======================================================================================================
void set_eyes_to_center() {
      speed_servo_rotating[Right_eye_x]=eye_x_speed;
      speed_servo_rotating[Left_eye_x]=eye_x_speed;
      speed_servo_rotating[Right_eye_y]=eye_y_speed;
      speed_servo_rotating[Left_eye_y]=eye_y_speed;

      setpoint_servo_position[Right_eye_x] = eye_r_x_zero; /// central position
      setpoint_servo_position[Left_eye_x] = eye_l_x_zero; /// central position
      setpoint_servo_position[Right_eye_y] = eye_r_y_zero; /// central position
      setpoint_servo_position[Left_eye_y] = eye_l_y_zero; /// central position
}

//=======================================================================================================
// Функция управления сервамий глаз
/// Поврот вверх
/// =======================================================================================================
void set_eyes_to_up() {
      speed_servo_rotating[Right_eye_x]=eye_x_speed;
      speed_servo_rotating[Left_eye_x]=eye_x_speed;
      speed_servo_rotating[Right_eye_y]=eye_y_speed;
      speed_servo_rotating[Left_eye_y]=eye_y_speed;

      setpoint_servo_position[Right_eye_x] = eye_r_x_zero; /// central position
      setpoint_servo_position[Left_eye_x] = eye_l_x_zero; /// central position
      setpoint_servo_position[Right_eye_y] = eye_r_y_min; /// up
      setpoint_servo_position[Left_eye_y] = eye_r_y_min; /// up
}

//=======================================================================================================
// Функция управления сервамий глаз
/// Прикрыть верхнее веко
/// =======================================================================================================
void set_eyes_up_veko_close() {
    speed_servo_rotating[veko_up] = eye_veko_speed;    
    speed_servo_rotating[veko_down] = eye_veko_speed;    
    setpoint_servo_position[veko_up] =  eye_v_u_middle1; /// middle position
    setpoint_servo_position[veko_down] =  eye_v_d_zero; /// open position
}

//=======================================================================================================
// Функция управления сервамий глаз
/// Прикрыть нижнее веко
/// =======================================================================================================
void set_eyes_down_veko_close() {
    speed_servo_rotating[veko_up] = eye_veko_speed;    
    speed_servo_rotating[veko_down] = eye_veko_speed;    
    setpoint_servo_position[veko_up] =  eye_v_u_zero; /// open position
    setpoint_servo_position[veko_down] =  eye_v_d_middle; /// middle position
}

//=======================================================================================================
// Функция управления сервамий глаз
/// закрыть глаза
/// =======================================================================================================
void set_eyes_to_close(){
    speed_servo_rotating[veko_up] = eye_veko_speed;    
    speed_servo_rotating[veko_down] = eye_veko_speed;    
    setpoint_servo_position[veko_up] =  eye_v_u_min;
    setpoint_servo_position[veko_down] =  eye_v_d_min;
}

//=======================================================================================================
// Функция управления сервамий глаз
/// реализует команды c цифровых входов
/// 
/// 
/// 
byte eyes_blink = 0;
byte eyes_random = 0;
byte eyes_up_veko = 0;
byte eyes_down_veko = 0;
byte eyes_close = 0;
byte eyes_to_left = 0;
byte eyes_to_right = 0;
byte eyes_to_center = 0;
byte eyes_to_up = 0;
byte flag_blink = 0;
byte eyes_standby_open = 0;

void Set_eyes(){ /// 

   eyes_blink = 0;
   eyes_random = 0;
   eyes_up_veko = 0;
   eyes_down_veko = 0;
   eyes_close = 0;
   eyes_to_left = 0;
   eyes_to_right = 0;
   eyes_to_center = 0;
   eyes_to_up = 0;

   if (input_state_pin5 == 1){
     eyes_blink = 1;
   } else {
     eyes_blink = 0;
   }

   
   if((input_state_pin6 == 1) && (input_state_pin7 == 1) && (input_state_pin8 == 1)){
    eyes_random = 1;
    eyes_up_veko = 0;
    eyes_down_veko = 0;
    eyes_close = 0;
    eyes_to_left = 0;
    eyes_to_right = 0;
    eyes_to_center = 0;
    eyes_to_up = 0;
    }
    
   if((input_state_pin6 == 1) && (input_state_pin7 == 0) && (input_state_pin8 == 0)){
     eyes_blink = 0;
     eyes_random = 0;
     eyes_up_veko = 1;
     eyes_down_veko = 0;
     eyes_close = 0;
     eyes_to_left = 0;
     eyes_to_right = 0;
     eyes_to_center = 1;
     eyes_to_up = 0;
    }
    
   if((input_state_pin6 == 1) && (input_state_pin7 == 1) && (input_state_pin8 == 0)){
     eyes_blink = 0;
     eyes_random = 0;
     eyes_up_veko = 0;
     eyes_down_veko = 1;
     eyes_close = 0;
     eyes_to_left = 0;
     eyes_to_right = 0;
     eyes_to_center = 1;
     eyes_to_up = 0;
    }

   if((input_state_pin6 == 0) && (input_state_pin7 == 0) && (input_state_pin8 == 0)){
     eyes_blink = 0;
     eyes_random = 0;
     eyes_up_veko = 0;
     eyes_down_veko = 0;
     eyes_close = 1;
     eyes_to_left = 0;
     eyes_to_right = 0;
     eyes_to_center = 1;
     eyes_to_up = 0;
    }

   if((input_state_pin6 == 0) && (input_state_pin7 == 0) && (input_state_pin8 == 1)){
     eyes_random = 0;
     eyes_up_veko = 0;
     eyes_down_veko = 0;
     eyes_close = 0;
     eyes_to_left = 1;
     eyes_to_right = 0;
     eyes_to_center = 0;
     eyes_to_up = 0;
    }

   if((input_state_pin6 == 0) && (input_state_pin7 == 1) && (input_state_pin8 == 0)){
     eyes_random = 0;
     eyes_up_veko = 0;
     eyes_down_veko = 0;
     eyes_close = 0;
     eyes_to_left = 0;
     eyes_to_right = 1;
     eyes_to_center = 0;
     eyes_to_up = 0;
    }

   if((input_state_pin6 == 0) && (input_state_pin7 == 1) && (input_state_pin8 == 1)){
     eyes_random = 0;
     eyes_up_veko = 0;
     eyes_down_veko = 0;
     eyes_close = 0;
     eyes_to_left = 0;
     eyes_to_right = 0;
     eyes_to_center = 1;
     eyes_to_up = 0;
    }

   if((input_state_pin6 == 1) && (input_state_pin7 == 0) && (input_state_pin8 == 1)){
     eyes_random = 0;
     eyes_up_veko = 0;
     eyes_down_veko = 0;
     eyes_close = 0;
     eyes_to_left = 0;
     eyes_to_right = 0;
     eyes_to_center = 1;
     eyes_to_up = 1;
    }

   eyes_standby_open = 1 ;

   if  (eyes_blink == 1) {
    set_eyes_blink(1);
    flag_blink = 1;
    eyes_standby_open = 0;
   } else {
     if (flag_blink == 1){
      set_eyes_blink(0);
      eyes_standby_open = 0;
      flag_blink = 0;
     }
  }

   if (eyes_random == 1) {
     set_random_eyes_position();
   } else {
     if (eyes_to_left == 1)set_eyes_to_left();
     if (eyes_to_right == 1) set_eyes_to_right();
     if (eyes_to_center == 1) set_eyes_to_center();
     if (eyes_close == 1){
      set_eyes_to_close();
      eyes_standby_open = 0;
     }
     if (eyes_up_veko == 1){
      set_eyes_up_veko_close();
      eyes_standby_open = 0;
     }
     if (eyes_down_veko == 1) {
      set_eyes_down_veko_close();
      eyes_standby_open = 0;
     }
     if (eyes_to_up == 1) set_eyes_to_up();
   }

   if (eyes_standby_open == 1) {
    speed_servo_rotating[veko_up] = eye_veko_speed;    
    speed_servo_rotating[veko_down] = eye_veko_speed;    
    setpoint_servo_position[veko_up] =  eye_v_u_zero;
    setpoint_servo_position[veko_down] =  eye_v_d_zero;
   }


}


///=================================================================================================================================================================
///===  ФУНКЦИИ ЧТЕНИЯ ВХОДОВ      ===
///=================================================================================================================================================================
 float answer1 = 0;  
 float answer2 = 0;  
 float answer3 = 0;  
 float answer4 = 0;
 float answer5 = 0;
 float answer6 = 0;
 float answer7 = 0;
 float answer8 = 0;
 int i_inputs = 0;
   
unsigned long timer_inputs = 0;
/// =======================================================================================================
/// таймер для чтения входов
void reset_timer_inputs() {
    timer_inputs = millis();   // current millis value
}
//=======================================================================================================
/// таймер для чтения входов
byte is_timer_inputs(uint16_t p_t) {
  if (millis() - timer_inputs >= p_t) 
  {
   return 1;
  }
  else 
  {
   return 0;
  }
}

//=======================================================================================================
/// функуия чтения входов, вызывается непрерывно, 
//// присваивает глобальным переменным input_state_pin1 .. input_state_pin8 значения на входе 
//// с вычислением среднего значения за number_read_iterations чтений каждое через read_state_time мс
void read_inputs() {
    if (drive_via_comport==1) return; /// ничего не делать с input_state_pin если управление по comport 

     if (is_timer_inputs(read_state_time)==1) {
       i_inputs = i_inputs + 1;
       answer1 = answer1 + digitalRead(Input_pin1) ;
       answer2 = answer2 + digitalRead(Input_pin2) ;
       answer3 = answer3 + digitalRead(Input_pin3) ;
       answer4 = answer4 + digitalRead(Input_pin4) ;
       answer5 = answer5 + digitalRead(Input_pin5) ;
       answer6 = answer6 + digitalRead(Input_pin6) ;
       answer7 = answer7 + digitalRead(Input_pin7) ;
       answer8 = answer8 + digitalRead(Input_pin8) ;
       reset_timer_inputs();
       if (i_inputs >= number_read_iterations) {
         answer1 = answer1 / number_read_iterations;  
         answer2 = answer2 / number_read_iterations;  
         answer3 = answer3 / number_read_iterations;  
         answer4 = answer4 / number_read_iterations;  
         answer5 = answer5 / number_read_iterations;  
         answer6 = answer6 / number_read_iterations;  
         answer7 = answer7 / number_read_iterations;  
         answer8 = answer8 / number_read_iterations;  
         if (answer1 >= 0.5) input_state_pin1 = 1;
             else input_state_pin1 = 0;
         if (answer2 >= 0.5) input_state_pin2 = 1;
             else input_state_pin2 = 0;
         if (answer3 >= 0.5) input_state_pin3 = 1;
             else input_state_pin3 = 0;
         if (answer4 >= 0.5) input_state_pin4 = 1;
             else input_state_pin4 = 0;
         if (answer5 >= 0.5) input_state_pin5 = 1;
             else input_state_pin5 = 0;
         if (answer6 >= 0.5) input_state_pin6 = 1;
             else input_state_pin6 = 0;
         if (answer7 >= 0.5) input_state_pin7 = 1;
             else input_state_pin7 = 0;
         if (answer8 >= 0.5) input_state_pin8 = 1;
             else input_state_pin8 = 0;
         i_inputs = 0;
         answer1 = 0;    
         answer2 = 0;    
         answer3 = 0;    
         answer4 = 0;    
         answer5 = 0;    
         answer6 = 0;    
         answer7 = 0;    
         answer8 = 0;    
      }
     }
}

///=================================================================================================================================================================
///=================================================================================================================================================================
///== Функции для общения по компорту - определение что за команда пришла по компорту
//// в мониторе порта ардуины при посылке команды show() в ответ придет полное состояние переменных программы для отладки
String uart_input_str;
String uart_command_str;
///String answer_str;
byte uart_command=30;
//int32_t uart_answer_int=0;
//float uart_answer_float=0;
//String uart_answer_str;
//String uart_read_str;
///int uart_fst_ind,uart_last_ind;
int uart_com_end=0;

void Setup_number_command_from_uart(){

if (uart_command_str=="show") {
   uart_command=8;
   return;
}

if (uart_command_str=="dr_on") {
   uart_command=0;
   return;
}

if (uart_command_str=="dr_off") {
   uart_command=1;
   return;
}

if (uart_command_str=="sm_cl") {
   uart_command=2;
   return;
}

if (uart_command_str=="sm_op") {
   uart_command=3;
   return;
}

if (uart_command_str=="sm_m1") {
   uart_command=4;
   return;
}

if (uart_command_str=="sm_m2") {
   uart_command=5;
   return;
}


if (uart_command_str=="h_c") {
   uart_command=6;
   return;
}

if (uart_command_str=="h_l") {
   uart_command=7;
   return;
}

if (uart_command_str=="h_r") {
   uart_command=9;
   return;
}

if (uart_command_str=="h_rnd") {
   uart_command=10;
   return;
}

if (uart_command_str=="e_bl1") {
   uart_command=11;
   return;
}

if (uart_command_str=="e_bl0") {
   uart_command=12;
   return;
}

if (uart_command_str=="e_rnd") {
   uart_command=13;
   return;
}

if (uart_command_str=="e_l") {
   uart_command=14;
   return;
}

if (uart_command_str=="e_r") {
   uart_command=15;
   return;
}

if (uart_command_str=="e_cent") {
   uart_command=16;
   return;
}

if (uart_command_str=="e_o") {
   uart_command=17;
   return;
}

if (uart_command_str=="e_cl") {
   uart_command=18;
   return;
}

if (uart_command_str=="e_up") {
   uart_command=19;
   return;
}

if (uart_command_str=="e_vu") {
   uart_command=20;
   return;
}

if (uart_command_str=="e_vd") {
   uart_command=21;
   return;
}


}

///=================================================================================================================================================================
///=================================================================================================================================================================
///== Функция для общения по компорту - получение команд и выполнение действия связанного с этими командами
void Uart_transfer(){

uart_input_str="";
uart_command_str="";
uart_command=30;
//uart_answer_int=0;
//uart_answer_float=0;
//uart_answer_str="";
//uart_read_str="";
//uart_fst_ind=0;
//uart_last_ind=0;
uart_com_end=-1;
 
 
 if (Serial.available()) {
  uart_input_str=Serial.readStringUntil('\n');
  uart_input_str.trim();

  uart_com_end = uart_input_str.indexOf('(');
  
  if (uart_com_end==-1) {
    Serial.println("Error");
    return;
  } else {
    uart_command_str = uart_input_str.substring(0, uart_com_end);
    Serial.println(uart_command_str);
  }

  uart_command=30;
  
  Setup_number_command_from_uart();
 
  switch (uart_command) {
 
  case 0:
      drive_via_comport=1;
      Serial.println("=====>comport drive");
      Serial.print("Drive via comport  = ");
      Serial.println(drive_via_comport);
  break;
  
  case 1:
      drive_via_comport=0;
      Serial.println("=====>comport drive");
      Serial.print("Drive via comport  = ");
      Serial.println(drive_via_comport);
 break;

  case 2: /// smile close
   input_state_pin3=1;
   input_state_pin4=1;
  break; 
   
  case 3: //smile open
   input_state_pin3=0;
   input_state_pin4=0;
  break; 

  case 4: /// smile middle1
   input_state_pin3=1;
   input_state_pin4=0;
  break; 

  case 5: /// smile middle2
   input_state_pin3=0;
   input_state_pin4=1;
  break; 

  case 6: // head center
   input_state_pin1=0;
   input_state_pin2=0;
  break; 

  case 7: // head left
   input_state_pin1=1;
   input_state_pin2=0;
  break; 

  case 8:
    // выполнить, если значение == show()
      Serial.println("Servo smile");
      Serial.print("Number =");
      Serial.println(Smile_servo);
      Serial.print("Current =");
      Serial.println(current_servo_position[Smile_servo]);
      Serial.print("Setpoint =");
      Serial.println(setpoint_servo_position[Smile_servo]);
      Serial.print("Speed =");
      Serial.println(speed_servo_rotating[Smile_servo]);
      Serial.print("Max pos =");
      Serial.println(max_servo_position[Smile_servo]);
      Serial.print("Min pos =");
      Serial.println(min_servo_position[Smile_servo]);
      Serial.print("Init pos =");
      Serial.println(initial_servo_position[Smile_servo]);


      Serial.println("Servo Head rotate ");
      Serial.print("Number =");
      Serial.println(Head_Povorot_servo);
      Serial.print("Current =");
      Serial.println(current_servo_position[Head_Povorot_servo]);
      Serial.print("Setpoint =");
      Serial.println(setpoint_servo_position[Head_Povorot_servo]);
      Serial.print("Speed =");
      Serial.println(speed_servo_rotating[Head_Povorot_servo]);
      Serial.print("Max pos =");
      Serial.println(max_servo_position[Head_Povorot_servo]);
      Serial.print("Min pos =");
      Serial.println(min_servo_position[Head_Povorot_servo]);
      Serial.print("Init pos =");
      Serial.println(initial_servo_position[Head_Povorot_servo]);

      Serial.println("Servo Veko up");
      Serial.print("Number =");
      Serial.println(veko_up);
      Serial.print("Current =");
      Serial.println(current_servo_position[veko_up]);
      Serial.print("Setpoint =");
      Serial.println(setpoint_servo_position[veko_up]);
      Serial.print("Speed =");
      Serial.println(speed_servo_rotating[veko_up]);
      Serial.print("Max pos =");
      Serial.println(max_servo_position[veko_up]);
      Serial.print("Min pos =");
      Serial.println(min_servo_position[veko_up]);
      Serial.print("Init pos =");
      Serial.println(initial_servo_position[veko_up]);

      Serial.println("Servo Veko down");
      Serial.print("Number =");
      Serial.println(veko_down);
      Serial.print("Current =");
      Serial.println(current_servo_position[veko_down]);
      Serial.print("Setpoint =");
      Serial.println(setpoint_servo_position[veko_down]);
      Serial.print("Speed =");
      Serial.println(speed_servo_rotating[veko_down]);
      Serial.print("Max pos =");
      Serial.println(max_servo_position[veko_down]);
      Serial.print("Min pos =");
      Serial.println(min_servo_position[veko_down]);
      Serial.print("Init pos =");
      Serial.println(initial_servo_position[veko_down]);
      
      Serial.println("Servo Right Eye x");
      Serial.print("Number =");
      Serial.println(Right_eye_x);
      Serial.print("Current =");
      Serial.println(current_servo_position[Right_eye_x]);
      Serial.print("Setpoint =");
      Serial.println(setpoint_servo_position[Right_eye_x]);
      Serial.print("Speed =");
      Serial.println(speed_servo_rotating[Right_eye_x]);
      Serial.print("Max pos =");
      Serial.println(max_servo_position[Right_eye_x]);
      Serial.print("Min pos =");
      Serial.println(min_servo_position[Right_eye_x]);
      Serial.print("Init pos =");
      Serial.println(initial_servo_position[Right_eye_x]);

      Serial.println("Servo Right Eye y");
      Serial.print("Number =");
      Serial.println(Right_eye_y);
      Serial.print("Current =");
      Serial.println(current_servo_position[Right_eye_y]);
      Serial.print("Setpoint =");
      Serial.println(setpoint_servo_position[Right_eye_y]);
      Serial.print("Speed =");
      Serial.println(speed_servo_rotating[Right_eye_y]);
      Serial.print("Max pos =");
      Serial.println(max_servo_position[Right_eye_y]);
      Serial.print("Min pos =");
      Serial.println(min_servo_position[Right_eye_y]);
      Serial.print("Init pos =");
      Serial.println(initial_servo_position[Right_eye_y]);

      Serial.println("Servo Left Eye x");
      Serial.print("Number =");
      Serial.println(Left_eye_x);
      Serial.print("Current =");
      Serial.println(current_servo_position[Left_eye_x]);
      Serial.print("Setpoint =");
      Serial.println(setpoint_servo_position[Left_eye_x]);
      Serial.print("Speed =");
      Serial.println(speed_servo_rotating[Left_eye_x]);
      Serial.print("Max pos =");
      Serial.println(max_servo_position[Left_eye_x]);
      Serial.print("Min pos =");
      Serial.println(min_servo_position[Left_eye_x]);
      Serial.print("Init pos =");
      Serial.println(initial_servo_position[Left_eye_x]);

      Serial.println("Servo Left Eye y");
      Serial.print("Number =");
      Serial.println(Left_eye_y);
      Serial.print("Current =");
      Serial.println(current_servo_position[Left_eye_y]);
      Serial.print("Setpoint =");
      Serial.println(setpoint_servo_position[Left_eye_y]);
      Serial.print("Speed =");
      Serial.println(speed_servo_rotating[Left_eye_y]);
      Serial.print("Max pos =");
      Serial.println(max_servo_position[Left_eye_y]);
      Serial.print("Min pos =");
      Serial.println(min_servo_position[Left_eye_y]);
      Serial.print("Init pos =");
      Serial.println(initial_servo_position[Left_eye_y]);


      Serial.println("=>Eyes command");

      Serial.print("eyes_blink = ");
      Serial.println(eyes_blink);
      
      Serial.print("eyes_random = ");
      Serial.println(eyes_random);

      Serial.print("eyes_up_veko = ");
      Serial.println(eyes_up_veko);

      Serial.print("eyes_down_veko = ");
      Serial.println(eyes_down_veko);

      Serial.print("eyes_close = ");
      Serial.println(eyes_close);

      Serial.print("eyes_to_left = ");
      Serial.println(eyes_to_left);

      Serial.print("eyes_to_right = ");
      Serial.println(eyes_to_left);

      Serial.print("eyes_to_center = ");
      Serial.println(eyes_to_center);

      Serial.print("eyes_to_up = ");
      Serial.println(eyes_to_up);
      
      Serial.println("=>Inputs state");

      Serial.print("Input(1)= ");
      Serial.println(input_state_pin1);
 
      Serial.print("Input(2)= ");
      Serial.println(input_state_pin2);
       
      Serial.print("Input(3)= ");
      Serial.println(input_state_pin3);
       
      Serial.print("Input(4)= ");
      Serial.println(input_state_pin4);
       
      Serial.print("Input(5)= ");
      Serial.println(input_state_pin5);
       
      Serial.print("Input(6)= ");
      Serial.println(input_state_pin6);

      Serial.print("Input(7)= ");
      Serial.println(input_state_pin7);

      Serial.print("Input(8)= ");
      Serial.println(input_state_pin8);

      Serial.print("Drive comport  = ");
      Serial.println(drive_via_comport);

  break;

  case 9: // head right
   input_state_pin1=0;
   input_state_pin2=1;
  break; 

  case 10: // head random
   input_state_pin1=1;
   input_state_pin2=1;
  break; 

  case 11: // blink on
   input_state_pin5=1;
  break; 

  case 12: // blink off
   input_state_pin5=0;
  break; 


  case 13: // eyes random
   input_state_pin6 = 1;
   input_state_pin7 = 1;
   input_state_pin8 = 1;
  break; 

  case 14: // eyes left
   input_state_pin6 = 0;
   input_state_pin7 = 0;
   input_state_pin8 = 1;
  break; 

  case 15: // eyes right
   input_state_pin6 = 0;
   input_state_pin7 = 1;
   input_state_pin8 = 0;
  break; 

  case 16: // eyes center
   input_state_pin6 = 0;
   input_state_pin7 = 1;
   input_state_pin8 = 1;
  break; 

  case 17: // eyes open
   input_state_pin5 = 1;
   input_state_pin6 = 0;
   input_state_pin7 = 1;
   input_state_pin8 = 1;
  break; 

  case 18: // eyes close
   input_state_pin6 = 0;
   input_state_pin7 = 0;
   input_state_pin8 = 0;
  break; 

  case 19: // eyes up
   input_state_pin6 = 1;
   input_state_pin7 = 0;
   input_state_pin8 = 1;
  break; 

  case 20: // eyes veko up to middle
   input_state_pin6 = 1;
   input_state_pin7 = 0;
   input_state_pin8 = 0;
  break; 

  case 21: // eyes veko down to middle
   input_state_pin6 = 1;
   input_state_pin7 = 1;
   input_state_pin8 = 0;
  break; 

  default:
    // выполнить, если значение не совпадает ни с одним из case
    Serial.println("Unknown command.");
    return;
    break;
   }

 }
  
}


///=================================================================================================================================================================
///===  НАЧАЛЬНыЕ НАСТРОЙКИ     ===
///=================================================================================================================================================================
void setup() {  

///входы у нас pullup поэтому по умолчанию згачения на входах=1
  input_state_pin1 = 1 ;
  input_state_pin2 = 1 ;
  input_state_pin3 = 1 ;
  input_state_pin4 = 1 ;
  input_state_pin5 = 1 ;
  input_state_pin6 = 1 ;
  input_state_pin7 = 1 ;
  input_state_pin8 = 1 ;
  
  
  pinMode(Input_pin1, INPUT_PULLUP);
  pinMode(Input_pin2, INPUT_PULLUP);
  pinMode(Input_pin3, INPUT_PULLUP);
  pinMode(Input_pin4, INPUT_PULLUP);
  pinMode(Input_pin5, INPUT_PULLUP);
  pinMode(Input_pin6, INPUT_PULLUP);
  pinMode(Input_pin7, INPUT_PULLUP);
  pinMode(Input_pin8, INPUT_PULLUP);
  
  
  // Перебираем значения серв от 0 до 9
   for (int count = 0; count < MULTI_SERVO_COUNT; count++) {
   // Подключаем сервомотор
   multiservo[count].attach(count);
   delay(5);
   }
   delay(10);

//// устанавливаем начальные и граничные значения для всех серв
init_servo_min_max();

/// устанавливаем физически сервы в начальное состояние.
init_servo_positions();

//comport init
Serial.begin(115200);
Serial.setTimeout(5);

/// сбрасываем все таймеры
reset_pause_timer();
reset_pause_timer1();
reset_timer_smile();
reset_timer_inputs();
reset_eyes_timer1();
reset_eyes_timer2();
reset_eyes_timer3();
reset_eyes_timer4();
reset_eyes_timer_blink();
reset_eyes_timer_blink1();
reset_eyes_random_position();

//delay(10000000);

}




///=================================================================================================================================================================
///===  ГЛАВНЫЙ ЦИКЛ     ===
///=================================================================================================================================================================
void loop(){
  
  Uart_transfer(); /// получение команд из монитора порта для отладки. Команда "show()"

  read_inputs(); //// функция чтения цифровых входов, устанавливает значение переменных отражающих значение на входах 
  
  Set_head_rotate(); /// анализ входов для поворота головы и переключение режимов поворота
  Set_smile(); /// анализ входов для улыбки и переключение режимов улыюбки

  Set_eyes(); /// анализ входов для глаз и переключение режима их работы

  head_povorot_loop(); /// функция движения головы - поворачивает голову в положение указанное в Set_head_rotate с указанной скоростью
  smile_loop(); /// функция движения сервы рта - поворачивает серву в положение указанное в Set_smile с указанной скоростью
  eyes_loop(); /// функция движения серв глаз - поворачивает сервы в положение указанное в Set_eyes с указанной скоростью

}
