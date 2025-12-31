add_subdirectory(external/cpptotp)
add_subdirectory(external/cpp-base32)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE cppotp)
target_link_libraries(myapp PRIVATE cpp-base32)