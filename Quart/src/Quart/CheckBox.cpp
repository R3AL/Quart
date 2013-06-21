# include "CheckBox.hpp"
# include "Window.hpp"
# include "Messagebox.hpp"

namespace Quart
{
	CheckBox::CheckBox(int x, int y, int width, int height, const tstring& text, unsigned long style /* = */ ):
		Controller(x, y, Controller::CHECKBOX),
		width(width), height(height), text(text), style(style)
	{

	}

	void CheckBox::Create(Window* parent)
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

	bool CheckBox::IsChecked() const
	{
		auto retVal = SendMessage(this->handle, BM_GETCHECK, 0, 0);

		return (retVal == BST_CHECKED);
	}

	void CheckBox::SetChecked(bool state /* = true */)
	{
		SendMessage(this->handle, BM_SETCHECK, state, 0);
	}

	void CheckBox::SetUnchecked()
	{
		this->SetChecked(false);
	}

	void CheckBox::MsgHandler(WPARAM wparam, LPARAM)
	{
		switch (wparam)
		{
		case BN_CLICKED:
			{
				auto state = this->IsChecked();
				this->SetChecked(!state);

				if(state && this->OnUncheck != nullptr)
					this->OnUncheck();
				else if(!state && this->OnCheck != nullptr)
					this->OnCheck();

			}break;

		default:
			break;
		}
	}
}