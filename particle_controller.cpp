#ifndef PART_CONT_CPP
#define PART_CONT_CPP

#include <vector>

#include "glfw_funcs.cpp"
#include "particle.cpp"

class ParticleController
{

    public:
        ParticleController( Coord *sourcePos, int lifeSpan, int prodRate, float angVary, float speed ); 

        void Draw();
        void Move();

    private:
        std::vector<Particle> particles;

        Coord *sourcePos;

        float angVary;
        float speed;

        int prodRate;

};

ParticleController::ParticleController( Coord *sourcePos, int lifeSpan, int prodRate, float angVary, float speed )
{

    this->angVary = angVary;

    this->sourcePos = sourcePos;

    this->speed = speed;

    this->prodRate = prodRate;

}

void ParticleController::Move()
{

    int doesProduce = FRAMES_PER_SECOND/prodRate;

    if( !(frame%doesProduce) )
    {

        std::cout << angVary << std::endl;

        float ang = rand()%(int)(angVary*(180/PI));

        std::cout << ang << std::endl;
        particles.push_back( Particle( *sourcePos, speed, ang ) ); 

    }
    
    for( int i = 0; i < particles.size(); i++ )
    {

        particles.at(i).Move();

    }

}

void ParticleController::Draw()
{

    std::vector<float> verts;

    for( int i = 0; i < particles.size(); i++ )
    {

        Coord *temp = particles.at(i).GetCorners();

        for( int j = 0; j < 4; j++ )
        {

            verts.push_back( temp[j].x );
            verts.push_back( temp[j].y );

        }

    }

    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 2, GL_FLOAT, 0, verts.data() );
    glDrawArrays( GL_QUADS, 0, verts.size()/2 );
    glDisableClientState( GL_VERTEX_ARRAY );

}

#endif
