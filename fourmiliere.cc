

#include "fourmiliere.h"
using namespace std;


Fourmiliere::Fourmiliere(Carre carre, unsigned int nbC, unsigned int nbD, unsigned int nbP)
: carre(carre),  nbC(nbC), nbD(nbD), nbP(nbP) {}

void Fourmiliere::test_superposition_fourmiliere(const Fourmiliere& autre_fourmiliere,
unsigned int countF, unsigned int i) {
	if(test_superposition_2_carres(carre, autre_fourmiliere.carre)) {
		cout << message::homes_overlap(i, countF);
		exit(0);
	}
}
void decodage_line_fourmiliere(string line, Grid& grid,unsigned int total, Ensemble_fourmiliere& ensemble_fourmiliere) {
	istringstream data(line);
	
	enum Etat_lecture{FRMIL, COLLECT, DEFNS, PREDAT};
	static unsigned int etat(FRMIL);
	static unsigned int countF(0), countC(0), countD(0), countP(0), i(0);
	unsigned int x, y, side, xg, yg, total_food;
	static unsigned int nbC, nbD, nbP;
	if(etat==FRMIL) {
	data >> x >> y >> side >> xg >> yg >> total_food >> nbC >> nbD >> nbP;
	//cout << "Fourmiliere "  << countF << " : "  << x << " " << y << " " << side << " " << xg << " " << yg << " " << total_food << " " << nbC << " " << nbD << " " << nbP << endl;
	Carre carre{side, {x, y}};
	Fourmiliere fourmiliere(carre, nbC, nbD, nbP);
	test_validation_carre(grid, carre);
	for(size_t i(0); i < ensemble_fourmiliere.size() ; ++i) {
		fourmiliere.test_superposition_fourmiliere(ensemble_fourmiliere[i], countF, i);
	}
	Carre carre_generator{sizeG, {xg, yg}};
	fourmiliere.ajouter_fourmis(new Generator(carre_generator, total_food));
	fourmiliere.test_fourmis(grid, countF, i);
	++i;
	++countF;
	ensemble_fourmiliere.push_back(std::move(fourmiliere));
	countC=0; countD=0; countP=0;
	
	if(nbC!=0) {
		etat=COLLECT ;
		return;
		}
	if(nbD!=0) {
		etat=DEFNS;
		return;
		}
	if(nbP!=0) {
		etat=PREDAT;
		return;
	}
	
	
	if(countF==total) {
		return;
		}
	}
	Carre carre_collect{0,{ 0,0}};
	Collector collector(carre_collect, 0, "");
	Carre carre_defens{0, {0,0}};
	Defensor defensor(carre_defens, 0);
	Carre carre_predat{0,{0,0}};
	Predator predator(carre_predat, 0);
	switch(etat) {
		case COLLECT :
			decodage_line_fourmis(line, grid, etat, collector, defensor, predator);
			ensemble_fourmiliere[countF-1].ajouter_fourmis(new Collector(collector));
			ensemble_fourmiliere[countF-1].test_fourmis(grid, countF-1, i);
			++i;
			++countC;
			if(countC==nbC) {
				etat=DEFNS;
			}
			break;
		
		case DEFNS :
			decodage_line_fourmis(line, grid, etat, collector, defensor, predator);
			ensemble_fourmiliere[countF-1].ajouter_fourmis(new Defensor(defensor));
			ensemble_fourmiliere[countF-1].test_fourmis(grid, countF-1, i);
			++i;
			++countD;
			if(countD==nbD) {
				etat=PREDAT;
			}
			break;
		case PREDAT :
			decodage_line_fourmis(line, grid, etat, collector, defensor, predator);
			ensemble_fourmiliere[countF-1].ajouter_fourmis(new Predator(predator));
			ensemble_fourmiliere[countF-1].test_fourmis(grid, countF-1, i);
			++i;
			++countP;
			if(countP==nbP) {
				etat=FRMIL;
				i=0;
			}
			break;
		}
	
	/*if(decodage_line_fourmis(fourmiliere, line, grid, nbC, nbD, nbP)==0) { // FRMI est le nombre 0 
		etat=FRMIL;
	}*/
	
	
	
}
	
