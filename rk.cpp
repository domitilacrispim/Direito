#include<bits/stdc++.h>
// x'=-cos(5t)+sen(4t)
// Integrando x': x= - 4cos(4t)-5sen(5t) + k 
// Sabe-se que x(0)=1,
// Entao 1 = - 4cos(4.0)-5sen(5.0) + k 
// Assim: k=5
// Período: 0<=t<=2 
int main (){

	// Primeiramente adota-se h=0.25

	double  x=1, x_p, t=0.25, aux; 
	
	printf("passo h=0.25\n");

	while ( t<=2){

		x_p=x+0.25*(-cos(5.0*(t-0.25))+sin(4.0*(t-0.25)));
		printf("%lf\n", x_p);
		x=x_p;
		t=t+0.25;
	}
	
	// Agora, adota-se h=0.20

	x=1; x_p; t=0.2;
	printf("passo h=0.2\n");

	while ( t<=2){

		x_p=x+0.2*(-cos(5.0*(t-0.2))+sin(4.0*(t-0.2)));
		printf("%lf\n", x_p);
		x=x_p;
		t=t+0.2;
	}
	// por 0,25 e 0,20 serem números próximos , podemos notar que os resultados
}
