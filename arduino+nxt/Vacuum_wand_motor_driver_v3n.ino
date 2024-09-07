/// Конфигурация пинов для управления мотором
#define PWM_Output 9 
#define Analog_speed_pin A0

#define Input_speed_pin1 A1
#define Input_speed_pin2 A2
#define Input_speed_pin3 A3
#define Input_speed_pin4 A4

#define number_read_iterations 3
#define ABSOLUTE_MAX_SPEED 1023 /// in arb units скорость мотора задается от 0 до 1023.

/// Конфигурация пинов для получения команд от головного устройства
#define RUN_COMMAND 12  

//// светодиод включается когда мотор крутится и выключается когда стоит
#define WORK_LED 13

bool motor_moving=false; // флажок показывающий что мотор вращается

//// Команды для мотора
int motor_run=0; /// запустить вращение мотора или нет
int speed_setpoint_current=0;///// Текущая уставка скорости мотора.

//////переменные для управления мотором по компорту
int drive_via_com=0; /// если равно 1 то команды принимаются по компорту, а пины не активны
int speed_com=500; ///скорость вращения мотора  заданная при управлении через компорт
int motor_run_com=0; /// команда из компорта для начала/остановки вращения

////// global vars for uart_transfer function
//// переменные для разбора команд приходящих из компорта
String uart_input_str;
String uart_command_str;
String answer_str;
int uart_command=0;
int32_t uart_answer_int=0;
float uart_answer_float=0;
String uart_answer_str;
String uart_read_str;
int uart_fst_ind,uart_last_ind;
int uart_com_end=0;

///=================================================================================================================================================================
///=================================================================================================================================================================
///=== запуск контроллера
void setup() {

   ///// настравиваем таймер чтобы генерировать на 9 и 10 пину шим с высокой частотой и 10бит разрешением
   //// раскомментировать соответсвующие строки
   /// по этим пинам управляется драйвер двигателя
   
  // Пины D9 и D10 - 7.8 кГц 10bit
  ///  TCCR1A = 0b00000011;  // 10bit
  //  TCCR1B = 0b00000001;  // x1 phase correct

  // Пины D9 и D10 - 15.6 кГц 10bit
  //   TCCR1A = 0b00000011;  // 10bit
  //   TCCR1B = 0b00001001;  // x1 fast pwm

  ///Пины D9 и D10 - 2 кГц 10bit
  //TCCR1A = 0b00000011;  // 10bit
  //TCCR1B = 0b00001010;  // x8 fast pwm

  // Пины D9 и D10 - 977 Гц 10bit
  TCCR1A = 0b00000011;  // 10bit
  TCCR1B = 0b00000010;  // x8 phase correct

  // Пины D9 и D10 - 244 Гц 10bit
  //TCCR1A = 0b00000011;  // 10bit
  //TCCR1B = 0b00001011;  // x64 fast pwm

  // Пины D9 и D10 - 122 Гц 10bit
  //TCCR1A = 0b00000011;  // 10bit
  //TCCR1B = 0b00000011;  // x64 phase correct

  // Пины D9 и D10 - 61 Гц 10bit
  //TCCR1A = 0b00000011;  // 10bit
  //TCCR1B = 0b00001100;  // x256 fast pwm

  // Пины D9 и D10 - 30 Гц 10bit
  //TCCR1A = 0b00000011;  // 10bit
  //TCCR1B = 0b00000100;  // x256 phase correct

  // Пины D9 и D10 - 15 Гц 10bit
  //TCCR1A = 0b00000011;  // 10bit
  //TCCR1B = 0b00001101;  // x1024 fast pwm

  // Пины D9 и D10 - 7.5 Гц 10bit
  //TCCR1A = 0b00000011;  // 10bit
  //TCCR1B = 0b00000101;  // x1024 phase correct  
  
  //pin in/out init
  /// commands from main controller

  ///// настройка входных пинов для получения команд от головного конроллера
  //// для исключения ложных срабатываний пины притянуты к +5В
  //// для подключения к головному контроллеру исправить на INPUT и исправить функцию read_inputs()
  pinMode(RUN_COMMAND, INPUT_PULLUP);

  ///pins for motor driver
  //// настройка пинов управления драйвером мотора.
  pinMode(PWM_Output, OUTPUT);
  pinMode(WORK_LED, OUTPUT);
  
  pinMode(Input_speed_pin1, INPUT_PULLUP);
  pinMode(Input_speed_pin2, INPUT_PULLUP);
  pinMode(Input_speed_pin3, INPUT_PULLUP);
  pinMode(Input_speed_pin4, INPUT_PULLUP);

  //comport init
  Serial.begin(115200);
  Serial.setTimeout(5);

  //// установка начальных значений важных переменных 
  motor_moving=false; /// мотор не вращается
  motor_run=0; /// остановить мотор
  speed_setpoint_current=0;///// Текущая уставка скорости мотора.
  motor_stop();
}


