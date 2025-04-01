//
// Created by Norberto Studios on 3/26/25.
//

#include "logger.h"

// Path to the log file on SPIFFS
const char *LOG_FILE = "/logs.txt"; // Define LOG_FILE

// Function to log a message to Serial and append it to SPIFFS log file.
void logMessage(const String &message) {
    // Print to Serial
    Serial.println(message);

    // // Open the log file in append mode.
    // File logFile = SPIFFS.open(LOG_FILE, FILE_APPEND);
    // if (logFile) {
    //     // Append the message with a newline.
    //     logFile.println(message);
    //     logFile.close();
    // } else {
    //     Serial.println("Error opening log file for appending.");
    // }
}

void heartbeat() {
    static unsigned long lastBeat = 0;
    if (millis() - lastBeat > 30000) {
        logMessage("Heartbeat: " + String(millis()/1000) + " seconds elapsed.");
        lastBeat = millis();
    }
}