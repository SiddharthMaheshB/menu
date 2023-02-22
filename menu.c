#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>

struct dish
{
    char name[20];
    int price;
};

struct bill
{
    int bill_no;
    struct dish dishes[10];
    int total_bill;
};

void display_menu(struct bill*,int);
int create_menu(struct bill*, int);
void create_order(struct bill*, struct bill*, int);

int main()
{
    struct bill menu,order[10];
    struct bill *menup = &menu,*orderp = &order[0];

    int n;
    char password[10] = "password";
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
    Sleep(1000);
    system("cls");
    printf("Creating menu...\n");
    Sleep(1000);

    create_menu(menup,5);
    create_order(menup,orderp,5);
}

void display_menu(struct bill* menup,int num_of_items)
{
    int i;

    printf("S.no Dish                  Cost\n");
    for(i=0;i<num_of_items;i++)
    {
        printf("%5d %-20s %d\n",i+1,menup->dishes[i].name, menup->dishes[i].price);
    }
}

int create_menu(struct bill* menup, int itemNum)
{
    int i;
    char check;
    char dish[20];
    printf("Please enter dish name and cost in two different lines\n");
    do
    {
        for(i=0;i<itemNum;i++)
        {
            //gets(dish);
            //printf("%d\n",i);
            scanf("%s %d",dish,&menup->dishes[i].price);
            strcpy(menup->dishes[i].name,dish);
        }
        printf("This is the menu you have entered:\n");
        display_menu(menup,itemNum);
        printf("finalize? (y/n)");
        scanf("\n%c",&check);
    }while(check == 'n');
}

void create_order(struct bill* menup, struct bill* orderp,int itemNum)
{
    char check = 'n';
    int input,i;
    system("cls");
    orderp->bill_no = rand()%100+1;
    printf("Your Bill no is: %d\n",orderp->bill_no);
    while(check == 'n')
    {
        display_menu(menup,5);
        printf("\nPlease enter the serial number of the items you would like to order (if you want more than one quantity of an item, please enter its serial number twice): \n");
        printf("Please enter 0 when you are done\n");
        for(i=0;input!=0;i++)
        {
            orderp->dishes[i-1].price = menup->dishes[input-1].price;
            strcpy(orderp->dishes[i-1].name,menup->dishes[input-1].name);
            scanf("%d",&input);
        }
        i--;
        display_menu(orderp,i);
        printf("\nfinalize? (y/n)\n");
        scanf("\n%c",&check);
    }
}