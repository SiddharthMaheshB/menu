#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
//#include<unistd.h>
//#include<windows.h>
#include<ctype.h>

struct dish
{
    char name[20];
    int price;
};

struct bill
{
    int bill_no;
    int table_no;
    int status;
    int total_dishes;
    struct dish dishes[10];
    int total_bill;
};

int menu_status = 0;

void display_menu(struct bill*);
int create_menu(struct bill*);
void create_order(struct bill*, struct bill*);
int check_table(struct bill*, struct bill*);
void initialise(struct bill*,struct bill*);
void admin_login(struct bill*, struct bill*);
void edit_order(struct bill*, struct bill*);


int main()
{
    struct bill menu,table[5];
    struct bill *menup = &menu,*tablep = &table[0];

    
    int n,i;
    char table_no;

    
    
    create_menu(menup);
    create_order(menup,tablep);
    edit_order(menup, tablep);
    

}


void display_menu(struct bill* menup)
{
    int i;

    printf("S.no Dish                  Cost\n");
    for(i=0;i<menup->total_dishes;i++)
    {
        printf("%5d %-20s %d\n",i+1,menup->dishes[i].name, menup->dishes[i].price);
    }
}

int create_menu(struct bill* menup)
{
    int i;
    printf("Please enter number of dishes on the menu: \n");
    scanf("%d",&menup->total_dishes);
    char check;

    char dish[20];
    printf("Please enter dish name and cost in two different lines\n");
    do
    {
        for(i=0;i<menup->total_dishes;i++)
        {
            //gets(dish);
            //printf("%d\n",i);
            
            scanf("%s %d",dish,&menup->dishes[i].price);
            strcpy(menup->dishes[i].name,dish);
        }
        printf("This is the menu you have entered:\n");
        display_menu(menup);
        printf("finalize? (y/n)");
        scanf("\n%c",&check);
    }while(check == 'n');
    menu_status = 1;
}

void create_order(struct bill* menup, struct bill* tablep)
{
    char check = 'n';
    int input=1,i=0;
    system("cls");
    tablep->status = 1;
    tablep->bill_no = rand()%100+1;
    printf("Your Bill no is: %d\n",tablep->bill_no);
    printf("\n\e[1mPlease keep note of your bill number.\e[m\n");
    while(check == 'n')
    {
        display_menu(menup);
        printf("\nPlease enter the serial number of the items you would like to order (if you want more than one quantity of an item, please enter its serial number twice): \n");
        printf("Please enter 0 when you are done\n");
        do
        {
            
            tablep->dishes[i-1].price = menup->dishes[input-1].price;
            strcpy(tablep->dishes[i-1].name,menup->dishes[input-1].name);
            scanf("%d",&input);
            i++;
        }while(input!=0);
        i--;
        tablep->total_dishes = i;
        printf("\e[1mThis is your order: \e[m\n");
        display_menu(tablep);
        printf("\nfinalize? (y/n)\n");
        scanf("\n%c",&check);
    }
}

int check_table(struct bill* menup, struct bill* tablep)
{
    int i;
    int check = 0;
    for(i=0;i<5;i++)
    {
        if((tablep+i)->status==1)
            continue;
        else
        {
            check = 1;
            break;
        }
    }
    if(check == 1)
    {
        printf("Table %d is free!\n",i+1);
        tablep->table_no = i+1;
        //Sleep(2000);
        create_order(menup,tablep+i);
    }
    else
    {
        printf("All tables are currently full, please wait for some time");
    }
}

void initialise(struct bill* menup,struct bill* tablep)
{
    char table_no;
    int i;

    //setting all tables status to unoccupied
    for(i=0;i<5;i++)
    {
        (tablep+i)->status = 0;
    }

    //log in to tables system
    printf("Please enter your table number(if new, please enter 0)(if admin, please enter a):\n");
    scanf("%c",&table_no);
    if(table_no == 'a')
    {  
        admin_login(menup,tablep);
    }
    else
    {
        if(menu_status == 1)            //checks if menu has been created or not
        {
            if((tablep + (((int)table_no)-49))->status == 1)
            {
                printf("Table no: %d",(int)table_no-48);
                //table_no(tablep+((int)table_no)-1);
            }
            else if(((int)table_no) == 48)
            {
                printf("Logging in as a new customer...");
                //Sleep(1000);
                check_table(menup, tablep);
            }
            else
            {
                printf("Please enter valid table number");
            }
        }
        else
        {
            printf("The restaurant hasn't opened yet, please wait.");
        }
    }
    
}

void admin_login(struct bill* menup, struct bill* tablep)
{
    char password[10] = "password";
    //int i;
    printf("Loggin in as admin...\n");
    while(1){
        printf("Enter Password: ");
        scanf("%s",password);
        
        if(!strcmp(password,"password"))
        {
            printf("Successful login!\n");
            break;
        }
        else{
            printf("Please try again\n");
        }
    }
}

void edit_order(struct bill* menup, struct bill* tablep)
{
    char check = 'n';
    int i,input=1;
    while(check == 'n')
    {
        display_menu(menup);
        printf("\nPlease enter the serial number of the items you would like to order (if you want more than one quantity of an item, please enter its serial number twice): \n");
        printf("Please enter 0 when you are done\n");
        for(i=tablep->total_dishes;input!=0;i++)
        {
            
            tablep->dishes[i].price = menup->dishes[input-1].price;
            strcpy(tablep->dishes[i].name,menup->dishes[input-1].name);
            scanf("%d",&input);
        }
        i--;
        tablep->total_dishes = i;
        printf("\e[1mThis is your order: \e[m\n");
        display_menu(tablep);
        printf("\nfinalize? (y/n)\n");
        scanf("\n%c",&check);
    }
}
