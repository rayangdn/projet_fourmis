#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include <gtkmm.h>

constexpr short unsigned g_dim(7);
const short unsigned g_max(pow(2, g_dim));

enum Couleur{RIEN, ROUGE, GREEN, BLUE, YELLOW, MAGENTA, CYAN}; 

class Graphic {
	public :
	Graphic() {};
	~Graphic() {};
	void set_context(const Cairo::RefPtr<Cairo::Context>&);
	void initialise_couleur(unsigned int, double&, double&, double&);
	void initialise_couleur_bis(unsigned int, double&, double&, double&);
	void draw_grille();
	void draw_carre_vide(unsigned int, unsigned int, unsigned int, unsigned int);
	void draw_carre_losange(unsigned int, unsigned int,  unsigned int);
	void draw_carre_uniforme(unsigned int, unsigned int, unsigned int, unsigned int);
	void draw_carre_diagonale(unsigned int, unsigned int, unsigned int, unsigned int);
	void draw_carre_grille(unsigned int, unsigned int, unsigned int, unsigned int);
};

#endif
