#pragma once
#include "../Common.h"
#include "../../util/gl-enums.h"

typedef int GLsizei;
typedef int GLint;
typedef unsigned int GLuint;
typedef unsigned int GLenum;

void (__stdcall **glGenTextures)(GLsizei n, GLuint *textures) = Cast(0x005EC030);
void (__stdcall **glTexParameteri)(GLenum target, GLenum pname, GLint param) = Cast(0x005EC368);