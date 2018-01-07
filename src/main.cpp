#include <algorithm>
#include <iostream>
#include <string>
#include "SDL.h"

/* Graphics */
#include "../inc/common.h"
#include "../inc/GraphicsCore.h"
/* Input */
#include "../inc/InputCore.h"

using namespace std;

size_t delay = 100;
const int FPS = 60;
const float DELAY_TIME = 1000.0f / FPS;

#define NUM_STARS    512  // number of stars in sim
#define NUM_TIES     32   // number of tie fighters in sim

// 3D engine constants
#define NEAR_Z          10   // the near clipping plane
#define FAR_Z           2000 // the far clipping plane    
#define VIEW_DISTANCE   320  // viewing distance from viewpoint 
// this gives a field of view of 90 degrees
// when projected on a window of 640 wide

// player constants
#define CROSS_VEL       8  // speed that the cross hair moves
#define PLAYER_Z_VEL    8  // virtual z velocity that player is moving
// to simulate motion without moving

// tie fighter model constants
#define NUM_TIE_VERTS     10
#define NUM_TIE_EDGES     8

// explosiond
#define NUM_EXPLOSIONS    (NUM_TIES) // total number of explosions

// game states
#define GAME_RUNNING      1
#define GAME_OVER         0



// TYPES ///////////////////////////////////////////////////

// this a 3D point
typedef struct POINT3D_TYP
{
	uint32_t color;     // color of point 16-bit
	float x, y, z;      // coordinates of point in 3D
} POINT3D, *POINT3D_PTR;

// this is a 3D line, nothing more than two indices into a vertex list
typedef struct LINE3D_TYP
{
	uint32_t color;  // color of line 16-bit
	int v1, v2;     // indices to endpoints of line in vertex list

} LINE3D, *LINE3D_PTR;

// a tie fighter
typedef struct TIE_TYP
{
	int state;      // state of the tie, 0=dead, 1=alive
	float x, y, z;  // position of the tie
	float xv, yv, zv; // velocity of the tie
} TIE, *TIE_PTR;

// a basic 3D vector used for velocity
typedef struct VEC3D_TYP
{
	float x, y, z; // coords of vector
} VEC3D, *VEC3D_PTR;

// a wireframe explosion
typedef struct EXPL_TYP
{
	int state;       // state of explosion
	int counter;     // counter for explosion 
	uint32_t color;    // color of explosion

					 // an explosion is a collection of edges/lines
					 // based on the 3D model of the tie that is exploding
	POINT3D p1[NUM_TIE_EDGES];  // start point of edge n
	POINT3D p2[NUM_TIE_EDGES];  // end point of edge n

	VEC3D   vel[NUM_TIE_EDGES]; // velocity of shrapnel

} EXPL, *EXPL_PTR;

// PROTOTYPES /////////////////////////////////////////////

// game console
int Game_Init(void *parms = NULL);
int Game_Shutdown(void *parms = NULL);
int Game_Main(void *parms = NULL);

// game functions
void Init_Tie(int index);

// GLOBALS ////////////////////////////////////////////////

// the tie fighter is a collection of vertices connected by
// lines that make up the shape. only one tie fighter see if 
// you can replicate it?

POINT3D tie_vlist[NUM_TIE_VERTS]; // vertex list for the tie fighter model
LINE3D  tie_shape[NUM_TIE_EDGES]; // edge list for the tie fighter model
TIE     ties[NUM_TIES];           // tie fighters
POINT3D stars[NUM_STARS]; // the starfield

						  // player vars
Sint32 cross_x = 0; // cross hairs
Sint32 cross_y = 0;

int cross_x_screen = WINDOW_WIDTH / 2,   // used for cross hair
cross_y_screen = WINDOW_HEIGHT / 2,
target_x_screen = WINDOW_WIDTH / 2,   // used for targeter
target_y_screen = WINDOW_HEIGHT / 2;

int player_z_vel = 4; // virtual speed of viewpoint/ship
int cannon_state = 0; // state of laser cannon
int cannon_count = 0; // laster cannon counter

EXPL explosions[NUM_EXPLOSIONS]; // the explosiions

int misses = 0; // tracks number of missed ships
int hits = 0; // tracks number of hits
int score = 0; // take a guess :)

bbq::GraphicsCore gCore; // provides framebuffer and line/point drawing functions

