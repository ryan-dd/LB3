add_library(LightPuzzle 
    model/Arena.cpp 
    model/obstacles/Mirror.cpp 
    model/Direction.cpp 
    model/Player.cpp 
    view/GameSession.cpp 
)

target_include_directories(LightPuzzle PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/model/
    ${CMAKE_CURRENT_SOURCE_DIR}/view/
    ${CMAKE_CURRENT_SOURCE_DIR}/model/obstacles
)

find_package(Curses REQUIRED)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
target_link_libraries (LightPuzzle Eigen3::Eigen ${CURSES_LIBRARIES})

add_executable(main main.cpp)
target_link_libraries(main LightPuzzle)