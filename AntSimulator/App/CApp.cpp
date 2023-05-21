/**********************************************************
 *  CApp.cpp
 *
 *  Created on: 18 nov. 2022
 *      Author: GarnierAndrew
 *
 **********************************************************/

#include <ctime>
#include <iostream>
using namespace std;

#include <CApp.h>

enum e_statusMasks:Uint32{
	ST_ALL_CLEARED			= 0x00000000,
	ST_APP_INIT_FAILED		= 0x80000000,
	ST_APP_SDL_INITIATED	= 0x00000001,
	ST_APP_PAUSED			= 0x00000002,
	ST_APP_LCTRL			= 0x00000004,
	ST_APP_LSHIFT			= 0x00000008,
};

CApp::CApp() :
	m_status(ST_ALL_CLEARED),
	m_pWindows(nullptr),
	m_pRenderer(nullptr),
	m_colorBkgnd(APP_WINDOW_COLOR_BKGND),
	m_timerID(0),
	m_pMutexCallback(nullptr),
	m_pScene(nullptr),
	m_sceneArea{
		APP_SCENE_PADDING,
		APP_SCENE_PADDING,
		APP_WINDOW_WIDTH-2*APP_SCENE_PADDING,
		APP_WINDOW_HEIGHT-2*APP_SCENE_PADDING}
{
	if(SDL_Init(SDL_INIT_VIDEO)!=0){
		cerr << "Failed to initiated SDL: " << SDL_GetError() << endl;
		mBitsSet(m_status,ST_APP_INIT_FAILED);
		return;
	}
	mBitsSet(m_status,ST_APP_SDL_INITIATED);
	m_pWindows=SDL_CreateWindow(
			APP_WINDOW_TITLE,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			APP_WINDOW_WIDTH,
			APP_WINDOW_HEIGHT,
			SDL_WINDOW_SHOWN);
	if(m_pWindows==nullptr){
		cerr << "Failed to create window: " << SDL_GetError() << endl;
		mBitsSet(m_status,ST_APP_INIT_FAILED);
		return;
	}
	m_pRenderer=SDL_CreateRenderer(m_pWindows, -1, SDL_RENDERER_ACCELERATED);
	if(m_pRenderer==nullptr){
		cerr << "Failed to create ACCELERATED renderer: " << SDL_GetError() << endl;
		m_pRenderer=SDL_CreateRenderer(m_pWindows, -1, SDL_RENDERER_SOFTWARE);
		if(m_pRenderer==nullptr){
			cerr << "Failed to create SOFTWARE renderer: " << SDL_GetError() << endl;
			mBitsSet(m_status,ST_APP_INIT_FAILED);
			return;
		}
		cerr << "Created SOFTWARE renderer instead!" << endl;
	}

	m_pScene = new CScene{
				{APP_SCENE_LEFT, APP_SCENE_TOP, APP_SCENE_WIDTH, APP_SCENE_HEIGHT},
				APP_SCENE_COLOR_BKGND,
				m_pRenderer
	};

	Run();
}

CApp::~CApp() {
	if(m_timerID) 			SDL_RemoveTimer(m_timerID);
	if(m_pMutexCallback)	SDL_DestroyMutex(m_pMutexCallback);
	if(m_pScene)			delete m_pScene;
	if(m_pRenderer)			SDL_DestroyRenderer(m_pRenderer);
	if(m_pWindows)			SDL_DestroyWindow(m_pWindows);
	/*if(mIsBitsSet(m_status,ST_APP_SDL_INITIATED)) SDL_Quit();	 */
}

