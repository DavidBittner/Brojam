#ifndef PART_CONT_CPP
#define PART_CONT_CPP

#include <vector>

#include "glfw_funcs.cpp"
#include "particle.cpp"

class ParticleController
{

    public:
        ParticleController( Coord *sourcePos, int lifeSpan, int prodRate, float angMin, float angMax, float speed ); 

        void Draw();
        void Move();

    private:
        std::vector<Particle> particles;

        Coord *sourcePos;

        float angMin, angMax;
        float speed;

        int prodRate;

};

void ParticleController::Move()
{

    int doesProduce = FRAMES_PER_SECOND/prodRate;

    if( !(frame%doesProduce) )
    {

        float ang = rand()%((int)(angMax - angMin))+angMin;

        particles.push_back( Particle( *sourcePos, speed, ang ) ); 

    }

}

#endif
