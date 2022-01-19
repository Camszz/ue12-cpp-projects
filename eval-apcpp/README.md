main program :
    - used to either solve the equation or test the different methods implemented;
    - lets you choose both the temporal and the spatial step. Be careful to keep DeltaX^2 < DeltaT !!;
    - You can create a random D vector, but only the Euler explicit and the Jacobi methods can then solve your system;
    - You can choose to save your settings (dt, dx, method used) and the execution time needed in the "performance.txt file". You already have a few results there (with a non-random D vector)
    - You can choose the filename of the file your results will be saved in

trace_data :
    - start the program in an iPython window to draw your results (you have to change the filename in the program). Results will be ploted with X as xaxis, Time as yaxis, the color being the temperature at time T, position X.
    (- you can choose the axis' graduation precision)

trace_chrono :
    - can plot the results of a .txt file with the format of "performance.txt", with datas grouped by method. 
    - Example : you have results for deltaX = cst and deltaT changing. You want to check the relation between deltaT and the resolution time. Export the useful datas from "performance.txt" in another .txt file. Set the right filename in "trace_chrono.py", start the program