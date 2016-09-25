#include "Former.h"
#include "Formation.h"
#include "Menu.h"
#define EFF_CLASS_NORMAL 30
#define EFF_CLASS_AccrediTation 20
#define NBRE_CLASS_ACCR 3
void Return_Fo(int *Former)
{
    *Former=thisFo;
}


void Fo_Nbre_Eff_Etab(Former_t *Fo_root , char * Etabli,int *T)
{
 if(Fo_root == NULL ) return ;
 else
 {

  Formation_t *p=Fo_root->Fo_Ft_liste;
  while(p)
  {
      if( strcmp(p->Ft_Location.Establishment,Etabli) == 0)
      {
          if(Fo_root->Fo_Level == Tutu ) T[0]++;
          if(Fo_root->Fo_Level == Nation ) T[1]++;
          if(Fo_root->Fo_Level == Region ) T[2]++;

      }
      p=p->Next;
  }
      Fo_Nbre_Eff_Etab(Fo_root->Fo_left,Etabli,T);
      Fo_Nbre_Eff_Etab(Fo_root->Fo_right,Etabli,T);




 }
}

void Fo_Nbre_Eff_Region(Former_t *Fo_root , char * Etabli,int *T)
{
 if(Fo_root == NULL ) return ;
 else
 {
  Formation_t *p=Fo_root->Fo_Ft_liste;
  while(p)
  {
      if( strcmp(p->Ft_Location.Area,Etabli) == 0)
      {
          if(Fo_root->Fo_Level == Tutu ) T[0]++;
          if(Fo_root->Fo_Level == Nation ) T[1]++;
          if(Fo_root->Fo_Level == Region ) T[2]++;

      }
      p=p->Next;
  }
      Fo_Nbre_Eff_Region(Fo_root->Fo_left,Etabli,T);
      Fo_Nbre_Eff_Region(Fo_root->Fo_right,Etabli,T);




 }
}

void Fo_Nbre_Eff_Ville(Former_t *Fo_root , char * Etabli,int *T)
{
 if(Fo_root == NULL ) return ;
 else
 {
  Formation_t *p=Fo_root->Fo_Ft_liste;
  while(p)
  {
      if( strcmp(p->Ft_Location.City ,Etabli) == 0)
      {
          if(Fo_root->Fo_Level == Tutu ) T[0]++;
          if(Fo_root->Fo_Level == Nation ) T[1]++;
          if(Fo_root->Fo_Level == Region ) T[2]++;

      }
      p=p->Next;
  }
      Fo_Nbre_Eff_Ville(Fo_root->Fo_left,Etabli,T);
      Fo_Nbre_Eff_Ville(Fo_root->Fo_right,Etabli,T);




 }
}

void Fo_Nbre_Eff_Univ(Former_t *Fo_root , char * Etabli,int *T)
{
 if(Fo_root == NULL ) return ;
 else
 {
  Formation_t *p=Fo_root->Fo_Ft_liste;
  while(p)
  {
      if( strcmp(p->Ft_Location.University,Etabli) == 0)
      {
          if(Fo_root->Fo_Level == Tutu ) T[0]++;
          if(Fo_root->Fo_Level == Nation ) T[1]++;
          if(Fo_root->Fo_Level == Region ) T[2]++;

      }
      p=p->Next;
  }
      Fo_Nbre_Eff_Univ(Fo_root->Fo_left,Etabli,T);
      Fo_Nbre_Eff_Region(Fo_root->Fo_right,Etabli,T);




 }
}
// Quand le transfert se fait , le nombre de formateur s incremente
void Fo_thisFormer()
{
    thisFo++;
}

// Cette fonction test si le formateur a le droit de se graduer , le int nbre_classe pour prevoir le grade du formateur (nbre_classe=3) Facil...
// de plus pour être plus clair quand le formateur passe de niveau facilitateur on doit vider sa formation d accreditation et les classes
// qu il forme pour que la prochaine condition soit verifier pour les nouvelles conditions .
BOOLEAN Fo_Gradute(Class_t *Cl_head,Former_t *thisFo, int nbre_class)
{
    if(thisFo->Fo_ClN_Nbr >= nbre_class && thisFo->Cl_Have_Accr && thisFo->Fo_ClA_Nbr > 0 && thisFo->Fo_ClA_Nbr >= NBRE_CLASS_ACCR)
    {
        int verify=0;
        Class_t *P_Normal=NULL,*P_Accre=NULL;
        Cl_Filtrin(thisFo->Fo_Cl_liste,&P_Normal,&P_Accre);
        while(P_Normal && verify!=nbre_class )
        {
            if( Cl_nbre_Eff(Cl_head,P_Normal->Cl_Id) >= EFF_CLASS_NORMAL ) verify++;
            P_Normal = P_Normal->Cl_Next;
        }
        if( verify == nbre_class )
        {
            verify=0;
            while(P_Accre && verify != NBRE_CLASS_ACCR )
        {
            if( Cl_nbre_Eff(Cl_head,P_Accre->Cl_Id) >= EFF_CLASS_AccrediTation ) verify++;
            P_Accre = P_Accre->Cl_Next;
        }
             if( verify == NBRE_CLASS_ACCR )
                return TRUE;
        }
        return FALSE;
    }
    return FALSE;

}