int Game_Init(void *parms)
{
	// this function is where you do all the initialization 
	// for your game

	int index; // used for looping
	uint16_t rgb_white = 0xFFFFFF;
	uint16_t rgb_green = 0x00FF00;

	// create the starfield
	for (index = 0; index < NUM_STARS; index++)
	{
		// randomly position stars in an elongated cylinder stretching from
		// the viewpoint 0,0,-d to the yon clipping plane 0,0,far_z
		stars[index].x = - WINDOW_WIDTH + rand() % (WINDOW_WIDTH * 2);
		stars[index].y = - WINDOW_HEIGHT + rand() % (WINDOW_HEIGHT * 2);
		stars[index].z =  NEAR_Z + rand() % (FAR_Z - NEAR_Z);

		// set color of stars
		stars[index].color = rgb_white;
	} // end for index

	  // create the tie fighter model

	  // the vertex list for the tie fighter
	POINT3D temp_tie_vlist[NUM_TIE_VERTS] =
		// color, x,y,z
	{ { rgb_white,-80,80,0 },    // p0
	{ rgb_white,-80,0,0 },    // p1
	{ rgb_white,-80,-80,0 },   // p2
	{ rgb_white,-20,0,0 },    // p3
	{ rgb_white,0,40,0 },     // p4
	{ rgb_white,20,0,0 },     // p5
	{ rgb_white,0,-40,0 },    // p6
	{ rgb_white,80,80,0 },     // p7
	{ rgb_white,80,0,0 },     // p8
	{ rgb_white,80,-80,0 } };   // p9

								// copy the model into the real global arrays
	for (index = 0; index < NUM_TIE_VERTS; index++)
		tie_vlist[index] = temp_tie_vlist[index];

	// the edge list for the tie fighter
	LINE3D temp_tie_shape[NUM_TIE_EDGES] =
		// color, vertex 1, vertex 2
	{ { rgb_green,0,2 },    // l0
	{ rgb_green,1,3 },    // l1
	{ rgb_green,3,4 },    // l2
	{ rgb_green,4,5 },    // l3
	{ rgb_green,5,6 },    // l4
	{ rgb_green,6,3 },    // l5
	{ rgb_green,5,8 },    // l6
	{ rgb_green,7,9 } };  // l7

						  // copy the model into the real global arrays
	for (index = 0; index < NUM_TIE_EDGES; index++)
		tie_shape[index] = temp_tie_shape[index];

	// initialize the position of each tie fighter and it's velocity
	for (index = 0; index < NUM_TIES; index++)
	{
		// initialize this tie fighter
		Init_Tie(index);

	} // end for index

	  // return success
	return(1);

} // end Game_Init

  //////////////////////////////////////////////////////////

void Start_Explosion(int tie)
{
	// this starts an explosion based on the sent tie fighter

	// first hunt and see if an explosion is free
	for (int index = 0; index < NUM_EXPLOSIONS; index++)
	{
		if (explosions[index].state == 0)
		{
			// start this explosion up using the properties
			// if the tie figther index sent

			explosions[index].state = 1; // enable state of explosion
			explosions[index].counter = 0; // reset counter for explosion 

										   // set color of explosion
			explosions[index].color = 0x00FF0000; // green

			// make copy of of edge list, so we can blow it up
			for (int edge = 0; edge < NUM_TIE_EDGES; edge++)
			{
				// start point of edge
				explosions[index].p1[edge].x = ties[tie].x + tie_vlist[tie_shape[edge].v1].x;
				explosions[index].p1[edge].y = ties[tie].y + tie_vlist[tie_shape[edge].v1].y;
				explosions[index].p1[edge].z = ties[tie].z + tie_vlist[tie_shape[edge].v1].z;

				// end point of edge
				explosions[index].p2[edge].x = ties[tie].x + tie_vlist[tie_shape[edge].v2].x;
				explosions[index].p2[edge].y = ties[tie].y + tie_vlist[tie_shape[edge].v2].y;
				explosions[index].p2[edge].z = ties[tie].z + tie_vlist[tie_shape[edge].v2].z;

				// compute trajectory vector for edges
				explosions[index].vel[edge].x = ties[tie].xv - 8 + rand() % 16;
				explosions[index].vel[edge].y = ties[tie].yv - 8 + rand() % 16;
				explosions[index].vel[edge].z = ties[tie].zv; //+ rand() % 4;

			} // end for edge

			  // done, so return
			return;
		} // end if found

	} // end for index

} // end Start_Explosion

  ///////////////////////////////////////////////////////////

