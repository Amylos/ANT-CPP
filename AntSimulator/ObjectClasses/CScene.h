/**********************************************************
 *  CScene.h
 *
 *  Created on: 17 dec. 2021
 *      Author: <Nom> <Prenom>
 *
 **********************************************************/

#ifndef CSCENE_H_
#define CSCENE_H_

#include <CContainer.h>
#include <CDisplay.h>
#include <CAnt.h>
#include <CCleanerAnt.h>
#include <CPheromone.h>
#include<cstdio>
#include<defines.h>

class CScene : public CObject {
private:
	CContainer<CAnt>			m_ants{};
	CContainer<CPheromone>		m_pheromones{};
	CDisplay	m_display{
					{APP_DISPLAY_LEFT,APP_DISPLAY_TOP,APP_DISPLAY_WIDTH,APP_DISPLAY_HEIGHT},
					{0xD0,0xFF,0x00,0xFF},
					{0x80,0x80,0x80,0xFF}
				};
	SDL_Rect	m_antHill;

private:
	CScene() = delete;	/* this constructor is suppressed from the class */
public:
	/**
	 * @brief Construct a new CScene object with parameter values
	 * 
	 * @param frame 
	 * @param color 
	 * @param pRenderer 
	 */
	CScene(const SDL_Rect&frame, const SDL_Color&color, SDL_Renderer*pRenderer);

	/**
	 * @brief Destroy the CScene object
	 * 
	 */
	virtual ~CScene();

	/* Pure virtual methods implementations ---------------------*/
	/**
	 * @brief Perform the scene drawing
	 * 		  Implement the pure virtual inherited Draw() method
	 * 
	 * @param pRenderer 
	 */
	virtual void Draw(SDL_Renderer*pRenderer) const;

	/**
	 * @brief Perform the scene animating
	 * 		  Implement the pure virtual inherited Animate() method
	 * 
	 * @param pArea 
	 * @return int 
	 */
	virtual int Animate(SDL_Rect*pArea);
	/**
	 * @brief An overloaded version of Animate : Not Virtual
	 * 
	 * @param pArea 
	 * @param pRenderer 
	 * @return int 
	 */
			int Animate(SDL_Rect*pArea, SDL_Renderer*pRenderer);

	/**
	 * @brief Add a random number of ants objects in the simulation
	 */
	void RandomAddAnts();

	/**
	 * @brief Add a 'szNb' number of ants objects in the simulation at location 'at'
	 * 
	 * @param at 	: location where to add ants
	 * @param szNb 	: number of ants to add
	 */
	void AddAnts(const SDL_Point& at, size_t szNb=1);



	void AddCCleanerAnts(const SDL_Point&at, size_t szNb);
	/**
	 * @brief Delete all the ants contained in the simulation
	 */
	void FlushAnts();

	/**
	 * @brief Add an new pheromone object in the simulation
	 * 
	 * @param frame : location and size of the pheromone
	 * @param speed : speed characteristics of the pheromone track
	 */
	void AddPheromone(const SDL_Rect& frame, const SDL_Point& speed);

	/**
	 * @brief Destroy a specific pheromone object
	 * 
	 * @param pObj : pointer to the specific pheromone object to destroy
	 */
	void DelPheromone(CPheromone*pObj);

	/**
	 * @brief Delete all the pheromones contained in the simulation
	 */
	void FlushPheromones();

	/**
	 * @brief Tell if some pheromone is found at location 'at'
	 * 
	 * @param at 	: location to check
	 * @return CPheromone* 	: return a pointer to the found pheromone if so, nullptr otherwise
	 */
	CPheromone*HasPheromoneAt(const SDL_Point& at) const;

	/**
	 * @brief Destroy the object(s) found at location 'at'
	 * 
	 * @param at 		: location where to destroy object(s)
	 * @return CObject* : nullptr
	 */
	CObject*DelObjectsAt(const SDL_Point& at);

	void Clone(){
		CContainer<CAnt>* pClone = new CContainer<CAnt>(m_ants);
		m_ants = *pClone;
		delete pClone;
	}


private:
	/**
	 * @brief Container delete method
	 * 
	 * @param pObj 		: pointer to the object to delete
	 * @return CObject* : nullptr
	 */
	static CObject*ObjectDeleteMethod(CObject*pObj){
		delete pObj;
		return nullptr;
	}
};

#endif /* CSCENE_H_ */
