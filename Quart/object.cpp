#include "object.hpp"

namespace Quart
{
	LRESULT Object::Proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		if(this->callback.count(message))
		{
			if(this->callback[message] != nullptr)
				this->callback[message](wparam,lparam);
		}

		if(this->callback.count(SELF))
		{
			if(this->callback[SELF] != nullptr)
				this->callback[SELF](wparam, lparam);
		}

		return 0;
	}

	void Object::Focus()
	{
		SetFocus(this->handle);
	}

	Object::operator HWND() 
	{ 
		return handle; 
	}

	void Object::SelfCall()
	{
		this->callback[SELF](0, 0);
	}
}