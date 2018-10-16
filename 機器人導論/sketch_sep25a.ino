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

// judge the state of the distance from car to wall
int state(){	
	digitalWrite(TrigPin, LOW);
	//
	delayMicroseconds(2);
	digitalWrite(TrigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(TrigPin, LOW);
	float time_reply=pulseIn(EchoPin, HIGH); //the time from sent to receive
	cm = time_reply /58.82;	//the distance(cm)
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

int leftspeed = 100;
int rightspeed = 120;

void loop() {
	// put your main code here, to run repeatedly:
	digitalWrite(in2, LOW);
	digitalWrite(in4, LOW);
	int front_clear = detect(Sensor_front_pin);
	int right_clear  = detect(Sensor_right_pin);
	
	if (state() == 1 ) {
		leftspeed = 150;
		rightspeed = 100;
		analogWrite(in3, rightspeed);
		analogWrite(in1, leftspeed);
	}
	else if (state() == 2) {	
		if (front_clear == 1) {
			leftspeed = 100;
			rightspeed = 150;
			analogWrite(in1, leftspeed);
			analogWrite(in3, rightspeed);
		}
		if (front_clear == 0) {
			leftspeed = 100;
			rightspeed = 120;
			analogWrite(in1,leftspeed);
			analogWrite(in3,rightspeed);
		}
	}
	else if (state() == 0) {
		leftspeed = 100;
		rightspeed = 150;
		analogWrite(in1,leftspeed);
		analogWrite(in3,rightspeed);
	}
	else {
		leftspeed = 100;
		rightspeed = 120;
		analogWrite(in1,leftspeed);
		analogWrite(in3,rightspeed);
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
