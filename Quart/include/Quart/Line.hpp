# pragma once

# include "Drawable.hpp"

namespace Quart
{
	struct Point2
	{
		int x1, y1, x2, y2;
		Point2(int x1, int y1, int x2, int y2);

		Point2& operator+=(const Point2&);
		Point2& operator-=(const Point2&);
		Point2& operator*=(const Point2&);
		Point2& operator/=(const Point2&);
	};

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

		Point2 GetPosition() const;
		void SetPosition(const Point2& position, bool forceRedraw         = true);
		void SetPosition(int x1, int y1, int x2, int y2, bool forceRedraw = true);

		std::pair<int, int> GetPoint1() const;
		std::pair<int, int> GetPoint2() const;
		void SetPoint1(const std::pair<int,int>& position, bool forceRedraw = true);
		void SetPoint1(int x, int y, bool forceRedraw                       = true);
		void SetPoint2(const std::pair<int,int>& position, bool forceRedraw = true);
		void SetPoint2(int x, int y, bool forceRedraw                       = true);

	private:
		void Draw(HDC&, PAINTSTRUCT&);
	};
}