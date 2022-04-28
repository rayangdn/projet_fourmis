#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cairomm/context.h>
#include <utility>


#include "gui.h"

using namespace std;

static Distortion default_distortion = {-70, 70, -70, 70, 1, 140, 140};

MyArea::MyArea(Simulation simulation): simulation(std::move(simulation)), empty(false) {
	set_frame(default_distortion);
}

MyArea::~MyArea () {}

Simulation MyArea::get_simulation() const {
	
}
void MyArea::set_frame(Distortion d) {
	if((d.xMin <= d.xMax) and (d.yMin <= d.yMax) and (d.height > 0))
	{
		d.asp = d.width/d.height;
		distortion = d;
	}
	else
		std::cout << "incorrect Model framing or window parameters" << std::endl;
} 

void MyArea::adjust_frame() {
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	
	distortion.width  = width;
	distortion.height = height;
	
    double new_aspect_ratio((double)width/height);
    if( new_aspect_ratio > default_distortion.asp) { 
	    distortion.yMax = default_distortion.yMax ;
	    distortion.yMin = default_distortion.yMin ;	
	    double delta(default_distortion.xMax - default_distortion.xMin);
	    double mid((default_distortion.xMax + default_distortion.xMin)/2);
	    distortion.xMax = mid + 0.5*(new_aspect_ratio/default_distortion.asp)*delta ;
	    distortion.xMin = mid - 0.5*(new_aspect_ratio/default_distortion.asp)*delta ;		  	  
    } else { 
	    distortion.xMax = default_distortion.xMax ;
	    distortion.xMin = default_distortion.xMin ;
 	    double delta(default_distortion.yMax - default_distortion.yMin);
	    double mid((default_distortion.yMax + default_distortion.yMin)/2);
	    distortion.yMax = mid + 0.5*(default_distortion.asp/new_aspect_ratio)*delta ;
	    distortion.yMin = mid - 0.5*(default_distortion.asp/new_aspect_ratio)*delta ;		  	  
    }
}

static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, Distortion distortion) {
	cr->translate(distortion.width/2, distortion.height/2);
	cr->scale(distortion.width/(distortion.xMax - distortion.xMin), 
           -distortion.height/(distortion.yMax - distortion.yMin));
	cr->translate(-(distortion.xMin + distortion.xMax)/2, -(distortion.yMin + distortion.yMax)/2);
	cr->translate(-64, -64); //origine de notre grille


}
void MyArea::clear() {
	empty = true; 
	refresh();
}

void MyArea::draw() {
	empty = false;
	refresh();
}
void MyArea::refresh() {
	auto win = get_window();
	if(win)
	{
		Gdk::Rectangle r(0,0, get_allocation().get_width(), 
						      get_allocation().get_height());
								
		win->invalidate_rect(r,false);
	}
}
	

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	adjust_frame();
	orthographic_projection(cr, distortion);
	if(not empty) {
	Graphic graphic;
	graphic.set_context(cr);
	simulation.draw_simulation(graphic);
	}
	return true;
}

//=====================================================================================

MyEvent::MyEvent(Simulation simulation): 
	//simulation(std::move(simulation)), // probleme unique ptr
	m_area(std::move(simulation)),
	timer_added(false),
	disconnect(false),
	timeout_value(500),
	val(1),
	indice_frmi(-1),  // valeur avant l'indice de la premiere fourmiliere qui est 0
	m_Box(Gtk::ORIENTATION_HORIZONTAL,10),
	m_Box_Left(Gtk::ORIENTATION_VERTICAL, 10),
	m_Box_Right(Gtk::ORIENTATION_VERTICAL, 10),
	m_Box_Top(Gtk::ORIENTATION_VERTICAL, 10),
	m_Box1(Gtk::ORIENTATION_VERTICAL, 10),
	m_Box2(Gtk::ORIENTATION_VERTICAL, 10),
	m_Box3(Gtk::ORIENTATION_VERTICAL, 10),
  
	m_Frame_General("General"),
	m_Frame_Info("Info"),
	m_Frame_AnthillInfo("Anthill info"),
  
	m_Label_Frmi("None selected"),
  
	m_Button_Exit("exit"),
	m_Button_Open("open"),
	m_Button_Save("save"),
	m_Button_Start("start"),
	m_Button_Step("step"),
	m_Button_Previous("previous"),
	m_Button_Next("next")
{
	set_title("Tchanz");
	add(m_Box);
	m_Box.pack_start(m_Box_Left);
	m_Box.pack_start(m_Box_Right);
	
	m_Box_Left.pack_start(m_Box_Top);
	
	m_area.set_size_request(taille_dessin, taille_dessin);
	m_Box_Right.pack_start(m_area);
  
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
  
	m_Box2.pack_start(m_Label_Info);
	maj_nbf();
  
	m_Box_Top.pack_start(m_Frame_AnthillInfo, Gtk::PACK_EXPAND_WIDGET, 10);
	m_Frame_AnthillInfo.add(m_Box3);
  
	m_Box3.pack_start(m_Button_Previous);
	m_Box3.pack_start(m_Button_Next);
	m_Box3.pack_start(m_Label_Frmi);
  
	m_Button_Exit.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_Exit) );

	m_Button_Open.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_Open) );

	m_Button_Save.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_Save) );

	m_Button_Start.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_Start) );

	m_Button_Step.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_Step) );
              
	m_Button_Previous.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_Previous) );
  
	m_Button_Next.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_Next) );

	add_events(Gdk::KEY_RELEASE_MASK);
	
	show_all_children();
}
MyEvent::~MyEvent() {}

