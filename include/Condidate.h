#ifndef CONDIDATE_H_INCLUDED
#define CONDIDATE_H_INCLUDED

#include "Formation.h"
#include "Class.h"
#include "Menu.h"
#include "Former.h"
#include "Enseignant.h";:


static int thisCd = 0;

typedef struct _Date
{
    int DD;
    int MM;
    int YY;
} Date_t;

typedef struct _Condidat
{
    char Cd_Code[8];
    char Cd_FirstName[20];
    char Cd_LastName[20];

    int Cd_Id;

    Date_t Cd_RegDate;

    Formation_t *Cd_Formation;
    Class_t     *Cd_Class;

    struct _Condidat *Cd_left;
    struct _Condidat *Cd_right;

} Condidat_t;

void Cd_Print(Condidat_t *);
void Cd_Save(Condidat_t *);
void Cd_profilPrint(Condidat_t *);

Condidat_t* Cd_Save_1(Condidat_t *, FILE *);
Condidat_t *Cd_load(Formation_t *,Class_t *);
Condidat_t *Cd_CopyData(Condidat_t *);
Condidat_t *Cd_FindMin(Condidat_t *);
Condidat_t *Cd_getData(Former_t **,Enseignant_t *,Formation_t *, Class_t **);
Condidat_t *Cd_Add(Condidat_t *, Condidat_t *);
Condidat_t *Cd_Delete(Condidat_t *, const char *);
Condidat_t *Cd_Update(Condidat_t *, const char *);
Condidat_t *Cd_Search(Condidat_t *, const char *);


#endif // CONDIDATE_H_INCLUDED
