
cmake_minimum_required(VERSION 2.8)
PROJECT (TOY3D-EXAMPLES)

if(NOT CMAKE_BUILD_TYPE)
	SET (CMAKE_BUILD_TYPE "RelWithDebInfo")
ENDIF()



if (WIN32)

add_definitions(-DVC6)
    
elseif (APPLE)

elseif (UNIX)
    
endif(WIN32)


#SET( GLES "YES" )

add_definitions(-DOPENGL)


if (NOT GLES)

find_package(GLUT)
find_package(OpenGL)


ADD_SUBDIRECTORY(triangle)
ADD_SUBDIRECTORY(rectangle)
ADD_SUBDIRECTORY(multi_rect)
ADD_SUBDIRECTORY(texture)
#ADD_SUBDIRECTORY(testDataStruct)
ADD_SUBDIRECTORY(blending)
#ADD_SUBDIRECTORY(textureCapacityTest)
ADD_SUBDIRECTORY(multi_texture)
#ADD_SUBDIRECTORY(imageviewer)
ADD_SUBDIRECTORY(framelistener)
ADD_SUBDIRECTORY(fbo)
ADD_SUBDIRECTORY(fbo_mini_screen)
ADD_SUBDIRECTORY(fbo_map)


else ()


endif()










