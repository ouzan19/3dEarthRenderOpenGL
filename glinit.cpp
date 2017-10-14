#include "glinit.h"

void initTextures()
{	
	int width, height, channels = 1;
	
	// read images into memory to generate textures
	unsigned char* textureMapData = SOIL_load_image("res/texturemap.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	unsigned char* heightMapData  = SOIL_load_image("res/heightmap.jpg", &width, &height, &channels, SOIL_LOAD_L);
	
	// TODO: Generate texture map and height map for the Earth
		glGenTextures(1, &gTextureHeightMap);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTextureHeightMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE,GL_UNSIGNED_BYTE, heightMapData);
    SOIL_free_image_data(heightMapData);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
	printf("HeightMap Info: %s\n", result_string_pointer);
	
	
	glGenTextures(1, &gTextureColorMap);		
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gTextureColorMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, textureMapData);
    SOIL_free_image_data(textureMapData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	printf("ColorMap Info: %s\n", result_string_pointer);
	// Generate CubeMap
	glGenTextures(1, &gTextureCubeMap);
	glActiveTexture(GL_TEXTURE2);
	
	glBindTexture(GL_TEXTURE_2D, gTextureCubeMap);
	gTextureCubeMap = SOIL_load_OGL_single_cubemap("res/cubemap.jpg", "WNESUD", SOIL_LOAD_AUTO, gTextureCubeMap, SOIL_FLAG_MIPMAPS);
	
	printf("CubeMap Info: %s\n", result_string_pointer);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void initShaders()
{
	// Creation and initialization of CubeMap's shaders
	gProgramCubeMap = glCreateProgram();
	
    glAttachShader(gProgramCubeMap, createVS("res/cubemap.vert"));
    glAttachShader(gProgramCubeMap, createFS("res/cubemap.frag"));
    
    glLinkProgram(gProgramCubeMap);
    
	glUniform1i(glGetUniformLocation(gProgramCubeMap, "cubeMap")   , 2);
	
	// TODO: Create and initialize new program(s) to use new shader(s)
	gProgramEarth = glCreateProgram();
    glAttachShader(gProgramEarth, createVS("res/Earth.vert"));
    glAttachShader(gProgramEarth, createFS("res/Earth.frag"));
    glLinkProgram(gProgramEarth);
}


void initCubeMap(GLuint *verticesVBO, GLuint *indicesVBO) 
{
	float vertices[] = {
		  1,  1,  1,				
		 -1,  1,  1,
		 -1, -1,  1,
		  1, -1,  1,
		  1, -1, -1,
		 -1, -1, -1,
		 -1,  1, -1,
		  1,  1, -1
	};

	GLuint indices[] = {
		0, 1, 2, 3,                 // Front face of the cube
		7, 4, 5, 6,                 // Back face of the cube
		6, 5, 2, 1,                 // Left face of the cube
		7, 0, 3, 4,                 // Right face of the cube
		7, 6, 1, 0,                 // Top face of the cube
		3, 2, 5, 4,                 // Bottom face of the cube
	};
	
	glGenBuffers(1, verticesVBO);
	glGenBuffers(1, indicesVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, *verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
}


void initEarthMap(GLuint *verticesVBO, GLuint *indicesVBO,GLuint* texCoordVBO,GLuint* normalVBO,float radius, unsigned int lon, unsigned int lat) 
{
	
	
	 std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<unsigned int> indices;
	float const dB =M_PI/(float)(lat);
    float const dA = 2*M_PI/(float)(lon);
    vertices.resize(lat * lon * 3);
    normals.resize(lat*lon * 3);
    texcoords.resize(lat * lon *2);
    std::vector<GLfloat>::iterator v = vertices.begin();
    std::vector<GLfloat>::iterator n = normals.begin();
    std::vector<GLfloat>::iterator t = texcoords.end();
   
    
		for(int j = 0; j <lat; j++) {
			for(int i = 0; i<lon; i++) {
				float const a= i*dA;
				float const b = j*dB;
				float const sina = sin(a);
				float const sinb = sin(b);
				float const cosa = cos(a);
				float const cosb= cos(b);
				*v++ = radius*sina*sinb;
				*v++ = radius * cosb;
				*v++ = radius * cosa*sinb;
				
				*t-- = 1-a/(2*M_PI);
				*t--=(M_PI-b)/M_PI;
				*n++ = radius*sina*sinb;
				*n++ = radius * cosb;
				*n++ = radius * cosa*sinb;
				
		}
	}
	
    indices.resize((lat-1) * (lon-1) * 6 +6*(lat-1) );
    std::vector<unsigned int>::iterator ind = indices.begin();
    for(int i = 0; i < lat-1; i++){
			for(int j = 0; j< lon-1; j++) {
			  
			  *ind++ = i*lon + j;
			  *ind++ = (i+1)*lon + j;
			  *ind++ = i*lon + j+1;
			  *ind++ = (i+1)*lon + j;
			  *ind++ = (i+1)*lon + j+1;
			  *ind++ = i*lon + j+1;
		}
	}	
   
   for(int i=0;i<lat-1;i++){
	  *ind++ = i*lon + lon-1;
	  *ind++ = (i+1)*lon + lon-1;
	  *ind++ = i*lon ;
	  *ind++ = (i+1)*lon + lon-1;
	  *ind++ = (i+1)*lon ;
	  *ind++ = i*lon ;
	   
	   
   }
  
   
	
	glGenBuffers(1, verticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, *verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, 3*lat*lon*sizeof(GLfloat) , &vertices[0], GL_STATIC_DRAW );
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, indicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ((lat-1) * (lon-1) * 6+6*(lat-1))*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, texCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, *texCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, 2*lat*lon*sizeof(GLfloat) , &texcoords[0], GL_STATIC_DRAW );
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, *normalVBO);
	glBufferData(GL_ARRAY_BUFFER, 3*lat*lon*sizeof(GLfloat) , &normals[0], GL_STATIC_DRAW );
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	
	
}
