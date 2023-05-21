/*
 * CDisplay.cpp
 *
 *  Created on: 4 nov. 2022
 *      Author: thierry
 */

#include "CDisplay.h"
#include <defines.h>
#include <CUtil.h>

CDisplay::CDisplay(const SDL_Rect&frame, const SDL_Color&colorText, const SDL_Color&colorBkgnd):
	CObject(frame, {0}, colorBkgnd),
	m_colorText(colorText),
	m_pSurface(nullptr),
	m_pTexture(nullptr),
	m_text(CUtil::InflatRect(frame, -APP_DISPLAY_PADDING))
{}

CDisplay::~CDisplay() {
	if(m_pSurface) SDL_FreeSurface(m_pSurface);
	if(m_pTexture) SDL_DestroyTexture(m_pTexture);
}

void CDisplay::Draw(SDL_Renderer*pRenderer) const { /*virtual*/
	SDL_SetRenderDrawColor(pRenderer, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRect(pRenderer, &m_frame);
	if(m_pTexture){
		SDL_Rect r{m_text.x, m_text.y, m_pSurface->w, m_text.h};
		SDL_RenderCopy(pRenderer, m_pTexture, nullptr, &r);
	}
}

int CDisplay::Animate(SDL_Rect*pArea){ /*virtual*/
	return 0;
}

CDisplay& CDisplay::SetText(char*pText, SDL_Renderer*pRenderer){
	if(m_pSurface) SDL_FreeSurface(m_pSurface);
	if(m_pTexture) SDL_DestroyTexture(m_pTexture);
	m_pSurface = TTF_RenderText_Blended(c_pFont, pText, m_colorText);
	m_pTexture = SDL_CreateTextureFromSurface(pRenderer, m_pSurface);
	return *this;
}

CDisplay& CDisplay::SetText(const char*pText, SDL_Renderer*pRenderer){
	return SetText((char*)pText, pRenderer);
}



TTF_Font* CDisplay::c_pFont{nullptr}; /* static */

int CDisplay::InitGraphics(const char*fontFileNameStr, size_t fontSize){ /* static */
	TTF_Init();
	if(c_pFont) TTF_CloseFont(c_pFont);
	c_pFont = TTF_OpenFont(fontFileNameStr, fontSize);
	if(c_pFont==nullptr){
		SDL_Log("Failed to load font: %s", SDL_GetError());
		return -1;
	}
	return 0;
}

int CDisplay::ReleaseGraphics(){ /* static */
	if(c_pFont) TTF_CloseFont(c_pFont);
	TTF_Quit();
	return 0;
}

