# include "Text.hpp"
# include "..\Window.hpp"

# include <strsafe.h>

namespace Quart
{
	namespace Gdi
	{
		Text::Text(int x, int y, const tstring& text, rgb textColor):
			x(x), y(y), text(text), textColor(textColor), size(0,0)
		{

		}

		void Text::Draw(HDC& hdc, PAINTSTRUCT&)
		{
			if(size.first == 0 && size.second == 0)
			{
				SIZE sz = {0};

				GetTextExtentPoint32(hdc, this->text.c_str(), this->text.length(), &sz);

				this->size.first  = sz.cx;
				this->size.second = sz.cy;
			}

			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, this->textColor);

			TextOut(hdc, this->x, this->y, this->text.c_str(), this->text.length());
		}

		tstring Text::GetText() const
		{
			return this->text;
		}

		void Text::SetText(const tstring& text)
		{
			this->text = text;

			this->parent->Redraw();
		}

		std::pair<int,int> Text::GetPosition() const
		{
			return std::make_pair(this->x, this->y);
		}

		void Text::SetPosition(const std::pair<int,int>& position, bool forceRedraw)
		{
			this->SetPosition(position.first, position.second, forceRedraw);
		}

		void Text::SetPosition(int x, int y, bool forceRedraw)
		{
			this->x = x;
			this->y = y;

			if(forceRedraw)
				this->parent->Redraw();
		}

		rgb Text::GetColor() const
		{
			return this->textColor;
		}

		void Text::SetColor(const rgb& color, bool forceRedraw /* = true */)
		{
			this->textColor = color;

			if(forceRedraw)
				this->parent->Redraw();
		}

		std::pair<int,int> Text::GetSize() const
		{
			return this->size;
		}
	}
}