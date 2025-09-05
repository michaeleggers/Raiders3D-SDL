cmake_minimum_required(VERSION 3.6)

project(Raiders3D)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# see: https://github.com/libsdl-org/SDL/issues/7267
set(SDL2_IMAGE_INSTALL OFF)
set(SDL2_DISABLE_INSTALL OFF)
add_subdirectory(./ThirdParty/SDL2-2.32.8/)
add_subdirectory(./ThirdParty/SDL2_image-2.6.0/)

add_executable(Raiders3D 
	src/main.cpp
	src/GraphicsCore.cpp
	src/InputCore.cpp
	src/Sprite.cpp 
	src/SpriteSheet.cpp
	src/GameState.cpp
	src/GameObject.cpp
	src/BitmapFont.cpp
	inc/GraphicsCore.h
	inc/InputCore.h
	inc/Sprite.h 
	inc/SpriteSheet.h
	inc/GameState.h
	inc/GameObject.h
	inc/BitmapFont.h
	inc/common.h
	)

target_link_libraries(Raiders3D PUBLIC
	SDL2::SDL2
	SDL2_image::SDL2_image
)

target_compile_options(Raiders3D PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_options(Raiders3D PRIVATE -Wno-unused-variable)
target_compile_options(Raiders3D PRIVATE -Wno-unused-parameter)
target_compile_options(Raiders3D PRIVATE -Wno-extra-semi)
target_compile_options(Raiders3D PRIVATE -Wno-newline-eof)
target_compile_options(Raiders3D PRIVATE -fms-extensions)
target_compile_options(Raiders3D PRIVATE -Wno-nested-anon-types)
target_compile_options(Raiders3D PRIVATE -Wno-gnu-anonymous-struct)
target_compile_options(Raiders3D PRIVATE -Wno-gnu-zero-variadic-macro-arguments)

