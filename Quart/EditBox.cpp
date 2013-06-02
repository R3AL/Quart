# include "EditBox.hpp"
# include "Window.hpp"

namespace Quart
{
	EditBox::EditBox(int x, int y, int width, int height, const tstring& text, unsigned long style /* = */ ):
		Controller(Controller::EDITBOX),
		x(x), y(y), width(width), height(height), text(text), style(style), IgnoreTextChange(true),
		OnTextChanged(nullptr), OnFocus(nullptr), OnFocusLost(nullptr), OnExceedingText(nullptr)
	{

	}

	void EditBox::Create(Window* parent)
	{
		this->handle = CreateWindowEx(
			0,
			WIDEN("EDIT"),
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
		{
			ERRORMB();
			return;
		}

		this->IgnoreTextChange = false;
	}

	tstring EditBox::GetText() const
	{
		auto len = GetWindowTextLength(this->handle) + 1;

		auto chr = new TCHAR[len];
		GetWindowText(this->handle, chr, len);

		tstring tmp(chr);
		delete chr;

		return tmp;
	}

	void EditBox::SetText(const tstring& text)
	{
		SetWindowText(this->handle, static_cast<LPCTSTR>(text.c_str()) );
	}

	void EditBox::Clear()
	{
		this->SetText(WIDEN(""));
	}

	void EditBox::LimitText(unsigned int limit)
	{
		SendMessage(this->handle, EM_LIMITTEXT, (WPARAM)limit, 0);
	}

	void EditBox::MsgHandler(WPARAM wparam, LPARAM lparam)
	{
		switch (wparam)
		{
		case EN_CHANGE:
			{
				if(!this->IgnoreTextChange && this->OnTextChanged != nullptr)
					this->OnTextChanged();
			}break;

		case EN_SETFOCUS:
			{
				if(this->OnFocus != nullptr)
					this->OnFocus();
			}break;

		case EN_KILLFOCUS:
			{
				if(this->OnFocusLost != nullptr)
					this->OnFocusLost();
			}break;

		case EN_MAXTEXT:
			{
				if(this->OnExceedingText != nullptr)
					this->OnExceedingText();
			}break;

		default:
			break;
		}
	}
}