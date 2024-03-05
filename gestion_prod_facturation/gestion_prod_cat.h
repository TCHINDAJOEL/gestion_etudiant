#if !defined(__gestion_prod_cat__h)
#define __gestion_prod_cat__h

/*-------------------------------------------*/
//defintion des structure

struct categorie
	{
		char codeCat[10];
		char nomCat [10];
	};
	typedef struct categorie categorie ;

	struct produit
	{
		char codeP[10];
		char nomP[10];
		int prixP;
		int stockP;
		int seuilP;
	    char codeCat[10];
	};typedef struct produit produit;

struct elementfacture
{
	char code[10];
	char nom[10];
	int  prixP;
	int quantite;
};typedef struct elementfacture elementfacture;

struct client
{
	char numClient[10];
	char name[20];
	char POBOX[10];
}; typedef struct client client;
	
/*------------------------------------------*/
// definition des prototypes des fonctions

void creationProd();
void creationCat();
void affichageProduit(produit prod);
void affichagecCategorie(categorie cat);
void lectureProd();
void lectureCat();
void rechercheProdCat();
void modifProd();
void deleteProd();
void deleteCat();
//void facturation();
void menu();
void gestion();
void manager();

#endif