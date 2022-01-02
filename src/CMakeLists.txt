cmake_minimum_required(VERSION 3.22)
project(Matrix_Operations)
set(APP_EXE Test)

add_library(Matrix_Operations STATIC matrix_operators.c)
add_executable(${APP_EXE} main.c)
target_link_libraries(${APP_EXE} Matrix_Operations)
install(TARGETS Matrix_Operations DESTINATION lib)