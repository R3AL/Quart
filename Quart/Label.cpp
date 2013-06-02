# include "Label.hpp"
# include "Window.hpp"

namespace Quart
{
	Label::Label(int x, int y, int width, int height, const tstring& text, unsigned long style /* = */ ):
		Controller(Controller::LABEL),
		x(x), y(y), width(width), height(height), text(text), style(style), 
		OnClick(nullptr), OnDbClick(nullptr)
	{

	}

	void Label::Create(Window* parent)
	{
		this->handle = CreateWindowEx(
			0,
			WIDEN("static"),
			this->text.c_str(),
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

	void Label::MsgHandler(WPARAM wparam, LPARAM lparam)
	{
		switch (wparam)
		{
		case STN_CLICKED:
			{
				if(this->OnClick != nullptr)
					this->OnClick();
			}break;

		case STN_DBLCLK:
			{
				if(this->OnDbClick != nullptr)
					this->OnDbClick();
			}break;

		default:
			break;
		}
	}
}