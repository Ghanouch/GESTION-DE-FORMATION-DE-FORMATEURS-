#include "Menu.h"
#include "Class.h"
#include "Formation.h"
#include "Former.h"
#include "Condidate.h"
#include "Enseignant.h"

Class_t     *Cl_liste = NULL;
Formation_t *Ft_liste = NULL;
Former_t    *Fo_BST   = NULL;
Condidat_t  *Cd_BST   = NULL;
Enseignant_t *Ens_BST = NULL;

char thisCode[15];
int thisId, totalEns=0, totalCd=0, totalFo=0, totalFt=0, totalCl=0;

void Cl_proces()
{
    int repet = 1;


    int Cl_choice;
    while(repet)
    {
        console_cls;
        fflush(stdin);
        Menu_Cl(&Cl_choice);
        switch(Cl_choice)
        {
        case 1 :
            console_cls;
            Cl_Print(Cl_liste);
            console_pause;
            break;

        case 2 :
            console_cls;
            printf("Write Id of Class : ");
            fflush(stdin);
            scanf("%d", &thisId);
            Cl_liste = Cl_Update(Cl_liste, thisId);
            console_pause;
            break;

        case 3 :
            console_cls;
            printf("Write Id of Class : ");
            fflush(stdin);
            scanf("%d", &thisId);
            Class_t *Cl = Cl_Search(Cl_liste, thisId);
            if(Cl) {  printf("EXIST"); Cl_ProfilPrint(Cl); console_pause; }
            else printf("NOT EXIST");
            console_pause;
            break;

            /*case 4 :
                console_cls;
                printf("Write Id of Class : ");
                fflush(stdin);
                scanf("%d", &thisId);
                Cl_liste = Cl_Delete(Cl_liste, thisId);
                console_pause;
                break;*/

        case 4 :
            repet = 0;
        }
    }
}


void Cd_proces()
{
    int repet = 1;
    int Cd_choice;

    while(repet)
    {
        console_cls;
        Menu_Cd(&Cd_choice);

        switch(Cd_choice)
        {
        case 1 :
            console_cls;
            Class_t *newCd = Cd_getData(&Fo_BST,Ens_BST,Ft_liste, &Cl_liste);
            Return_Cd(&totalCd);
            Cd_BST = Cd_Add(Cd_BST, newCd);
            console_pause;
            break;
        case 2 :
            console_cls;
            Cd_Print(Cd_BST);
            console_pause;
            break;
        case 3 :
            console_cls;
            printf("\nGive the Code of Condidate : ");
            scanf("%s", thisCode);
            Cd_BST = Cd_Update(Cd_BST, thisCode);
            console_pause;
            break;
        case 4 :
            console_cls;
            printf("\nGive the Code of Condidate : ");
            scanf("%s", thisCode);
            Condidat_t *Cd = Cd_Search(Cd_BST, thisCode);
            if(Cd) {  Cd_profilPrint(Cd);    }
            else printf("\nNo Exist\n");
            console_pause;
            break;
        case 5 :
            console_cls;
            printf("\nGive the Code of Condidate : ");
            scanf("%s", thisCode);
            Cd_BST = Cd_Delete(Cd_BST, thisCode);
            Return_Cd(&totalCd);
            console_pause;
            break;
        case 6 :
            repet = 0;
            Return_Fo(&totalFo);

        }
    }
}

void Charger_Class()
{
    Class_t *p=Cl_liste;
    while(p)
    {

        if(p->Cl_TYPE == Normal) p->nbre_eff = 30;
        if(p->Cl_TYPE == Accreditation) p->nbre_eff = 20;
        if(p->Cl_Id == 62) p->nbre_eff = 29;
        if(p->Cl_Id == 78) p->nbre_eff = 20;
         if(p->Cl_Id == 66) p->nbre_eff = 29;
        if(p->Cl_Id == 67) p->nbre_eff = 29;
         if(p->Cl_Id == 75) p->nbre_eff = 18;
          if(p->Cl_Id == 44) p->nbre_eff = 18;

            p=p->Cl_Next;
    }
}

