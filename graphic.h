#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include <gtkmm.h>

constexpr short unsigned g_dim(7);
const short unsigned g_max(pow(2, g_dim));

enum Couleur{WHITE, ROUGE, GREEN, BLUE, YELLOW, MAGENTA, CYAN}; 

enum Style{VIDE, LOSANGE, UNIFORME, DIAGONALE, GRILLE};

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>&);

void initialise_couleur(unsigned int, double&, double&, double&);

void initialise_couleur_bis(unsigned int, double&, double&, double&);

void graphic_draw_grille();

void graphic_draw_carre_vide(unsigned int, unsigned int, unsigned int, unsigned int);
	
void graphic_draw_carre_losange(unsigned int, unsigned int,  unsigned int, unsigned int);
	
void graphic_draw_carre_uniforme(unsigned int, unsigned int, unsigned int, unsigned int);
	
void graphic_draw_carre_diagonale(unsigned int, unsigned int, unsigned int, unsigned int);
	
void graphic_draw_carre_grille(unsigned int, unsigned int, unsigned int, unsigned int);


#endif
