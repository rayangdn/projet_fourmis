#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cairomm/context.h>
#include <utility>
//#include <bits/stdc++.h> 

#include "gui.h"

using namespace std;

//static Frame default_frame = {-64., 64., -64., 64, 1, 128, 128};
//static Frame default_frame = {-150., 150, -100., 100 1.5, 300, 200};
 
Gui::Gui(Simulation simulation): 
	simulation(std::move(simulation)),
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

  // Connect the clicked signal of the button to
  // thier signal handler
	m_Button_Exit.signal_clicked().connect(sigc::mem_fun(*this,
              &Gui::on_button_clicked_Exit) );

	m_Button_Open.signal_clicked().connect(sigc::mem_fun(*this,
              &Gui::on_button_clicked_Open) );

	m_Button_Save.signal_clicked().connect(sigc::mem_fun(*this,
              &Gui::on_button_clicked_Save) );

	m_Button_Start.signal_clicked().connect(sigc::mem_fun(*this,
              &Gui::on_button_clicked_Start) );

	m_Button_Step.signal_clicked().connect(sigc::mem_fun(*this,
              &Gui::on_button_clicked_Step) );
              
	m_Button_Previous.signal_clicked().connect(sigc::mem_fun(*this,
              &Gui::on_button_clicked_Previous) );
  
	m_Button_Next.signal_clicked().connect(sigc::mem_fun(*this,
              &Gui::on_button_clicked_Next) );

  // Show all children of the window
		show_all_children();


	//set_frame(default_frame);
}
Gui::~Gui() {}

void Gui::on_button_clicked_Exit()
{
  cout << "Exit" << endl;
  hide();
}

void Gui::on_button_clicked_Open()
{
 // cout << "Open"  << endl;
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
   //   std::cout << "Open clicked." << std::endl;

      //Notice that this is a std::string, not a Glib::ustring.
      std::string filename = dialog.get_filename();
      std::cout << "File selected: " <<  filename << std::endl;
	simulation.lecture(filename);
    /* if(simulation.lecture(filename)==false){
		simulation.supprimer_structs();
	}*/
      
    }
    case(Gtk::RESPONSE_CANCEL):
    {
    //  std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }

}

void Gui::on_button_clicked_Save()
{
  cout << "Save" << endl;
}

void Gui::on_button_clicked_Start()
{
   if(not timer_added)
  {	  
	  cout << "Start" << endl;
	  
	  Glib::signal_timeout().connect( sigc::mem_fun(*this, &Gui::on_timeout),
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

bool Gui::on_timeout()
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


void Gui::on_button_clicked_Step()
{
	if(not timer_added) {													// Suffisant ou est ce que on doit bloqué le bouttons ?
		cout << "Step" << endl;												//hide () to close the application. (ça fait la même que exit() mais pour gtkmm car exit ça marche pas !!)
		cout << "This is simulation update number : " << val << endl;
		++val; // tic the simulation clock
	}
}
void Gui::on_button_clicked_Previous()
{
  
}

void Gui::on_button_clicked_Next()
{	

}
/*void Gui::set_frame(Frame f)
{
	if((f.xMin <= f.xMax) and (f.yMin <= f.yMax) and (f.height > 0))
	{
		f.asp = f.width/f.height;
		frame = f;
	}
	else
		std::cout << "incorrect Model framing or window parameters" << std::endl;
} 
void Gui::adjust_frame()
{
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	
	frame.width  = width;
	frame.height = height;

	// Preventing distorsion by adjusting the frame (cadrage)
	// to have the same proportion as the graphical area
	
    // use the reference framing as a guide for preventing distortion
    double new_aspect_ratio((double)width/height);
    if( new_aspect_ratio > default_frame.asp)
    { // keep yMax and yMin. Adjust xMax and xMin
	    frame.yMax = default_frame.yMax ;
	    frame.yMin = default_frame.yMin ;	
	  
	    double delta(default_frame.xMax - default_frame.xMin);
	    double mid((default_frame.xMax + default_frame.xMin)/2);
        // the new frame is centered on the mid-point along X
	    frame.xMax = mid + 0.5*(new_aspect_ratio/default_frame.asp)*delta ;
	    frame.xMin = mid - 0.5*(new_aspect_ratio/default_frame.asp)*delta ;		  	  
    }
    else
    { // keep xMax and xMin. Adjust yMax and yMin
	    frame.xMax = default_frame.xMax ;
	    frame.xMin = default_frame.xMin ;
	  	  
 	    double delta(default_frame.yMax - default_frame.yMin);
	    double mid((default_frame.yMax + default_frame.yMin)/2);
        // the new frame is centered on the mid-point along Y
	    frame.yMax = mid + 0.5*(default_frame.asp/new_aspect_ratio)*delta ;
	    frame.yMin = mid - 0.5*(default_frame.asp/new_aspect_ratio)*delta ;		  	  
    }
}
static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, Frame frame) {
	
	// déplace l'origine au centre de la fenêtre
	cr->translate(frame.width/2, frame.height/2);
 
	// normalise la largeur et hauteur aux valeurs fournies par le cadrage
	// ET inverse la direction de l'axe Y
	
	cr->scale(frame.width/(frame.xMax - frame.xMin), 
           -frame.height/(frame.yMax - frame.yMin));
  
	// décalage au centre du cadrage
	cr->translate(-(frame.xMin + frame.xMax)/2, -(frame.yMin + frame.yMax)/2);
	cr->translate(-64, -64); //origine de notre grille


}

bool Gui::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
		
	adjust_frame();
	orthographic_projection(cr, frame);
	
	Graphic graphic;
	graphic.set_context(cr);
	simulation.draw_simulation(graphic);
	return true;
}

*/
