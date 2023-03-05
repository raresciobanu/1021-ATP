#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#pragma warning(disable:4996) //pentru a dezactiva _CRT_SECURE_NO_WARNINGS

enum CULORI
{
	ALB,
	NEGRU = 10,
	VERDE = 20,
	ROSU
};


// const int * --> ce se afla la zona de memorie catre care pointeaza pointerul este constanta.
// int * const --> var pointer este constanta (nu poti altera adresa catre care pointeaza pointerul).
//const int * const -> un pointer constant ce pointeaza catre o zona de memorie constanta

const char* transformaEnumInSirDeCaractere(CULORI culoare) {
	switch (culoare)
	{
	case ALB:
		return "alb";
	case NEGRU:
		return "negru";
	case VERDE:
		return "verde";
	case ROSU:
		return "rosu";
	default:
		return "culoarea introdusa nu a fost interpretata";
	}
}

CULORI transformaSirDeCaractereInEnum(const char* pointerSir) {
	if (strcmp(pointerSir, "alb") == 0) {
		return CULORI::ALB;
	}
	else if (strcmp(pointerSir, "negru") == 0) {
		return CULORI::NEGRU;
	}
	else if (strcmp(pointerSir, "verde") == 0) {
		return CULORI::VERDE;
	}
	else if (strcmp(pointerSir, "rosu") == 0) {
		return CULORI::ROSU;
	}
}

//104 bytes
struct client {
	char nume[100];//100 bytes
	int varsta;//4 bytes
};

//100 bytes
union user {
	int varsta; //4bytes
	char nume[100]; //100 bytes
	char gen; //1 bytes
};

struct telefon
{
	CULORI culoareTelefon;//4bytes
	char* marca;//8bytes
	double pret;//8bytes
	int anFabricatie;//4bytes
	char version;//1byte
	client proprietar;//104bytes
};

void scrieClientLaConsola(client c) {
	printf("varsta = %d\n", c.varsta);

	printf("client = %s\n\n", c.nume);
}

void citesteClientDeLaConsola(client& c) {
	printf("varsta = ");
	scanf("%d", &c.varsta);


	printf("client = ");
	getchar();// folosit pt a elibera bufferul
	gets_s(c.nume);
	//scanf("%s", c.nume); //scanf citeste pana la primul spatiu
}

void scrieClientInFisier(FILE* fisier, client c) {
	fprintf(fisier, "%d\n", c.varsta);
	fprintf(fisier, "%s\n", c.nume);

}

void citireClientDinFisier(FILE* fisier, client& c) {
	fscanf(fisier, "%d\n", &c.varsta);
	fgets(c.nume, 100, fisier);
}

void scrieTelefonLaConsola(telefon t) {
	printf("culoare telefon = %s\n", transformaEnumInSirDeCaractere(t.culoareTelefon));

	printf("marca = %s\n", t.marca);
	printf("pret = %.2lf\n", t.pret);
	printf("an fabricatie = %d\n", t.anFabricatie);
	printf("version = %c\n", t.version);

	scrieClientLaConsola(t.proprietar);
	//linia de mai sus este echivalenta cu:
	//printf("client = %s\n", t.proprietar.nume);
	//printf("varsta = %d\n\n", t.proprietar.varsta);
}

void citireTelefonDeLaConsola(telefon& t) {
	//TODO week 3
	printf("culoare telefon = ");


	printf("marca = ");

	printf("pret = ");
	scanf("%lf", &t.pret);

	printf("an fabricatie = ");
	scanf("%d", &t.anFabricatie);

	printf("version = ");
	scanf("%c", &t.version);

	citesteClientDeLaConsola(t.proprietar);
}

