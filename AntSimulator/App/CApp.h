/**********************************************************
 *  CApp.h
 *
 *  Created on: 18 nov. 2022
 *      Author: GarnierAndrew
 *
 **********************************************************/


#include <defines.h>
#include <SDL2/SDL.h>

#include <CScene.h>

class CApp {
private:
	Uint32				m_status;
	SDL_Window	 	*	m_pWindows;
	SDL_Renderer 	*	m_pRenderer;
	SDL_Color			m_colorBkgnd;
	SDL_TimerID			m_timerID;
	SDL_mutex		*	m_pMutexCallback;
	/************************************************************/
	CScene			*	m_pScene;
	SDL_Rect			m_sceneArea;
public:
	CApp();
	~CApp();
private:
	int Run();
private:
	static Uint32 Animate(Uint32 interval, CApp*pObj);
};
