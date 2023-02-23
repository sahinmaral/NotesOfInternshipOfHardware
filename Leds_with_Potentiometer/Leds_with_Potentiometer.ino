void setup() {
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  if(sensorValue < 400){
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
  }
  else if(sensorValue >= 400 && sensorValue <= 900){
        digitalWrite(8,LOW);
        digitalWrite(9,HIGH);
  }
  else{
        digitalWrite(8,HIGH);
        digitalWrite(9,HIGH);
  }
  Serial.println(sensorValue);
}
