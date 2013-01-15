
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
ADD_SUBDIRECTORY(testDataStruct)



else ()


endif()










