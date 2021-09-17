#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 5000

typedef struct{
    char code[100];
    char name[100];
    char category[100];
    float price;
    int stock;
} product;

typedef struct{
    product p;
    struct node *left, *right;
} node;

typedef struct{
    product p;
    struct node *next;
} hashing;

hashing *arr[M];

typedef struct Node{
    product data;
    struct Node *next;
} NODE;

typedef struct List{
    NODE *head;
    int n;
} List;

List *create_list(){
    List *list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->n = 0;

    return list;
}

void insert_front(List *list) {

    product pro;
    NODE *tmp = (NODE*)malloc(sizeof(NODE));

    fflush(stdin);
    printf("Input product code: ");
    gets(pro.code);
    fflush(stdin);
    printf("Input product name: ");
    gets(pro.name);
    fflush(stdin);
    printf("Input product category: ");
    gets(pro.category);
    printf("Input product price: ");
    scanf("%f",&pro.price);
    printf("Input product stock: ");
    scanf("%d",&pro.stock);

    int search=search_id(pro.code,pro.category,list);

    if(search==0){
        strcpy(tmp->data.code,pro.code);
        strcpy(tmp->data.name,pro.name);
        strcpy(tmp->data.category,pro.category);
        tmp->data.price = pro.price;
        tmp->data.stock = pro.stock;
        tmp->next = list->head;
        list->head = tmp;
        list->n++;
    }
    else{
        printf("This code has been existed\n");
    }
}

