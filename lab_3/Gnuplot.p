set term jpeg size 800, 600
set xlabel 'x'
set ylabel 'v'

set out 'wykres.jpg'

plot 'zad_a.dat' u 1:2 w l lt -1 lw 2 t 'V(numeryczne)',\
 '' u 1:4 w l lt 2 lw 2 t 'V(teoretyczne)'

