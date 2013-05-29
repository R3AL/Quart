Quart
=====

**Quart** is a modern **C++11** Winapi wrapper that aims to provide a simple way of creating GUIs for your applications.

Unlike Qt/wxWidgets and other libraries, Quart uses a callback system which in combination with lambdas leads to easy to read and concise code.

Installation
============

First of all you will need a compiler that supports **C++11**:

- **MSVC11** ( provided by Visual Studio 2012 )
- **GCC** ( 4.4+ )
- **ICC** ( 12.1+ )

Actual installation is rather easy, just add the path to the **'Quart'** folder to your include path:

- ***Code::Blocks***

*Build options -> Search directories -> Compiler*

- ***Visual Studio***

*Project proprieties -> Configuration proprieties -> C/C++ -> Additional include directories*


And that's it ! You can now use **Quart** ! (start by compiling the example)

API Refference
==============

**Window**
==========

  **Parameters**
  - **width**  ( *unsigned int* )
  - **height** ( *unsigned int* ) 
  - **title**  ( *string* )
  - **parent** ( *Window** = **nullptr** )
  
  **Note**: If a parent Window is specified, it (the parent) will be disabled while the child Window is running.

  **Member functions**
  - **Create** : creates the window and its children (bool)

      **Parameters**
      
      - **styles** ( *unsigned long* = **WS_OVERLAPPEDWINDOW**)
      - **extended styles** ( *unsigned long* = **NULL** )
      - **window show command** ( *int* = **SW_SHOW** )
      - **startup x coordonate** ( *int* = **CW_USEDEFAULT** )
      - **startup y coordonate** ( *int* = **CW_USEDEFAULT** )
      - **window cursor** ( *unsigned short* = **IDC_ARROW** )
      - **window icon** ( *unsigned short* = **IDI_APPLICATION** )
      - **window icon small** ( *unsigned short* = **IDI_APPLICATION** )
      
  - **Run** : starts the message loop (int)

  - **Close** : closes the window
  - **Enable** : enables the window
  - **Disable** : disables the window
  - **Add** : adds an object to the window ( *Object** or *MenuBar** or *Accelerator** )
  - **operator HWND()** : conversion operator to HWND

**Label**
=========
  
  **Parameters**
  - **x coordonate** ( *int* )
  - **y coordonate** ( *int* )
  - **width** ( *int* )
  - **height** ( *int* )
  - **text** ( *string* )
  - **parent** ( *HWND* = **nullptr** )
  - **styles** ( *unsigned long* = **WS_CHILD | WS_VISIBLE** )

