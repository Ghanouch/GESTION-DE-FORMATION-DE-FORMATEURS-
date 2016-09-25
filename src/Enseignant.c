#include "Formation.h"
#include "Class.h"
#include "Enseignant.h"
#include "Menu.h"

#define EFF_CLASS_NORMAL 21
void  Return_Ens(int *total)
{
    *total=thisEns;
}

void Ens_Gradute_My_Teachers(Former_t **Fo_root,Enseignant_t *Ens_root,Class_t *Cl_head,int IdClass)
{

   if(Ens_root == NULL) return ;
   else
    {

     Ens_Gradute_My_Teachers(&(*Fo_root),Ens_root->left,Cl_head,IdClass);

     if( Cl_trouve(Ens_root->Ens_Cl_liste,IdClass) == 1)
     {
     if( Ens_Graduate(Ens_root,Cl_head) == TRUE )
     {
         char *nom = (char*)malloc(strlen(Ens_root->Ens_Name)*sizeof(char));
         strcpy(nom,Ens_root->Ens_Name);
         char *string=strcat(nom," \t : Gradute as FaciliTateur TuTeur In our System ");
         REMARQUE(string);
         Transfert(&(*Fo_root),Ens_root);
         console_pause;
         console_cls;
     }
     }
     Ens_Gradute_My_Teachers(&(*Fo_root),Ens_root->right,Cl_head,IdClass);
    }

}

BOOLEAN Ens_Graduate(Enseignant_t *thisEns,Class_t *Cl_head)
{
    if(thisEns->Ens_Cl_Nbr == 3 && thisEns->Ft_Have_Accr && Part_Fini(thisEns))
    {
        int ClassSupTrente=0;
        Class_t *p=thisEns->Ens_Cl_liste;
        while(p)
        {
            if(Cl_nbre_Eff(Cl_head,p->Cl_Id) >= EFF_CLASS_NORMAL)
                ClassSupTrente++;
            p=p->Cl_Next;
        }
        if(ClassSupTrente<3) return FALSE;
        else return TRUE;
    }
    return FALSE;
}

void Transfert(Former_t **For_root, Enseignant_t *this_Ens)
{

   Former_t *New_Fo = (Former_t*)malloc(sizeof(Former_t));
    New_Fo->Fo_Ft_liste	=	NULL;
    New_Fo->Fo_Cl_liste	=	NULL;
    New_Fo->Fo_left		=	NULL;
    New_Fo->Fo_right	=	NULL;
    New_Fo->Ft_Have_Accr=   NULL;
    New_Fo->Cl_Have_Accr=   NULL;

    New_Fo->Fo_Act_Nbr	=	0;
    New_Fo->Fo_ClA_Nbr  =   0;
    New_Fo->Fo_FtA_Nbr  =   0;
    New_Fo->Fo_ClN_Nbr	=	0;
    New_Fo->Fo_FtN_Nbr	=	0;
    New_Fo->Fo_Level    =   Tutu;


    strcpy(New_Fo->Fo_Name,this_Ens->Ens_Name);
    strcpy(New_Fo->Fo_Code,this_Ens->Ens_Code);
    Fo_thisFormer();
    *For_root=Fo_Add(*For_root,New_Fo);

}

int Part_Fini(Enseignant_t *this_Ens)
{
    int i=0;
    while(i<3 && this_Ens->Part_Of_Formation[i]==1 )
        i++;
    if(i==3) return 1;   // En cas Ou l enseignant a fini les 3 parties
    else return 0;
}
Enseignant_t *Ens_getData(Formation_t **Ft_head,Class_t **Cl_head)
{

    int thisID;

    Enseignant_t *New_Ens=(Enseignant_t*)malloc(sizeof(Enseignant_t));

    New_Ens->Part_Of_Formation[0]=0;
    New_Ens->Part_Of_Formation[1]=0;
    New_Ens->Part_Of_Formation[2]=0;

    New_Ens->Ens_Ft_Nbr=1;
    New_Ens->Ens_Cl_Nbr=1;
    New_Ens->Ens_Ft_liste=NULL;
    New_Ens->Ens_Cl_liste=NULL;
    New_Ens->Ft_Have_Accr=NULL;
    New_Ens->Cl_Have_Accr=NULL;
    New_Ens->left=NULL;
    New_Ens->right=NULL;


    printf("Teacher code  : ");
    scanf("%s",New_Ens->Ens_Code);
    printf("Teacher Name  : ");
    scanf("%s",New_Ens->Ens_Name);

    printf("\n\nGive the Id of the Formation that you wish teach : ");
    scanf("%d", &thisID);

    Formation_t *This_For = Ft_Search(*Ft_head, thisID);

    if(This_For)
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

        New_Ens->Ens_Ft_liste = newFt;
        }
        else { This_For = NULL ; }
    }

    if(! This_For)
    {
        textcolor('F');
        printf("\n\nWrite New information about your new formation\n\n");
        textcolor(7);
        This_For = Ft_GetData('n');


        Formation_t *newFt = Ft_CopyData(This_For);

        New_Ens->Ens_Ft_liste = newFt;
        *Ft_head = Ft_Add(*Ft_head, This_For);
    }
    textcolor('F');
    printf("\nWrite New information about your new class \n");
    textcolor(7);

    Class_t *New_Cl = Cl_GetData('n');
    New_Cl->Ft_key  = This_For->Ft_Id;

    Class_t *thisCl = Cl_CopyData(New_Cl);

    New_Ens->Ens_Cl_liste = thisCl;

    *Cl_head = Cl_Add(*Cl_head, New_Cl);

    thisEns++;

    return New_Ens;
}

