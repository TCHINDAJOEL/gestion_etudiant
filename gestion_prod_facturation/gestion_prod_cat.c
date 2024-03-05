#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"gestion_prod_cat.h"

/*------------------------------------------------------*/
// defintion des fonctions

void creationProd()
	{
		produit prod;
		printf("entrer le code du produit \n -->");-
		scanf("%s",&prod.codeP);
		printf("entrer le nom du produit \n -->");
		scanf("%s",&prod.nomP);
		printf("entrer le prix du produit \n -->");
		scanf("%d",&prod.prixP);
		printf("entrer le seuil du produit \n -->");
		scanf("%d",&prod.seuilP);
		printf("entrer le stock du produit \n -->");
		scanf("%d",&prod.stockP);
		printf("entrer le code de la categorie du produit \n -->");
		scanf("%s",&prod.codeCat);

		FILE *t ;
  		t = fopen("fprod.ing","a") ;
 	if(t == NULL) 
 		printf("probleme d’ouverture") ;
	else
	{ 
		fwrite(&prod,sizeof(prod),1,t) ;
  		fclose(t) ;
	} 


	}

void creationCat()
	{
		categorie cat;

		printf("entrer le code de la categorie \n -->");
		scanf("%s",&cat.codeCat);
		printf("entrer le nom de la categorie \n -->");
		scanf("%s",&cat.nomCat);

		FILE *t ;
  		t = fopen("fcate.ing","a") ;
 	if(t == NULL) 
 		printf("probleme d’ouverture") ;
	else
	{ 
		fwrite(&cat,sizeof(cat),1,t) ;
  		fclose(t) ;
	}
	}

	void affichageProduit(produit prod)
	{
		printf("le code du produit est %s \n",prod.codeP);
		printf("le nom du produit est %s \n",prod.nomP);
		printf("le prix du produit est %d \n",prod.prixP);
		printf("le stock du produit est %d \n",prod.stockP);
		printf("le seuil du produit est %d \n",prod.seuilP);
		printf("le code du produit est %s \n",prod.codeCat);
	}

	void affichageCategorie(categorie cat)
	{
		printf("le code de la categorie est %s \n",cat.codeCat);
		printf("le nom de la categorie est %s \n",cat.nomCat);
 	}


void lectureProd ()
	{
			
  			FILE *fproduit = NULL ;
  			produit prod;
 			fproduit = fopen("fprod.ing","r") ;
 			if(fproduit == NULL)
 				printf("probleme d’ouverture") ;
 			else
 			{ 	
 				printf("voici la liste des produit \n");
				printf("code \t nom \t\tprix \t stock \tseuil \tcodeCat\n");
 			while( !feof(fproduit)&&fread(&prod,sizeof(prod),1,fproduit))
    		{ 
       			printf("%s \t %s \t %d \t %d \t %d \t %s\n",prod.codeP,prod.nomP,prod.prixP,prod.stockP,prod.seuilP,prod.codeCat);
    		}
    		fclose(fproduit);
			}
			
	}

void lectureCat ()
 	{
 		categorie cat;
 		FILE *fcat ;
 		fcat = fopen("fcate.ing","r") ;
 		if(fcat == NULL)
 			printf("probleme d’ouverture") ;
 		else
 			{ 
 				printf("voici la liste des categorie \n");
				printf("code \t\t nom\n");
 				while( !feof(fcat) && fread(&cat,sizeof(cat),1,fcat) )
    				{ 				
       					printf("%s\t %s\n",cat.codeCat,cat.nomCat);
    				} 
			}
 	}

