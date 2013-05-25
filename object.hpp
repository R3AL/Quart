# pragma once

# include <windows.h>
# include <string>
# include <functional>
# include <map>

# ifdef UNICODE
    typedef std::wstring tstring;
	# define to_tstring(a) std::to_wstring(a)
    # define WIDEN2(x) L ## x 
    # define WIDEN(x) WIDEN2(x)
# else
	typedef std::string tstring;
	# define to_tstring(a) std::to_string(a)
    # define WIDEN(x) x
# endif

namespace Quart
{
	static const int SELF = -1;

    class Object
    {
    protected:
        HWND handle;
        WNDPROC oldproc;
    public:
        HWND parent;
        unsigned long styles;
        int id;
        int width;
        int height;
        int x;
        int y;
        
        std::map<unsigned int, std::function<void(WPARAM,LPARAM)> > callback;

        Object(int id, int x, int y) : 
            id(id), 
            x(x), 
            y(y),
            handle(nullptr) {}
        Object(int id, int x, int y, int width, int height, unsigned long styles) : 
            id(id), 
            x(x),
            y(y),
            width(width), 
            height(height),
            handle(nullptr),
            styles(styles) {}
        virtual ~Object()                             = 0;
        virtual void Draw(HWND&,HDC&,PAINTSTRUCT&)    = 0;
        virtual void Create(HWND&)                    = 0;
		virtual LRESULT Proc(HWND, UINT, WPARAM, LPARAM);

        operator HWND() { return handle; }
		void Focus();
    };

    inline Object::~Object() {}
}