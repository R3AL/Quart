# pragma once

# include "Controller.hpp"

# include <functional>

namespace Quart
{
	class CheckBox : public Controller
	{
	private:
		int width, height;
		tstring text;
		unsigned long style;

	public:
		std::function<void()> OnCheck,
			OnUncheck;

		CheckBox(int x,
				 int y,
				 int width,
				 int height,
				 const tstring& text,
				 unsigned long style = (WS_VISIBLE | 
										WS_CHILD   | 
										BS_CHECKBOX) );

		bool IsChecked() const;
		void SetChecked(bool state = true);
		void SetUnchecked();

	private:
		void Create(Window*);
		void MsgHandler(WPARAM, LPARAM);
	};
}