**Button**
==========
  
  **Parameters**
  - **x coordonate** ( *int* )
  - **y coordonate** ( *int* )
  - **width** ( *int* )
  - **height** ( *int* )
  - **text** ( *string* )
  - **parent** ( *HWND* = **nullptr** )
  - **styles** ( *unsigned long* = **WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON** )
  
  **Note** : example of adding a callback for when the button is clicked:

    ```C++
       Window window(800, 600, "Title");
    
       auto button = new Button(0, 0, 100, 20, "Click me! ");

       button->callback[SELF] = [](WPARAM, LPARAM)
       {
          //Add code here
       };
       
       window.Add(button);
       ...
       ```
       More on C++11 lambdas [here](http://en.cppreference.com/w/cpp/language/lambda).

**EditBox**
===========

  **Parameters**
  - **x coordonate** ( *int* )
  - **y coordonate** ( *int* )
  - **width** ( *int* )
  - **height** ( *int* )
  - **text** ( *string* )
  - **parent** ( *HWND* = **nullptr** )
  - **styles** ( *unsigned long* = **WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL** )
  
  **Member functions**
  - **Clear** : removes text from control
  - **GetText** : returns text inside control (string)
  - **SetText** : sets text inside control
      
      **Parameters**
      - **text** ( *string* )

**MultiLineEditBox**
====================
  
  **Parameters**
  - **x coordonate** ( *int* )
  - **y coordonate** ( *int* )
  - **width** ( *int* )
  - **height** ( *int* )
  - **text** ( *string* )
  - **parent** ( *HWND* = **nullptr** )
  - **styles** ( *unsigned long* = **WS_CHILD | WS_VISIBLE | ES_LEFT | WS_VSCROLL | ES_AUTOVSCROLL** )
  
  **Member functions**
  - **GetText** : returns text inside control (string)

**ComboBox**
============

  **Parameters**
  - **x coordonate** ( *int* )
  - **y coordonate** ( *int* )
  - **width** ( *int* )
  - **height** ( *int* )
  - **parent** ( *HWND* = **nullptr* )
  - **styles** ( *unsigned long* = **CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE** )
  
  **Member functions**
  - **Add** : adds string to control
      
      **Parameters**
      - **text** ( *string* )

  - **Remove** : removes string from control

      **Parameters**
      - **index** ( *unsigned int* )
      
  - **SelectionIndex** : gets the current selection index ( *unsigned int* )( *const* )

**ListView**
============

  **Parameters**
  - **x coordonate** ( *int* )
  - **y coordonate** ( *int* )
  - **width** ( *int* )
  - **height** ( *int* )
  - **parent** ( *HWND* = **nullptr** )
  - **styles** ( *unsigned long* = **WS_CHILD | LVS_REPORT | LVS_EDITLABELS | LVS_SHOWSELALWAYS** )
  
  **Member functions**
  - **AddCollumn** : adds collumn to control
      
      **Parameters**
      - **text** ( *string* )
      - **index** ( *int* = **-1** )
      - **collumn width** ( *unsigned int* = **100** )

  - **AddItem** : adds item to control

      **Parameters**
      - **index** ( *unsigned int* )
      - **...** ( *char** or *wchar_t**, depending on the environment )
      
      **Note** : number of arguments is the same as the number of collumns added.
  
  - **EditItem** : changes collumns value of item
      
      **Parameters**
      - **index** ( *unsigned int* )
      - **...** ( *char** or *wchar_t**, depending on the environment )
      
      **Note** : number of arguments is the same as the number of collumns added.

  - **RemoveItem** : removes item from control
    
      **Parameters**
      - **index** ( *unsigned int* )

  - **ScrollTo** : scrolls to item at index and selects it
      
      **Parameters**
      - **index** ( *unsigned int* )

  - **GetSelectedIndex** : gets the current selection index ( *int* )
  - **Count** : gets the number of items in control ( *int* )
  - **Clear** : clears all items from control

**SubmenuElement**
==================

   **Parameters**
   - **text** ( *string* )
    
**MenuElement**
===============
  
   **Parameters**
   - **text** ( *string* )
   - **SubmenuElements count** ( *unsigned int* )
   - **...** ( *SubmenuElement** )

**MenuBar**
===========

   **Parameters**
   - **parent** ( *Window** )
   
   **Member functions**
   - **Add** : adds an element to the control
       
       **Parameters**
       - **element** ( *MenuElement** )
   
   **Note** : example of creating and using a MenuBar:
   
   ```C++
   Window window(800, 600, "Title");
   
   auto menuBar        = new MenuBar(&window);
   auto loadSubelement = new SubmenuElement("&Load"); // '&' used to access the menu using ALT + letter key after ampersand
   auto saveSubelement = new SubmenuElement("&Save");
   
   loadSubelement->callback[SELF] = [](WPARAM, LPARAM)
   {
     // Add code here
   };
   
   saveSubelement->callback[SELF] = [](WPARAM, LPARAM)
   {
     // Add code here
   };
   
   menuBar->Add(new MenuElement("&File", 2, loadSubelement, saveSubelement));
   
   window.Add(menuBar);
   ...
   ```

**Accelerator**
===============

   **Parameters**
   - **modifier key** ( *Modifiers* )
   - **virtual key** ( *vKeys* )
   
   **Note** : click [here](https://github.com/R3AL/Quart/blob/master/Quart/Accelerator.hpp) for parameter values.
    
    
**OpenFileDialog**
==================

   **Parameters**
   - **parent** ( *Window* )
   - **filter** ( *string* )
   
   **Member functions**
   - **Get** : returns path to selected file ( *string* )( *const* )
    
**SaveFileDialog**
==================

   **Parameters**
   - **parent** ( *Window* )
   - **filter** ( *string* )
   
   **Member functions**
   - **Get** : returns path to selected file ( *string* )( *const* )

**Messagebox**
==============
  
   **Parameters**
   - **text** ( *string* )
   - **title** ( *string* = **empty** )
   - **parent** ( *Window** = **nullptr** )
  
