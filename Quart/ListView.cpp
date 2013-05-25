#include "ListView.hpp"
#include <cstdarg>

namespace Quart
{
	ListView::ListView(int x, 
					   int y, 
					   int width, 
					   int height, 
					   HWND parent /* = nullptr */, 
					   unsigned long styles /* = */ ) : 
	Object(x, y, width, height, styles), collumnsNumber(0) {}

	void ListView::Draw(HWND&,HDC&,PAINTSTRUCT&) {}

	void ListView::Create(HWND& parent)
	{
		this->parent = parent;

		this->handle = CreateWindowEx(NULL,
			WC_LISTVIEW,
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
		ListView_SetExtendedListViewStyleEx(this->handle, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	}

	void ListView::AddCollumn(const tstring& txt, int index, unsigned int width)
	{
		LVCOLUMN lvc;
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.pszText = (LPTSTR)txt.c_str();
		lvc.cx = width;

		if(index == -1)
			ListView_InsertColumn(this->handle, this->collumnsNumber++, &lvc);
		else
		{
			ListView_InsertColumn(this->handle, index, &lvc);
			this->collumnsNumber++;
		}
	}

	void ListView::AddItem(unsigned int index, ...)
	{
		LVITEM lvi;
		lvi.mask = LVIF_TEXT;
		lvi.cchTextMax = 256;
		lvi.iItem = index;

		va_list list;
		va_start(list, index);

		for(unsigned i = 0; i < this->collumnsNumber; ++i)
		{
			lvi.iSubItem = i;
			lvi.pszText = (LPTSTR)(va_arg(list, tstring).c_str());
			
			if(!i)
				SendMessage(this->handle, LVM_INSERTITEM, 0, (LPARAM)&lvi);
			else
				SendMessage(this->handle, LVM_SETITEM, 0, (LPARAM)&lvi);
		}

		va_end(list);
	}

	void ListView::RemoveItem(unsigned int index)
	{
		SendMessage(this->handle, LVM_DELETEITEM, index, 0);
	}

	void ListView::ScrollTo(unsigned int index)
	{
		ListView_EnsureVisible(this->handle, index, false);
		ListView_SetItemState(this->handle, index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	}

	void ListView::EditItem(unsigned int index, ...)
	{
		LVITEM lvi;
		lvi.mask = LVIF_TEXT;
		lvi.cchTextMax = 256;
		lvi.iItem = index;

		va_list list;
		va_start(list, index);

		for(unsigned int i = 0; i < this->collumnsNumber; ++i)
		{
			lvi.iSubItem = i;
			lvi.pszText = (LPTSTR)(va_arg(list, tstring).c_str());
			SendMessage(this->handle, LVM_SETITEM, 0, (LPARAM)&lvi);
		}

		va_end(list);
	}

	void ListView::Clear()
	{
		ListView_DeleteAllItems(this->handle);
	}
}