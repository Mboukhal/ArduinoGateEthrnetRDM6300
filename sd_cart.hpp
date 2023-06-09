#pragma once

#include "request.hpp"
#include <SD.h>

#define SD_CART 4
#define LOG_FILE "log.csv"

void initSdCart();

void parseURL(String& hostname, String& uri, int& port);

void logData(const String& dataTime, const String& id, const String& state);