#include <GL/glfw3.h>
#include <thread>

#include "glfw_funcs.cpp"

#include "planet.cpp"
#include "player.cpp"

const int WIND_WIDTH = 800;
const int WIND_HEIGHT = 600;

const int FRAMES_PER_SECOND = 60.0f;

int main()
{
	
	glfwInit();
	GLFWwindow *window = glfwCreateWindow( WIND_WIDTH, WIND_HEIGHT, "Tiny World", nullptr, nullptr );

	glfwMakeContextCurrent( window );
	glfwSwapInterval( 1 );

	Reshape( window, WIND_WIDTH, WIND_HEIGHT );
	glfwSetWindowSizeCallback( window, Reshape );

	glfwSetKeyCallback( window, KeyFunc );

	Planet TempPlanet( 200, 2 );
	Player TempPlayer( TempPlanet.GetSize(), TempPlanet.GetMass() );

	int stime = 0.0f, etime = 0.0f;

	while( !glfwWindowShouldClose( window ) )
	{

		stime = glfwGetTime();

		glClear( GL_COLOR_BUFFER_BIT );
		glLoadIdentity();

		glTranslatef( 0.0f, 0.0f, -1.0f );
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

	}

	glfwTerminate();

}