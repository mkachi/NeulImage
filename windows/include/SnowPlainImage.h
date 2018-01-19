#pragma once

#include "SPSubModule.h"

extern "C" SP_SM bool loadPng(const char* name, int& outWidth, int& outHeight, bool& outHasAlpha, unsigned char** outData);