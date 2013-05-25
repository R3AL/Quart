#include "MultiLineEditBox.hpp"

namespace Quart
{
	MultiLineEditBox::MultiLineEditBox( int x, 
										int y, 
										int width, 
										int height, 
										const tstring& text, 
										unsigned long styles /* = */ ) : 
	Object(x, y, width, height, styles), text(text) {}

	void MultiLineEditBox::Draw(HWND&,HDC&,PAINTSTRUCT&) {}

	void MultiLineEditBox::Create(HWND& parent)
	{
		this->parent = parent;
		this->handle = CreateWindowEx(NULL,
			WIDEN("EDIT"),
			this->text.c_str(),
			(this->styles | ES_MULTILINE),
			this->x,
			this->y,
			this->width,
			this->height,
			this->parent,
			(HMENU)this->id,
			(HINSTANCE)GetWindowLongPtr(this->parent, GWL_HINSTANCE),
			NULL);
		ShowWindow(this->handle, SW_SHOW);
	}

	tstring MultiLineEditBox::GetText() const
	{
		int len = GetWindowTextLength(this->handle);

		TCHAR* chr = new TCHAR[len + 1];
		GetWindowText(this->handle, chr, len);

		tstring tmp(chr);
		delete chr;

		return tmp;
	}

}