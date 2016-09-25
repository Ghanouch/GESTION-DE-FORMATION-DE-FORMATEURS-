#include "Class.h"


void Return_Cl(int *Class)
{
    *Class=thisCl;
}

Class_t *Cl_Search_1(Class_t *Cl_list, const int this_id)
{

    Class_t *p = Cl_list;
    while(p)
    {
        if(p->Cl_Id == this_id)
        {
         return p ;

        }
        p = p->Cl_Next;
    }
    return NULL;
}

int Cl_nbre_Eff(Class_t *head,const int thisID)
{
    Class_t *p=head;
    while(p && p->Cl_Id!=thisID) p=p->Cl_Next;
    if(p) return p->nbre_eff;
}

// cette fonction nous permet de tester si un id se trouve dans une liste de class

int Cl_trouve(Class_t *Cl_head, int thisId)
{
    while(Cl_head && Cl_head->Cl_Id!=thisId)
        Cl_head=Cl_head->Cl_Next;
    if( ! Cl_head) return 0 ;
    else return 1;
}

void Cl_ProfilPrint(Class_t *Cl_root)
{
    printf("\n------------------------\n");

    textcolor(7);
    printf("Class ID           : ");
    textcolor(6);
    printf("%d\n", Cl_root->Cl_Id);
    textcolor(7);
    printf("Formation Key      : ");
    textcolor(6);
    printf("%d\n", Cl_root->Ft_key);
    textcolor(7);
    printf("Class Name         : ");
    textcolor(6);
    printf("%s\n", Cl_root->Cl_Name);
    textcolor(7);
    printf("Number of Condidat : ");
    textcolor(6);
    printf("%d\n", Cl_root->nbre_eff);

    char *type;

    if(Cl_root->Cl_TYPE == Normale) type = "Normale";
    else type = "Former";

    textcolor(7);
    printf("Class Type         : ", type);
    textcolor(6);
    printf("%s", type);
    textcolor(7);
    printf("\n------------------------\n");
}

void Cl_Print_ID(Class_t *root,Class_t *root_Pr)
{

    if(root==NULL)   perror("Empty Liste \n");
    Class_t * Cl_root = root;

    while(Cl_root != NULL)
    {
        printf("\n------------------------\n");

        textcolor(7);
        printf("Class ID           : ");
        textcolor(6);
        printf("%d\n", Cl_root->Cl_Id);
        textcolor(7);
        printf("Formation Key      : ");
        textcolor(6);
        printf("%d\n", Cl_root->Ft_key);
        textcolor(7);
        printf("Class Name         : ");
        textcolor(6);
        printf("%s\n", Cl_root->Cl_Name);
        textcolor(7);
        printf("Number of Condidat : ");
        textcolor(6);
        printf("%d\n", Cl_nbre_Eff(root_Pr,Cl_root->Cl_Id));

        char *type;

        if(Cl_root->Cl_TYPE == Normale) type = "Normale";
        else type = "Former";

        textcolor(7);
        printf("Class Type         : ", type);
        textcolor(6);
        printf("%s", type);
        textcolor(7);
        printf("\n------------------------\n");

        Cl_root = Cl_root->Cl_Next;
    }

}

void Cl_Print(Class_t *root)
{
    if(root==NULL)   perror("Empty Liste \n");
    Class_t * Cl_root = root;

    while(Cl_root != NULL)
    {
        Cl_ProfilPrint(Cl_root);
        Cl_root = Cl_root->Cl_Next;
    }
}

Class_t *Cl_CopyData(Class_t *thisCl)
{
    Class_t *newCl = (Class_t*)malloc(sizeof(Class_t));

    newCl->Cl_Id   = thisCl->Cl_Id;
    newCl->Ft_key  = thisCl->Ft_key;
    newCl->nbre_eff  = thisCl->nbre_eff;

    newCl->Cl_TYPE = thisCl->Cl_TYPE;
    strcpy(newCl->Cl_Name, thisCl->Cl_Name);

    newCl->Cl_Next = NULL;

    return newCl;
}

Class_t *Cl_GetData(char type)
{
    Class_t *newCl = (Class_t*) malloc(sizeof(Class_t));

    newCl->Cl_Id = thisCl++;
    newCl->Ft_key= 0;
    newCl->nbre_eff= 0;

    printf("Class Name : ");
    scanf("%s", newCl->Cl_Name);
    fflush(stdin);
    if(type == 'n') newCl->Cl_TYPE = Normale;
    if(type == 'a') newCl->Cl_TYPE = Acreditation;

    newCl->Cl_Next  = NULL;

    return newCl;
}

Class_t *Cl_Add(Class_t *Cl_root,Class_t *New_Cl)
{
    if(New_Cl)
    {

        if(Cl_root == NULL) Cl_root = New_Cl;
        else
        {
            New_Cl->Cl_Next  = Cl_root;
            Cl_root			= New_Cl;
        }
    }

    return Cl_root;
}

