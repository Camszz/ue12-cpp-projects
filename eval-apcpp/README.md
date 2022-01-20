## Main program :
    - Used to either solve the equation or test the different methods implemented;
    - Lets you choose both the temporal and the spatial step. Be careful to keep DeltaX^2 < DeltaT !!;
    - You can create a random D vector, but only the Euler explicit and the Jacobi methods can then solve your system;
    - You can choose to save your settings (dt, dx, method used) and the execution time needed in the "performance.txt file". You already have a few results there (with a non-random D vector)
    - You can choose the filename of the file your results will be saved in

## Trace_data :
    - Start the program in an iPython window to draw your results (you have to change the filename in the program). Results will be ploted with X as xaxis, Time as yaxis, the color being the temperature at time T, position X.
    (- You can choose the axis' graduation precision)

## Trace_chrono :
    - Can plot the results of a .txt file with the format of "performance.txt", with datas grouped by method. 
    - Example : you have results for deltaX = cst and deltaT changing. You want to check the relation between deltaT and the resolution time. Export the useful datas from "performance.txt" in another .txt file. Set the right filename in "trace_chrono.py", start the program

## Fichier performance.txt
Les fichiers en version 1 (qui finissent par -1.txt) sont relatifs à la méthodes vector(vector(double)) et ceux en version 2-3-4 à la version vector(double) avec tous les passages en référence. Elles démontrent une optimisation du temps de calcul, notamment pour la méthode des matrices creuses (passage de 23s à 1.8s de temps résolution).
Le fichier performance contient différentes données du temps d'exécution en fonction de certains paramètres (méthode utilisée, pas de temps, pas spatial et version du programme). Le programme "trace_chrono" n'est malheureusement pas fini actuellement. Je n'ai pas eu le temps de le corriger après avoir changé la méthode de représentaiton des matrices.