# pragma once

# include "Controller.hpp"

# include <CommCtrl.h>
# include <functional>
# include <utility>

namespace Quart
{
	class ProgressBar : public Controller
	{
	private:
		int width, height;
		unsigned long style;
		std::pair<unsigned int, unsigned int> range;
		unsigned int stepSize;

	public:
		std::function<void()> OnMaxVal;

		ProgressBar(int x,
					int y,
					int width,
					int height,
					unsigned int minVal   = 0,
					unsigned int maxVal   = 100,
					unsigned int stepSize = 1,
					unsigned long style   = (WS_CHILD | WS_VISIBLE) );

		void Step(int size = -1);
		unsigned int GetStep() const;
		void SetStep(int step);

		void SetStepSize(unsigned int stepSize);
		unsigned int GetStepSize() const;

		std::pair<unsigned int, unsigned int> GetRange() const;
		void SetRange(const std::pair<unsigned int, unsigned int>& range);
		void SetRange(unsigned int minVal, unsigned int maxVal);

		void SetColor(const std::tuple<unsigned char, unsigned char, unsigned char>& color);
		void SetColor(unsigned char r, unsigned char g, unsigned char b);
		std::tuple<unsigned char, unsigned char, unsigned char> GetColor() const;

		void SetBgColor(const std::tuple<unsigned char, unsigned char, unsigned char>& color);
		void SetBgColor(unsigned char r, unsigned char g, unsigned char b);
		std::tuple<unsigned char, unsigned char, unsigned char> GetBgColor() const;

		void SetMarquee(bool enable = true, unsigned int interval = 0);

	private:
		void Create(Window*);
		void MsgHandler(WPARAM, LPARAM);
	};
}