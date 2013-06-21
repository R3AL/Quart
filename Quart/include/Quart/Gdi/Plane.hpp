# pragma once

# include "Drawable.hpp"
# include "../Controller.hpp"

namespace Quart
{
	namespace Gdi
	{
		class Plane : public Drawable
		{
			friend class BarChart;

		private:
			int x, y, width, height;
			long fillColor;
			long strokeColor;
			int strokeWidth;
			PenStyle penStyle;

		public:
			Plane(int x,
				  int y,
				  int width,
				  int height,
				  rgb fillColor    = rgb(),
				  rgb strokeColor  = rgb(),
				  int strokeWidth  = 0);

			PenStyle GetPenStyle() const;
			void SetPenStyle(PenStyle style);

			std::pair<int, int> GetPosition() const;
			void SetPosition(const std::pair<int,int>& position, bool forceRedraw = true);
			void SetPosition(int x, int y, bool forceRedraw = true);

			std::pair<int, int> GetSize() const;
			void SetSize(const std::pair<int,int>& size, bool forceRedraw = true);
			void SetSize(int width, int height, bool forceRedraw = true);

			rgb GetFillColor() const;
			void SetFillColor(const rgb& color, bool forceRedraw = true);

			rgb GetStrokeColor() const;
			void SetStrokeColor(const rgb& color, bool forceRedraw = true);
			int GetStrokeWidth() const;
			void SetStrokeWidth(int width, bool forceRedraw = true);	

		private:
			void Draw(HDC&, PAINTSTRUCT&);
		};
	}
}