#include<stdio.h> //librarie folosita pt citire si scriere
#include<stdlib.h> //librarie folosita pentru alocarea/dezalocarea pointerilor
#include<math.h> //librarie folosita pentru diverse functii matematice


int suma(int x, int y) {
	return x + y;
}

void fct1(int& x) {
	x = 100;
}

void fct2(int& x) {
	x = 200;
}

void fct3(int& x) {
	x = 300;
}


//metoda bisectiei
//Sa se rezolve ecuatiile 1,2,3 prin metoda bisectiei

double ecuatie1(double x) {
	return 3 * pow(x, 3) - 2 * pow(x, 2) + 10 * x + 30;
}

double ecuatie2(double x) {
	return 3 * x - 9;
}

double ecuatie3(double x) {
	return 3 * pow(x, 2) - 3 * x - 1;
}

void metodaBisectiei(double A, double B, int N,
	double(*ptr_ecuatie)(double), double epsilon,
	double& solutie, int& cod) {//se pune "&" pentru ca variabilele cod si solutie se modifica in acest bloc si vrem sa primim valorile modificate si in main()

	//A,B - capetele intervalului in care se cauta radacina unica

	//N-numarul maxim de pasi de cautare(daca nu gasesti radicina in 1000 pasi te opresti...nu cauti la nesfarsit)

	//double(*ptr_ecuatie)(double) - pointer la functie -> folosita pentru a transmite mai departe din main() ecuatiile de mai sus (1,2,3)
	//daca va uitati atent pointerul la functie are acelasi format ca antetul functiilor de mai sus.

	//epsilon - eroarea acceptata - o variabila cat mai mica : 0.00001 

	//solutie - se va salva in variabila solutie valoarea radacinei
	//cod - poate fi 0 sau 1 ...-> 1 daca s-a gasit radacina, 0 altfel.

	solutie = cod = 0;

	if (ptr_ecuatie(A) == 0) { solutie = A; cod = 1; return; } //aici se verifica daca partea inferioara a intervalului este radacina ecuatiei
	if (ptr_ecuatie(B) == 0) { solutie = B; cod = 1; return; } //aici se verifica daca partea superioara a intervalului este radacina ecuatiei
	if (ptr_ecuatie(A) * ptr_ecuatie(B) > 0) {
		printf("Nu s-a gasit nicio radacina sau s-au gasit prea multe\n"); //aici e clar ce se intampla sper...
		cod = 0; return;
	}
	while (N > 0 && cod == 0) {///se itereaza in maxim N pasi sau pana cand se gaseste radacina
		solutie = (A + B) / 2; //ne pozitionam la mijlocul intervalului [A,B]

		if (ptr_ecuatie(solutie) == 0) { //daca valoarea de la mijlocul intervalului [A,B] este radacina atunci am gasit solutia.
			cod = 1; continue;
		}

		if (ptr_ecuatie(A) * ptr_ecuatie(solutie) < 0) {//daca nu s a gasit radacina mai sus atunci trebuie sa cautam alt interval
			B = solutie;//in cazul asta noul interval de cautare va fi [A,solutie] - (unde solutie era (A+B)/2)
		}
		else {
			A = solutie;//in cazul asta noul interval de cautare va fi [solutie, B] - (unde solutie era (A+B)/2)
		}

		if (B - A <= epsilon) {//se accepta o radacina x in care f(x) sa tinda catre 0......
			cod = 1;
		}

		N--;//se trece la urmatorul pas. daca nu se gaseste solutia in N pasi atunci codul ramane 0;
	}


}

void main() {
	//un bit este valoarea 0 sau 1
	//1 byte - 8 biti
	int x = 10; //var. intreaga - 4 bytes
	float y = 11.3; //var. reala - 4 bytes
	double z = 99.2; //var. reala  - 8 bytes
	char w = 'c'; //var. caracter - 1 byte

	char sir[6] = { 'R','a','r','e','s','\0' }; //un sir de caractere

	const int aa = 200;//variabila constanta intreaga. nu mai poate fi modificata.

	//%d = format de afisare pentru int
	//%lf = format de afisare pentru double
	//%f = format de afisare pentru float
	//%c = format de afisare pentru un caracter
	//%p = format de afisare pentru pointer/adrese
	//%s = format de afisare pentru un sir de caractere
	printf("suma(3,6)=%d\n", suma(3, 6));
	printf("Acesta este un mesaj\n");
	printf("x=%d; y=%.2f; z=%.2lf; w=%c\n", x, y, z, w);
	printf("Afisare sir de caractere: %s\n", sir);

	printf("adresa lui x este:%p\n", &x);

	int var1 = 233;
	fct1(var1);
	printf("var1=%d\n", var1);


	//pointeri

	printf("\n\n---pointeri---\n\n");
	//sa presupunem ca variabila x este salvata la adresa #222
	int* pointer1 = &x; //adica variabila pointer este creata de ex la adresa #11 si are ca valoare #222 
	printf("pointer1=%p\n", pointer1);
	printf("*pointer1=%d\n", *pointer1);

	//sa presupunem ca variabila var1 este salvata la adresa #333
	pointer1 = &var1;
	printf("pointer1=%p\n", pointer1);
	printf("*pointer1=%d\n", *pointer1);

	*pointer1 = *pointer1 + 10;  //se numeste indirectare - adica se acceseaza zona de memorie #333 si se incrementeaza cu 10
	printf("*pointer1=%d\n", *pointer1);

	printf("adresa var1=%p\n", &var1);
	printf("var1=%d\n", var1);


	printf("\n\n---pointeri la functii---\n\n");
	//pointeri la functii
	int uuu = 60;
	void (*pointerLaFunctie)(int&);

	pointerLaFunctie = fct1;
	pointerLaFunctie(uuu); //e ca si cum ai executa fct1(uuu)
	printf("pointerLaFunctie a executat fct1(uuu) si se afiseaza uuu=%d\n", uuu);

	pointerLaFunctie = fct2;
	pointerLaFunctie(uuu);  //e ca si cum ai executa fct2(uuu)
	printf("pointerLaFunctie a executat fct2(uuu) si se afiseaza uuu=%d\n", uuu);

	pointerLaFunctie = fct3;
	pointerLaFunctie(uuu);  //e ca si cum ai executa fct3(uuu)
	printf("pointerLaFunctie a executat fct3(uuu) si se afiseaza uuu=%d\n", uuu);


	printf("\n\n---metoda bisectiei---\n\n");

	//metoda bisectiei
	double solutie = 0;
	int cod = 0;
	metodaBisectiei(-2, 12, 1000, ecuatie1, 0.0001, solutie, cod);
	printf("ecuatie 1: cod=%d, solutie=%.2lf\n", cod, solutie);

	metodaBisectiei(-2, 12, 1000, ecuatie2, 0.0001, solutie, cod);
	printf("ecuatie 2: cod=%d, solutie=%.2lf\n", cod, solutie);

	metodaBisectiei(-2, 12, 1000, ecuatie3, 0.0001, solutie, cod);
	printf("ecuatie 3: cod=%d, solutie=%.2lf\n", cod, solutie);
}