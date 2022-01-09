import matplotlib.pyplot as plt
import pandas as pd 
import numpy as np

i=0
fichier = open("data.txt", 'r')
lignes = fichier.readlines()

N = int(lignes[0])
Nt = int(lignes[1])
tfinal = float(lignes[2])
X = np.array([k/(N-1) for k in range(N)])
T = np.array([k/(Nt-1)*tfinal for k in range(Nt)])

df = pd.read_csv("data.txt", skiprows = 3, names = [k/(N-1) for k in range(N)])
Tmax = np.max(df.abs().max())

plt.pcolor(df)
plt.yticks(np.arange(0.5, len(df.index), 1), df.index)
plt.xticks(np.arange(0.5, len(df.columns), 1), df.columns)
plt.show()