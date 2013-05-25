# include "Accelerator.hpp"

namespace Quart
{
	Accelerator::Accelerator(const Modifiers& modifierKeys, const vKeys& virtualKey) : 
		Object(0, 0) 
	{
 		this->accel.fVirt = static_cast<unsigned char>(modifierKeys) | FNOINVERT | FVIRTKEY;
 		this->accel.key   = static_cast<unsigned short>(virtualKey);
		this->accel.cmd   = id;
	}

	Accelerator::operator ACCEL()
	{
		return this->accel;
	}

	void Accelerator::Draw(HWND&,HDC&,PAINTSTRUCT&) {}
	void Accelerator::Create(HWND&) {}

	LRESULT Accelerator::Proc(HWND, UINT, WPARAM wparam, LPARAM lparam)
	{
		if(this->callback.count(SELF))
		{
			if(this->callback[SELF] != nullptr)
				this->callback[SELF](wparam, lparam);
		}

		return 0;
	}
}