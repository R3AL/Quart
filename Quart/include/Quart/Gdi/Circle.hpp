# pragma once

# include "Drawable.hpp"

namespace Quart
{
	namespace Gdi
	{
		class Circle : public Drawable
		{
	
		private:
			int x, y;
			unsigned int diameter;
			long fillColor;
			long strokeColor;
			int strokeWidth;
			PenStyle penStyle;

		public:
			Circle(int x,
				   int y,
				   unsigned int diameter,
				   rgb fillColor             = rgb(),
				   rgb strokeColor           = rgb(),
				   int strokeWidth           = 0);

			PenStyle GetPenStyle() const;
			void SetPenStyle(PenStyle style);

			std::pair<int, int> GetPosition() const;
			void SetPosition(const std::pair<int,int>& position, bool forceRedraw = true);
			void SetPosition(int x, int y, bool forceRedraw = true);

			rgb GetFillColor() const;
			void SetFillColor(const rgb& color, bool forceRedraw = true);

			rgb GetStrokeColor() const;
			void SetStrokeColor(const rgb& color, bool forceRedraw = true);
			int GetStrokeWidth() const;
			void SetStrokeWidth(int width, bool forceRedraw = true);		

			unsigned int GetDiameter() const;
			void SetDiameter(unsigned int diameter, bool forceRedraw = true);

		private:
			void Draw(HDC&, PAINTSTRUCT&);
		};
	}
}