// Enable common controls and visual styles
# define ENABLE_CC_VS

# include <Quart/Controller.hpp>
# include <Quart/Window.hpp>
# include <Quart/Button.hpp>
# include <Quart/Label.hpp>
# include <Quart/EditBox.hpp>
# include <Quart/ComboBox.hpp>
# include <Quart/ListView.hpp>
# include <Quart/MenuBar.hpp>
# include <Quart/Messagebox.hpp>
# include <Quart/Accelerator.hpp>
# include <Quart/SaveFileDialog.hpp>
# include <Quart/OpenFileDialog.hpp>
# include <Quart/MultilineEditBox.hpp>
# include <Quart/ProgressBar.hpp>
# include <Quart/UpDown.hpp>

int main()
{
	using namespace Quart;

	Window window(600, 250, L"Window title");

	// [ ] Creating a menu
	auto menuBar  = new MenuBar();
	auto saveSub  = new MenuSubElement(L"&Save");
	auto openSub  = new MenuSubElement(L"&Open");
	auto exitSub  = new MenuSubElement(L"E&xit");
	auto aboutSub = new MenuElement(L"&About");

	menuBar->Add(new MenuElement(L"&File", 3, openSub, saveSub, exitSub));
	menuBar->Add(aboutSub);

	window.Add(menuBar); // Window class takes ownership of objects, therefor no need to delete them

	// Adding actions using lambdas
	saveSub->OnClick = [&]()
	{
		SaveFileDialog dlg(window);

		auto fName = dlg.Get();

		if(fName.empty())
			Messagebox(L"No file selected !");
		else
			Messagebox(L"Selected: " + fName);
	};

	openSub->OnClick = [&]()
	{
		OpenFileDialog dlg(window);

		auto fName = dlg.Get();

		if(fName.empty())
			Messagebox(L"No file selected !");
		else
			Messagebox(L"Selected: " + fName);
	};

	exitSub->OnClick = [&]()
	{
		window.Close();
	};

	aboutSub->OnClick = []()
	{
		Messagebox(L"Example application created using Quart C++11 library", L"About");
	};
	// [/]

	// [ ] Creating buttons
	auto button1 = new Button(10,  10, 150, 20, L"MessageBox");
	auto button2 = new Button(10,  50, 150, 20, L"New Window");
	auto button3 = new Button(10,  90, 150, 20, L"New child Window");
	auto button4 = new Button(10, 130, 150, 20, L"Controls examples");

	window.Add(button1);
	window.Add(button2);
	window.Add(button3);
	window.Add(button4);

	// [ ] Adding actions to buttons
	button1->OnClick = []()
	{
		Messagebox(L"This is a Messagebox example !", L"This is a Messagebox title !");
	};

	button2->OnClick = [&]()
	{
		Window window2(400, 400, L"New Window");

		window2.Run();
	};

	button3->OnClick = [&]()
	{
		Window window3(400, 400, L"New child Window", &window);

		window3.Run();
	};

	button4->OnClick = [&]()
	{
		Window wnd(470, 480, L"Controls examples", &window);

		auto labelEx        = new Label(10,  10, 100, 20,  L"This is a label !");
		auto editboxEx      = new EditBox(120, 10, 150, 20,  L"This is an EditBox !");
		auto buttonEx       = new Button(290, 10, 150, 20,  L"Get text from EditBox");
		auto multieditboxEx = new MultilineEditBox(10,  60, 150, 150, L"This is a MultiLineEditBox !");
		auto comboboxEx     = new ComboBox(290, 60, 150, 20);
		auto listviewEx     = new ListView(10, 220, 440, 200);

		buttonEx->OnClick = [&]()
		{
			Messagebox(L"Text from EditBox is: \"" + editboxEx->GetText() + L"\"");
		};

		wnd.Add(labelEx);
		wnd.Add(editboxEx);
		wnd.Add(buttonEx);
		wnd.Add(multieditboxEx);
		wnd.Add(comboboxEx);
		wnd.Add(listviewEx);

		// [ ] Operations on controls must be performed after calling Window.Add(control)
		{
		comboboxEx->Add(L"Item 1");
		comboboxEx->Add(L"Item 2");
		comboboxEx->Add(L"Item 3");

		listviewEx->AddCollumn(L"Collumn 1");
		listviewEx->AddCollumn(L"Collumn 2");
		listviewEx->AddCollumn(L"Collumn 3");
		listviewEx->AddCollumn(L"Collumn 4");

		listviewEx->AddItem(0, L"Item 0, C1", L"Item 0, C2", L"Item 0, C3", L"Item0, C4");
		listviewEx->AddItem(1, L"Item 1, C1", L"Item 1, C2", L"Item 1, C3", L"Item1, C4");
		listviewEx->AddItem(2, L"Item 2, C1", L"Item 2, C2", L"Item 2, C3", L"Item2, C4");
		listviewEx->AddItem(3, L"Item 3, C1", L"Item 3, C2", L"Item 3, C3", L"Item3, C4");
		}
		// [/]

		wnd.Run();
	};
	// [/]

	// [ ] Creating accelerators
	auto accelerator1 = new Accelerator(Modifiers::CONTROL, Keys::Key_S);
	auto accelerator2 = new Accelerator(Modifiers::SHIFT,	Keys::Key_D);
	auto accelerator3 = new Accelerator(Modifiers::CONTROL, Keys::Key_Q);

	window.Add(accelerator1);
	window.Add(accelerator2);
	window.Add(accelerator3);

	// [ ] Adding actions to accelerators
	accelerator1->OnFire = [&]()
	{
		// Calling callbacks from other objects
		saveSub->OnClick();
	};

	accelerator2->OnFire = [&]()
	{
		openSub->OnClick();
	};

	accelerator3->OnFire = [&]()
	{
		exitSub->OnClick();
	};
	// [/]

	auto infoLbl = new Label(170, 10, 400, 200, L"To use accelerators just press the specific key combination\n"
		L"For example: Control + S");

	return window.Run();
}