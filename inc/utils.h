#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <unistd.h>
#include <sys/time.h>
#include <GL/gl.h>   
#include <GL/glut.h> 
#include "glentry.h"

using namespace std;

GLuint createVS(const string& filename);

GLuint createFS(const string& filename);

bool readDataFromFile(const string& fileName, string &data);

long getCurrentTime();

#endif
