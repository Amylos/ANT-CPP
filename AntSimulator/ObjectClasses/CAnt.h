/**********************************************************
 *  CAnt.h
 *
 *  Created on: 17 dec. 2021
 *      Author: <Nom> <Prenom>
 *
 **********************************************************/

#ifndef CANT_H_
#define CANT_H_


#include "CObject.h"
class CScene;

class CAnt : public CObject {
protected:
	static CScene*		c_pScene;

private:

protected:
	CAnt() = delete;
public:
	/**
	 * @brief Construct a new CAnt object with parameter values
	 * 
	 * @param frame 
	 * @param speed 
	 * @param color 
	 */
	CAnt(const SDL_Rect&frame, const SDL_Point&speed, const SDL_Color&color);


	/**
	 * @brief Destroy the CAnt object
	 */
	virtual ~CAnt();

	/* Pure virtual methods implementations ---------------------*/
	/**
	 *  @brief Perform the ant drawing
	 *  		  Implement the pure virtual inherited Draw() method
	 * 
	 * @param pRenderer 
	 */
	virtual void Draw(SDL_Renderer*pRenderer) const;

	/**
	 * @brief Perform the ant animating
	 * 		  Implement the pure virtual inherited Animate() method
	 * 
	 * @param pArea 
	 * @return int 
	 */
	virtual int Animate(SDL_Rect*pArea);

public:
	/**
	 * @brief Perform class parameter initialization
	 * 
	 * @param pScene : pointer to the CScene object
	 * @return int 	 : 0
	 */
	static int InitGraphics(CScene*pScene);

	/**
	 * @brief Release static class resources
	 * 
	 * @return int : 0
	 */
	static int ReleaseGraphics();
};

#endif /* CANT_H_ */
