#include "leds.h"

// Define the initializeLeds() function
void initializeLeds() {
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
}

// Global variables for millis() timing
unsigned long previousMillis = 0; // Store the last time an LED was updated
unsigned long interval = 500;     // Initial interval (1000ms)
int currentLed = 0;               // Track the current LED
int cycleCount = 0;               // Track number of cycles for speed increase
bool initialLedsOn = true;        // Track whether all LEDs were turned on initially

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
void cycleAllLeds() {
    unsigned long currentMillis = millis(); // Get the current time

    // If the LEDs haven't been turned on yet, turn them all on
    if (initialLedsOn) {
        setAllLeds();            // Turn all LEDs on
        delay(1000);             // Optional: keep them on for 1 second
        initialLedsOn = false;   // Indicate that the LEDs are now initialized
        previousMillis = currentMillis; // Reset the timing
        return;
    }

    // Check if the interval has passed
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis; // Save the current time

        setLed(currentLed); // Set the current LED

        currentLed++; // Move to the next LED
        if (currentLed > 3) {
            currentLed = 0; // Reset to the first LED after cycling through all

            cycleCount++; // Increment cycle count after completing a full cycle

            // Increase speed (reduce interval) after 10 cycles
            if (cycleCount >= 10 && interval >= 100) {
                interval -= 100; // Decrease interval by 100ms to increase speed
            }

            // Optionally reset cycleCount after 20 cycles
            if (cycleCount >= 20) {
                cycleCount = 0;
                interval = 500; // Reset to the original speed
            } 
        }
    }
}

// Non-blocking random LED blinking using millis()
void show2(int rounds) {
    static unsigned long previousMillis2 = 0;
    static int currentRound = 0;
    int delayTime = interval; // Use the dynamic interval

    unsigned long currentMillis = millis(); // Get the current time

    // If the LEDs haven't been turned on yet, turn them all on
    if (initialLedsOn) {
        setAllLeds();            // Turn all LEDs on
        delay(1000);             // Optional: keep them on for 1 second
        initialLedsOn = false;   // Indicate that the LEDs are now initialized
        previousMillis2 = currentMillis; // Reset the timing
        return;
    }

    // Check if the interval has passed
    if (currentMillis - previousMillis2 >= delayTime) {
        previousMillis2 = currentMillis; // Save the current time

        byte randomLed = random(0, 4); // Pick a random LED
        setLed(randomLed);

        currentRound++;

        // If the currentRound reaches the number of rounds, reset
        if (currentRound >= rounds) {
            clearAllLeds(); // Turn off all LEDs
            currentRound = 0;
            cycleCount++; // Increase the cycle count

            // Increase speed after 10 cycles
            if (cycleCount >= 10 && delayTime > 200) {
                interval -= 100;
            }

            // Reset the interval and cycleCount after 20 cycles
            if (cycleCount > 20) {
                cycleCount = 0;
                interval = 500; // Reset to original speed
            } 
        }
    }
}