void Process_Explosions(void)
{
	// this processes all the explosions

	// loop thro all the explosions and render them
	for (int index = 0; index < NUM_EXPLOSIONS; index++)
	{
		// test if this explosion is active?
		if (explosions[index].state == 0)
			continue;

		for (int edge = 0; edge < NUM_TIE_EDGES; edge++)
		{
			// must be exploding, update edges (shrapel)
			explosions[index].p1[edge].x += explosions[index].vel[edge].x;
			explosions[index].p1[edge].y += explosions[index].vel[edge].y;
			explosions[index].p1[edge].z += explosions[index].vel[edge].z;

			explosions[index].p2[edge].x += explosions[index].vel[edge].x;
			explosions[index].p2[edge].y += explosions[index].vel[edge].y;
			explosions[index].p2[edge].z += explosions[index].vel[edge].z;
		} // end for edge

		  // test for terminatation of explosion?
		if (++explosions[index].counter > 100)
			explosions[index].state = explosions[index].counter = 0;

	} // end for index

} // end Process_Explosions

  ///////////////////////////////////////////////////////////

void Draw_Explosions(void)
{
	// this draws all the explosions

	// loop thro all the explosions and render them
	for (int index = 0; index < NUM_EXPLOSIONS; index++)
	{
		// test if this explosion is active?
		if (explosions[index].state == 0)
			continue;

		// render this explosion
		// each explosion is made of a number of edges
		for (int edge = 0; edge < NUM_TIE_EDGES; edge++)
		{
			POINT3D p1_per, p2_per; // used to hold perspective endpoints

									// test if edge if beyond near clipping plane
			if (explosions[index].p1[edge].z < NEAR_Z &&
				explosions[index].p2[edge].z < NEAR_Z)
				continue;

			// step 1: perspective transform each end point
			p1_per.x = VIEW_DISTANCE * explosions[index].p1[edge].x / explosions[index].p1[edge].z;
			p1_per.y = VIEW_DISTANCE * explosions[index].p1[edge].y / explosions[index].p1[edge].z;
			p2_per.x = VIEW_DISTANCE * explosions[index].p2[edge].x / explosions[index].p2[edge].z;
			p2_per.y = VIEW_DISTANCE * explosions[index].p2[edge].y / explosions[index].p2[edge].z;

			// step 2: compute screen coords
			int p1_screen_x = WINDOW_WIDTH / 2 + p1_per.x;
			int p1_screen_y = WINDOW_HEIGHT / 2 - p1_per.y;
			int p2_screen_x = WINDOW_WIDTH / 2 + p2_per.x;
			int p2_screen_y = WINDOW_HEIGHT / 2 - p2_per.y;

			// step 3: draw the edge
			gCore.drawLine(p1_screen_x, p1_screen_y, p2_screen_x, p2_screen_y,
				explosions[index].color);
			//Draw_Clip_Line16(p1_screen_x, p1_screen_y, p2_screen_x, p2_screen_y,
			//	explosions[index].color, back_buffer, back_lpitch);

		} // end for edge

	} // end for index

} // end Draw_Explosions

  //////////////////////////////////////////////////////////

void Init_Tie(int index)
{
	// this function starts a tie fighter up at the far end
	// of the universe and sends it our way!

	// position each tie in the viewing volume
	ties[index].x = -WINDOW_WIDTH + rand() % (2 * WINDOW_WIDTH);
	ties[index].y = -WINDOW_HEIGHT + rand() % (2 * WINDOW_HEIGHT);
	ties[index].z = 4 * FAR_Z;

	// initialize velocity of tie fighter
	ties[index].xv = -4 + rand() % 8;
	ties[index].yv = -4 + rand() % 8;
	ties[index].zv = -4 - rand() % 64;

	// turn the tie fighter on
	ties[index].state = 1;
} // end Init_Tie

void Process_Ties(void)
{
	// process the tie fighters and do AI (what there is of it!)
	int index; // looping var

			   // move each tie fighter toward the viewpoint
	for (index = 0; index < NUM_TIES; index++)
	{
		// is this one dead?
		if (ties[index].state == 0)
			continue;

		// move the next star
		ties[index].z += ties[index].zv;
		ties[index].x += ties[index].xv;
		ties[index].y += ties[index].yv;

		// test for past near clipping plane
		if (ties[index].z <= NEAR_Z)
		{
			// reset this tie
			Init_Tie(index);

			// another got away
			//misses++;

		} // reset tie

	} // end for index

}  // Process_Ties


