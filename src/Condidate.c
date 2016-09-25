#include "Condidate.h"
#define EFF_CLASS_NORMAL 30

void Return_Cd(int *Condidat)
{
    *Condidat=thisCd;
}

void Cd_profilPrint(Condidat_t *Cd_root)
{
    msg("                                    Candidate                                  ");
    printf("\n\n");
    textcolor('F'); printf("                                     About                                     "); textcolor(7);
    printf("\n\n");
    printf("-----------------\n");
    printf("First Name : %s\n", Cd_root->Cd_FirstName);
    printf("Last  Name : %s\n", Cd_root->Cd_LastName);
    printf("Code       : %s\n", Cd_root->Cd_Code);
    printf("-----------------\n");
    printf("Resestration day : %d ---%d ---%d\n", Cd_root->Cd_RegDate.DD, Cd_root->Cd_RegDate.MM, Cd_root->Cd_RegDate.YY);
    printf("-----------------\n\n");
    printf("\n");
    textcolor('F'); printf("                            Resestration Formation                             "); textcolor(7);
    Ft_Print(Cd_root->Cd_Formation);printf("\n");
    textcolor('F'); printf("                              Resestration Class                               "); textcolor(7);
    Cl_Print(Cd_root->Cd_Class);
}

void Cd_Print(Condidat_t *Cd_root)
{
    if(Cd_root)
    {
        Cd_Print(Cd_root->Cd_left);
        Cd_Print(Cd_root->Cd_right);
        Cd_profilPrint(Cd_root);
    }
    return;
}

Condidat_t *Cd_getData(Former_t **Fo_root,Enseignant_t *Ens_root,Formation_t *Ft_head, Class_t **Cl_head)
{
    Condidat_t *newCd = (Condidat_t*) malloc(sizeof(Condidat_t));

    char txt[20];

    newCd->Cd_Id = thisCd++;

    printf("Condidate First Name : ");
    scanf("%s", newCd->Cd_FirstName);
    //strcpy(newCd->Cd_FirstName, txt);
    printf("Condidate Last Name : ");
    scanf("%s", newCd->Cd_LastName);
    //strcpy(newCd->Cd_LastName, txt);
    printf("Condidate Code : ");
    scanf("%s", txt);
    strcpy(newCd->Cd_Code, txt);

    printf("\nResestration Data\n_____________________\n");
    printf("Day   : ");
    scanf("%d", &newCd->Cd_RegDate.DD);
    printf("Month : ");
    scanf("%d", &newCd->Cd_RegDate.MM);
    printf("Year  : ");
    scanf("%d", &newCd->Cd_RegDate.YY);

    printf("\nChoice your formation & your Class\n_____________________________\n");

    Formation_t *newFt = NULL;
    Formation_t *thisFt= NULL;

    int yes = 1;
    int thisID;

    do
    {
        FORMATION:
        do
        {
            printf("Forrmation ID : (0 QUit) ");
            scanf("%d", &thisID);
            thisFt = Ft_Search(Ft_head, thisID);
            if(!thisFt) printf("\nError : Formation doesn't exist\n");

        }
        while(!thisFt && thisID!=0);

        newFt  = Ft_CopyData(thisFt);
        newCd->Cd_Formation = newFt;

        Ft_Print(newFt);
        printf("\n0. Confirm & 1. No : ");
        scanf("%d", &yes);

    }
    while(yes);

    printf("\nSecces Operation with Cdrmation\n");

    Class_t *thisCl_list = Cl_Search_ByFtID(*Cl_head, newFt->Ft_Id);

    printf("\n---- This is the list of all classes that has %s like Formation\n", newFt->Ft_Name);

    Cl_Print(thisCl_list);
    Class_t *MYCl = NULL;
    do
    {
        printf("\nYOUR CHOICE PLS (ID OF CLASS) (-1 : EXIST ):  ");
        scanf("%d", &thisID);
        if(thisID == -1) goto FORMATION;
        if(Cl_nbre_Eff(*Cl_head,thisID) >= EFF_CLASS_NORMAL)
        {
            textcolor('F');
            printf("Sorry ! This Class Have Already %d candidat => You must choice an other Class : ",EFF_CLASS_NORMAL);
            textcolor(7);
            continue;
        }
        if( Cl_Search(*Cl_head,thisID)->Cl_TYPE == Accreditation )
        {
            printf("This is a not a normal class , Sorry !");
            continue;
        }
        Cl_SetNbreEff(&(*Cl_head),thisID);
        MYCl   = Cl_Search(thisCl_list, thisID);

    }
    while(!MYCl);

    Ens_Gradute_My_Teachers(&(*Fo_root),Ens_root,*Cl_head,thisID);
    Fo_Gradute_My_Former(*Cl_head,*Fo_root,thisID);

    Class_t *thisCl = Cl_CopyData(MYCl);
    newCd->Cd_Class = thisCl;

    printf("\nSecces Operation with class\n");

    newCd->Cd_left  = NULL;
    newCd->Cd_right = NULL;

    return newCd;
}

