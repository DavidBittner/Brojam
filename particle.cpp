#ifndef PARTICLE_CPP
#define PARTICLE_CPP

#include <chrono>

#include "glfw_funcs.cpp"

typedef std::chrono::high_resolution_clock Clock;

class Particle
{

    public:
        Particle( Coord sourcePos, float mag, float ang, float lifeSpan );

        void Move();
        void Draw();

        float GetLife(){ return existTime/lifeSpan; }
        bool IsAlive(){ return alive; }

        Coord *GetCorners();

    private:
        Coord *pos;

        std::vector< Coord > corners;        

        float lifeSpan;
        float existTime;

        float mag;
        float ang;

        bool alive;

        Clock::time_point birth;

};

Particle::Particle( Coord sourcePos, float mag, float ang, float lifeSpan )
{

    pos = new Coord(sourcePos.x, sourcePos.y);
    
    this->mag = mag;
    this->ang = ang;

    this->lifeSpan = lifeSpan;

    alive = true;
    existTime = 0.0f;

    birth = Clock::now();

}

void Particle::Move()
{
    
    corners.clear();

    pos->x += (cos( ang )*mag)*(1-(existTime/lifeSpan));
    pos->y += (sin( ang )*mag)*(1-(existTime/lifeSpan));

    auto etime = Clock::now();
    existTime = std::chrono::duration_cast< std::chrono::milliseconds >(etime-birth).count();

    if( existTime >= lifeSpan )
    {

        alive = false;

    }

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
