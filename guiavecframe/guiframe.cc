#include <iostream>
#include "guiframe.h"

using namespace std;

Interface::Interface () :
  m_Box_Top(Gtk::ORIENTATION_VERTICAL, 10),
  m_Box1(Gtk::ORIENTATION_VERTICAL, 10),
  m_Box2(Gtk::ORIENTATION_VERTICAL, 10),
  m_Box3(Gtk::ORIENTATION_VERTICAL, 10),
  
  m_Frame_General("General"),
  m_Frame_Info("Info"),
  m_Frame_AnthillInfo("Anthill info"),
  
  m_Button_Exit("exit"),
  m_Button_Open("open"),
  m_Button_Save("save"),
  m_Button_Start("start"),
  m_Button_Step("step"),
  m_Button_Previous("previous"),
  m_Button_Next("next"),
  
  timer_added(false),
  disconnect(false),
  timeout_value(500),
  val(1) 
{
  set_title("Tchanz");
  add(m_Box_Top);
  
  m_Box_Top.pack_start(m_Frame_General, Gtk::PACK_EXPAND_WIDGET, 10);
 
  m_Box_Top.set_border_width(10);
  m_Frame_General.add(m_Box1);
  
  m_Box1.pack_start(m_Button_Exit);
  m_Box1.pack_start(m_Button_Open);
  m_Box1.pack_start(m_Button_Save);
  m_Box1.pack_start(m_Button_Start);
  m_Box1.pack_start(m_Button_Step);
  
  m_Box_Top.pack_start(m_Frame_Info, Gtk::PACK_EXPAND_WIDGET, 10);
  m_Frame_Info.add(m_Box2);
  
  m_Box_Top.pack_start(m_Frame_AnthillInfo, Gtk::PACK_EXPAND_WIDGET, 10);
  m_Frame_AnthillInfo.add(m_Box3);
  
  m_Box3.pack_start(m_Button_Previous);
  m_Box3.pack_start(m_Button_Next);
  
  m_Button_Exit.signal_clicked().connect(sigc::mem_fun(*this,
              &Interface::on_button_clicked_Exit) );

  m_Button_Open.signal_clicked().connect(sigc::mem_fun(*this,
              &Interface::on_button_clicked_Open) );

  m_Button_Save.signal_clicked().connect(sigc::mem_fun(*this,
              &Interface::on_button_clicked_Save) );

  m_Button_Start.signal_clicked().connect(sigc::mem_fun(*this,
              &Interface::on_button_clicked_Start) );

  m_Button_Step.signal_clicked().connect(sigc::mem_fun(*this,
              &Interface::on_button_clicked_Step) );
              
  m_Button_Previous.signal_clicked().connect(sigc::mem_fun(*this,
              &Interface::on_button_clicked_Previous) );
  
  m_Button_Next.signal_clicked().connect(sigc::mem_fun(*this,
              &Interface::on_button_clicked_Next) );
  
  // Show all children of the window
  show_all_children();				// IMPORTANT permet de voir les bouttons et l'intérieur de la fenêtre
}

Interface::~Interface()
{}

void Interface::on_button_clicked_Exit()
{
  cout << "Exit " << endl;			 
  exit(0);							
}									

void Interface::on_button_clicked_Open()
{
  cout << "Open" << endl;

  Gtk::FileChooserDialog dialog("Please choose a file",
          Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*this);

  //Add response buttons the the dialog:
  dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  dialog.add_button("_Open", Gtk::RESPONSE_OK);

  m_Label_Info.set_text("choosing a file");

  //Show the dialog and wait for a user response:
  int result = dialog.run();

  m_Label_Info.set_text("Done choosing a file");

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      std::cout << "Open clicked." << std::endl;

      //Notice that this is a std::string, not a Glib::ustring.
      std::string filename = dialog.get_filename();
      std::cout << "File selected: " <<  filename << std::endl;
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }

}

void Interface::on_button_clicked_Save()
{
  cout << "Save" << endl;
}

void Interface::on_button_clicked_Start()
{  
  if(not timer_added)
  {	  
	  cout << "Start" << endl;
	  
	  Glib::signal_timeout().connect( sigc::mem_fun(*this, &Interface::on_timeout),
									  timeout_value );
		
	  timer_added = true;
	  m_Button_Start.set_label("Stop");
		
	  cout << "Timer added" << endl;
	  //~ m_Button_Start("Start") = m_Buton_Start("Stop");
  }
  else
  {
 	  //~ std::cout << "The timer already exists : nothing more is created" << std::endl;
 	    
      cout << "manually disconnecting the timer " << endl;
	  disconnect  = true;   
      timer_added = false;
      
      cout << "Stop" << endl;
      m_Button_Start.set_label("Start");
  }

}

bool Interface::on_timeout()
{
  if(disconnect)
  {
	  disconnect = false; // reset for next time a Timer is created
	  
	  return false; // End of Timer 
  }
  
  cout << "This is simulation update number : " << val << endl;
  ++val; // tic the simulation clock

  return true; 
}

void Interface::on_button_clicked_Step()		
{
  if(not timer_added) {													// Suffisant ou est ce que on doit bloqué le bouttons ?
	cout << "Step" << endl;												//hide () to close the application. (ça fait la même que exit() mais pour gtkmm car exit ça marche pas !!)
	cout << "This is simulation update number : " << val << endl;
	++val; // tic the simulation clock
	}
}							

void Interface::on_button_clicked_Previous()
{
  cout << "Previous" << endl;
}

void Interface::on_button_clicked_Next()
{
  cout << "Next" << endl;
}
