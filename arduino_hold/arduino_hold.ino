void setup() {
  // initialize serial:
  Serial.begin(9600);
  pinMode(12, INPUT);
  digitalWrite(12, HIGH); //internal pullups
  pinMode(13, OUTPUT);
}

void loop() {
  if (digitalRead(12) == LOW)
  {
    Serial.write(0x0E);
    digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(13, LOW);
  }
  delay(1000);
}



