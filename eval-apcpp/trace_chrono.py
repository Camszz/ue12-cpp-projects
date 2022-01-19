from cProfile import label
import pandas as pd
import matplotlib.pyplot as plt
import os

if (os.getcwd()[-4:] != 'data') :
    os.chdir('data')

filename = 'performance.txt'
df = pd.read_csv(filename, names = ['Méthode', 'delta X', 'delta T', 'temps exécution'], sep = ';')

df.set_index('delta T', inplace = True)
df.where(df['delta X'] == 0.02).groupby('Méthode')['temps exécution'].plot(legend = True)
plt.show()

df = pd.read_csv(filename, names = ['Méthode', 'delta X', 'delta T', 'temps exécution'], sep = ';')

df.set_index('delta X', inplace = True)
df.where(df['delta T'] == 0.02).groupby('Méthode')['temps exécution'].plot(legend = True)