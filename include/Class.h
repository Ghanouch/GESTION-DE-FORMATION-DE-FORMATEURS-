#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int thisCl = 0;

typedef enum _Cl_Type {Normale, Acreditation} Cl_Type_t;

typedef struct _Class
{
	int Cl_Id;
	int Ft_key;
	char Cl_Name[10];
    int nbre_eff;
	Cl_Type_t Cl_TYPE;

	struct _Class *Cl_Next;

} Class_t;
void Cl_Print_ID(Class_t *,Class_t *);
void Cl_Print(Class_t *);
void Cl_ProfilPrint(Class_t *);
void Cl_Save(Class_t *);
void Cl_SetNbreEff(Class_t **,const int );
int Cl_trouve(Class_t *, int );

Class_t *Cl_SearchById(Class_t *,const int);
Class_t *Cl_load();
Class_t *Cl_CopyData(Class_t *);
Class_t *Cl_GetData(char c);
Class_t *Cl_Add(Class_t *,Class_t *);
Class_t *Cl_Delete(Class_t *, const int);
Class_t *Cl_Update(Class_t *, const int);
Class_t *Cl_Search(Class_t *, const int);
Class_t *Cl_Search_ByFtID(Class_t *, const int);
Class_t *Cl_Destroy(Class_t *);

int Cl_nbre_Eff(Class_t *,const int );

#endif // CLASS_H_INCLUDED