void Fo_proces()
{


    int repet = 1;
    int Fo_choice;
    while(repet)
    {
        console_cls;
        Menu_Fo(&Fo_choice);

        switch(Fo_choice)
        {
        case 6 :
            console_cls;
            Former_t * thisFo = Fo_getData(&Ft_liste, &Cl_liste);
            Return_Cl(&totalCl);
            Return_Fo(&totalFo);
            Return_Ft(&totalFt);
            Fo_BST = Fo_Add(Fo_BST, thisFo);
            console_pause;
            break;
        case 1 :
            console_cls;
            Fo_Print(Fo_BST,Cl_liste);
            console_pause;
            break;
        case 2 :
            console_cls;
            printf("Write Code of Former : ");
            fflush(stdin);
            scanf("%s", thisCode);
            Fo_BST = Fo_Update(Fo_BST,thisCode, &Ft_liste, &Cl_liste);
            Return_Cl(&totalCl);
            Return_Ft(&totalFt);
            console_pause;
            break;
        case 3 :
            console_cls;
            printf("Write Code of Former : ");
            fflush(stdin);
            scanf("%s", thisCode);
            Former_t *Fo = Fo_Search(Fo_BST, thisCode);
            if(Fo)
            {
                Fo_prifilPrint(Fo,Cl_liste);

            }
            else printf("NOT EXIST");
            console_pause;
            break;
        case 4 :
            console_cls;
            printf("Write Code of Former : ");
            fflush(stdin);
            scanf("%s", thisCode);
            Fo_BST = Fo_Delete(Fo_BST, &Cl_liste, thisCode);
            Return_Cl(&totalCl);
            Return_Fo(&totalFo);
            Return_Ft(&totalFt);
            console_pause;
            break;
        case 5 :
            repet = 0;
        }
    }
}

void Ft_proces()
{

    int repet = 1;
    int Ft_choice;

    while(repet)
    {
        console_cls;
        Menu_Ft(&Ft_choice);

        switch(Ft_choice)
        {

        case 1 :
            console_cls;
            Ft_Print(Ft_liste)
            console_pause;
            break;
        case 2 :
            console_cls;
            printf("Write Id of Formation : ");
            fflush(stdin);
            scanf("%d", &thisId);
            Ft_liste = Ft_Update(Ft_liste, thisId);
            console_pause;
            break;
        case 3 :
            console_cls;
            printf("Write Id of Formation : ");
            fflush(stdin);
            scanf("%d", &thisId);
            Formation_t *C = Ft_Search(Ft_liste, thisId);
            if(C)
            {
              Ft_ProfilPrint(C);
            }
            else printf("NOT EXIST");
            console_pause;
            break;
        /*case 4 :
            console_cls;
            printf("Write Id of Formation : ");
            fflush(stdin);
            scanf("%d", &thisId);
            Ft_liste = Ft_Delete(Ft_liste, thisId);
            console_pause;
            break;*/
        case 4 :
            repet = 0;
        }
    }
}

void STATISTICS()
{
    int ST_choice;
    int *T;
    T=(int)calloc(T,3*sizeof(int));
    Fo_BST=Fo_Niveau(Fo_BST,T);
    Menu_STATISTICS(&ST_choice,T[0],T[1],T[2]);
    switch(ST_choice)
    {
    case 1 :
        console_cls;
        Fo_Print_Niveau(Fo_BST, Tutu,Cl_liste);
        console_pause;
        break;
    case 2 :
        console_cls;
        Fo_Print_Niveau(Fo_BST, Nation,Cl_liste);
        console_pause;
        break;
    case 3 :
        console_cls;
        Fo_Print_Niveau(Fo_BST, Region,Cl_liste);
        console_pause;
        break;
    case 4 :
        console_cls;
        break;
    default:
        console_cls;
    }
}

void Ens_proces()
{
    int REPET=1;
    int choice_Ens;
    char *thiscode[15];
    do
    {
        console_cls;
        Menu_Ens(&choice_Ens);
        switch(choice_Ens)
        {
        case 1:
            console_cls;
            Enseignant_t * thisEns = Ens_getData(&Ft_liste, &Cl_liste);
            Return_Cl(&totalCl);
            Return_Ens(&totalEns);
            Return_Ft(&totalFt);
            Ens_BST = Ens_add(Ens_BST, thisEns);
            console_pause;
            break;
        case 2:
            console_cls;
            char thisCode[10];
            printf("Write the Code of Teacher  : ");
            fflush(stdin);
            scanf("%s", thisCode);
            if( Ens_Search(Ens_BST,thisCode) != NULL )
            {
                Ens_Update(&Ens_BST,&Fo_BST,thisCode, &Ft_liste, &Cl_liste);
                Return_Cl(&totalCl);
                Return_Ft(&totalFt);
                Return_Fo(&totalFo);

                console_pause;
            }
            else
                printf("Sorry , this id of Teacher doesn't exist ! \n");
            console_pause;
            break;
        case 3:
            console_cls;
            Ens_Print(Ens_BST,Cl_liste);
            console_pause;
            break;
            case 4:
                console_cls;
             printf("Write Code of Teacher : ");
            fflush(stdin);
            scanf("%s", thiscode);
            Enseignant_t *Ens = Ens_Search(Ens_BST,thiscode);
            if(Ens)
            {
              Ens_Print_Profil(Ens,Cl_liste);
            }
            else printf("NOT EXIST");
            console_pause;
            break;
        case 5:
            REPET=0;
            break;
        default:
            console_cls;
        }
    }
    while(REPET==1);

}

