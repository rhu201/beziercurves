# beziercurves

Visalização de splines cubicas naturais e curvas de Bezier usando Glut e OpenGL.<br>
É possivel perceber algumas diferenças entre os dois tipos de spline e algmas de suas propriedades.<br>
A curva de Bezier não é interpolante (isto é, não passa por todos os pontos marcados pelo mouse) ao contrario da spline cubica.<br>
Em compensação, a curva de Bezier nunca escapa o feixo convexo de seu poligono de controle, o que lhe torna mais simples de controlar.<br>
Ambas produzem curvas fechadas quando o primeiro e ultimo ponto de controle são iguais.<br>
Demonstração: https://youtu.be/-wkMQcUBip4

Controle:<br>
Click do mouse - insere ponto<br>
ESC, q, Q - Fecha o programa<br>
v - Atualiza as curvas desenhadas na tela <br>
r - limpa a tela, apagando curvas e pontos
