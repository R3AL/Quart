# pragma once

# include "Controller.hpp"

# include <functional>
# include <CommCtrl.h>
# include <utility>

namespace Quart
{
	class SlideBar : public Controller
	{
	private:
		int width, height;
		unsigned long style;

	public:
		std::function<void()> OnEndKey,
			OnHomeKey,
			OnKeyUp,
			OnLineDown,
			OnLineUp,
			OnPageDown,
			OnPageUp,
			OnChange;

		SlideBar(int x,
				 int y,
				 int width,
				 int height,
				 unsigned long style = (WS_CHILD			|
										WS_VISIBLE			|
										TBS_AUTOTICKS		|
										TBS_ENABLESELRANGE	|
										TBS_TRANSPARENTBKGND) );

		std::pair<int, int> GetRange() const;
		void SetRange(const std::pair<int, int>&);
		void SetRange(int min, int max);

		int GetPageSize() const;
		void SetPageSize(int size);

		int GetSliderPos() const;
		void SetSliderPos(int pos);

	private:
		void Create(Window*);
		void MsgHandler(WPARAM, LPARAM);
	};
}