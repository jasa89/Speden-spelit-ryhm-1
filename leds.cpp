

#include "leds.h"
 randomSeed(analogRead(0)); // Seed the random number generator
// Define the initializeLeds() function
void initializeLeds() {
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
}

// Global variables for millis() timing
unsigned long previousMillis = 0;     // Store the last time an LED was updated
unsigned long interval = 1000;        // Start with 1 second (1000ms)
unsigned long offTime = 200;          // Time for LED to stay off between cycles
int cycleCount = 0;                   // Track number of cycles for speed increase
bool initialLedsOn = true;            // Track whether all LEDs were turned on initially
int previousLed = -1;                 // Variable to store the previously lit LED
bool ledOn = false;                   // Track if an LED is currently on

const unsigned long MIN_INTERVAL = 100; // Set the minimum speed (100ms)



// Set the specified LED and turn off all others
void setLed(byte ledNumber) {
    clearAllLeds(); // Turn off all LEDs first
    switch (ledNumber) {
        case 0: digitalWrite(A0, HIGH); break;
        case 1: digitalWrite(A1, HIGH); break;
        case 2: digitalWrite(A2, HIGH); break;
        case 3: digitalWrite(A3, HIGH); break;
    }
}

// Turn off all LEDs
void clearAllLeds() {
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
}

// Turn on all LEDs
void setAllLeds() {
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
}

// Non-blocking LED cycle using millis()
void cycleRandomLeds() {
    unsigned long currentMillis = millis(); // Get the current time

    // If the LEDs haven't been turned on yet, turn them all on
    if (initialLedsOn) {
        setAllLeds();            // Turn all LEDs on
        delay(1000);             // Optional: keep them on for 1 second
        initialLedsOn = false;   // Indicate that the LEDs are now initialized
        previousMillis = currentMillis; // Reset the timing
        return;
    }

    // If an LED is currently on and the interval has passed, turn it off
    if (ledOn && currentMillis - previousMillis >= interval) {
        clearAllLeds();          // Turn off all LEDs
        ledOn = false;           // Set flag to indicate LEDs are off
        previousMillis = currentMillis; // Update previousMillis to current time
    }
    // If the LEDs are off and the offTime has passed, turn on the next LED
    else if (!ledOn && currentMillis - previousMillis >= offTime) {
        previousMillis = currentMillis; // Save the current time

        // Choose a random LED
        int randomLed = random(0, 4);

        setLed(randomLed);       // Set the randomly chosen LED
        previousLed = randomLed; // Update previousLed to the current one
        ledOn = true;            // Set flag to indicate LEDs are on

        // Print to track LED changes
        Serial.print("Random LED: ");
        Serial.println(randomLed);

        cycleCount++; // Increment cycle count after each blink

        // Increase speed (reduce interval) after 10 cycles, until MIN_INTERVAL is reached
        if (cycleCount >= 10 && interval > MIN_INTERVAL) {
            interval -= 100; // Decrease interval by 100ms to increase speed
            cycleCount = 0;  // Reset cycle count, so we increase speed every 10 cycles

            // Print to track interval change
            Serial.print("Speeding up. New interval: ");
            Serial.println(interval);
        }
    }
}











