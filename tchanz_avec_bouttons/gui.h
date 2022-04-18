#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <gtkmm.h>
#include <string>

#include "simulation.h"
#include "graphic.h"

struct Frame // Model Framing and window parameters
{
	double xMin; // frame parameters
	double xMax;
	double yMin;
	double yMax;
	double asp;  // frame aspect ratio
	int height;  // window height
	int width;   // window width
};

class Gui : public Gtk::Window //Gtk::DrawingArea
{
public:
	Gui(Simulation);
	virtual ~Gui();
	void affiche_food();
	//void set_frame(Frame); 
	//void adjust_frame();
private :
	Simulation simulation;
  
  
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
    
  //Child widgets:
  Gtk::Box m_Box_Top, m_Box1, m_Box2, m_Box3;
  
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
private :
  bool timer_added;
  bool disconnect;
  const int timeout_value;
  unsigned int val;
  unsigned int nb_food;	
  int indice_frmi; 
  void maj_nbf(); 
  void maj_info_frmi(unsigned int indice);
  std::string convertion_unInt_to_strg(unsigned int&) const;
  //bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

  //Frame frame;
				// est ce que ça doit être une variable static ??
};

//~ class MyArea : public Gtk::DrawingArea {
	
#endif
