#pragma once

#include <map>
#include <string>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <chrono>
#include <vector>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <stdint.h>

#ifndef _WIN32
    #include <unistd.h>
#endif // _WIN32

#include "logyapi.h"
