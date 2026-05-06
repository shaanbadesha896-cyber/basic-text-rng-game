#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <algorithm>
#include <cstdlib> 

extern int slowdown1;

void slowdown(int slow);
int randomint(int min, int max);
void typewrite(const std::string& text, int delay_ms);