// Quand le condidat vient pour se creer automatiquement le formateur  destinée a accepter le condidat s il verifie les condition => se gradute
// Si le formateur est facilitateur tuteur doit verifier leurs  condition => appel fonction avec nbre_class=3

void Fo_Gradute_My_Former(Class_t *Cl_head,Former_t *Fo_root,int IdClass)
{

    if(Fo_root == NULL) return ;
    else
    {
        Fo_Gradute_My_Former(Cl_head,Fo_root->Fo_right,IdClass);
        if( Cl_trouve(Fo_root->Fo_Cl_liste,IdClass) == 1)
        {
            if( Fo_Gradute(Cl_head,Fo_root,Fo_root->Fo_Level == Tutu ? 3 : 4) == TRUE )
            {
                /* char *nom=(char*)malloc(strlen(Fo_root->Fo_Name)*sizeof(char));
                 strcpy(nom,Fo_root->Fo_Name);
                 nom=(char*)realloc(nom,strlen(Fo_root->Fo_Name)+60);
                 char *TYPE =  (Fo_root->Fo_Level == Tutu )? " --Nation-- " : " --Region-- ";
                 char *string=strcat(strcat(strcat(nom," \t : Gradute as"),TYPE)," TuTeur In our System ");
                 REMARQUE(string); */

                char *TYPE =  (Fo_root->Fo_Level == Tutu )? " --Nation-- " : " --Region-- ";
                console_cls;
                textcolor('F');
                printf(" \n\n\n\t\t\tCongratulation to %s  : Admite in %s Leveel  \n",Fo_root->Fo_Name,TYPE);
                textcolor(7);
                Fo_root->Fo_Level =  (Fo_root->Fo_Level == Tutu )? Nation : Region ;
                if(Fo_root->Fo_Level == Nation)
               {
                Fo_root->Cl_Have_Accr = NULL;
                Fo_root->Ft_Have_Accr = NULL;
                Fo_root->Fo_ClA_Nbr = 0;
                Fo_root->Fo_FtA_Nbr = 0;
               }
                console_pause;
            }
        }
        Fo_Gradute_My_Former(Cl_head,Fo_root->Fo_left,IdClass);
    }

}



Former_t *Fo_Niveau(Former_t *Fo_root,int *T)
{
    if(Fo_root)
    {
    Fo_root->Fo_right=Fo_Niveau(Fo_root->Fo_right,T);
    Fo_root->Fo_left=Fo_Niveau(Fo_root->Fo_left,T);
    if(Fo_root->Fo_Level == Tutu)    T[0]++;
    else if(Fo_root->Fo_Level == Nation)  T[1]++;
    else  T[2]++;

    }

    return Fo_root;
}

void Fo_Print_Niveau(Former_t *Fo_root, Level_t niveau,Class_t *head)
{
    if(Fo_root == NULL) return ;
    Fo_Print_Niveau(Fo_root->Fo_right,niveau,head);

    if(Fo_root->Fo_Level == niveau)
        Fo_prifilPrint(Fo_root,head);

    Fo_Print_Niveau(Fo_root->Fo_left,niveau,head);
}



void Ft_Filtrin(Formation_t *liste, Formation_t **No_liste, Formation_t **Ac_liste)
{
    Formation_t *No = *No_liste;
    Formation_t *Ac = *Ac_liste;

    Formation_t *p = liste;

    while(p!=NULL)
    {
        //obj=p;
        Formation_t *obj = Ft_CopyData(p);

        if(obj->Ft_TYPE == Normal)
            No = Ft_Add(No,obj);
        else
            Ac = Ft_Add(Ac,obj);

        p = p->Next;
    }

    *No_liste = No;
    *Ac_liste = Ac;

    return ;
}

void Cl_Filtrin(Class_t *liste, Class_t **No_liste, Class_t **Ac_liste)
{
    Class_t *No=*No_liste;
    Class_t *Ac=*Ac_liste;

    Class_t *p=liste;

    while(p!=NULL)
    {
        //obj=p;
        Class_t *obj = Cl_CopyData(p);

        if(obj->Cl_TYPE == Normal)
            No=Cl_Add(No,obj);
        else
            Ac=Cl_Add(Ac,obj);

        p=p->Cl_Next;
    }

    *No_liste=No;
    *Ac_liste=Ac;

    return ;
}

