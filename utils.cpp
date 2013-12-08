#include "utils.h"

void CheckForGLError() {

	switch (GLenum e = glGetError()) {

		case GL_NO_ERROR:
			break;

		case GL_INVALID_ENUM:
			Log::Err("GL Error: GL_INVALID_ENUM");
			break;

		case GL_INVALID_VALUE:
			Log::Err("GL Error: GL_INVALID_VALUE");
			break;

		case GL_INVALID_OPERATION:
			Log::Err("GL Error: GL_INVALID_OPERATION");
			break;

		case GL_INVALID_FRAMEBUFFER_OPERATION:
			Log::Err("GL Error: GL_INVALID_FRAMEBUFFER_OPERATION");
			break;

		case GL_OUT_OF_MEMORY:
			Log::Err("GL Error: GL_OUT_OF_MEMORY");
			break;

		case GL_STACK_UNDERFLOW:
			Log::Err("GL Error: GL_STACK_UNDERFLOW");
			break;

		case GL_STACK_OVERFLOW:
			Log::Err("GL Error: GL_STACK_OVERFLOW");
			break;
	
		default:
			Log::Err("GL Error: Unknown error");
			break;
	}
}