#ifndef BULLET_CPP
#define BULLET_CPP

#include "coord.cpp"
#include "glfw_funcs.cpp"

#include "particle_controller.cpp"

//Bullet class for handling their movement/drawing
class Bullet
{
	
	public:
		Bullet( Coord ply, float ang, float vel, float decel, float size );

        Coord *GetPos(){ return &pos; }

		void Move();
		void Draw();

	private:

		float xvel, yvel;
		float decel, size;
		Coord pos;

        ParticleController *partCont;

};

Bullet::Bullet( Coord ply, float ang, float vel, float decel, float size ) : pos( 0, 0 )
{

	xvel = cos( ang )*vel;
	yvel = sin( ang )*vel;

	pos.x = ply.x;
	pos.y = ply.y;

    this->size = size;
	this->decel = decel;

    partCont = new ParticleController( &pos, 20, 20, PI/4, 10.0f );

}

void Bullet::Move()
{

	float decelAng = GetInclin( Coord( 0, 0 ), pos );

	float xPull = cos(decelAng)*(decel/6);
	float yPull = sin(decelAng)*(decel/6);

	xvel-=xPull;
	yvel-=yPull;

	pos.x+=xvel;
	pos.y+=yvel;

    partCont->Move();

}

void Bullet::Draw()
{

    partCont->Draw();

    std::vector<float> verts;

    std::vector< Coord > corners;
    corners.push_back( Coord( -5, -2 ) );
	corners.push_back( Coord( 5, -2 ) );
	corners.push_back( Coord( 5, 2 ) );
	corners.push_back( Coord( -5, 2 ) );
	
    for( int i = 0; i < 4; i++ )
    {
 
        float tempAng = atan( yvel/xvel );

        corners.at(i) = RotateVector( corners.at(i), tempAng );

        verts.push_back( corners.at(i).x + pos.x );
        verts.push_back( corners.at(i).y + pos.y );

    }

    glEnableClientState( GL_VERTEX_ARRAY );
    
    glVertexPointer( 2, GL_FLOAT, 0, verts.data() );
    glDrawArrays( GL_QUADS, 0, verts.size()/2 );

    glDisableClientState( GL_VERTEX_ARRAY );

}

#endif
