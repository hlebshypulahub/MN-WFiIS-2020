set term jpeg
set xlabel 'x'
set ylabel 'u(x)'

set out 'a0.jpg'

plot 	'a0.dat' u 1:2 w l t 'u 1:2',\
		'a0.dat' u 1:3 w l t 'u 1:3',\
		'a0.dat' u 1:4 w l t 'u 1:4',\
		'a0.dat' u 1:5 w l t 'u 1:5',\
		'a0.dat' u 1:6 w l t 'u 1:6',\
		'a0.dat' u 1:7 w l t 'u 1:7',\

set out 'a100.jpg'

plot 	'a100.dat' u 1:2 w l t 'u 1:2',\
		'a100.dat' u 1:3 w l t 'u 1:3',\
		'a100.dat' u 1:4 w l t 'u 1:4',\
		'a100.dat' u 1:5 w l t 'u 1:5',\
		'a100.dat' u 1:6 w l t 'u 1:6',\
		'a100.dat' u 1:7 w l t 'u 1:7',\
		

