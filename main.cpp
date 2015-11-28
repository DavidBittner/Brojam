#include <GLFW/glfw3.h>
#include <thread>

#include "glfw_funcs.cpp"
#include "planet.cpp"
#include "player.cpp"

#include "enemy.cpp"

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
	Player *TempPlayer = new Player( TempPlanet.GetSize(), TempPlanet.GetMass() );

    //Point the camera to the player's position.
	camera = TempPlayer->GetPos();

    //Just for frame capping.
	float stime = 0.0f, etime = 0.0f;
    float fade = 0.0f;

    glEnable( GL_BLEND );

	while( !glfwWindowShouldClose( window ) )
	{
        
        stime = glfwGetTime();

		glClear( GL_COLOR_BUFFER_BIT );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glLoadIdentity();
        
        if( !TempPlayer->Lost() )
        {
        
            TempPlayer->Move();

            if( fade > 0.0f )
            {

                fade-=0.01f;

            }

        }else
        {

            fade += 0.01f;
         
        }

        glPushMatrix();
		glTranslatef( -camera->x, -camera->y, -1.0f );

        TempPlayer->Draw();
		TempPlanet.Draw();
        glPopMatrix();

        if( fade > 0.0f )
        {

            if( fade > 1.1f )
            {

                TempPlayer->Reset();
                TempPlayer = new Player( TempPlanet.GetSize(), TempPlanet.GetMass() );
                camera = TempPlayer->GetPos();

            }

            glTranslatef( 0.0f, 0.0f, -1.0f );
            int w, h;
            glfwGetWindowSize( window, &w, &h );

            float verts[] =
            {
                -w/2.0f, -h/2.0f,
                w/2.0f, -h/2.0f,
                w/2.0f, h/2.0f,
                -w/2.0f, h/2.0f
            };

            float colors[] = 
            {
                0.0f, 0.0f, 0.0f, fade,
                0.0f, 0.0f, 0.0f, fade,
                0.0f, 0.0f, 0.0f, fade,
                0.0f, 0.0f, 0.0f, fade
            };

            glEnableClientState( GL_VERTEX_ARRAY );
            glEnableClientState( GL_COLOR_ARRAY );

            glVertexPointer( 2, GL_FLOAT, 0, verts );
            glColorPointer( 4, GL_FLOAT, 0, colors );

            glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );

            glDisableClientState( GL_VERTEX_ARRAY );
            glDisableClientState( GL_COLOR_ARRAY );

        }

		ResetKeys();
		glfwPollEvents();
		glfwSwapBuffers( window );

		etime = glfwGetTime();

		if( etime - stime < 1000.0f/FRAMES_PER_SECOND )
		{

            int timeDelay = (1000.0f/FRAMES_PER_SECOND)-(etime-stime);
			std::this_thread::sleep_for( std::chrono::milliseconds( timeDelay ) );

		}

        frame++;

        if( frame == FRAMES_PER_SECOND )
        {

            frame = 0;

        }

        glDisable( GL_BLEND );

	}

	glfwTerminate();

}