///=================================================================================================================================================================
///=================================================================================================================================================================
///== Чтение входов для команд мотору
void read_inputs() {

  if (drive_via_com==0) {

    ///// управление через пины
     if (digitalRead(RUN_COMMAND)==LOW) { //// вход у нас pullup
        motor_run=HIGH; /// запустить вращение мотора или нет
     } else {
        motor_run=LOW; /// запустить вращение мотора или нет
     }

      speed_setpoint_current=read_motor_speed(); 

   //// чтение уставки скорости из аналогвого входа от 0 до 1023

  } else { 
   ///// управление через компорт командами
   speed_setpoint_current=speed_com;
   motor_run=motor_run_com;   
  }

}

///=================================================================================================================================================================
///=================================================================================================================================================================
///== Установка выходов для индикации вращения мотора
void set_outputs() {
  if (motor_moving==true) {
   digitalWrite(WORK_LED, HIGH);
  } else
  {
   digitalWrite(WORK_LED, LOW);
  }
  
}


int read_speed_input(int number) {
	
 float answer = 0;	
	
  switch (number) {
 
  case 1:
     for (int i = 0; i < number_read_iterations; i++) {
       answer = answer + float(digitalRead(Input_speed_pin1));
	   delay(1);
     }
     answer = answer / number_read_iterations;	
	 if (answer >= 0.5) return 1;
	 else return 0;
	 
  break;
  
  case 2:
   for (int i = 0; i < number_read_iterations; i++) {
       answer = answer + float(digitalRead(Input_speed_pin2));
	   delay(1);
     }
     answer = answer / number_read_iterations;	
	 if (answer >= 0.5) return 1;
	 else return 0;
  break;
  
  case 3:
   for (int i = 0; i < number_read_iterations; i++) {
       answer = answer + float(digitalRead(Input_speed_pin3));
	   delay(1);
     }
     answer = answer / number_read_iterations;	
	 if (answer >= 0.5) return 1;
	 else return 0;
  
  break;
  
  case 4:
   for (int i = 0; i < number_read_iterations; i++) {
       answer = answer + float(digitalRead(Input_speed_pin4));
	   delay(1);
     }
     answer = answer / number_read_iterations;	
	 if (answer >= 0.5) return 1;
	 else return 0;
  
  break;
  }
  return 0;
	
}

