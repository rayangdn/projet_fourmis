#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "gui.h"

using namespace std;

Interface::Interface () :
  m_Box_Top(Gtk::ORIENTATION_VERTICAL, 10),
  m_Box1(Gtk::ORIENTATION_VERTICAL, 10),
  m_Box2(Gtk::ORIENTATION_VERTICAL, 10),
  m_Box3(Gtk::ORIENTATION_VERTICAL, 10),
  m_Label_General("General"),
  m_Label_Info("Info"),
  m_Label_AnthillInfo("Anthill info"),
  m_Button_Exit("exit"),
  m_Button_Open("open"),
  m_Button_Save("save"),
  m_Button_Start("start"),
  m_Button_Step("step"),
  m_Button_Previous("previous"),
  m_Button_Next("next")
{
  // Set title and border of the window
  set_title("Tchanz");
  set_border_width(0);

  // Add outer box to the window (because the window
  // can only contain a single widget)
  add(m_Box_Top);

  //Put the inner boxes and the separator in the outer box:
  m_Box_Top.pack_start(m_Label_General);
  m_Box_Top.pack_start(m_Box1);
  m_Box_Top.pack_start(m_Separator1);
  m_Box_Top.pack_start(m_Label_Info);
  m_Box_Top.pack_start(m_Box2);
  m_Box_Top.pack_start(m_Separator2);
  m_Box_Top.pack_start(m_Label_AnthillInfo);
  m_Box_Top.pack_start(m_Box3);

  // Set the inner boxes' borders
  m_Box2.set_border_width(10);
  m_Box1.set_border_width(10);

  // Put Hello / Bonjour buttons in Box1:
  m_Box1.pack_start(m_Button_Exit);
  m_Box1.pack_start(m_Button_Open);
  m_Box1.pack_start(m_Button_Save);
  m_Box1.pack_start(m_Button_Start);
  m_Box1.pack_start(m_Button_Step);

  // Put Madame / Monsieur buttons in Box2:
  m_Box3.pack_start(m_Button_Previous);
  m_Box3.pack_start(m_Button_Next);

  // Connect the clicked signal of the button to
  // thier signal handler
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
  show_all_children();												// IMPORTANT permet de voir les bouttons et l'intérieur de la fenêtre
}

Interface::~Interface()
{
}

void Interface::on_button_clicked_Exit()
{
  cout << "Exit " << endl;			// Le endl vide le buffer de sortie => 
									// quand on cliquera sur Hello ce sera directement 
}									// affiché mais pas si onclique sur Bonjour car pas de endl !!

void Interface::on_button_clicked_Open()
{
  cout << "Open" << endl;
}

void Interface::on_button_clicked_Save()
{
  cout << "Save" << endl;
}

void Interface::on_button_clicked_Start()
{
  cout << "Start" << endl;
}

void Interface::on_button_clicked_Step()
{
  cout << "Step" << endl; //hide () to close the application.
}

void Interface::on_button_clicked_Previous()
{
  cout << "Previous" << endl;
}

void Interface::on_button_clicked_Next()
{
  cout << "Next" << endl;
}
