#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct date{
    int a;
    int j;
    int m;
} date;

typedef struct produit {
    char nom[10];
    char id[10];
    char description[100];
    float prix;
    int quantite;
    int quantite_a;
    date dernier_s;
    date dernier_e;
} produit;


typedef struct employe {
    char nom[20];
    char password[20];
    int admin;
} employe;




void remplissage(int n) {
    FILE *fichier;
    produit *t = (produit *)malloc(n * sizeof(produit));

    fichier = fopen("test.csv", "a");

    for (int i = 0; i < n; i++) {
        printf("Entrez le nom du produit : ");
        scanf("%s", t[i].nom);
        fprintf(fichier, "%s,", t[i].nom);

        printf("Entrez l'ID du produit : ");
        scanf("%s", t[i].id);
        fprintf(fichier, "%s,", t[i].id);

        printf("Entrez la description du produit : ");
        scanf("%s", t[i].description);
        fprintf(fichier, "%s,", t[i].description);

        printf("Entrez le prix du produit : ");
        scanf("%f", &t[i].prix);
        fprintf(fichier, "%.2f,", t[i].prix);

        printf("Entrez la quantite du produit : ");
        scanf("%d", &t[i].quantite);
        fprintf(fichier, "%d,", t[i].quantite);

        printf("Entrez la quantite alerte du produit : ");
        scanf("%d", &t[i].quantite_a);
        fprintf(fichier, "%d,", t[i].quantite_a);

        printf("Entrez la date de dernier entree (jj mm aaaa) : ");
        scanf("%d %d %d", &t[i].dernier_s.j, &t[i].dernier_s.m, &t[i].dernier_s.a);
        fprintf(fichier, "%d/%d/%d\n", t[i].dernier_s.j, t[i].dernier_s.m, t[i].dernier_s.a);
    }

    fclose(fichier);
    free(t);
}





void ajout() {
    FILE *fichier;
    fichier = fopen("test.csv", "a+");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(1);
    }

    produit *t = (produit *)malloc(sizeof(produit));
    if (t == NULL) {
        printf("Allocation de mémoire échouée\n");
        exit(1);
    }

    printf("Entrez l'ID du produit : ");
    scanf("%s", t->id);
    fprintf(fichier, "%s,", t->id);

    printf("Entrez le nom du produit : ");
    scanf("%s", t->nom);
    fprintf(fichier, "%s,", t->nom);

    printf("Entrez la description du produit : ");
    scanf("%s", t->description);
    fprintf(fichier, "%s,", t->description);

    printf("Entrez le prix du produit : ");
    scanf("%f", &t->prix);
    fprintf(fichier, "%.2f,", t->prix);

    printf("Entrez la quantite du produit : ");
    scanf("%d", &t->quantite);
    fprintf(fichier, "%d,", t->quantite);

    printf("Entrez la quantite alerte du produit : ");
    scanf("%d", &t->quantite_a);
    fprintf(fichier, "%d,", t->quantite_a);

    printf("Entrez la date de dernier entree (jj mm aaaa) : ");
    scanf("%d %d %d", &t->dernier_s.j, &t->dernier_s.m, &t->dernier_s.a);
    fprintf(fichier, "%d/%d/%d\n", t->dernier_s.j, t->dernier_s.m, t->dernier_s.a);

    fclose(fichier);
    free(t);
}