void Fo_Print(Former_t *Fo_root,Class_t *Cl_head)
{
    if(Fo_root)
    {
        Fo_Print(Fo_root->Fo_left,Cl_head);
        Fo_Print(Fo_root->Fo_right,Cl_head);
        Fo_prifilPrint(Fo_root,Cl_head);
    }
    return ;

}

void Fo_prifilPrint(Former_t *Fo_root,Class_t *Cl_head)
{
    msg("                                     FORMER                                     ");

    textcolor('F'); printf("                                     About                                      "); textcolor(7);

    printf("Code : %s\n", Fo_root->Fo_Code);
    printf("Name : %s\n", Fo_root->Fo_Name);
    char *level;

    if(Fo_root->Fo_Level == Tutu)   level = "TUTO";
    if(Fo_root->Fo_Level == Nation) level = "NATION";
    if(Fo_root->Fo_Level == Region) level = "REGION";

    printf("Level : %s\n", level);

    printf("Acitivity Number : %d\n\n", Fo_root->Fo_Act_Nbr);

    int i;
    for(i = 0; i < Fo_root->Fo_Act_Nbr; i++) printf("Acitivity %d : %s\n", i+1, Fo_root->Fo_Activity[i]);

    Formation_t *Fo_Ft_Normal = NULL;
    Formation_t *Fo_Ft_Accre  = NULL;
    Class_t     *Fo_Cl_Normal = NULL;
    Class_t     *Fo_Cl_Accre  = NULL;

    Ft_Filtrin(Fo_root->Fo_Ft_liste, &Fo_Ft_Normal, &Fo_Ft_Accre);
    Cl_Filtrin(Fo_root->Fo_Cl_liste, &Fo_Cl_Normal, &Fo_Cl_Accre);

    textcolor('F'); printf("                                Normal Formation                                "); textcolor(7);

    printf("Normal Formation Number : %d\n", Fo_root->Fo_FtN_Nbr);
    Ft_Print(Fo_Ft_Normal);

    textcolor('F'); printf("                                  Normal Class                                  "); textcolor(7);

    printf("Normal Class Number : %d\n", Fo_root->Fo_ClN_Nbr);
    Cl_Print_ID(Fo_Cl_Normal,Cl_head);

    textcolor('F'); printf("                               Accreditate Formation                            "); textcolor(7);

    printf("Accreditate Formation Number : %d\n", Fo_root->Fo_FtA_Nbr);
    Ft_Print(Fo_Ft_Accre);

    textcolor('F'); printf("                                 Accreditate Class                              "); textcolor(7);

    printf("Accreditation Class Number : %d\n", Fo_root->Fo_ClA_Nbr);
    Cl_Print_ID(Fo_Cl_Accre,Cl_head);

    if(Fo_root->Ft_Have_Accr)
    {

        textcolor('F'); printf("                          Accreditate Formation Have                         "); textcolor(7);
        Ft_Print(Fo_root->Ft_Have_Accr);
        textcolor('C'); printf("                            Accreditate Class Have                           "); textcolor(7);
        Cl_Print_ID(Fo_root->Cl_Have_Accr,Cl_head);
    }
}

Former_t *Fo_getData(Formation_t **Ft_head,Class_t **Cl_head)
{
    int thisID;

    Former_t *New_Fo=(Former_t*)malloc(sizeof(Former_t));

    New_Fo->Fo_Ft_liste	=	NULL;
    New_Fo->Fo_Cl_liste	=	NULL;
    New_Fo->Fo_left		=	NULL;
    New_Fo->Fo_right	=	NULL;
    New_Fo->Ft_Have_Accr=   NULL;
    New_Fo->Cl_Have_Accr=   NULL;

    New_Fo->Fo_Act_Nbr	=	0;
    New_Fo->Fo_ClA_Nbr  =   0;
    New_Fo->Fo_FtA_Nbr  =   0;
    New_Fo->Fo_ClN_Nbr	=	1;
    New_Fo->Fo_FtN_Nbr	=	1;
    New_Fo->Fo_Level    =   Tutu;

    printf("Former code  : ");
    scanf("%s",New_Fo->Fo_Code);
    printf("Former Name : ");
    scanf("%s",New_Fo->Fo_Name);

  BB :  printf("\nGive the Id of the Formation wish you want informate : ");
    scanf("%d", &thisID);

    Formation_t *This_For = Ft_Search(*Ft_head, thisID);

   if(This_For && This_For->Ft_TYPE == Accreditation )
   {
       printf("You must choice a normal class !! \n");
       goto BB ;
   }
         if(This_For )
    {
        char rep;
        printf("\nWe find this Formation in our System  :\n");
        Ft_ProfilPrint(This_For);
        printf(" \n If you wana choise her : PRESS 1 -- else : 0  : ");
        fflush(stdin);
        rep=getchar();
        if(rep == '1')
        {
        Formation_t *newFt = Ft_CopyData(This_For);

        New_Fo->Fo_Ft_liste = newFt;
        }
        else { This_For = NULL ; }
    }

 if(! This_For)
    {
        printf("You Have to entry the informations about your new formation \n");
        printf("Write New information about your new formation \n");

        This_For = Ft_GetData('n');


        Formation_t *newFt = Ft_CopyData(This_For);

        New_Fo->Fo_Ft_liste = newFt;
        *Ft_head = Ft_Add(*Ft_head, This_For);
    }

    printf("\nWrite New information about your new class \n");

    Class_t *New_Cl = Cl_GetData('n');
    New_Cl->Ft_key  = This_For->Ft_Id;

    Class_t *thisCl = Cl_CopyData(New_Cl);

    New_Fo->Fo_Cl_liste = thisCl;

    *Cl_head = Cl_Add(*Cl_head, New_Cl);

    thisFo++;
    int r;
     printf(" 1- TuTu \t 2- Nation \t 3- Region \n");
     scanf("%d",&r);
     New_Fo->Fo_Level = r == 1 ? Tutu : r == 2 ? Nation : Region ;

    return New_Fo;
}


