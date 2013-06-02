# include "UpDown.hpp"
# include "Window.hpp"
# include "EditBox.hpp"

namespace Quart
{
	int UpDown::wDiff = 20;

	UpDown::UpDown(int x, int y, int width, int height, int minVal, int maxVal, unsigned int stepSize):
		Controller(Controller::UPDOWN),
		range(minVal, maxVal), stepSize(stepSize),
		buddy(new EditBox(x, y, width - wDiff, height, to_tstring(minVal), ES_NUMBER | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER)), 
			plusBtn(nullptr), minusBtn(nullptr),
		OnMinValue(nullptr), OnMaxValue(nullptr),
		OnFocus( static_cast<EditBox*>(this->buddy)->OnFocus ),
		OnFocusLost( static_cast<EditBox*>(this->buddy)->OnFocus)
	{
		this->plusBtn  = new Button(x + (width - wDiff), y , wDiff, height/2, WIDEN("+"));
		this->minusBtn = new Button(x + (width - wDiff), y + height/2 , wDiff, height/2, WIDEN("-"));

		this->plusBtn->OnClick = [&]()
		{
			tstring text = static_cast<EditBox*>(this->buddy)->GetText();

			int val;
			tstringstream(text) >> val;
			
			if(val < this->range.second)
			{
				static_cast<EditBox*>(this->buddy)->SetText( to_tstring(val += this->stepSize) );

				if(val == this->range.second && this->OnMaxValue != nullptr)
					this->OnMaxValue();
			}
			else if(val > this->range.second)
			{
				static_cast<EditBox*>(this->buddy)->SetText( to_tstring(this->range.second) );
			}
		};

		this->minusBtn->OnClick = [&]()
		{
			tstring text = static_cast<EditBox*>(this->buddy)->GetText();

			int val;
			tstringstream(text) >> val;

			if(val > this->range.first)
			{
				static_cast<EditBox*>(this->buddy)->SetText( to_tstring(val -= this->stepSize) );

				if(val == this->range.first && this->OnMinValue != nullptr)
					this->OnMinValue();
			}
			else if(val < this->range.first)
			{
				static_cast<EditBox*>(this->buddy)->SetText( to_tstring(this->range.first) );
			}
		};

		this->SetRange(this->range);
	}

	UpDown::~UpDown()
	{
		delete this->buddy;
		delete this->plusBtn;
		delete this->minusBtn;
	}

	void UpDown::Create(Window* parent)
	{
		parent->Add(buddy);
		parent->Add(plusBtn);
		parent->Add(minusBtn);
	}

	void UpDown::SetRange(int min, int max)
	{
		this->SetRange(std::make_pair(min, max));
	}

	void UpDown::SetRange(const std::pair<int,int>& range)
	{
		if(this->range != range)
			this->range = range;
	}

	std::pair<int,int> UpDown::GetRange() const
	{
		return this->range;
	}

	unsigned int UpDown::GetStepSize() const
	{
		return this->stepSize;
	}

	void UpDown::SetStepSize(unsigned int size)
	{
		this->stepSize = size;
	}

	int UpDown::GetValue() const
	{
		tstring text = static_cast<EditBox*>(this->buddy)->GetText();
		int val      = -1;

		tstringstream(text) >> val;
		
		return val;
	}

	void UpDown::MsgHandler(WPARAM, LPARAM) {}
};