Enseignant_t *Ens_add(Enseignant_t *Ens_BST,Enseignant_t *this_Ens)
{
    if(Ens_BST==NULL) Ens_BST=this_Ens;
    else
    {
        if(strcmp(Ens_BST->Ens_Code,this_Ens->Ens_Code)<0)
            Ens_BST->left=Ens_add(Ens_BST->left,this_Ens);
        else
            Ens_BST->right=Ens_add(Ens_BST->right,this_Ens);
    }
    return Ens_BST;
}

void Ens_Print_Profil(Enseignant_t *Ens_BST,Class_t *Cl_head)
{
    msg("                                     Teacher                                    ");

    textcolor('F'); printf("                                     About                                      "); textcolor(7);
    printf("CODE            : %s\n", Ens_BST->Ens_Code);
    printf("NAME            : %s\n", Ens_BST->Ens_Name);


    textcolor('F'); printf("                                Normal Formation                                "); textcolor(7);
    printf("\nNormal Formation : %d\n", Ens_BST->Ens_Ft_Nbr);
    Ft_Print(Ens_BST->Ens_Ft_liste);


    textcolor('F'); printf("                                  Normal Class                                  "); textcolor(7);
    printf("\nNormal Class     : %d\n", Ens_BST->Ens_Cl_Nbr);
    Cl_Print_ID(Ens_BST->Ens_Cl_liste,Cl_head);



    if(Ens_BST->Ft_Have_Accr)
    {
        textcolor('F'); printf("                               Accreditate Formation                            "); textcolor(7);
        Ft_Print(Ens_BST->Ft_Have_Accr);
        textcolor('F'); printf("                                 Accreditate Class                              "); textcolor(7);
        Cl_Print(Ens_BST->Cl_Have_Accr);
    }

    printf("\n\t   Part  : \t\t _.1._ \t\t _.2._ \t\t _.3._\n");
    printf("\t Realise :  \t\t .%s. \t\t .%s. \t\t .%s.\n",(( Ens_BST->Part_Of_Formation[0] == 1)? "Oui" : "Non"),(( Ens_BST->Part_Of_Formation[1] == 1)? "Oui" : "Non"),(( Ens_BST->Part_Of_Formation[2] == 1)? "Oui" : "Non"));
}

void Ens_Print(Enseignant_t *BST_Ens,Class_t *Cl_head)
{
    if(BST_Ens == NULL) return ;
    Ens_Print_Profil(BST_Ens,Cl_head);
    Ens_Print(BST_Ens->left,Cl_head);
    Ens_Print(BST_Ens->right,Cl_head);
}


Enseignant_t *Ens_Search(Enseignant_t *Ens_BST, char *this)
{

    if(Ens_BST==NULL)
        return NULL;
    if(strcmp(Ens_BST->Ens_Code,this)<0)
        Ens_Search(Ens_BST->left,this);
    else if(strcmp(Ens_BST->Ens_Code,this)>0)
        Ens_Search(Ens_BST->right,this);
    else
        return Ens_BST;

}


