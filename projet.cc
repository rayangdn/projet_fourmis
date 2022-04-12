//projet.cc
//Rayan Gauderon membre 1: 100%
//Maxime Luyet membre 2: 0%

#include <iostream>
#include <vector>
#include <gtkmm.h>
#include <utility>


#include "simulation.h"
#include "gui.h"

using namespace std;

int main(int argc, char * argv[]) {
	initialise_grid(g_max);
	Simulation simulation;
	if(argc != 2){
		exit(0);
	 }
	if(simulation.lecture(argv[1])==false){
		simulation.supprimer_structs();
	}
	//affiche_grid();
	auto app = Gtk::Application::create();

		Gui gui(std::move(simulation));
		
		return app->run(gui);
		/*Gtk::Window tchankz;
		tchankz.set_title("tchankz");
		tchankz.add(gui);
		gui.show();*/
}
