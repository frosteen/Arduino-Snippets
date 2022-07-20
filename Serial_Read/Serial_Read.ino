void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()) {
    // read character
    char c = Serial.read();
    // read string ending with \n
//    String s = Serial.readStringUntil("\n");
    // read integer
//    int i = Serial.parseInt();
    // read float
//    float f = Serial.parseFloat();
  }
}
