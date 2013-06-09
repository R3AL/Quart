# pragma once

# include "Drawable.hpp"

namespace Quart
{
	class GdiText : public Drawable
	{
	private:
		int x, y;
		tstring text;
		unsigned long textColor;

	public:
		GdiText(int x,
				int y,
				const tstring& text,
				unsigned long textColor = RGB(0, 0, 0));

		tstring GetText() const;
		void SetText(const tstring& text);

		std::pair<int, int> GetPosition() const;
		void SetPosition(const std::pair<int,int>& position, bool forceRedraw = true);
		void SetPosition(int x, int y, bool forceRedraw = true);

	private:
		void Draw(HDC&, PAINTSTRUCT&);
	};
}