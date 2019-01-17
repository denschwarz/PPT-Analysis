CC = g++
ROOTFLAGS = `root-config --cflags --glibs`

all: Analysis Plotter

Analysis: src/Analysis.cc include/Analysis.h src/ReadLeptons.cc include/ReadLeptons.h src/Particle.cc include/Particle.h include/Samples.h
	$(CC) -g -o Analyse src/Analysis.cc src/ReadLeptons.cc src/Particle.cc $(ROOTFLAGS)

Plotter: src/Plotter.cc include/Plotter.h
	$(CC) -g -o Plotter src/Plotter.cc $(ROOTFLAGS)

clean:
	rm -f Analysis Plotter
