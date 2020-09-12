# beziercurves

Visalização de splines cubicas naturais e curvas de Bezier usando Glut e OpenGL.

É possivel perceber algumas diferenças entre os dois tipos de spline e algmas de suas propriedades.

A curva de Bezier não é interpolante (isto é, não passa por todos os pontos marcados pelo mouse) ao contrario da spline cubica.

Em compensação, a curva de Bezier nunca escapa o feixo convexo de seu poligono de controle, o que lhe torna mais simples de controlar.

Ambas produzem curvas fechadas quando o primeiro e ultimo ponto de controle são iguais.

Demonstração: https://youtu.be/-wkMQcUBip4

Controle:

Click do mouse - insere ponto

ESC, q, Q - Fecha o programa

v - Atualiza as curvas desenhadas na tela

r - limpa a tela, apagando curvas e pontos
