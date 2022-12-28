#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct item_details
{
    char item_name[10];
    int item_price;
    int item_quantity;
}id;
typedef struct inventory
{
    id item;
    int available;
}inv;

void add();
void show();
void update();
void search();
void alert();
int main()
{
    FILE *fp;
    int choice;
    fp=fopen("inventory.dat","ab+");
    printf("==========================WELCOME=======================\n");
    while(1)
    {
    printf("1.Add item\n2.update item\n3.search item\n4.Show all items\n5.Alert Me\n6.exit\n");
    printf("========================================================\n");
    printf("Choose an Option :");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
        add();
        break;
        case 2:
        update();
        break;
        case 3:
        search();
        break;
        case 4:
        show();
        break;
        case 5:
        alert();
        break;
        default:
        exit(0); 
    }
    printf("---------------------------END---------------------------\n\n\n");
    }
}


void add()
{   
    int check;
    FILE *fp;
    fp=fopen("inventory.dat","ab+");
    inv itm,t;
    fflush(stdin);
    printf("Enter Name of item :");
    gets(itm.item.item_name);
    while(fread(&t,sizeof(t),1,fp)!=0)
    {
        check=strcmp(itm.item.item_name,t.item.item_name);
    }
    if(check==0)
    {
        printf("Item already exist in inventory\n");
    }
    else
    {
    printf("Price of Item :");
    scanf("%d",&itm.item.item_price);
    printf("Quantity :");
    scanf("%d",&itm.item.item_quantity);
    fwrite(&itm,sizeof(itm),1,fp);
    fclose(fp);
    }
}

void show()
{
    FILE *fp;
    fp=fopen("inventory.dat","ab+");
    inv itm;
    printf("Item Name\t\t\tprice\t\tQuantity\n");
    while(fread(&itm,sizeof(itm),1,fp)!=0)
    {
        printf("%-33s%-18d%-10d\n\n",itm.item.item_name,itm.item.item_price,itm.item.item_quantity);
    }
}

void update()
{
    FILE *fp;
    fp=fopen("inventory.dat","rb+");
    inv itm,t;
    fflush(stdin);
    printf("Enter the item name you want to change :");
    gets(t.item.item_name);
    while(fread(&itm,sizeof(itm),1,fp)!=0)
    {
        if(strcmp(itm.item.item_name,t.item.item_name)==0)
        {
            printf("Enter the Updated price :");
            scanf("%d",&t.item.item_price);
            printf("Enter the Updated quantity :");
            scanf("%d",&t.item.item_quantity);
            fseek(fp,(long long int)-sizeof(itm),SEEK_CUR);
            fwrite(&t,sizeof(t),1,fp);
            fclose(fp);
        }     
    }
}

void search()
{   
    char name[10];
    inv itm;
    FILE *fp;
    fp=fopen("inventory.dat","rb");
    printf("Enter the Item Name :");
    fflush(stdin);
    gets(name);
    printf("Item Name\t\t\tprice\t\tQuantity\n");
    while(fread(&itm,sizeof(itm),1,fp)!=0)
    {
        if(strcmp(itm.item.item_name,name)==0)
        {
        printf("%-33s%-18d%-10d\n\n",itm.item.item_name,itm.item.item_price,itm.item.item_quantity);
        }
    }
}

void alert()
{   
    int flag;
    inv temp;
    FILE *fp;
    fp=fopen("inventory.dat","rb");
    while(fread(&temp,sizeof(temp),1,fp)!=0)
    {
        if(temp.item.item_quantity==0)
        {
            printf("%s need to be added\n",temp.item.item_name);
        }
    }

}