# pragma once

# include "Drawable.hpp"

namespace Quart
{
	class Circle : public Drawable
	{
	
	private:
		int x, y;
		unsigned int radius;
		unsigned long fillColor;
		unsigned long strokeColor;
		int strokeWidth;
		PenStyle penStyle;

	public:
		Circle(int x,
			   int y,
			   unsigned int radius,
			   unsigned long fillColor   = 0,
			   unsigned long strokeColor = 0,
			   int strokeWidth           = 0);

		PenStyle GetPenStyle() const;
		void SetPenStyle(PenStyle style);

	private:
		void Draw(HDC&, PAINTSTRUCT&);
	};
}