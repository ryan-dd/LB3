add_library(LightPuzzle 
    model/Direction.cpp 
    model/Arena.cpp 
    view/GameSession.cpp 
    view/GameEventHandler.cpp 
    view/GameRenderer.cpp 
)

target_include_directories(LightPuzzle PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/model/
    ${CMAKE_CURRENT_SOURCE_DIR}/view/
    ${CMAKE_CURRENT_SOURCE_DIR}/util/
)

find_package(Curses REQUIRED)

target_link_libraries (LightPuzzle ${CURSES_LIBRARIES})

add_executable(main main.cpp)
target_link_libraries(main LightPuzzle)