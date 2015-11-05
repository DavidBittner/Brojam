#ifndef COORD_CPP
#define COORD_CPP

struct Coord
{

	float x, y;
	
	template<class dattype>
	Coord( dattype x, dattype y )
	{ 
		this->x = x; 
		this->y = y; 
	}

	Coord();

};

#endif