cmake_minimum_required(VERSION 3.15)
project(TrabalhoAEDs)

set(CMAKE_BUILD_TYPE Debug)

add_executable(
    main
    main.cpp
    manip_udados.hpp
    manip_udados.cpp
    operacoes.hpp
    menu.hpp
)