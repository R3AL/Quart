#pragma once

#include "object.hpp"

namespace Quart
{
	class MultiLineEditBox : public Object
	{
		tstring text;

	public:
		using Object::operator HWND;

		MultiLineEditBox(int x,
						int y,
						int width,
						int height,
						const tstring& text,
						unsigned long styles = (WS_CHILD | WS_VISIBLE | ES_LEFT | WS_VSCROLL | ES_AUTOVSCROLL) );

		void Draw(HWND&,HDC&,PAINTSTRUCT&);

		void Create(HWND&);

		tstring GetText() const;

	};
}