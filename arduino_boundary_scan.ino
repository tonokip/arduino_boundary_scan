

//Arduino Mega
uint8_t pins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14 ,15, 16, 17, 18, 19, 20, 21, 22, 23, 24 ,25, 26, 27 };

//DB25
uint8_t dbmp[] = { 1, 2, 3, 4, 5, 6, 7 ,8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };

#define LED_PIN 13

uint8_t test_pass;

void setup() {
  Serial.begin(115200);
  Serial.println("start");
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  test_pass=1;

  for(int i=0; i<sizeof(pins); i++) {
    pinMode(pins[i], INPUT_PULLUP);
    if( digitalRead(pins[i]) == LOW ) {
      Serial.print("Short to GND on pin: ");
      Serial.println(pins[i]);
      test_pass = 0;
    }
  }

  for(int i=0; i<sizeof(pins); i++)
  {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i],LOW);
    for(int j=0; j<sizeof(pins); j++)
    {
      if(j != i && digitalRead(pins[j]) == LOW)
      {
        test_pass = 0;
        Serial.print("Driving pin ");
        Serial.print(pins[i]);
        Serial.print(" low causes pin ");
        Serial.print(pins[j]);
        Serial.println(" to be low.");
      }
    }
    pinMode(pins[i], INPUT_PULLUP);
  }

  if(test_pass)
    digitalWrite(LED_PIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

}
