include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.8.0
)
    
FetchContent_MakeAvailable(googletest)
    
add_executable(integration_tests IntegrationTest.cpp)
target_link_libraries(integration_tests PUBLIC gtest_main)

add_test(integration_tests tests) 
