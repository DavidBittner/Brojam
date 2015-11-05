#ifndef PLAYER_CPP
#define PLAYER_CPP

#include <GL/glfw3.h>
#include <iostream>

#include "coord.cpp"

class Player
{

	public:

		Player( float size, float accel )
		{ 
		
			mapSize = size;
			mapAccel = accel;

			basePos = new Coord( size, 0.0f );
			curAngle = 0.0f;

			yVel = 0.0f;
			mag = 0.0f;

		};

		void Move()
		{

			KeyOps();

			yVel -= mapAccel/6.0f;
			mag += yVel;

			Coord origin( 0, 0 );

			basePos->x = (cos( curAngle )*mapSize)+cos(curAngle)*mag;
			basePos->y = (sin( curAngle )*mapSize)+sin(curAngle)*mag;

			if( GetDist( *basePos, origin ) < mapSize )
			{

				yVel = 0.0f;
				mag = 0.0f;

				basePos->x = (cos( curAngle )*mapSize)+cos(curAngle)*mag;
				basePos->y = (sin( curAngle )*mapSize)+sin(curAngle)*mag;

			}

		}

		void SetSize( float size ){ mapSize = size; };
		void SetAccel( float accel ){ mapAccel = accel; }

		void Draw();

	private:

		float GetDist( Coord a, Coord b )
		{

			return sqrt( pow( a.x-b.x, 2 ) + pow( a.y-b.y, 2 ) );

		}

		void KeyOps();

		Coord *basePos;
		float curAngle;

		float yVel;
		float mag;

		float mapSize;
		float mapAccel;

};

void Player::Draw()
{

	glPointSize( 10 );

	glBegin( GL_POINTS );
		glVertex2f( basePos->x, basePos->y );
	glEnd();

}

void Player::KeyOps()
{

	if( keyStates[GLFW_KEY_A] )
	{

		curAngle+=0.05f;

	}else if( keyStates[GLFW_KEY_D] )
	{

		curAngle-=0.05f;

	}

	if( keyPresses[ GLFW_KEY_SPACE ] )
	{

		yVel = 15.0f;

	}

}

#endif