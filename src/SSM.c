//SuperMarket Smart Manager
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTS 50
#define MAX_CART 50
#define STAFF_PASSWORD "1234"

struct Product {
    int id;
    char name[50];
    float price;
    int stock;
};

struct CartItem {
    int id;
    char name[50];
    float price;
    int qty;
};

void productList(struct Product *p, int n)
{
    int i=0;

    printf("\n=====================================\n");
    printf("            PRODUCT LIST\n");
    printf("=====================================\n");

    printf("ID\tName\t\tPrice\tStock\n");

    while(i<n)
    {
        printf("%d\t%s\t\t%.2f\t%d\n",p[i].id,p[i].name,p[i].price,p[i].stock);
        i++;
    }
}

void searchProduct(struct Product *p,int n)
{
    char name[50],tname[50],titem[50];
    int i,j,found,len;

    while(1)
    {
        printf("\n=====================================\n");
        printf("          SEARCH PRODUCT\n");
        printf("=====================================\n");

        printf("Enter Name (0 to exit): ");
        scanf(" %49[^\n]",name);

        if(strcmp(name,"0")==0)
        return;

        len=strlen(name);
        i=0;
        while(i<len)
        {
            tname[i]=tolower(name[i]);
            i++;
        }
        tname[len]='\0';

        found=-1;

        i=0;
        while(i<n)
        {
            j=0;
            while(p[i].name[j])
            {
                titem[j]=tolower(p[i].name[j]);
                j++;
            }
            titem[j]='\0';

            if(strcmp(tname,titem)==0)
            {
                found=i;
                break;
            }
            i++;
        }

        if(found==-1)
        {
            printf("\nProduct Not Found\n");
        }
        else
        {
            printf("\n========== PRODUCT FOUND ==========\n");
            printf("ID: %d\n",p[found].id);
            printf("Name: %s\n",p[found].name);
            printf("Price: %.2f\n",p[found].price);
            printf("Stock: %d\n",p[found].stock);
            printf("===================================\n");
            return;
        }
    }
}

void addNewProduct(struct Product *p,int *n)
{
    printf("\n=====================================\n");
    printf("           ADD NEW PRODUCT\n");
    printf("=====================================\n");

    if(*n>=MAX_PRODUCTS)
    {
        printf("Inventory Full\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d",&p[*n].id);

    printf("Enter Name: ");
    scanf(" %49[^\n]",p[*n].name);

    printf("Enter Price: ");
    scanf("%f",&p[*n].price);

    printf("Enter Stock: ");
    scanf("%d",&p[*n].stock);

    *n = *n + 1;

    printf("Product Added Successfully\n");
}

void updateProduct(struct Product *p,int n)
{
    int id,i=0,pos=-1,ch,newSt;
    float newPr;

    printf("\n=====================================\n");
    printf("           UPDATE PRODUCT\n");
    printf("=====================================\n");

    printf("Enter ID: ");
    scanf("%d",&id);

    while(i<n)
    {
        if(p[i].id==id)
        {
            pos=i;
            break;
        }
        i++;
    }

    if(pos==-1)
    {
        printf("Not Found\n");
        return;
    }

    printf("1. Update Price\n2. Update Stock\nEnter choice: ");
    scanf("%d",&ch);

    switch(ch)
    {
        case 1:
            printf("Enter new price: ");
            scanf("%f",&newPr);
            p[pos].price=newPr;
            break;

        case 2:
            printf("Enter new stock: ");
            scanf("%d",&newSt);
            p[pos].stock=newSt;
            break;

        default:
            printf("Invalid\n");
    }
}

void staffMenu(struct Product *p,int *n)
{
    char pass[20];
    int ch;

    printf("\n=====================================\n");
    printf("             STAFF LOGIN\n");
    printf("=====================================\n");

    printf("Enter Password: ");
    scanf("%s",pass);

    if(strcmp(pass,STAFF_PASSWORD)!=0)
    {
        printf("Wrong Password\n");
        return;
    }

    while(1)
    {
        printf("\n=====================================\n");
        printf("              STAFF MENU\n");
        printf("=====================================\n");
        printf("1. Show Inventory\n2. Add Product\n3. Update Product\n4. Back\n");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
                productList(p,*n);
                break;

            case 2:
                addNewProduct(p,n);
                break;

            case 3:
                updateProduct(p,*n);
                break;

            case 4:
                return;

            default:
                printf("Invalid\n");
        }
    }
}