void Draw_Ties(void)
{
	// draw the tie fighters in 3D wireframe with perspective

	int index; // looping var

			   // used to compute the bounding box of tie fighter
			   // for collision detection
	int bmin_x, bmin_y, bmax_x, bmax_y;

	// draw each tie fighter
	for (index = 0; index < NUM_TIES; index++)
	{
		// draw the next tie fighter

		// is this one dead?
		if (ties[index].state == 0)
			continue;

		// reset the bounding box to impossible values
		bmin_x = 100000;
		bmax_x = -100000;
		bmin_y = 100000;
		bmax_y = -100000;

		// based on z-distance shade tie fighter
		// normalize the distance from 0 to max_z then
		// scale it to 255, so the closer the brighter
		uint32_t rgb_tie_color = (255 - 255 * (ties[index].z / (4 * FAR_Z)));
    rgb_tie_color <<= 16;

		// each tie fighter is made of a number of edges
		for (int edge = 0; edge < NUM_TIE_EDGES; edge++)
		{
			POINT3D p1_per, p2_per; // used to hold perspective endpoints

									// step 1: perspective transform each end point
									// note the translation of each point to the position of the tie fighter
									// that is the model is relative to the position of each tie fighter -- IMPORTANT
			p1_per.x =
				VIEW_DISTANCE * (ties[index].x + tie_vlist[tie_shape[edge].v1].x) /
				(tie_vlist[tie_shape[edge].v1].z + ties[index].z);

			p1_per.y = VIEW_DISTANCE * (ties[index].y + tie_vlist[tie_shape[edge].v1].y) /
				(tie_vlist[tie_shape[edge].v1].z + ties[index].z);

			p2_per.x = VIEW_DISTANCE * (ties[index].x + tie_vlist[tie_shape[edge].v2].x) /
				(tie_vlist[tie_shape[edge].v2].z + ties[index].z);

			p2_per.y = VIEW_DISTANCE * (ties[index].y + tie_vlist[tie_shape[edge].v2].y) /
				(tie_vlist[tie_shape[edge].v2].z + ties[index].z);

			// step 2: compute screen coords
			int p1_screen_x = WINDOW_WIDTH / 2 + p1_per.x;
			int p1_screen_y = WINDOW_HEIGHT / 2 - p1_per.y;
			int p2_screen_x = WINDOW_WIDTH / 2 + p2_per.x;
			int p2_screen_y = WINDOW_HEIGHT / 2 - p2_per.y;

			// step 3: draw the edge
			gCore.drawLine(p1_screen_x, p1_screen_y, p2_screen_x, p2_screen_y, rgb_tie_color);

			// update bounding box with next edge
			int min_x = min(p1_screen_x, p2_screen_x);
			int max_x = max(p1_screen_x, p2_screen_x);

			int min_y = min(p1_screen_y, p2_screen_y);
			int max_y = max(p1_screen_y, p2_screen_y);

			bmin_x = min(bmin_x, min_x);
			bmin_y = min(bmin_y, min_y);

			bmax_x = max(bmax_x, max_x);
			bmax_y = max(bmax_y, max_y);

		} // end for edge

		  // test if this guy has been hit by lasers???
		if (cannon_state == 1)
		{
			// simple test of screen coords of bounding box contain laser target
			if (target_x_screen > bmin_x && target_x_screen < bmax_x &&
				target_y_screen > bmin_y && target_y_screen < bmax_y)
			{
				std::cout << "HIT!" << std::endl;
				// this tie is dead meat!
				Start_Explosion(index);

				// start sound
				//DSound_Play(explosion_id);

				// increase score
				score += ties[index].z;

				// add one more hit
				hits++;

				// finally reset this tie figher
				Init_Tie(index);

			} // end if

		} // end if

	} // end for index

} // end Draw_Ties

void Move_Starfield(void)
{
	// move the stars

	int index; // looping var

			   // the stars are technically stationary,but we are going
			   // to move them to simulate motion of the viewpoint
	for (index = 0; index < NUM_STARS; index++)
	{
		// move the next star
		stars[index].z -= player_z_vel;

		// test for past near clipping plane
		if (stars[index].z <= NEAR_Z)
			stars[index].z = FAR_Z;

	} // end for index

} // end Move_Starfield

  /////////////////////////////////////////////////////////

