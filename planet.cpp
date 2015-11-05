#ifndef CIRC_CPP
#define CIRC_CPP

#include <GL/glfw3.h>
#include <cmath>
#include <vector>

class Planet
{

	public:
		Planet( float radius, float mass )
		{

			_radius = radius; _mass = mass;

		}

		void Draw();

		float GetSize(){ return _radius; }
		float GetMass(){ return _mass; }

	private:
		float _radius;
		float _mass;

};

void Planet::Draw()
{


	glColor3f( 0.4f, 0.4f, 0.4f );

	std::vector< float > verts;

	verts.push_back( 0 );
	verts.push_back( 0 );

	for( float i = 0; i < (2*PI)+(PI/6.0f); i+=0.01f )
	{

		verts.push_back( cos( i )*_radius );
		verts.push_back( sin( i )*_radius );

	}

	glEnableClientState( GL_VERTEX_ARRAY );

	glVertexPointer( 2, GL_FLOAT, 0, verts.data() );
	glDrawArrays( GL_TRIANGLE_FAN, 0, verts.size()/2 );

	glDisableClientState( GL_VERTEX_ARRAY );

	glColor3f( 1.0f, 1.0f, 1.0f );

}

#endif