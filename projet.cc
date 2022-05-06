//projet.cc
//Rayan Gauderon membre 1: 100%
//Maxime Luyet membre 2: 0%

#include "simulation.h"
#include "gui.h"

int main(int argc, char* argv[]) {
	initialise_grid(g_max);
	Simulation simulation;
	if(argc == 2) {
		simulation.lecture(argv[1]);
		
	}
	auto app = Gtk::Application::create();
	MyEvent myevent(&simulation);
	return app->run(myevent);
}
//si collector a une food celle-çi appartient à ensemble_food??
//différence entre size et sizeF??
