#ifndef GLFW_FUNCS
#define GLFW_FUNCS

#include <cmath>

#include "coord.cpp"

const float PI = 3.14159;

bool *keyStates = new bool[256];
bool *keyPresses = new bool[256];
Coord mousePos( 0, 0 );

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

float GetDist( Coord a, Coord b )
{

	return sqrt( pow( a.x-b.x, 2 ) + pow( a.y-b.y, 2 ) );

}

float GetInclin( Coord a, Coord b )
{

	float deltax = b.x - a.x;
	float deltay = b.y - a.y;

	float ang = atan( deltay/deltax );

	if( deltax < 0 )
	{

		ang+=(PI);

	}

	if( ang < 0 )
	{

		ang+=(2*PI);

	}

	return ang;

}

void MotionFunc( int x, int y )
{

	mousePos.x = x;
	mousePos.y = y;

}

#endif