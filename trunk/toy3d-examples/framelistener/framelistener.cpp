
#include <toy3d/Toy3DCommon.h>
#include <toy3d/Toy3DWorld.h>
#include <toy3d/Toy3DEntity.h>
#include <toy3d/Toy3DMesh.h>
#include <toy3d/Toy3DMaterial.h>
#include <toy3d/Toy3DShaderProgramParams.h>
#include <toy3d/Toy3DShaderProgramManager.h>
#include <toy3d/Toy3DMeshManager.h>
#include <toy3d/Toy3DMaterialManager.h>
#include <toy3d/Toy3DRenderWindow.h>


#include "myapp.h"
#include "user_data.h"

using namespace TOY3D;
MyApp *myApp = NULL;


void display()
{

    myApp->startRendering(); 

	glFlush();
    glutSwapBuffers ();
}

void changeSize( int w, int h ) 
{
    myApp->changeWindowSize(w, h);
    return;
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'q':
    case 'Q':
    case 27:
        DELETEANDNULL(myApp);
        exit(0);

    case 'p':
    case 'P':
    case 26:
        //myApp->mWorld->rotate (0.0f, angle_y, 0.0f);
        //angle_y += 10;
        break;

    default:
        DELETEANDNULL(myApp);
        exit(0);
    }
    
    return;
}


int main(int argc, char** argv){

	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  	glutInitWindowSize(WINDOW_W, WINDOW_H);
  	glutInitWindowPosition(0,0);
  	glutCreateWindow("Renctangle");
  	glutDisplayFunc(display);
	glutIdleFunc(display);
    glutReshapeFunc(changeSize);
  	glutKeyboardFunc(keyboard);


    glewInit();
    if (glewIsSupported("GL_VERSION_2_0"))
        printf("Ready for OpenGL 2.0\n");
    else {
        printf("OpenGL 2.0 not supported\n");
        exit(1);
    }

  	myApp = new MyApp();
    myApp->createScene();

  	glutMainLoop();

    DELETEANDNULL(myApp);

  	return 0;
}