int CApp::Run(){
	if(mIsBitsSet(m_status,ST_APP_INIT_FAILED)) return -1;

	int iQuit=0;
	SDL_Event event;

	srand((unsigned int)time(nullptr));
	m_pMutexCallback = SDL_CreateMutex();

	m_timerID=SDL_AddTimer(APP_TIMER_RATE, SDL_TimerCallback(Animate), this);

	while(!iQuit){
		while(SDL_PollEvent(&event)){
			switch(event.type) {
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button) {
				case SDL_BUTTON_LEFT:
					if(SDL_LockMutex(m_pMutexCallback)==0){
						size_t nb = event.button.clicks==1?1:event.button.clicks*10;
						if(mIsBitsSet(m_status, ST_APP_LCTRL)){
							/**
							 * ToDo: Add ask for adding some CCleanerAnt objects
							 */
							m_pScene->AddCCleanerAnts({event.button.x, event.button.y}, nb);
						}
						else{
							/**
							 * Ask for adding some CAnt objects
							 */
							m_pScene->AddAnts({event.button.x, event.button.y}, nb);
						}
						SDL_UnlockMutex(m_pMutexCallback);
					}
					break;
				case SDL_BUTTON_RIGHT:
					if(SDL_LockMutex(m_pMutexCallback)==0){
						/**
						 * Ask for deleting object(s) under mouse cursor pointer
						 */
						if(m_pScene->DelObjectsAt({event.button.x, event.button.y})){
							SDL_SetRenderDrawColor(m_pRenderer, APP_WINDOW_COLOR_BKGND.r, APP_WINDOW_COLOR_BKGND.g, APP_WINDOW_COLOR_BKGND.b, APP_WINDOW_COLOR_BKGND.a);
							SDL_RenderClear(m_pRenderer);
							m_pScene->Draw(m_pRenderer);
							SDL_RenderPresent(m_pRenderer);
						}
						SDL_UnlockMutex(m_pMutexCallback);
					}
					break;
				default:
					break;
				}
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
				case SDLK_LCTRL:
					mBitsSet(m_status, ST_APP_LCTRL);
					break;
				case SDLK_LSHIFT:
					mBitsSet(m_status, ST_APP_LSHIFT);
					break;
				case SDLK_a:
					if(SDL_LockMutex(m_pMutexCallback)==0){
						/**
						 * Ask for flushing ants
						 */
						m_pScene->FlushAnts();
						SDL_UnlockMutex(m_pMutexCallback);
					}
					break;
				case SDLK_z:
					if(SDL_LockMutex(m_pMutexCallback)==0){
						/**
						 * Ask for flushing ants
						 */
						m_pScene->FlushPheromones();
						SDL_UnlockMutex(m_pMutexCallback);
					}
					break;
				case SDLK_p:
					mBitsTgl(m_status, ST_APP_PAUSED);
					break;
				case SDLK_c:
					if(SDL_LockMutex(m_pMutexCallback)==0){
						mBitsSet(m_status, ST_APP_PAUSED);
						SDL_Log("CLone in progress...");
						m_pScene->Clone();
						SDL_Log("CLone completed");
						mBitsClr(m_status, ST_APP_PAUSED);
						SDL_UnlockMutex(m_pMutexCallback);
					}
					break;
				case SDLK_SPACE:{
					if(SDL_LockMutex(m_pMutexCallback)==0){
						/**
						 * Ask for adding some random ants
						 */
						m_pScene->RandomAddAnts();
						SDL_UnlockMutex(m_pMutexCallback);
					}
					break;
				}
				case SDLK_ESCAPE:
					event.type=SDL_QUIT;
					SDL_PushEvent(&event);
					break;
				default:
					break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym) {
				case SDLK_LCTRL:
					mBitsClr(m_status, ST_APP_LCTRL);
					break;
				case SDLK_LSHIFT:
					mBitsClr(m_status, ST_APP_LSHIFT);
					break;
				default:
					break;
				}
				break;
			case SDL_QUIT:
				SDL_LockMutex(m_pMutexCallback);
				iQuit=1;
				break;
			default:
				break;
			}
		}
	}
	return 0;
}

Uint32 CApp::Animate(Uint32 interval, CApp*pApp){

	if(mIsBitsClr(pApp->m_status, ST_APP_PAUSED) && SDL_TryLockMutex(pApp->m_pMutexCallback)==0){

		/**
		 * Processing object animation
		 */

		pApp->m_pScene->Animate(&pApp->m_sceneArea, pApp->m_pRenderer); /* ### USE THE VERSION WITH A RENDERER PARAMETER ### */


		/********************************************************************************/
		SDL_SetRenderDrawColor(pApp->m_pRenderer, APP_WINDOW_COLOR_BKGND.r, APP_WINDOW_COLOR_BKGND.g, APP_WINDOW_COLOR_BKGND.b, APP_WINDOW_COLOR_BKGND.a);
		SDL_RenderClear(pApp->m_pRenderer);

		/**
		 * Processing object drawing
		 */

		pApp->m_pScene->Draw(pApp->m_pRenderer);


		/********************************************************************************/
		SDL_RenderPresent(pApp->m_pRenderer);

		/********************************************************************************/
		SDL_UnlockMutex(pApp->m_pMutexCallback);
	}

	return interval;
}