int rechercheProdCat(nomcategorie_1)
 	{
 		char nomcategorie_1[10];
 		int n = 0;
 		char code[10]; 
 		produit prod;
 		FILE *fproduit;
 		fproduit = fopen("fprod.ing","r");
 		if(fproduit == NULL)
 			printf("il y'a eu une erreur de lecture");
 		else
 		{
 			printf("entrer le code de la categorie a rechercher \n-->");
 			scanf("%s",&nomcategorie_1);
 			while(!feof(fproduit) && fread(&prod,sizeof(prod),1,fproduit))
    		{ 
    			if(strcmp(nomcategorie_1,prod.codeCat) == 0)
    			{
    				printf("le nom du produit que vous chercher est %s \n",prod.nomP);
       				n++ ;
       				return 1;	
    			}	
    		}

    		if(n == 0)
    			printf("il n'y a pas de produit ayant ce nom de categorie \n");
    		fclose(fproduit);
 		}
 		return 0;
 		
 	}

void modifProd()
{
	char choix[4];
	char choice[]="OK";
	char code[10];
	int tr = 0,newStock = 0;
	produit prod;
	produit prodtemp;
	FILE *temp;
	FILE *fproduit;

	fproduit=fopen("fprod.ing","r");
	if(fproduit == NULL)
		printf("probleme d'ouverture du fichier");
	else
	{
		temp=fopen("temp.ing","w");
		if(temp == NULL)
			printf("probleme");
		else
		{
			printf("entrer le code du produit a modifier\n -->");
			scanf("%s",&code);
			while(!feof(fproduit) && fread(&prod,sizeof(prod),1,fproduit))
			{
				prodtemp = prod;
				if(strcmp(code,prodtemp.codeP) == 0)
				{
					printf("voici les information du produit\n");
					affichageProduit(prodtemp);
					printf("entrer en majuscule OK pour modifier le stock du produit et NOT pour ne plus modifier\n");
					scanf("%s",&choix);
					if(strcmp(choix,choice) == 0)
					{
						tr = 1;
						printf("entrer la quantité du stock a ajouter dans le produit\n");
						scanf("%d",&newStock);
						prodtemp.stockP += newStock;
					}
				}
				fwrite(&prodtemp,sizeof(prodtemp),1,temp);
			}
			fclose(temp);
		}
	fclose(fproduit);
	
	remove("fprod.ing");
	rename("temp.ing","fprod.ing");
	if(tr == 1)
		printf("modification du stock realiser\n");
	else
		printf("rien n'a ete modifier \t");	
	}
}

void deleteProd()
{
	char choix[4];
	char choice[]="OK";
	char code[10];
	int tr = 0;
	produit prod;
	FILE *temp;
	FILE *fproduit;

	fproduit=fopen("fprod.ing","r");
	if(fproduit == NULL)
		printf("probleme d'ouverture du fichier");
	else
	{
		temp=fopen("temp.ing","w");
		if(temp == NULL)
			printf("probleme");
		else
		{
			printf("entrer le code du produit a supprimer\n -->");
			scanf("%s",&code);
			while(!feof(fproduit) && fread(&prod,sizeof(prod),1,fproduit))
			{
				if(strcmp(code,prod.codeP) == 0)
				{
					printf("voici les information du produit\n");
					affichageProduit(prod);
					printf("\n");
					printf("entrer en majuscule OK pour supprimer le stock du produit et NOT pour ne plus modifier\n");
					scanf("%s",&choix);
					if(strcmp(choix,choice) != 0)
					{
						fwrite(&prod,sizeof(prod),1,temp);
					}
					else
					{
						tr = 1;
					}
				}
				else
				{
					fwrite(&prod,sizeof(prod),1,temp);
				}

			}
			fclose(temp);
		}
		fclose(fproduit);
	remove("fprod.ing");
	rename("temp.ing","fprod.ing");
	if(tr == 1)
		printf("le produit a ete supprimer \n");
	else
		printf("rien n'a ete modifier");
	}
	
}

