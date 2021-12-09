add_library(LightPuzzle 
    model/Arena.cpp 
    model/obstacles/Mirror.cpp 
    model/Direction.cpp 
    model/Agent.cpp 
    view/GameSession.cpp 
)

target_include_directories(LightPuzzle PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/model/
    ${CMAKE_CURRENT_SOURCE_DIR}/view/
    ${CMAKE_CURRENT_SOURCE_DIR}/model/obstacles
)

find_package(Curses REQUIRED)

target_link_libraries (LightPuzzle ${CURSES_LIBRARIES})

add_executable(main main.cpp)
target_link_libraries(main LightPuzzle)