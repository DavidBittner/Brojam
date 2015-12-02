#ifndef PLAYER_CPP
#define PLAYER_CPP

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "coord.cpp"
#include "bullet.cpp"
#include "enemy.cpp"

static const int PLY_SIZE = 32;

//Player class for handling the intersactions of the player.
class Player
{

	public:

		//Constructor for establishing the bases for different variables
		Player( float size, float accel ) : refRect( size, 0.0f )
		{ 
		
			mapSize = size;
			mapAccel = accel;

			plyPos = new Coord( size, 0.0f );
			curAngle = 0.0f;

            xVel = 0.0f;
            yVel = 0.0f;
			mag = 0.0f;

            refRect.w = PLY_SIZE;
            refRect.h = PLY_SIZE;

            health = 1.0f;

            createThread = new std::thread( &Player::CreateEnemy, this );

		};

        float *GetAng(){ return &curAngle; }

		//Function for handling moving code
		void Move();

		void SetSize( float size ){ mapSize = size; };
		void SetAccel( float accel ){ mapAccel = accel; }

		Coord *GetPos(){ return plyPos; }

		void Draw();

        void Reset();
        bool Lost(){ return ( health <= 0.0f ); }

	private:

		void KeyOps();
        void CreateEnemy();

        std::vector< Bullet* > bullets;
        std::vector< Coord > corners;

        std::vector< Enemy > enemies;

        std::thread *createThread;

        Rect refRect;

		Coord *plyPos;
		float curAngle;

        float xVel;
		float yVel;
		float mag;

		float mapSize;
		float mapAccel;

        float health;

};

void Player::Draw()
{

    if( health <= 0.0f )
    {

        corners.push_back( Coord( 0, PLY_SIZE/2 ) );
        corners.push_back( Coord( 0, -PLY_SIZE/2 ) );
        corners.push_back( Coord( PLY_SIZE, -PLY_SIZE/2 ) );
        corners.push_back( Coord( PLY_SIZE, PLY_SIZE/2 ) );
        
        for( unsigned i = 0; i < corners.size(); i++ )
        {

            corners.at(i) = RotateVector( corners.at(i), curAngle );

        }

    }

	std::vector< float > verts;
    std::vector< float > colors;

	for( unsigned i = 0; i < corners.size(); i++ )
	{

		verts.push_back( corners.at(i).x+plyPos->x );
		verts.push_back( corners.at(i).y+plyPos->y );

        colors.push_back( 1.0f-health );
        colors.push_back( health );
        colors.push_back( 0.0f );

	}

    corners.clear();

    if( health >= 0.0f )
    {
     
        std::mutex mtx;
        mtx.lock();
        for( unsigned i = 0; i < enemies.size(); i++ )
        {

            enemies.at(i).Draw();

        }
        mtx.unlock();

        for( unsigned i = 0; i < bullets.size(); i++ )
        {

            bullets.at(i)->Draw();

        }

    }
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );

	glVertexPointer( 2, GL_FLOAT, 0, verts.data() );
    glColorPointer( 3, GL_FLOAT, 0, colors.data() );
	glDrawArrays( GL_QUADS, 0, verts.size()/2 );
	
	glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );

    verts.clear();

}

void Player::Reset()
{

    for( unsigned i = 0; i < bullets.size(); i++ )
    {
    
        Bullet *temp = bullets.at(i);
        bullets.erase( bullets.begin() + i );

        delete temp;

    }

    //delete createThread;

}

void Player::CreateEnemy()
{

    std::mutex mtx;

    while( true )
    {

        mtx.lock();
        enemies.push_back( Enemy( &curAngle, mapSize ) );
        mtx.unlock();

        std::this_thread::sleep_for( std::chrono::seconds( 4 ) );

    }

}

