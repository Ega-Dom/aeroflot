cmake_minimum_required(VERSION 3.5)
project(aeroflot CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(aeroflot
    main.cpp AEROFLOT.cpp FlightList.cpp TextProcessor.cpp
    Exceptions.cpp Input.cpp)
