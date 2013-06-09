# include "GdiText.hpp"
# include "Window.hpp"

namespace Quart
{
	GdiText::GdiText(int x, int y, const tstring& text, unsigned long textColor):
		x(x), y(y), text(text), textColor(textColor)
	{

	}

	void GdiText::Draw(HDC& hdc, PAINTSTRUCT&)
	{
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, this->textColor);
		TextOut(hdc, this->x, this->y, this->text.c_str(), this->text.length());
	}

	tstring GdiText::GetText() const
	{
		return this->text;
	}

	void GdiText::SetText(const tstring& text)
	{
		this->text = text;
	}

	std::pair<int,int> GdiText::GetPosition() const
	{
		return std::make_pair(this->x, this->y);
	}

	void GdiText::SetPosition(const std::pair<int,int>& position, bool forceRedraw)
	{
		this->SetPosition(position.first, position.second, forceRedraw);
	}

	void GdiText::SetPosition(int x, int y, bool forceRedraw)
	{
		this->x = x;
		this->y = y;

		if(forceRedraw)
			this->parent->Redraw();
	}
}