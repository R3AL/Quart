# include "UpDown.hpp"
# include "Window.hpp"
# include "Messagebox.hpp"

namespace Quart
{
	UpDown::UpDown(int x, int y, int width, int height, int minval, int maxval, unsigned long style /* = */ ):
		Controller(Controller::UPDOWN),
		x(x), y(y), width(width), height(height), style(style),
		range(minval, maxval), readyForChange(false),
		buddy(new EditBox(x, y, width, height, to_tstring(minval), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_LEFT)),
		OnValueChanged(nullptr), OnFocus(buddy->OnFocus), OnFocusLost(buddy->OnFocusLost)
	{

	}

	void UpDown::Create(Window* parent)
	{
		this->buddy->id = this->id;
		this->buddy->Create(parent);

		this->handle = CreateWindowEx(
			WS_EX_LEFT | WS_EX_LTRREADING,
			WIDEN("msctls_updown32"),
			nullptr,
			WS_CHILD | WS_VISIBLE | UDS_AUTOBUDDY | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK,
			0, 
			0,
			0, 
			0,
			parent->GetHandle(),
			0,
			GetModuleHandle(0),
			nullptr);


		if(!this->handle)
		{
			ERRORMB();
			return;
		}

		this->SetRange(this->range);
	}

	std::pair<int, int> UpDown::GetRange() const
	{
		return this->range;
	}

	void UpDown::SetRange(const std::pair<int, int>& range)
	{
		if(this->range != range)
			this->range = range;
	
		SendMessage(this->handle, UDM_SETRANGE32, this->range.first, this->range.second);
	}

	void UpDown::SetRange(int minval, int maxval)
	{
		this->SetRange(std::make_pair(minval, maxval));
	}

	int UpDown::GetValue() const
	{
		return static_cast<int>(SendMessage(this->handle, UDM_GETPOS32, 0, 0));
	}

	void UpDown::SetValue(int value)
	{
		SendMessage(this->handle, UDM_SETPOS32, 0, value);
	}

	void UpDown::MsgHandler(WPARAM wparam, LPARAM lparam)
	{
		switch (wparam)
		{
		case 256: 
				this->readyForChange = true; 
			break;
		case 768:
			{
				if(this->readyForChange && this->OnValueChanged != nullptr)
				{
					this->OnValueChanged();
					this->readyForChange = false;
				}
			}break;
		}
	}
}