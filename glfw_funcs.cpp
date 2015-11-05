#ifndef GLFW_FUNCS
#define GLFW_FUNCS

#include <cmath>

bool *keyStates = new bool[256];
bool *keyPresses = new bool[256];

void Reshape( GLFWwindow *wind, int width, int height )
{
	
	glViewport( 0, 0, (GLsizei)width, (GLsizei)height );
	glMatrixMode( GL_PROJECTION );

	glLoadIdentity();
	glOrtho( -width/2, width/2, -height/2, height/2, 1.0f, 2.0f );

	glMatrixMode( GL_MODELVIEW );

}

void KeyFunc( GLFWwindow *window, int key, int scancode, int action, int mods )
{

	if( action == GLFW_PRESS )
	{

		keyStates[key] = true;

		if( keyPresses[key] != true )
		{

			keyPresses[key] = true;

		}

	}

	if( action == GLFW_RELEASE )
	{

		keyStates[key] = false;
		keyPresses[key] = false;

	}

}

void ResetKeys()
{

	for( int i = 0; i < 256; i++ )
	{

		keyPresses[i] = false;

	}

}

#endif