
if (WIN32)
    set(PLATFORM_LIBS GLEW32 GLUT32)
elseif (APPLE)

elseif (UNIX)
    set(PLATFORM_LIBS m GLEW)
endif(WIN32)


set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${PLATFORM_LIBS})


add_executable (texture texture.cpp)
target_link_libraries (texture toy3d ${CORELIBS})


install (TARGETS texture 
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/toy3d/texture)

