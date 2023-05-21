/*
 * CUtil.h
 *
 *  Created on: 13 oct. 2022
 *      Author: thierry
 */


class CUtil {
public:
	static int RenderDrawCircle(SDL_Renderer*pRenderer, SDL_Point ptCenter, int iRadius);
	static int RenderFillCircle(SDL_Renderer*pRenderer, SDL_Point ptCenter, int iRadius);

	static int RenderFillPolygon(SDL_Renderer*pRenderer, const SDL_Point*const pVertexes, int iVertexesCount);
	static SDL_Point GetPolygonCenter(const SDL_Point*const pVertexes, int iVertexesCount);

	static SDL_Rect InflatRect(const SDL_Rect& r, int inflat);

};

