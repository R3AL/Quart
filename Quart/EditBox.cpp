#include "EditBox.hpp"
#include <windowsx.h>

namespace Quart
{
	EditBox::EditBox(int x, 
					 int y, 
					 int width, 
					 int height, 
					 const tstring& text, 
					 HWND parent /* = nullptr */, 
					 unsigned long styles /* = */ ) : Object(x, y, width, height, styles), text(text) {}

	void EditBox::Draw(HWND&,HDC&,PAINTSTRUCT&) {}

	void EditBox::Create(HWND& parent)
	{
		this->parent = parent;

		this->handle = CreateWindowEx(NULL,
			WIDEN("EDIT"),
			this->text.c_str(),
			this->styles,
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

	tstring EditBox::GetText() const
	{
		auto len = GetWindowTextLength(this->handle) + 1;

		auto chr = new TCHAR[len];
		GetWindowText(this->handle, chr, len);

		tstring tmp(chr);
		delete chr;

		return tmp;
	}

	void EditBox::SetText(const tstring& txt)
	{
		Edit_SetText(this->handle, txt.c_str());
	}

	void EditBox::Clear()
	{
		Edit_SetText(this->handle, "");
	}
}