set table "Exercise_14.01.pgf-plot.table"; set format "%.5f"
set samples 25; plot [x=-5:5]  f(x,y) = (y-2)**2 + (x-2)**2 - 4; set xrange [-3:3]; set yrange [-3:3]; set view 0,0; set isosample 1000,1000; set cont base; set cntrparam levels discrete 0; unset surface; splot f(x,y) 
