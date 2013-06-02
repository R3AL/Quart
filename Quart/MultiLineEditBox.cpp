# include "MultilineEditBox.hpp"
# include "Window.hpp"

namespace Quart
{
	MultilineEditBox::MultilineEditBox(int x, int y, int width, int height, const tstring& text, unsigned long style):
		Controller(Controller::MLEDITBOX),
		eb(x, y, width, height, text, (style | ES_MULTILINE) ),
		OnTextChanged(eb.OnTextChanged), OnFocus(eb.OnFocus), OnFocusLost(eb.OnFocusLost), OnExceedingText(OnExceedingText)
	{

	}

	void MultilineEditBox::Create(Window* parent)
	{
		this->eb.id = this->id;

		this->eb.Create(parent);
	}

	tstring MultilineEditBox::GetText() const
	{
		return this->eb.GetText();
	}

	void MultilineEditBox::SetText(const tstring& text)
	{
		this->eb.SetText(text);
	}

	void MultilineEditBox::Clear()
	{
		this->eb.Clear();
	}

	void MultilineEditBox::LimitText(unsigned int limit)
	{
		this->eb.LimitText(limit);
	}

	void MultilineEditBox::MsgHandler(WPARAM wparam, LPARAM lparam)
	{
		this->eb.MsgHandler(wparam, lparam);
	}
}