#include "Menu.h"
#include<stdio.h>

void textcolor(int color)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,color);
}

int getChoice(const int min, const int max)
{
    int c;
    do
    {
        fflush(stdin);
        scanf("%d", &c);
    }
    while(c < min && c > max);

    return c;
}

void Menu_Principal(int *choice,
                    const int totalFt,
                    const int totalCl,
                    const int totalCd,
                    const int totalFo,
                    const int totalEns)
{
	console_cls;

    system("color 0C");
	printf("\n\t\t\t------------ ADMINISTRATOR ------------\n\n");
	textcolor(8);printf("\t\t\tTOTAL FORMATION : %d\n", totalFt);
	textcolor(2);printf("\t\t\tTOTAL CLASS     : %d\n", totalCl);
	textcolor(3);printf("\t\t\tTOTAL Candidate : %d\n", totalCd);
	textcolor(4);printf("\t\t\tTOTAL FORMER    : %d\n", totalFo);
	textcolor(6);printf("\t\t\tTOTAL Teacher   : %d\n", totalEns);
	textcolor(7);
	printf("\n\t\t\t\t1.CLASS\n");
	printf("\t\t\t\t2.CANDIDATE\n");
	printf("\t\t\t\t3.FORMATION\n");
	printf("\t\t\t\t4.FORMER\n");
	printf("\t\t\t\t5.STATISTICS\n");
	printf("\t\t\t\t6.TEACHER\n");
	printf("\t\t\t\t8.EFFECTIF\n");
	printf("\t\t\t\t7.RETURN\n");
	printf("\t\t\t---------------------------------------\n\n");
	printf("\t\t\tYour choise pls : ");
	int c = getChoice(1, 8);
	*choice = c;
}

void Menu_STATISTICS(int *choice,int Niveau_1,int Niveau_2,int Niveau_3)
{
	console_cls;

	printf("\n\t\t\t-------------- STATISTICS --------------\n\n");
	printf("\t\t\tEFFECTIFE OF FORMER\n\n");
	printf("\t\t\tNational     : %d \n", Niveau_2);
	printf("\t\t\tFacilitator  : %d \n", Niveau_1);
	printf("\t\t\tRegional     : %d \n\n", Niveau_3);
	printf("\t\t\t--------\n\n");
	printf("\t\t\t\t1.View all facilitators\n");
	printf("\t\t\t\t2.View all nationals\n");
	printf("\t\t\t\t3.View all regionals\n");
	printf("\t\t\t\t4.Return\n\n");
	printf("\t\t\t--------------------------------------\n\n");
	printf("\t\t\tYour choise pls : ");
	int c;
	scanf("%d", &c);
	*choice = c;
}

void Menu_Ens(int *choice)
{
    console_cls;
    //system("color 0A");
	printf("\n\t\t\t------------ TEACHER ------------\n\n");
	printf("\t\t\t\t1.Add\n");
	printf("\t\t\t\t2.Update\n");
	printf("\t\t\t\t3.Print\n");
	printf("\t\t\t\t4.Search\n");
	printf("\t\t\t\t5.Return\n\n");
	printf("\t\t\t---------------------------------\n\n");
	printf("\t\t\tYour choise pls : ");

	int c = getChoice(1, 4);
	*choice = c;
}


void Menu_Cl(int *choice)
{
	console_cls;
    //system("color 0A");
	printf("\n\t\t\t------------ CLASS ------------\n\n");
	printf("\t\t\t\t1.Print\n");
	printf("\t\t\t\t2.Update\n");
	printf("\t\t\t\t3.Serch\n");
	//printf("\t\t\t\t4.Remove\n");
	printf("\t\t\t\t4.Return\n\n");
	printf("\t\t\t--------------------------------\n\n");
	printf("\t\t\tYour choise pls : ");

	int c = getChoice(1, 4);
	*choice = c;
}

