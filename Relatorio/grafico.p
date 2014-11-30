plot '../rank/dados.dat' using 1:2 title "Pontos"
replot x**5-7*x**4+5*x**3-3*x**2+2*x-1 title "Funcao 5º grau"
set title "Pontos e funcao base"
replot
set key right bottom inside
replot

##############################

plot '../rank/dados.dat' using 1:2 title "Pontos"
replot x**5-7.05190*x**4+6.13233*x**3-2.98373*x**2+1.73653*x-0.99223 title "Solução 5º grau"
set title "Solucao 5º grau"
set xlabel "Resíduo: 50.69759"
replot

###############################
#Soluções com perturbações em b
###############################
replot x**5-7.68487*x**4+6.75034*x**3-3.08711*x**2+1.78203*x-1.06678 title "Solução com variaçãoem b"
set title "Solução 5º grau com 15% de variação"
set xlabel " "
replot

###############################

plot '../rank/dados.dat' using 1:2 title "Pontos"
replot x**4+6.95427*x**3-8.95480*x**2+1.25949*x-0.34728 title "Solução 4º grau"
set title "Solucao 4º grau"
set xlabel "Resíduo: 54.68442"
replot

###############################
#Soluções com perturbações em b
###############################
replot x**4+7.05937*x**3-10.16380*x**2+1.77751*x-0.27643 title "Solução com variação em b"
set title "Pontos e solução 4º grau com 15% de variação"
set xlabel ""
replot


###############################


plot '../rank/dados.dat' using 1:2 title "Pontos"
replot x**3-9.03908*x**2+5.45203*x-0.39367 title "Solução 3º grau"
set title "Solucao 3º grau"
set xlabel "Resíduo: 59.01694"
replot

###############################
#Soluções com perturbações em b
###############################
replot x**3-10.41216*x**2+6.33740*x-0.47817 title "Solução com variação em b"
set title "Pontos e solução 3º grau com 15% de variação"
set xlabel ""
replot

###############################

plot '../rank/dados.dat' using 1:2 title "Pontos"
replot x**2+5.87079*x-3.74052 title "Solução 2º grau"
set title "Solucao 2º grau"
set xlabel "Resíduo: 68.33327"
replot

###############################
#Soluções com perturbações em b
###############################

replot x**2+7.31828*x-4.36521 title "Solução com variação em b"
set title "Pontos e solução 2º grau com 15% de variação"
set xlabel ""
replot


 -----/\----- EXCLUDED -----/\-----}
