# include "SlideBar.hpp"
# include "Window.hpp"
# include "Messagebox.hpp"
# include "Label.hpp"

namespace Quart
{
	SlideBar::SlideBar(int x, int y, int width, int height, unsigned long style /* = */ ):
		Controller(Controller::SLIDEBAR),
		x(x), y(y), width(width), height(height), style(style),
		OnEndKey(nullptr), OnHomeKey(nullptr), OnLineDown(nullptr), OnLineUp(nullptr),
		OnPageDown(nullptr), OnPageUp(nullptr), /*OnNewPosition(nullptr),*/ OnChange(nullptr), OnKeyUp(nullptr)
	{

	}

	void SlideBar::Create(Window* parent)
	{
		this->handle = CreateWindowEx(
			0,
			WIDEN("msctls_trackbar32"),
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

//  		SendMessage(this->handle, TBM_SETRANGE, true, (LPARAM)MAKELONG(0, 100));
//  		SendMessage(this->handle, TBM_SETPAGESIZE, 0, 4);
// // 		SendMessage(this->handle, TBM_SETSEL, false, (LPARAM)MAKELONG(0, 100));
//  		SendMessage(this->handle, TBM_SETPOS, true, 50);

	}

	std::pair<int, int> SlideBar::GetRange() const
	{
		return std::make_pair<int, int>(SendMessage(this->handle, TBM_GETRANGEMIN, 0, 0),
										SendMessage(this->handle, TBM_GETRANGEMAX, 0, 0));
	}

	void SlideBar::SetRange(const std::pair<int, int>& range)
	{
		this->SetRange(range.first, range.second);
	}

	void SlideBar::SetRange(int min, int max)
	{
		SendMessage(this->handle, TBM_SETRANGE, min, max);
	}

	int SlideBar::GetPageSize() const
	{
		return static_cast<int>(SendMessage(this->handle, TBM_GETPAGESIZE, 0, 0));
	}

	void SlideBar::SetPageSize(int size)
	{
		SendMessage(this->handle, TBM_SETPAGESIZE, 0, size);
	}

	int SlideBar::GetSliderPos() const
	{
		return static_cast<int>(SendMessage(this->handle, TBM_GETPOS, 0, 0));
	}

	void SlideBar::SetSliderPos(int pos)
	{
		SendMessage(this->handle, TBM_SETPOS, true, pos);
	}

	void SlideBar::MsgHandler(WPARAM wparam, LPARAM lparam)
	{
		switch (wparam)
		{
		case TB_BOTTOM:
			{
				if(this->OnEndKey != nullptr)
					this->OnEndKey();
			}break;

		case TB_TOP:
			{
				if(this->OnHomeKey != nullptr)
					this->OnHomeKey();
			}break;

		case TB_ENDTRACK:
			{
				if(this->OnKeyUp != nullptr)
					this->OnKeyUp();
			}break;

		case TB_LINEDOWN:
			{
				if(this->OnLineDown != nullptr)
					this->OnLineDown();
			}break;

		case TB_LINEUP:
			{
				if(this->OnLineUp != nullptr)
					this->OnLineUp();

			}break;

		case TB_PAGEDOWN:
			{
				if(this->OnPageDown != nullptr)
					this->OnPageDown();
			}break;

		case TB_PAGEUP:
			{
				if(this->OnPageUp != nullptr)
					this->OnPageUp();
			}break;

// 		case TB_THUMBPOSITION:
// 			{
// 				if(this->OnNewPosition != nullptr)
// 					this->OnNewPosition();
// 			}break;

		case TB_THUMBTRACK:
			{
				if(this->OnChange != nullptr)
					this->OnChange();
			}break;
		}
	}
}