OUT = projet
CXX = g++
CXXFLAGS = -Wall -std=c++11
LINKING = `pkg-config --cflags gtkmm-3.0`
LDLIBS = `pkg-config --libs gtkmm-3.0`
OFILES = projet.o gui.o simulation.o food.o fourmiliere.o fourmis.o squarecell.o message.o error_squarecell.o graphic.o

all: $(OUT)

projet.o: projet.cc gui.h simulation.h fourmiliere.h fourmis.h food.h \
  squarecell.h constantes.h message.h error_squarecell.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

gui.o: gui.cc gui.h simulation.h fourmiliere.h fourmis.h food.h \
  squarecell.h constantes.h message.h error_squarecell.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

simulation.o: simulation.cc simulation.h fourmiliere.h fourmis.h food.h \
  squarecell.h constantes.h message.h error_squarecell.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

food.o: food.cc food.h squarecell.h constantes.h message.h \
  error_squarecell.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

fourmiliere.o: fourmiliere.cc fourmiliere.h fourmis.h food.h squarecell.h \
  constantes.h message.h error_squarecell.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

fourmis.o: fourmis.cc fourmis.h food.h squarecell.h constantes.h \
  message.h error_squarecell.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

message.o: message.cc message.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

squarecell.o: squarecell.cc squarecell.h constantes.h message.h \
  error_squarecell.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

error_squarecell.o: error_squarecell.cc error_squarecell.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

graphic.o: graphic.cc graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

$(OUT): $(OFILES)
	$(CXX) $(CXXFLAGS) $(LINKING) $(OFILES) -o $@ $(LDLIBS)

clean:
	@echo "Cleaning compilation files"
	@rm *.o $(OUT) *.cc~ *.h~
