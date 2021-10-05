import numpy as np
import matplotlib.pyplot as plt

charity = 1

pareto_distribution = [ 1000.0/i for i in range(1,101) ]
randomly_derived_distribution = [ 1 for i in range(0,101) ]

fig = plt.figure()
for i in range(0,100):
    # print(randomly_derived_distribution)
    randomly_derived_distribution = [ abs(np.random.normal(i, i/2)) + charity for i in randomly_derived_distribution ]
    randomly_derived_distribution.sort(reverse = True)
    plt.clf()
    plt.plot(randomly_derived_distribution)
    plt.plot(pareto_distribution)
    plt.ylabel('some numbers')
    plt.legend(["random", "pareto"])
    plt.pause(0.5)

plt.show()
