CC = g++
ROOTFLAGS = `root-config --cflags --glibs`

all: Analysis Plot

Analysis: src/Analysis.cc include/Analysis.h src/ReadLeptons.cc include/ReadLeptons.h src/Particle.cc include/Particle.h include/Samples.h
	$(CC) -g -o Analysis src/Analysis.cc src/ReadLeptons.cc src/Particle.cc $(ROOTFLAGS)

Plot: src/Plot.cc include/Plot.h src/Plotter.cc include/Plotter.h
	$(CC) -g -o Plot src/Plot.cc src/Plotter.cc $(ROOTFLAGS)

clean:
	rm -f Analysis Plot
