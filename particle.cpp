#ifndef PARTICLE_CPP
#define PARTICLE_CPP

#include "glfw_funcs.cpp"

class Particle
{

    public:
        Particle( Coord sourcePos, float mag, float ang );

        void Move();
        void Draw();

        Coord *GetCorners();

    private:
        Coord *pos;

        Coord *corners;        

        float mag;
        float ang;

};

Particle::Particle( Coord sourcePos, float mag, float ang )
{

    pos = new Coord(sourcePos.x, sourcePos.y);
    
    this->mag = mag;
    this->ang = ang;

}

void Particle::Move()
{

    pos->x += cos( ang )*mag;
    pos->y += sin( ang )*mag;

}

Coord *Particle::GetCorners()
{

    return corners;

}

#endif
