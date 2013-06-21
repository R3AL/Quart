# pragma once

# include "Drawable.hpp"
# include "../Controller.hpp"

# include <utility>

namespace Quart
{
	namespace Gdi
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
			friend class BarChart;

		private:
			int x1, y1, x2, y2;
			long strokeColor;
			int strokeWidth;
			PenStyle penStyle;

		public:
			Line(int x1,
				 int y1,
				 int x2,
				 int y2,
				 rgb strokeColor           = rgb(),
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

			int GetStrokeWidth() const;
			void SetStrokeWidth(int width, bool forceRedraw = true);
			
			rgb GetStrokeColor() const;
			void SetStrokeColor(const rgb& color, bool forceRedraw = true);

		private:
			void Draw(HDC&, PAINTSTRUCT&);
		};
	}
}