void main() {
	user user1;
	user1.varsta = 20;
	printf("varsta=%d\n", user1.varsta);
	user1.gen = 'M';
	printf("gen=%c\n", user1.gen);
	printf("varsta=%d\n", user1.varsta);

	printf("\n\n---scriere in fisiere---\n\n");
	// scriere in fisiere
	//w-creare fisier si scriere in el, daca exista fisierul exista se sterg toate informatiile din el
	//wb-este "w" in mod binar
	//r-citire din fisier, daca fisierul nu exista se intoarce NULL la fopen()
	//rb-este "r" in mod binar, daca fisierul nu exista se intoarce NULL la fopen()
	//a-adaugare informatii la sf fisierului, daca NU exista fisierul se face unul nou
	//ab- este "a" in mod binar
	//r+ sau rb+ - fisier deschis pentru citire si scriere/ citire si scriere in mod binar, daca fisierul nu exista se intoarce NULL la fopen()
	//w+ sau wb+ - fisier deschis pentru citire si scriere in mod binar. 
	//a+ si ab+ - fisier deschis pentru citire si adaugare la final


	FILE* fisierClienti = fopen("clienti.txt", "w");
	if (fisierClienti == NULL) {
		printf("EROARE: Nu s-a putut deschide pentru scriere fisierul clienti.txt");
		exit(1000);
	}

	client c1;
	strcpy(c1.nume, "Rares");
	c1.varsta = 20;

	client c2;
	strcpy(c2.nume, "Ana");
	c2.varsta = 21;
	client c3;
	citesteClientDeLaConsola(c3);

	printf("\n\n---scriere CLIENT la consola---\n\n");

	scrieClientLaConsola(c1);
	scrieClientLaConsola(c2);
	scrieClientLaConsola(c3);

	printf("\n\n---scrierea a 3 CLIENTI in fisier text---\n\n");

	scrieClientInFisier(fisierClienti, c1);
	scrieClientInFisier(fisierClienti, c2);
	scrieClientInFisier(fisierClienti, c3);
	fclose(fisierClienti);


	printf("\n\n---citirea a 3 CLIENTI din fisier text---\n\n");
	FILE* fisierClientiReadMode = fopen("clienti.txt", "r");
	if (fisierClientiReadMode == NULL) {
		printf("EROARE: Nu s-a putut deschide pentru citire fisierul clienti.txt");
		exit(1000);
	}

	client c4, c5, c6;
	citireClientDinFisier(fisierClientiReadMode, c4);
	citireClientDinFisier(fisierClientiReadMode, c5);
	citireClientDinFisier(fisierClientiReadMode, c6);
	fclose(fisierClientiReadMode);


	printf("\n\n---scriere CLIENT (c4,c5,c6) din fisier text la consola---\n\n");

	scrieClientLaConsola(c4);
	scrieClientLaConsola(c5);
	scrieClientLaConsola(c6);






	printf("\n\n---scriere TELEFON la consola---\n\n");
	telefon t1, t2, t3;
	t1.anFabricatie = 2020;
	t2.anFabricatie = 2021;

	t1.culoareTelefon = CULORI::NEGRU;
	t2.culoareTelefon = VERDE;

	t1.pret = 2000.99;
	t2.pret = 2599.99;

	t1.version = '6';
	t2.version = 'X';

	t1.proprietar = c1;
	t2.proprietar = c2;

	//pt a declara un sir de caractere pe stack ai face asa:
	//char aux[100]; //cand scrii asa de fapt variabila aux reprezinta adresa primului element din vector adica aux[0];
	//strcpy(aux, "ceva");

	//pt a declara un sir de caractere pe heap ai face asa:
	//1) rezervi intai spatiu in memorie
	t1.marca = (char*)malloc(strlen("Apple") + 1);//se aloca memorie pe heap pt 6 bytes (apple =  5 si +1=6 pentru \0);
	//2) copiezi informatia la acea zona de memorie
	strcpy(t1.marca, "Apple");

	t2.marca = (char*)malloc(strlen("Huawei") + 1);
	strcpy(t2.marca, "Huawei");

	scrieTelefonLaConsola(t1);
	scrieTelefonLaConsola(t2);





	printf("\n\n---scriere TELEFOANE in fisier text---\n\n");
	FILE* fisierTelefoane = fopen("telefoane.txt", "w");
	if (fisierTelefoane == NULL) {
		printf("EROARE: Nu s-a putut deschide fisierul telefoane.txt");
		exit(1000);
	}
}