Former_t *Fo_Add(Former_t *Fo_root, Former_t *New_For)
{
    if(Fo_root == NULL) Fo_root=New_For;
    else
    {
        if(strcmp(New_For->Fo_Code,Fo_root->Fo_Code) > 0)
            Fo_root->Fo_right = Fo_Add(Fo_root->Fo_right, New_For);
        else
            Fo_root->Fo_left  = Fo_Add(Fo_root->Fo_left, New_For);

    }
    return Fo_root;
}


Former_t* Fo_FindMin(Former_t* Fo_root)
{
    if(Fo_root == NULL) return NULL;
    if(Fo_root->Fo_left) return Fo_FindMin(Fo_root->Fo_left);
    else return Fo_root;
}

void Fo_CopyData(Former_t **Fo, Former_t* thisFo)
{
    Former_t *newFo = *Fo;

    strcpy(newFo->Fo_Name, thisFo->Fo_Name);
    strcpy(newFo->Fo_Code, thisFo->Fo_Code);

    newFo->Fo_Level   = thisFo->Fo_Level;
    newFo->Fo_Act_Nbr = thisFo->Fo_Act_Nbr;
    newFo->Fo_FtN_Nbr = thisFo->Fo_FtN_Nbr;
    newFo->Fo_FtA_Nbr = thisFo->Fo_FtA_Nbr;
    newFo->Fo_ClN_Nbr = thisFo->Fo_ClN_Nbr;
    newFo->Fo_ClA_Nbr = thisFo->Fo_ClA_Nbr;

    int i;
    for(i = 0; i < thisFo->Fo_Act_Nbr; i++) strcpy(newFo->Fo_Activity[i], thisFo->Fo_Activity[i]);

    newFo->Fo_Ft_liste = thisFo->Fo_Ft_liste;
    newFo->Fo_Cl_liste = thisFo->Fo_Cl_liste;

    *Fo = newFo;
}