void Affe()
{

    int rep;
    char Estab[20];
    int *S=(int*)calloc(S,3*sizeof(int));
    S[0]=S[1]=S[2]=0;
    console_cls;
    textcolor(8);printf("\t\t\t1-Par Etablissement : \n");
	textcolor(2);printf("\t\t\t2-Par Region        : \n");
	textcolor(3);printf("\t\t\t3-Par Ville         : \n");
	textcolor(4);printf("\t\t\t4-Par University    : \n");
	textcolor(3);printf("\t\t\tDonnez votre choix  : \n");
	scanf("%d",&rep);



switch(rep)
{

  case 1 : printf(" Donnez le nom de l'etablissement \t :");
        scanf("%s",Estab);
        S[0]=S[1]=S[2]=0;
        Fo_Nbre_Eff_Etab(Fo_BST,Estab,S);
        if( S[0] == 0 && S[1] == 0 && S[2] == 0)
        {
            REMARQUE("We have not a former in this Establishment ") ;

        }
        else
        {
            printf("\t\t\tEFFECTIF IN  %s \n\n",Estab);
            printf("\t\t\tFacilitator  : %d \n",S[0]);
            printf("\t\t\tNational     : %d \n", S[1]);

            printf("\t\t\tRegional     : %d \n\n", S[2]);
            console_pause;

        }
        break;
  case 2 : printf(" Donnez le nom de la Region \t :");
        scanf("%s",Estab);


        S[0]=S[1]=S[2]=0;
        Fo_Nbre_Eff_Region(Fo_BST,Estab,S);
        if( S[0] == 0 && S[1] == 0 && S[2] == 0)
        {
            REMARQUE("We have not a former in this Region ") ;
            console_pause;
        }
        else
        {
            printf("\t\t\tEFFECTIF IN  %s \n\n",Estab);
            printf("\t\t\tFacilitator  : %d \n",S[0]);
            printf("\t\t\tNational     : %d \n", S[1]);

            printf("\t\t\tRegional     : %d \n\n", S[2]);
            console_pause;

        }
        break;

case 3 : printf(" Donnez le nom de la ville \t :");
        scanf("%s",Estab);
        S[0]=S[1]=S[2]=0;

        Fo_Nbre_Eff_Ville(Fo_BST,Estab,S);
        if( S[0] == 0 && S[1] == 0 && S[2] == 0)
        {
            REMARQUE("We have not a former in this City  ") ;
            console_pause;
        }
        else
        {
            printf("\t\t\tEFFECTIF IN  %s \n\n",Estab);
            printf("\t\t\tFacilitator  : %d \n",S[0]);
            printf("\t\t\tNational     : %d \n", S[1]);

            printf("\t\t\tRegional     : %d \n\n", S[2]);
            console_pause;

        }
        break;

case 4 : printf(" Donnez le nom de l'universite \t :");
        scanf("%s",Estab);
        S[0]=S[1]=S[2]=0;

        Fo_Nbre_Eff_Univ(Fo_BST,Estab,S);
        if( S[0] == 0 && S[1] == 0 && S[2] == 0)
        {
            REMARQUE("We have not a former in this University ") ;
console_pause;        }
        else
        {
            printf("\t\t\tEFFECTIF IN  %s \n\n",Estab);
            printf("\t\t\tFacilitator  : %d \n",S[0]);
            printf("\t\t\tNational     : %d \n", S[1]);

            printf("\t\t\tRegional     : %d \n\n", S[2]);
            console_pause;

        }
        break;

}


}


void Admin_Proces()
{
    int REPET = 1;
    int AdminChoice;
    while(REPET)
    {
        console_cls;
        Menu_Principal(&AdminChoice, totalFt, totalCl, totalCd, totalFo,totalEns);
        switch(AdminChoice)
        {
        case 1 :
            Cl_proces();
            break;
        case 2 :
            Cd_proces();
            break;
        case 3 :
            Ft_proces();
            break;
        case 4 :
            Fo_proces();
            break;
        case 5 :
            STATISTICS();
            break;
        case 6 :
            Ens_proces();
            break;
        case 7 :
            REPET = 0;
            break;
         case 8 :
            Affe();
            break;

        default:
            console_cls;
        }
    }
}

