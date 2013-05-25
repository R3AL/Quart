# define ENABLE_COMMON_CONTROLS

# include <fstream>
# include <windows.h>

# include "window.hpp"
# include "Label.hpp"
# include "button.hpp"
# include "MultiLineEditBox.hpp"
# include "MenuBar.hpp"
# include "EditBox.hpp"
# include "ComboBox.hpp"
# include "ListView.hpp"
# include "SaveFileDialog.hpp"
# include "OpenFileDialog.hpp"
# include "MessageBox.hpp"
# include "Accelerator.hpp"

# include "backend/Colleague.hpp"
# include "backend/Friend.hpp"
# include "backend/Agenda.hpp"
# include "backend/Acquaintance.hpp"
# include "backend/ContactFactory.hpp"

static int ID()
{
	static int _id = 0;
	return _id++;
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	/*
	Quart::Window window(780, 300, "Agenda telefonica");

	auto lv = new Quart::ListView(0, 175, 0, 588, 241);

	auto numeLbl     = new Quart::Label	  (1,  5,  5   + 30 , 100, 100, "Nume");
	auto numeEdit    = new Quart::EditBox (2,  70, 5   + 30 , 100, 20,  "");
	auto prenumeLbl  = new Quart::Label	  (3,  5,  30  + 30 , 100, 100, "Prenume");
	auto prenumeEdit = new Quart::EditBox (4,  70, 30  + 30 , 100, 20,  "");
	auto numarLbl    = new Quart::Label	  (5,  5,  55  + 30 , 100, 100, "Numar");
	auto numarEdit   = new Quart::EditBox (6,  70, 55  + 30 , 100, 20,  "");
	auto adresaLbl   = new Quart::Label	  (7,  5,  80  + 30 , 100, 100, "Adresa");
	auto adresaEdit  = new Quart::EditBox (8,  70, 80  + 30 , 100, 20,  "");
	auto orasLbl     = new Quart::Label	  (9,  5,  105 + 30 , 100, 100, "Oras");
	auto orasEdit    = new Quart::EditBox (10, 70, 105 + 30 , 100, 20,  "");
	auto judetLbl    = new Quart::Label	  (11, 5,  130 + 30 , 100, 100, "Judet");
	auto judetEdit   = new Quart::EditBox (12, 70, 130 + 30 , 100, 20,  "");

	auto addBtn		 = new Quart::Button  (13, 5,  196,  82, 20,  "Add");
	auto removeBtn	 = new Quart::Button  (14, 90, 196,  82, 20,  "Remove");
	auto findBtn	 = new Quart::Button  (15, 5,  218,  82, 20,  "Find");
	auto editBtn	 = new Quart::Button  (16, 90, 218,	 82, 20,  "Edit");

	auto tipLbl		 = new Quart::Label	  (17, 5,  5, 100, 100, "Tip");
	auto tipCb		 = new Quart::ComboBox(18, 70, 5, 100, 50);

	auto mb       = new Quart::MenuBar();

	auto saveElem  = new Quart::SubmenuElement(19, "Save");
	auto loadElem  = new Quart::SubmenuElement(20, "Load");
	auto clearElem = new Quart::SubmenuElement(21, "Clear");

	mb->Add(new Quart::MenuElement("File", 3, saveElem, loadElem, clearElem));

	window.Add(mb);
	window.Add(lv);
	window.Add(numeLbl);
	window.Add(numeEdit);
	window.Add(prenumeLbl);
	window.Add(prenumeEdit);
	window.Add(numarLbl);
	window.Add(numarEdit);
	window.Add(adresaLbl);
	window.Add(adresaEdit);
	window.Add(orasLbl);
	window.Add(orasEdit);
	window.Add(judetLbl);
	window.Add(judetEdit);
	window.Add(addBtn);
	window.Add(removeBtn);
	window.Add(findBtn);
	window.Add(tipLbl);
	window.Add(tipCb);
	window.Add(editBtn);

	window.Create(inst, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME);

	tipCb->Add("Friend");
	tipCb->Add("Acquaintance");
	tipCb->Add("Colleague");

	lv->AddCollumn("Nume");
	lv->AddCollumn("Prenume");
	lv->AddCollumn("Numar");
	lv->AddCollumn("Adresa");
	lv->AddCollumn("Oras");
	lv->AddCollumn("Judet");

	Agenda ag;

	for(const auto& contact : ag.GetContacts())
	{
		lv->AddItem(ID(), contact->GetNume(), 
			contact->GetPrenume(), 
			contact->GetNumar(), 
			contact->GetAdresa(),
			contact->GetOras(),
			contact->GetJudet());
	}

	lv->Focus();

	window.callback[WM_DESTROY] = [&](WPARAM wparam, LPARAM lparam)
	{
		saveElem->callback[Quart::SELF](wparam, lparam);
	};

	clearElem->callback[Quart::SELF] = [&](WPARAM, LPARAM)
	{
		if(ag.GetContacts().size() != 0)
		{
			ag.Clear();
			lv->Clear();
		}
	};

	saveElem->callback[Quart::SELF] = [&](WPARAM, LPARAM)
	{
		if(ag.Modified())
		{
			Quart::SaveFileDialog saveDlg(window, "All files\0*.*\0\0");
			tstring fileName = saveDlg.Get();

			if(!fileName.empty())
				ag.SaveToFile(fileName);
		}
	};

	loadElem->callback[Quart::SELF] = [&](WPARAM, LPARAM)
	{
		Quart::OpenFileDialog dlg(window, "All files\0*.*\0\0");
		auto fname = dlg.Get();

		if(fname.empty())
			return;

		std::ifstream fp(fname);
		fp>>ag;
		fp.close();
		ag.modified = false;

		for(const auto& contact : ag.GetContacts())
		{
			lv->AddItem(ID(), contact->GetNume(), 
				contact->GetPrenume(), 
				contact->GetNumar(), 
				contact->GetAdresa(),
				contact->GetOras(),
				contact->GetJudet());
		}

		lv->Focus();
	};

	addBtn->callback[BN_CLICKED] = [&](WPARAM, LPARAM)
	{
		if(numeEdit->GetText().empty() || numarEdit->GetText().empty())
		{
			Quart::Messagebox("Nu ati completat campurile obligatorii !");
			return;
		}

		Contact* what = nullptr;

		switch(tipCb->SelectionIndex())
		{
		case 0:
			what = ContactFactory::Create("Friend");
			break;

		case 1:
			what = ContactFactory::Create("Acquaintance");
			break;
		
		case 2:
			what = ContactFactory::Create("Colleague");
			break;
		}
		what->SetNumar(numarEdit->GetText());
		what->SetNume(numeEdit->GetText());
		what->SetPrenume(prenumeEdit->GetText());
		what->SetAdresa(adresaEdit->GetText());
		what->SetOras(orasEdit->GetText());
		what->SetJudet(orasEdit->GetText());

		ag.Add(what);

		lv->AddItem(ID(),	numeEdit->GetText(), 
							prenumeEdit->GetText(), 
							numarEdit->GetText(),
							adresaEdit->GetText(),
							orasEdit->GetText(),
							judetEdit->GetText());

		numeEdit->Clear();
		prenumeEdit->Clear();
		numarEdit->Clear();
		adresaEdit->Clear();
		orasEdit->Clear();
		judetEdit->Clear();
	};

	removeBtn->callback[BN_CLICKED] = [&](WPARAM, LPARAM)
	{
		if(numeEdit->GetText().empty() && numarEdit->GetText().empty())
		{
			Quart::Messagebox("Nu ati completat campurile obligatorii !");
			return;
		}

		auto contacts = ag.GetContacts();

		for(unsigned int i = 0; i < contacts.size(); ++i)
		{
			if((contacts[i]->GetNume()	  == numeEdit->GetText())   ||
				contacts[i]->GetPrenume() == prenumeEdit->GetText() ||
				contacts[i]->GetNumar()   == numarEdit->GetText()   ||
				contacts[i]->GetAdresa()  == adresaEdit->GetText())
			{
				lv->RemoveItem(i);

				if(!numarEdit->GetText().empty())
					ag.RemoveByNumber(numarEdit->GetText());
				else if(!numeEdit->GetText().empty())
					ag.RemoveByName(numeEdit->GetText());
				else if(!prenumeEdit->GetText().empty())
					ag.RemoveBySurname(prenumeEdit->GetText());
				else if(!adresaEdit->GetText().empty())
					ag.RemoveByAddress(adresaEdit->GetText());
			}
		}
	};

	unsigned int selectedIndex = -1;

	findBtn->callback[BN_CLICKED] = [&](WPARAM,LPARAM)
	{
		if(numeEdit->GetText().empty()	  && 
		   prenumeEdit->GetText().empty() && 
		   numarEdit->GetText().empty()	  &&
		   adresaEdit->GetText().empty())
		{
			Quart::Messagebox("Nu ati introdus date suficiente pentru o cautare !");
			return;
		}

		auto contacts = ag.GetContacts();
		bool found = false;

		for(unsigned int i = 0; i < contacts.size(); ++i)
		{
			if(!numeEdit->GetText().empty() && 
				contacts[i]->GetNume() == numeEdit->GetText() );

			else if(!prenumeEdit->GetText().empty() && 
					 contacts[i]->GetPrenume() == prenumeEdit->GetText() );
			
			else if(!numarEdit->GetText().empty() &&
					 contacts[i]->GetNumar() == numarEdit->GetText());
			
			else if(!adresaEdit->GetText().empty() &&
					 contacts[i]->GetAdresa() == adresaEdit->GetText());
			else
				continue;

			selectedIndex = i;
			lv->ScrollTo(i);
			lv->Focus();

			numeEdit->SetText(contacts[i]->GetNume());
			prenumeEdit->SetText(contacts[i]->GetPrenume());
			numarEdit->SetText(contacts[i]->GetNumar());
			adresaEdit->SetText(contacts[i]->GetAdresa());
			orasEdit->SetText(contacts[i]->GetOras());
			judetEdit->SetText(contacts[i]->GetJudet());
			
			found = true;
			break;
		}

		if(!found)
			Quart::Messagebox("Contactul nu a putut fi gasit !");
	};

	editBtn->callback[BN_CLICKED] = [&](WPARAM, LPARAM)
	{
		if(selectedIndex != -1)
		{
			auto contacts = ag.GetContacts();

			if((!numeEdit->GetText().empty()	&& numeEdit->GetText()		!= contacts[selectedIndex]->GetNume())	  ||
			   (!prenumeEdit->GetText().empty() && prenumeEdit->GetText()	!= contacts[selectedIndex]->GetPrenume()) ||
			   (!numarEdit->GetText().empty()	&& numarEdit->GetText()		!= contacts[selectedIndex]->GetNumar())   ||
			   (adresaEdit->GetText() != contacts[selectedIndex]->GetAdresa()) ||
			   (orasEdit->GetText()	  != contacts[selectedIndex]->GetOras()) ||
			   (judetEdit->GetText()  != contacts[selectedIndex]->GetJudet()))
			{
				contacts[selectedIndex]->SetNume(numeEdit->GetText());
				contacts[selectedIndex]->SetPrenume(prenumeEdit->GetText());
				contacts[selectedIndex]->SetNumar(numarEdit->GetText());
				contacts[selectedIndex]->SetAdresa(adresaEdit->GetText());
				contacts[selectedIndex]->SetOras(orasEdit->GetText());
				contacts[selectedIndex]->SetJudet(judetEdit->GetText());

				lv->EditItem(selectedIndex, numeEdit->GetText(),
											prenumeEdit->GetText(),
											numarEdit->GetText(),
											adresaEdit->GetText(),
											orasEdit->GetText(),
											judetEdit->GetText());
				ag.modified = true;
				return;
			}
		}
	};

	return window.Run();*/

	Quart::Window wnd(800, 600, "I'm a title");

	auto btn = new Quart::Button(ID(), 50, 50, 100, 20, "PUSH ME");

	auto mb = new Quart::MenuBar();
	auto file = new Quart::SubmenuElement(ID(), "&Test");

	auto testAccel = new Quart::Accelerator(ID(), Quart::Modifiers::CONTROL, Quart::vKeys::Key_S);
	testAccel->callback[Quart::SELF] = [](WPARAM, LPARAM)
	{
		Quart::Messagebox("testing stuff");
	};

	mb->Add(new Quart::MenuElement("&File", 1, file));

	wnd.Add(mb);
	wnd.Add(testAccel);

	btn->callback[BN_CLICKED] = [&](WPARAM, LPARAM)
	{
		Quart::Window lel(400, 300, "I'm a dialog title", &wnd);
		wnd.Disable();

		auto editBox = new Quart::Button(1, 50, 50, 200, 20, "PUT TEXT HERE");
		editBox->callback[BN_CLICKED] = [&](WPARAM, LPARAM)
		{
			lel.Close();
		};

		lel.Add(editBox);

		lel.Run(WS_VISIBLE | WS_CAPTION);

		wnd.Enable();
	};

	wnd.Add(btn);

	return wnd.Run();
}