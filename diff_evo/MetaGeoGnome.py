## Differential Evolution Solver Class
## Based on algorithms developed by Dr. Rainer Storn & Kenneth Price
## Written By: Lester E. Godwin
##             PushCorp, Inc.
##             Dallas, Texas
##             972-840-0208 x102
##             godwin@pushcorp.com
## Created: 6/8/98
## Last Modified: 6/8/98
## Revision: 1.0
##
## Ported To Python From C++ July 2002
## Ported To Python By: James R. Phillips
##                      Birmingham, Alabama USA
##                      zunzun@zunzun.com

import sys
import subprocess

import DESolver
reload(DESolver) # for debugging and development

true  = 1
false = 0

stBest1Exp          = 0
stRand1Exp          = 1
stRandToBest1Exp    = 2
stBest2Exp          = 3
stRand2Exp          = 4
stBest1Bin          = 5
stRand1Bin          = 6
stRandToBest1Bin    = 7
stBest2Bin          = 8
stRand2Bin          = 9


# Polynomial fitting problem
class MetaGeoGnomeSolver(DESolver.DESolver):

    def __init__(self, dim, pop):
        DESolver.DESolver.__init__(self, dim, pop) # superclass
        self.count = 0
        self.testGenerations = 20
        self.cutoffEnergy = 0.0


    def setCutoffEnergy(self, energy):
        self.cutoffEnergy = energy

    
    def EnergyFunction(self, trial, bAtSolution):

        sys.stdout.write("Trial %d: %s " % ((self.count)%self.nPop, str(trial)))
        
        # Run GeoGnome.exe with the trial paramters as command-line arguments
        # GeoGnome will print the resulting fitness (== 1 / energy) to stdout
        # before exiting.
        
        output = subprocess.Popen(["GeoGnome.exe"] + map(str, [500.0, 180.0, 15.0] + trial), stdout=subprocess.PIPE).communicate()[0]

        result = 1.0 / float(output)

        sys.stdout.write(" = %f\n" % result)
        
        self.count += 1
        # self.count is per evaluation, self.count % nPop is per self.generation
        if (self.count-1)%self.nPop == 0:
            self.generation = self.count / self.nPop

            # we will be "done" if the energy is less than or equal to the cutoff energy (default 0.0)
            if self.Energy() <= self.cutoffEnergy:
                    bAtSolution = true

            # we will be "done" if the energy is changed by less that 10% every "self.testGenerations" generations
            if self.generation == self.testGenerations: # set initial test energy
                self.testEnergy = self.Energy()

            # test every self.testGenerations generations after the initialization above
            if self.generation > self.testGenerations and self.generation % self.testGenerations == 0:

                # if energy changes by less than 50% in "self.testGenerations" generations, stop
                deltaEnergy = self.testEnergy - self.Energy()
                if deltaEnergy < (self.testEnergy/2.0):
                    bAtSolution = true

                self.testEnergy = self.Energy()
        return result, bAtSolution



N_DIM = 2
N_POP = N_DIM*10
MAX_GENERATIONS = N_DIM*N_POP

def main():
    #       rho      theta  disp  breed  mut
    min = [ 0.0,   0.0 ]
    max = [ 1.0,   1.0 ]

    solver = MetaGeoGnomeSolver(N_DIM, N_POP)

    solver.Setup(min, max, stBest1Exp, 0.9, 1.0)

    solver.setCutoffEnergy(10.0)

    print "Calculating...\n"
    solver.Solve(MAX_GENERATIONS)

    solution = solver.Solution()

    print "\n\nBest Coefficients:"
    for i in range(N_DIM):
        print "[" + str(i) + "]: " + str(solution[i])
        
    print "with energy %f" % solver.Energy()



if __name__ == '__main__':
    main()