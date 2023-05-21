/*
 * CDisplay.h
 *
 *  Created on: 4 nov. 2022
 *      Author: thierry
 */

#ifndef CDISPLAY_H_
#define CDISPLAY_H_

#include "CObject.h"
#include <SDL2/SDL_ttf.h>

class CDisplay: public CObject {
private:
	static TTF_Font*	c_pFont;

private:
	SDL_Color		m_colorText;
	SDL_Surface*	m_pSurface;
	SDL_Texture*	m_pTexture;
	SDL_Rect		m_text;

private:
	CDisplay() = delete;

public:
	/**
	 * @brief Construct a new CDisplay object with parameter values
	 * 
	 * @param frame 
	 * @param colorText 
	 * @param colorBkgnd 
	 */
	CDisplay(const SDL_Rect&frame, const SDL_Color&colorText, const SDL_Color&colorBkgnd);

	/**
	 * @brief Destroy the CDisplay object
	 * 
	 */
	virtual ~CDisplay();

	/* Pure virtual methods implementations ---------------------*/
	
	/* Pure virtual methods implementations ---------------------*/
	/**
	 *  @brief Perform the display drawing
	 *  	   Implement the pure virtual inherited Draw() method
	 * 
	 * @param pRenderer 
	 */
	virtual void Draw(SDL_Renderer*pRenderer) const;

	/**
	 * @brief Perform the display animating
	 * 		  Implement the pure virtual inherited Animate() method
	 * 
	 * @param pArea 
	 * @return int 
	 */
	virtual int Animate(SDL_Rect*pArea);

	/**
	 * @brief Set the Text object
	 * 
	 * @param pText 	: pointer to the C-string to display
	 * @param pRenderer : pointer to the renderer to display to
	 * @return CDisplay& : the object himself
	 */
	CDisplay& SetText(char*pText, SDL_Renderer*pRenderer);
	CDisplay& SetText(const char*pText, SDL_Renderer*pRenderer);

public:
	/**
	 * @brief Perform class parameter initialization
	 * 
	 * @param fontFileNameStr : pointer to the font file name string
	 * @param fontSize 		  : size of the font
	 * @return int 			  : 0 if no error, not 0 otherwise
	 */
	static int InitGraphics(const char*fontFileNameStr, size_t fontSize);

	/**
	 * @brief Release static class resources
	 * 
	 * @return int 
	 */
	static int ReleaseGraphics();
};

#endif /* CDISPLAY_H_ */
