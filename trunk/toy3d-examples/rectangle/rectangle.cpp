
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>



#include <toy3d/Toy3DCommon.h>
#include <toy3d/Toy3DWorld.h>
#include "data.h"


#define WINDOW_W    500
#define WINDOW_H    500

using namespace TOY3D;

World *world = NULL;


void display()
{

    world->startRendering (); 

	glFlush();
}

void init()
{

    world = new World ();
    world->setMesh ();


}

void keyboard(unsigned char key, int x, int y){
  switch(key) {
    case 'q': case 'Q': case 27:
      exit(0);
      break;
  }
}

int main(int argc, char** argv){

	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(WINDOW_W, WINDOW_H);
  	glutInitWindowPosition(0,0);
  	glutCreateWindow("renctangle");
  	glutDisplayFunc(display);
	glutIdleFunc(display);
  	glutKeyboardFunc(keyboard);
  	init();
  	glutMainLoop();

  	return 0;
}


