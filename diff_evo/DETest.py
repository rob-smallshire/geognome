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
class PolynomialSolver(DESolver.DESolver):

    def __init__(self, dim, pop):
        DESolver.DESolver.__init__(self, dim, pop) # superclass
        self.count = 0
        self.testGenerations = 20
        self.cutoffEnergy = 0.0


    def setCutoffEnergy(self, energy):
        self.cutoffEnergy = energy

    
    def EnergyFunction(self, trial, bAtSolution):

        print "Trial:", str(trial)
        
        M=60
        x=-1.0
        dx=M * 1.0 # promote to double
        result=0.0

        dx = 2.0 / dx
        for i in range(M+1):
            px = trial[0]
            for j in range(1, self.nDim):
                px = x*px + trial[j]

            if px<-1 or px>1:
                result += (1 - px) * (1 - px)

            x += dx

        px = trial[0]
        for j in range(1, self.nDim):
            px = 1.2*px + trial[j]

        px = px - 72.661
        if px<0:
            result += px * px

        px = trial[0]
        for j in range(1, self.nDim):
            px = -1.2*px + trial[j]

        px = px - 72.661
        
        if px<0:
            result+=px*px

        self.count += 1
        # self.count is per evaluation, self.count % nPop is per self.generation
        if (self.count-1)%self.nPop == 0:
            self.generation = self.count / self.nPop
            print self.count, self.nPop, self.count / self.nPop, self.Energy()

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



N_DIM = 9
N_POP = N_DIM*10
MAX_GENERATIONS = N_DIM*N_POP

def main():
    min = [None] * N_DIM
    max = [None] * N_DIM

    solver = PolynomialSolver(N_DIM, N_POP)

    for i in range(N_DIM):
        max[i] =  100.0
        min[i] = -100.0

    solver.Setup(min,max,stBest1Exp,0.9,1.0)

    solver.setCutoffEnergy(0.005)

    print "Calculating...\n"
    solver.Solve(MAX_GENERATIONS)

    solution = solver.Solution()

    print "\n\nBest Coefficients:"
    for i in range(N_DIM):
        print "[" + str(i) + "]: " + str(solution[i])



if __name__ == '__main__':
    main()