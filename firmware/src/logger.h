//
// Created by Norberto Studios on 3/26/25.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <SPIFFS.h>

extern const char *LOG_FILE;  // Declare LOG_FILE globally

void logMessage(const String &message);
void heartbeat();

#endif //LOGGER_H
