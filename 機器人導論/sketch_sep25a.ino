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
	
	if (ultraSoundState() == ultrasoundstate::too_far) {
		setSpeed(leftspeed=150, rightspeed=100);
	}
	else if (ultraSoundState() == ultrasoundstate::in_range) {	
		if (front_clear == 1) {
			setSpeed(leftspeed=100, rightspeed=150);
		}
		if (front_clear == 0) {
			setSpeed(leftspeed=100, rightspeed=120);
		}
	}
	else if (ultraSoundState() == ultrasoundstate::too_close) {
		setSpeed(leftspeed=100, rightspeed=150);
	}
	else {
		setSpeed(leftspeed=100, rightspeed=120);
	}
}

void normalRun(){    
	 // turn on motor A
	//digitalWrite(in1, HIGH);
	
	digitalWrite(in2, LOW);
	digitalWrite(in4, LOW);
	analogWrite(in1,175);//å·?
	analogWrite(in3,210);
	/*for(int i = 0;i <255;i+= 5){
		analogWrite(in3,i);
		analogWrite(in1,i);
		delay(10);
	}
	 for(int i = 255;i > 0;i-= 5){
		analogWrite(in3,i+20);
		analogWrite(in1,i);
		delay(10);
	}*/
	//analogWrite(6,255);
	//delay(5000);
	// turn on motor B
	//digitalWrite(in3, HIGH);
	//analogWrite(10,180);
	//delay(5000);
	
}
