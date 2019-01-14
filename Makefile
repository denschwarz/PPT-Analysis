CC = g++
ROOTFLAGS = `root-config --cflags --glibs`

all: Analyse Plotter

Analyse: src/Analyse.cc include/Analyse.h
	$(CC) -g -o Analyse src/Analyse.cc include/Analyse.h $(ROOTFLAGS)

Plotter: src/Plotter.cc include/Plotter.h
	$(CC) -g -o Plotter src/Plotter.cc include/Plotter.h $(ROOTFLAGS)

clean:
	rm -f Analyse Plotter
