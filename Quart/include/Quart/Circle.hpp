# pragma once

# include "Drawable.hpp"

namespace Quart
{
	class Circle : public Drawable
	{
	
	private:
		int x, y;
		unsigned int diameter;
		unsigned long fillColor;
		unsigned long strokeColor;
		int strokeWidth;
		PenStyle penStyle;

	public:
		Circle(int x,
			   int y,
			   unsigned int diameter,
			   unsigned long fillColor   = 0,
			   unsigned long strokeColor = 0,
			   int strokeWidth           = 0);

		PenStyle GetPenStyle() const;
		void SetPenStyle(PenStyle style);

		std::pair<int, int> GetPosition() const;
		void SetPosition(const std::pair<int,int>& position, bool forceRedraw = true);
		void SetPosition(int x, int y, bool forceRedraw = true);

		unsigned int GetDiameter() const;
		void SetDiameter(unsigned int diameter, bool forceRedraw = true);

	private:
		void Draw(HDC&, PAINTSTRUCT&);
	};
}