void Player::KeyOps()
{

	if( keyStates[GLFW_KEY_A] )
	{

	    xVel=0.05f*(200.0f/mapSize);

        xVel = xVel*( mapSize/GetDist(*plyPos, Coord( 0, 0 ) ) );

	}else if( keyStates[GLFW_KEY_D] )
	{

		xVel=-0.05f*(200.0f/mapSize);
        xVel = xVel*( mapSize/GetDist(*plyPos, Coord( 0, 0 ) ) );

	}

	if( keyPresses[ GLFW_KEY_SPACE ] )
	{

		yVel = 15.0f;

	}

    if( mouseClick )
    {

        float playerToMouse = GetInclin( *plyPos, mousePos );
        
        float xMod = cos( curAngle ) * (PLY_SIZE/2.0f);
        float yMod = sin( curAngle ) * (PLY_SIZE/2.0f);

        const float reduceConst = 1.4f;

        Coord tempPos = Coord( (plyPos->x + cos( playerToMouse )*(PLY_SIZE/reduceConst))+xMod,
                               (plyPos->y + sin( playerToMouse )*(PLY_SIZE/reduceConst))+yMod);

        bullets.push_back( new Bullet( tempPos, playerToMouse, 32.0f, mapAccel, mapSize ) );

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

    std::mutex mtx;
    mtx.lock();
    for( unsigned i = 0; i < bullets.size(); i++ )
    {

        bullets.at(i)->Move();

        if( GetDist( *bullets.at(i)->GetPos(), Coord( 0, 0 ) ) < mapSize )
        {

            Bullet *point = bullets.at( i );
            bullets.erase( bullets.begin() + i );

            delete point;

        }else if( AABB( bullets.at(i)->GetRect(), &refRect ) )
        {

            health-=0.2f;

            Bullet *point = bullets.at( i );
            bullets.erase( bullets.begin() + i );

            xVel += point->GetMovAng()/10.0f;

            delete point;

        }else
        {

            for( unsigned j = 0; j < enemies.size(); j++ )
            {

                if( AABB( bullets.at(i)->GetRect(), enemies.at(j).GetRect() ) )
                {

                    if( bullets.size() > 0 && enemies.size() > 0 )
                    {
                        Bullet *point = bullets.at(i);
                        bullets.erase( bullets.begin() + i );

                        delete point;

                        enemies.erase( enemies.begin() + j );
                        j--;
                        i--;
                    }

                }

            }

        }

    }
    for( unsigned i = 0; i < enemies.size(); i++ )
    {

        if( AABB( enemies.at(i).GetRect(), &refRect ) )
        {

            health = -1.0f;
            break;

        }

    }

    mtx.unlock();

    curAngle+=xVel;
    
    if( xVel != 0.0f )
    {
        xVel = xVel/1.5f;
    }
    
    corners.push_back( Coord( 0, PLY_SIZE/2 ) );
	corners.push_back( Coord( 0, -PLY_SIZE/2 ) );
	corners.push_back( Coord( PLY_SIZE, -PLY_SIZE/2 ) );
	corners.push_back( Coord( PLY_SIZE, PLY_SIZE/2 ) );

    float xmax, ymax;
    float xmin, ymin;

    for( int i = 0; i < 4; i++ )
    {

        corners.at(i) = RotateVector( corners.at(i), curAngle );

        if( !i )
        {

            xmax = corners.at(i).x; xmin = corners.at(i).x;
            ymax = corners.at(i).x; ymin = corners.at(i).y;

        }

        if( corners.at(i).x < xmin )
        {

            xmin = corners.at(i).x;

        }

        if( corners.at(i).x > xmax )
        {

            xmax = corners.at(i).x;

        }

        if( corners.at(i).y < ymin )
        {

            ymin = corners.at(i).y;

        }

        if( corners.at(i).y > ymax )
        {

            ymax = corners.at(i).y;

        }

    }

    refRect.x = xmin + plyPos->x;
    refRect.y = ymin + plyPos->y;

    refRect.w = xmax-xmin;
    refRect.h = ymax-ymin;

    curAngle = NormalizeAng( curAngle );

    mtx.lock();
    for( unsigned i = 0; i < enemies.size(); i++ )
    {

        enemies.at(i).Move();

    }
    mtx.unlock();

}

#endif
