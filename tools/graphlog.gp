#!/usr/bin/gnuplot --persist

# Requires a text file named "epoch-log.txt" in the log directory

set term png size 2000, 400
set output "./images/log.png"

# Left Y axis gets scaled to the max survivors.
# Right Y axis gets scaled to 0..255.
#   1:2 Survivors 0..N        => 0..N
#   1:3 Genome length 0..50   => 0..255
#   1:4 Diversity 0..0.7      => 0..255
#   1:5 Anxiety 0..255        => 0..255

set mxtics
set ytics autofreq nomirror tc lt 2
set yrange [ 0:1000 ]
set y2range [ 0:1000 ]
set y2tics autofreq nomirror tc lt 1
set grid
set key lmargin

ScaleSurvivors(s) = s
ScaleGenomeLength(y)= y*2
ScaleDiversity(d)= d/1000
#ScaleMurders(m) = m

plot "./logs/epoch-log.txt" \
       using 1:(ScaleSurvivors($2)) with lines lw 2 linecolor 2 title "Survivors", \
    "" using 1:(ScaleDiversity($8)) with lines lw 2 linecolor 1 title "Total energy" axes x1y2

