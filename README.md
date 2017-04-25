# Neutrino portal dark matter model Code files

## This repository contains the relevant files for the published article ["A realistic model for dark matter 
interactions in the neutrino portal paradigm"](https://link.springer.com/article/10.1007%2FJHEP05%282016%29171), authors: V. Gonzalez, J. Illana, J. Wudka.

We discuss a simple extension of the Standard Model (SM) that provides an explicit realization of the dark-matter (DM) 
neutrino-portal paradigm. The dark sector is composed of a scalar $\Phi$ and a Dirac fermion $\Psi$, with the latter assumed to be 
lighter than the former. These particles interact with the SM through the exchange of a set of heavy Dirac fermion mediators 
that are neutral under all local SM symmetries, and also under the dark-sector symmetry that stabilizes the $\Psi$ against decay. 
We show that this model can accommodate all experimental and observational constraints provided the DM mass is below $\sim35$ GeV 
or is in a resonant region of the Higgs or Z boson. We also show that if the dark scalar and dark fermion are almost degenerate
in mass, heavier DM fermions are not excluded. We note that in this scenario DM annihilation in the cores of astrophysical 
objects and the galactic halo produces a monochromatic neutrino beam of energy $m_\Psi$, which provides a clear signature for this 
paradigm. Other experimental signatures are also discussed.

For the generl public: We propose two hypothetical species of dark particles, one which is abundant and one which is no longer abundant,
that we add to the standard model that describes the
subatomic particle interactions. We add it in such a way that the model is consistent with all the known symmetries realized
in nature (or forces). We then test this model against all possible observations, from detectors on Earth (such as Lux), to 
detectors on space (such as the FermiLat telescope and Planck). The model is plausible within experimental constraints, provided
the dark matter mass is relatively light (as compared with the Higgs boson for example) or the dark sector is almost degenerate
(when the dark particles have almost the same mass). 

### Files breakdown for the mechanistic analysis

|Filename|Description|
|--------|-----------|
|mainObs.c|Main program to compute all the relevant observables using micrOmegas package lib, numerical solutions|
|vannia2Cprogram.bash|Code to submit into cluster|
|DataOmfine.dat|Synthesized data|
|DMObervables...|Process data and compare with semi-analytic solutions and experiments|
|(xenon/lux/icecube/fermilat/upmuonfluxSK).m|Coordinate transformation of plots from published articles of experiments|
|DirectIndirectwithlux16.nb|Update on experimental constraints vs model|
|Model Implementation| Model implementation with feynrules in micrOmegas|
|figs| All the plots|
|art%3A10.1007%2FJHEP05%282016%29171.pdf|Published article|