void Menu_Cd(int *choice)
{
	console_cls;
    //system("color 0D");
	printf("\n\t\t\t------------ CANDIDATE ------------\n\n");
	printf("\t\t\t\t1.Add\n");
	printf("\t\t\t\t2.Print\n");
	printf("\t\t\t\t3.Update\n");
	printf("\t\t\t\t4.Serch\n");
	printf("\t\t\t\t5.Remove\n");
	printf("\t\t\t\t6.Return\n\n");
	printf("\t\t\t-----------------------------------\n\n");
	printf("\t\t\tYour choise pls : ");

	int c = getChoice(1, 6);
	*choice = c;
}

void Menu_Fo(int *choice)
{
	console_cls;
    //system("color 0E");
	printf("\n\t\t\t------------ FORMER ------------\n\n");
	printf("\t\t\t\t6.Add\n");
	printf("\t\t\t\t1.Print\n");
	printf("\t\t\t\t2.Update\n");
	printf("\t\t\t\t3.Serch\n");
	printf("\t\t\t\t4.Remove\n");
	printf("\t\t\t\t5.Return\n\n");
	printf("\t\t\t--------------------------------\n\n");
	printf("\t\t\tYour choise pls : ");

	int c = getChoice(1, 5);
	*choice = c;
}

void Menu_Ft(int *choice)
{
	console_cls;
    //system("color 09");
	printf("\n\t\t\t------------ FORMATION ------------\n\n");
	printf("\t\t\t\t1.Print\n");
	printf("\t\t\t\t2.Update\n");
	printf("\t\t\t\t3.Serch\n");
	//printf("\t\t\t\t4.Remove\n");
	printf("\t\t\t\t4.Return\n\n");
	printf("\t\t\t-----------------------------------\n\n");
	printf("\t\t\tYour choise pls : ");

	int c = getChoice(1, 4);
	*choice = c;
}

void Menu_Upadte_Fo(int *choice)
{
	console_cls;
    //system("color 08");
	printf("\n\t\t\t------------ UPDATE FORMER ------------\n\n");
	printf("\t\t\t\t1.Name\n");
	printf("\t\t\t\t2.Add Activity\n");
	printf("\t\t\t\t3.Add Formation\n");
	printf("\t\t\t\t4.New Accred\n");
	printf("\t\t\t\t5.Return\n\n");
	printf("\t\t\t----------------------------------------\n\n");
	printf("\t\t\tYour choise pls : ");

    int c = getChoice(1, 5);
	*choice = c;
}

void Menu_Upadte_Ens(int *choice)
{
	console_cls;
    //system("color 08");
	printf("\n\t\t\t------------ UPDATE Teacher ------------\n\n");
	printf("\t\t\t\t1.Name\n");
	printf("\t\t\t\t2.Add Formation\n");
	printf("\t\t\t\t3.New AccrediTation\n");
	printf("\t\t\t\t4.Part finished\n");
	printf("\t\t\t\t5.Return\n\n");
	printf("\t\t\t----------------------------------------\n\n");
	printf("\t\t\tYour choise pls : ");

    int c = getChoice(1, 5);
	*choice = c;
}

void Menu_Upadte_Cd(int *choice)
{
    console_cls;
    //system("color 03");
	printf("\n\t\t\t------------ UPDATE Candidate ------------\n\n");
	printf("\t\t\t\t1.First Name\n");
	printf("\t\t\t\t2.Last Neme\n");
	printf("\t\t\t\t3.Code\n");
	printf("\t\t\t\t4.Regestration date\n");
	printf("\t\t\t\t5.Return\n\n");
	printf("\t\t\t------------------------------------------\n\n");
	printf("\t\t\tYour choise pls : ");

    int c = getChoice(1, 5);
	*choice = c;
}

void Menu_Cd_Profile(int *choice, const char *code)
{
	   console_cls;

	printf("\n\t\t\t------------ Candidate %s ------------\n\n", code);
	printf("\t\t\t\t1.View Profile\n");
	printf("\t\t\t\t2.Update Profile\n");
	//printf("\t\t\t\t3.Print your Former\n");
	//printf("\t\t\t\t4.Save your Data\n");
	printf("\t\t\t\t3.Return\n\n");
	printf("\t\t\t___________________\n\n");
	printf("\t\t\tYour choise pls : ");

    int c = getChoice(1, 3);
	*choice = c;
}

