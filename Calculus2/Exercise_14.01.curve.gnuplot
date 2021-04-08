set table "Exercise_14.01.curve.table"; set format "%.5f"
 f(x,y) = (y-2)**2 + (x-2)**2 - 4; set xrange [0:4]; set yrange [0:4]; set view 0,0; set isosample 1000,1000; set cont base; set cntrparam levels discrete 0; unset surface; splot f(x,y) 