Former_t *Fo_Delete(Former_t *Fo_root, Class_t **Cl_liste, const char *data)
{
    if(Fo_root == NULL) return Fo_root;
    else if(strcmp(data, Fo_root->Fo_Code) < 0) Fo_root->Fo_left  = Fo_Delete(Fo_root->Fo_left, Cl_liste, data);
    else if(strcmp(data, Fo_root->Fo_Code) > 0) Fo_root->Fo_right = Fo_Delete(Fo_root->Fo_right,Cl_liste, data);
    else
    {
        Class_t *THISFo_Cl_liste  = NULL;
        //case 1 : no child
        if(Fo_root->Fo_left == NULL && Fo_root->Fo_right == NULL)
        {
            Fo_root->Fo_Ft_liste = Ft_Destroy(Fo_root->Fo_Ft_liste);
            THISFo_Cl_liste = Fo_root->Fo_Cl_liste;
            while(THISFo_Cl_liste)
            {
                *Cl_liste = Cl_Delete(*Cl_liste, Fo_root->Fo_Cl_liste->Cl_Id);
                 THISFo_Cl_liste = THISFo_Cl_liste->Cl_Next;
            }
            Fo_root->Fo_Cl_liste = Cl_Destroy(Fo_root->Fo_Cl_liste);
            free(Fo_root->Ft_Have_Accr);
            free(Fo_root->Cl_Have_Accr);

            free(Fo_root);
            thisFo--;
            Fo_root = NULL;
        }
        //case 2 : 1 child
        else if(Fo_root->Fo_left == NULL)
        {
            Former_t* temp = Fo_root;
            Fo_root = Fo_root->Fo_right;

            temp->Fo_Ft_liste = Ft_Destroy(temp->Fo_Ft_liste);
            THISFo_Cl_liste = Fo_root->Fo_Cl_liste;
            while(THISFo_Cl_liste)
            {
                *Cl_liste = Cl_Delete(*Cl_liste, Fo_root->Fo_Cl_liste->Cl_Id);
                 THISFo_Cl_liste = THISFo_Cl_liste->Cl_Next;
            }
            temp->Fo_Cl_liste = Cl_Destroy(temp->Fo_Cl_liste);

            //temp->Ft_Have_Accr= Ft_Destroy(&temp->Ft_Have_Accr);
            //temp->Cl_Have_Accr= Cl_Destroy(&temp->Cl_Have_Accr);

            free(Fo_root->Ft_Have_Accr);
            free(Fo_root->Cl_Have_Accr);

            free(temp);
            thisFo--;
        }
        else if(Fo_root->Fo_right == NULL)
        {
            Former_t *temp = Fo_root;
            Fo_root = Fo_root->Fo_left;

            temp->Fo_Ft_liste = Ft_Destroy(temp->Fo_Ft_liste);
            THISFo_Cl_liste = Fo_root->Fo_Cl_liste;
            while(THISFo_Cl_liste)
            {
                *Cl_liste = Cl_Delete(*Cl_liste, Fo_root->Fo_Cl_liste->Cl_Id);
                 THISFo_Cl_liste = THISFo_Cl_liste->Cl_Next;
            }
            temp->Fo_Cl_liste = Cl_Destroy(temp->Fo_Cl_liste);

            //temp->Ft_Have_Accr= Ft_Destroy(&temp->Ft_Have_Accr);
            //temp->Cl_Have_Accr= Cl_Destroy(&temp->Cl_Have_Accr);

            free(Fo_root->Ft_Have_Accr);
            free(Fo_root->Cl_Have_Accr);

            free(temp);
            thisFo--;
        }
        //case 3 : 2 child
        else
        {
            Former_t* temp = Fo_FindMin(Fo_root->Fo_right);
            Fo_CopyData(&Fo_root, temp);
            Fo_root->Fo_right = Fo_Delete(Fo_root->Fo_right, Cl_liste, temp->Fo_Code);
        }
    }

    return Fo_root;
}

