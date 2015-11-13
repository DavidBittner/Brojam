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

        std::vector< Coord > corners;        

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
    
    corners.clear();

    pos->x += cos( ang )*mag;
    pos->y += sin( ang )*mag;

}

Coord *Particle::GetCorners()
{

    corners.push_back( Coord( pos->x, pos->y ) );
    corners.push_back( Coord( pos->x+5, pos->y ) );
    corners.push_back( Coord( pos->x+5, pos->y+5 ) );
    corners.push_back( Coord( pos->x, pos->y+5 ) );

    return corners.data();

}

#endif
