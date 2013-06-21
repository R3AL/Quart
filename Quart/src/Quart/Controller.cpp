# include "Controller.hpp"
# include "Messagebox.hpp"

namespace Quart
{
	Controller::Controller(enum type type):
		id(0),
		handle(nullptr),
		type(type)
	{

	}

	Controller::Controller(int x, int y, enum type type) :
		x(x),
		y(y),
		id(0),
		handle(nullptr),
		type(type)

	{

	}

	Controller::~Controller() {}

	void Controller::Enable()
	{
		if(this->handle != nullptr)
			EnableWindow(this->handle, true);
		else
			ERRORMB();
	}

	void Controller::Disable()
	{
		if(this->handle != nullptr)
			EnableWindow(this->handle, false);
		else
			ERRORMB();
	}

	void Controller::Focus()
	{
		if(this->handle != nullptr && SetFocus(this->handle) != 0);
		else
			ERRORMB();
	}

	std::pair<int, int> Controller::GetPosition() const
	{
		return std::make_pair(this->x, this->y);
	}

	void Controller::SetPosition(const std::pair<int,int>& position)
	{
		this->SetPosition(position.first, position.second);
	}

	void Controller::SetPosition(int x, int y)
	{
		this->x = x;
		this->y = y;

		SetWindowPos(this->handle, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
	}
}