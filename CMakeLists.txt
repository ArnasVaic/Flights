cmake_minimum_required (VERSION 3.22.0)
project (Flights)
file(GLOB SOURCE "src/*.c")
add_executable (${PROJECT_NAME} ${SOURCE})
include_directories("include/")
# temporary
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "a")