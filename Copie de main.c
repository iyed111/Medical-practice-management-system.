#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// systeme de gestion de cabinet medical :


int count(int x){
    int count = 0 ;
    do{
        x/=10 ;
        count ++ ;
    } while (x != 0);
    return count ;
}

bool isperfect(char *date) {
    bool perfect = true;
    if (date[2] != '/' || date[5] != '/') {
        perfect = false;
    }
    return perfect;
}


typedef struct {
    int id;
    char nom[20];
    char prenom[20];
    char date_naissance[15];
    char numero_tel[15];
} Patient;

typedef struct {
    int id;
    char nom[20];
    char prenom[20];
    char specialite[20];
    char numero_tel[15];
    char disponibilite[20];
} Medecin;

typedef struct {
    int id;
    char date[15];
    int heure;
    int code_patient;
    int code_medecin;
} RDV;

FILE * ouvrirF(char * nomfichier , char * mode ){
    FILE * fichier = fopen(nomfichier,mode);
    if (fichier == NULL ){
        printf("Impossible d'ouvrir ou de creer le fichier %s !\n", nomfichier);
        exit(1);
    }
    //printf("Le fichier %s est cree/ouvert avec succes ! \n", nomfichier);
    return fichier;
}

Patient saisiepatient(){
    Patient p1 ;
    printf("Entrer les coordonnees du patient : \n");
    do{
        printf("Identifiant (8 chiffres) : ");
        scanf("%d",& p1.id);
    }while(count(p1.id) != 8);
    printf("Nom : ");
    scanf(" %[^\n]s",p1.nom);
    printf("Prenom : ");
    scanf(" %[^\n]s",p1.prenom);
    do{
        printf("Date de naissance (format : JJ/MM/AAAA) : ");
        scanf(" %[^\n]s",p1.date_naissance);
    }while(strlen(p1.date_naissance)!= 10 || !isperfect(p1.date_naissance));
    do{
        printf("Numero du telephone : ");
        scanf(" %[^\n]s",p1.numero_tel);
    }while(strlen(p1.numero_tel)!= 8);
    return p1 ;
}

void ajouterPatient(FILE * fichier){
    Patient p; Patient p1 = saisiepatient() ;
    rewind(fichier);
    while (fread(&p,sizeof(Patient),1,fichier)== 1){
        if (p.id == p1.id ){
            printf("Impossible d'ajouter un patient qui existe deja !\n");
            exit(1);
        }
    }
    fseek(fichier,0,SEEK_END);
    fwrite(&p1,sizeof(Patient),1,fichier);
    printf("Le patient est ajoute avec succes !\n");
}

