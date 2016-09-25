#ifndef FORMER_H_INCLUDED
#define FORMER_H_INCLUDED

#include "Formation.h"
#include "Class.h"
#include "Menu.h"

static int thisFo = 0;

typedef enum _level {Tutu, Nation, Region} Level_t;

typedef struct _Former
{
    int Fo_Act_Nbr; //Nombre des activites
    int Fo_FtN_Nbr; //Nombre des formations normale
    int Fo_FtA_Nbr; //Nombre des formation Accreditation
    int Fo_ClN_Nbr; //Nombre des classes normale
    int Fo_ClA_Nbr; //Nombre des classes d accreditaion

    char Fo_Code[8];
    char Fo_Name[20];
    char *Fo_Activity[15];

    Level_t Fo_Level;

    Formation_t *Fo_Ft_liste;
    Class_t     *Fo_Cl_liste;

    Formation_t *Ft_Have_Accr;
    Class_t     *Cl_Have_Accr;

    struct _Former *Fo_left;
    struct _Former *Fo_right;

} Former_t;


void Fo_Print(Former_t *,Class_t*);
void Fo_prifilPrint(Former_t *,Class_t*);
void Fo_Save(Former_t *);
void Ft_Filtrin(Formation_t *, Formation_t **, Formation_t **);
void Cl_Filtrin(Class_t *, Class_t **, Class_t **);
void Fo_CopyData(Former_t **, Former_t *);
void Fo_thisFormer();
void Fo_Gradute_My_Former(Class_t *,Former_t *,int);

Former_t* Fo_Save_1(Former_t *,FILE *);
Former_t *Fo_getData(Formation_t **,Class_t **);
Former_t *Fo_Add(Former_t *,Former_t *);
Former_t *Fo_Delete(Former_t *,Class_t **, const char *);
Former_t *Fo_Update(Former_t *, const char *, Formation_t **, Class_t **);
Former_t *Fo_Search(Former_t *, const char *);
Former_t *Fo_load(Formation_t *, Class_t *);
Former_t *Fo_FindMin(Former_t *);
void Fo_Print_Niveau(Former_t *Fo_root, Level_t niveau,Class_t*);
Former_t *Fo_Niveau(Former_t *,int*);
void Fo_Nbre_Eff_Region (Former_t * , char * ,int *);


#endif // FORMER_H_INCLUDED