void Ens_Update(Enseignant_t **Ens_root,
                         Former_t **Fo_root,
                         const char *this,
                         Formation_t **Ft_Head,
                         Class_t ** Cl_Head)
{
    Enseignant_t *thisEns = Ens_Search(*Ens_root, this);

    int choice;
    int ftID;
    char txt[10];
    int Repet = 1;

    do
    {

        console_cls;
        Menu_Upadte_Ens(&choice);

        switch(choice)
        {
        case 1 :
            console_cls;
            printf("Old name : %s New pls : ", thisEns->Ens_Name);
            scanf("%s", txt);
            strcpy(thisEns->Ens_Name, txt);
            printf("\nSuccsed Opration\n");
            console_pause;
            break;
        case 2 :
            console_cls;


            Formation_t *thisFt = NULL;
            Class_t     *thisCl = NULL;

            thisFt = Ft_GetData('n');
            thisEns->Ens_Ft_Nbr++;

            thisCl = Cl_GetData('n');
            thisEns->Ens_Cl_Nbr++;
            thisCl->Ft_key  = thisFt->Ft_Id;

            if( Ens_Graduate(thisEns,*Cl_Head) == TRUE )
            {
                // Le faire Avec des formers
                textcolor('F');
                printf("\nCongratulation %s , You are admite As FaciliTateur TuTeur \n",thisEns->Ens_Name);
                Transfert(&(*Fo_root),thisEns);
                textcolor(7);
            }

            //Add formation
            Formation_t *newFt = Ft_CopyData(thisFt);

            thisEns->Ens_Ft_liste = Ft_Add(thisEns->Ens_Ft_liste, newFt);
            // Ft_Print(*Ft_Head);
            //printf("_________________________________________");
            *Ft_Head = Ft_Add(*Ft_Head, thisFt);
            // Ft_Print(*Ft_Head);

            //Add class
            Class_t *newCl = Cl_CopyData(thisCl);

            thisEns->Ens_Cl_liste = Cl_Add(thisEns->Ens_Cl_liste, newCl);
            *Cl_Head = Cl_Add(*Cl_Head, thisCl);

            console_pause;
            break;
        case 3 :
            console_cls;

            printf("Give the Id of Formation : ");
            scanf("%d", &ftID);
            thisFt = Ft_Search(*Ft_Head, ftID);
            if(thisFt && thisFt->Ft_TYPE == Accreditation)
            {
                //  thisFo->Ft_Have_Accr = (Formation_t*) malloc (sizeof(Formation_t));
                thisEns->Ft_Have_Accr=Ft_CopyData(thisFt);
                thisEns->Ft_Have_Accr->Next = NULL;
Class_Accr:
                Cl_Print(Cl_Search_ByFtID(*Cl_Head,thisFt->Ft_Id));

                Class_t *thisCl=NULL;
                printf("\n\nGive the Id of Class :   (-1 Quit) " );

                scanf("%d", &ftID);
                thisCl = Cl_SearchById(*Cl_Head, ftID);
                if(thisCl==NULL)
                {
                    goto Class_Accr;
                }
                if(thisCl->Cl_TYPE != Acreditation ) { printf("Class Normal Sorry ! \n "); goto Class_Accr; }
                if(thisCl->Cl_TYPE == Acreditation)

                { // Ces 2 fonctions pour mettre a jour le nombre d effectif pour chaque classe

                    Cl_SetNbreEff(&(*Cl_Head),thisCl->Cl_Id);
                    Fo_Gradute_My_Former(*Cl_Head,*Fo_root,thisCl->Cl_Id);

                    //  thisFo->Cl_Have_Accr = (Class_t*) malloc (sizeof(Class_t));
                    thisEns->Cl_Have_Accr = Cl_CopyData(thisCl);
                    thisEns->Cl_Have_Accr->Cl_Next = NULL;
                }
                if( Ens_Graduate(thisEns,*Cl_Head) == TRUE )
                {
                    // Le faire Avec des formers
                    textcolor('F');
                    printf("\nCongratulation %s , You are admite As FaciliTateur TuTeur \n",thisEns->Ens_Name);
                    Transfert(&(*Fo_root),thisEns);
                    textcolor(7);
                }
            }
            else REMARQUE("Formation doesn't exist ");
        console_pause;
            break;
            case 4 :
                console_cls;
               int i;
               for(i=0;i<3;i++)
                    if(! thisEns->Part_Of_Formation[i])
                    {
                         printf(" Part %d Have Finished ? ( 1_ Oui . 2_ Non ) :",i+1);
                         int c=getChoice(1,2);
                          if(c==1)
                            thisEns->Part_Of_Formation[i] = 1 ;
                            else  thisEns->Part_Of_Formation[i] = 0;
                    }
                  if( Ens_Graduate(thisEns,*Cl_Head) == TRUE )
                {
                    // Le faire Avec des formers
                    textcolor('F');
                    printf("\nCongratulation %s , You are admite As FaciliTateur TuTeur \n",thisEns->Ens_Name);
                    Transfert(&(*Fo_root),thisEns);
                    textcolor(7);
                }

          console_pause;
            break;

        case 5 :
            Repet = 0;
            break;

        }


    }
    while(Repet==1);


    return ;
}


