# pragma once

# include "Controller.hpp"
# include "Button.hpp"

# include <functional>
# include <utility>
# include <CommCtrl.h>

namespace Quart
{
	class UpDown : public Controller
	{
		friend class Window;

	private:
		std::pair<int, int> range;
		unsigned int stepSize;

		Controller* buddy;
		Button* plusBtn;
		Button* minusBtn;

	public:
		static int wDiff;

		std::function<void()> OnMaxValue,
			OnMinValue,
			&OnFocus,
			&OnFocusLost;

		UpDown(int x,
			   int y,
			   int width,
			   int height,
			   int minVal            = 0,
			   int maxVal            = 100,
			   unsigned int stepSize = 1);

		~UpDown();

		void SetRange(int min, int max);
		void SetRange(const std::pair<int,int>& range);
		std::pair<int,int> GetRange() const;

		void SetStepSize(unsigned int size);
		unsigned int GetStepSize() const;

		int GetValue() const;

	private:
		void Create(Window*);
		void MsgHandler(WPARAM, LPARAM);
	};
}