void supprimerPatient(FILE* fichier) {
    int idP;
    do{
        printf("Entrez l'identifiant du patient a retirer (8 chiffres) : \n");
        scanf("%d", &idP);
    }while(count(idP) != 8);
    Patient p;

    FILE* temp = fopen("tmp.dat", "w+");
    rewind(fichier);
    int found = 0;

    while (fread(&p, sizeof(Patient), 1, fichier) == 1) {
        if (p.id != idP) {
            fwrite(&p, sizeof(Patient), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(fichier);
    fclose(temp);
    remove("patient.dat");
    rename("tmp.dat", "patient.dat");
    if (found) {
        printf("Le patient est supprime avec succes !\n");
    } else {
        printf("Le patient n'a pas ete trouve !\n");
    }
}

Medecin saisieMedecin(){
    Medecin m1 ;
    printf("Entrer les coordonnees du medecin : \n");
    do{
        printf("L'identifiant :  l'id se compose 8 chiffres ! ");
        scanf("%d",& m1.id);
    }while (count(m1.id) != 8);
    printf("Le nom : ");
    scanf(" %[^\n]s",m1.nom);
    printf("Le prenom : ");
    scanf(" %[^\n]s",m1.prenom);
    printf("specialite : ");
    scanf(" %[^\n]s",m1.specialite);
    do{
        printf("Numero du telephone : ");
        scanf(" %[^\n]s",m1.numero_tel);
    }while(strlen(m1.numero_tel)!= 8);
    printf("disponibilite : ");
    scanf(" %[^\n]s",m1.disponibilite);
    return m1 ;
}

void ajouterMedecin(FILE * fichier){
    Medecin m;
    Medecin m1 = saisieMedecin();
    rewind(fichier);
    while (fread(&m,sizeof(Medecin),1,fichier)== 1){
        if (m.id == m1.id ){
            printf("Impossible d'ajouter un medecin qui existe deja !\n");
            exit(1);
        }
    }
    fseek(fichier,0,SEEK_END);
    fwrite(&m1,sizeof(Medecin),1,fichier);
    printf("Le medecin est ajoute avec succes !\n");
}

void supprimerMedecin(FILE* fichier) {
    int idM;
    do{
        printf("Entrez l'identifiant du medecin a retirer : l'id se compose 8 chiffres ! \n");
        scanf("%d", &idM);
    }while(count(idM) != 8);
    Medecin m ;

    FILE* temp = fopen("tmp.dat", "w+");
    rewind(fichier);
    int found = 0;

    while (fread(&m, sizeof(Medecin), 1, fichier) == 1) {
        if (m.id != idM) {
            fwrite(&m, sizeof(Medecin), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(fichier);
    fclose(temp);
    remove("medecin.dat");
    rename("tmp.dat","medecin.dat");

    if (found == 1) {
        printf("Le medecin est supprime avec succes !\n");
    } else {
        printf("Le medecin ne se trouve pas !\n");
    }
}


void rechercheMedecin(FILE * fichier){
    int idMedcin ; Medecin m ;
    do{
        printf("Entrer l'identifiant du medecin que vous cherchez : l'id se compose 8 chiffres ! ");
        scanf("%d",&idMedcin);
    }while(count(idMedcin) != 8);
    rewind(fichier);
    int found = 0 ;
    while (fread(&m, sizeof(Medecin),1, fichier) == 1){
        if (m.id == idMedcin){
            printf("Voici les coordonnees de ce medecin : \n");
            printf("L'identifiant est : %d \n",m.id);
            printf("Le nom est : %s \n",m.nom);
            printf("Le prenom est : %s \n",m.prenom);
            printf("Specialite est : %s \n",m.specialite);
            printf("Numero du telephone est : %d \n",m.numero_tel);
            printf("Disponibilite est : %s \n",m.disponibilite);
            found = 1;
            break;
        }
    }
    if (found==0){
        printf("Desole, ce medecin n'est pas trouve !\n");
    }
}


RDV saisieRDV(){
    RDV rdv1 ;
    printf("Merci d'entrer ces coordonnes pour prendre un rendez-vous : \n");
    do{
        printf("L'identifiant : l'id se compose 8 chiffres ! ");
        scanf("%d",&rdv1.id);
    }while(count(rdv1.id)!= 8);
    do{
        printf("La date : (format : JJ/MM/AAAA) : ");
        scanf(" %[^\n]s", rdv1.date);
    }while(strlen(rdv1.date)!= 10 || !isperfect(rdv1.date));
    do{
        printf("L'heure : Nous travaillons de 7h a 20 h ! : ");
        scanf("%d",&rdv1.heure);
    }while( rdv1.heure < 7 || rdv1.heure > 20 );
    do{
        printf("Code patient ,8chiffres : ");
        scanf("%d",&rdv1.code_patient);
    }while(count(rdv1.code_patient) != 8 );
    do{
        printf("Code medecin : ");
        scanf("%d",&rdv1.code_medecin);
    }while(count(rdv1.code_medecin) != 8 );
    return rdv1 ;
}


void prendreRDV (FILE * fichier) {
    RDV rdv; RDV rdv1 = saisieRDV();
    int found = 0;
    rewind(fichier);
    while (fread(&rdv, sizeof(RDV), 1, fichier) == 1) {
        if (strcmp(rdv.date,rdv1.date)==0 && rdv.heure == rdv1.heure  && rdv.code_medecin == rdv1.code_medecin ) {
            printf("Desole, vous devez choisir une autre date !\n");
            found = 1;
            break;
        }
    }
    if (! found) {
        fseek(fichier, 0, SEEK_END);
        fwrite(&rdv1, sizeof(RDV), 1, fichier);
        printf("Vous avez pris un rendez-vous. Soyez a l'heure et merci !\n");
    }
}


void annulerRDV(FILE * fichier){
    int idRDV;
    do{
        printf("Entrez l'identifiant du rendez-vous a annuler : l'id se compose 8 chiffres ! \n");
        scanf("%d", &idRDV);
    }while(count(idRDV) != 8) ;
    RDV rdv ;

    FILE* temp = fopen("tmp.dat", "w+");
    rewind(fichier);
    int found = 0;

    while (fread(&rdv, sizeof(RDV), 1, fichier) == 1) {
        if (rdv.id != idRDV) {
            fwrite(&rdv, sizeof(RDV), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(fichier);
    fclose(temp);
    remove("RDV.dat");
    rename("tmp.dat", "RDV.dat");
    if (found) {
        printf("Le rendez-vous est annule !\n");
    } else {
        printf("Le rendez-vous n'a pas ete trouve !\n");
    }
}

void modifierRDV (FILE * fichier){
    int idRDV;
    do{
        printf("Entrez l'identifiant du rendez-vous a annuler : l'id se compose 8 chiffres ! \n");
        scanf("%d", &idRDV);
    }while(count(idRDV) != 8) ;
    RDV rdv ;
    FILE* temp = fopen("tmp.dat", "w+");
    rewind(fichier);
    while (fread(&rdv, sizeof(RDV), 1, fichier) == 1) {
        if (rdv.id != idRDV) {
            fwrite(&rdv, sizeof(RDV), 1, temp);
        }
    }
    fclose(temp);
    remove("RDV.dat");
    rename("tmp.dat", "RDV.dat");
    printf("Modification en cours...\n");
    prendreRDV(fichier);
}

void visualiserRDVMedecin(FILE* fichierRDV) {
    int idMedecin;
    do{
        printf("Entrez l'identifiant du medecin pour visualiser ses RDV : ");
        scanf("%d", &idMedecin);
    }while(count(idMedecin)!= 8);

    RDV rdv;
    rewind(fichierRDV);
    int found = 0;

    printf("RDV programmes pour le medecin avec l'identifiant %d :\n", idMedecin);
    while (fread(&rdv, sizeof(RDV), 1, fichierRDV) == 1) {
        if (rdv.code_medecin == idMedecin) {
            printf("ID RDV: %d | Date: %s | Heure: %d | Code Patient: %d\n", rdv.id, rdv.date, rdv.heure, rdv.code_patient);
            found = 1;
        }
    }
    if (!found) {
        printf("Aucun RDV programme pour ce medecin.\n");
    }
}

void visualiserRDVParDate(FILE* fichierRDV) {
    char date[15];
    do{
        printf("Entrez la date pour visualiser les RDV programmes (format JJ/MM/AAAA) : ");
        scanf("%s", date);
    }while(strlen(date)!= 10 || !isperfect(date));

    RDV rdv;
    rewind(fichierRDV);
    int found = 0;

    printf("RDV programmes pour la date %s :\n", date);
    while (fread(&rdv, sizeof(RDV), 1, fichierRDV) == 1) {
        if (strcmp(rdv.date, date) == 0) {
            printf("ID RDV: %d | Medecin: %d | Heure: %d | Code Patient: %d\n", rdv.id, rdv.code_medecin, rdv.heure, rdv.code_patient);
            found = 1;
        }
    }
    if (!found) {
        printf("Aucun RDV programme pour cette date.\n");
    }
}



int main() {
    FILE* fichierPatients = ouvrirF("patient.dat", "a+");
    FILE* fichierMedecins = ouvrirF("medecin.dat", "a+");
    FILE* fichierRDV = ouvrirF("RDV.dat", "a+");
    int categories, choix;

    printf("Le systeme est defini comme suit :\n");
    printf("1 : la categorie des patients\n");
    printf("2 : la categorie des medecins\n");
    printf("3 : les RDV \n");
    printf("Entrez d'abord la categorie : ");
    scanf("%d", &categories);

    switch (categories) {
        case 1:
            printf("Le menu est comme suit : \n");
            printf("1 : ajouter un patient  \n");
            printf("2 : supprimer un patient \n");
            printf("Entrez votre choix : ");
            scanf("%d", &choix);
            switch (choix) {
                case 1:
                    ajouterPatient(fichierPatients);
                    break;
                case 2:
                    supprimerPatient(fichierPatients);
                    break;
                default:
                    printf("Choix invalide !\n");
                    break;
            }
            break;
        case 2:
            printf("Le menu est comme suit : \n");
            printf("1 : ajouter un medecin  \n");
            printf("2 : supprimer un medecin \n");
            printf("3 : recherche d'un medecin \n");
            printf("Entrez votre choix : ");
            scanf("%d", &choix);
            switch (choix) {
                case 1:
                    ajouterMedecin(fichierMedecins);
                    break;
                case 2:
                    supprimerMedecin(fichierMedecins);
                    break;
                case 3:
                    rechercheMedecin(fichierMedecins);
                    break;
                default:
                    printf("Choix invalide !\n");
                    break;
            }
            break;
        case 3:
            printf("Le menu est comme suit : \n");
            printf("1 : prise d'un rendez-vous  \n");
            printf("2 : annuler un rendez-vous \n");
            printf("3 : modifier un rendez-vous \n");
            printf("4 : visualiser les RDV programmes pour chaque medecin\n");
            printf("5 : visualiser les RDV programmes par date\n");
            printf("Entrez votre choix : ");
            scanf("%d", &choix);
            switch (choix) {
                case 1 :
                    prendreRDV(fichierRDV);
                    break;
                case 2 :
                    annulerRDV(fichierRDV);
                    break;
                case 3 :
                    modifierRDV(fichierRDV);
                    break;
                case 4:
                    visualiserRDVMedecin(fichierRDV);
                    break;
                case 5:
                    visualiserRDVParDate(fichierRDV);
                    break;
                default:
                    printf("Choix invalide !\n");
                    break;
            }
    }
    fclose(fichierPatients);
    fclose(fichierMedecins );
    fclose(fichierRDV);
    return 0;
}
