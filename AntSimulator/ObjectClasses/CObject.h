/**********************************************************
 *  CObject.h
 *
 *  Created on: 18 nov. 2022
 *      Author: <Nom> <Prenom>
 *
 **********************************************************/

#ifndef COBJECT_H_
#define COBJECT_H_

#include <SDL2/SDL.h>
#include <typeinfo>

class CObject { /* Abstract class ****/
protected:
	SDL_Rect		m_frame;
	SDL_Point		m_center;
	SDL_Point		m_speed;
	SDL_Color		m_color;

protected:
	/**
	 * @brief Construct a new CObject object with default values
	 */
	CObject();

	/**
	 * @brief Construct a new CObject object with parameter values
	 * 
	 * @param frame 
	 * @param speed 
	 * @param color 
	 */
	CObject(const SDL_Rect&frame, const SDL_Point&speed, const SDL_Color&color);

	CObject(const CObject& other);

public:
	/* Virtual destructor -----------------------------------------------------*/
	/**
	 * @brief Destroy the CObject object
	 */
	virtual ~CObject();

	/* Pure virtual methods --------------------------------------------------*/
	/**
	 * @brief As a pure virtual method, make the class abstract
	 * 		  The non abstract derived classes, must implement Draw()
	 * 
	 * @param pRenderer 
	 */
	virtual void Draw(SDL_Renderer*pRenderer) const = 0;

	/**
	 * @brief As a pure virtual method, make the class abstract
	 * 		  The non abstract derived classes, must implement Animate()
	 * 
	 * @param pArea 
	 * @return int 
	 */
	virtual int Animate(SDL_Rect*pArea) = 0;

	/* Concrete methods ------------------------------------------------------*/
	/**
	 * @brief Tell if the object is over at particular point
	 * 
	 * @param pAt 	: point coordinates to check
	 * @return int  : a non null value in case of matching, zero otherwise
	 */
	int IsThisObjectAt(SDL_Point*pAt) const;

	/**
	 * @brief Tell if the object has the same hash code type of this passed by parameter
	 * 
	 * @param hashCode : type hash code to check
	 * @return int 	   : a non null value in case of matching, zero otherwise
	 */
	int IsThisObjectType(size_t hashCode) const;
	
	/**
	 * @brief Get the Location object
	 * 
	 * @return SDL_Point 
	 */
	SDL_Point GetLocation() const;

	/**
	 * @brief Get the Center object
	 * 
	 * @return SDL_Point 
	 */
	SDL_Point GetCenter() const;

	/**
	 * @brief Get the Speed object
	 * 
	 * @return SDL_Point 
	 */
	SDL_Point GetSpeed() const;

public:
	/* Static methods --------------------------------------------------------*/
	/**
	 * @brief For drawing objects from the associated container
	 * 
	 * @param pObj 		: pointer to the object issued from the container
	 * @param pRenderer : pointer to the renderer to draw in
	 * @return CObject* : nullptr to completely parsing the container
	 */
	static CObject*ParseDrawMethod(CObject*pObj, SDL_Renderer*pRenderer){
		pObj->Draw(pRenderer);
		return nullptr;
	}

	/**
	 * @brief For animating objects from the associated container
	 * 
	 * @param pObj  	: pointer to the object issued from the container
	 * @param pArea 	: pointer to the area rectangle inclosing the animating area
	 * @return CObject* : an non null value if the object get out the area, nullptr otherwise
	 */
	static CObject*ParseAnimateMethod(CObject*pObj, SDL_Rect*pArea){
		return (CObject*)(long)pObj->Animate(pArea);
	}

	/**
	 * @brief For parsing objects and checking matching location criteria
	 * 
	 * @param pObj 		: pointer to the object issued from the container
	 * @param pAt 		: pointer to the point location to check
	 * @return CObject* : an non null value if the object match the criteria, nullptr otherwise
	 */
	static CObject*ParseIsThisOjbectAtMethod(CObject*pObj, SDL_Point*pAt){
		return (CObject*)(long)pObj->IsThisObjectAt(pAt);
	}

	/**
	 * @brief For parsing objects and checking matching type hash code criteria
	 * 
	 * @param pObj 			: pointer to the object issued from the container
	 * @param pSzHashCode 	: pointer to the type hash code value to check
	 * @return CObject* 	: an non null value if the object match the criteria, nullptr otherwise
	 */
	static CObject*ParseIsThisObjectTypeMethod(CObject*pObj, size_t*pSzHashCode){
		return (CObject*)(long)pObj->IsThisObjectType(*pSzHashCode);
	}
};

#endif /* COBJECT_H_ */
