
#include "fourmis.h"
using namespace std;
Fourmi::Fourmi(Carre carre) : carre(carre) {}

Generator::Generator(Carre carre, unsigned int total_food) 
: Fourmi(carre), total_food(total_food) {}

Collector::Collector(Carre carre, unsigned int age, string have_food)
: Fourmi(carre), age(age), have_food(have_food) {}

Defensor::Defensor(Carre carre, unsigned int age) : Fourmi(carre), age(age) {}

Predator::Predator(Carre carre, unsigned int age) : Fourmi(carre), age(age) {}

void Fourmi::initialise_fourmi(Grid& grid) {
	initialise_carre_centre(grid, carre);
}

void Generator::test_chaque_fourmi(Grid& grid, unsigned int countF, const Carre& carre) {
	superposition_fourmi_G(grid);
	fourmis_in_house_G(countF, carre);
	initialise_fourmi(grid);
}

void Generator::superposition_fourmi_G(Grid& grid) {
	for(size_t i(carre.point.y-carre.longeur/2); i <carre.point.y + carre.longeur/2+1 ; ++i) {
		for(size_t j(carre.point.x-carre.longeur/2); j < carre.point.x + carre.longeur/2+1; ++j) {
			if(grid[grid.size()-1-i][j] == true) {
				cout << message::generator_overlap( carre.point.x, carre.point.y,j,i );
				exit(EXIT_FAILURE);
			}
		}
	}
	
}

void Generator::fourmis_in_house_G(int countF, const Carre& autre_carre) {
		if(((carre.point.x-carre.longeur/2) <= (autre_carre.point.x)) or
		((carre.point.y-carre.longeur/2) <= (autre_carre.point.y)) or
		((carre.point.x+carre.longeur/2+1) >= (autre_carre.point.x + autre_carre.longeur)) or
		((carre.point.y+carre.longeur/2+1) >= (autre_carre.point.y + autre_carre.longeur))) {
			cout << message::generator_not_within_home(carre.point.x, carre.point.y, countF);
			exit(EXIT_FAILURE); 
		}
}

void Collector::test_chaque_fourmi(Grid& grid, unsigned int countF,const Carre& autre_carre) {
	superposition_fourmi_C(grid);
	initialise_fourmi(grid);
}

void Collector::superposition_fourmi_C(Grid& grid) {
	for(size_t i(carre.point.y-carre.longeur/2); i <carre.point.y + carre.longeur/2+1 ; ++i) {
		for(size_t j(carre.point.x-carre.longeur/2); j < carre.point.x + carre.longeur/2+1; ++j) {
			if(grid[grid.size()-1-i][j] == true) {
				cout << message::collector_overlap( carre.point.x, carre.point.y, j,i );
				exit(EXIT_FAILURE);
			}
		}
	}
}

void Defensor::test_chaque_fourmi(Grid& grid, unsigned int countF, const Carre& autre_carre) {
	superposition_fourmi_D(grid);
	fourmis_in_house_D(countF, carre);
	initialise_fourmi(grid);
}

void Defensor::superposition_fourmi_D(Grid& grid) {
	for(size_t i(carre.point.y-carre.longeur/2); i <carre.point.y + carre.longeur/2+1 ; ++i) {
		for(size_t j(carre.point.x-carre.longeur/2); j < carre.point.x + carre.longeur/2+1; ++j) {
			if(grid[grid.size()-1-i][j] == true) {
				cout << message::defensor_overlap( carre.point.x, carre.point.y,j, i );
				exit(EXIT_FAILURE);
			}
		}
	}
}

void Defensor::fourmis_in_house_D(int count, const Carre& autre_carre) {
	if(((carre.point.x-carre.longeur/2) <= (autre_carre.point.x)) or
		((carre.point.y-carre.longeur/2) <= (autre_carre.point.y)) or
		((carre.point.x+carre.longeur/2+1) >= (autre_carre.point.x + autre_carre.longeur)) or
		((carre.point.y+carre.longeur/2+1) >= (autre_carre.point.y + autre_carre.longeur))) {
			cout << message::defensor_not_within_home(carre.point.x, carre.point.y, count-1);
			exit(EXIT_FAILURE); 
		}
}

void Predator::test_chaque_fourmi(Grid& grid, unsigned int countF, const Carre& autre_carre) {
	superposition_fourmi_P(grid);
	initialise_fourmi(grid);
}

void Predator::superposition_fourmi_P(Grid& grid) {
	if(test_superposition(grid, carre)) {
		cout << message::predator_overlap(carre.point.x, carre.point.y);
		exit(EXIT_FAILURE);
	}
}

unsigned int decodage_line_fourmis(string line, Grid& grid, unsigned int nbC, unsigned int nbD,
unsigned int nbP) {
	istringstream data(line);
	
	enum Etat_lecture{FRMI, COLLECT, DEFNS, PREDAT, SORTIE};
	static int etat(FRMI);
	static unsigned int countC(0), countD(0), countP(0);
	unsigned int x, y, age;
	
	string have_food;
	Carre carre{0, {0,0}};
	switch(etat) {
		case FRMI :
			if(nbC!=0) {
				etat=COLLECT ;
				break;
			}
			if(nbD!=0) {
				etat=DEFNS;
				break;
			}
			if(nbP!=0) {
				etat=PREDAT;
				break;
			}
			break;
		 
		case COLLECT :
			data >> x >> y >> age >> have_food; 
			carre={sizeC, {x, y}};
			test_validation_carre(grid, carre);
			//fourmiliere.ajouter_fourmis(new Collector(carre, age, have_food);
			cout << "Collector " << countC << " : " <<  x << " " << y << " " << age << " " << have_food << endl;
			++countC;
			if(countC == nbC) {
				countC=0;
				etat = DEFNS;
			}
	
		break;
		
		case DEFNS:
			data >> x >> y >> age;
			carre={sizeD, {x, y}}; 
			test_validation_carre(grid, carre);
			++countD;
			cout << "Defensor " << countD << " : " <<  x << " " << y << " " << age << endl;
			if(countD == nbD) {
				countD=0;
				etat = PREDAT;
			}
		
		break;

		case PREDAT:
			data >> x >> y >> age; 
			++countP;
			carre={sizeP, {x, y}};
			test_validation_carre(grid, carre);
			cout << "Prédateur " << countP << " : " <<  x << " " << y << " " << age << endl;
			if(countP == nbP) {
				countP=0;
				etat = FRMI;
			}
			break;
			
		default : exit(0);
	}
	return etat;
}









