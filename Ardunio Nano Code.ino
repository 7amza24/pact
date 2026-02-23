// ------------ Ultrasonic Pins ------------
#define TRIG1 8
#define ECHO1 9
#define TRIG2 4
#define ECHO2 5
#define TRIG3 6
#define ECHO3 7

// ------------ Output Pins to ESP ------------
#define OUT_1 10   // Road 1
#define OUT_2 11   // Road 2  
#define OUT_3 12   // Road 3

// ------------ Timing ------------
unsigned long detectStart1 = 0;
unsigned long detectStart2 = 0;
unsigned long detectStart3 = 0;

bool congested1 = false;
bool congested2 = false;
bool congested3 = false;

const int THRESHOLD_CM = 8;
const unsigned long REQUIRED_TIME = 10000;  // 10 seconds

// ------------ Functions ------------
long readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 100000);
  if (duration == 0) return -1;
  return duration * 0.034 / 2;
}

void setup() {
  Serial.begin(9600);

  pinMode(TRIG1, OUTPUT); pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT); pinMode(ECHO2, INPUT);
  pinMode(TRIG3, OUTPUT); pinMode(ECHO3, INPUT);

  pinMode(OUT_1, OUTPUT); digitalWrite(OUT_1, LOW);
  pinMode(OUT_2, OUTPUT); digitalWrite(OUT_2, LOW);
  pinMode(OUT_3, OUTPUT); digitalWrite(OUT_3, LOW);

  Serial.println("Nano Ready - Monitoring 3 Roads (Road 4 Disabled)");
}

void loop() {
  unsigned long now = millis();

  long d1 = readUltrasonic(TRIG1, ECHO1);
  long d2 = readUltrasonic(TRIG2, ECHO2);
  long d3 = readUltrasonic(TRIG3, ECHO3);

  // Print sensor readings
  Serial.print("R1:"); Serial.print(d1);
  Serial.print(" R2:"); Serial.print(d2);
  Serial.print(" R3:"); Serial.print(d3);
  Serial.print(" R4: CLEAR");  // Road 4 always clear
  Serial.println();

  //
