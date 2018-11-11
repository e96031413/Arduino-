
void setup() {

  pinMode(3, INPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  }

void loop() {
  if (digitalRead(3) == 0 && analogRead(A0) > 100) {
    digitalWrite(6, HIGH);

  }
  else {
    digitalWrite(6, LOW);

  }

  if (digitalRead(3) == 1 && analogRead(A0) > 100 ) {
    digitalWrite(7, HIGH);
  }
    else {
      digitalWrite(7, LOW);
    }
    Serial.println(digitalRead(3));
  }
