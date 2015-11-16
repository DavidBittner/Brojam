#ifndef PART_CONT_CPP
#define PART_CONT_CPP

#include <vector>

#include "glfw_funcs.cpp"
#include "particle.cpp"

class ParticleController
{

    public:
        ParticleController( Coord *sourcePos, float lifeSpan, int prodRate, float angVary, float createAng, float speed ); 

        void Draw();
        void Move();

        void SetAng( float ang ){ this->createAng = ang; }
    
    private:
        std::vector<Particle> particles;

        Coord *sourcePos;

        float angVary;
        float speed;

        float createAng;

        int prodRate;

        float lifeSpan;

};

ParticleController::ParticleController( Coord *sourcePos, float lifeSpan, int prodRate, float angVary, float createAng, float speed )
{

    this->angVary = angVary;
    this->createAng = createAng;

    this->sourcePos = sourcePos;

    this->speed = speed;
    this->prodRate = prodRate;

    this->lifeSpan = lifeSpan;

}

void ParticleController::Move()
{

    int doesProduce = FRAMES_PER_SECOND/prodRate;

    if( !(frame%doesProduce) )
    {

        float randAng = rand()%((int)(angVary*(180/PI)));
        randAng*=(PI/180);
        
        randAng = randAng-(angVary/2);

        particles.push_back( Particle( *sourcePos, speed, randAng+createAng, lifeSpan ) ); 

    }
    
    for( int i = 0; i < particles.size(); i++ )
    {

        particles.at(i).Move();

        if( !particles.at(i).IsAlive() )
        {

            particles.erase( particles.begin()+i );
            i--;

        }

    }

}

void ParticleController::Draw()
{

    std::vector<float> verts;
    std::vector<float> colors;

    for( int i = 0; i < particles.size(); i++ )
    {

        Coord *temp = particles.at(i).GetCorners();

        for( int j = 0; j < 4; j++ )
        {

            verts.push_back( temp[j].x );
            verts.push_back( temp[j].y );

            for( int f = 0; f < 3; f++ )
            {

                colors.push_back( 1.0f-particles.at(i).GetLife() );

            }

        }

    }

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
    
    glVertexPointer( 2, GL_FLOAT, 0, verts.data() );
    glColorPointer( 3, GL_FLOAT, 0, colors.data() );

    glDrawArrays( GL_QUADS, 0, verts.size()/2 );

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );

}

#endif
