#ifndef BULLET_CPP
#define BULLET_CPP

#include "coord.cpp"
#include "glfw_funcs.cpp"

//Bullet class for handling their movement/drawing
class Bullet
{
	
	public:
		Bullet( Coord ply, float ang, float vel, float decel );

        Coord GetPos(){ return pos; }

		void Move();
		void Draw();

	private:

		float xvel, yvel;
		float decel;
		Coord pos;

};

Bullet::Bullet( Coord ply, float ang, float vel, float decel ) : pos( 0, 0 )
{

    std::cout << ang*(180/PI) << std::endl;

	xvel = cos( ang )*vel;
	yvel = sin( ang )*vel;

	pos.x = ply.x;
	pos.y = ply.y;

	this->decel = decel;

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

}

void Bullet::Draw()
{

	glPointSize( 15 );

	glBegin( GL_POINTS );
		glVertex2f( pos.x, pos.y );
	glEnd();

}

#endif
