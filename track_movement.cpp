/*
  Additional functions for motor control and movement.
  <>forward:
        kk
  <>reverse:
        kk
  <>turn_left:
        kk
*/

void motor_setup() {
  // put your setup code here, to run once:
  // Initialize the stepper driver control pins to output drive mode.
  //Serial.begin(9600);

  pinMode(ln1_pin, OUTPUT);
  pinMode(ln2_pin, OUTPUT);
  pinMode(ln3_pin, OUTPUT);
  pinMode(ln4_pin, OUTPUT);

  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);
}

// void loop() {
//   // put your main code here, to run repeatedly:
//   forward();
//   delay(1000);
//   reverse();
//   delay(1000);
//   turn_left();
//   delay(1000);
// }

void forward(){
  //Left track forward
  digitalWrite(ln1_pin, LOW);
  digitalWrite(ln2_pin, HIGH);
  //Right track forward
  digitalWrite(ln3_pin, HIGH);
  digitalWrite(ln4_pin, LOW);
  
  analogWrite(enableA, mSpeed);
  analogWrite(enableB, mSpeed);
}
void reverse() {
  //Left track backward
  digitalWrite(ln1_pin, HIGH);
  digitalWrite(ln2_pin, LOW);
  //Right track backward
  digitalWrite(ln3_pin, LOW);
  digitalWrite(ln4_pin, HIGH);
  
  //assign speeds
  analogWrite(enableA, mSpeed);
  analogWrite(enableB, mSpeed);
}
void turn_left(){
  //Left track forward
  digitalWrite(ln1_pin, HIGH);
  digitalWrite(ln2_pin, LOW);
  //Right track backward
  digitalWrite(ln3_pin, HIGH);
  digitalWrite(ln4_pin, LOW);
  
  analogWrite(enableA, mSpeed);
  analogWrite(enableB, mSpeed); 
}