# PPT Analysis
Framework for a search for Higgs decaying into 4 leptons.

1) Install

- Git clone somewhere
- Source thisroot.sh (/usr/local/root/bin/thisroot.sh)
- Compile with 'make'
- Run Analysis with './Analysis'
- Run Plotter with './Plotter'

2) Workflow

To run the analysis, first run "Analysis", then run "Plotter".
Analyse will create a root file containing histograms.
Plotter can read these histograms and create plots in the plot folder


3) rootfiles

This directory contains data, background MC and simulated Higgs signals.
All these files are preselected to have 4 leptons.
In every file there is a flat tree containing variables like px, py, pz, E of every lepton.


4) Helper Classes

The classes Particle and ReadLeptons help reading the rootfiles.
A Particle has a 4-vector and a charge. Also it can return values like pT, eta, phi.
ReadLeptons takes the rootfiles as input and reads the trees.
With GetMuons or GetElectrons you get a vector with the size of N_events that contains a vector of muons/electrons for every event (vector containing vectors).
The file Samples.h is the interface to use the rootfiles.
It defines a list of file names, you also find the correct weight for every process, the relevant channels and an hist index which defines what process a file belongs to.

5) Possible Tasks

- How many data events do you analyse?                           (solution: 278)
- How many data events do you see in each channel?               (solution: 117 in 2mu2el, 113 in 4mu, 48 in 4el)
- What is the highest pT of any Lepton in data?                  (solution: 243.6 GeV)
- Do you see more +1 or -1 charged leptons? What do you expect? 
- Reconstruct all Z bosons and plot the mass
- Reconstruct Higgs Boson and plot the mass
