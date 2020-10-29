cmake_minimum_required(VERSION 3.13)
project(projeto C)

set(CMAKE_C_STANDARD 99)

add_executable(projeto main.c estado.c interpretador.c estado.h interpretador.h bot.c bot.h stack.c stack.h interpretadorBOT.c interpretadorBOT.h COMUNS.h COMUNS.c)