void addToCart(struct Product *p,int n,struct CartItem *c,int *cn)
{
    int id,qty,i,pos;

    while(1)
    {
        printf("\n=====================================\n");
        printf("            ADD TO CART\n");
        printf("=====================================\n");

        printf("Enter Product ID (0 to stop): ");
        scanf("%d",&id);

        if(id==0)
        {
            printf("Stopping Add To Cart...\n");
            return;
        }

        pos=-1;
        i=0;

        while(i<n)
        {
            if(p[i].id==id)
            {
                pos=i;
                break;
            }
            i++;
        }

        if(pos==-1)
        {
            printf("Product Not Found\n");
            continue;
        }

        printf("Enter Quantity: ");
        scanf("%d",&qty);

        if(qty > p[pos].stock)
        {
            printf("Not enough stock\n");
            continue;
        }

        c[*cn].id = p[pos].id;
        strcpy(c[*cn].name, p[pos].name);
        c[*cn].price = p[pos].price;
        c[*cn].qty = qty;

        *cn = *cn + 1;

        printf("Item Added To Cart\n");
    }
}

void viewCart(struct CartItem *c,int cn)
{
    int i=0;

    printf("\n=====================================\n");
    printf("               VIEW CART\n");
    printf("=====================================\n");

    if(cn==0)
    {
        printf("Cart Empty\n");
        return;
    }

    printf("ID\tName\tQty\tPrice\n");

    while(i<cn)
    {
        printf("%d\t%s\t%d\t%.2f\n",c[i].id,c[i].name,c[i].qty,c[i].price);
        i++;
    }
}

void removeFromCart(struct CartItem *c,int *cn)
{
    int id,i=0,pos=-1;

    printf("\n=====================================\n");
    printf("             REMOVE ITEM\n");
    printf("=====================================\n");

    if(*cn==0)
    {
        printf("Cart Empty\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d",&id);

    while(i<*cn)
    {
        if(c[i].id==id)
        {
            pos=i;
            break;
        }
        i++;
    }

    if(pos==-1)
    {
        printf("Not Found\n");
        return;
    }

    while(pos<*cn-1)
    {
        c[pos]=c[pos+1];
        pos++;
    }

    *cn=*cn-1;

    printf("Item Removed\n");
}

float calculateGST(float t)
{
    return t*0.18;
}

void generateBill(struct CartItem *c,int *cn)
{
    float total=0,amt,gst,grand;
    int i=0;

    printf("\n=====================================\n");
    printf("              FINAL BILL\n");
    printf("=====================================\n");

    if(*cn==0)
    {
        printf("Cart Empty\n");
        return;
    }

    printf("ID\tName\tQty\tAmount\n");

    while(i<*cn)
    {
        amt=c[i].qty*c[i].price;
        total+=amt;
        printf("%d\t%s\t%d\t%.2f\n",c[i].id,c[i].name,c[i].qty,amt);
        i++;
    }

    gst=calculateGST(total);
    grand=total+gst;

    printf("\nSubtotal: %.2f\n",total);
    printf("GST: %.2f\n",gst);
    printf("Total: %.2f\n",grand);

    *cn=0;
}

void billingMenu(struct CartItem *c,int *cn)
{
    int ch;

    while(1)
    {
        printf("\n=====================================\n");
        printf("            BILLING MENU\n");
        printf("=====================================\n");

        printf("1. Generate Bill\n2. Back\n");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
                generateBill(c,cn);
                break;

            case 2:
                return;

            default:
                printf("Invalid\n");
        }
    }
}

void cartMenu(struct Product *p,int n,struct CartItem *c,int *cn)
{
    int ch;

    while(1)
    {
        printf("\n=====================================\n");
        printf("               CART MENU\n");
        printf("=====================================\n");

        printf("1.Add\n2.View\n3.Remove\n4.Back\n");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
                addToCart(p,n,c,cn);
                break;

            case 2:
                viewCart(c,*cn);
                break;

            case 3:
                removeFromCart(c,cn);
                break;

            case 4:
                return;

            default:
                printf("Invalid\n");
        }
    }
}

void customerMenu(struct Product *p,int n,struct CartItem *c,int *cn)
{
    int ch;

    while(1)
    {
        printf("\n=====================================\n");
        printf("              CUSTOMER MENU\n");
        printf("=====================================\n");

        printf("1.List\n2.Search\n3.Cart\n4.Back\n");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
                productList(p,n);
                break;

            case 2:
                searchProduct(p,n);
                break;

            case 3:
                cartMenu(p,n,c,cn);
                break;

            case 4:
                return;

            default:
                printf("Invalid\n");
        }
    }
}

int main()
{
    struct Product p[MAX_PRODUCTS]={
        {1,"Apple",50,40},
        {2,"Milk",30,20},
        {3,"Bread",25,15},
        {4,"Rice",60,50}
    };

    int pn=4;

    struct CartItem c[MAX_CART];
    int cn=0;

    int ch;

    while(1)
    {
        printf("\n=====================================\n");
        printf("               MAIN MENU\n");
        printf("=====================================\n");

        printf("1.Customer\n2.Staff\n3.Billing\n4.Exit\n");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
                customerMenu(p,pn,c,&cn);
                break;

            case 2:
                staffMenu(p,&pn);
                break;

            case 3:
                billingMenu(c,&cn);
                break;

            case 4:
                return 0;

            default:
                printf("Invalid\n");
        }
    }
}