Former_t *Fo_Update(Former_t *Fo_root,
                    const char *this,
                    Formation_t **Ft_Head,
                    Class_t ** Cl_Head)
{
    Former_t *thisFo = Fo_Search(Fo_root, this);

    if(thisFo)
    {
        int choice;
        int ftID;
        char txt[10];
        int Repet = 1;

        while(Repet)
        {

start :
            console_cls;
            Menu_Upadte_Fo(&choice);

            switch(choice)
            {
            case 1 :
                console_cls;
                printf("Old name : %s New pls : ", thisFo->Fo_Name);
                scanf("%s", txt);
                strcpy(thisFo->Fo_Name, txt);
                printf("\nSuccsed Opration\n");
                console_pause;
                break;
            case 2 :
                console_cls;
                if(thisFo->Fo_Level == Region)
                {

                    printf("The Activity title pls : ");
                    scanf("%s", txt);
                    /*if(thisFo->Fo_Act_Nbr == 0)
                    {
                        thisFo->Fo_Act_Nbr++;
                        thisFo->Fo_Activity[thisFo->Fo_Act_Nbr-1] = (char*)malloc(sizeof(char));
                        strcpy(thisFo->Fo_Activity[thisFo->Fo_Act_Nbr-1], txt);
                    }
                    else
                    {
                        thisFo->Fo_Act_Nbr++;
                        thisFo->Fo_Activity[thisFo->Fo_Act_Nbr-1] = (char*)malloc(sizeof(char));
                        strcpy(thisFo->Fo_Activity[thisFo->Fo_Act_Nbr-1], txt);
                    }*/

                    thisFo->Fo_Activity[thisFo->Fo_Act_Nbr] = (char*)malloc(50*sizeof(char));
                    strcpy(thisFo->Fo_Activity[thisFo->Fo_Act_Nbr], txt);
                    thisFo->Fo_Act_Nbr++;
                    printf("\nSuccsed Opration\n");
                }
                else printf("\nYou can't it is reserved for Region level\n");
                console_pause;
                break;
            case 3 :
                console_cls;
                 int thisID;
                char mode;
                rja3:

                do
                {


       normal:             printf("Give the type of formation (n-Normale, a-Acrredetation) : ");
                    fflush(stdin);
                    scanf("%c", &mode);
                                    }
                while(mode != 'n' && mode != 'a');
                int trouve=0;
                Formation_t *thisFt = NULL;
                Class_t     *thisCl = NULL;

                if(mode == 'a')
                {

                    printf("\nGive the Id of the Formation wish you want informate : ");
                    scanf("%d", &thisID);
                    Formation_t *This_For = Ft_Search(*Ft_Head, thisID);


         if(This_For && This_For->Ft_TYPE == Accreditation)
    {
        char rep;
        printf("\nWe find this Formation in our System  :\n");
        Ft_ProfilPrint(This_For);
        printf(" \n If you wana choise her : PRESS 1 -- else : 0  : ");
        fflush(stdin);
        rep=getchar();
        if(rep == '1')
        {
            trouve=1;
        Formation_t *newFt = Ft_CopyData(This_For);

       thisFo->Fo_Ft_liste = Ft_Add(thisFo->Fo_Ft_liste,newFt);
        thisFo->Fo_FtA_Nbr++;
        thisFo->Fo_ClA_Nbr++;
        thisCl = Cl_GetData('a');
        thisCl->Ft_key  = This_For->Ft_Id;

        }

        else { This_For = NULL ; }
                   /// if(thisFo->Fo_ClN_Nbr < 3) {printf("You have not the permission ! \n");
                                                   ///   goto rja3; }
      }

      if(This_For && This_For->Ft_TYPE == Normal)
      {
      printf("It's a normal class  !!\n ");
      goto normal;
      }///  else
                    ////{
   if(This_For == NULL )
   {


                    thisFt = Ft_GetData('a');
                    thisFo->Fo_FtA_Nbr++;

                    thisCl = Cl_GetData('a');
                    thisFo->Fo_ClA_Nbr++;
                    thisCl->Ft_key  = thisFt->Ft_Id;
                   /// }

    }
                }

                Formation_t *This_For=NULL;
                if(mode == 'n')
                {
          trouve=0;
                    printf("\nGive the Id of the Formation wish you want informate : ");
                    scanf("%d", &thisID);

                    This_For = Ft_Search(*Ft_Head, thisID);

      if(This_For && This_For->Ft_TYPE == Accreditation)
      {
      printf("It's a Accreditation class  !!\n ");
      goto normal;
      }
         if(This_For && This_For->Ft_TYPE == Normal)
    {
        char rep;
        printf("\nWe find this Formation in our System  :\n");
        Ft_ProfilPrint(This_For);
        printf(" \n If you wana choise her : PRESS 1 -- else : 0  : ");
        fflush(stdin);
        rep=getchar();
        if(rep == '1')
        {
            trouve=1;
        Formation_t *newFt = Ft_CopyData(This_For);

        thisFo->Fo_Ft_liste = Ft_Add(thisFo->Fo_Ft_liste,newFt);
         thisFo->Fo_FtN_Nbr++;
         thisFo->Fo_ClN_Nbr++;
         thisCl = Cl_GetData('n');
           thisCl->Ft_key  = This_For->Ft_Id;


        }
        else { This_For = NULL ; }
    }
    if(This_For == NULL)
    {

                    thisFt = Ft_GetData('n');
                    thisFo->Fo_FtN_Nbr++;

                    thisCl = Cl_GetData('n');
                    thisFo->Fo_ClN_Nbr++;
                    thisCl->Ft_key  = thisFt->Ft_Id;
                }
                }
                    if( Fo_Gradute(*Cl_Head,thisFo,3)==TRUE && thisFo->Fo_Level != Nation)
                    {
                        thisFo->Fo_Level = Nation;
                          textcolor(7);
                        printf("\nCongratulation Mr. %s , You are admite In Nation Level \n",thisFo->Fo_Name);
                          textcolor(8);
                    }
                    if( Fo_Gradute(*Cl_Head,thisFo,4)==TRUE && thisFo->Fo_Level!=Region )
                    {     thisFo->Fo_Level = Region;
                      textcolor(7);
                        printf("\nCongratulation Mr. %s , Now You are admite In Region Level  :) \n",thisFo->Fo_Name);
                          textcolor(8);
                    }

                //Add formation

                if(trouve==0) {
                Formation_t *newFt = Ft_CopyData(thisFt);

                thisFo->Fo_Ft_liste = Ft_Add(thisFo->Fo_Ft_liste, newFt);
               // Ft_Print(*Ft_Head);
               //printf("_________________________________________");

                *Ft_Head = Ft_Add(*Ft_Head, thisFt);
               // Ft_Print(*Ft_Head);
 }
                //Add class
                Class_t *newCl = Cl_CopyData(thisCl);

                thisFo->Fo_Cl_liste = Cl_Add(thisFo->Fo_Cl_liste, newCl);

                    *Cl_Head = Cl_Add(*Cl_Head, thisCl);


                console_pause;
                break;
            case 4 :
                console_cls;
                if(thisFo->Fo_Level != Region)
                {
                    printf("Give the Id of Formation : ");
                    scanf("%d", &ftID);
                    Formation_t *thisFt = Ft_Search(*Ft_Head, ftID);
                    if(thisFt && thisFt->Ft_TYPE == Accreditation)
                    {
                      //  thisFo->Ft_Have_Accr = (Formation_t*) malloc (sizeof(Formation_t));
                        thisFo->Ft_Have_Accr=Ft_CopyData(thisFt);
                        thisFo->Ft_Have_Accr->Next = NULL;
                 Class_Accr:
Cl_Print(Cl_Search_ByFtID(*Cl_Head,thisFt->Ft_Id));

                       Class_t *thisCl=NULL;
                        printf("Give the Id of Class :  (-1 Quit) " );

                        scanf("%d", &ftID);
                        thisCl = Cl_SearchById(*Cl_Head, ftID);
                        if(thisCl==NULL) {goto Class_Accr;  }
                        if(thisCl->Cl_TYPE != Acreditation ) { printf("it s a normal class ! \n "); goto Class_Accr; }
                        if(thisCl->Cl_TYPE == Acreditation)
                        {

                            Cl_SetNbreEff(&(*Cl_Head),thisCl->Cl_Id);
                             if( Fo_Gradute(*Cl_Head,thisFo,4)==TRUE && thisFo->Fo_Level!=Region )
                    {     thisFo->Fo_Level = Region;
                      textcolor(7);
                        printf("\nCongratulation Mr. %s , Now You are admite In Region Level  :) \n",thisFo->Fo_Name);
                          textcolor(8);
                    }
                            Fo_Gradute_My_Former(*Cl_Head,Fo_root,thisCl->Cl_Id);
                          //  thisFo->Cl_Have_Accr = (Class_t*) malloc (sizeof(Class_t));
                            thisFo->Cl_Have_Accr = Cl_CopyData( thisCl);
                            thisFo->Cl_Have_Accr->Cl_Next = NULL;
                        }
                    }
                    else printf("Formation doesn't exist \n");
                }
                else printf("\nHHHHHHHHHH TUTU\n");
                break;
            case 5 :
                Repet = 0;
                break;
            default :
                goto start;
            }
            //levele of thisFo be Region if ClN_nbr > 3 and he staded Acred formation and he open same accr formation
          /*  if(thisFo->Fo_ClN_Nbr > 3
                    && thisFo->Ft_Have_Accr != NULL
                    && thisFo->Fo_FtA_Nbr   != 0)
            {
                thisFo->Fo_Level = Region;
                printf("\nCongratulation Mr. %s , You are admite In Region Level \n",thisFo->Fo_Name);
            }*/
        }
    }

    else {  printf("This Former Doesn't exist \n"); }
    return Fo_root;
}

