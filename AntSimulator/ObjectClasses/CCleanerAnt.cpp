/*
 * CCleanerAnt.cpp
 *
 *  Created on: 25 nov. 2022
 *      Author: andre
 */

#include <CCleanerAnt.h>
#include <iostream>

CCleanerAnt::CCleanerAnt(const SDL_Rect&frame, const SDL_Point&speed, const SDL_Color&color, int iTrack):
	CAnt(frame, speed, color),
	m_iTrackingDirection(iTrack)
{}

CCleanerAnt::~CCleanerAnt(){
}

int CCleanerAnt::Animate(SDL_Rect*pArea){

	m_frame.x += m_speed.x;
	m_frame.y += m_speed.y;

	m_center.x = m_frame.x + m_frame.w /2;
	m_center.y = m_frame.y + m_frame.h /2;

	CPheromone* pPheromone = c_pScene->HasPheromoneAt(m_center);

    if(pPheromone){
        if(m_iTrackingDirection == -1){
            m_speed = pPheromone->GetSpeed();
        }
        else if(m_iTrackingDirection == 1){
            m_speed = pPheromone->GetSpeed();
            m_speed.x *= -1;
            m_speed.y *= -1;
        }
    }
    c_pScene->DelPheromone(pPheromone);

	return !SDL_HasIntersection(pArea, &m_frame);
}
