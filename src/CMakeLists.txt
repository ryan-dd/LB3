add_library(LB3 
    GameSession.cpp 
    logic/GameEventHandler.cpp 
    rendering/GameRenderer.cpp 
    data/GameStartParameters.cpp 
    data/game/Direction.cpp 
    data/game/Arena.cpp 
    data/ui/PlayerInputInfo.cpp 
    data/ui/GameColor.cpp 
    util/Logger.cpp 
    util/RandomIntGenerator.cpp 
    util/ArenaCoordinateGenerator.cpp 
)

target_include_directories(LB3 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/data/
    ${CMAKE_CURRENT_SOURCE_DIR}/data/game
    ${CMAKE_CURRENT_SOURCE_DIR}/data/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/logic/
    ${CMAKE_CURRENT_SOURCE_DIR}/rendering/
    ${CMAKE_CURRENT_SOURCE_DIR}/util/
)

find_package(Curses REQUIRED)

target_link_libraries (LB3 ${CURSES_LIBRARIES})

add_executable(main main.cpp)
target_link_libraries(main LB3)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/main 
        DESTINATION ${CMAKE_BINARY_DIR}/bin)