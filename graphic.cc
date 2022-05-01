//graphic.cc
//Rayan Gauderon membre 1: 60%
//Maxime Luyet membre 2: 40%

#include "graphic.h"

#include <iostream>

using namespace std;

static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr);

void Graphic::set_context(const Cairo::RefPtr<Cairo::Context>& cr) {
	ptcr = &cr;
}

void Graphic::initialise_couleur(unsigned int c, double& r, double& g,
double& b) {
	if(c == ROUGE) {
		r = 1.0; g = 0.0, b = 0.0;
	}
	if(c == GREEN) {
		r = 0.0; g = 1.0; b = 0.0;
	}
	if(c == BLUE) {
		r = 0.0; g = 0.0; b = 1.0;
	}
	if(c == YELLOW) {
		r = 1.0; g = 1.0; b = 0.0;
	}
	if(c == MAGENTA) {
		r = 1.0; g = 0.0; b = 1.0;
	}
	if(c == CYAN) {
		r = 0.0; g = 1.0; b = 1.0;
	}
}

void Graphic::initialise_couleur_bis(unsigned int c, double& r, double& g,
double& b) {
	if(c == ROUGE) {
		r = 1.0; g = 0.5, b = 0.5;
	}
	if(c == GREEN) {
		r = 0.5; g = 1.0; b = 0.5;
	}
	if(c == BLUE) {
		r = 0.5; g = 0.5; b = 1.0;
	}
	if(c == YELLOW) {
		r = 1.0; g = 1.0; b = 1.0;
	}
	if(c == MAGENTA) {
		r = 1.0; g = 0.5; b = 1.0;
	}
	if(c == CYAN) {
		r = 0.5; g = 1.0; b = 1.0;
	}
}


void Graphic::draw_grille() {
	(*ptcr)->set_line_width(1.0);
	(*ptcr)->set_source_rgb(0.0, 0.0, 0.0);
	(*ptcr)->move_to(0.0,0.0);
	(*ptcr)->line_to(0.0, g_max-1);
	(*ptcr)->line_to(g_max-1 ,g_max-1);
	(*ptcr)->line_to(g_max-1,0.0);
	(*ptcr)->line_to(0.0, 0.0);
	(*ptcr)->fill_preserve();
	(*ptcr)->stroke();
	(*ptcr)->set_line_width(1.0);
	(*ptcr)->set_source_rgb(1.0, 1.0, 1.0);
	(*ptcr)->move_to(0.0,0.0);
	(*ptcr)->line_to(0.0, g_max-1);
	(*ptcr)->line_to(g_max-1 ,g_max-1);
	(*ptcr)->line_to(g_max-1 ,0.0);
	(*ptcr)->line_to(0.0, 0.0);
	(*ptcr)->stroke();
	for(unsigned int i(0); i <= g_max; ++i) { 
	(*ptcr)->set_line_width(0.1);
	(*ptcr)->set_source_rgb(0.6, 0.6, 0.6);
	(*ptcr)->move_to(i-0.5, -0.5);
	(*ptcr)->line_to(i-0.5, g_max-0.5);
	(*ptcr)->stroke();
	}
	for(unsigned int i(0); i <= g_max; ++i) { 
	(*ptcr)->set_line_width(0.1);
	(*ptcr)->set_source_rgb(0.6, 0.6, 0.6);
	(*ptcr)->move_to(-0.5, i-0.5);
	(*ptcr)->line_to(g_max-0.5,i-0.5);
	(*ptcr)->stroke();
	}
}

void Graphic::draw_carre_vide(unsigned int x, unsigned int y, unsigned int longeur,
unsigned int c) {
	double r, g, b;
	initialise_couleur(c, r, g, b);
	(*ptcr)->set_line_width(0.4);
	(*ptcr)->set_source_rgb(r, g, b);
	(*ptcr)->move_to(x,y);
	(*ptcr)->line_to(x+longeur-1, y);
	(*ptcr)->line_to(x+longeur-1,y + longeur-1);
	(*ptcr)->line_to(x,y+longeur-1);
	(*ptcr)->line_to(x,y);
	(*ptcr)->stroke();
}

