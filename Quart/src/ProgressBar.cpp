# include "ProgressBar.hpp"
# include "Window.hpp"
# include "Messagebox.hpp"

# include <CommCtrl.h>

namespace Quart
{
	ProgressBar::ProgressBar(int x, int y, int width, int height, unsigned int minVal, unsigned int maxVal, unsigned int stepSize, unsigned long style /* = */ ):
		Controller(Controller::PROGRESSBAR),
		x(x), y(y), width(width), height(height), style(style), range(minVal,maxVal), stepSize(stepSize)
	{

	}

	void ProgressBar::Create(Window* parent)
	{
		this->handle = CreateWindowEx(
			0,
			WIDEN("msctls_progress32"),
			nullptr,
			this->style,
			this->x,
			this->y,
			this->width,
			this->height,
			parent->GetHandle(),
			(HMENU)this->id,
			GetModuleHandle(0),
			nullptr);

		if(!this->handle)
		{
			ERRORMB();
			return;
		}

		this->SetRange(this->range);
		this->SetStepSize(this->stepSize);
	}

	void ProgressBar::Step(int size)
	{
		if(size == -1)
			SendMessage(this->handle, PBM_STEPIT, 0, 0);
		else
			SendMessage(this->handle, PBM_DELTAPOS, size, 0);
	}

	unsigned int ProgressBar::GetStep() const
	{
		return static_cast<unsigned int>(SendMessage(this->handle, PBM_GETPOS, 0, 0));
	}

	void ProgressBar::SetStep(int step)
	{
		SendMessage(this->handle, PBM_SETSTEP, step, 0);
	}

	void ProgressBar::SetStepSize(unsigned int stepSize)
	{
		this->stepSize = stepSize;

		SendMessage(this->handle, PBM_SETSTEP, this->stepSize, 0);
	}

	unsigned int ProgressBar::GetStepSize() const
	{
		return this->stepSize;
	}

	std::pair<unsigned int, unsigned int> ProgressBar::GetRange() const
	{
		return this->range;
	}

	void ProgressBar::SetRange(unsigned int minVal, unsigned int maxVal)
	{
		this->SetRange(std::make_pair(minVal, maxVal));	
	}

	void ProgressBar::SetRange(const std::pair<unsigned int, unsigned int>& range)
	{
		if(this->range != range)
			this->range = range;

		SendMessage(this->handle, PBM_SETRANGE32, this->range.first, this->range.second);
	}

	void ProgressBar::SetColor(unsigned char r, unsigned char g, unsigned char b)
	{
		if(!___internal::vsEnable)
			SendMessage(this->handle, PBM_SETBARCOLOR, 0, RGB(r,g,b));
	}

	void ProgressBar::SetColor(const std::tuple<unsigned char, unsigned char, unsigned char>& color)
	{
		if(!___internal::vsEnable)
			this->SetColor(std::get<0>(color), std::get<1>(color), std::get<2>(color));
	}

	std::tuple<unsigned char, unsigned char, unsigned char> ProgressBar::GetColor() const
	{
		auto tmpColor = SendMessage(this->handle, PBM_GETBARCOLOR, 0, 0);
		
		return std::forward_as_tuple(GetRValue(tmpColor), GetGValue(tmpColor), GetBValue(tmpColor));
	}

	void ProgressBar::SetMarquee(bool enable /* = true */, unsigned int interval /* = 0 */)
	{
		if(enable)
		{
			SetWindowLongPtr(this->handle, GWL_STYLE, (this->style | PBS_MARQUEE) );
			SendMessage(this->handle, PBM_SETMARQUEE, enable, interval);
		}
		else
			SetWindowLongPtr(this->handle, GWL_STYLE, (this->stepSize & ~PBS_MARQUEE));
	}

	void ProgressBar::SetBgColor(const std::tuple<unsigned char, unsigned char, unsigned char>& color)
	{
		if(!___internal::vsEnable)
			this->SetBgColor(std::get<0>(color), std::get<1>(color), std::get<2>(color));
	}

	void ProgressBar::SetBgColor(unsigned char r, unsigned char g, unsigned char b)
	{
		if(!___internal::vsEnable)
			SendMessage(this->handle, PBM_SETBKCOLOR, 0, RGB(r,g,b));
	}

	std::tuple<unsigned char, unsigned char, unsigned char> ProgressBar::GetBgColor() const
	{
		auto tmpColor = SendMessage(this->handle, PBM_GETBKCOLOR, 0, 0);

		return std::forward_as_tuple(GetRValue(tmpColor), GetGValue(tmpColor), GetBValue(tmpColor));
	}


	void ProgressBar::MsgHandler(WPARAM, LPARAM)
	{

	}
}