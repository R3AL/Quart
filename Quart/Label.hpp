#pragma once

#include "object.hpp"

namespace Quart
{
	class Label : public Object
	{
		tstring text;
	public:
		Label(int x,
			  int y,
			  int width,
			  int height,
			  const tstring& text,
			  HWND parent = nullptr,
			  unsigned long styles = (WS_CHILD | WS_VISIBLE) );

		void Draw(HWND&,HDC&,PAINTSTRUCT&);
		void Create(HWND&);
	};
}