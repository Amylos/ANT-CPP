/**********************************************************
 *  CPheromone.h
 *
 *  Created on: 17 dec. 2021
 *      Author: <Nom> <Prenom>
 *
 **********************************************************/

#ifndef CPHEROMONE_H_
#define CPHEROMONE_H_

#include "CObject.h"

class CPheromone : public CObject {
private:
	int			m_ttl;

private:
	CPheromone() = delete;
public:
	/**
	 * @brief Construct a new CPheromone object with parameter values
	 * 
	 * @param frame : location and size of pheromone object
	 * @param speed : speed parameter for track characteristics
	 * @param color : pheromone color object
	 * @param ttl 	: initial Time To Live
	 */
	CPheromone(const SDL_Rect&frame, const SDL_Point&speed, const SDL_Color&color, int ttl);

	/**
	 * @brief Destroy the CPheromone object
	 * 
	 */
	virtual ~CPheromone();

	/* Pure virtual methods implementations ---------------------*/
	/**
	 *  @brief Perform the pheromone drawing
	 *  	   Implement the pure virtual inherited Draw() method
	 * 
	 * @param pRenderer 
	 */	
	virtual void Draw(SDL_Renderer*pRenderer)const;

	/**
	 * @brief Perform the pheromone animating
	 * 		  Implement the pure virtual inherited Animate() method
	 * 
	 * @param pArea 
	 * @return int 
	 */	
	virtual int Animate(SDL_Rect*pArea);

	/**
	 * @brief Increase the pheromone TTL by ttlInc
	 * 
	 * @param ttlInc : TTL units for increment
	 */
	void IncreaseTTL(int ttlInc=1);

private:
	/**
	 * @brief Perform pheromone aging mechanism
	 * 
	 * @return int : non null value if pheromone TTL reached 0, null value otherwise
	 */
	int Growup();

};

#endif /* CPHEROMONE_H_ */
