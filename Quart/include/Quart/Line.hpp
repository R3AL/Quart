# pragma once

# include "Drawable.hpp"

namespace Quart
{
	class Line : public Drawable
	{
	private:
		int x1, y1, x2, y2;
		unsigned long strokeColor;
		int strokeWidth;
		PenStyle penStyle;

	public:
		Line(int x1,
			 int y1,
			 int x2,
			 int y2,
			 unsigned long strokeColor = 0,
			 int strokeWidth           = 0);

		PenStyle GetPenStyle() const;
		void SetPenStyle(PenStyle style);

	private:
		void Draw(HDC&, PAINTSTRUCT&);
	};
}