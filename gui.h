#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED


#include "simulation.h"
#include <gtkmm.h>

class Interface : public Gtk::Window
{
public:
  Interface();
  virtual ~Interface();

protected:
  //Signal handlers:
  void on_button_clicked_Exit();
  void on_button_clicked_Open();
  void on_button_clicked_Save();
  void on_button_clicked_Start();
  void on_button_clicked_Step();
  void on_button_clicked_Previous();
  void on_button_clicked_Next();
  
  //Child widgets:
  Gtk::Box m_Box_Top, m_Box1, m_Box2, m_Box3;
  
  Gtk::Separator m_Separator1;
  Gtk::Separator m_Separator2;
  
  Gtk::Label m_Label_General;
  Gtk::Label m_Label_Info;
  Gtk::Label m_Label_AnthillInfo;
  
  Gtk::Button m_Button_Exit;
  Gtk::Button m_Button_Open;
  Gtk::Button m_Button_Save;
  Gtk::Button m_Button_Start;
  Gtk::Button m_Button_Step;
  Gtk::Button m_Button_Previous;
  Gtk::Button m_Button_Next;
};

#endif