void Menu_Fo_Profile(int *choice, const char *code)
{
	   console_cls;

	printf("\n\t\t\t------------ FORMER %s ------------\n\n", code);
	printf("\t\t\t\t1.View Profile\n");
	printf("\t\t\t\t2.Update Profile\n");
	//printf("\t\t\t\t3.Print your Candidate\n");
	//printf("\t\t\t\t4.Save your Data\n");
	printf("\t\t\t\t3.Return\n\n");
	printf("\t\t\t___________________\n\n");
	printf("\t\t\tYour choise pls : ");

    int c = getChoice(1, 3);
	*choice = c;
}

void _MENU_(int *choice)
{
	console_cls;
    //system("color 0F");
	printf("\n\t\t---------- MANGEMENT OF FORMERS FORMATIONS ----------");
	printf("\n\t\t|\t\t\t\t\t\t    |\n\t\t|");
    printf("\tARE YOU.\t                            |\n\t\t|\t\t\t\t\t\t    |\n");
	printf("\t\t|\t\t1.ADMINISTRATOR                     |\n");
	printf("\t\t|\t\t2.FORMER                            |\n");
	printf("\t\t|\t\t3.CANDIDATE                         |\n");
	printf("\t\t|\t\t4.QUIT                              |\n\t\t|\t\t\t\t\t\t    |\n");
	printf("\t\t----------------------------------------------------\n\n");
	printf("\t\tYour choise pls : ");

	int c = getChoice(1, 4);
	*choice = c;
}

void REMARQUE(char* mot){
    console_cls;
    //system("color 1F");
    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t    %s\n\n\n", mot);
    printf("\t\t\t     PRESS ANY KEY FOR CONTUNUE");
    system("PAUSE>null");
}

void msg(char *txt)
{
    printf("\n");
    textcolor('CC');
    printf("                                                                                ");
    textcolor('CC'); printf("%s", txt);
    printf("                                                                                ");
    textcolor(7);
    printf("\n");
}

/*
void Menu_End(int repet){
    system("color 0F");
    start:
    console_cls;
    printf("\n\n\n\n\n\n\n\n\n\n\t\tVEULLEZ VOUS VRAIMENT SORTIRE (oui/non)? : ");
    char Answer[3]; scanf("%s", Answer);
    int i;
    for(i=0;i<3;i++)Answer[i]=tolower(Answer[i]);
    if(strcmp(Answer, "oui")==0)  {
        console_cls;
        repet=false;
        printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tFIN");
        for(i=0;i<3;i++){
            printf(".");
            Sleep(1500);
        }
        printf("\n\n\n\n\n\n\n\n\n");
        system("EXIT");
    }
    else if(strcmp(Answer, "non")==0)repet=true;
    else goto start;
}
*/
void Loading(int x,int y,int z){
    //system("color 0E");
    int i, j;
    for(i=0;i<x;i++){
    console_cls;
    printf("\n\n\n\n\n\n\n\n\n\t\t\t\t   LOADING");
    for(j=0;j<y;j++){
        printf(".");
        Sleep(z);
    }
    }
    console_cls;
}


char *newPassword()
{
	char c, *str = (char*)malloc(sizeof(char));
	int i = 0, j = 1;
	do
	{
		c = getch();
		if((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 8)
		{
			if(c == 8)
            {
                if(i > 0 && j >1)
                {
                    i--;
                    j--;
                }
            }
            else
            {
    		str = (char*)realloc(str,j*sizeof(char));
   			str[i] = c;
   			i++;
   			j++;
            }
   			//c = '*';
			//printf("%c", c);
   		}

	}
	while(c != 13 || i == 0);
	j++;
	str = (char*)realloc(str, j*sizeof(char));
	str[i] = '\0';
	return str;
}
