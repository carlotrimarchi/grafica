#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 60;

//The attributes of the square
const int SQUARE_WIDTH = 200;
const int SQUARE_HEIGHT = 200;

// Event handler
SDL_Event event;

class Square
{
    private:
        int x, y;
    public:
        Square();

        void show();
};

bool init_GL()
{
    //Set clear color
    glClearColor( 0, 0, 0, 0 );

    //Set projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1 );

    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //If there was any errors
    if( glGetError() != GL_NO_ERROR )
    {
        return false;
    }

    //If everything initialized
    return true;
}


bool init()
{
    //Initialize SDL
    if(SDL_Init( SDL_INIT_EVERYTHING ) < 0)
    {
        return false;
    }

    //Create Window
    if(SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL) == NULL )
    {
        return false;
    }

    //Initialize OpenGL
    if(init_GL() == false)
    {
        return false;
    }

    //Set caption
    SDL_WM_SetCaption("OpenGL Test", NULL);

    return true;
}

void clean_up()
{
    //Quit SDL
    SDL_Quit();
}

Square::Square()
{
    //Initialize offsets
    x = 0;
    y = 0;

}


void Square::show()
{
    //Move to offset
    glTranslatef(x, y, 0);

    glBegin(GL_QUADS);
        //Set color to white
        //Draw square
        glColor4f(1.0, 1.0, 1.0, 1.0);
	    glVertex3f(0, 0, 0);
	    glVertex3f(SQUARE_WIDTH, 0, 0);
        glColor4f(0.5, 0.5, 0.5, 1.0);
	    glVertex3f(SQUARE_WIDTH, SQUARE_HEIGHT, 0);
	    glVertex3f(0, SQUARE_HEIGHT, 0);
    glEnd();

    //Reset
    glLoadIdentity();
}


int main(int argc, char *argv[])
{
    //Quit flag
    bool quit = false;

    //Initialize
    if (init() == false)
    {
        return 1;
    }

    //Our square object
    Square square;

    //The frame rate regulator

    // Turn on wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Turn off wireframe mode
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
	//Wait for user exit
	while(quit == false)
	{
        //While there are events to handle
		while( SDL_PollEvent( &event ) )
			if( event.type == SDL_QUIT )
                quit = true;

	    //Clear the screen
	    glClear(GL_COLOR_BUFFER_BIT);

	    square.show();

	    //Update screen
	    SDL_GL_SwapBuffers();
	}

	clean_up();
	return 0;
}
