# pragma once

# include "Controller.hpp"
# include "EditBox.hpp"

# include <functional>

namespace Quart
{
	class MultilineEditBox : public Controller
	{
		EditBox eb;
	public:
		std::function<void()> &OnTextChanged,
			&OnFocus,
			&OnFocusLost,
			&OnExceedingText;

		MultilineEditBox(int x,
						 int y,
						 int width,
						 int height,
						 const tstring& text = WIDEN(""),
						 unsigned long style = (WS_CHILD		|
												WS_VISIBLE		|
												WS_VSCROLL		|
												ES_LEFT			|
												ES_AUTOVSCROLL) );

		tstring GetText() const;
		void SetText(const tstring&);
		void Clear();
		void LimitText(unsigned int);

		std::pair<int, int> GetPosition() const;
		void SetPosition(const std::pair<int,int>& position);
		void SetPosition(int x, int y);

	private:
		void Create(Window*);
		void MsgHandler(WPARAM, LPARAM);
	};
}