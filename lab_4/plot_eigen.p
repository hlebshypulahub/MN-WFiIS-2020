set term jpeg
set xlabel 'alfa'
set ylabel 'eigen value'
set yrange [0:0.25]

set out 'eigen.jpg'

plot 	'eigen.dat' u 1:2 w l t 'u 1:2',\
		'eigen.dat' u 1:3 w l t 'u 1:3',\
		'eigen.dat' u 1:4 w l t 'u 1:4',\
		'eigen.dat' u 1:5 w l t 'u 1:5',\
		'eigen.dat' u 1:6 w l t 'u 1:6',\
		'eigen.dat' u 1:7 w l t 'u 1:7',\
