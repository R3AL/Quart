# include "Accelerator.hpp"
# include "Window.hpp"

namespace Quart
{
	Accelerator::Accelerator(const Modifiers& modifierKeys, const Keys& Key):
		Controller(Controller::ACCELERATOR),
		OnFire(nullptr)
	{
		this->accel.fVirt = static_cast<unsigned char>(modifierKeys) | FNOINVERT | FVIRTKEY;
		this->accel.key   = static_cast<unsigned short>(Key);
	}

	Accelerator::operator ACCEL()
	{
		return this->accel;
	}

	void Accelerator::Create(Window*) {}

	void Accelerator::MsgHandler(WPARAM wparam, LPARAM)
	{
		if(wparam == 0 && this->OnFire != nullptr)
			this->OnFire();
	}
}