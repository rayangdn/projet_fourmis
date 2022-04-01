
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

void Generator::fourmis_in_house_G(unsigned int countF, const Carre& autre_carre) {
		if(((carre.point.x-carre.longeur/2) <= (autre_carre.point.x)) or
		((carre.point.y-carre.longeur/2) <= (autre_carre.point.y)) or
		((carre.point.x+carre.longeur/2+1) >= (autre_carre.point.x + autre_carre.longeur)) or
		((carre.point.y+carre.longeur/2+1) >= (autre_carre.point.y + autre_carre.longeur))) {
			cout << message::generator_not_within_home(carre.point.x, carre.point.y, countF);
			exit(EXIT_FAILURE); 
		}
}

void Collector::initialise_collect(const Carre& autre_carre, unsigned int autre_age, string autre_have_food) {
	carre.longeur = autre_carre.longeur;
	carre.point.x = autre_carre.point.x;
	carre.point.y = autre_carre.point.y;
	age = autre_age;
	have_food = autre_have_food;
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
	initialise_fourmi(grid);
}

void Defensor::initialise_defens(const Carre& autre_carre, unsigned int autre_age) {
	carre.longeur = autre_carre.longeur;
	carre.point.x = autre_carre.point.x;
	carre.point.y = autre_carre.point.y;
	age = autre_age;
	
}

void Defensor::test_chaque_fourmi(Grid& grid, unsigned int countF, const Carre& autre_carre) {
	fourmis_in_house_D(countF, autre_carre);
	superposition_fourmi_D(grid);
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

void Defensor::fourmis_in_house_D(unsigned int countF, const Carre& autre_carre) {
	if(((carre.point.x-carre.longeur/2) <= (autre_carre.point.x)) or
		((carre.point.y-carre.longeur/2) <= (autre_carre.point.y)) or
		((carre.point.x+carre.longeur/2+1) >= (autre_carre.point.x + autre_carre.longeur)) or
		((carre.point.y+carre.longeur/2+1) >= (autre_carre.point.y + autre_carre.longeur))) {
			cout << message::defensor_not_within_home(carre.point.x, carre.point.y, countF);
			exit(EXIT_FAILURE); 
		}
}

void Predator::initialise_predat(const Carre& autre_carre, unsigned int autre_age) {
	carre.longeur = autre_carre.longeur;
	carre.point.x = autre_carre.point.x;
	carre.point.y = autre_carre.point.y;
	age = autre_age;
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

void decodage_line_fourmis(string line, Grid& grid, unsigned int etat, Collector& collector,
Defensor& defensor, Predator& predator) {
	istringstream data(line);
	
	unsigned int x, y, age;
	string have_food;
	
	if(etat==1) {
		data >> x >> y >> age >> have_food;
		Carre carre{sizeC, {x, y}};
		test_validation_carre(grid, carre);
		collector.initialise_collect(carre, age, have_food);
		
		//cout << "Collector " <<" : " <<  x << " " << y << " " << age << " " << have_food << endl;
		return;
	}
	
	if(etat==2) {
		data >> x >> y >> age;
		Carre carre{sizeC, {x, y}};
		test_validation_carre(grid, carre);
		defensor.initialise_defens(carre, age);
		//cout << "Defensor " << " : " <<  x << " " << y << " " << age << endl;
		return;
	}
	if(etat==3) {
		data >> x >> y >> age;
		Carre carre{sizeC, {x, y}};
		test_validation_carre(grid, carre);
		predator.initialise_predat(carre, age);
		//cout << "Predator " <<   " : " <<  x << " " << y << " " << age << endl;
		return;
	}
}
		
		
/*void decodage_line_fourmis(string line, Grid& grid) {
	
	istringstream data(line);
	
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
			fourmiliere.ajouter_fourmis(new Collector(carre, age, have_food);
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


*/






