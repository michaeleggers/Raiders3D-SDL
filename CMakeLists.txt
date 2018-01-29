cmake_minimum_required(VERSION 3.6)

project(Barbecue)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
#set(SDL2_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2-2.0.5")

set(SDL2_IMAGE_LIBRARY "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2_image-2.0.2/lib/x64/SDL2_image.lib")
set(SDL2_IMAGE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2_image-2.0.2/include")

set(SDL2_LIBRARY "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2-2.0.7/lib/x64/*.lib")
set(SDL2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2-2.0.7/include")

#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)

## executable target


## ! executable target

include_directories(${SDL2_INCLUDE_DIR} 
                    ${SDL2_IMAGE_INCLUDE_DIR}
                     )

set(SDL2_IMAGE_LIBRARIES ${SDL2_IMAGE_LIBRARY}
                        )
set(SDL2_LIBRARIES ${SDL2_LIBRARY}	
)

add_executable(Barbecue 
	src/main.cpp
	src/GraphicsCore.cpp
	src/InputCore.cpp
	src/Sprite.cpp 
	src/SpriteSheet.cpp
	src/GameState.cpp
	src/GameObject.cpp
	src/BitmapFont.cpp
	src/TileMap.cpp
	inc/GraphicsCore.h
	inc/InputCore.h
	inc/Sprite.h 
	inc/SpriteSheet.h
	inc/GameState.h
	inc/GameObject.h
	inc/BitmapFont.h
	inc/TileMap.h
	inc/common.h
	)

source_group("resources" FILES ${RESOURCES})
target_link_libraries(Barbecue ${SDL2_IMAGE_LIBRARIES}
							   ${SDL2_LIBRARIES}
							   )
