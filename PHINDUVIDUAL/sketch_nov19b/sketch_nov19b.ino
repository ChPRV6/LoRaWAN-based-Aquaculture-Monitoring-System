const int potPin=A0;
float ph;
float Value=0;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(potPin,INPUT);
  delay(1000);
}
 void loop(){
 
    Value= analogRead(potPin);
    float voltage=Value*(3.3/4095.0);
    ph=(3.3*voltage);
    Serial.println("The PH of the terminal is given by: ");
    Serial.println(ph);
    delay(500);
 }