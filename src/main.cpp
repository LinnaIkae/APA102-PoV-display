// #include "Arduino.h"

// #define LED_BUILTIN PC13
// #define MOIST PA1

// int moisture;

// void setup()
// {
//     pinMode(LED_BUILTIN, OUTPUT);
//     Serial.begin(9600);

//     pinMode(MOIST, INPUT_ANALOG);
// }

// void loop()
// {
//     moisture = analogRead(MOIST);
//     Serial.println(moisture);
//     delay(1000);
// }

// #include "Arduino.h"
// #define MOTOR PA1

// //min pwm 44000. max 65535

// int onTime;
// void setup()
// {
//     Serial1.begin(9600);

//     pinMode(MOTOR, PWM);

//     Serial1.println("Writing 1000 for 3s");
//     pwmWrite(MOTOR, 1000);
//     delay(3000);

//     Serial1.println("Startup with x duty cycle.");
//     pwmWrite(MOTOR, 1000);
//     delay(5000);
//     Serial1.println("Motor starting...");
//     onTime = 43000;
// }

// void loop()
// {
//     onTime += 100;
//     if(onTime > 65535){
//         onTime = 43000;
//     }
//     pwmWrite(MOTOR, onTime);
//     Serial1.print("New onTime:");
//     Serial1.println(onTime);
//     delay(200);
// }
