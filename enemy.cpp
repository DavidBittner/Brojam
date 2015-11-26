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

            direction = rand()%2;
            this->mapSize = mapSize;
            this->plyAng = plyAng;

            float genAng = (((rand()%180)+90)*(PI/180))+(*plyAng);  
            curAng = genAng;
            
            EnemyPos.x = cos(genAng)*mapSize;
            EnemyPos.y = sin(genAng)*mapSize;
            
            HitLoc.x = EnemyPos.x;
            HitLoc.y = EnemyPos.y;
            HitLoc.w = ENEMY_SIZE;
            HitLoc.h = ENEMY_SIZE;

        }

        void Draw();

        void Move()
        {

            corners.push_back( Coord( 0, ENEMY_SIZE/2 ) );
            corners.push_back( Coord( 0, -PLY_SIZE/2 ) );
            corners.push_back( Coord( PLY_SIZE, -PLY_SIZE/2 ) );
            corners.push_back( Coord( PLY_SIZE, PLY_SIZE/2 ) );
 
            float newAng = curAng - *plyAng;
            newAng = NormalizeAng( newAng );

            if( newAng > PI  )
            {

                curAng+=0.005f;

            }else
            {

                curAng-=0.005f;

            }

            EnemyPos.x = cos(curAng)*mapSize;
            EnemyPos.y = sin(curAng)*mapSize;

            curAng = NormalizeAng( curAng );

        }

        float getHealth();

        Rect GetRect(){ return HitLoc; }

    private:
        Coord EnemyPos;
        Rect HitLoc;

        float isAlive;
        float curAng;
        float *plyAng;

        float mapSize;
        bool direction;

        std::vector<Coord> corners;

};

void Enemy::Draw()
{

    std::vector<float> verts;
    
    for( int i = 0; i < 4; i++ )
    {

        corners.at(i) = RotateVector( corners.at(i), curAng );

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
