#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <windows.h>

#define console_cls   system("cls");   printf("\n");

#define console_pause; printf("\n\n");  system("PAUSE");

void Menu_Principal(int *, const int, const int, const int, const int, const int);
void Menu_Cl(int *);
void Menu_Fo(int *);
void Menu_Ens(int *);
void Menu_Ft(int *);
void Menu_Cd(int *);
void Menu_Upadte_Fo(int *);
void Menu_Upadte_Cd(int *);
void Menu_Upadte_Ens(int *);
void Menu_Cd_Profile(int *, const char *);
void Menu_Fo_Profile(int *, const char *);
void _MENU_(int *);
void Loading(int,int,int);
void REMARQUE(char*);

char *newPassowrd();



#endif // MENU_H_INCLUDED
