#ifndef ENSEIGNANT_H_INCLUDED
#define ENSEIGNANT_H_INCLUDED
#include "Former.h"


static int thisEns = 0;

typedef struct _Enseigant
{

    int Ens_Ft_Nbr;
    int Ens_Cl_Nbr;

    char Ens_Code[8];
    char Ens_Name[20];

    Formation_t *Ens_Ft_liste; //Liste des formations
    Class_t     *Ens_Cl_liste; //Liste des classes

    Formation_t *Ft_Have_Accr;//Formation d'accreditation suivie
    Class_t     *Cl_Have_Accr;//Classe d'accreditation suivie

    int Part_Of_Formation[3];  // Les parties qu'il suivie durant la formation

    struct _Enseigant *left;
    struct _Enseigant *right;

} Enseignant_t;

//Return VRAI si l'enseignant a réalisé toute les conditions pour être Facilitateur
BOOLEAN Ens_Graduate(Enseignant_t *,Class_t *);
// fonction cherche l'enseignant qui s'occupe d'une classe , verifie et fait appel à TRANSFERT
void Ens_Gradute_My_Teachers(Former_t **,Enseignant_t *,Class_t *,int);
// fonction ajoute un enseignant avec les formateurs et reinitialise les valeurs
void Transfert(Former_t **, Enseignant_t *);
// Passage par adresse pour returner nombre d'enseignants
void  Return_Ens(int *);
// afficher le profil d'un enseignant
void Ens_Print_Profil(Enseignant_t *,Class_t*);
// afficher tous les enseignants
void Ens_Print(Enseignant_t *,Class_t*);
// Enrigistrer les enseignants dans un fichier binaire
void Ens_Save(Enseignant_t *);
// return 1 si l'enseignant a pu de suivre les 3 parties de sa formation
int Part_Fini(Enseignant_t *);
// recuperer les donnees d'un enseignant , en ajoutant la formation et la classe aux principaux
Enseignant_t *Ens_getData(Formation_t **,Class_t **);
// Ajouter un enseignant dans l'arbre des enseignant .
Enseignant_t *Ens_add(Enseignant_t *,Enseignant_t *);
// Rechercher un enseignant avec son code d'enrigistrement .
Enseignant_t *Ens_Search(Enseignant_t *, char *);
// Modifier le profil d'un enseignant ( Ajouter Formation , Compléter une partie .... )
void Ens_Update(Enseignant_t **,Former_t **,const char *,Formation_t **,Class_t ** );
// Enrigistrer la liste des ensignants
Enseignant_t* Ens_Save_1(Enseignant_t *,FILE *);
// charger la liste des enseignants à partir d'un fichier binaire
Enseignant_t *Ens_load(Formation_t *,Class_t *);


#endif // ENSEIGNANT_H_INCLUDED
