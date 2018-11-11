/******************************************
  PURPOSE:	Step Motor Elevator
  Created by      Diego Serrano Reinel after some sketches by Rudy Schlaf
  DATE:		11/2014
*******************************************/



//----- Switches & Photocells -----//

#define switchFloor1 6 // Switches are connected to these pins
#define switchFloor2 5


#define photocellFloor2 0 // Photocells and 10K pulldown resistor are connected to A0 and A1 for an analog reading

//----- Stepper motor -----//

#define steps 1 // Number of steps needed to reach the next floor (displace the elevator 7cm)

#define stepperPin1  10 // These are the Arduino pins that we use to activate coils 1-4 of the stepper motor
#define stepperPin2  11
#define stepperPin3  12
#define stepperPin4  13

#define delaytime 10   // Delay time in ms to control the stepper motor delaytime
// 8 is about the fastest that can yield reliable operation w/o missing steps

// Variables

boolean firstRun = true;
int currentFloor = 1; // Used to save the current floor. This value is changed with the switches and with the readings done by the photocells
long debounceTime = 200; // The switch's debounce time
int secondFloorReading = 0; // The analog reading from the sensor divider (for floor 2 and 3)
int thirdFloorReading = 0;

//----- readSwitch -----//
//This function reads the current state of the switches
byte readSwitch(int switchPin, long debounceTime)
{
  long debounce = debounceTime;
  static long lastTime;
  static byte previousState;
  byte currentState = digitalRead(switchPin);
  if (currentState == LOW && previousState == HIGH && millis() - lastTime > debounce) { // Check if the Switch went from HIGH to LOW
    lastTime = millis(); // Measure the time for which it was pressed
    previousState = LOW;
    return (true); // Switch was pressed
  }
  else
  {
    previousState = HIGH;
    return (false); // Switch has not been pressed
  }
}

//----- Pin settings for Stepper Motor, forward() and backward( -----/

// These functions set the pin settings for each of the four steps per rotation of the motor (keepp in mind that the motor in the kit is geared down,
// i.e. there are many steps necessary per rotation
void Step_A() {
  digitalWrite(stepperPin1, HIGH); // Turn on coil 1
  digitalWrite(stepperPin2, LOW);
  digitalWrite(stepperPin3, LOW);
  digitalWrite(stepperPin4, LOW);
}
void Step_B() {
  digitalWrite(stepperPin1, LOW);
  digitalWrite(stepperPin2, HIGH); // Turn on coil 2
  digitalWrite(stepperPin3, LOW);
  digitalWrite(stepperPin4, LOW);
}
void Step_C() {
  digitalWrite(stepperPin1, LOW);
  digitalWrite(stepperPin2, LOW);
  digitalWrite(stepperPin3, HIGH); // Turn on coil 3
  digitalWrite(stepperPin4, LOW);
}
void Step_D() {
  digitalWrite(stepperPin1, LOW);
  digitalWrite(stepperPin2, LOW);
  digitalWrite(stepperPin3, LOW);
  digitalWrite(stepperPin4, HIGH); // Turn on coil 4
}
void step_OFF() {
  digitalWrite(stepperPin1, LOW); // Power all coils down
  digitalWrite(stepperPin2, LOW);
  digitalWrite(stepperPin3, LOW);
  digitalWrite(stepperPin4, LOW);
}

// These functions run the above configurations in forward and reverse order
// The direction of a stepper motor depends on the order in which the coils are turned on.
void forward() { // One tooth forward
  Step_A();
  delay(delaytime);
  Step_B();
  delay(delaytime);
  Step_C();
  delay(delaytime);
  Step_D();
  delay(delaytime);
}

void backward() { // One tooth backward
  Step_D();
  delay(delaytime);
  Step_C();
  delay(delaytime);
  Step_B();
  delay(delaytime);
  Step_A();
  delay(delaytime);
}


void setup() {
  Serial.begin(9600); // Initialize serial port

  pinMode(switchFloor1, INPUT); // Define the arduino pins for the swi tches as inputs
  pinMode(switchFloor2, INPUT);

  pinMode(stepperPin1, OUTPUT); // Define the the arduino pins for the stepper's coils as outputs
  pinMode(stepperPin2, OUTPUT);
  pinMode(stepperPin3, OUTPUT);
  pinMode(stepperPin4, OUTPUT);
}

void loop() {

  secondFloorReading = analogRead(photocellFloor2); // Get a reading from the photocells to verify the current floor

  Serial.print("Analog reading (Second floor) = ");
  Serial.println(secondFloorReading); // the raw analog reading
  delay(1000);

  if (secondFloorReading > 790 ) // Check if the elevator is in the first floor
  {
    // Turn on the segments that display the number 1
    currentFloor = 1; // Set the current floor to 1
    // The elevator is meant to start at the first floor
  }
  else if (secondFloorReading < 750) // Check if the elevator is in the second floor
  {
    // Turn on the segments that display the number 2
    currentFloor = 2;
  }


  // The following if statement will only allow the switch's input if the current floor is not already 1
  // The coils in the stepper motor will go backwards if the elevator
  // is on either floor 2 or floor 3
  // If it is on floor 3, it will go backwards twice the number of steps
  if (readSwitch(switchFloor1, debounceTime) == true && currentFloor != 1) {
    int numberOfSteps;
    if (currentFloor == 2) {
      Serial.println("going down");
      int numberOfSteps = steps + 90;
      step_OFF(); // Turning all coils off

      while (numberOfSteps > 0) {
        backward(); // Going backward
        numberOfSteps -- ; // Counting down the number of steps
      }
    }

    while (numberOfSteps > 0) {
      backward(); // Going backward
      numberOfSteps -- ; // Counting down the number of steps
    }
  }
  currentFloor = 1; // Sets the currentFloor to 1 since the elevator is now at the first floor
  delay(1000);


  // The following if statement will only allow the switch's input if the current floor is not already 2
  // The coils in the stepper motor will go forward or backwards if the elevator
  // is on either floor 1 or floor 3, respectively
  if (readSwitch(switchFloor2, debounceTime) == true && currentFloor != 2) {
    int numberOfSteps;
    if (currentFloor == 1) {
      Serial.println("going up");
      int numberOfSteps = steps + 90;
      step_OFF(); // Turning all coils off

      while (numberOfSteps > 0) {
        forward(); // Going forward
        numberOfSteps -- ; // Counting down the number of steps
      }
    }
    while (numberOfSteps > 0) {
      backward(); // Going forward
      numberOfSteps -- ; // Counting down the number of steps
    }
  }
  currentFloor = 2; // Sets the currentFloor to 2 since the elevator is now at the second floor
  delay(2000);
}

// The following if statement will only allow the switch's input if the current floor is not already 3
// The coils in the stepper motor will go backwards if the elevator
// is on either floor 1 or floor 2
// If it is on floor 1, it will go forward twice the number of steps
