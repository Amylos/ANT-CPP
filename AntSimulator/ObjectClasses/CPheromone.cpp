/**********************************************************
 *  CPheromone.cpp
 *
 *  Created on: 17 dec. 2021
 *      Author: <Nom> <Prenom>
 *
 **********************************************************/

#include <CPheromone.h>
#include <algorithm>
using namespace std;
#include <defines.h>
#include <CUtil.h>

CPheromone::CPheromone(const SDL_Rect&frame, const SDL_Point&speed, const SDL_Color&color, int ttl) :
	CObject(frame, speed, color),
	m_ttl(ttl)
{}

CPheromone::~CPheromone() {
}

void CPheromone::Draw(SDL_Renderer*pRenderer)const{
	/**********************************************************************
	 * ToDo: Draw an pheromone object.
	 */

	SDL_SetRenderDrawColor(pRenderer, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRect(pRenderer, &m_frame);

}

int CPheromone::Growup(){
	/**********************************************************************
	 * ToDo: Get older an pheromone object.
	 * Change the return statement to conform description
	 * towards m_ttl limit.
	 */

	m_ttl--;
	if(m_ttl == 0) return 1;

	return 0;
}


int CPheromone::Animate(SDL_Rect*pArea){
	/**********************************************************************
	 * ToDo: ToDo
	 */


	int ret = Growup();
	return ret;
}

void CPheromone::IncreaseTTL(int ttlInc) {
	/**********************************************************************
	 * ToDo: ToDo
	 */

	m_ttl+=ttlInc;

}
