# pragma once

# include "Controller.hpp"

# include <functional>

namespace Quart
{
	class Button : public Controller
	{
		friend class UpDown;

	private:
		int x, y, width, height;
		tstring text;
		unsigned long style;

	public:
		std::function<void()> OnClick,
			OnDbClick,
			OnFocus,
			OnFocusLost;
		
		Button(int x,
			   int y,
			   int width,
			   int height,
			   const tstring& text,
			   unsigned long style = (WS_TABSTOP	   | 
									  WS_VISIBLE	   | 
									  WS_CHILD		   | 
									  BS_DEFPUSHBUTTON |
									  BS_NOTIFY));

		tstring GetText() const;
		void SetText(const tstring& text);

	private:
		void Create(Window*);
		void MsgHandler(WPARAM, LPARAM);
	};
}