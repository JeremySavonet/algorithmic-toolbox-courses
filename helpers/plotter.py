import matplotlib.pyplot as plt
import numpy as np

n = np.linspace(1, 100)

exp =  np.log( n ) / np.log( 4 )  # = [3, 4]
plt.plot(n, exp, label="log4 n")

plt.plot(n, n ** .5, label="n^.5")
plt.plot(n, n, label="n")

plt.plot(n, n * np.log2(n), label="n * (log n)")


plt.plot(n, n*n, label="n2")

plt.legend(loc='upper left')
plt.show()

#plt.plot(n, np.sqrt(n))
#plt.plot(n, n )
#plt.plot(n, n * n )
#plt.plot(n, pow(3,n))

plt.show()
