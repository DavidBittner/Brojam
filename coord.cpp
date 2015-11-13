#ifndef COORD_CPP
#define COORD_CPP

struct Coord
{

	float x, y;
	
	template<class dattype, class secdattype >
	Coord( dattype x, secdattype y )
	{ 
		this->x = x; 
		this->y = y; 
	}

	Coord();

};

#endif