Former_t *Fo_Search(Former_t *Fo_root, const char *this)
{

    if(Fo_root==NULL)
        return NULL;
    if(strcmp(Fo_root->Fo_Code,this)>0)
        return Fo_Search(Fo_root->Fo_left,this);
    else if(strcmp(Fo_root->Fo_Code,this)<0)
        return Fo_Search(Fo_root->Fo_right,this);
    else
        return Fo_root;

}

void Fo_Save(Former_t *Fo_root)
{
    FILE *F=fopen("Former.dat","wb");
    fwrite(&thisFo,sizeof(thisFo),1,F);
    ///printf("%d lors du save  ThisFo  \n ",thisFo);
    Fo_Save_1(Fo_root,F);
    fclose(F);
}

Former_t* Fo_Save_1(Former_t *Fo_root,FILE *F)
{

    if(  Fo_root==NULL)  return ;
    else
    {
        int a;
        Fo_root->Fo_left = Fo_Save_1(Fo_root->Fo_left,F);
        Fo_root->Fo_right = Fo_Save_1(Fo_root->Fo_right,F);

        fwrite(&Fo_root->Fo_Act_Nbr,sizeof(int),1,F);

        fwrite(&Fo_root->Fo_ClA_Nbr,sizeof(int),1,F);
        fwrite(&Fo_root->Fo_ClN_Nbr,sizeof(int),1,F);

        fwrite(&Fo_root->Fo_FtN_Nbr,sizeof(int),1,F);
        fwrite(&Fo_root->Fo_FtA_Nbr,sizeof(int),1,F);

        fwrite(&Fo_root->Fo_Name,sizeof(Fo_root->Fo_Name),1,F);
        fwrite(&Fo_root->Fo_Code,sizeof(Fo_root->Fo_Code),1,F);
        fwrite(&Fo_root->Fo_Level,sizeof(Fo_root->Fo_Level),1,F);
        int k;
        char txt[20];
        for(k=0;k<Fo_root->Fo_Act_Nbr;k++)
        {

            strcpy(txt,Fo_root->Fo_Activity[k]);
            fwrite(&txt,sizeof(txt),1,F);

        }

        if(Fo_root->Ft_Have_Accr && Fo_root->Cl_Have_Accr)
        {
            a=1;
            fwrite(&a,sizeof(int),1,F);
            fwrite(&Fo_root->Ft_Have_Accr->Ft_Id,sizeof(int),1,F);
            fwrite(&Fo_root->Cl_Have_Accr->Cl_Id,sizeof(int),1,F);
        }
        else
        {
            a=0;
            fwrite(&a,sizeof(int),1,F);
        }

        Formation_t *p=Fo_root->Fo_Ft_liste;
        Class_t *q=Fo_root->Fo_Cl_liste;
        while(p)
        {
            fwrite(&p->Ft_Id,sizeof(int),1,F);

            p=p->Next;
        }
        while(q)
        {
            fwrite(&q->Cl_Id,sizeof(int),1,F);

            q=q->Cl_Next;
        }
    }
}

