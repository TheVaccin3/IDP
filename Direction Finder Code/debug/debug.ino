void setup() {
  Serial.begin(9600);
}

int newV1;
int newV2;


void loop() {
  newV1 = analogRead(A0);
  Serial.print(newV1);
  Serial.print(",");
  newV2 = analogRead(A3);
  Serial.println(newV2);
}