int search_id(char *search_code, char *cat, List *list){
    NODE *tmp;
    tmp = list->head;
    while(tmp != NULL){
        if((strcmp(tmp->data.code,search_code)==0)&&(strcmp(tmp->data.category,cat)==0)){
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}
//1. add product
void add_product(List *list){
    system("CLS");
    int n;
    printf("Insert amount of product to add: ");
    scanf("%d", &n);
    int i;
    for(i=0; i<n; i++){
        insert_front(list);
    }
}

//2. modify product
void modify_product(List *list){
    system("CLS");
    int found=0;
    product pro;
    char code[100];
    fflush(stdin);
    printf("Input the code:");
    gets(code);
    NODE *tmp = list->head;
    while (tmp != NULL) {
        if(strcmp(tmp->data.code,code)==0){
            fflush(stdin);
            printf("Product name: ");
            gets(pro.name);
            fflush(stdin);
            printf("Product category: ");
            gets(pro.category);
            printf("Product price: ");
            scanf("%f",&pro.price);
            printf("Product stock: ");
            scanf("%d",&pro.stock);
            strcpy(tmp->data.name,pro.name);
            strcpy(tmp->data.category,pro.category);
            tmp->data.price=pro.price;
            tmp->data.stock=pro.stock;
            found=1;
        }
        tmp=tmp->next;
    }
    if(found==0){
        printf("Product is not found\n");
    }
    printf("\n\n");
}
//3. delete product
void delete_product(List *list){
    system("CLS");
    int found = 0;
    char code[100];
    NODE *p;
    NODE *tmp;
    p = list->head;
    int i;
    fflush(stdin);
    printf("Input code to delete product:");
    gets(code);
    search_pos(code,&found,list);
    if(found == 0){
        printf("Not found\n");
    }
    else{
        found--;
        if (found == 0) {
            remove_front(list);
        } else {
            NODE *tmp;
            NODE *tmp2 = list->head;
            for (int i = 0; i < found - 1; i++) {
                tmp2 = tmp2->next;
            }
            tmp = tmp2->next;
            tmp2->next = tmp->next;
            free(tmp);
            list->n--;
        }
        printf("Product deleted\n");
    }
    free(tmp);
}

//4. list all existing products
void list_product(List *list){
    system("CLS");
    NODE *tmp = list->head;
    while (tmp != NULL) {
        printf("Product code: %s\n", tmp->data.code);
        printf("Product name: %s\n", tmp->data.name);
        printf("Product category: %s\n", tmp->data.category);
        printf("Product price: $%f\n", tmp->data.price);
        printf("Product stock: %d\n", tmp->data.stock);
        printf("\n");
        tmp = tmp->next;
    }
}

node *new_node(product pro){
    node *head;
    head=(node*)malloc(sizeof(node));
    strcpy(head->p.code, pro.code);
    strcpy(head->p.name, pro.name);
    strcpy(head->p.category, pro.category);
    head->p.stock=pro.stock;
    head->p.price=pro.price;
    head->left=NULL;
    head->right=NULL;

    return head;
}
//function to help sort by code
node *insert_code(node *head,product pro){
    if(head==NULL){
        return new_node(pro);
    }
    else if(strcmp(head->p.code,pro.code)>0){
        head->left = insert_code(head->left,pro);
    }
    else if(strcmp(head->p.code,pro.code)<0){
        head->right = insert_code(head->right,pro);
    }

    return head;
}
// function to help sort by name
node *insert_name(node *head,product pro)
{
    if(head==NULL){
        return new_node(pro);
    }
    else if(strcmp(head->p.name,pro.name)>0){
        head->left=insert_code(head->left,pro);
    }
    else if(strcmp(head->p.name,pro.name)<0){
        head->right=insert_code(head->right,pro);
    }

    return head;
}
// print product by price in order
void inorder (node *tmp){
    if (tmp != NULL)
    {
        inorder (tmp -> left) ;
		printf("%s|%s|%s|$%.2f|%d\n",tmp->p.code,tmp->p.name,tmp->p.category,tmp->p.price,tmp->p.stock);
        inorder (tmp -> right) ;
    }
}
//5. function to sort product by code and name
void sort_product(List *list){
    system("CLS");
    FILE *fptr;
    int i = 1;
    node *head = NULL;
    int num;
    NODE *tmp = list->head;
    printf("1. Sort by code\n");
    printf("2. Sort by name\n");
    printf("Choose an operation: ");
    scanf("%d", &num);
    switch(num)
    {
    case 1:
        {
            while (tmp != NULL) {
                head = insert_code(head,tmp->data);
                tmp = tmp->next;
            }
            break;
        }
    case 2:
        {
            while (tmp != NULL) {
                head = insert_name(head,tmp->data);
                tmp = tmp->next;
            }
            break;
        }
    }

    printf("Code|Name|Category|Price|Stock\n");
    inorder(head);
}

//6.list all products by price
void list_product_price(List *list){
    system("CLS");
    float product_price;
    float price;
    printf("Input a product price: ");
    scanf("%f",&price);
    NODE *tmp = list->head;
    while (tmp != NULL) {
        product_price =( tmp->data.stock)*(tmp->data.price);
        if(product_price > price){
            printf("Product code: %s\n", tmp->data.code);
            printf("Product name: %s\n", tmp->data.name);
            printf("Product category: %s\n", tmp->data.category);
            printf("Product price: $%f\n", tmp->data.price);
            printf("Product stock: %d\n", tmp->data.stock);
            printf("\n\n");
        }
        tmp = tmp->next;
    }
}

int h(char *s){
    int slength=strlen(s);
    int i,sum=0;
    for(i=0;i<slength;i++){
        sum+=(int)s[i];
    }
    return sum%M;
}

void search(char *n){
    int key;
    key = h(n);
    hashing *tmp;
    tmp = arr[key];

    while(tmp){
        if(strcmp(tmp->p.code,n)== 0){
            printf("%s|%s\t|%s\t|$%.2f\t|%d\n",tmp->p.code,tmp->p.name,tmp->p.category,tmp->p.price,tmp->p.stock);
        }
        tmp=tmp->next;
    }
}

void search_pos(char *search_code,int *find,List *list){
    NODE *tmp;
    tmp = list->head;
    int j=0;
    while(tmp != NULL){
        *find = *find+1;
        if((strcmp(tmp->data.code,search_code)==0)){
            return;
        }
        tmp=tmp->next;
    }
    *find=0;
    return 0;
}

void remove_front (List *list){
    NODE *tmp = list->head;
    list->head = tmp->next;
    free(tmp);
    list->n--;
}

void insert_product(product pro){
    hashing *newnode = (hashing*)malloc(sizeof(hashing));
    int key;
    strcpy(newnode->p.code,pro.code);
    strcpy(newnode->p.name,pro.name);
    strcpy(newnode->p.category,pro.category);
    newnode->p.stock = pro.stock;
    newnode->p.price = pro.price;
    newnode->next=NULL;

    key = h(pro.code);

    if(arr[key] == NULL){
        arr[key] = newnode;
    }
    else{
        hashing *temp = arr[key];
        while(temp->next){
            temp = temp->next;
        }
        temp->next = newnode;
    }
}
//7. search product by using code
void search_product(List *list){
    system("CLS");
    FILE *fptr;
    int i = 1;
    float price;
    char search_code[50];
    NODE *tmp = list->head;
    while (tmp != NULL) {
        insert_product(tmp->data);
        tmp = tmp->next;
    }
    fflush(stdin);
    printf("Insert product code: ");
    gets(search_code);
    printf("Code\t|Name\t|Category|Price\t|Stock\n");
    search(search_code);
}
//8. function to save file
void save_file(List *list,char *name){
    system("CLS");
    FILE *fptr;
    product pro;

    fptr = fopen(name,"wb");

    if(!fptr){
        printf("Error loading\n");
        exit(1);
    }
    NODE *tmp = list->head;
    while (tmp != NULL) {
        strcpy(pro.code, tmp->data.code);
        strcpy(pro.name, tmp->data.name);
        strcpy(pro.category, tmp->data.category);
        pro.price = tmp->data.price;
        pro.stock = tmp->data.stock;
        fwrite(&pro,sizeof (product),1,fptr);
        tmp = tmp->next;
    }
    fclose(fptr);
    printf("File saved\n");
}

void insert_end (List *list, product pro){
    NODE *tmp = (NODE*)malloc(sizeof(NODE));
    NODE *tail = list->head;
    if (list->n == 0) {
        strcpy(tmp->data.code,pro.code);
        strcpy(tmp->data.name,pro.name);
        strcpy(tmp->data.category,pro.category);
        tmp->data.price = pro.price;
        tmp->data.stock = pro.stock;
        tmp->next = list->head;
        list->head = tmp;
        list->n++;
    } else {

        strcpy(tmp->data.code,pro.code);
        strcpy(tmp->data.name,pro.name);
        strcpy(tmp->data.category,pro.category);
        tmp->data.price = pro.price;
        tmp->data.stock = pro.stock;
        tmp->next = NULL;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = tmp;
        list->n++;
    }
}

void insertfront (List *list,product pro) {

    NODE *tmp = (NODE*)malloc(sizeof(NODE));
    strcpy(tmp->data.code,pro.code);
    strcpy(tmp->data.name,pro.name);
    strcpy(tmp->data.category,pro.category);
    tmp->data.price = pro.price;
    tmp->data.stock = pro.stock;
    tmp->next = list->head;
    list->head = tmp;
    list->n++;
}
//9. function to load data from file
void load_file(List *list,char *name){
    system("CLS");
    FILE *fptr;
    product pro;
    int n;
    int i;

    fptr=fopen(name,"rb");
    if(!fptr){
        printf("Error loading\n");
        exit(1);
    }
    while(fread(&pro, sizeof (product),1,fptr)==1){
        insert_end(list,pro);
    }
    printf("File loaded\n");
}

int main(){
    system("Color 71");
    List *list = create_list();
    int num;
    do
    {
        system("CLS");
        printf("==============================\n");
        printf("    SUPERMARKET MANAGEMENT    \n");
        printf("==============================\n");
		printf("1. Add a new product\n");
		printf("2. Modify a product\n");
		printf("3. Delete a product\n");
		printf("4. List all products\n");
		printf("5. Sort products\n");
		printf("6. List all products by price\n");
		printf("7. Search a product\n");
		printf("8. Save to file\n");
		printf("9. Load from file\n");

		printf("\nChoose an operation: ");
		scanf("%d", &num);
		switch(num)
		{
        case 1:
            add_product(list);
            break;
        case 2:
            modify_product(list);
            break;
        case 3:
            delete_product(list);
            break;
        case 4:
            list_product(list);
            break;
        case 5:
            sort_product(list);
            break;
        case 6:
            list_product_price(list);
            break;
        case 7:
            search_product(list);
            break;
        case 8:
            {
                system("CLS");
                char name[100];
                fflush(stdin);
                printf("Input file's name: ");
                gets(name);
                save_file(list, name);
                break;
            }
        case 9:
            {
                system("CLS");
                list = create_list();
                char name[100];
                fflush(stdin);
                printf("Input file's name: ");
                gets(name);
                load_file(list, name);
                break;
            }
        default:
            {
                printf("You input the invalid number.");
                break;
            }
		}
		printf("\nPress ENTER to continue transaction.\n");
    }
    while(getch()==13);
}
