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

void display_menu(struct bill,int);
int create_menu(struct bill, int);
void create_order(struct bill, struct bill,int);

int main()
{
    struct bill menu;
    struct bill order[10];

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
    Sleep(2000);
    //clrscr();
    printf("Creating menu...\n");
    Sleep(2000);

    create_menu(menu,5);
    display_menu(menu,5);
    create_order(menu,order[0],5);
}

void display_menu(struct bill menu,int num_of_items)
{
    int i;

    printf("S.no Dish                  Cost\n");
    for(i=0;i<num_of_items;i++)
    {
        printf("%5d %-20s %d\n",i+1,menu.dishes[i].name, menu.dishes[i].price);
    }
}

int create_menu(struct bill menu, int itemNum)
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
            scanf("%s %d",dish,&menu.dishes[i].price);
            strcpy(menu.dishes[i].name,dish);
        }
        printf("This is the menu you have entered:\n");
        display_menu(menu,itemNum);
        printf("finalize? (y/n)");
        scanf("\n%c",&check);
    }while(check == 'n');
}

void create_order(struct bill menu, struct bill order,int itemNum)
{
    char check = 'n';
    int input,i;
    order.bill_no = rand()%100+1;
    printf("Your Bill no is: %d\n",order.bill_no);
    display_menu(menu,5);
    /*while(check == 'n')
    {
        display_menu(menu,5);
        printf("\nPlease enter the serial number of the items you would like to order: \n");
        printf("Please enter 0 when you are done\n");
        for(i=0;input!=0;i++)
        {
            scanf("%d",&input);
            order.dishes[i].price = menu.dishes[input-1].price;
            strcpy(order.dishes[i].name,menu.dishes[input-1].name);
        }
        display_menu(order,i);
        printf("\nfinalize? (y/n)\n");
        scanf("\n%c",&check);
    }*/
    
}