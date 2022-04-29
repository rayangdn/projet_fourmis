#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include <gtkmm/drawingarea.h>
#include <vector>
constexpr short unsigned g_dim(7);
const short unsigned g_max(pow(2, g_dim));

struct Couleur {
	double red;
	double green;
	double blue;
};
typedef std::vector<Couleur> Ensemble_couleurs;
class Graphic {
	public :
	Graphic() {};
	~Graphic() {};
	void set_context(const Cairo::RefPtr<Cairo::Context>&);
	void draw_grille();
	void draw_carre_vide(unsigned int, unsigned int, unsigned int, Couleur);
	void draw_carre_losange(unsigned int, unsigned int,  unsigned int);
	void draw_carre_uniforme(unsigned int, unsigned int, unsigned int, Couleur);
	void draw_carre_diagonale(unsigned int, unsigned int, unsigned int, Couleur);
	void draw_carre_grille(unsigned int, unsigned int, unsigned int, Couleur);
};




#endif
