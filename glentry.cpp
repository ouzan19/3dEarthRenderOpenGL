#include <stdio.h>
#include <stdlib.h>
#include "glentry.h"

PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
PFNGLGENERATEMIPMAPPROC  glGenerateMipmap;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLFRAMEBUFFERTEXTUREARBPROC glFramebufferTextureARB;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
PFNGLPROGRAMPARAMETERIPROC glProgramParameteriARB;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArray;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORM4FVPROC glUniform4fv;
PFNGLUNIFORM3FVPROC glUniform3fv;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLBUFFERSUBDATAPROC glBufferSubData;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLGETSHADERIVPROC glGetShaderiv;

int init_glentry()
{
    glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) glXGetProcAddress((const GLubyte*) "glGenFramebuffers");
    glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) glXGetProcAddress((const GLubyte*) "glGenerateMipmap");
    glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) glXGetProcAddress((const GLubyte*) "glBindFramebuffer");
    glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC) glXGetProcAddress((const GLubyte*) "glFramebufferTextureLayer");
    glCreateShader = (PFNGLCREATESHADERPROC) glXGetProcAddress((const GLubyte*) "glCreateShader");
    glShaderSource = (PFNGLSHADERSOURCEPROC) glXGetProcAddress((const GLubyte*) "glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC) glXGetProcAddress((const GLubyte*) "glCompileShader");
    glAttachShader = (PFNGLATTACHSHADERPROC) glXGetProcAddress((const GLubyte*) "glAttachShader");
    glCreateProgram = (PFNGLCREATEPROGRAMPROC) glXGetProcAddress((const GLubyte*) "glCreateProgram");
    glLinkProgram = (PFNGLLINKPROGRAMPROC) glXGetProcAddress((const GLubyte*) "glLinkProgram");
    glUseProgram = (PFNGLUSEPROGRAMPROC) glXGetProcAddress((const GLubyte*) "glUseProgram");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) glXGetProcAddress((const GLubyte*) "glGetUniformLocation");
    glUniform1i = (PFNGLUNIFORM1IPROC) glXGetProcAddress((const GLubyte*) "glUniform1i");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) glXGetProcAddress((const GLubyte*) "glGetShaderInfoLog");
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) glXGetProcAddress((const GLubyte*) "glGetProgramInfoLog");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC) glXGetProcAddress((const GLubyte*) "glGetProgramiv");
    glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) glXGetProcAddress((const GLubyte*) "glCheckFramebufferStatus");
    glFramebufferTextureARB = (PFNGLFRAMEBUFFERTEXTUREARBPROC) glXGetProcAddress((const GLubyte*) "glFramebufferTextureARB");
    glProgramParameteriARB = (PFNGLPROGRAMPARAMETERIPROC) glXGetProcAddress((const GLubyte*) "glProgramParameteriARB");
    glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) glXGetProcAddress((const GLubyte*) "glFramebufferTexture2D");
    glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) glXGetProcAddress((const GLubyte*) "glFramebufferTexture3D");
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) glXGetProcAddress((const GLubyte*) "glVertexAttribPointer");
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC) glXGetProcAddress((const GLubyte*) "glEnableVertexAttribArray");
    glUniform1f = (PFNGLUNIFORM1FPROC) glXGetProcAddress((const GLubyte*) "glUniform1f");
    glUniform4fv = (PFNGLUNIFORM4FVPROC) glXGetProcAddress((const GLubyte*) "glUniform4fv");
    glUniform3fv = (PFNGLUNIFORM3FVPROC) glXGetProcAddress((const GLubyte*) "glUniform3fv");
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) glXGetProcAddress((const GLubyte*) "glUniformMatrix4fv");
    glGenBuffers = (PFNGLGENBUFFERSPROC) glXGetProcAddress((const GLubyte*) "glGenBuffers");
    glBufferData = (PFNGLBUFFERDATAPROC) glXGetProcAddress((const GLubyte*) "glBufferData");
    glBufferSubData = (PFNGLBUFFERSUBDATAPROC) glXGetProcAddress((const GLubyte*) "glBufferSubData");
    glBindBuffer = (PFNGLBINDBUFFERPROC) glXGetProcAddress((const GLubyte*) "glBindBuffer");
    glGetShaderiv = (PFNGLGETSHADERIVPROC) glXGetProcAddress((const GLubyte*) "glGetShaderiv");

    if (!glGenFramebuffers ||
        !glGenerateMipmap ||
        !glBindFramebuffer ||
        !glFramebufferTextureLayer ||
        !glCreateShader ||
        !glShaderSource ||
        !glCompileShader ||
        !glAttachShader ||
        !glCreateProgram ||
        !glLinkProgram ||
        !glUseProgram ||
        !glGetUniformLocation ||
        !glUniform1i ||
        !glGetShaderInfoLog ||
        !glGetProgramInfoLog ||
        !glGetProgramiv ||
        !glCheckFramebufferStatus ||
        !glFramebufferTextureARB ||
        !glProgramParameteriARB ||
        !glFramebufferTexture2D ||
        !glFramebufferTexture3D ||
        !glVertexAttribPointer ||
        !glEnableVertexAttribArray ||
        !glUniform1f ||
        !glUniform4fv ||
        !glUniform3fv ||
        !glUniformMatrix4fv ||
        !glGenBuffers ||
        !glBufferData ||
        !glBufferSubData ||
        !glBindBuffer ||
        !glGetShaderiv
        )
    {
        fprintf(stderr, "One or more entry points returned NULL\n");
        return -1;
    }

    return 0;
}

