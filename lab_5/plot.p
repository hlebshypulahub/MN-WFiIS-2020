set term jpeg

set out 'wynik_lin.jpg'

set xrange [1:12]

plot 'wyniki1.dat' u 2:3 w l t 'przyblizenia wartosci wlasnych'

