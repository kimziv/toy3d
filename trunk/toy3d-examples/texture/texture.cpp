
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

World *world = NULL;
Texture *texture = NULL;


unsigned char* generateColorData(int w, int h, int *length)
{
    unsigned char *buf = NULL;
    int i = 0, j = 0, ww, hh, _w = w, _h = h;
    {
        ww = 2;
        while((_w /= 2) > 0)ww *= 2;
        hh = 2;
        while((_h /= 2) > 0)hh *= 2;
    }
    *length = ww*hh*2;
    buf = (unsigned char *)malloc(ww*hh*2);
    if( !buf )
        return 0;
    memset(buf, 255, ww*hh*2);
    
    for(i = 0; i < h; i ++)
    {
        for(j = 0; j < w; j++)
        {
            *(buf+i*ww*2+j*2) = 255;
            *(buf+i*ww*2+j*2 + 1) = i%256;
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

bool init()
{

    world = new World ();
    world->setSize(WINDOW_W, WINDOW_H);
    world->setBackColor (1.0, 1.0, 1.0, 1.0);  //white back color


    ShaderProgram* shaderProgram = world->createShaderProgram();
    shaderProgram->loadShaderSource (SHADER_VERT_FILE, SHADER_FRAG_FILE);
    printf("shaderProgram id: %d\n", shaderProgram->getShaderProgramID());


    ShaderProgramParams *params = new ShaderProgramParams ();
    //no shader uniforms ...
    //Need to add a kind of custom variable.

    //shader attributes
    params->setNamedAttrConstant(TOY3D_ATTR_VERTEX_INDEX, "vPosition");
    params->setNamedAttrConstant(TOY3D_ATTR_UV_INDEX, "vTexture");
    shaderProgram->bindShaderParameters(params);

    Mesh *mesh = world->createMesh();
    mesh->setVertices (vertices, VERTEX_COUNT);
    mesh->setRenderMode (TOY3D_TRIANGLE_STRIP);
    mesh->setUVs( uvs, VERTEX_COUNT);

    int texid;
#if 1
    // need to delete by yourself
    texture = TextureManager::getInstance()->createTextureByFile(TEXTURE_FILE);
    if( !texture )
    {
    printf("create texture failed.\n");
    return false;
    }
#endif

#if 0
    unsigned char *buf;
    int length;
    buf = generateColorData(WINDOW_W, WINDOW_H, &length);
    if( !buf )
        return false;
    texture = TextureManager::getInstance()->createTexture(buf, length);
    if( !texture )
    {
        printf("create texture failed.\n");
        return false;
    }
    if(buf)
        FREEANDNULL(buf);
#endif

    texid = texture->getTextureID();
    printf("texid = %d\n", texid);
    mesh->setTextureID(texid);

    unsigned int sampler2d = glGetUniformLocation( shaderProgram->getShaderProgramID(), "sampler2d");
    glUniform1i(sampler2d, 0); // pass in texture

    return true;
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
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  	glutInitWindowSize(WINDOW_W, WINDOW_H);
  	glutInitWindowPosition(0,0);
  	glutCreateWindow("triangle");
  	glutDisplayFunc(display);
	glutIdleFunc(display);
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

    //delete world;
    //delete texture;

  	return 0;
}


