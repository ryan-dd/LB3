add_library(LB3 
    model/Direction.cpp 
    model/Arena.cpp 
    view/GameSession.cpp 
    view/GameEventHandler.cpp 
    view/GameRenderer.cpp 
    view/GameStartParameters.cpp 
    view/PlayerInputInfo.cpp 
    util/Logger.cpp 
    util/RandomIntGenerator.cpp 
    util/ArenaCoordinateGenerator.cpp 
)

target_include_directories(LB3 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/model/
    ${CMAKE_CURRENT_SOURCE_DIR}/view/
    ${CMAKE_CURRENT_SOURCE_DIR}/util/
)

find_package(Curses REQUIRED)

target_link_libraries (LB3 ${CURSES_LIBRARIES})

add_executable(main main.cpp)
target_link_libraries(main LB3)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/main 
        DESTINATION ${CMAKE_BINARY_DIR}/bin)