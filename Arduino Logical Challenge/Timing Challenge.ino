// Constants for timing
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long duration = 50000; // Default duration: 50 seconds
bool isRunning = false;

// Pin definitions
const int startPin = 13; // Pin for starting the timer
const int stopPin = 9;  // Pin for stopping the timer
const int resetPin = 6; // Pin for resetting the timer
const int incPin = 2;   // Pin for increasing the duration
const int decPin = 0;   // Pin for decreasing the duration

// Function to start the timer
void startTimer() {
  if (!isRunning) {
    // If the timer is not running, adjust startTime
    startTime = millis() - elapsedTime;
    isRunning = true;
  }
}

// Function to stop the timer
void stopTimer() {
  if (isRunning) {
    elapsedTime = millis() - startTime;
    isRunning = false;
  }
}

// Function to reset the timer
void resetTimer() {
  elapsedTime = 0;
  isRunning = false;
}

// Function to increase the timer's duration
void increaseDuration() {
  elapsedTime += 5000; // Increase duration by 1 second (1000 milliseconds)
}

// Function to decrease the timer's duration
void decreaseDuration() {
  if (elapsedTime > 5000) { // Ensure duration doesn't go below 1 second
    elapsedTime -= 5000;    // Decrease duration by 1 second (1000 milliseconds)
  }
}

void setup() {
  Serial.begin(9600);
  
  // Set button pins as inputs with pull-up resistors
  pinMode(startPin, INPUT_PULLUP);
  pinMode(stopPin, INPUT_PULLUP);
  pinMode(resetPin, INPUT_PULLUP);
  pinMode(incPin, INPUT_PULLUP);
  pinMode(decPin, INPUT_PULLUP);
}

void loop() {
  // Check start button
  if (digitalRead(startPin) == HIGH) {
    if (!isRunning) {
      startTimer();
      Serial.println("Timer started.");
    }
    // Wait for button release
    while (digitalRead(startPin) == HIGH);
  }
  
  // Check stop button
  if (digitalRead(stopPin) == HIGH) {
    if (isRunning) {
      stopTimer();
      Serial.println("Timer stopped.");
      Serial.print("Elapsed Time: ");
      Serial.print(elapsedTime);
      Serial.println(" ms");
      
    }
    // Wait for button release
    while (digitalRead(stopPin) == HIGH);
  }
  
  // Check reset button
  if (digitalRead(resetPin) == HIGH) {
    resetTimer();
    Serial.println("Timer reset.");
    Serial.print("Elapsed Time: ");
      Serial.print(elapsedTime);
      Serial.println(" ms");
    // Wait for button release
    while (digitalRead(resetPin) == HIGH);
  }
  
  // Check increase duration button
  if (digitalRead(incPin) == HIGH) {
    increaseDuration();
    Serial.println("Duration increased.");
    // Wait for button release
    while (digitalRead(incPin) == HIGH);
  }
  
  // Check decrease duration button
  if (digitalRead(decPin) == HIGH) {
    decreaseDuration();
    Serial
.println("Duration decreased.");
    // Wait for button release
    while (digitalRead(decPin) == HIGH);
  }
  
  // Start the timer
  if (isRunning && millis() - startTime >= duration) {
    // Perform action when timer reaches duration
    Serial.println("Timer expired!");
    
    // Stop the timer
    stopTimer();
  }
  
  // Simulate delay
  delay(100);
}
