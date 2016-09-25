#include "Formation.h"
#include "Menu.h"

void Return_Ft(int *Formation)
{
    *Formation=thisFt;
}

void Ft_ProfilPrint(Formation_t *F)
{
    char *type;

    printf("\n------------------------------------\n");

    textcolor(7);printf("Id of Formation       : ");
    textcolor(9);printf("%d\n",F->Ft_Id);
    textcolor(7);printf("The Name of Formation : ");
    textcolor(9);printf("%s\n",F->Ft_Name);
    textcolor(7);printf("Duration              : ");
    textcolor(9);printf("%d jours \n",F->Ft_Duration);

    if(F->Ft_TYPE == Normal) type = "Normal";
    else type = "Accreditation";

    textcolor(7);printf("Type                  : ");
    textcolor(9);printf("%s\n",type);
    textcolor(2);
    printf("\tArea          : %s \n\tCity          : %s \n\tUniversity    : %s \n\tEstablishment : %s \n",F->Ft_Location.Area,F->Ft_Location.City,F->Ft_Location.University,F->Ft_Location.Establishment);
    textcolor(7);
    printf("------------------------------------\n\n");

}

void Ft_Print(Formation_t *Ft_Head)
{
    if(Ft_Head == NULL) printf("Empty List ! \n");
    else
    {
        Formation_t *F = Ft_Head;
        while(F!=NULL)
        {
            Ft_ProfilPrint(F);
            F=F->Next;
        }
    }
}

Formation_t *Ft_CopyData(Formation_t *thisFt)
{
    Formation_t *newFt = (Formation_t*)malloc(sizeof(Formation_t));

    newFt->Ft_Duration = thisFt->Ft_Duration;
    newFt->Ft_TYPE     = thisFt->Ft_TYPE;
    newFt->Ft_Id       = thisFt->Ft_Id;
    newFt->Ft_Occ      = thisFt->Ft_Occ;

    strcpy(newFt->Ft_Name, thisFt->Ft_Name);
    strcpy(newFt->Ft_Location.Area,             thisFt->Ft_Location.Area);
    strcpy(newFt->Ft_Location.City,             thisFt->Ft_Location.City);
    strcpy(newFt->Ft_Location.Establishment,    thisFt->Ft_Location.Establishment);
    strcpy(newFt->Ft_Location.University,       thisFt->Ft_Location.University);

    newFt->Next = NULL;

    return newFt;
}

Formation_t *Ft_GetData(char c)
{
    Formation_t *New_Ft=(Formation_t*)malloc(sizeof(Formation_t));
    New_Ft->Ft_Id=thisFt++;
    printf("The Name of Formation : ");
    scanf("%s",New_Ft->Ft_Name);
    printf("Duration ( In day ) : ");
    scanf("%d",&New_Ft->Ft_Duration);
    char type;
    if(c=='n') New_Ft->Ft_TYPE = Normal;
    else  New_Ft->Ft_TYPE = Accreditation;
    printf("The Information Of location\n");
    printf("Area : ");
    scanf("%s",New_Ft->Ft_Location.Area);
    printf("City : ");
    scanf("%s",New_Ft->Ft_Location.City);
    printf("University : ");
    scanf("%s",New_Ft->Ft_Location.University);
    printf("Establishment : ");
    scanf("%s",New_Ft->Ft_Location.Establishment);
    New_Ft->Ft_Occ = 1;
    New_Ft->Next=NULL;

    return New_Ft;
}
// cette fonction nous permet d additionner une noveau formation mais selon le char d , on sera capable de distinguer si l ajout se fait a partir du clavier
// ou du parametre New_Ft --- char c permet de remplir le type de formation if(d=='c' implique a partir du clavier ) if(d==o (objet) a partir du fonction)
Formation_t *Ft_Add(Formation_t *Fo_root,Formation_t *Data_ft)
{
    //Data_ft->Next=NULL;
            if(Data_ft) {
    if(Fo_root == NULL) Fo_root=Data_ft;
    else
    {


        Data_ft->Next=Fo_root;
        Fo_root=Data_ft;

    }
            }

    return Fo_root;

}

Formation_t *Ft_Delete(Formation_t *Fo_root, const int this)
{
    if(Ft_Search(Fo_root,this)==NULL)
    {
        printf("The Formation %d not existe for deleting ! \n",this);
    }
    else
    {
        Formation_t* Pred   = NULL;

        if(Fo_root->Ft_Id == this)
        {
            Pred = Fo_root;
            Fo_root = Fo_root->Next;
            free(Pred);
            thisFt--;
            return Fo_root;
        }

        Formation_t *Cursor = Fo_root;

        while(Cursor != NULL)
        {
            Pred   = Cursor;
            Cursor = Cursor->Next;
            if(Cursor->Ft_Id == this)
            {
                Pred->Next = Cursor->Next;
                free(Cursor);
                break;
            }
        }
        thisFt--;
        printf("Succes deleting ! \n ");
    }
    return Fo_root;

}