void deleteCat()
{
	char choix[4];
	char choice[]="OK";
	char code[10];
	int tr = 0;
	categorie cat;
	FILE *temp;
	FILE *fcat;

	fcat=fopen("fcate.ing","r");
	if(fcat == NULL)
		printf("probleme d'ouverture du fichier");
	else
	{
		temp=fopen("temp.ing","w");
		if(temp == NULL)
			printf("probleme");
		else
		{
			printf("entrer le code de la categorie a supprimer\n -->");
			scanf("%s",&code);
			while(!feof(fcat) && fread(&cat,sizeof(cat),1,fcat))
			{
				if(strcmp(code,cat.codeCat) == 0)
				{
					printf("voici les information de la categorie\n");
					affichageCategorie(cat);
					printf("\n");
					printf("entrer en majuscule OK pour supprimer le stock du produit et NOT pour ne plus modifier\n");
					scanf("%s",&choix);
					if(strcmp(choix,choice) != 0)
					{
						fwrite(&cat,sizeof(cat),1,temp);
					}
					else
					{
						tr = 1;
					}
				}
				else
				{
					fwrite(&cat,sizeof(cat),1,temp);
				}

			}
			fclose(temp);
		}
		fclose(fcat);
	remove("fcate.ing");
	rename("temp.ing","fcate.ing");
	if(tr == 1)
		printf("le produit a ete supprimer \n");
	else
		printf("rien n'a ete modifier");
	}
}
/*
void facturation()
	{
		char choix[4];
		char choice[]="OK";
		char code[10];
		int tr = 0,n=0;
		produit prod;
		produit prodtemp;
		FILE *temp;
		FILE *fproduit;
		FILE *ffacture;

		fproduit=fopen("fprod.ing","r");
		if(fproduit == NULL)
			printf("probleme de lecture");
		else
		{
			ffacture=fopen("facture.ing","w");
			if(ffacture == NULL)
				printf("probleme");
			else
			{
				printf("entrer FIN en majuscule pour arreter l'enregistrement de la facture");
				do
					{
						
					} while (strcmp(fin));	
			}
		}
	}
*/
void menu()
 	{
 		printf("salut voici le menu \n");
		printf(" 1- ajouter un produit au fichier \n 2- ajouter une categorie \n 3- pour lire les informations sur les produits dans le fichier \n 4-pour lire les informations sur les categories dans le fichier \n 5- pour faire une recherche de produit sur une categorie \n 6-Approvisionement \n 7-Supprimer un produit \n 8-supprimer une categorie \n 9-facturation \n 10-quitter le programme \n");
 	}

 	void gestion(int t)
 	{
 		switch(t)
 		{
 		case 1 :
 			system("CLS");
 			creationProd();
 			break;

 		case 2 :
 			system("CLS");
 			creationCat();
 			break;

 		case 3 :
 			system("CLS");
 			lectureProd();
 			break;

 		case 4 :
 			system("CLS");
 			lectureCat();
 			break;

 		case 5 :
 			system("CLS");
 			char nomcategorie_1[10]; produit prod;
 			printf("entrer le code de la categorie a rechercher \n-->");
 			scanf("%s",&nomcategorie_1);
 			prod = rechercheProdCat(nomcategorie_1);
 			if(prod.prixP == 0)
 				printf("le produit existe");
 			else
 				printf("le produit n'existe pas");
 			break;

 		case 6 :
 			system("CLS");
 			char code[10];
			int newStock = 0;
			printf("entrer le code du produit a modifier\n -->");
			scanf("%s",&code);
			printf("entrer la quantité du stock a ajouter dans le produit\n");
			scanf("%d",&newStock);
 			modifProd(code,newStock);
 			break;

 		case 7 :
 			system("CLS");
 			deleteProd();

 		case 8:
 			system("CLS");
 			deleteCat();
 			break;

 		/*case 9:
 			system("CLS");
 			facturation();*/

 		case 10 :
 			system("CLS");
 			printf("aurevoir mon cher ami \n");
 			break;

 		default :
 			system("CLS");
 			printf("impossible de realiser cette action\n");
 		}
 	}

void manager()
 	{
 		printf("bienvenue dans visualisation fichier \n \n");
	int choix = 0;

	do
	{
		printf("\n");
		menu();
		printf("entrer votre choix \n -->");
		scanf("%d",&choix);
		gestion(choix);
		printf("merci \n");
		printf("/---------------------------------------------------------------/ \n");
	} while (choix != 10);

 	}