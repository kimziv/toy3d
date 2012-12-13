
cmake_minimum_required(VERSION 2.8)
PROJECT (TOY3D-EXAMPLES)

if(NOT CMAKE_BUILD_TYPE)
	SET (CMAKE_BUILD_TYPE "RelWithDebInfo")
ENDIF()


#SET( GLES "YES" )

add_definitions(-DOPENGL)


if (NOT GLES)

find_package(GLUT)
find_package(OpenGL)


ADD_SUBDIRECTORY(rectangle)
ADD_SUBDIRECTORY(triangle)


else ()


endif()










