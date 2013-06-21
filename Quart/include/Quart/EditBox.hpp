# pragma once

# include "Controller.hpp"


# include <functional>

namespace Quart
{
	class EditBox : public Controller
	{
		friend class MultilineEditBox;
		friend class UpDown;

	private:
		int width, height;
		tstring text;
		unsigned long style;

	public:
		bool IgnoreTextChange;

		std::function<void()> OnTextChanged,
			OnFocus,
			OnFocusLost,
			OnExceedingText;

		EditBox(int x,
				int y,
				int width,
				int height,
				const tstring& text = WIDEN(""),
				unsigned long style = (WS_CHILD		  | 
									   WS_VISIBLE	  | 
									   WS_TABSTOP	  | 
									   WS_BORDER	  |
									   ES_AUTOHSCROLL | 
									   ES_AUTOVSCROLL) );

		tstring GetText() const;
		void SetText(const tstring&);
		void Clear();
		void LimitText(unsigned int);

	private:
		void Create(Window*);
		void MsgHandler(WPARAM, LPARAM);
	};
}