void Fo_Profile()
{
    console_cls;
    printf("\n\n\n\n\n\n");
    printf("\n\n\t\t\tPassword : ");
    char *Password = newPassword();

    Former_t *My = Fo_Search(Fo_BST, Password);

    if(My != NULL)
    {
        int choice;
        int rep = 1;
        while(rep)
        {
            console_cls;
            Menu_Fo_Profile(&choice, My->Fo_Code);
            switch(choice)
            {
            case 1 :
                console_cls;
                Fo_prifilPrint(My,Cl_liste);
                console_pause;
                break;
            case 2 :
                console_cls;
                Fo_BST = Fo_Update(Fo_BST, My->Fo_Code, &Ft_liste, &Cl_liste);
                console_pause;
                break;
            //case 3 : console_cls; console_pause; break;
            case 3 :
                rep = 0;
                break;
            default:
                console_cls;
            }
        }
    }
    else printf("Password Inccorect");

}

void Cd_Profile()
{
    console_cls;
    printf("\n\n\n\n\n\n");
    printf("\n\n\t\t\tPassword : ");
    char *Password = newPassword();

    Condidat_t *My = Cd_Search(Cd_BST, Password);

    if(My != NULL)
    {
        int rep = 1;
        while(rep)
        {
            console_cls;
            int choice;
            Menu_Cd_Profile(&choice, My->Cd_Code);
            switch(choice)
            {
            case 1 :
                console_cls;
                Cd_profilPrint(My);
                console_pause;
                break;
            case 2 :
                console_cls;
                Cd_Update(Cd_BST, My->Cd_Code);
                console_pause;
                break;
            //case 3 : console_cls; console_pause; break;
            case 3 :
                rep = 0;
                break;
            default:
                console_cls;
            }
        }
    }
    else printf("Password Inccorect");
}

void Admin()
{
    char thisLogin[10], thisPassword[10], Login[10], *Password;
    FILE *adminFile = NULL;
    adminFile = fopen("AdminFile.admin", "rb");
    if(adminFile)
    {
        do
        {
            console_cls;
            printf("\n\n\n\n\n\n");
            printf("\t\t\tLogin    : ");
            scanf("%s", Login);
            printf("\n\n\t\t\tPassword : ");
            Password = newPassword();
            //Loading(1, 3, 500);
            fread(&thisLogin,    sizeof(thisLogin),    1, adminFile);
            char Pass[10];
            fread(&Pass, sizeof(Pass), 1, adminFile);
            strcpy(thisPassword, Pass);
            fclose(adminFile);
            if(strcmp(thisLogin, Login) == 0 && strcmp(thisPassword, Password) == 0) Admin_Proces();
            else
            {
                REMARQUE("Login OR Password inccorect");
            }
        }
        while(strcmp(thisLogin, Login) != 0 && strcmp(thisPassword, Password) != 0);
    }
    else
    {
        console_cls;
        printf("\n\n\n\tNO ROOT SAVE YOUR SELF AS ROOT");
        printf("\n\n\n");
        printf("\t\t\t\tLogin    : ");
        scanf("%s", Login);
        printf("\n\n\t\t\t\tPassword : ");
        Password  = newPassword();
        adminFile = fopen("AdminFile.admin", "wb");
        fwrite(&Login,    sizeof(Login),    1, adminFile);
        char Pass[10];
        strcpy(Pass, Password);
        fwrite(&Pass, sizeof(Pass),  1, adminFile);
        fclose(adminFile);
        REMARQUE("SUCCED OPERATION YOU ARE AN ADMIN");
    }
}

void LOAD_DATA()
{

    Ft_liste = Ft_load();
    Cl_liste = Cl_load();
    // Class_t *thist = Cl_Search_1(Cl_liste,62);
   // thist->nbre_eff = 29;
    Cd_BST   = Cd_load(Ft_liste, Cl_liste);
    Fo_BST   = Fo_load(Ft_liste, Cl_liste);
    Ens_BST  = Ens_load(Ft_liste,Cl_liste);


  //  Charger_Class();



    Return_Cd(&totalCd);
    Return_Cl(&totalCl);
    Return_Fo(&totalFo);
    Return_Ft(&totalFt);
    Return_Ens(&totalEns);
}

void SAVE_DATA()
{
    Ft_Save(Ft_liste);
    Cl_Save(Cl_liste);
    Cd_Save(Cd_BST);
    Fo_Save(Fo_BST);
    Ens_Save(Ens_BST);
}

int main()
{
    system("title MANGEMENT OF FORMERS FORMATIONS");

    LOAD_DATA();

    //  Loading(3, 3, 500);
    int rep = 1, choice;
    while(rep)
    {
        console_cls;
        _MENU_(&choice);

        switch(choice)
        {
        case 1 : /*Loading(1, 3, 500);*/
            Admin();
            break;
        case 2 : /*Loading(1, 3, 500);*/
            Fo_Profile();
            break;
        case 3 : /*Loading(1, 3, 500);*/
            Cd_Profile();
            break;
        case 4 :
            rep = 0;
        default:
            console_cls;
        }
    }

    SAVE_DATA();

    return 0;
}
