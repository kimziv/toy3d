
// #include <GL/glew.h>
// #include <GL/glut.h>


#include <toy3d/Toy3DCommon.h>
#include <toy3d/Toy3DWorld.h>
#include <toy3d/Toy3DShaderProgramParams.h>
#include <toy3d/Toy3DTexture.h>
#include <toy3d/Toy3DTextureManager.h>


#define WINDOW_W    500
#define WINDOW_H    500


#ifdef VC6
#define SHADER_VERT_FILE "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/texture/texture.glslv"
#define SHADER_FRAG_FILE "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/texture/texture.glslf"
#define TEXTURE_FILE     "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/texture/leaf.tga"
#else 
#define SHADER_VERT_FILE "/usr/local/share/toy3d/texture/texture.glslv"
#define SHADER_FRAG_FILE "/usr/local/share/toy3d/texture/texture.glslf"
#define TEXTURE_FILE     "/usr/local/share/toy3d/texture/leaf.tga"
#endif


using namespace TOY3D;

#define VERTEX_COUNT 6


//global
World *world = NULL;
Mesh  *mesh;
Camera *camera = NULL;
ShaderProgram* shaderProgram;
ShaderProgramParams *params = NULL;
//Texture *texture = NULL;


Real vertices[VERTEX_COUNT * 3] = {
    -1.0f, -1.0f, 0.0f,
    1.0f,  -1.0f, 0.0f,
    -1.0f, 1.0f,  0.0f,

    1.0f,  1.0f,  0.0f,
    1.0f,  -1.0f, 0.0f,
    -1.0f, 1.0f,  0.0f
};

Real uvs[VERTEX_COUNT * 2] = {
    0.0f,0.0f, 1.0f,0.0f, 0.0f,1.0f,
    1.0f,1.0f, 1.0f,0.0f, 0.0f,1.0f
};

//Bpp muset be 3 or 4.
unsigned char* generateColorData(int w, int h, int bpp)
{
    unsigned char *buf = NULL;
    int length, i, j, c;

    length = w * h * bpp;
    buf = (unsigned char *)malloc(length);
    if( !buf )
        return 0;
    memset(buf, 0, length);
    
    for(i = 0; i < h; i ++)
    {
        for(j = 0; j < w; j++)
        {
            c = ( ((i&0x8)==0) ^ ((j&0x8)==0) ) * 255;
            *(buf+i*h*bpp+j*bpp) = (Uchar)c;
            *(buf+i*h*bpp+j*bpp + 1) = (Uchar)c;
            *(buf+i*h*bpp+j*bpp + 2) = (Uchar)c;
            if(bpp==BPP_4)
                *(buf+i*h*bpp+j*bpp + 3) = (Uchar)255;
        }
        //memset(buf+i*ww, i%256, w);
    }

    return buf;
}


void display()
{

    world->startRendering (); 

	glFlush();
    glutSwapBuffers();
}

void changeSize( int w, int h ) 
{
    Real aspect, fovy;
    Real nearz  = 1.0f;//5.0f;
    Real farz   = 1000.0f;//60.0f;
    
    world->setSize(w, h);

    camera->lookAt (0.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    aspect = 1.0 * w / h;
    fovy = 60;
    camera->perspective (fovy, aspect, nearz, farz);
    
    return;
}


bool init()
{
    int   width = WINDOW_W, height = WINDOW_H;
    //int   texid;
    Bool  rvb;
    int   texUnit = 0;
    Real  limit;
    Material *mat;
    Entity *entity;

    world = new World ();
    printf("pointer world: %d.\n", world);
    world->setSize(width, height);
    world->setBackColor (1.0, 0.0, 1.0, 1.0);

    camera = world->createCamera ("camera1");
    entity = world->createEntity();
    mat = entity->createMaterial ();

    shaderProgram = new ShaderProgram();
    params = new ShaderProgramParams ();

    //shader
    shaderProgram->loadShaderSource (SHADER_VERT_FILE, SHADER_FRAG_FILE);
    printf("shaderProgram id: %d\n", shaderProgram->getShaderProgramID());

    //shader auto constant
    params->setNamedAutoConstant (TOY3D_ACT_PROJECTION_MATRIX, "proj_mat");
    params->setNamedAutoConstant (TOY3D_ACT_VIEW_MATRIX, "view_mat");
    params->setNamedAutoConstant (TOY3D_ACT_WORLD_MATRIX, "world_mat");
    //params->setNamedAutoConstant (TOY3D_ACT_SAMPLER2D, "sampler2d");

    //shader attributes
    params->setNamedAttrConstant(TOY3D_ATTR_VERTEX, "vPosition");
    params->setNamedAttrConstant(TOY3D_ATTR_UV, "vTexture");

    //shader custom constant
    limit = 1.0f;
    printf("limit = %f.\n", limit);
    params->setNamedCustUniformConstant(TOY3D_CUST_REAL1, "limit", limit);
    params->setNamedCustUniformConstant(TOY3D_CUST_SAMPLER2D, "sampler2d", texUnit);

    shaderProgram->bindShaderParameters(params);

    //Entity
    mesh = new Mesh();
    mesh->setRenderMode (TOY3D_TRIANGLE_STRIP);
    mesh->setVertices (vertices, VERTEX_COUNT);
    mesh->setUVs( uvs, VERTEX_COUNT);
    entity->setMesh(mesh);

    //texture
    rvb = mat->loadTexture(TEXTURE_FILE);
    if(FALSE == rvb)
    {
        printf("create texture failed.\n");
        return false;
    }
    mat->setShaderProgram (shaderProgram);
    //mat->setTexture(texture);

    /*
    //another way to create texture
    unsigned char *buf;
    int  bpp = BPP_3;
    int  imageW = 64;
    int  imageH = 64;
    buf = generateColorData(imageW, imageH, bpp);
    if( !buf )
        return false;
    texture = mat->createTexture(buf, imageW, imageH, bpp);
    if( !texture )
    {
        printf("create texture failed.\n");
        return false;
    }
    if(buf)
        FREEANDNULL(buf);
    */

    return true;
}

Real angle_y = 0.0f;

void keyboard(unsigned char key, int x, int y){
    switch(key)
    {
    case 'q':
    case 'Q':
    case 27:
        /*
        unsigned int texid;
        if( texture )
        {
            texid = texture->getTextureID();
            TextureManager::getInstance()->deleteTexture(&texid, 1);
        }
        DELETEANDNULL(texture);
        */

        DELETEANDNULL(world);
        DELETEANDNULL(mesh);
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
}

int main(int argc, char** argv){

	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  	glutInitWindowSize(WINDOW_W, WINDOW_H);
  	glutInitWindowPosition(0,0);
  	glutCreateWindow("texture");
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

    bool rv;
  	rv = init();
    if(rv==false)
        return 0;

  	glutMainLoop();


  	return 0;
}


