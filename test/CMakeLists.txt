enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.8.0
)
    
FetchContent_MakeAvailable(googletest)
    
add_executable(unit_tests 
    VectorTest.cpp
)
target_link_libraries(unit_tests 
    gtest_main 
    LB3
)

include(GoogleTest)
gtest_discover_tests(unit_tests)