# include "VerticalText.hpp"

# include <strsafe.h>

namespace Quart
{
	namespace Gdi
	{
		VerticalText::VerticalText(int x, int y, const tstring& text, rgb textColor):
			Text(x, y, text, textColor)
		{

		}

		void VerticalText::Draw(HDC& hdc, PAINTSTRUCT& ps)
		{
			SetGraphicsMode(hdc, GM_ADVANCED);

			LOGFONT font          = {0};

			font.lfHeight         = 0;
			font.lfWidth          = 0;
			font.lfEscapement     = 900;
			font.lfOrientation	  = 900;
			font.lfWeight         = 0;
			font.lfItalic         = false;
			font.lfUnderline      = false;
			font.lfStrikeOut      = false;
			font.lfCharSet        = DEFAULT_CHARSET;
			font.lfOutPrecision   = OUT_DEFAULT_PRECIS;
			font.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
			font.lfQuality        = CLEARTYPE_QUALITY;
			font.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

			auto newfont = CreateFontIndirect(&font);
			auto oldfont = SelectObject(hdc, newfont);

			Text::Draw(hdc, ps);

			SelectObject(hdc, oldfont);

			SetGraphicsMode(hdc, GM_COMPATIBLE);

			DeleteObject(newfont);
		}

		std::pair<int,int> VerticalText::GetSize() const
		{
			return std::make_pair(this->size.second, this->size.first);
		}
	}
}