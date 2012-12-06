
cmake_minimum_required(VERSION 2.8)
PROJECT (TOY3D)

if(NOT CMAKE_BUILD_TYPE)
	SET (CMAKE_BUILD_TYPE "RelWithDebInfo")
ENDIF()


#SET( GLES "YES" )

#add_definitions(-DMAC)
add_definitions(-DVC6)
add_definitions(-DOPENGL)


if (NOT GLES)

find_package(GLUT)
find_package(OpenGL)


ADD_SUBDIRECTORY(source)


else ()


endif()