Condidat_t *Cd_FindMin(Condidat_t* Cd_root)
{
    if(Cd_root == NULL) return NULL;
    if(Cd_root->Cd_left) return Cd_FindMin(Cd_root->Cd_left);
    else return Cd_root;
}

Condidat_t *Cd_CopyData(Condidat_t *thisCd)
{
    Condidat_t *Cd = (Condidat_t*) malloc(sizeof(Condidat_t));

    strcpy(Cd->Cd_Code,         thisCd->Cd_Code);
    strcpy(Cd->Cd_FirstName,    thisCd->Cd_FirstName);
    strcpy(Cd->Cd_LastName,     thisCd->Cd_LastName);

    Cd->Cd_RegDate.DD = thisCd->Cd_RegDate.DD;
    Cd->Cd_RegDate.MM = thisCd->Cd_RegDate.MM;
    Cd->Cd_RegDate.YY = thisCd->Cd_RegDate.YY;

    Cd->Cd_Formation  = Ft_CopyData(thisCd->Cd_Formation);
    Cd->Cd_Class      = Cl_CopyData(thisCd->Cd_Class);

    Cd->Cd_Id = thisCd->Cd_Id;

    Cd->Cd_left  = NULL;
    Cd->Cd_right = NULL;

    return Cd;
}

Condidat_t *Cd_Add(Condidat_t *Cd_root, Condidat_t *newCd)
{
    if(Cd_root == NULL) Cd_root = newCd;
    else
    {
        if(strcmp(newCd->Cd_Code, Cd_root->Cd_Code) > 0)
            Cd_root->Cd_right = Cd_Add(Cd_root->Cd_right, newCd);
        else
            Cd_root->Cd_left  = Cd_Add(Cd_root->Cd_left, newCd);
    }

    return Cd_root;
}

Condidat_t *Cd_Delete(Condidat_t *Cd_root, const char *data)
{
    if(Cd_root == NULL) return Cd_root;
    else if(strcmp(data, Cd_root->Cd_Code) < 0) Cd_root->Cd_left  = Cd_Delete(Cd_root->Cd_left,  data);
    else if(strcmp(data, Cd_root->Cd_Code) > 0) Cd_root->Cd_right = Cd_Delete(Cd_root->Cd_right, data);
    else
    {
        //case 1 : no child
        if(Cd_root->Cd_left == NULL && Cd_root->Cd_right == NULL)
        {
            Cd_root->Cd_Formation = Ft_Destroy(Cd_root->Cd_Formation);
            Cd_root->Cd_Class     = Cl_Destroy(Cd_root->Cd_Class);

            free(Cd_root);
            thisCd--;
            Cd_root = NULL;
        }
        //case 2 : 1 child
        else if(Cd_root->Cd_left == NULL)
        {
            Condidat_t* temp = Cd_root;
            Cd_root = Cd_root->Cd_right;

            temp->Cd_Formation = Ft_Destroy(temp->Cd_Formation);
            temp->Cd_Class     = Ft_Destroy(temp->Cd_Class);

            free(temp);
            thisCd--;
        }
        else if(Cd_root->Cd_left == NULL)
        {
            Condidat_t *temp = Cd_root;
            Cd_root = Cd_root->Cd_left;

            temp->Cd_Formation = Ft_Destroy(temp->Cd_Formation);
            temp->Cd_Class     = Ft_Destroy(temp->Cd_Class);

            free(temp);
            thisCd--;
        }
        //case 3 : 2 child
        else
        {
            Condidat_t* temp = Cd_FindMin(Cd_root->Cd_right);
            Cd_root = Cd_CopyData(temp);
            Cd_root->Cd_right = Cd_Delete(Cd_root->Cd_right, temp->Cd_Code);
        }
    }

    return Cd_root;
}

Condidat_t *Cd_Update(Condidat_t *Cd_root, const char *this)
{

    Condidat_t *thisCd = Cd_Search(Cd_root, this);

    if(thisCd)
    {
        printf("\n\n");
        int rep = 1, choice;
        char txt[10];
        while(rep)
        {
            Menu_Upadte_Cd(&choice);
            switch(choice)
            {
            case 1 :
                console_cls;
                printf("New First name of %s pls : ", thisCd->Cd_Code);
                scanf("%s", txt);
                strcpy(thisCd->Cd_FirstName, txt);
                break;
            case 2 :
                console_cls;
                printf("New Last name of %s pls : ", thisCd->Cd_Code);
                scanf("%s", txt);
                strcpy(thisCd->Cd_LastName, txt);
                break;
            case 3 :
                console_cls;
                printf("New Code of %s pls : ", thisCd->Cd_Code);
                scanf("%s", txt);
                strcpy(thisCd->Cd_Code, txt);
                break;
            case 4 :
                console_cls;
                printf("New RegDate of %s pls\n\n", thisCd->Cd_Code);
                printf("DD PLS : ");
                scanf("%d", &thisCd->Cd_RegDate.DD);
                printf("MM PLS : ");
                scanf("%d", &thisCd->Cd_RegDate.MM);
                printf("YY PLS : ");
                scanf("%d", &thisCd->Cd_RegDate.YY);
                break;
            case 5 :
                rep = 0;
            default:
                ;
            }
        }
        return Cd_root;
    }
    else printf("\n\nImpossible This Condidate does not exist");
}

