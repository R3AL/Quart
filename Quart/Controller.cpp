# include "Controller.hpp"
# include "Messagebox.hpp"

namespace Quart
{
	Controller::Controller(enum type type) :
		id(0),
		handle(nullptr),
		type(type)
	{}

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
}