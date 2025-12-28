add_subdirectory(external/cpptotp)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE cppotp)