void Ens_Save(Enseignant_t *Ens_root)
{
    FILE *F=fopen("Enseignant.dat","wb");
    fwrite(&thisEns,sizeof(thisEns),1,F);
    ///printf("%d lors du save  ThisFo  \n ",thisFo);
    Ens_Save_1(Ens_root,F);
    fclose(F);
}

Enseignant_t* Ens_Save_1(Enseignant_t *Ens_root,FILE *F)
{

    if(  Ens_root== NULL)  return ;
    else
    {
        int a;
        Ens_root->left = Ens_Save_1(Ens_root->left,F);
        Ens_root->right = Ens_Save_1(Ens_root->right,F);

        fwrite(&Ens_root->Ens_Ft_Nbr,sizeof(int),1,F);
        fwrite(&Ens_root->Ens_Cl_Nbr,sizeof(int),1,F);

        fwrite(&Ens_root->Ens_Name,sizeof(Ens_root->Ens_Name),1,F);
        fwrite(&Ens_root->Ens_Code,sizeof(Ens_root->Ens_Code),1,F);



        fwrite(Ens_root->Part_Of_Formation,sizeof(Ens_root->Part_Of_Formation),1,F);

        int k;

        if(Ens_root->Ft_Have_Accr && Ens_root->Cl_Have_Accr)
        {
            a=1;
            fwrite(&a,sizeof(int),1,F);
            fwrite(&Ens_root->Ft_Have_Accr->Ft_Id,sizeof(int),1,F);
            fwrite(&Ens_root->Cl_Have_Accr->Cl_Id,sizeof(int),1,F);
        }
        else
        {
            a=0;
            fwrite(&a,sizeof(int),1,F);
        }

        Formation_t *p=Ens_root->Ens_Ft_liste;
        Class_t *q=Ens_root->Ens_Cl_liste;
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

Enseignant_t *Ens_load(Formation_t *Ft_head,Class_t *Cl_head)
{

    int i,count,a,j,Cl_id,Ft_id;
    int Id_Accre_Ft,Id_Accre_cl;
    Enseignant_t *Ens_root=NULL;
    FILE *F=fopen("Enseignant.dat","rb");
    fread(&count,sizeof(int),1,F);
    if(F==NULL) return NULL;
    else
    {
        for(i=0; i<count; i++)
        {
            Enseignant_t *p=(Enseignant_t*)malloc(sizeof(Enseignant_t));

            fread(&p->Ens_Ft_Nbr,sizeof(int),1,F);

            fread(&p->Ens_Cl_Nbr,sizeof(int),1,F);

            fread(&p->Ens_Name,sizeof(p->Ens_Name),1,F);
            fread(&p->Ens_Code,sizeof(p->Ens_Code),1,F);

            fread(p->Part_Of_Formation,sizeof(p->Part_Of_Formation),1,F);

            int k;

            p->Cl_Have_Accr=NULL;
            p->Ft_Have_Accr=NULL;
            fread(&a,sizeof(int),1,F);
            if(a==1)
            {
                fread(&Id_Accre_Ft,sizeof(int),1,F);
                fread(&Id_Accre_cl,sizeof(int),1,F);
                p->Ft_Have_Accr=Ft_SearchById(Ft_head,Id_Accre_Ft);
                p->Cl_Have_Accr=Cl_SearchById(Cl_head,Id_Accre_cl);
            }

            p->Ens_Ft_liste=NULL;
            for(j=0; j<p->Ens_Ft_Nbr; j++)
            {
                Formation_t *THISFT=NULL;
                fread(&Ft_id,sizeof(int),1,F);
                THISFT=Ft_SearchById(Ft_head,Ft_id);
                //printf("%d formation 1 \n",Ft_id);   console_pause;
                p->Ens_Ft_liste=Ft_Add(p->Ens_Ft_liste,THISFT);

            }
            p->Ens_Cl_liste=NULL;
            for(j=0; j<p->Ens_Cl_Nbr; j++)
            {
                Class_t *THISCL=NULL;
                fread(&Cl_id,sizeof(int),1,F);
                THISCL=Cl_SearchById(Cl_head,Cl_id);
                ///printf("%d Classe 1 \n",Cl_id);console_pause;
                p->Ens_Cl_liste=Cl_Add(p->Ens_Cl_liste,THISCL);
            }

            p->right=NULL;
            p->left=NULL;

            Ens_root=Ens_add(Ens_root, p);
        }


        thisEns=count;
        fclose(F);
        return Ens_root;
    }

}


