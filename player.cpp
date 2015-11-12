#ifndef PLAYER_CPP
#define PLAYER_CPP

#include <GL/glfw3.h>
#include <iostream>

#include <vector>

#include "coord.cpp"
#include "bullet.cpp"

static const int PLY_SIZE = 32;

//Player class for handling the intersactions of the player.
class Player
{

	public:

		//Constructor for establishing the bases for different variables
		Player( float size, float accel )
		{ 
		
			mapSize = size;
			mapAccel = accel;

			plyPos = new Coord( size, 0.0f );
			curAngle = 0.0f;

            yVel = 0.0f;
			mag = 0.0f;

		};

		//Function for handling moving code
		void Move();

		void SetSize( float size ){ mapSize = size; };
		void SetAccel( float accel ){ mapAccel = accel; }

		Coord *GetPos(){ return plyPos; }

		void Draw();

	private:

		void KeyOps();

        std::vector< Bullet* > bullets;

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
	glDrawArrays( GL_QUADS, 0, verts.size()/2 );
	
	glDisableClientState( GL_VERTEX_ARRAY );

    for( Bullet *i : bullets )
    {

        i->Draw();

    }

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

    Coord *tempCord = new Coord( plyPos->x + cos(curAngle)*(PLY_SIZE/2), plyPos->y + sin(curAngle)*(PLY_SIZE/2) );

    if( mouseClick )
    {

        float varyAng = (rand()%10)-5;
        varyAng = varyAng*(PI/180);

        bullets.push_back( new Bullet( *tempCord, GetInclin( *plyPos, mousePos )+varyAng, 40.0f, mapAccel, mapSize ) );


    }

}

void Player::Move()
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

    for( int i = 0; i < bullets.size(); i++ )
    {

        bullets.at(i)->Move();

        if( GetDist( bullets.at(i)->GetPos(), Coord( 0, 0 ) ) < mapSize )
        {

            Bullet *point = bullets.at( i );
            bullets.erase( bullets.begin() + i );

            delete point;

        }

    }

}

#endif
