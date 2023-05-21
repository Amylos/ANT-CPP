/*
 * defines.h
 *
 *  Created on: 4 nov. 2022
 *      Author: thierry
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#define APP_WINDOW_TITLE			("Ants Simulator")
#define APP_WINDOW_WIDTH			(1400)
#define APP_WINDOW_HEIGHT			(900)
#define APP_WINDOW_COLOR_BKGND		(SDL_Color{0xE0,0xE0,0xE0,0xFF})

#define APP_FONT_FILE_NAME_STR		"./Resources/Fonts/SpaceMono-Regular.ttf"
#define APP_FONT_SIZE				(20)
#define APP_TIMER_RATE				(50)

#define APP_SCENE_PADDING			(50)
#define APP_SCENE_LEFT				(APP_SCENE_PADDING)
#define APP_SCENE_TOP				(int(APP_SCENE_PADDING*1.5))
#define APP_SCENE_WIDTH				(APP_WINDOW_WIDTH-APP_SCENE_LEFT-APP_SCENE_PADDING)
#define APP_SCENE_HEIGHT			(APP_WINDOW_HEIGHT-APP_SCENE_TOP-APP_SCENE_PADDING)
#define APP_SCENE_COLOR_BKGND		{0xA0,0xA0,0xA0,0xFF}

#define APP_DISPLAY_LEFT			(APP_SCENE_LEFT)
#define APP_DISPLAY_TOP				(15)
#define APP_DISPLAY_WIDTH			(APP_SCENE_WIDTH)
#define APP_DISPLAY_HEIGHT			(APP_SCENE_TOP-2*APP_DISPLAY_TOP)
#define APP_DISPLAY_PADDING			(5)

#define APP_ANT_COUNT_INIT			(500)
#define APP_ANT_SIZE				(5)
#define APP_ANT_COLOR				{80,80,80,255}
#define APP_CCLEANER_ANT_COLOR		{200,100,40,255}
#define APP_CCLEANER_ANT_REV_COLOR	{40,50,200,255}
#define APP_ANT_N_MAX				(4000)

#define APP_PHEROMONE_SIZE			(2)
#define APP_PHEROMONE_COLOR			{0xFF,0xFF,0x90,0xFF}
#define APP_PHEROMONE_TTL_INIT		(200)
#define APP_PHEROMONE_TTL_MAX		(APP_PHEROMONE_TTL_INIT*3)
#define APP_PHEROMONE_TTL_INC_VAL	(1)
#define APP_PHEROMONE_N_MAX			(20000)

#define mBitsSet(f,m)		((f)|=(m))
#define mBitsClr(f,m)		((f)&=(~(m)))
#define mBitsTgl(f,m)		((f)^=(m))
#define mBitsMsk(f,m)		((f)& (m))
#define mIsBitsSet(f,m)		(((f)&(m))==(m))
#define mIsBitsClr(f,m)		(((~(f))&(m))==(m))

#endif /* DEFINES_H_ */
