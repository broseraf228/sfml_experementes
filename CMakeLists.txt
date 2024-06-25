cmake_minimum_required(VERSION 3.16)
project(bexperem LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME}
				src/main.cpp
				src/constants.hpp
				src/constants.cpp
				src/screen/Screen.hpp
				src/screen/Screen.cpp
				src/screen/tile_atlas.hpp
				src/screen/tile_atlas.cpp
				src/events/Events.hpp
				src/events/Events.cpp
				src/game/Game.hpp
				src/game/Game.cpp
				src/game/World.hpp
				src/game/World.cpp
				src/resource_manager/ResourceManager.hpp
				src/resource_manager/ResourceManager.cpp
				src/other/math.hpp
				src/other/math.cpp

				)
				
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)