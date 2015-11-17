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

int frame = 0;

const int FRAMES_PER_SECOND = 60.0f;

struct Rect
{

    Rect( float x, float y) { this->x = x; this->y = y; }

    float x, y;
    float w, h;

};

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

Coord RotateVector( Coord in, float rotationangle )
{

	float inclin = GetInclin( Coord( 0, 0 ), in );
	float mag = sqrt(pow(in.x,2)+pow(in.y,2));

	inclin+=rotationangle;

	Coord temp( 0.0f, 0.0f );

	temp.x = cos( inclin )*mag;
	temp.y = sin( inclin )*mag;

	return temp;

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

bool AABB( Rect *a, Rect *b )
{

    if( a->x < b->x + b->w &&
        a->x+a->w > b->x &&
        a->y < b->y + b->h &&
        a->y + a->h > b->y )
    {

        return true;

    }

    return false;

}

#endif
