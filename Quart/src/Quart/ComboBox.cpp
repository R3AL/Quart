# include "ComboBox.hpp"
# include "Window.hpp"
# include "Messagebox.hpp"

# include <windowsx.h>

namespace Quart
{
	ComboBox::ComboBox(int x, int y, int width, int height, unsigned long style /* = */ ):
		Controller(x, y, Controller::COMBOBOX),
		width(width), height(height), style(style),
		elementCount(0)
	{

	}

	void ComboBox::Create(Window* parent)
	{
		this->handle = CreateWindowEx(
			0,
			WIDEN("ComboBox"),
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

	void ComboBox::Add(const tstring& text)
	{
		SendMessage(this->handle, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(static_cast<LPCTSTR>(text.c_str())) );
		this->elementCount++;
	}

	void ComboBox::Remove(unsigned int index)
	{
		if( SendMessage(this->handle, CB_DELETESTRING, index, 0) != CB_ERR)
			this->elementCount--;
	}

	unsigned int ComboBox::Count() const
	{
		return this->elementCount;
	}

	int ComboBox::SelectionIndex() const
	{
		return static_cast<int>(SendMessage(this->handle, CB_GETCURSEL, 0, 0) );
	}

	void ComboBox::Select(unsigned int index)
	{
		SendMessage(this->handle, CB_SETCURSEL, index, 0);
	}

	void ComboBox::MsgHandler(WPARAM wparam, LPARAM lparam)
	{
		switch (wparam)
		{
		case CBN_CLOSEUP:
			{
				if(this->OnListClose != nullptr)
					this->OnListClose();
			}break;

		case CBN_DROPDOWN:
			{
				if(this->OnListOpen != nullptr)
					this->OnListOpen();
			}break;

		case CBN_EDITCHANGE:
			{
				if(this->OnElementEdit != nullptr)
					this->OnElementEdit();
			}break;

		case CBN_SETFOCUS:
			{
				if(this->OnFocus != nullptr)
					this->OnFocus();
			}break;

		case CBN_KILLFOCUS:
			{
				if(this->OnFocusLost != nullptr)
					this->OnFocusLost();
			}break;

		case CBN_SELCHANGE:
			{
				if(this->OnSelectionChanged != nullptr)
					this->OnSelectionChanged();
			}break;

		case CBN_SELENDCANCEL:
			{
				if(this->OnSelectionCanceled != nullptr)
					this->OnSelectionCanceled();
			}break;


		default:
			break;
		}
	}
}