void Graphic::draw_carre_losange(unsigned int x, unsigned int y, unsigned int longeur) {
	(*ptcr)->set_line_width(0.1);
	(*ptcr)->set_source_rgb(1.0, 1.0, 1.0);
	(*ptcr)->move_to(x-0.4, y);
	(*ptcr)->line_to(x, y+0.4);
	(*ptcr)->line_to(x+0.4,y);
	(*ptcr)->line_to(x,y-0.4);
	(*ptcr)->line_to(x-0.4, y);
	(*ptcr)->fill_preserve();
	(*ptcr)->stroke();
}

void Graphic::draw_carre_uniforme(unsigned int x, unsigned int y, unsigned int longeur, 
unsigned int c) {
	double r, g, b;
	initialise_couleur(c, r, g, b);
	(*ptcr)->set_line_width(1.0);
	(*ptcr)->set_source_rgb(r, g, b);
	(*ptcr)->move_to(x,y-0.5);
	(*ptcr)->line_to(x, y+longeur-1);
	(*ptcr)->line_to(x+longeur-1,y+longeur-1);
	(*ptcr)->line_to(x+longeur-1,y);
	(*ptcr)->line_to(x-0.5,y);
	(*ptcr)->fill_preserve();
	(*ptcr)->stroke();
}
	
void Graphic::draw_carre_diagonale(unsigned int x, unsigned int y, unsigned int longeur,
unsigned int c) {
	double r, g ,b;
	double r_bis, g_bis, b_bis; 
	initialise_couleur(c, r, g, b);
	initialise_couleur_bis(c, r_bis, g_bis, b_bis);
	(*ptcr)->set_line_width(1.0);
	for(size_t i(0); i < longeur; ++i) {
		for(size_t j(0); j<longeur; ++j) {
			if(i % 2 ==0 and j % 2==0) {
				(*ptcr)->set_source_rgb(r, g, b);
				(*ptcr)->move_to(x+i-0.5,y+j);
				(*ptcr)->line_to(x+i+0.5, y+j);
				(*ptcr)->stroke();
			} else if (i % 2 != 0 and j% 2 != 0) {
				(*ptcr)->set_source_rgb(r, g, b);
				(*ptcr)->move_to(x+i-0.5,y+j);
				(*ptcr)->line_to(x+i+0.5, y+j);
				(*ptcr)->stroke();
			} else {
				
				(*ptcr)->set_source_rgb(r_bis, g_bis, b_bis);
				(*ptcr)->move_to(x+i-0.5,y+j);
				(*ptcr)->line_to(x+i+0.5, y+j);
				(*ptcr)->stroke();
			}
		}
	}	
}
	
void Graphic::draw_carre_grille(unsigned int x, unsigned int y, unsigned int longeur,
unsigned int c) {
	double r, g ,b;
	double r_bis, g_bis, b_bis; 
	initialise_couleur(c, r, g, b);
	initialise_couleur_bis(c, r_bis, g_bis, b_bis);
	(*ptcr)->set_line_width(1.0);
	for(size_t i(0); i < longeur; ++i) {
		for(size_t j(0); j<longeur; ++j) {
			if ( i==longeur/2 or j==longeur/2) {
				(*ptcr)->set_source_rgb(r, g, b);
				(*ptcr)->move_to(x+i-0.5,y+j);
				(*ptcr)->line_to(x+i+0.5, y+j);
				(*ptcr)->stroke();
			} else {
				(*ptcr)->set_source_rgb(r_bis, g_bis, b_bis);
				(*ptcr)->move_to(x+i-0.5,y+j);
				(*ptcr)->line_to(x+i+0.5, y+j);
				(*ptcr)->stroke();
			}
		}
	}
}
