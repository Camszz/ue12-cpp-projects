from cProfile import label
import matplotlib.pyplot as plt
import pandas as pd 
import numpy as np
import os

i=0
filename ='euler_exp-aleatoire-1.txt'
echellex, echelley = 1/5, 1/10

if (os.getcwd()[-4:] != 'data') :
    os.chdir('data')
fichier = open(filename, 'r')
lignes = fichier.readlines()

N = int(lignes[0])
Nt = int(lignes[1])
tfinal = float(lignes[2])
X = np.array([k/(N-1) for k in range(N)])
T = np.array([k/(Nt-1)*tfinal for k in range(Nt)])

df = pd.read_csv(filename, skiprows = 3, names = [k/(N-1) for k in range(N)])
Tmax = np.max(df.abs().max())

fichier.close()

plt.pcolor(df)

plt.xticks(np.arange(0, N+1, step=echellex*N))
xlab = np.array(plt.xticks()[0], dtype = np.double)
plt.xticks(np.arange(0, N+1, step=echellex*N), labels=xlab/N)
plt.yticks(np.arange(0, Nt+1, step=echelley*Nt))
ylab = np.array(plt.yticks()[0], dtype = np.double)
plt.yticks(np.arange(0, Nt+1, step=echelley*Nt), labels=tfinal*ylab/Nt)
plt.xlabel('X')
plt.ylabel('temps (s)')

plt.colorbar()
plt.show()