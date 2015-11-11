#ifndef GLFW_FUNCS
#define GLFW_FUNCS

#include <cmath>
#include <GL/glfw3.h>

#include <iostream>

#include "coord.cpp"

const float PI = 3.14159;

bool *keyStates = new bool[256];
bool *keyPresses = new bool[256];

Coord *camera = new Coord( 0, 0 );

Coord mouseRef( 0, 0 );
Coord mousePos( 0, 0 );
bool mouseButton = false;
bool mouseClick = false;

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

		if( !keyPresses[key] )
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

    mouseClick = false;

	int w, h;
    glfwGetWindowSize( glfwGetCurrentContext(), &w, &h );

    mousePos.x = (mouseRef.x-(w/2)) + camera->x;
	mousePos.y = ((h-mouseRef.y)-(h/2)) + camera->y;


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

void MotionFunc( GLFWwindow *wind, double x, double y )
{

    mouseRef.x = x;
    mouseRef.y = y;

    //Relative calcuations so the mouse lines up with the camera.
}

void MouseFunc( GLFWwindow *wind, int button, int action, int mods )
{

	if( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS )
	{

		mouseButton = true;

		if( !mouseClick )
		{

			mouseClick = true;

		}

	}else if( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE )
    {

        mouseButton = false;

    }

}

#endif
