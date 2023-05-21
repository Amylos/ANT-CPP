/*
 * CCleanerAnt.h
 *
 *  Created on: 25 nov. 2022
 *      Author: andre
 */

#include<CAnt.h>
#include<CPheromone.h>
#include<CScene.h>

#ifndef CCLEANERANT_H_
#define CCLEANERANT_H_

class CCleanerAnt : public CAnt{
private:
	int m_iTrackingDirection;
public:
	CCleanerAnt() = delete;
	CCleanerAnt(const SDL_Rect&frame, const SDL_Point&speed, const SDL_Color&color, int iTrack);
	virtual ~CCleanerAnt();

	virtual int Animate(SDL_Rect*pArea);

};

#endif /* CCLEANERANT_H_ */
