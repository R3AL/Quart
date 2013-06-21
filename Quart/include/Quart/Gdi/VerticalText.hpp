# pragma once

# include "Text.hpp"

namespace Quart
{
	namespace Gdi
	{
		class VerticalText : public Text
		{
			friend class BarChart;

		public:
			VerticalText(int x,
						 int y,
						 const tstring& text,
						 rgb textColor = rgb(Colors::BLACK));

			std::pair<int, int> GetSize() const;

		private:
			void Draw(HDC&, PAINTSTRUCT&);
		};
	}
}