///=================================================================================================================================================================
///=================================================================================================================================================================
///== Функция чтения скорости мотора из аналогового пина
int read_motor_speed() {

  int SpeedValue = 0;
  //SpeedValue = analogRead(Analog_speed_pin);
  int pin1 = 0 ;
  int pin2 = 0 ;
  int pin3 = 0 ;
  int pin4 = 0 ;
  
  pin1 = read_speed_input(1);
  pin2 = read_speed_input(2);
  pin3 = read_speed_input(3);
  pin4 = read_speed_input(4);

  
   if((pin1 == 1) && (pin2 == 0) && (pin3 == 0) && (pin4 == 0)){
     SpeedValue = 254;
    
   }
   
   if((pin1 == 0) && (pin2 == 1) && (pin3 == 0) && (pin4 == 0)){
     SpeedValue = 300;
   }
   
   if((pin1 == 0) && (pin2 == 0) && (pin3 == 1) && (pin4 == 0)){
     SpeedValue = 355;
   }
   
   if((pin1 == 0) && (pin2 == 0) && (pin3 == 0) && (pin4 == 1)){
     SpeedValue = 410;
   }
///////==================================================================================='//////////////////////////
   if((pin1 == 1) && (pin2 == 1) && (pin3 == 0) && (pin4 == 0)){
     SpeedValue = 520;
   }
   
   if((pin1 == 0) && (pin2 == 1) && (pin3 == 1) && (pin4 == 0)){
     SpeedValue = 575;
   }
   
   if((pin1 == 0) && (pin2 == 0) && (pin3 == 1) && (pin4 == 1)){
     SpeedValue = 630;
   }
   
   if((pin1 == 1) && (pin2 == 0) && (pin3 == 1) && (pin4 == 0)){
     SpeedValue = 685;
   }
   
   if((pin1 == 1) && (pin2 == 0) && (pin3 == 0) && (pin4 == 1)){
     SpeedValue = 740;
   }
   
   if((pin1 == 0) && (pin2 == 1) && (pin3 == 0) && (pin4 == 1)){
     SpeedValue = 795;
   }

  //////=======================================================================================================////////  
   if((pin1 == 1) && (pin2 == 1) && (pin3 == 1) && (pin4 == 0)){
     SpeedValue = 850;
   }
   if((pin1 == 1) && (pin2 == 1) && (pin3 == 0) && (pin4 == 1)){
     SpeedValue = 905;
   }

   if((pin1 == 1) && (pin2 == 0) && (pin3 == 1) && (pin4 == 1)){
      SpeedValue = 960;
   }
   if((pin1 == 0) && (pin2 == 1) && (pin3 == 1) && (pin4 == 1)){
     SpeedValue = 1015;
   }
  
 // SpeedValue = 500;
  //SpeedValue = analogRead(Analog_speed_pin);
 // return(SpeedValue);
   Serial.println("1");
  return(SpeedValue);
  
}

///=================================================================================================================================================================
///=================================================================================================================================================================
///== Функция остановки вращения мотора
void motor_stop() {
    analogWrite(PWM_Output, 0);
    motor_moving=false;
}


///=================================================================================================================================================================
///=================================================================================================================================================================
///== Функция запуска вращения мотора
void motor_start(int rotation_speed) {

          motor_moving=true;

          if (rotation_speed==255) {
            rotation_speed=254;
          }

          if (rotation_speed>1023) {
            rotation_speed=1023;
          }

          if (rotation_speed<0) {
            rotation_speed=0;
          }

          analogWrite(PWM_Output, rotation_speed);
}

///=================================================================================================================================================================
///=================================================================================================================================================================
///== Функция вращения мотора
void motor_move() {

 if (motor_run==HIGH) {
      //// включаем вращение 
      motor_start(speed_setpoint_current);
      
  } else {
    motor_stop(); 
  }

}

///=================================================================================================================================================================
///=================================================================================================================================================================
///== Функция для общения по компорту - определение что за команда пришла по компорту
void Setup_number_command_from_uart(){

if (uart_command_str=="DEBUG") {
   uart_command=8;
   return;
}


if (uart_command_str=="COM") {
   uart_command=10;
   return;
}

if (uart_command_str=="SPD") {
   uart_command=11;
   return;
}

if (uart_command_str=="START") {
   uart_command=12;
   return;
}


}

