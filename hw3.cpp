#include <string>
#include <iostream>
#include <math.h>
#include <GL/gl.h>   
#include <GL/glut.h>
#include "SOIL.h"
#include "glinit.h"
#include "utils.h"
#include "glentry.h"

// In order to handle the error mentioned for HW2.
#include <pthread.h>
void junk() {
  int i;
  i=pthread_getconcurrency();
};

using namespace std;


GLuint gProgramCubeMap;					// program handler of the cube map with two attached shaders: CubeMap.vert, CubeMap.frag

GLuint gTextureCubeMap;					// texture handler for the cube map. 

GLuint gVerticesVBO, gIndicesVBO;		// Vertex Buffer Objects for the cubemap's indices and vertices.

GLfloat gDispLevel = 0;					// displacement level for the height map. Can be passed to the shader source
GLuint gProgramEarth;
GLuint gTextureHeightMap;
GLuint gTextureColorMap;
GLuint gEarthVerticesVBO, gEarthIndicesVBO,gEarthTexCoordsVBO,normalVBO;
float radius;
int   num_lon;
int   num_lat;

// Camera's properties
float gCamAngle = 0.0f;
float gCamDirX  = 0.0f;
float gCamDirZ  = 0.0f;
float gCamDist  = 5.0f;

// Earth's properties
float gEarthAngle	 = 0.0f;			// rotation angle of the Earth around its own axis
float gEarthAngleSun = 0.0f;			// rotation angle of the Earth around Sun
float gEarthPosX     = 0.0f;
float gEarthPosZ     = -1.0f;

void reshape(int w, int h) 
{
    w = w < 1 ? 1 : w;
    h = h < 1 ? 1 : h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(45, double(w)/h, 0.1f, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
		
void mouse(int button, int state, int x, int y)
{
    if (button == 3 && state == GLUT_UP)		 	// mouse wheel down
   		gCamDist -= 0.1f;
	else if (button == 4 && state == GLUT_UP)    	// mouse wheel up
    	gCamDist += 0.1f;
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key) 
    {
        case 27:	// Escape
            exit(0); 
            break; 
        case 'a' :	// rotate camera around the Earth clockwise
			gCamAngle -= 0.01f;
			break;
		case 'd' :	// rotate camera around the Earth counterclockwise
			gCamAngle += 0.01f;
			break;
		case '-':	// decrease displacement level of the height map
			gDispLevel -= 0.01f;
			break;
		case '+':	// increase displacement level of the height map
			gDispLevel += 0.01f;
			break;
        default:  
            break;
    }
}

void init(int *argc, char** argv) 
{
    glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glShadeModel(GL_SMOOTH);
	
	initTextures();
    initShaders();      
    
	if (*argc < 3) {
		cout << "Missing argument(s)." << endl 
			 << "Usage: ./hw3 <# of Latitudes> <# of Longitudes> <radius of the Earth>" << endl;
			 
		exit(0);	
	}
	
	// initialize Cubemap
	initCubeMap(&gVerticesVBO, &gIndicesVBO);
    
	// read command line arguments
	radius  = atof(argv[--*argc]);
	num_lon = atoi(argv[--*argc]);
	num_lat = atoi(argv[--*argc]);
		
    // TODO: initialize the Earth.
     initEarthMap(&gEarthVerticesVBO, &gEarthIndicesVBO,&gEarthTexCoordsVBO,&normalVBO,radius,num_lon,num_lat);
}

void display()
{	
    long startTime = getCurrentTime();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	
	glLoadIdentity();
	
	// calculations for the position of the Earth
	gEarthAngleSun += 0.002739f;
	gEarthPosX = sin(gEarthAngleSun) * 50;
	gEarthPosZ = cos(gEarthAngleSun) * 50;

	// calculations for the position and view direction of the camera
	gCamDirX = sin(gCamAngle);
	gCamDirZ = cos(gCamAngle);

	gluLookAt(gEarthPosX + gCamDirX*gCamDist, 0, gEarthPosZ + gCamDirZ*gCamDist, 
			  gEarthPosX                    , 0, gEarthPosZ, 
			  0.0f						    , 1, 0.0f);        
	
	// Stars -- Cubemap
	glPushMatrix();
		glScalef(300,100,300);
		glUseProgram(gProgramCubeMap);
		
		glBindBuffer(GL_ARRAY_BUFFER, gVerticesVBO);
		glVertexPointer(3, GL_FLOAT, sizeof(float) * 3, 0);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndicesVBO);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT,  0);
	glPopMatrix();
		
	// Earth
	glPushMatrix();
		GLfloat matrix[16]; 
		glGetFloatv (GL_MODELVIEW_MATRIX, matrix);
		gEarthAngle += 1;
		glTranslatef(gEarthPosX, 0, gEarthPosZ);
		glRotatef(23.5f, 0, 0, 1);
		glRotatef(gEarthAngle, 0, 1, 0);
		
		// TODO: Display the Earth	
		glUseProgram(gProgramEarth);
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, gEarthVerticesVBO);
		glVertexPointer(3, GL_FLOAT, 0, 0);
	
		glEnableClientState(GL_NORMAL_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
		glNormalPointer(GL_FLOAT, 0, 0);
		
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, gEarthTexCoordsVBO);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);
		
		
		/*
		glUniform1i(glGetUniformLocation(gProgramEarth, "hmap"), 1);
		glBindTexture(GL_TEXTURE_2D,gTextureHeightMap);
		glActiveTexture(GL_TEXTURE0);*/
		
		glUniform1i(glGetUniformLocation(gProgramEarth, "texturemap"), 1);
		glBindTexture(GL_TEXTURE_2D,gTextureColorMap);
		glActiveTexture(GL_TEXTURE1);
		
		
		glUniform1f(glGetUniformLocation(gProgramEarth, "displevel"), gDispLevel);
		glUniform1f(glGetUniformLocation(gProgramEarth, "ex"), gEarthPosX + gCamDirX*gCamDist);
		glUniform1f(glGetUniformLocation(gProgramEarth, "ez"), gEarthPosZ + gCamDirZ*gCamDist);
		
		glUniformMatrix4fv(glGetUniformLocation(gProgramEarth, "MW"), 1, GL_FALSE, &matrix[0]);
	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEarthIndicesVBO);
		glDrawElements(GL_TRIANGLES,6*(num_lat-1)*(num_lon-1)+6*(num_lat-1) , GL_UNSIGNED_INT,  0);	
		
	glPopMatrix();
	
	// Sun
	glPushMatrix();
		glUseProgram(0); // 0 means using no program		
		glColor3f(1,1,0);
		glutSolidSphere(1, 20, 20);
		
		// BONUS: Add some nice shader effects, textures etc. for the Sun
	
	glPopMatrix();
	
	glutSwapBuffers();
	
	// Set FPS to 100
	long diff = getCurrentTime() - startTime;
	if (diff < 10000)
        usleep(10000 - diff);
}

int main(int argc, char** argv)   
{	
    // Hack. Handle the error OpenGL - NVidia consistency error.
	junk();
	
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("20141 - CEng477 - HW3");

    init_glentry();
    init(&argc, argv);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(glutPostRedisplay);

    glutMainLoop();

    return 0;
}

