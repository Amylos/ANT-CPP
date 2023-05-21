/**********************************************************
 *  CScene.cpp
 *
 *  Created on: 17 dec. 2021
 *      Author: <Nom> <Prenom>
 *
 **********************************************************/

#include <defines.h>
#include <CScene.h>
#include <typeinfo>
#include <CUtil.h>
CScene::CScene(const SDL_Rect&frame, const SDL_Color&color, SDL_Renderer*pRenderer) :
	CObject(frame, {0}, color),
	m_antHill{m_frame.x+int(m_frame.w*2.0/5), m_frame.y+int(m_frame.h*2.0/5), m_frame.w/5, m_frame.h/5}
{
	CAnt::InitGraphics(this);
	CDisplay::InitGraphics(APP_FONT_FILE_NAME_STR, APP_FONT_SIZE);
	/**********************************************************************
	 * ToDo: Generate some random ants for starting simulation
	 */
}

CScene::~CScene() {
	CAnt::ReleaseGraphics();
	CDisplay::ReleaseGraphics();
}

void CScene::Draw(SDL_Renderer*pRenderer)const{
	SDL_SetRenderDrawColor(pRenderer, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRect(pRenderer, &m_frame);
	/**********************************************************************
	 * ToDo: Draw all objects in the scene
	 */

	SDL_SetRenderDrawColor(pRenderer, m_color.r+20, m_color.g+20, m_color.b+20, m_color.a);
	SDL_RenderDrawRect(pRenderer, &m_antHill);

	m_pheromones.Parse((CContainer<CPheromone>::t_ptfTV)CPheromone::ParseDrawMethod,pRenderer);
	m_ants.Parse((CContainer<CAnt>::t_ptfTV)CAnt::ParseDrawMethod,pRenderer);

	m_display.Draw(pRenderer);
}

int CScene::Animate(SDL_Rect*pArea){
	/**********************************************************************
	 * ToDo: Animate all objects in the scene.
	 */
	return 0;
}

int CScene::Animate(SDL_Rect*pArea, SDL_Renderer*pRenderer){
	/**********************************************************************
	 * ToDo: Animate all objects in the scene. This version use a renderer.
	 */

	char buf[255];
	size_t sHashCode = typeid(CCleanerAnt).hash_code();
	size_t iAntNumber = m_ants.ParseCount((CContainer<CAnt>::t_ptfTV)CAnt::ParseIsThisObjectTypeMethod, &sHashCode);

	sprintf(buf," ANTS : [%d] CLEANERANTS : [%d] PHEROMONES : [%6d]", m_ants.Card()- iAntNumber,iAntNumber,m_pheromones.Card());
	m_display.SetText(buf, pRenderer);

	m_pheromones.ParseDelIf((CContainer<CPheromone>::t_ptfTV)CPheromone::ParseAnimateMethod, pArea);
	m_ants.ParseDelIf((CContainer<CAnt>::t_ptfTV)CAnt::ParseAnimateMethod, pArea);


	return 0;
}

void CScene::RandomAddAnts(){
	/**********************************************************************
	 * ToDo: Generate some random ants, if capacity is not reached.
	 */

 size_t szNb = rand()%(100-50)+50;

	for(size_t k = 0; k<szNb;k++){
		if(m_ants.Card()<APP_ANT_N_MAX){
			m_ants.PushBack(new CAnt(
			SDL_Rect{m_antHill.x + rand()%(m_antHill.w),m_antHill.y+ rand()%(m_antHill.h),APP_ANT_SIZE,APP_ANT_SIZE},
			SDL_Point{rand()%(12)-6,rand()%(12)-6},
			APP_ANT_COLOR));
		}
	}
}

void CScene::AddCCleanerAnts(const SDL_Point&at, size_t szNb){

	for(size_t k = 0; k<szNb;k++){
		if(m_ants.Card()<APP_ANT_N_MAX){
			int iTrack;

			iTrack = rand()%2;
			if(iTrack == 0){ iTrack = 1; }
			else{ iTrack = -1;}

			if(iTrack == 1){
				m_ants.PushBack(new CCleanerAnt(
				SDL_Rect{at.x,at.y,APP_ANT_SIZE,APP_ANT_SIZE},
				SDL_Point{rand()%(12)-6,rand()%(12)-6},
				APP_CCLEANER_ANT_COLOR,iTrack ));
			}
			if(iTrack == -1){
				m_ants.PushBack(new CCleanerAnt(
				SDL_Rect{at.x,at.y,APP_ANT_SIZE,APP_ANT_SIZE},
				SDL_Point{rand()%(12)-6,rand()%(12)-6},
				APP_CCLEANER_ANT_REV_COLOR,iTrack ));
			}
		}
	}
}

void CScene::AddAnts(const SDL_Point&at, size_t szNb){
	/**********************************************************************
	 * ToDo: Generate some 'szNb' ants at location 'at', if capacity
	 * 		 is not reached.
	 */
	for(size_t k = 0; k<szNb;k++){
		if(m_ants.Card()<APP_ANT_N_MAX){
			m_ants.PushBack(new CAnt(
			SDL_Rect{at.x,at.y,APP_ANT_SIZE,APP_ANT_SIZE},
			SDL_Point{rand()%(12)-6,rand()%(12)-6},
			APP_ANT_COLOR));
		}
	}



}

void CScene::FlushAnts(){
	/**********************************************************************
	 * ToDo: Ask deleting all ant objects from the scene.
	 */
	m_ants.Flush();
}


void CScene::AddPheromone(const SDL_Rect& frame, const SDL_Point& speed){
	/**********************************************************************
	 * ToDo: Add a pheromone according to the parameters, if capacity
	 * 		 is not reached.
	 */
	if(m_pheromones.Card() < APP_PHEROMONE_N_MAX){
		m_pheromones.PushBack(new CPheromone(
			SDL_Rect{frame.x,frame.y,
			APP_PHEROMONE_SIZE,
			APP_PHEROMONE_SIZE},
			speed,
			APP_PHEROMONE_COLOR,APP_PHEROMONE_TTL_INIT));
	}

}


void CScene::DelPheromone(CPheromone*pObj){
	/**********************************************************************
	 * ToDo: Ask deleting object pObj from the scene.
	 */
	m_pheromones.DelObject(pObj);
}

void CScene::FlushPheromones(){
	/**********************************************************************
	 * ToDo: Ask deleting all pheromones objects from the scene.
	 */

	m_pheromones.Flush();
}

CPheromone*CScene::HasPheromoneAt(const SDL_Point& at) const {
	/**********************************************************************
	 * ToDo: Processing pheromone detection at location 'at' and return
	 * 		 result.
	 */

	SDL_Point At = at;
	return (CPheromone*) m_pheromones.Parse((CContainer<CPheromone>::t_ptfTV)CPheromone::ParseIsThisOjbectAtMethod, &At);
	return nullptr;

}

CObject*CScene::DelObjectsAt(const SDL_Point&at){
	/**********************************************************************
	 * ToDo: Processing deleting object(s) at location 'at' and return
	 * 		 result.
	 */
	SDL_Point pAt = at;
		m_ants.ParseDelIf((CContainer<CAnt>::t_ptfTV)CObject::ParseIsThisOjbectAtMethod, &pAt);
		m_pheromones.ParseDelIf((CContainer<CPheromone>::t_ptfTV)CObject::ParseIsThisOjbectAtMethod, &pAt);


	return nullptr;
}