///=================================================================================================================================================================
///=================================================================================================================================================================
///== Функция для общения по компорту - получение команд и выполнение действия связанного с этими командами
void Uart_transfer(){

uart_input_str="";
uart_command_str="";
uart_command=0;
uart_answer_int=0;
uart_answer_float=0;
uart_answer_str="";
uart_read_str="";
uart_fst_ind=0;
uart_last_ind=0;
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

  uart_command=0;
  
  Setup_number_command_from_uart();
 
  switch (uart_command) {
 
  case 8:
    // выполнить, если значение == DEBUG()
  
      Serial.println("=========================Debug information ===============================");

      Serial.println("=====>inputs state");

      Serial.print("Input RUN_COMMAND (");
      Serial.print(RUN_COMMAND);
      Serial.print(") = ");
      Serial.println(digitalRead(RUN_COMMAND));
     
      Serial.print("current motor speed=");
      Serial.println(speed_setpoint_current);
      
      Serial.println("=====>motor moving parameters");

      Serial.print("Motor run (command from main controller)=");
      Serial.println(motor_run);

      Serial.print("Motor moving (current state)=");
      Serial.println(motor_moving);
      
      
      Serial.println("=====>comport commands");

      Serial.print("drive via comport=");
      Serial.println(drive_via_com);
      
      Serial.print("speed via comport=");
      Serial.println(speed_com);

      Serial.print("motor run via comport=");
      Serial.println(motor_run_com);
      
      Serial.print("Input pin 1=");
      Serial.println(read_speed_input(1));

      Serial.print("Input pin 2=");
      Serial.println(read_speed_input(2));

      Serial.print("Input pin 3=");
      Serial.println(read_speed_input(2));

      Serial.print("Input pin 4=");
      Serial.println(read_speed_input(4));
  break;

 case 10:
   // выполнить, если значение == COM(число)
   uart_fst_ind = uart_input_str.indexOf('(');
   uart_last_ind = uart_input_str.indexOf(')');
  
  if ((uart_fst_ind==-1) || (uart_last_ind==-1)) {
    Serial.println("Error");
    return;
  } else {
    if (uart_fst_ind<(uart_last_ind-1)) {
       uart_read_str = uart_input_str.substring(uart_fst_ind+1, uart_last_ind);
    } else {
       Serial.println("Error");
       return;
    }
  }
    uart_answer_int = uart_read_str.toInt();

    if ((uart_answer_int<0) || (uart_answer_int>1)) {
     uart_answer_int=0; 
    }

   drive_via_com = uart_answer_int;

    answer_str = "COM("+String(drive_via_com)+')';
    uart_answer_str = answer_str;
    Serial.println(uart_answer_str);
    break;

 case 11:
   // выполнить, если значение == SPD(число)
   uart_fst_ind = uart_input_str.indexOf('(');
   uart_last_ind = uart_input_str.indexOf(')');
  
  if ((uart_fst_ind==-1) || (uart_last_ind==-1)) {
    Serial.println("Error");
    return;
  } else {
    if (uart_fst_ind<(uart_last_ind-1)) {
       uart_read_str = uart_input_str.substring(uart_fst_ind+1, uart_last_ind);
    } else {
       Serial.println("Error");
       return;
    }
  }
    uart_answer_int = uart_read_str.toInt();

    if ((uart_answer_int<0) || (uart_answer_int>ABSOLUTE_MAX_SPEED)) {
     uart_answer_int=ABSOLUTE_MAX_SPEED; 
    }

   speed_com = uart_answer_int;

    answer_str = "SPD("+String(speed_com)+')';
    uart_answer_str = answer_str;
    Serial.println(uart_answer_str);
    break;


case 12:
   // выполнить, если значение == START(число)
   uart_fst_ind = uart_input_str.indexOf('(');
   uart_last_ind = uart_input_str.indexOf(')');
  
  if ((uart_fst_ind==-1) || (uart_last_ind==-1)) {
    Serial.println("Error");
    return;
  } else {
    if (uart_fst_ind<(uart_last_ind-1)) {
       uart_read_str = uart_input_str.substring(uart_fst_ind+1, uart_last_ind);
    } else {
       Serial.println("Error");
       return;
    }
  }
    uart_answer_int = uart_read_str.toInt();

    if ((uart_answer_int<0) || (uart_answer_int>1)) {
     uart_answer_int=0; 
    }

   motor_run_com = uart_answer_int;

    answer_str = "START("+String(motor_run_com)+')';
    uart_answer_str = answer_str;
    Serial.println(uart_answer_str);
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
///===  ГЛАВНЫЙ ЦИКЛ     ===
///=================================================================================================================================================================

void loop() {

///// все функции не блокирующие
read_inputs();

Uart_transfer();

motor_move();

set_outputs();

}
