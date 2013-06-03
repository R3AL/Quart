# include "ListView.hpp"
# include "Window.hpp"

# include <cstdarg>

namespace Quart
{
	ListView::ListView(int x, int y, int width, int height, unsigned long style /* = */ ):
		Controller(Controller::LISTVIEW),
		x(x), y(y), width(width), height(height), style(style),
		collumnsNumber(0)
	{

	}

	void ListView::Create(Window* parent)
	{
		this->handle = CreateWindowEx(
			0,
			WIDEN("SysListView32"),
			nullptr,
			this->style,
			this->x,
			this->y,
			this->width,
			this->height,
			parent->GetHandle(),
			(HMENU)this->id,
			GetModuleHandle(0),
			nullptr);

		if(!this->handle)
			ERRORMB();
	}

	void ListView::AddCollumn(const tstring& text, int index /* = -1 */, unsigned int width /* = 100 */)
	{
		LVCOLUMN lvc;
		lvc.mask    = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.pszText = (LPTSTR)text.c_str();
		lvc.cx      = width;

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
		lvi.mask       = LVIF_TEXT;
		lvi.cchTextMax = 256;
		lvi.iItem      = index;

		va_list list;
		va_start(list, index);

		for(unsigned i = 0; i < this->collumnsNumber; ++i)
		{
			lvi.iSubItem = i;
			lvi.pszText = (LPTSTR)(va_arg(list, TCHAR*));

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
		SendMessage(this->handle, LVM_ENSUREVISIBLE, index, MAKELPARAM(false, 0));
	}

	void ListView::Select(unsigned int index)
	{
		LV_ITEM li;
		li.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
		li.state = LVIS_SELECTED | LVIS_FOCUSED;

		SendMessage(this->handle, LVM_SETITEMSTATE, index, reinterpret_cast<LPARAM>(&li));
	}

	void ListView::Unselect(unsigned int index /* = -1 */)
	{
		LV_ITEM li;
		li.stateMask = LVIS_SELECTED;
		li.state     = 0;

		SendMessage(this->handle, LVM_SETITEMSTATE, index, reinterpret_cast<LPARAM>(&li) );
	}

	int ListView::Count() const
	{
		return static_cast<int>(SendMessage(this->handle, LVM_GETITEMCOUNT, 0, 0));
	}

	void ListView::Clear()
	{
		SendMessage(this->handle, LVM_DELETEALLITEMS, 0, 0);
	}

	void ListView::EditItem(unsigned int index, ...)
	{
		LVITEM lvi;
		lvi.mask       = LVIF_TEXT;
		lvi.cchTextMax = 256;
		lvi.iItem      = index;

		va_list list;
		va_start(list, index);

		for(unsigned int i = 0; i < this->collumnsNumber; ++i)
		{
			lvi.iSubItem = i;
			lvi.pszText  = (LPTSTR)(va_arg(list, TCHAR));
			SendMessage(this->handle, LVM_SETITEM, 0, (LPARAM)&lvi);
		}

		va_end(list);
	}

	int ListView::SelectionIndex() const
	{
		int retval = -1;

		auto end = this->Count();

		for(auto i = 0; i < end; ++i)
		{
			if((static_cast<unsigned int>(SendMessage(this->handle, LVM_GETITEMSTATE, i, LVIS_SELECTED)) == LVIS_SELECTED))
			{
				retval = i;
				break;
			}
		}

		return retval;
	}

	void ListView::MsgHandler(WPARAM wparam, LPARAM lparam)
	{

	}
}