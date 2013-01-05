
// #include <GL/glew.h>
// #include <GL/glut.h>


#include <toy3d/Toy3DCommon.h>
#include <toy3d/Toy3DWorld.h>
#include <toy3d/Toy3DShaderProgramParams.h>


#define WINDOW_W    800
#define WINDOW_H    600


#ifdef VC6
#define SHADER_VERT_FILE "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/multi_rect/rect.glslv"
#define SHADER_FRAG_FILE "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/multi_rect/rect.glslf"
#else
#define SHADER_VERT_FILE "/usr/local/share/toy3d/multi_rect/rect.glslv"
#define SHADER_FRAG_FILE "/usr/local/share/toy3d/multi_rect/rect.glslf"
#endif


using namespace TOY3D;

#define VERTEX_COUNT  6


//global
World *world = NULL;
Camera *camera = NULL;
ShaderProgram* shaderProgram;
ShaderProgramParams *params = NULL;
Mesh *mesh_left, *mesh_right;



Real vertices[VERTEX_COUNT * 3] = {
    -1.0f, -1.0f, 0.0f,
    1.0f,  -1.0f, 0.0f,
    -1.0f, 1.0f,  0.0f,
    
    1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f
};

void display()
{

    world->startRendering (); 

	glFlush();
    glutSwapBuffers ();
}


void changeSize( int w, int h ) 
{
    Real aspect, fovy;
    Real nearz  = 1.0f;//5.0f;
    Real farz   = 1000.0f;//60.0f;

    world->setSize(w, h);

    aspect = 1.0 * w / h;
    fovy = 60;
    camera->perspective (fovy, aspect, nearz, farz);
    camera->lookAt (0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  
    return;
}



Bool init()
{
    int   texUnit = 0;
    //Real aspect, fovy;
    const Real nearz  = 1.0f;//5.0f;
    const Real farz   = 1000.0f;//60.0f;

    world = new World ();
    world->setSize(WINDOW_W, WINDOW_H);
    world->setBackColor (1.0, 1.0, 0.0, 1.0);

    camera = world->createCamera ("camera1");

    shaderProgram = new ShaderProgram();
    shaderProgram->loadShaderSource (SHADER_VERT_FILE, SHADER_FRAG_FILE);

    params = new ShaderProgramParams ();
    //uniforms
    params->setNamedAutoConstant (TOY3D_ACT_PROJECTION_MATRIX, "proj_mat");
    params->setNamedAutoConstant (TOY3D_ACT_VIEW_MATRIX, "view_mat");
    params->setNamedAutoConstant (TOY3D_ACT_WORLD_MATRIX, "world_mat");

    //attributes
    params->setNamedAttrConstant (TOY3D_ATTR_VERTEX, "vPosition");
    //shader custom constant
    params->setNamedCustUniformConstant(TOY3D_CUST_SAMPLER2D, "sampler2d", texUnit);

    shaderProgram->bindShaderParameters(params);

    //Entity
    Entity *entity1 = world->createEntity();
    //Mesh *mesh_left = entity1->createMesh();
    mesh_left = new Mesh();
    if( !mesh_left )
    {
        TOY3D_TIPS("Failed to create mesh.\n");
        return FALSE;
    }
    mesh_left->setVertices (vertices, VERTEX_COUNT);
    mesh_left->setRenderMode (TOY3D_TRIANGLE_STRIP);
    entity1->setMesh(mesh_left);
    entity1->translate (-3.0, 0.0, 0.0);
    entity1->rotate (0.0, 30.0, 0.0);


    Entity *entity2 = world->createEntity();
    //mesh_right = entity2->createMesh();
    mesh_right = new Mesh();
    if( !mesh_right )
    {
        TOY3D_TIPS("Failed to create mesh.\n");
        return FALSE;
    }
    mesh_right->setVertices (vertices, VERTEX_COUNT);
    mesh_right->setRenderMode(TOY3D_TRIANGLE_STRIP);
    entity2->setMesh(mesh_right);
    entity2->translate (3.0, 0.0, 0.0);
    entity2->rotate (0.0, -30.0, 0.0);

    Material *mat = entity1->createMaterial();
    mat->setShaderProgram (shaderProgram);

    mat = entity2->createMaterial();
    mat->setShaderProgram (shaderProgram);

    return TRUE;
}

Real angle_y = 0.0f;

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'q':
    case 'Q':
    case 27:
        printf("pointer world: %d.\n", world);
        DELETEANDNULL(world);
        DELETEANDNULL(mesh_left);
        DELETEANDNULL(mesh_right);
        DELETEANDNULL(shaderProgram);
        DELETEANDNULL(params);
        camera = NULL;

        exit(0);
        
    case 'p':
    case 'P':
    case 26:
        world->rotate (0.0f, angle_y, 0.0f);
        angle_y += 10;
        break;
    }
    
    return;
}


int main(int argc, char** argv)
{
    Bool rvb;

	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  	glutInitWindowSize(WINDOW_W, WINDOW_H);
  	glutInitWindowPosition(0,0);
  	glutCreateWindow("renctangle");
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



  	rvb = init();
    if( FALSE==rvb )
        return 0;
  	glutMainLoop();

  	return 0;
}


