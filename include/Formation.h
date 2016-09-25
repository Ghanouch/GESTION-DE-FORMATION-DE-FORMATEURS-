#ifndef FORMATION_H_INCLUDED
#define FORMATION_H_INCLUDED

#include<stdio.h>

static int thisFt = 0;

typedef struct _Local
{
    char Area[20];
    char City[20];
    char University[30];
    char Establishment[30];

} Local_t;

typedef enum Ft_Type {Normal, Accreditation} Ft_Type_t;

typedef struct _Formation
{
    int Ft_Id;
    int Ft_Duration;

    char Ft_Name[15];

    Local_t Ft_Location;

    Ft_Type_t Ft_TYPE;
    int Ft_Occ;

    struct _Formation *Next;

} Formation_t;

void Ft_Save(Formation_t *);
void Ft_Print(Formation_t *);
void Ft_ProfilPrint(Formation_t *);

Formation_t *Ft_load();

Formation_t *Ft_SearchById(Formation_t *, const int);
Formation_t *Ft_CopyData(Formation_t *);
Formation_t *Ft_GetData(char c);
Formation_t *Ft_Add(Formation_t *,Formation_t *);
Formation_t *Ft_Delete(Formation_t *, const int);
Formation_t *Ft_Update(Formation_t *, const int);
Formation_t *Ft_Search(Formation_t *, const int);
Formation_t *Ft_fRead();
Formation_t *Ft_Destroy(Formation_t *);


#endif // FORMATION_H_INCLUDED