void affichageemploye() {
    
     FILE *fichier;
    char id[30], password[30], prenom[30], nom[30], ville[30];
    int admin, age, dureeTravail;

    fichier = fopen("employe.csv", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    printf("%-20s%-20s%-10s%-20s%-20s\n", "Prénom", "Nom", "Âge", "Ville", "Durée de travail");
    printf("-------------------------------------------------------------------------------\n");

    while (fscanf(fichier, "%29[^,],%29[^,],%d,%29[^,],%29[^,],%d,%29[^,],%d\n", id, password, &admin, prenom, nom, &age, ville, &dureeTravail) == 8) {
        printf("%-20s%-20s%-10d%-20s%-20d\n", prenom, nom, age, ville, dureeTravail);
    }

    fclose(fichier);
}


void rechercherEmployeParNom() {
    FILE *fichier;
    fichier = fopen("employe.csv", "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    int found = 0;
    char name[20], pass[20], nomm[20], prenom[20], ville[20];
    int admin, age, mois;

    printf("Entrez le nom de l'employé que vous recherchez : ");
    char nomEmploye[20];
    scanf("%19s", nomEmploye);

    while (fscanf(fichier, "%19[^,],%19[^,],%d,%19[^,],%19[^,],%d,%19[^,],%d\n",
                  name, pass, &admin, nomm, prenom, &age, ville, &mois) == 8) {
        if (strcasecmp(name, nomEmploye) == 0) {
            printf("Nom : %s\n", nomm);
            printf("Prenom : %s\n", prenom);
            printf("Age : %d\n", age);
            printf("Ville : %s\n", ville);
            printf("Mois : %d\n", mois);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Aucun employé trouvé avec ce nom.\n");
    }

    fclose(fichier);
}



void affichage() {
    FILE *fichier = fopen("test.csv", "rt");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    printf("+--------------------+----------+-------------------------------------------+----------+----------+----------------+---------------------+\n");
    printf("| NOM                | ID       | Description                               | Prix     | Quantite | Quantite Alerte| Dernier Entrée      |\n");
    printf("+--------------------+----------+-------------------------------------------+----------+----------+----------------+---------------------+\n");

    char id[30], name[30], descc[30];
    float theprice;
    int quantity, quantity_a, datej, datem, datea;

    while (fscanf(fichier, "%29[^,],%29[^,],%29[^,],%f,%d,%d,%d/%d/%d\n", id, name, descc, &theprice, &quantity, &quantity_a, &datej, &datem, &datea) == 9) {
        printf("| %-18s | %-8s | %-41s | %-8.2f | %-8d | %-14d | %02d/%02d/%04d       |\n", id, name, descc, theprice, quantity, quantity_a, datej, datem, datea);
    }

    printf("+--------------------+----------+-------------------------------------------+----------+----------+----------------+---------------------+\n");

    fclose(fichier);
}

void menu() {
    printf("----------------------------MENU----------------------------- \n");

    printf("0. Effectuer le remplissage \n");
    printf("1. Ajout produit \n");
    printf("2. Suppression produit \n");
    printf("3. Modification produit \n");
    printf("4. Chercher par nom \n");
    printf("5. voir les informations des employés\n");
    printf("6. Effectuer la recherche sur un employé \n");
    printf("7. Effectuer l'affichage \n");
     printf("8. Retourner à L'interface des choix \n");
    printf("9. Quitter le programme \n");
}


void menuemloye() {
	
	
    printf("----------------------------MENU----------------------------- \n");

    printf("0. Effectuer le remplissage \n");
    printf("1. Ajout produit \n");
    printf("2. Chercher par nom \n");
    printf("3. Effectuer l'affichage \n");
    printf("4. Retourner à L'interface des choix \n");
    printf("5. Quitter le programme \n");
    
    
    
}

void modifyy() {
    int ID, tr = 0;
    produit prod;
    FILE *fichier2, *fichier1;
    char id[30], name[30], descc[30];
    float theprice;
    int casee;
    int quantity, quantity_a, datej, datem, datea;
    fichier2 = fopen("test2.csv", "w");
    fclose(fichier2);
    fichier2 = fopen("test2.csv", "a");

    fichier1 = fopen("test.csv", "rt");

    printf("Entrez la case a modifier:\n");
    scanf("%d", &casee);
    int y = 0;
    while (fscanf(fichier1, "%29[^,],%29[^,],%29[^,],%f,%d,%d,%d/%d/%d\n", id, name, descc, &theprice, &quantity, &quantity_a, &datej, &datem, &datea) == 9) {
        if (casee == y) {
            printf("donner moi l'id que tu veux placer a la case %d : ", y);
            scanf("%s", id);
            printf("Donnez-moi le nom que vous voulez placer à la case %d : ", y);
            scanf("%s", name);

            printf("Donnez-moi la description que vous voulez placer à la case %d : ", y);
            scanf("%s", descc);

            printf("Donnez-moi le prix que vous voulez placer à la case %d : ", y);
            scanf("%f", &theprice);

            printf("Donnez-moi la quantité que vous voulez placer à la case %d : ", y);
            scanf("%d", &quantity);

            printf("Donnez-moi la quantité_a que vous voulez placer à la case %d : ", y);
            scanf("%d", &quantity_a);

            printf("Donnez-moi le jour de la date que vous voulez placer à la case %d : ", y);
            scanf("%d", &datej);

            printf("Donnez-moi le mois de la date que vous voulez placer à la case %d : ", y);
            scanf("%d", &datem);

            printf("Donnez-moi l'année de la date que vous voulez placer à la case %d : ", y);
            scanf("%d", &datea);

            fprintf(fichier2, "%s,%s,%s,%.2f,%d,%d,%d/%d/%d\n", id, name, descc, theprice, quantity, quantity_a, datej, datem, datea);
        } else {
            fprintf(fichier2, "%s,%s,%s,%.2f,%d,%d,%d/%d/%d\n", id, name, descc, theprice, quantity, quantity_a, datej, datem, datea);
        }

        y++;
    }
    fclose(fichier1);
    fclose(fichier2);
    remove("test.csv");
    rename("test2.csv", "test.csv");
}
void modifye() {
    produit prod;
    FILE *fichier1, *fichier2;
    char id[30];
    
    fichier1 = fopen("test.csv", "r");
    fichier2 = fopen("temp.csv", "w");
    
    printf("Entrez l'ID du produit à modifier : ");
    scanf("%29s", id);
    int found = 0;

    while (fscanf(fichier1, "%29[^,],%29[^,],%99[^,],%f,%d,%d,%d/%d/%d\n",
                  prod.nom, prod.id, prod.description, &prod.prix,
                  &prod.quantite, &prod.quantite_a,
                  &prod.dernier_s.j, &prod.dernier_s.m, &prod.dernier_s.a) == 9) {
        if (strcmp(prod.id, id) == 0) {
            found = 1;
            printf("Produit trouvé. Entrez les nouvelles informations :\n");
            
            printf("Donnez-moi le nom : ");
            scanf("%29s", prod.nom);
			
			printf("Donnez-moi l'ID : ");
            scanf("%29s", prod.id);
			
            printf("Donnez-moi la description : ");
            scanf(" %99[^\n]", prod.description);  // Permet de lire les espaces dans la description

            printf("Donnez-moi le prix : ");
            scanf("%f", &prod.prix);

            printf("Donnez-moi la quantité : ");
            scanf("%d", &prod.quantite);

            printf("Donnez-moi la quantité alerte : ");
            scanf("%d", &prod.quantite_a);

            printf("Donnez-moi la date de dernière entrée (jj mm aaaa) : ");
            scanf("%d %d %d", &prod.dernier_s.j, &prod.dernier_s.m, &prod.dernier_s.a);
        }

        fprintf(fichier2, "%s,%s,%s,%.2f,%d,%d,%d/%d/%d\n",
                prod.nom, prod.id, prod.description, prod.prix,
                prod.quantite, prod.quantite_a,
                prod.dernier_s.j, prod.dernier_s.m, prod.dernier_s.a);
    }

    if (!found) {
        printf("Aucun produit trouvé avec cet ID.\n");
    }

    fclose(fichier1);
    fclose(fichier2);

    remove("test.csv");
    rename("temp.csv", "test.csv");
}
void cherchenom() {
    FILE *fichier1;
    char id[30], name[30], descc[30];
    float theprice;
    int quantity, quantity_a, datej, datem, datea;

    fichier1 = fopen("test.csv", "rt");

    char cherche_nom[30];

    printf("Entrez le nom que vous cherchez : ");
    scanf("%s", cherche_nom);

    int y = 0;
    int l = 0;

    while (fscanf(fichier1, "%29[^,],%29[^,],%29[^,],%f,%d,%d,%d/%d/%d\n", id, name, descc, &theprice, &quantity, &quantity_a, &datej, &datem, &datea) == 9) {
        if (strcmp(name, cherche_nom) == 0 && l == 1) {
            printf(" et %d", y);
        } else if (strcmp(name, cherche_nom) == 0) {
            printf("ce nom existe dans les produits : %d", y);

            l = 1;
        }
        y++;
    }

    if (l == 0) {
        printf("le nom n'existe pas\n");
    }

    printf("\n");

    fclose(fichier1);
}
void deleteid() {
    char id[30], target_id[30], name[30], descc[100];
    float theprice;
    int quantity, quantity_a, datej, datem, datea;
    FILE *fichier1, *fichier2;
    
    fichier1 = fopen("test.csv", "r");
    fichier2 = fopen("test2.csv", "w");

    printf("Entrez l'ID du produit à supprimer :\n");
    scanf("%29s", target_id);

    int found = 0;

    while (fscanf(fichier1, "%29[^,],%29[^,],%99[^,],%f,%d,%d,%d/%d/%d\n", id, name, descc, &theprice, &quantity, &quantity_a, &datej, &datem, &datea) == 9) {
        if (strcmp(name, target_id) != 0) {
            fprintf(fichier2, "%s,%s,%s,%.2f,%d,%d,%d/%d/%d\n", id, name, descc, theprice, quantity, quantity_a, datej, datem, datea);
        } else {
            found = 1;
        }
    }

    fclose(fichier1);
    fclose(fichier2);

    if (found) {
        remove("test.csv");
        rename("test2.csv", "test.csv");
        printf("Produit supprimé avec succès.\n");
    } else {
        printf("Aucun produit trouvé avec cet ID.\n");
        remove("test2.csv");
    }
}
void deelete() {
    int casee, y = 0;
    char id[30], name[30], descc[30];
    float theprice;
    int quantity, quantity_a, datej, datem, datea;
    FILE *fichier1, *fichier2;
    
    fichier1 = fopen("test.csv", "r");
    if (fichier1 == NULL) {
        printf("Erreur lors de l'ouverture du fichier test.csv.\n");
        return;
    }

    fichier2 = fopen("test2.csv", "w");
    if (fichier2 == NULL) {
        printf("Erreur lors de la création du fichier test2.csv.\n");
        fclose(fichier1);
        return;
    }

    printf("Entrez le numéro de la ligne à supprimer :\n");
    scanf("%d", &casee);

    while (fscanf(fichier1, "%29[^,],%29[^,],%29[^,],%f,%d,%d,%d/%d/%d\n", id, name, descc, &theprice, &quantity, &quantity_a, &datej, &datem, &datea) == 9) {
        if (y != casee) {
            fprintf(fichier2, "%s,%s,%s,%.2f,%d,%d,%d/%d/%d\n", id, name, descc, theprice, quantity, quantity_a, datej, datem, datea);
        }
        y++;
    }

    fclose(fichier1);
    fclose(fichier2);

    if (remove("test.csv") != 0) {
        printf("Erreur lors de la suppression du fichier test.csv.\n");
    } else {
        if (rename("test2.csv", "test.csv") != 0) {
            printf("Erreur lors du renommage du fichier test2.csv en test.csv.\n");
        } else {
            printf("Ligne supprimée avec succès.\n");
        }
    }
}




int employee() {
    FILE *fichier;
    char nom[20], password[20];
    char name[20], pass[20];
    int admin;
    char nomm[20];
    char prenom[20];
    char ville[20];
    int age, mois;

    printf("Veuillez entrer le nom : ");
    scanf("%19s", nom);

    fichier = fopen("employe.csv", "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }

    while (fscanf(fichier, "%19[^,],%19[^,],%d,%19[^,],%19[^,],%d,%19[^,],%d\n",
                  name, pass, &admin, nomm, prenom, &age, ville, &mois) == 8) {
        if (strcmp(nom, name) == 0) {
            printf("Utilisateur trouvé, veuillez entrer le mot de passe : ");
            scanf("%19s", password);
            if (strcmp(pass, password) == 0) {
                if (admin == 1) {
                    printf("Authentification réussie en tant qu'administrateur.\n");
                    fclose(fichier);
                    return 2;
                } else {
                    printf("Authentification réussie.\n");
                    fclose(fichier);
                    return 1;
                }
            } else {
                printf("Mot de passe incorrect.\n");
                fclose(fichier);
                return 0;
            }
        }
    }

    printf("Utilisateur non trouvé.\n");
    fclose(fichier);
    return 0;
}













void interface() {
    printf("____________________________________\n");
    printf("1. Interface employé \n");
    printf("2. Interface utilisateur \n");

    printf("le choix :");
}

void parcourirrecue() {
    FILE *fichier = fopen("achats.csv", "rt");
   

    char nom_client[30];
    char name[30];
    int quantite_user;
    float prix_total;
    float prix;
    int y = 1;

    while (fscanf(fichier, "%29[^,],%29[^,],%f,%d,%f\n", nom_client, name, &prix, &quantite_user, &prix_total) == 5) {
        printf("________________________________________________\n");
        printf("Reçu N*%d \n", y);
        printf("Le nom : %s\n", nom_client);
        printf("Le nom du produit : %s \n", name);
        printf("Le prix du produit  : %.2f\n", prix);
        printf("La quantité utilisateur : %d\n", quantite_user);
        printf("Le prix total : %.2f\n", prix_total);
        printf("_________________________________________________\n");
        y++;
    }

    fclose(fichier);
}













void achatproduit() {
    FILE *fichier1, *fichier2, *temp;
    char id[30], name[30], descc[100];
    float theprice;
    int quantity, quantity_a, datej, datem, datea;
    
    fichier1 = fopen("test.csv", "r");
    fichier2 = fopen("achats.csv", "a");
    temp = fopen("temp.csv", "w");
    
    if (fichier1 == NULL || fichier2 == NULL || temp == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }
    
    char cherche_nom[30], nom_client[30];
    printf("Donnez moi le nom du client : ");
    scanf("%29s", nom_client);
    printf("Entrez le nom du produit que vous cherchez : ");
    scanf("%29s", cherche_nom); 
    
    int produit_trouve = 0;
    int quantite_user, nouvelle_quantite; 
    float prix_total;
    
    while (fscanf(fichier1, "%29[^,],%29[^,],%99[^,],%f,%d,%d,%d/%d/%d\n",
                  id, name, descc, &theprice, &quantity, &quantity_a,
                  &datej, &datem, &datea) == 9) {
        if (strcmp(name, cherche_nom) == 0) {
            produit_trouve = 1;
            printf("Ce produit est disponible. Entrez la quantité souhaitée : ");
            scanf("%d", &quantite_user);
            if (quantite_user <= quantity) {
                nouvelle_quantite = quantity - quantite_user;
                prix_total = quantite_user * theprice; 
                
                fprintf(temp, "%s,%s,%s,%.2f,%d,%d,%02d/%02d/%04d\n", id, name, descc, theprice, nouvelle_quantite, quantity_a, datej, datem, datea);
                
                fprintf(fichier2, "%s,%s,%.2f,%d,%.2f\n", nom_client, name, theprice, quantite_user, prix_total);
                
                printf("Achat effectué avec succès. Nouvelle quantité disponible : %d\n", nouvelle_quantite);
                printf("Prix total : %.2f\n", prix_total);
            } else {
                printf("La quantité demandée n'est pas disponible.\n");
                fprintf(temp, "%s,%s,%s,%.2f,%d,%d,%02d/%02d/%04d\n", id, name, descc, theprice, quantity, quantity_a, datej, datem, datea);
            }
        } else {
            fprintf(temp, "%s,%s,%s,%.2f,%d,%d,%02d/%02d/%04d\n", id, name, descc, theprice, quantity, quantity_a, datej, datem, datea);
        }
    }
    
    if (!produit_trouve) {
        printf("Ce produit n'existe pas.\n");
    }
    
    fclose(fichier1);
    fclose(fichier2);
    fclose(temp);
    
    remove("test.csv");
    rename("temp.csv", "test.csv");
}


void retourrecue() {
    FILE *fichier1 = fopen("achats.csv", "rt");
    FILE *fichier2 = fopen("retour.csv", "a");
    FILE *tempfile = fopen("temp.csv", "wt");

    if (fichier1 == NULL || fichier2 == NULL || tempfile == NULL) {
        perror("Erreur lors de l'ouverture des fichiers");
        return;
    }

    char nom_client[30];
    char name[30];
    char nom[30];
    float prix;
    int quantite_user;
    float prix_total;
    int y = 0;
    int choix_user;
    int typeretour;

    printf("Veuillez me donner le nom du client : ");
    scanf("%s", nom);


    while (fscanf(fichier1, "%29[^,],%29[^,],%f,%d,%f\n", nom_client, name, &prix, &quantite_user, &prix_total) == 5) {
        if (strcmp(nom, nom_client) == 0) {
            printf("________________________________________________\n");
            printf("Reçu N*%d \n", y + 1);
            printf("Le nom : %s\n", nom_client);
            printf("Le nom du produit : %s \n", name);
            printf("Le prix du produit  : %.2f\n", prix);
            printf("La quantité utilisateur : %d\n", quantite_user);
            printf("Le prix total : %.2f\n", prix_total);
            printf("_________________________________________________\n");
            y++;
        }
    }

    if (y == 0) {
        printf("Ce client n'a aucune commande\n");
        fclose(fichier1);
        fclose(fichier2);
        fclose(tempfile);
        return;
    }

    printf("Ce nom a effectué %d commande(s). Laquelle voulez-vous retourner ? ", y);
   
        scanf("%d", &choix_user);
    

    rewind(fichier1);

    int i = 1;
    while (fscanf(fichier1, "%29[^,],%29[^,],%f,%d,%f\n", nom_client, name, &prix, &quantite_user, &prix_total) == 5) {
        if (strcmp(nom, nom_client) == 0 && i == choix_user) {
            printf("________________________________________________\n");
            printf("Reçu N*%d \n", i);
            printf("Le nom : %s\n", nom_client);
            printf("Le nom du produit : %s \n", name);
            printf("Le prix du produit  : %.2f\n", prix);
            printf("La quantité utilisateur : %d\n", quantite_user);
            printf("Le prix total : %.2f\n", prix_total);
            printf("_________________________________________________\n");
            i++;

            printf("Tapez (0) pour retourner la totalité et (1) pour une quantité spécifique.\n");
            scanf("%d", &typeretour);
            int quantiteretour;
            int newq;

            if (typeretour == 0) {
                fprintf(fichier2, "%s,%s,%.2f,%d,%.2f\n", nom_client, name, prix, quantite_user, prix_total);
            } else if (typeretour == 1) {
                printf("Donnez-moi la quantité que vous voulez retourner : ");
                scanf("%d", &quantiteretour);

                if (quantiteretour <= quantite_user) {
                    newq = quantite_user - quantiteretour;
                    float prix_total_retour = quantiteretour * prix;
                    float new_prix_total = newq * prix;

                    if (newq > 0) {
                        fprintf(tempfile, "%s,%s,%.2f,%d,%.2f\n", nom_client, name, prix, newq, new_prix_total);
                    }

                    fprintf(fichier2, "%s,%s,%.2f,%d,%.2f\n", nom_client, name, prix, quantiteretour, prix_total_retour);

                    printf("Retour effectué avec succès. Nouvelle quantité disponible : %d\n", newq);
                    printf("Prix total retourné : %.2f\n", prix_total_retour);
                } else {
                    printf("La quantité demandée n'est pas disponible.\n");
                    fprintf(tempfile, "%s,%s,%.2f,%d,%.2f\n", nom_client, name, prix, quantite_user, prix_total);
                }
            }
        } else {
            fprintf(tempfile, "%s,%s,%.2f,%d,%.2f\n", nom_client, name, prix, quantite_user, prix_total);
        }
        
    }

    fclose(fichier1);
    fclose(fichier2);
    fclose(tempfile);

    remove("achats.csv");
    rename("temp.csv", "achats.csv");
}


void recueclientsp() {
    FILE *fichier1 = fopen("achats.csv", "rt");
    

    char nom_client[30];
    char name[30];
    char nom[30];
    float prix;
    int quantite_user;
    float prix_total;
    int y = 0;
    int choix_user;
    int typeretour;

    printf("Veuillez me donner le nom du client : ");
    scanf("%29s", nom);

    // Compter le nombre de commandes du client
    while (fscanf(fichier1, "%29[^,],%29[^,],%f,%d,%f\n", nom_client, name, &prix, &quantite_user, &prix_total) == 5) {
        if (strcmp(nom, nom_client) == 0) {
            printf("________________________________________________\n");
            printf("Reçu N*%d \n", y + 1);
            printf("Le nom : %s\n", nom_client);
            printf("Le nom du produit : %s \n", name);
            printf("Le prix du produit  : %.2f\n", prix);
            printf("La quantité utilisateur : %d\n", quantite_user);
            printf("Le prix total : %.2f\n", prix_total);
            printf("_________________________________________________\n");
            y++;
        }
    }

    

    fclose(fichier1);
   
}


affichageretour(){
	
	FILE *fichier;
    fichier = fopen("retour.csv", "rt");
    char nom_client[30];
    char name[30];
    int quantite_user;
    float prix_total;
    int y = 1;

    while (fscanf(fichier, "%30[^,],%30[^,],%d,%f\n", nom_client, name, &quantite_user, &prix_total) == 4) {
        printf("________________________________________________\n");
        printf("Reçu N*%d \n", y);

        printf("Le nom : %s\n", nom_client);
        printf("Le nom du produit : %s \n", name);
        printf("La quantité utilisateur : %d\n", quantite_user);
        printf("Le prix total : %.2f\n", prix_total);
        printf("_________________________________________________\n");
        y++;
    }

    fclose(fichier);
	
	
}

int main() {
a:
    int choiche;

    interface();
b:
    scanf("%d", &choiche);

    if (choiche == 1) {
    	int var1  = employee() ;  
        if ( var1 == 0) {
            printf("Utilisateur ou mot de passe non valide");
            return 0;
        } 
		else if(var1 == 1){
					int n;
            produit *tab;
            FILE* fichier;

            int choix;
            tab = (produit *)malloc(sizeof(produit));
            do {
                menuemloye();
                printf("Veuillez me donner votre choix : ");
                scanf("%d", &choix);

                switch (choix) {
                    case 0:
                        printf("Veuillez me donner la taille : ");
                        scanf("%d", &n);
                        remplissage(n);
                        break;
                    case 1:
                        ajout();
                        break;
                    case 2:
                        cherchenom();
                        break;
                    case 3:
                        affichage();
                        break;
                    case 4:
                        cherchenom();
                        break;
                    case 5:
                        rechercherEmployeParNom();
                        break;
                   
                    
                }
            } while (choix == 9);
            return 0;
			
			
			
			
			
			
			
			
			
		}
		else if( var1 == 2) {
            int n;
            produit *tab;
            FILE* fichier;

            int choix;
            tab = (produit *)malloc(sizeof(produit));
            do {
                menu();
                printf("Veuillez me donner votre choix : ");
                scanf("%d", &choix);

                switch (choix) {
                    case 0:
                        printf("Veuillez me donner la taille : ");
                        scanf("%d", &n);
                        remplissage(n
						);
                        break;
                    case 1:
                        ajout();
                        break;
                    case 2:
                        int choixmodii;
                    	printf("________________________________\n");
                    	printf("1. Supprimer par case .\n");
                    	printf("2. Supprimer par ID .\n");	
                    	res : 
                    	scanf("%d",&choixmodii);
                    	if(choixmodii  == 1){
						
                        deelete();
						}
                        else if(choixmodii  == 2){
                        	deleteid() ; 
                        	
                        	
						}
						else{
							goto res ;
						}
                        break;
                    case 3:
                    	int choixmodi;
                    	printf("________________________________\n");
                    	printf("1. modifier par case .\n");
                    	printf("2. modifier par ID .\n");	
                    	re : 
                    	scanf("%d",&choixmodi);
                    	if(choixmodi  == 1){
						
                        modifyy();}
                        else if(choixmodi  == 2){
                        	modifye() ; 
                        	
                        	
						}
						else{
							goto re ;
						}
                        break;
                    case 4:
                        cherchenom();
                        break;
                    case 5:affichageemploye();
                        break;
                    case 6:
                       rechercherEmployeParNom();
                        break;
                        
                    case 7:
                         affichage();
                        break;
                   
                   
                        	
					
                    case 10  : 
                    	goto a ; break  ;
                }
            } while (choix != 11);
            return 0;
        }
    } 
	
	else if (choiche == 2) {
        int choix = 0;
		
		
        do {
            printf("______________________________________________\n");
            printf("1. Afficher les produits\n");
            printf("2. Achetez un produit\n");
            
            printf("3. Retourner à l'interface des choix\n");
            printf("4. Quitter le programme\n");
            printf("Veuillez entrer votre choix : ");
            scanf("%d", &choix);

            switch (choix) {
                case 1:
                    affichage();
                    break;
                case 2:
                    achatproduit();
                    break;
                
                case 3: goto a ;
                    break;
                default:
                    printf("Option non valide. Veuillez réessayer.\n");
                    break;
            }
        } while (choix != 4);
    }

    return 0;
}

