/*TO DO:
pay?

BUGS: 
3rd new customer is taken as an existing customer for no reason at all
*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
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
int create_menu(struct bill*,struct bill* tablep);
void create_order(struct bill*, struct bill*);
int check_table(struct bill*, struct bill*);
void initialise(struct bill*,struct bill*);
void admin_login(struct bill*, struct bill*);
void edit_order(struct bill*, struct bill*);
void login(struct bill*, struct bill*);
void admin(struct bill*, struct bill*);
void cust(struct bill*, struct bill*);
void display_bill(struct bill*, struct bill*);
void view_table(struct bill*, struct bill*);
void cust_login(struct bill*, struct bill*);
void checkout(struct bill*, struct bill*);

int main()
{
    struct bill menu,table[5];
    struct bill *menup = &menu,*tablep = &table[0];
    initialise(menup,tablep);    
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

int create_menu(struct bill* menup,struct bill* tablep)
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
    login(menup,tablep-((tablep->table_no)-1));
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
        i = 0;
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
    cust(menup,tablep);
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
        (tablep+i)->status = 1;
        Sleep(2000);
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
        (tablep+i)->table_no = i+1;
    }
    login(menup,tablep-((tablep->table_no)-1));
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
            admin(menup,tablep);
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
    cust(menup,tablep);
}

void login(struct bill* menup,struct bill* tablep)  
{

    //log in to tables system
    char table_no;
    printf("Please enter your table number(if new, please enter 0)(if admin, please enter a):\n");
    scanf("\n%c",&table_no);
    if(table_no == 'a')
    {  
        admin_login(menup,tablep-((tablep->table_no)-1));
    }
    else if(table_no == 'e')
    {
        printf("Exiting... ");
        Sleep(1000);
        exit(0);
    }
    else
    {
        if(menu_status == 1)            //checks if menu has been created or not
        {
            if((tablep + (((int)table_no)-49))->status == 1)
            {
                printf("Table no: %d\n",(int)table_no-48);
                cust_login(menup,tablep);
                //table_no(tablep+((int)table_no)-1);
            }
            else if(((int)table_no) == 48)
            {
                printf("Logging in as a new customer...");
                Sleep(1000);
                check_table(menup, tablep-((tablep->table_no)-1));
            }
            else
            {
                printf("Please enter valid table number\n");
            }
        }
        else
        {
            printf("The restaurant hasn't opened yet, please wait.\n");
        }
    }
    login(menup,tablep-((tablep->table_no)-1));
}

void admin(struct bill*menup,struct bill*tablep)
{
    int n;
    char yesNo;
    printf("Welcome, Admin!\n");
    one:
    printf("What action would you like to perform?\n");
    printf("1. create today's menu\n");
    printf("2. View a table's order\n");
    printf("3. Close restraunt\n");
    printf("4. Log out\n");
    scanf("%d",&n);

    switch(n)
    {
        case 1:
            printf("Creating menu\n");
            create_menu(menup,tablep);
            break;
        case 2:
            printf("view_table_order(tableno)\n");
            break;
        case 3:
            printf("Are you sure you want to close the restaurant?\n");
            scanf("\n%c",&yesNo);
            if(yesNo == 'y')
            {
                printf("Closing restaurant...\n");
                exit(0);
            }
            else
            {
                goto one;
            }
            break;
        case 4:
            printf("Logging out...");
            login(menup,tablep-((tablep->table_no)-1));
            break;
        default:
            printf("Invalid input\n");
    }
}

void cust(struct bill*menup,struct bill*tablep)
{
    int n;
    
    printf("Welcome, customer!\n");
    printf("What action would you like to perform?\n");
    printf("1. Order more items\n");
    printf("2. View bill\n");
    printf("3. Log out\n");
    scanf("%d",&n);

    switch(n)
    {
        case 1:
            printf("Opening your order...\n");
            edit_order(menup,tablep);
            break;
        case 2:
            display_bill(menup,tablep);
            break;
        case 3:
            printf("Logging out...\n");
            login(menup,tablep-((tablep->table_no)-1));
            break;
        default:
            printf("Invalid input\n");
    }

}

void display_bill(struct bill* menup, struct bill* tablep)
{
    int i,j;
    int quantity=1,sum=0,sno=1,rep=0;
    char yesno;
    printf("S.no Dish                  Cost  Quantity\n");
    for(i=0;i<tablep->total_dishes;i++)
    {
        quantity = 1;
        rep = 0;
        for(j=i-1;j>=0;j--)
        {
            if(strcmp(tablep->dishes[i].name,tablep->dishes[j].name) == 0)
            {
                rep = 1;
                break;
            }
        }
        if(rep == 0)
        {
            for(j=i+1;j<tablep->total_dishes;j++)
            {
                if(strcmp(tablep->dishes[i].name,tablep->dishes[j].name) == 0)
                {
                    quantity++;
                }
            }
            printf("%4d %-20s %5d  %d\n",sno,tablep->dishes[i].name, tablep->dishes[i].price,quantity);
            sno++;
            sum+= tablep->dishes[i].price*quantity;
        }
        else
        {
            continue;
        }

        
    }
    printf("\n\e[1mTotal amount: %d\e[m",sum);

    checkout(menup,tablep);
    login(menup,tablep-((tablep->table_no)-1));
}

void view_table(struct bill* menup, struct bill* tablep)
{
    printf("\e[1mHere is the order and bill from table no. %d:\e[m\n",tablep->table_no);
    printf("Bill no: %d",tablep->bill_no);
    display_bill(menup,tablep);
    printf("\n Press any key to continue");
    getchar();
    admin(menup,tablep);
}

void cust_login(struct bill* menup, struct bill* tablep)
{
    int n;
    int i;
    for(i=0;i<5;i++)
    {
        printf("Please enter your bill number: \n");
        scanf("%d",&n);
        if(n == tablep->bill_no)
        {
            printf("Successful login!\n");
            cust(menup,tablep);
        }
        else
        {
            printf("please enter correct bill number. If lost, contact manager\n");
        }
    }
    printf("Too many incorrect attempts. Logging out...\n");
    Sleep(1000);
    login(menup,tablep-(tablep->table_no + 1));
}

void checkout(struct bill* menup,struct bill* tablep)
{
    char yesno;
    printf("\nWould you like to pay now? (y/n) ");
    scanf("\n%c",&yesno);
    if(yesno == 'n')
    {
        printf("Going back to menu...\n");
        Sleep(1000);
        cust(menup,tablep);
    }
    else if(yesno == 'y')
    {
        printf("Thank you for eating at our restaurant");
        checkout(menup,tablep);
    }
    tablep->status = 0;
}
