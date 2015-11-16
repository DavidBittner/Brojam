#include <GL/glfw3.h>
#include <thread>

#include "glfw_funcs.cpp"
#include "planet.cpp"
#include "player.cpp"

const int WIND_WIDTH = 800;
const int WIND_HEIGHT = 600;

int main()
{
	
	glfwInit();

	glfwWindowHint( GLFW_SAMPLES, 2 );
	GLFWwindow *window = glfwCreateWindow( WIND_WIDTH, WIND_HEIGHT, "Tiny World", nullptr, nullptr );

	glfwMakeContextCurrent( window );
	glfwSwapInterval( 1 );

	Reshape( window, WIND_WIDTH, WIND_HEIGHT );
	glfwSetWindowSizeCallback( window, Reshape );

	glfwSetKeyCallback( window, KeyFunc );

    glfwSetCursorPosCallback( window, MotionFunc );
    glfwSetMouseButtonCallback( window, MouseFunc ); 

    srand(time(nullptr));

    //Randomizing the size and gravity of the planet.
    int size = (rand()%512)+256;
    int gravity = (rand()%8)+2;

	Planet TempPlanet( size, gravity );
	Player TempPlayer( TempPlanet.GetSize(), TempPlanet.GetMass() );

    //Point the camera to the player's position.
	camera = TempPlayer.GetPos();

    //Just for frame capping.
	float stime = 0.0f, etime = 0.0f;

	while( !glfwWindowShouldClose( window ) )
	{

		stime = glfwGetTime();

		glClear( GL_COLOR_BUFFER_BIT );
		glLoadIdentity();

		glTranslatef( -camera->x, -camera->y, -1.0f );
		TempPlanet.Draw();

		TempPlayer.Draw();
		TempPlayer.Move();

		ResetKeys();
		glfwPollEvents();
		glfwSwapBuffers( window );

		etime = glfwGetTime();

		if( etime - stime < 1000.0f/FRAMES_PER_SECOND )
		{

			std::this_thread::sleep_for( std::chrono::milliseconds( (1000/FRAMES_PER_SECOND)-(etime-stime) ) );

		}

        frame++;

        if( frame == FRAMES_PER_SECOND )
        {

            frame = 0;

        }

	}

	glfwTerminate();

}
