#ifndef PLAYER_CPP
#define PLAYER_CPP

#include <GL/glfw3.h>
#include <iostream>

#include "coord.cpp"

static const int PLY_SIZE = 10;

class Player
{

	public:

		Player( float size, float accel )
		{ 
		
			mapSize = size;
			mapAccel = accel;

			plyPos = new Coord( size, 0.0f );
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

			plyPos->x = (cos( curAngle )*mapSize)+cos(curAngle)*mag;
			plyPos->y = (sin( curAngle )*mapSize)+sin(curAngle)*mag;

			if( GetDist( *plyPos, origin ) < mapSize )
			{

				yVel = 0.0f;
				mag = 0.0f;

				plyPos->x = (cos( curAngle )*mapSize)+cos(curAngle)*mag;
				plyPos->y = (sin( curAngle )*mapSize)+sin(curAngle)*mag;

			}

		}

		void SetSize( float size ){ mapSize = size; };
		void SetAccel( float accel ){ mapAccel = accel; }

		Coord *GetPos(){ return plyPos; }

		void Draw();

	private:

		float GetDist( Coord a, Coord b )
		{

			return sqrt( pow( a.x-b.x, 2 ) + pow( a.y-b.y, 2 ) );

		}

		Coord RotateVector( Coord in, float rotateAngle );
		float GetInclin( Coord a, Coord b );

		void KeyOps();

		Coord *plyPos;
		float curAngle;

		float yVel;
		float mag;

		float mapSize;
		float mapAccel;

};

void Player::Draw()
{

	std::vector< float > verts;

	std::vector< Coord > corners;
	corners.push_back( Coord( 0, PLY_SIZE/2 ) );
	corners.push_back( Coord( 0, -PLY_SIZE/2 ) );
	corners.push_back( Coord( PLY_SIZE, -PLY_SIZE/2 ) );
	corners.push_back( Coord( PLY_SIZE, PLY_SIZE/2 ) );

	for( int i = 0; i < 4; i++ )
	{

		corners.at(i) = RotateVector( corners.at(i), curAngle );

		verts.push_back( corners.at(i).x+plyPos->x );
		verts.push_back( corners.at(i).y+plyPos->y );

	}

	glEnableClientState( GL_VERTEX_ARRAY );

	glVertexPointer( 2, GL_FLOAT, 0, verts.data() );
	glDrawArrays( GL_TRIANGLE_FAN, 0, verts.size()/2 );
	
	glDisableClientState( GL_VERTEX_ARRAY );


}

float Player::GetInclin( Coord a, Coord b )
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

Coord Player::RotateVector( Coord in, float rotationangle )
{

	float inclin = GetInclin( Coord( 0, 0 ), in );
	float mag = sqrt(pow(in.x,2)+pow(in.y,2));

	inclin+=rotationangle;

	Coord temp( 0.0f, 0.0f );

	temp.x = cos( inclin )*mag;
	temp.y = sin( inclin )*mag;

	return temp;

}

void Player::KeyOps()
{

	if( keyStates[GLFW_KEY_A] )
	{

		curAngle+=0.05f*(200.0f/mapSize);

	}else if( keyStates[GLFW_KEY_D] )
	{

		curAngle-=0.05f*(200.0f/mapSize);

	}

	if( keyPresses[ GLFW_KEY_SPACE ] )
	{

		yVel = 15.0f;

	}

}

#endif