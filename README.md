# PPT Analysis
Framework for a search for Higgs decaying into 4 leptons.

1) Workflow

To run the analysis, first run "Analysis", then run "Plotter".
Analyse will create a root file containing histograms.
Plotter can read these histograms and create plots in the plot folder


2) rootfiles

This directory contains data, background MC and simulated Higgs signals.
All these files are preselected to have 4 leptons.
In every file there is a flat tree containing variables like px, py, pz, E of every lepton.


3) Helper Classes

The classes Particle and ReadLeptons help reading the rootfiles.
A Particle has a 4-vector and a charge. Also it can return values like pT.
ReadLeptons takes the rootfiles as input and reads the trees.
From this, it creates vectors of muons and electrons.
Every event has a vector of muons and a vector of electrons.
With GetMuons or GetElectrons you get a vector with the size of N_events that contains a vector of muons/electrons for every event.
The file Samples.h is the interface to use the rootfiled.
It defines a list of file names, you also find the correct weight for every process, the relevant channels and an hist index which defines what process a file belongs to.
