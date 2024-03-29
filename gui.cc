//gui.cc
//Rayan Gauderon membre 1: 50%
//Maxime Luyet membre 2: 50%

#include <iostream>
#include <iomanip>

#include "gui.h"

using namespace std;

static Simulation *simu;
static Distortion default_distortion = {-70, 70, -70, 70, 1, 140, 140};

MyArea::MyArea() : empty(false) {
	set_frame(default_distortion);
}

MyArea::~MyArea () {}

void MyArea::set_frame(Distortion d) {
	if((d.xMin <= d.xMax) and (d.yMin <= d.yMax) and (d.height > 0))
	{
		d.asp = d.width/d.height;
		distortion = d;
	}
	else
		cout << "incorrect Model framing or window parameters" << endl;
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
	    distortion.xMax = mid + 0.5*(new_aspect_ratio/default_distortion.asp)*delta;
	    distortion.xMin = mid - 0.5*(new_aspect_ratio/default_distortion.asp)*delta;		  	  
    } else { 
	    distortion.xMax = default_distortion.xMax ;
	    distortion.xMin = default_distortion.xMin ;
 	    double delta(default_distortion.yMax - default_distortion.yMin);
	    double mid((default_distortion.yMax + default_distortion.yMin)/2);
	    distortion.yMax = mid + 0.5*(default_distortion.asp/new_aspect_ratio)*delta;
	    distortion.yMin = mid - 0.5*(default_distortion.asp/new_aspect_ratio)*delta;		  	  
    }
}

static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, 
Distortion distortion) {
	cr->translate(distortion.width/2, distortion.height/2);
	cr->scale(distortion.width/(distortion.xMax - distortion.xMin), 
         -distortion.height/(distortion.yMax - distortion.yMin));
	cr->translate(-(distortion.xMin + distortion.xMax)/2,
	     -(distortion.yMin + distortion.yMax)/2);
	cr->translate(-64, -64);
}

void MyArea::clear() {
	empty = true; 
}

void MyArea::draw() {
	empty = false;
}

void MyArea::refresh() {
	(*simu).refresh();
	auto win = get_window();
	if(win) {
		Gdk::Rectangle r(0,0,
		get_allocation().get_width(),
		get_allocation().get_height());
		win->invalidate_rect(r,false);
	}
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	adjust_frame();
	orthographic_projection(cr, distortion);
	graphic_set_context(cr);
	graphic_draw_grille();
	if(not empty) {
		(*simu).draw_simulation();
	}
	return true;
}

//=====================================================================================

MyEvent::MyEvent(Simulation *simulation) : 
	timer_added(false),
	disconnect(false),
	timeout_value(20),
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
	simu = simulation;
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
	maj_nombre_food();
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
	m_area.clear();
	indice_frmi = -1;
	maj_info_frmi(indice_frmi);
	val = 1;
	Gtk::FileChooserDialog dialog("Please choose a file",
    Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);
	int result = dialog.run();
	switch(result) {
		case(Gtk::RESPONSE_OK): {
			(*simu).supprimer_structs();
			string filename = dialog.get_filename();
			cout << "File selected: " <<  filename << endl;
			(*simu).lecture(filename);
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
	maj_nombre_food();
}

void MyEvent::on_button_clicked_Save() {
	if(not timer_added) {
		Gtk::FileChooserDialog dialog("Please choose a file",
		Gtk::FILE_CHOOSER_ACTION_SAVE);
		dialog.set_transient_for(*this);
		dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
		dialog.add_button("_Save", Gtk::RESPONSE_OK);
		int result = dialog.run();
		switch(result) {
			case(Gtk::RESPONSE_OK): {
				ofstream fichier(dialog.get_filename());
				if(!(fichier.fail())) {
					(*simu).ecriture_fichier(fichier);
				}
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
	m_area.refresh();
	maj_nombre_food();
	maj_info_frmi(indice_frmi);
	cout << val << endl;
	++val;
	
	return true; 
}

void MyEvent::on_button_clicked_Step() {
	if(not timer_added) {	
		m_area.refresh();		
		maj_nombre_food();
		maj_info_frmi(indice_frmi);
		cout << val << endl;												
		++val; 
		
	}
}

void MyEvent::on_button_clicked_Previous() {
	indice_frmi = indice_frmi - 1;
	if(indice_frmi < -1) {
		indice_frmi= (*simu).get_nb_fourmiliere()-1;
	}
	maj_info_frmi(indice_frmi);
}

void MyEvent::on_button_clicked_Next() {
	indice_frmi = indice_frmi + 1;
	if(indice_frmi >= (int)(*simu).get_nb_fourmiliere()){
		indice_frmi = -1;
	}
	maj_info_frmi(indice_frmi);
}

void MyEvent::maj_info_frmi(int indice) {
	if((*simu).get_nb_fourmiliere() == 0) {
		indice= -1;
	}
	if (indice == -1){
		m_Label_Frmi.set_text("None selected");
	} else {
		string info("id: ");
		info += to_string(indice);
		info += "\n";
		info += "Total food: ";
		double total_food = (*simu).get_total_food(indice);
		ostringstream stream;
		stream << fixed;
		stream << setprecision(2);
		stream << total_food;
		info +=  stream.str(); //pour avoir deux décimales seulement
		info += "\n\n nbC: ";
		int nbC =(*simu).get_nbC(indice);
		info += to_string(nbC);
		info += "\n nbD: ";
		int nbD = (*simu).get_nbD(indice);
		info +=to_string(nbD);
		info += "\n nbP: ";
		int nbP = (*simu).get_nbP(indice);
		info += to_string(nbP);
		info += "\n";
		m_Label_Frmi.set_text(info);
		
	}
}

void MyEvent::maj_nombre_food() {
	unsigned int nb_food((*simu).get_nb_food());
	stringstream food;
	string nbr;
	string info("Nb food: ");
	info += to_string(nb_food);
	m_Label_Info.set_text(info);
}

bool MyEvent::on_key_press_event(GdkEventKey * key_event) {
	if(key_event->type == GDK_KEY_PRESS) {
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

