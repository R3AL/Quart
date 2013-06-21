# pragma once

# include "Controller.hpp"
# include "EditBox.hpp"

# include <functional>
# include <CommCtrl.h>

namespace Quart
{
	class UpDown : public Controller
	{
	private:
		int width, height;
		unsigned long style;
		std::pair<int, int> range;

		EditBox* buddy;
		bool readyForChange;

	public:
		std::function<void()> OnValueChanged;
		std::function<void()>& OnFocus;
		std::function<void()>& OnFocusLost;

		UpDown(int x,
			   int y,
			   int width,
			   int height,
			   int minval,
			   int maxval,
			   unsigned long style = (WS_CHILD		  | 
									  WS_VISIBLE	  |
									  UDS_AUTOBUDDY	  | 
									  UDS_SETBUDDYINT | 
									  UDS_ALIGNRIGHT  | 
									  UDS_ARROWKEYS	  | 
									  UDS_HOTTRACK	  ) );

		std::pair<int, int> GetRange() const;
		void SetRange(const std::pair<int, int>& range);
		void SetRange(int minval, int maxval);

		int GetValue() const;
		void SetValue(int value);

	private:
		void Create(Window*);
		void MsgHandler(WPARAM, LPARAM);
	};
}