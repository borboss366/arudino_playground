#define NUM_ANALOG_INPUTS 6

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < NUM_ANALOG_INPUTS; ++i) {
    int inputValue = analogRead(i);
    Serial.print(inputValue);
    Serial.print(" ");
  }
  Serial.println();
  delay(1000);
}
