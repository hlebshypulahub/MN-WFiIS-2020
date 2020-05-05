set term jpeg

set out 'wynik_kropki.jpg'

plot 'wyniki1.dat' u 1:3 w p lt 3 lw 2 t 'przyblizenia wartosci wlasnych'


