# include "Button.hpp"
# include "Window.hpp"
# include "Messagebox.hpp"

namespace Quart
{
	Button::Button(int x, int y, int width, int height, const tstring& text, unsigned long style /* = */ ):
		Controller(x, y, Controller::BUTTON),
		width(width), height(height), text(text), style(style)
	{

	}

	void Button::Create(Window* parent)
	{
		this->handle = CreateWindowEx(
			0,
			WIDEN("BUTTON"),
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

	tstring Button::GetText() const
	{
		auto len = GetWindowTextLength(this->handle) + 1;

		auto chr = new TCHAR[len];
		GetWindowText(this->handle, chr, len);

		tstring tmp(chr);
		delete chr;

		return tmp;
	}

	void Button::SetText(const tstring& text)
	{
		SetWindowText(this->handle, static_cast<LPCTSTR>(text.c_str()) );
	}

	void Button::MsgHandler(WPARAM wparam, LPARAM lparam)
	{
		switch (wparam)
		{
		case BN_CLICKED:
			{
				if(this->OnClick != nullptr)
					this->OnClick();
			}break;

		case BN_DBLCLK:
			{
				if(this->OnDbClick != nullptr)
					this->OnDbClick();
			}break;
			
		case BN_SETFOCUS:
			{
				if(this->OnFocus != nullptr)
					this->OnFocus();
			}break;

		case BN_KILLFOCUS:
			{
				if(this->OnFocusLost != nullptr)
					this->OnFocusLost();
			}break;

		default:
			break;
		}
	}
}