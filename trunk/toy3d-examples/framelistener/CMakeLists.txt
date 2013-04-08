
if (WIN32)
    set(PLATFORM_LIBS GLEW32 GLUT32)
elseif (APPLE)

elseif (UNIX)
    set(PLATFORM_LIBS m GLEW)
endif(WIN32)


set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${PLATFORM_LIBS})


add_executable (framelistener framelistener.cpp myapp.cpp)
target_link_libraries (framelistener toy3d ${CORELIBS})


install (TARGETS framelistener 
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/toy3d/framelistener)

