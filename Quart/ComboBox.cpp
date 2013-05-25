#include "ComboBox.hpp"
#include <CommCtrl.h>
#include <windowsx.h>

namespace Quart
{
	ComboBox::ComboBox(int id, 
					   int x, 
					   int y, 
					   int width, 
					   int height, 
					   HWND parent /* = nullptr */, 
					   unsigned long styles /* = */ ) : Object(id, x, y, width, height, styles) {}

	void ComboBox::Draw(HWND&,HDC&,PAINTSTRUCT&) {}

	void ComboBox::Create(HWND& parent)
	{
		this->parent = parent;

		this->handle = CreateWindowEx(NULL,
			WC_COMBOBOX,
			WIDEN(""),
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

	void ComboBox::Add(const tstring& txt)
	{
		ComboBox_AddString(this->handle, LPCTSTR(txt.c_str()));
		this->items.emplace_back(txt);
		
		if(this->items.size() == 1)
			ComboBox_SetCurSel(this->handle, 0);
	}

	void ComboBox::Remove(const unsigned int index)
	{
		ComboBox_DeleteString(this->handle, index);
	}

	unsigned int ComboBox::SelectionIndex() const
	{
		return SendMessage(this->handle, CB_GETCURSEL, 0, 0);
	}

}