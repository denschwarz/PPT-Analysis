CC = g++
ROOTFLAGS = `root-config --cflags --glibs`

all: Analyse.cc Analyse.h Plot.cc Plot.h
	$(CC) -g -o Analyse Analyse.cc Analyse.h $(ROOTFLAGS)
	$(CC) -g -o Plot Plot.cc Plot.h $(ROOTFLAGS)
