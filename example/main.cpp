// Enabling common controls gives access to modern looking controls
# define ENABLE_COMMON_CONTROLS

# include <windows.h>

# include <Quart/Window.hpp>
# include <Quart/Label.hpp>
# include <Quart/button.hpp>
# include <Quart/MultiLineEditBox.hpp>
# include <Quart/MenuBar.hpp>
# include <Quart/EditBox.hpp>
# include <Quart/ComboBox.hpp>
# include <Quart/ListView.hpp>
# include <Quart/SaveFileDialog.hpp>
# include <Quart/OpenFileDialog.hpp>
# include <Quart/MessageBox.hpp>
# include <Quart/Accelerator.hpp>

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	using namespace Quart;

	Window window(600, 250, "Title");

	//  [ ] Creating a menu
	auto menuBar  = new MenuBar(&window);
	auto saveSub  = new SubmenuElement("&Save");
	auto loadSub  = new SubmenuElement("&Load");
	auto exitSub  = new SubmenuElement("E&xit");
	auto aboutSub = new SubmenuElement("&About");

	menuBar->Add(new MenuElement("&File", 3, saveSub, loadSub, exitSub));
	menuBar->Add(new MenuElement("&Help", 1, aboutSub));

		// [ ] Adding actions to submenu elements using lambdas
		saveSub->callback[SELF] = [&](WPARAM, LPARAM)
		{
			SaveFileDialog dlg(window, "All files\0*.*");
			
			auto fName = dlg.Get();

			if(fName.empty())
				Messagebox("No file selected !");
			else
				Messagebox("Selected: " + fName);
		};

		loadSub->callback[SELF] = [&](WPARAM, LPARAM)
		{
			OpenFileDialog dlg(window, "All files\0*.*");
			
			auto fName = dlg.Get();

			if(fName.empty())
				Messagebox("No file selected !");
			else
				Messagebox("Selected: " + fName);
		};

		exitSub->callback[SELF] = [&](WPARAM, LPARAM)
		{
			window.Close();
		};

		aboutSub->callback[SELF] = [](WPARAM, LPARAM)
		{
			Messagebox("Example application created using Quart C++11 library", "About");
		};
		// [/]

	//  [/]

	// [ ] Creating buttons
	auto button1 = new Button(10,  10, 150, 20, "MessageBox");
	auto button2 = new Button(10,  50, 150, 20, "New Window");
	auto button3 = new Button(10,  90, 150, 20, "New child Window");
	auto button4 = new Button(10, 130, 150, 20, "Controls examples");
	
		// [ ] Adding actions to buttons
		button1->callback[SELF] = [&](WPARAM, LPARAM)
		{
			Messagebox("This is a messagebox example !", "This is a messagebox title !");
		};

		button2->callback[SELF] = [&](WPARAM, LPARAM)
		{
			Window window2(400, 400, "New Window");
			window2.Create();

			// Force non-child window to close when main window is closed
			window.callback[WM_DESTROY] = [&](WPARAM, LPARAM)
			{
				window2.Close();
			};

			window2.Run();
		};

		button3->callback[SELF] = [&](WPARAM, LPARAM)
		{
			Window window3(400, 400, "New child Window", &window);
			window3.Create();
			window3.Run();
		};
		
		button4->callback[SELF] = [&](WPARAM, LPARAM)
		{
			Window wnd(470, 480, "Controls examples", &window);

			auto labelEx        = new Label		  (10,  10, 100, 20, "This is a label !");
			auto editboxEx      = new EditBox	  (120, 10, 150, 20, "This is an EditBox !");
			auto buttonEx       = new Button	  (290, 10, 150, 20, "Get text from EditBox");
			auto labelEx        = new Label			  (10,  10, 100, 20,  "This is a label !");
			auto editboxEx      = new EditBox		  (120, 10, 150, 20,  "This is an EditBox !");
			auto buttonEx       = new Button		  (290, 10, 150, 20,  "Get text from EditBox");
			auto multieditboxEx = new MultiLineEditBox(10,  60, 150, 150, "This is a MultiLineEditBox !");
			auto comboboxEx     = new ComboBox	  (290, 60, 150, 20);
			auto listviewEx     = new ListView	  (10, 220, 440, 200);

			buttonEx->callback[SELF] = [&](WPARAM, LPARAM)
			{
				Messagebox("Text from EditBox is: \"" + editboxEx->GetText() + "\"");
			};

			wnd.Add(labelEx);
			wnd.Add(editboxEx);
			wnd.Add(buttonEx);
			wnd.Add(multieditboxEx);
			wnd.Add(comboboxEx);
			wnd.Add(listviewEx);

			wnd.Create();
			
			// [ ] Operations on ComboBoxes and ListViews can only be made after calling Window.Create()
			comboboxEx->Add("Item 1");
			comboboxEx->Add("Item 2");
			comboboxEx->Add("Item 3");

 			listviewEx->AddCollumn("Collumn 1");
			listviewEx->AddCollumn("Collumn 2");
			listviewEx->AddCollumn("Collumn 3");
			listviewEx->AddCollumn("Collumn 4");

 			listviewEx->AddItem(0, "Item 0, C1", "Item 0, C2", "Item 0, C3", "Item0, C4");
			listviewEx->AddItem(1, "Item 1, C1", "Item 1, C2", "Item 1, C3", "Item1, C4");
			listviewEx->AddItem(2, "Item 2, C1", "Item 2, C2", "Item 2, C3", "Item2, C4");
			listviewEx->AddItem(3, "Item 3, C1", "Item 3, C2", "Item 3, C3", "Item3, C4");
			// [/]

			wnd.Run();
		};
		// [/]

	// [/]

	// [ ] Creating accelerators
	auto accelerator1 = new Accelerator(Modifiers::CONTROL, vKeys::Key_S);
	auto accelerator2 = new Accelerator(Modifiers::SHIFT,	vKeys::Key_D);
	auto accelerator3 = new Accelerator(Modifiers::CONTROL, vKeys::Key_Q);

		// [ ] Adding actions to accelerators
		accelerator1->callback[SELF] = [&](WPARAM, LPARAM)
		{
			// Calling another object
			saveSub->SelfCall(); 
		};

		accelerator2->callback[SELF] = [&](WPARAM, LPARAM)
		{
			loadSub->SelfCall();
		};

		accelerator3->callback[SELF] = [&](WPARAM, LPARAM)
		{
			exitSub->SelfCall();
		};
		// [/]

	// [/]

	auto infoLbl = new Label(170, 10, 400, 200, "To use accelerators just press the specific key combination\n"
		"For example: Control + S");
	
	window.Add(menuBar); // Window class takes ownership of these objects
	window.Add(button1); // so no need to delete them
	window.Add(button2);
	window.Add(button3);
	window.Add(button4);
	window.Add(accelerator1);
	window.Add(accelerator2);
	window.Add(accelerator3);
	window.Add(infoLbl);

	window.Create();

	return window.Run();
}
