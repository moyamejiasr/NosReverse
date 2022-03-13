#pragma once
#include "../Common.h"
#include "../../util/gl-enums.h"

typedef void GLvoid;
typedef int GLsizei;
typedef int GLint;
typedef unsigned int GLuint;
typedef unsigned int GLenum;

void (__stdcall **glBindTexture)(GLenum target, GLuint texture) = Cast(0x005EBEBC);
void (__stdcall **glDeleteTextures)(GLsizei n, const GLuint *textures) = Cast(0x005EBF94);
void (__stdcall **glGenTextures)(GLsizei n, GLuint *textures) = Cast(0x005EC030);
void (__stdcall **glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLvoid *pixels) = Cast(0x005EC35C);
void (__stdcall **glTexParameteri)(GLenum target, GLenum pname, GLint param) = Cast(0x005EC368);
void (__stdcall **glTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels) = Cast(0x005EC374);