void Fourmiliere::ajouter_fourmis(Fourmi* nouveau) {
	if( nouveau!= nullptr) {
		ensemble_fourmis.push_back(unique_ptr<Fourmi>(nouveau));
	}
}


/*void Fourmiliere::test_superposition_ensemble_fourmis(const Grid& grid) {
	for(const auto& fourmi : ensemble_fourmis) {
		fourmi->test_superposition_fourmi(grid);
	}
}
*/
/*void Fourmiliere::initialise_ensemble_fourmis(Grid& grid) {
	for(const auto& fourmi : ensemble_fourmis) {
		fourmi->initialise_fourmi(grid);
	}
}*/
void Fourmiliere::test_fourmis(Grid& grid, unsigned  int countF, unsigned int i) {
	/*for(const auto& fourmi : ensemble_fourmis) {
		fourmi->test_chaque_fourmi(grid, countF, carre);
		
	}*/
	ensemble_fourmis[i]-> test_chaque_fourmi(grid, countF, carre);
}
/*
		
		If(!(carre.point.x < fourmi.carre.point.x and carre.point.y < fourmi.carre.point.y and
			carre.point.x + carre.longeur > carre.point.x + carre.longeur and
			carre.point.y + carre.longeur > carre.point.y + carre.longeur) ) {
			cout << message::generator_not_within_home(carre.point.x, carre.point.y, count);
			exit(EXIT_FAILURE); 
		}
}
*/
	/*for(int i(carre_generator.point.x); i < carre_generator.point.x + carre_generator.longeur; ++i) {
		for(int j(carre_generator.point.y); j < carre_generator.point.y + carre_generator.longeur; ++j) {
			if(grid[grid.size()-1-i][j]==true) {
				cout << message::generator_overlap( carre_generator.point.x, carre_generator.point.y,grid.size()-1-i,j );
				exit(EXIT_FAILURE);
			}
		}
	}*/


/*void Fourmiliere::test_fourmis_in_house(int count, Fourmi fourmi) {
	if(!(carre.point.x < fourmi.carre.point.x and carre.point.y < fourmi.carre.point.y and
	carre.point.x + carre.longeur > carre_generator.point.x + carre_generator.longeur and
	carre.point.y + carre.longeur > carre_generator.point.y + carre_generator.longeur) ) {
		cout << message::generator_not_within_home(carre_generator.point.x, carre_generator.point.y, count);
		exit(EXIT_FAILURE); 
	}
	
}
*/

/*void Fourmiliere::decodage_ligne(string line) {
	istringstream data(line);
	enum Etat_lecture { COLLECT, DEFNS, PREDAT, SORTIE };
	static int etat(COLLECT);
	static int count(0);
	unsigned int  x, y, age;
	string have_food;
	cout << nbC << nbD << nbP;
	while( etat!= SORTIE) {
	switch(etat) {
		case COLLECT :
			if(nbC == 0) {
				etat = DEFNS;
				break;
			}
			data >> x >> y >> age >> have_food; ++count;
			cout << "Collector " << count << " : " <<  x << " " << y << " " << age << " " << have_food << endl;
			if(count == nbC) {
				etat = DEFNS;
			}
		case DEFNS :
			count=0;
			if(nbD == 0) {
				etat = PREDAT;
				break;
			}
			data >> x >> y >> age; ++ count;
			cout << "Defensor " << count << " : " <<  x << " " << y << " " << age << endl;
			if(count == nbD) {
				etat = PREDAT;
			}
			break;
		case PREDAT :
		count=0;
		if(nbP == 0) {
			etat = SORTIE;
			break;
		}
		data >> x >> y >> age; ++count;
		cout << "Prédateur " << count << " : " <<  x << " " << y << " " << age << endl;
		if(count == nbP) {
			etat = SORTIE;
		}
		break;
		default : exit(0);
	
	}
}
	
}*/