void MyEvent::on_button_clicked_Exit() {
	hide();
}

void MyEvent::on_button_clicked_Open() {
	m_area.simulation.supprimer_structs();
	m_area.clear();
	indice_frmi = -1;
	maj_info_frmi(indice_frmi);
	val=1;
	Gtk::FileChooserDialog dialog("Please choose a file",
    Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);
	
	int result = dialog.run();

	switch(result) {
		case(Gtk::RESPONSE_OK): {
			std::string filename = dialog.get_filename();
			std::cout << "File selected: " <<  filename << std::endl;
			m_area.simulation.lecture(filename);
			m_area.draw();
		}
		case(Gtk::RESPONSE_CANCEL): {
			m_area.draw();
			break;
		}
		default: {
			m_area.draw();
			break;
		}
	}
	maj_nbf();
}

void MyEvent::on_button_clicked_Save() {
	//comment sauvegarder notre grille a la place d'un nouveau fichier??
	Gtk::FileChooserDialog dialog("Please choose a file",
	Gtk::FILE_CHOOSER_ACTION_SAVE);
	dialog.set_transient_for(*this);
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Save", Gtk::RESPONSE_OK);
	int result = dialog.run();
	switch(result) {
		case(Gtk::RESPONSE_OK): {
			std::string filename = dialog.get_filename();
			std::cout << "File saved: " <<  filename << std::endl;
		}
		case(Gtk::RESPONSE_CANCEL): {
			break;
		}
		default: {
			std::cout << "Unexpected button clicked." << std::endl;
			break;
		}
	}
}


void MyEvent::on_button_clicked_Start() {
	if(not timer_added) {	  
		Glib::signal_timeout().connect( sigc::mem_fun(*this, &MyEvent::on_timeout),
		timeout_value );
		timer_added = true;
		m_Button_Start.set_label("stop");
	} else {	    
		disconnect  = true;   
		timer_added = false;
		m_Button_Start.set_label("start");
	}
}

bool MyEvent::on_timeout() {
	if(disconnect) {
		disconnect = false; 
		return false;
	}
	cout << val << endl;
	++val;
	m_area.refresh();
	return true; 
}

void MyEvent::on_button_clicked_Step() {
	if(not timer_added) {												
		cout << val << endl;												
		++val; 
		m_area.refresh();
	}
}

void MyEvent::on_button_clicked_Previous() {
	indice_frmi = indice_frmi - 1;
	if(indice_frmi < -1) {
		indice_frmi=  m_area.simulation.get_nb_fourmiliere()-1;
	}
	maj_info_frmi(indice_frmi);
}

void MyEvent::on_button_clicked_Next() {	
	indice_frmi = indice_frmi + 1;
	if(indice_frmi >=  m_area.simulation.get_nb_fourmiliere()){
		indice_frmi = -1;
	}
	maj_info_frmi(indice_frmi);
}

void MyEvent::maj_info_frmi(int indice) {
	if (indice == -1){
		m_Label_Frmi.set_text("None selected");
	} else {
		string info("id: ");
		info += convertion_unInt_to_strg(indice);
		info += "\n";
		info += "Total food: ";
		int total_food = m_area.simulation.get_total_food(indice);
		info += convertion_unInt_to_strg(total_food);
		info += "\n\n nbC: ";
		int nbC = m_area.simulation.get_nbC(indice);
		info += convertion_unInt_to_strg(nbC);
		info += "\n nbD: ";
		int nbD = m_area.simulation.get_nbD(indice);
		info += convertion_unInt_to_strg(nbD);
		info += "\n nbP: ";
		int nbP = m_area.simulation.get_nbP(indice);
		info += convertion_unInt_to_strg(nbP);
		info += "\n";
		m_Label_Frmi.set_text(info);
		
	}
}

void MyEvent::maj_nbf() {
	unsigned int nb_food(m_area.simulation.get_nb_food());
	stringstream food;
	string nbr;
	string info("Nb food: ");
	
	food << nb_food;
	food >> nbr;
	info = info + nbr;
	
	m_Label_Info.set_text(info);
}

string MyEvent::convertion_unInt_to_strg(int& nbr) const {
	stringstream tmp;
	string rendu;
	tmp << nbr;
	tmp >> rendu;
	return rendu;
}

bool MyEvent::on_key_press_event(GdkEventKey * key_event) {
	if(key_event->type == GDK_KEY_PRESS) { //seulement si pas erreur??
		switch(gdk_keyval_to_unicode(key_event->keyval)) {
			case 's':
				on_button_clicked_Start();
				return true;
			case '1':
				if(not timer_added) {
					on_button_clicked_Step();
				}
				return true;
			case 'n':
				on_button_clicked_Next();
				return true;
			case 'p':
				on_button_clicked_Previous();
				return true;
			case 'q':
				on_button_clicked_Exit();
				return true;
		}
	}
	return Gtk::Window::on_key_press_event(key_event);
}

