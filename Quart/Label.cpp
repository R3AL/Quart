#include "Label.hpp"

namespace Quart
{
	Label::Label(int id, 
				 int x, 
				 int y, 
				 int width, 
				 int height, 
				 const tstring& text, 
				 HWND parent /* = nullptr */, 
				 unsigned long styles /* = */ ): Object(id, x, y, width, height, styles), text(text) {}

	void Label::Draw(HWND&,HDC&,PAINTSTRUCT&) {}

	void Label::Create(HWND& parent)
	{
		this->parent = parent;

		this->handle = CreateWindowEx(NULL,
			WIDEN("static"),
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
}