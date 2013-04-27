
if (WIN32)
    set(PLATFORM_LIBS GLEW32 GLUT32)
elseif (APPLE)

elseif (UNIX)
    set(PLATFORM_LIBS m GLEW)
endif(WIN32)


set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${PLATFORM_LIBS})


add_executable (fbo_mini_screen fbo_mini_screen.cpp fbo_mini_app.cpp)
target_link_libraries (fbo_mini_screen toy3d ${CORELIBS})


install (TARGETS fbo_mini_screen 
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/toy3d/fbo_mini_screen)