void Draw_Starfield(void)
{
	// draw the stars in 3D using perspective transform

	int index; // looping var

	for (index = 0; index < NUM_STARS; index++)
	{
		// draw the next star
		// step 1: perspective transform
		float x_per = VIEW_DISTANCE * stars[index].x / stars[index].z;
		float y_per = VIEW_DISTANCE * stars[index].y / stars[index].z;

		// step 2: compute screen coords
		int x_screen = WINDOW_WIDTH / 2 + x_per;
		int y_screen = WINDOW_HEIGHT / 2 - y_per;

		// clip to screen coords
		if (x_screen >= WINDOW_WIDTH || x_screen < 0 ||
			y_screen >= WINDOW_HEIGHT || y_screen < 0)
		{
			// continue to next star
			continue;
		} // end if
		else
		{
			// else render to buffer
      uint32_t luminosity = rand() * 0x01010100;
      uint32_t rgb_star_color = 0xFFFFFF00; /*(255 - 255 * (stars[index].z / (FAR_Z)));
      rgb_star_color <<= 8;
      rgb_star_color |= rgb_star_color << 8;
      rgb_star_color |= rgb_star_color << 8;*/
      gCore.drawPoint(x_screen, y_screen, rgb_star_color);
			//((USHORT *)back_buffer)[x_screen + y_screen * (back_lpitch >> 1)]
			//	= stars[index].color;
		} // end else

	} // end for index

}  // Draw_Starfield

int main(int argc, char** argv)
{



	// Init SDL2 //////////////////////////////////////

  // for now done in graphics core

	// ! Init SDL2 //////////////////////////////////////


  // Init Graphics Core ///////////////////////////////

	gCore.init();
	// ! Init Graphics Core /////////////////////////////

	// Init Input Core //////////////////////////////////

	bbq::InputCore iCore;
	iCore.init();

	// ! Init Input Core ////////////////////////////////

	Game_Init();


	bool running = true;
	size_t iter = 0;
	SDL_Event event;

	int before_update_time = 0;
	int last_update_time = SDL_GetTicks();
	float last_update_time_input = SDL_GetTicks();
	int before_render_time = SDL_GetTicks();
	int after_render_time = 0.0f;
	int time_needed = 0;

	while (running) {

		before_render_time = SDL_GetTicks();

		while (SDL_PollEvent(&event) != 0)
		{
			cross_x = event.motion.x;
			cross_y = event.motion.y;
			cannon_state = 1;
			if (event.type == SDL_QUIT) {
				running = false;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{			
				// save last position of targeter
				target_x_screen = cross_x;
				target_y_screen = cross_y;

			}
		}

		// input update
		if (SDL_GetTicks() - last_update_time_input > 10) // not quite what the threshold should be
		{
			iCore.update();

			if (iCore.keyDown(SDL_SCANCODE_DOWN))
			{

			}
			if (iCore.keyDown(SDL_SCANCODE_UP))
			{

			}
			if (iCore.keyUp(SDL_SCANCODE_RIGHT))
			{

			}
			if (iCore.keyUp(SDL_SCANCODE_LEFT))
			{

			}
			if (iCore.keyDown(SDL_SCANCODE_SPACE))
			{

			}

			if (iCore.keyDown(SDL_SCANCODE_ESCAPE))
			{
				running = false;
			}

			last_update_time_input = SDL_GetTicks();
		}

		Move_Starfield();
		Process_Ties();
		Process_Explosions();

		gCore.clear();
		SDL_SetRenderDrawColor(gCore.getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
		Draw_Starfield();
		Draw_Ties();
		Draw_Explosions();

		target_x_screen = -10000;
		target_y_screen = -10000;
		// first compute screen coords of crosshair
		// note inversion of y-axis
		cross_x_screen = WINDOW_WIDTH / 2 + cross_x;
		cross_y_screen = WINDOW_HEIGHT / 2 - cross_y;

		//SDL_RenderDrawLine(gCore.getRenderer(), 0, 0, 200, 200);
		SDL_RenderPresent(gCore.getRenderer());
		//SDL_Delay(100); // artificial render time 

		after_render_time = SDL_GetTicks();
		time_needed = after_render_time - before_render_time;

		if (time_needed < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - time_needed);
		}

	}


	SDL_Quit();

	return 0;
}