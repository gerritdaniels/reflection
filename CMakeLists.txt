
project(reflection)

add_executable(test test/test.cpp)
target_include_directories(test PUBLIC include)
target_link_libraries(test boost_serialization)
set_property(TARGET test PROPERTY CXX_STANDARD 14)
