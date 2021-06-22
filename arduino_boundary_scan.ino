//Arduino Mega
uint8_t pins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14 ,15, 16, 17, 18, 19, 20, 21, 22, 23, 24 ,25, 26, 27 };

//DB25
uint8_t dbmp[] = { 1, 2, 3, 4, 5, 6, 7 ,8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };

// RJ45
uint8_t rj_out[] = { 31, 32, 33, 34, 35, 36, 37, 38 };
uint8_t db_in[] = { 6,   9,  4,  8,  8,  3,  22, 5 };
#define LED_PIN 13

uint8_t test_pass;

void setup() {
  Serial.begin(115200);
  test();
}
void test() {
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
        Serial.print("Driving DB25 pin ");
        Serial.print(dbmp[i]);
        Serial.print(" low causes DB25 pin ");
        Serial.print(dbmp[j]);
        Serial.println(" to be low.");
      }
    }
    pinMode(pins[i], INPUT_PULLUP);
  }

  for (int i=0; i<sizeof(rj_out); i++)
  {
    pinMode(rj_out[i], OUTPUT);
    digitalWrite(rj_out[i], LOW);
    if (digitalRead(db_in[i]) == HIGH)
    {
      test_pass = 0;
      Serial.print("RJ output pin ");
      Serial.print(i + 1);
      Serial.println(" not connected to DB25 pin.");
    }
    pinMode(rj_out[i], INPUT);
  }
  
  if(test_pass) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Test PASSED.");
  } else {
    Serial.println("Test FAILED.");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    // read the incoming byte:
    Serial.println(Serial.read());
    test();
    }
}