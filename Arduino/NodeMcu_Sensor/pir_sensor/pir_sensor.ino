int pirPin = 16;
int ledPin = 5;
int i = 0;

void setup() {
 // put your setup code here, to run once:
 Serial.begin(115200);
 pinMode(pirPin, INPUT);
 pinMode(ledPin, OUTPUT);
}
 
void loop() {
 // put your main code here, to run repeatedly:
 int s = digitalRead(pirPin);
 Serial.print("input no.");
 Serial.print(i);
 Serial.print(": ");
 Serial.println(s);
 i++;
 digitalWrite(ledPin, s);
 //delay(100);
}