Former_t *Fo_load(Formation_t *Ft_head,Class_t *Cl_head)
{

    int i,count,a,j,Cl_id;
    int Id_Accre_Ft,Id_Accre_cl;
    Former_t *Fo_root=NULL;
    FILE *F=fopen("Former.dat","rb");
    fread(&count,sizeof(int),1,F);
    if(F==NULL) return NULL;
    else
    {
        for(i=0; i<count; i++)
        {
            Former_t *p=(Former_t*)malloc(sizeof(Former_t));

            fread(&p->Fo_Act_Nbr,sizeof(int),1,F);

            fread(&p->Fo_ClA_Nbr,sizeof(int),1,F);
            fread(&p->Fo_ClN_Nbr,sizeof(int),1,F);

            fread(&p->Fo_FtN_Nbr,sizeof(int),1,F);
            fread(&p->Fo_FtA_Nbr,sizeof(int),1,F);

            fread(&p->Fo_Name,sizeof(p->Fo_Name),1,F);
            fread(&p->Fo_Code,sizeof(p->Fo_Code),1,F);
            fread(&p->Fo_Level,sizeof(p->Fo_Level),1,F);

            int k;
            char txt[20];

            for(k=0;k<p->Fo_Act_Nbr;k++)
            {
                fread(&txt,sizeof(txt),1,F);
                p->Fo_Activity[k]=(char*)malloc(15*sizeof(char));
                strcpy(p->Fo_Activity[k],txt);
            }

            p->Ft_Have_Accr=NULL;
            p->Cl_Have_Accr=NULL;
            fread(&a,sizeof(int),1,F);
            if(a==1)
            {
                fread(&Id_Accre_Ft,sizeof(int),1,F);
                fread(&Id_Accre_cl,sizeof(int),1,F);
                p->Ft_Have_Accr=Ft_SearchById(Ft_head,Id_Accre_Ft);
                p->Cl_Have_Accr=Cl_SearchById(Cl_head,Id_Accre_cl);
            }
            int i_Ft=0,j_Cl=0;
            i_Ft= p->Fo_FtN_Nbr+p->Fo_FtA_Nbr;
            j_Cl= p->Fo_ClA_Nbr+p->Fo_ClN_Nbr;
           /*   if(p->Fo_Level == Nation)
          {
                i_Ft+=NBRE_CLASS_ACCR;
                j_Cl+= NBRE_CLASS_ACCR;
            } */
            int Ft_id;
            p->Fo_Ft_liste=NULL;
            for(j=0; j<i_Ft; j++)
            {
                Formation_t *THISFT=NULL;
                fread(&Ft_id,sizeof(int),1,F);
                THISFT=Ft_SearchById(Ft_head,Ft_id);
                //printf("%d formation 1 \n",Ft_id);   console_pause;
                p->Fo_Ft_liste=Ft_Add(p->Fo_Ft_liste,THISFT);

            }
            p->Fo_Cl_liste=NULL;
            for(j=0; j<j_Cl; j++)
            {
                Class_t *THISCL=NULL;
                fread(&Cl_id,sizeof(int),1,F);
                THISCL=Cl_SearchById(Cl_head,Cl_id);
                ///printf("%d Classe 1 \n",Cl_id);console_pause;
                p->Fo_Cl_liste=Cl_Add(p->Fo_Cl_liste,THISCL);
            }

            p->Fo_right=NULL;
            p->Fo_left=NULL;

            Fo_root=Fo_Add(Fo_root, p);
        }


        thisFo=count;
        fclose(F);
        return Fo_root;
    }

}


