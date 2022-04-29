#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <gtkmm.h>
#include <utility>
#include "simulation.h"
#include "graphic.h"

constexpr unsigned taille_dessin(500);

struct Distortion 
{
	double xMin; 
	double xMax;
	double yMin;
	double yMax;
	double asp; 
	int height;  
	int width; 
};
class MyArea : public Gtk::DrawingArea {
	public :
	MyArea();
	~MyArea();
	void set_frame(Distortion); 
	void adjust_frame();
	void clear();
	void draw();
	void refresh();
	protected :
	
	bool empty;
	Distortion distortion;
	
	 
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  
	
};
class MyEvent : public Gtk::Window {
public:
	MyEvent(Simulation *simulation);
	virtual ~MyEvent();
	void affiche_food();
private :
	MyArea m_area;
	bool timer_added;
	bool disconnect;
	const int timeout_value;
	unsigned int val;
	unsigned int nb_food;	
	int indice_frmi; 
	void maj_nbf(); 
	void maj_info_frmi(int indice);
	std::string convertion_unInt_to_strg(int&) const;
	
protected:
	void on_button_clicked_Exit();
	void on_button_clicked_Open();
	void on_button_clicked_Save();
	void on_button_clicked_Start();
	void on_button_clicked_Step();
	void on_button_clicked_Previous();
	void on_button_clicked_Next();
	bool on_key_press_event(GdkEventKey * key_event);
	bool on_timeout();
    
	Gtk::Box m_Box, m_Box_Left, m_Box_Right, m_Box_Top, m_Box1, m_Box2, m_Box3;
  
	Gtk::Frame m_Frame_General;
	Gtk::Frame m_Frame_Info;
	Gtk::Frame m_Frame_AnthillInfo;
  
	Gtk::Label m_Label_Info;
	Gtk::Label m_Label_Frmi;				
  
	Gtk::Button m_Button_Exit;
	Gtk::Button m_Button_Open;
	Gtk::Button m_Button_Save;
	Gtk::Button m_Button_Start;
	Gtk::Button m_Button_Step;
	Gtk::Button m_Button_Previous;
	Gtk::Button m_Button_Next;
};
#endif