Formation_t *Ft_Update(Formation_t *Fo_root, const int this)
{
    Formation_t *New_F=Ft_Search(Fo_root,this);
    char *type;
    if(!New_F) perror("The Formation not EXISTE! \n");
    else
    {

        printf("The New Name Is  : ");
        scanf("%s",New_F->Ft_Name);

        if(New_F->Ft_TYPE == Normal) type = "Normal";
        else type = "Accreditation";
        char t;
        do
        {
            fflush(stdin);
            printf("Formation Type %s,	NEW plz (n-Normale, f-Accreditation) : ", type);
            t = getchar();
        }
        while(t!='n' && t!='a');
        if(t == 'n')New_F->Ft_TYPE = Normal;
        if(t == 'a')New_F->Ft_TYPE = Accreditation;

        printf(" old Duration : ( %d jours ) \t  New Duration : ",New_F->Ft_Duration);
        scanf("%d",&New_F->Ft_Duration);
        printf("The Information Of location\n ");
        printf(" old : %s \t Area : ",New_F->Ft_Location.Area);
        scanf("%s",New_F->Ft_Location.Area);
        printf(" old : %s \t City : ",New_F->Ft_Location.City);
        scanf("%s",New_F->Ft_Location.City);
        printf(" old : %s \t University : ",New_F->Ft_Location.University);
        scanf("%s",New_F->Ft_Location.University);
        printf(" old : %s \t Establishment : ",New_F->Ft_Location.Establishment);
        scanf("%s",New_F->Ft_Location.Establishment);
        printf("Modify succed ! \n");

        return Fo_root;

    }
}


Formation_t *Ft_Search(Formation_t *Fo_root, const int this)
{
    if(Fo_root==NULL) return NULL;
    Formation_t *F=Fo_root;
    while(F!=NULL)
    {

        if(F->Ft_Id == this)
            return F;
        F=F->Next;
    }
    return NULL;

}

Formation_t *Ft_SearchById(Formation_t *Ft_list, const int this_id)
{
    Formation_t *New_Ft=NULL;
    Formation_t *p=Ft_list;
    while(p)
    {
        if(p->Ft_Id==this_id)
        {
            New_Ft = Ft_CopyData(p);
            return New_Ft;
        }
        p=p->Next;
    }
    return NULL;
}

void Ft_Save(Formation_t *Ft_list)
{
    int i;
    FILE *F=fopen("Formation.dat","wb");
    if(F==NULL) perror("Impossible d'ouvrir le Fichier \n");
    fwrite(&thisFt,sizeof(Ft_list->Ft_Id),1,F);
    ///printf("%d nombre formation \n",Ft_list->Ft_Id);
    Formation_t *p=Ft_list;
    while(p)
    {
        fwrite(&p->Ft_Id,sizeof(Ft_list->Ft_Id),1,F);
        fwrite(&p->Ft_Duration,sizeof(Ft_list->Ft_Duration),1,F);
        fwrite(&p->Ft_Location.Area,sizeof(Ft_list->Ft_Location.Area),1,F);
        fwrite(&p->Ft_Location.City,sizeof(Ft_list->Ft_Location.City),1,F);
        fwrite(&p->Ft_Location.Establishment,sizeof(Ft_list->Ft_Location.Establishment),1,F);
        fwrite(&p->Ft_Location.University,sizeof(Ft_list->Ft_Location.University),1,F);
        fwrite(&p->Ft_Name,sizeof(Ft_list->Ft_Name),1,F);
        fwrite(&p->Ft_TYPE,sizeof(Ft_list->Ft_TYPE),1,F);
        p=p->Next;
    }
    fclose(F);
}

Formation_t *Ft_load()
{
    int i,count=0;
    Formation_t *Ft_liste=NULL;
    FILE *F=fopen("Formation.dat","rb");
    if(F!=NULL)
    {
        fread(&count,sizeof(int),1,F);
        for(i=0; i<count; i++)
        {

            Formation_t *p=(Formation_t*)malloc(sizeof(Formation_t));
            fread(&p->Ft_Id,sizeof(p->Ft_Id),1,F);
            fread(&p->Ft_Duration,sizeof(p->Ft_Duration),1,F);
            fread(&p->Ft_Location.Area,sizeof(p->Ft_Location.Area),1,F);
            fread(&p->Ft_Location.City,sizeof(p->Ft_Location.City),1,F);
            fread(&p->Ft_Location.Establishment,sizeof(p->Ft_Location.Establishment),1,F);
            fread(&p->Ft_Location.University,sizeof(p->Ft_Location.University),1,F);
            fread(&p->Ft_Name,sizeof(p->Ft_Name),1,F);
            fread(&p->Ft_TYPE,sizeof(p->Ft_TYPE),1,F);
            p->Next=NULL;
            Ft_liste=Ft_Add(Ft_liste,p);
        }

    }
    thisFt=count;
  //  printf(" count formation %d \n",count);  console_pause;

    return Ft_liste;
    fclose(F);

}

Formation_t *Ft_Destroy(Formation_t *Ft_liste)
{
    Formation_t* corsor = Ft_liste;
    Formation_t* prec   = NULL;

    while(!corsor)
    {
        prec   = corsor;
        corsor = corsor->Next;
        free(prec);
    }
    Ft_liste = NULL;
    return Ft_liste;
}
