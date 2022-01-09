The executable built with main.cpp lets you chose both the spatial and the temporal steps. For the numeric resolution method to converge you have to chose deltaT so that deltaT > deltaX^2.

It generates a "data.txt" file where the first three raws are N, Nt and tfinal (ie. spatial step, temporal step and final time) and where the following ones represent the vector T at different times.
You can draw these T vectors heatmap w/ the "trace.py" file.

Happy coding ;)