Condidat_t *Cd_Search(Condidat_t *Cd_root, const char *this)
{
    if(!Cd_root) return NULL;

    if(strcmp(this, Cd_root->Cd_Code) < 0) Cd_Search(Cd_root->Cd_left, this);
    else if(strcmp(this, Cd_root->Cd_Code) > 0) Cd_Search(Cd_root->Cd_right, this);
    else return Cd_root;
}

void Cd_Save(Condidat_t *Cd_list)
{
    FILE *F=fopen("Condidat.dat","wb");

    fwrite(&thisCd,sizeof(thisCd),1,F);
    //printf("%d lors du save  ThisCd  \n ",thisCd);
    Cd_Save_1(Cd_list,F);
    fclose(F);
}

Condidat_t *Cd_Save_1(Condidat_t *Cd_root,FILE *F)
{
    if(Cd_root==NULL) return ;
    else
    {

        Cd_root->Cd_left=Cd_Save_1(Cd_root->Cd_left,F);
        Cd_root->Cd_right=Cd_Save_1(Cd_root->Cd_right,F);


        fwrite(&Cd_root->Cd_Id,sizeof(Cd_root->Cd_Id),1,F);
        fwrite(&Cd_root->Cd_Code,sizeof(Cd_root->Cd_Code),1,F);
        fwrite(&Cd_root->Cd_Formation->Ft_Id,sizeof(int),1,F);
        fwrite(&Cd_root->Cd_Class->Cl_Id,sizeof(int),1,F);
        fwrite(&Cd_root->Cd_FirstName,sizeof(Cd_root->Cd_FirstName),1,F);
        fwrite(&Cd_root->Cd_LastName,sizeof(Cd_root->Cd_LastName),1,F);
        fwrite(&Cd_root->Cd_RegDate.DD,sizeof(Cd_root->Cd_RegDate.DD),1,F);
        fwrite(&Cd_root->Cd_RegDate.MM,sizeof(Cd_root->Cd_RegDate.YY),1,F);
        fwrite(&Cd_root->Cd_RegDate.YY,sizeof(Cd_root->Cd_RegDate.MM),1,F);
    }
    // printf("%d nombre condidat \n",thisCd);

}



Condidat_t *Cd_load(Formation_t *Ft_head,Class_t *Cl_head)
{
    int this_Id_Cl,this_Id_Ft;

    int i,count=0;
    Condidat_t *Cd_root=NULL;
    FILE *F=fopen("Condidat.dat","rb");
    fread(&count,sizeof(int),1,F);
   /// printf("%d \n",count);
    if(F==NULL) return NULL;
    else

    {
        int j=0;
      ///  printf("%d \n",j++);

        for(i=0; i<count; i++)
        {
            Condidat_t *p=(Condidat_t*)malloc(sizeof(Condidat_t));

            fread(&p->Cd_Id,sizeof(Cd_root->Cd_Id),1,F);
            //  printf("%d \n",p->Cd_Id);
            fread(&p->Cd_Code,sizeof(Cd_root->Cd_Code),1,F);
            // printf("%s \n",p->Cd_Code);
            fread(&this_Id_Ft,sizeof(int),1,F);
            //  printf("%d \n",this_Id_Ft);
            fread(&this_Id_Cl,sizeof(int),1,F);
            //  printf("%d \n",this_Id_Cl);
            fread(&p->Cd_FirstName,sizeof(Cd_root->Cd_FirstName),1,F);
            // printf("%s \n",p->Cd_FirstName);
            fread(&p->Cd_LastName,sizeof(Cd_root->Cd_LastName),1,F);
            //  printf("%s \n",p->Cd_LastName);
            fread(&p->Cd_RegDate.DD,sizeof(Cd_root->Cd_RegDate.DD),1,F);
            // printf("%d \n",p->Cd_RegDate.DD);
            fread(&p->Cd_RegDate.MM,sizeof(Cd_root->Cd_RegDate.MM),1,F);
            fread(&p->Cd_RegDate.YY,sizeof(Cd_root->Cd_RegDate.YY),1,F);

            // printf("%s \n","SALA HADA");

            //  printf("%d \n",j++);
            //printf(" ID CLASSE : %d  OD FOTMATION %d",this_Id_Cl,this_Id_Ft);

            p->Cd_Class = (Class_t*)malloc(sizeof(Class_t));
            p->Cd_Class = Cl_SearchById(Cl_head, this_Id_Cl);

            p->Cd_Formation = (Formation_t*)malloc(sizeof(Formation_t));
            p->Cd_Formation = Ft_SearchById(Ft_head, this_Id_Ft);

            p->Cd_left=NULL;
            p->Cd_right=NULL;

            Cd_root=Cd_Add(Cd_root, p);
        }

        //printf("%d hada conteur dial load \n",count);
        thisCd=count;
        //printf("%d lors du load  ThisCd  \n ",thisCd);
        fclose(F);
        return Cd_root;
    }

}
