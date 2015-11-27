#ifndef ENEMY_CPP
#define ENEMY_CPP

#include <vector>

#include "glfw_funcs.cpp"

const int ENEMY_SIZE = 32;

class Enemy
{

    public:
        Enemy( float *plyAng, float mapSize ) : EnemyPos( 0, 0 ), HitLoc( 0, 0 )
        {

            shoot = false;

            direction = rand()%2;
            this->mapSize = mapSize;
            this->plyAng = plyAng;

            float genAng = (((rand()%180)+90)*(PI/180))+(*plyAng);  
            curAng = genAng;
            
            EnemyPos.x = cos(genAng)*mapSize;
            EnemyPos.y = sin(genAng)*mapSize;
            
        }

        void Draw();

        void Move();
        float getHealth();

        Rect *GetRect(){ return &HitLoc; }

    private:
        Coord EnemyPos;
        Rect HitLoc;

        float isAlive;
        float curAng;
        float *plyAng;

        float mapSize;
        bool direction;

        bool shoot;

        std::vector<Coord> corners;

};

void Enemy::Move()
{

    corners.push_back( Coord( 0, ENEMY_SIZE/2 ) );
    corners.push_back( Coord( 0, -ENEMY_SIZE/2 ) );
    corners.push_back( Coord( ENEMY_SIZE, -ENEMY_SIZE/2 ) );
    corners.push_back( Coord( ENEMY_SIZE, ENEMY_SIZE/2 ) );

    float newAng = curAng - *plyAng;
    newAng = NormalizeAng( newAng );

    if( newAng > PI  )
    {

        curAng+=0.01f;

    }else
    {

        curAng-=0.01f;

    }

    EnemyPos.x = cos(curAng)*mapSize;
    EnemyPos.y = sin(curAng)*mapSize;

    curAng = NormalizeAng( curAng );

    float xMin, xMax;
    float yMin, yMax;

    for( unsigned i = 0; i < corners.size(); i++ )
    {

        corners.at(i) = RotateVector( corners.at(i), curAng );
        Coord TempHit( corners.at(i).x+EnemyPos.x, corners.at(i).y+EnemyPos.y );

        if( !i )
        {

            xMin = TempHit.x;
            xMax = TempHit.x;
            yMin = TempHit.y;
            yMax = TempHit.y;

        }

        if( TempHit.x < xMin )
        {

            xMin = TempHit.x;

        }
        if( TempHit.x > xMax )
        {

            xMax = TempHit.x;

        }
        if( TempHit.y < yMin )
        {

            yMin = TempHit.y;

        }
        if( TempHit.y > yMax )
        {

            yMax = TempHit.y;

        }

    }

    HitLoc.x = xMin;
    HitLoc.y = yMin;
    HitLoc.w = xMax - xMin;
    HitLoc.h = yMax - yMin;

}


void Enemy::Draw()
{

    std::vector<float> verts;
    
    for( int i = 0; i < 4; i++ )
    {

        verts.push_back( corners.at(i).x + EnemyPos.x );
        verts.push_back( corners.at(i).y + EnemyPos.y );

    }

    corners.clear();

    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 2, GL_FLOAT, 0, verts.data() );
    glDrawArrays( GL_QUADS, 0, verts.size()/2 );

    verts.clear();

}

#endif
