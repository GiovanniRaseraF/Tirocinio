#define BATTERY  A0 //digital signal
void setup() {
  Serial.begin(9600);
  while(!Serial);
  pinMode(BATTERY, INPUT);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  bool battery = digitalRead(A0);
  Serial.println(battery);

}
