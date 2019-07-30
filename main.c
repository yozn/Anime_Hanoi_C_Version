/*
name: yozn (Liou, yow shin)
mail: a757777@gmail.com
date: 2017/09/30
*/
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<time.h>
#define TXT "hanoi.txt"

void setcolor(int x)
{
    SetConsoleTextAttribute ( GetStdHandle ( STD_OUTPUT_HANDLE ),x);
    return;
}
void gotoxy(int xpos, int ypos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}
void draw_txt(char filename[])
{
    FILE *f=fopen(filename,"r");
    if(f==NULL)
    {
        printf("error read file!\n");
        exit(1);
    }
    int color,sign,x,y;
    fscanf(f,"%*[^\n]");
    while(fscanf(f,"%d %d %d %d",&color,&sign,&x,&y)!=EOF)
    {
        setcolor(color);
        gotoxy(x,y);
        printf("%c",sign);
    }
    fclose(f);
    setcolor(15);
    return;


}
int** create_diskinfo(int layers)
{
    int** temp;
    int i,colorcount=0;
    temp=(int**)malloc(layers*sizeof(int*));
    for(i=0; i<layers; i++)
    {
        temp[i]=(int*)malloc(2*sizeof(int));
    }
    for(i=0; i<layers; i++)
    {
        temp[i][0]=5+2*i;
        temp[i][1]=144+16*colorcount;
        colorcount++;
        if(colorcount==6)colorcount=0;
    }
    return temp;
}
void set_disk(int **diskinfo,int layerinfo[][2],int disk,int layer,int layers )
{
    int i,len=diskinfo[disk][0];
    setcolor(diskinfo[disk][1]);
    for(i=0; i<len; i++)
    {
        gotoxy(layerinfo[layer][0]-len/2+i,layerinfo[layer][1]-layers+disk);
        printf(" ");
    }
    return;
}
void move_disk(int **diskinfo,int layerinfo[][2],int diskindex,int layerindex1,int layerindex2)
{
    int i;
    int len=diskinfo[diskindex][0];
    setcolor(15);
    for(i=0; i<len; i++)
    {
        gotoxy(layerinfo[layerindex1][0]-len/2+i,layerinfo[layerindex1][1]);
        printf(" ");
    }
    layerinfo[layerindex1][1]++;
    setcolor(diskinfo[diskindex][1]);
    for(i=0; i<len; i++)
    {
        gotoxy(layerinfo[layerindex2][0]-len/2+i,layerinfo[layerindex2][1]-1);
        printf(" ");
    }
    layerinfo[layerindex2][1]--;
    setcolor(15);
}
void Hanoi_Tower(int** diskinfo,int layerinfo[][2],int layers,int n,char origin,char destination,char sup)
{
    if(n==1)
    {
        gotoxy(69,19);
        printf("Move disk %d from %c to %c.\n",n,origin,destination);
        move_disk(diskinfo,layerinfo,n-1,origin-65,destination-65);
        Sleep(400);
        return;
    }
    Hanoi_Tower(diskinfo,layerinfo,layers,n-1,origin,sup,destination);
    gotoxy(69,19);
    printf("Move disk %d from %c to %c.\n",n,origin,destination);
    move_disk(diskinfo,layerinfo,n-1,origin-65,destination-65);
    Sleep(400);
    Hanoi_Tower(diskinfo,layerinfo,layers,n-1,sup,destination,origin);
}
void relayer(int lay[][2])
{
    lay[0][0]=34;
    lay[0][1]=16;
    lay[1][0]=80;
    lay[1][1]=16;
    lay[2][0]=126;
    lay[2][1]=16;
}
int main()
{
    clock_t ta,tb;
     int layersinfo[][2]=
    {
        {34,16},
        {80,16},
        {126,16},
    };


    int **diskinfo;
    int layers=10,i=0;
    printf("Press any key after fit screen size.");
    getchar();
    while(1)
    {
        draw_txt(TXT);
        relayer(layersinfo);
        gotoxy(0,0);
        printf("Please input the number of layers of Hanoi Tower:");
        scanf("%d",&layers);
        CONSOLE_CURSOR_INFO cursor_info = {100, 0};
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
        getchar();

        diskinfo=create_diskinfo(layers);
        for(i=0; i<layers; i++)
        {
            set_disk(diskinfo,layersinfo,i,0,layers);
        }
        layersinfo[0][1]-=layers;
        getchar();
        setcolor(15);
        ta=clock();
        Hanoi_Tower(diskinfo,layersinfo,layers,layers,'A','C','B');
        tb=clock();
        gotoxy(0,20);
        printf("Process execution time : %.2lf s\nPress any key to continue .",(double)(tb-ta)/1000);
        getchar();
        system("cls");

    }



    return 0;
}