Class_t *Cl_Delete(Class_t *Cl_root, const int this)
{
    if(Cl_Search(Cl_root,this)==NULL)
    {
        printf("The Class %d not existe for deleting ! \n",this);
    }
    else
    {
        Class_t* Pred   = NULL;

        if(Cl_root->Cl_Id == this)
        {
            Pred = Cl_root;
            Cl_root = Cl_root->Cl_Next;
            free(Pred);
            thisCl--;
            return Cl_root;
        }

        Class_t *Cursor = Cl_root;

        while(Cursor != NULL)
        {
            Pred   = Cursor;
            Cursor = Cursor->Cl_Next;
            if(Cursor->Cl_Id == this)
            {
                Pred->Cl_Next = Cursor->Cl_Next;
                free(Cursor);
                break;
            }
        }
        thisCl--;
        printf("Succes deleting ! \n ");
    }
    return Cl_root;
}

Class_t *Cl_Search(Class_t *Cl_root, const int this)
{
    Class_t *Cursor = Cl_root;

    while(Cursor != NULL)
    {
        if(Cursor->Cl_Id == this) return Cursor;
        Cursor = Cursor->Cl_Next;
    }

    return NULL;
}

Class_t *Cl_Search_ByFtID(Class_t *Cl_liste, const int KEY)
{
    Class_t *Cl_cursor   = Cl_liste;
    Class_t *myCl_Linked = NULL;

    while(Cl_cursor)
    {
        if(Cl_cursor->Ft_key == KEY)
        {
            Class_t *thisCl = Cl_CopyData(Cl_cursor);
            myCl_Linked     = Cl_Add(myCl_Linked, thisCl);
        }
        Cl_cursor = Cl_cursor->Cl_Next;
    }

    return myCl_Linked;
}

Class_t *Cl_Update(Class_t *Cl_root, const int this)
{
    Class_t *Cl = Cl_Search(Cl_root, this);

    if(Cl)
    {
        printf("Class Id %d\n", Cl->Cl_Id);
        printf("Class Name %s, 	NEW pls : ", Cl->Cl_Name);
        scanf("%s", Cl->Cl_Name);

        char *type;
        if(Cl->Cl_TYPE == Normale) type = "Normale";
        else type = "Former";


        char t;
        do
        {
            fflush(stdin);
            printf("Class Type %s,	NEW pls (n-Normale, f-Former) : ", type);
            type = getchar();
        }
        while(t!='n' && t!='f');
        if(t == 'n') Cl->Cl_TYPE = Normale;
        if(t == 'f') Cl->Cl_TYPE = Acreditation;
    }

    return Cl_root;
}

void Cl_SetNbreEff(Class_t **Cl_list, const int this_id)
{
    Class_t *P=*Cl_list;
    while(P && P->Cl_Id!=this_id) P=P->Cl_Next;
    if(P) P->nbre_eff++;


}

Class_t *Cl_SearchById(Class_t *Cl_list, const int this_id)
{
    Class_t *New_Cl = NULL;
    Class_t *p = Cl_list;
    while(p)
    {
        if(p->Cl_Id == this_id)
        {
            New_Cl = Cl_CopyData(p);
            return New_Cl;
        }
        p = p->Cl_Next;
    }
    return NULL;
}


void Cl_Save(Class_t *Cl_list)
{
    FILE *F= F=fopen("Class.dat","wb");
    if(F)
    {
        Class_t *p=Cl_list;

        fwrite(&thisCl,sizeof(int),1,F);
        ///printf("%d nombre classe \n",thisCl);
        while(p)
        {
            fwrite(&p->Cl_Id,sizeof(int),1,F);
            fwrite(&p->nbre_eff,sizeof(int),1,F);
            fwrite(&p->Cl_Name,sizeof(p->Cl_Name),1,F);
            fwrite(&p->Cl_TYPE,sizeof(p->Cl_TYPE),1,F);
            fwrite(&p->Ft_key,sizeof(p->Ft_key),1,F);
            p=p->Cl_Next;
        }
    }

    fclose(F);

}

Class_t *Cl_load()
{
    int i,count=0;
    FILE *F = fopen("Class.dat", "rb");
    Class_t *Cl_list=NULL;
    if(F)
    {
        fread(&count,sizeof(int),1,F);

        for(i=0; i<count; i++)
        {
            Class_t *p=(Class_t*)malloc(sizeof(Class_t));
            fread(&p->Cl_Id,sizeof(p->Cl_Id),1,F);
            fread(&p->nbre_eff,sizeof(int),1,F);
            fread(&p->Cl_Name,sizeof(p->Cl_Name),1,F);
            fread(&p->Cl_TYPE,sizeof(p->Cl_TYPE),1,F);
            fread(&p->Ft_key,sizeof(p->Ft_key),1,F);
            p->Cl_Next=NULL;
            Cl_list=Cl_Add(Cl_list,p);
        }

    }

    fclose(F);
    thisCl=count;
    return Cl_list;
}


Class_t *Cl_Destroy(Class_t *Cl_liste)
{
    Class_t* corsor = Cl_liste;
    Class_t* prec   = NULL;

    while(!corsor)
    {
        prec   = corsor;
        corsor = corsor->Cl_Next;
        free(prec);
    }
    Cl_liste = NULL;
    return Cl_liste;
}
