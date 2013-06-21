# pragma once

# include "Drawable.hpp"

namespace Quart
{
	namespace Gdi
	{
		class Text : public Drawable
		{
			friend class BarChart;
			friend class VerticalText;

		private:
			int x, y;
			std::pair<int, int> size;
			tstring text;
			long textColor;

		public:
			Text(int x,
				 int y,
				 const tstring& text,
				 rgb textColor = rgb(Colors::BLACK) );

			tstring GetText() const;
			void SetText(const tstring& text);

			std::pair<int, int> GetPosition() const;
			void SetPosition(const std::pair<int,int>& position, bool forceRedraw = true);
			void SetPosition(int x, int y, bool forceRedraw = true);

			rgb GetColor() const;
			void SetColor(const rgb& color, bool forceRedraw = true);

			virtual std::pair<int, int> GetSize() const;

		private:
			void Draw(HDC&, PAINTSTRUCT&);
		};
	}
}