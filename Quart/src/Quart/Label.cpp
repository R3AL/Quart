# include "Label.hpp"
# include "Window.hpp"
# include "Messagebox.hpp"

namespace Quart
{
	Label::Label(int x, int y, int width, int height, const tstring& text, unsigned long style /* = */ ):
		Controller(x, y, Controller::LABEL),
		width(width), height(height), text(text), style(style)
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

	tstring Label::GetText() const
	{
		auto len = GetWindowTextLength(this->handle) + 1;

		auto chr = new TCHAR[len];
		GetWindowText(this->handle, chr, len);

		tstring tmp(chr);
		delete chr;

		return tmp;
	}

	void Label::SetText(const tstring& text)
	{
		SetWindowText(this->handle, static_cast<LPCTSTR>(text.c_str()) );
	}
}