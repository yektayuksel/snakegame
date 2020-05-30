#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define TABLESIZE 25
typedef struct node
{
    char data;
    int x;
    int y;
    struct node *next;
} node;
int bait_x, bait_y, snakeLen=0; ///Daha sonra ulasilip silinmesi gerektigi icin global declare edildi.
void createTable(char arr[][TABLESIZE]);
void printTable(char arr[][TABLESIZE]);
void generateBait(char arr[][TABLESIZE]);
void feedSnake(node *snake, char arr[][TABLESIZE]);
void createSnake(node *snake, char arr[][TABLESIZE]);
void move(char arr[][TABLESIZE], node *snake, char input);
void placeSnake(node *snake,char arr[][TABLESIZE]);
int main()
{
    srand(time(NULL));
    node *snake=(node*)malloc(sizeof(node));
    snake->data='O';
    snake->x=13;
    snake->y=15;
    snake->next=NULL;
    char table[TABLESIZE][TABLESIZE];
    createTable(table);
    createSnake(snake, table);
    placeSnake(snake, table);
    generateBait(table);
    char lastInput='W';
    char basla;
    while(1)
    {
        printf("\n\n\n\nBASLAMAK ICIN \"P\" TUSUN BASIN\n\n\n\n");
        scanf("%c", &basla);
        if(basla=='P' || basla=='p')
            break;
        else
            exit(0);
    }
    while(1)
    {
        while( !_kbhit() && lastInput != '\b' )
        {
            system("cls");
            Sleep(10);
            move(table, snake, lastInput);
            printTable(table);
        }
        lastInput = getche();
    }

    return 0;
}
void createTable(char arr[][TABLESIZE])
{
    int i,j;
    for(i=0; i<TABLESIZE; i++)
    {
        for(j=0; j<TABLESIZE; j++)
        {
            if(i==0 || i==TABLESIZE-1 || j==0 || j==TABLESIZE-1)
            {
                arr[i][j] = '*';
            }
            else
            {
                arr[i][j] = ' ';
            }
        }
    }
}
void printTable(char arr[][TABLESIZE])
{
    int i,j;
    for(i=0; i<TABLESIZE; i++)
    {
        for(j=0; j<TABLESIZE; j++)
        {
            printf("%2c", arr[i][j]);
        }
        printf("\n");
    }

    printf("                                    Puan: %5d", (snakeLen-5)*10);
}
void generateBait(char arr[][TABLESIZE])
{

    bait_x=(rand() % TABLESIZE-1)+1;
    bait_y=(rand() % TABLESIZE-1)+1;
    if(bait_x==0)
        bait_x++;
    if(bait_y==0)
        bait_y++;
    if(bait_x==TABLESIZE-1)
        bait_x--;
    if(bait_y==TABLESIZE-1)
        bait_y--;
    arr[bait_x][bait_y]='#';
}
void feedSnake(node *snake, char arr[][TABLESIZE])
{
    node *tmp=(node*)malloc(sizeof(node));
    tmp->data='O';
    node*iter=snake;
    while(iter->next!=NULL)
    {
        iter=iter->next;
    }
    iter->next=tmp;
    if(arr[iter->x+1][iter->y] != 'O')
    {
        tmp->x = iter->x+1;
        tmp->y=iter->y;
    }
    else if(arr[iter->x-1][iter->y] != 'O')
    {
        tmp->x = iter->x-1;
        tmp->y=iter->y;
    }
    else if(arr[iter->x][iter->y+1] != 'O')
    {
        tmp->y = iter->y+1;
        tmp->x = iter->x;
    }
    else if(arr[iter->x][iter->y-1] != 'O')
    {
        tmp->y = iter->y-1;
        tmp->x = iter->x;
    }
    tmp->next=NULL;
    snakeLen++;
}
void createSnake(node *snake, char arr[][TABLESIZE])
{
    for(int i=0; i<5; i++)
    {
        feedSnake(snake, arr);
    }
}
void move(char arr[][TABLESIZE], node *snake, char input)
{
    node*iter = snake;
    int i=0;
    int x=iter->x;
    int y= iter->y;
    int a,b;
    while(iter->next!=NULL)
    {

        if(i==0)
        {
            if(input=='W' || input== 'w')
            {
                iter->x--;
            }
            else if(input=='A' || input== 'a')
            {
                iter->y--;
            }
            else if(input=='S' || input== 's')
            {
                iter->x++;

            }
            else if(input=='D' || input== 'd')
            {
                iter->y++;
            }

            if(iter->x == bait_x && iter->y==bait_y)
            {
                feedSnake(snake, arr);
                generateBait(arr);
            }
            if(arr[iter->x][iter->y]=='*' || arr[iter->x][iter->y]=='O')
            {
                yandin();
            }
        }
        else if(i!=0)
        {
            a = iter->x;
            b = iter->y;
            iter->x = x;
            iter->y= y;
            x=a;
            y=b;
        }
        if(i==snakeLen-1)
        {
            arr[a][b]=' ';
        }
        i++;

        iter=iter->next;
    }
    placeSnake(snake, arr);
}
void placeSnake(node *snake,char arr[][TABLESIZE])
{
    node *iter=snake;
    while(iter->next!=NULL)
    {
        arr[iter->x][iter->y] = iter->data;
        iter=iter->next;
    }
}
void yandin()
{
    system("cls");

    for(int i=0; i<15; i++)
        printf("\n");

    printf("                      OYUNU KAYBETTINIZ\n                          Puan: %5d",(snakeLen-5)*10);
    for(int i=0; i<15; i++)
        printf("\n");
    getch();
    exit(0);
}

