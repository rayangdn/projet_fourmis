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
  bool on_timeout();
    
  //Child widgets:
  Gtk::Box m_Box_Top, m_Box1, m_Box2, m_Box3;
  
  Gtk::Frame m_Frame_General;
  Gtk::Frame m_Frame_Info;
  Gtk::Frame m_Frame_AnthillInfo;
  
  Gtk::Label m_Label_Info;				// Peut-on utiliser Frame_Info ???
  
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
  unsigned int val;					// est ce que ça doit être une variable static ??
};


