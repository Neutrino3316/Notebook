int in1 = 5;
int in2 = 4;
// motor two
int in3 = 6;
int in4 = 7;

const int TrigPin =  9;
const int EchoPin =  8;
float cm;

int Sensor_front_pin = 2;
int Sensor_right_pin = 3;

namespace ultrasoundstate {
	int too_far = 2;
	int too_close = 0;
	int in_range = 1;
}

// judge the state of the distance from car to wall
int ultraSoundState(){	
	digitalWrite(TrigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(TrigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(TrigPin, LOW);
	float time_reply=pulseIn(EchoPin, HIGH); //the time from sent to receive
	cm = time_reply / 58.82;	//the distance(cm)
	Serial.println(cm);
	if (cm > 30) return ultrasoundstate::too_far;
	else if (cm < 25) return ultrasoundstate::too_close;
	else return ultrasoundstate::in_range;
}
void setup() {
	// put your setup code here, to run once:
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	Serial.begin(9600);
	pinMode(TrigPin, OUTPUT);
	pinMode(EchoPin, INPUT);
}

int infraredDetect(int Sensor_pin) {
	int sensorValue = digitalRead(Sensor_pin);
	Serial.print(Sensor_pin);
	Serial.println(sensorValue);
	delay(100);
	return sensorValue;
}

void setSpeed(int leftspeed, int rightspeed) {
	// go straight or turn right or turn left
	analogWrite(in3, rightspeed);
	analogWrite(in1, leftspeed);
}

int leftspeed = 100;
int rightspeed = 120;

void loop() {
	// put your main code here, to run repeatedly:
	digitalWrite(in2, LOW);
	digitalWrite(in4, LOW);
	int front_clear = infraredDetect(Sensor_front_pin);
	int right_clear  = infraredDetect(Sensor_right_pin);
	
    if (front_clear == 1) {
        if (ultraSoundState() == ultrasoundstate::too_far) {
            if (right_clear == 0) {
                setSpeed(leftspeed=80, rightspeed=100);
            }
            else {
                setSpeed(leftspeed=50, rightspeed=50);
            }
        }
        else if (ultraSoundState() == ultrasoundstate::in_range) {
            setSpeed(leftspeed=80, rightspeed=95);
        }
        else {
            // ultraSoundState() == ultrasoundstate::too_close
            setSpeed(leftspeed=80, rightspeed=100);
        }
    }
}

/*
TODO: merge code of zkm

int in1 = 5;
int in2 = 4;
// motor two
int in3 = 6;
int in4 = 7;
const int TrigPin =  9;
const int EchoPin =  8;
float cm;
int Sensor_front_pin = 2;
int Sensor_right_pin = 3;
int value(){
  digitalWrite(TrigPin, LOW);
  //低高低电平发一丟�时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  float time_reply=pulseIn(EchoPin, HIGH); //the time from sent to receive
  cm = time_reply /58.82;
  Serial.println(cm);
  if (cm >30 ) return 1;
  else if (cm < 25) return 0;
  else return 2;
}
void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
   Serial.begin(9600);
   pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}
int detect(int Sensor_pin) {
   int sensorValue = digitalRead(Sensor_pin);
   Serial.print(Sensor_pin);
   Serial.println(sensorValue);
   delay(100);
   return sensorValue;
}
int leftspeed = 80;
int rightspeed = 95;
void loop() {
  // put your main code here, to run repeatedly:

      digitalWrite(in2, LOW);
      digitalWrite(in4, LOW);
      int front = detect(Sensor_front_pin);
      int right = detect(Sensor_right_pin);
      int check = value();
      if (front == 1){//no front
        if (check == 1 ){ //too far
          if (right == 0){
            leftspeed = 80;
            rightspeed = 100;
            analogWrite(in3,rightspeed);
            analogWrite(in1,leftspeed);
            //delay(10);
          }
          //while(right == 1)
          else{
             leftspeed = 50;
             rightspeed = 50;
            analogWrite(in3,rightspeed);
            analogWrite(in1,leftspeed);
          }
         }
         else if(check == 2){//all right right
             leftspeed = 80;
             rightspeed = 95;
            analogWrite(in1,leftspeed);
            analogWrite(in3,rightspeed);
         }
           
       else if(check == 0){//too close
           leftspeed = 80;
           rightspeed = 100;
          an

*/