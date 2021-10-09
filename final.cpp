#include<bits/stdc++.h>
#include<windows.h>
#include<mmsystem.h>
#include<iostream>
#include<graphics.h>
#include<vector>
#include<string>
#include<cstdlib>
using namespace std;

vector<int>L;
vector<int>error;
vector<int>C;
vector<string>Confidential;
vector<int>Word_th;
int step=0;
int M_st=0;
int tp;
int get_letter(char,string,string&);
int Max_tries;

struct player
{
    char name[50];
    int score;
};
FILE *file;
///Write and modify file
void modify(char nm[],int point)
{
    struct player data;
    int found=0;
    file = fopen("hangman.txt","rb+");
    while((fread(&data, sizeof(data), 1, file)) > 0 && found == 0)
    {
        if(strcmp(data.name,nm)==0)
        {
            found = 1;
            data.score += point;
            fseek(file,  - (long)sizeof(data), 1);
            fwrite(&data, sizeof(data), 1, file);
            //bgiout<<"Successfully updated.\n";
        }
    }
    fclose(file);
    if(found == 0)
    {
        file=fopen("hangman.txt","ab");
        strcpy(data.name,nm);
        data.score=point;
        fwrite(&data, sizeof(data), 1, file);
        fclose(file);
        //bgiout<<"Successfully inserted.\n";
    }
}
///Display data
void display(char nm[])
{
    struct player data;
    file = fopen("hangman.txt","rb");
    while((fread(&data, sizeof(data), 1, file)) > 0)
    {
        if(strcmp(data.name,nm)==0)
        {
            bgiout<<"Name of the player is : "<<data.name;
            bgiout<<"\nTotal score : "<<data.score<<endl;
        }
    }
    fclose(file);
    cleardevice();
}

int fun()
{
    int i;
    for(i=0; i<=1000; i++)
    {
        L.push_back(0);
        error.push_back(0);
        C.push_back(0);
        Confidential.push_back("\0");
        Word_th.push_back(0);
    }

}

int main()
{
    fun();
    initwindow(1600,1000);
    setbkcolor(BLUE);
    setcolor(YELLOW);
    ///playing background music
    PlaySound("bmusic.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
    ///-----------portion1----------///
    settextstyle(DEFAULT_FONT,HORIZ_DIR,6);
q:
    int i,j;
    for(i=10; i<=120; i+=5)
    {
        outtextxy(620,i,"WELCOME");
        delay(210);
        if(i<120)
        {
            cleardevice();
        }
    }
    for(i=120,j=1360; i<=680,j>=760; i+=60,j-=60)
    {
        cleardevice();
        setcolor(YELLOW);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,6);
        outtextxy(620,120,"WELCOME");///correction
        setcolor(WHITE);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,5);
        outtextxy(i,170,"T");///correction
        outtextxy(j,170,"O");///correction
        delay(130);
    }

    for(i=480; i>=220; i-=20)
    {
        cleardevice();
        setcolor(YELLOW);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,6);
        outtextxy(620,120,"WELCOME");
        setcolor(WHITE);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,5);
        outtextxy(730,170,"TO");///correction
        setcolor(YELLOW);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
        outtextxy(500,i,"Hangman Codding Game");
        delay(255);
    }
    ///------portion2----------///
    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    outtextxy(60,350,"->>Press enter for next");
    setbkcolor(GREEN);
    getch();
    cleardevice();

    ///-----------------------------portion3-----------------------------///

a:
    cleardevice();
    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    outtextxy(100,60,"press'S' for Start Game ");
    outtextxy(100,100,"Press'Q' for Quit");
    outtextxy(100,140,"Press'I' for Information");
    setbkcolor(RED);
    getch();
    cleardevice();
    if(GetAsyncKeyState('S'))
    {
        settextstyle(SCRIPT_FONT,HORIZ_DIR,5);
        for( i=10; i<=100; i+=10)
        {
            outtextxy(i,100,"Ready");
            delay(120);
            if(i<100)
            {
                cleardevice();
            }
        }
        for(i=10; i<=100; i+=10)
        {
            cleardevice();
            outtextxy(100,100,"Ready");
            outtextxy(230,i,"Stedy");
            delay(120);
        }
        for(i=480; i>=350; i-=20)
        {
            cleardevice();
            outtextxy(100,100,"Ready");
            outtextxy(240,100,"Stedy");
            outtextxy(i,100,"go now");
            delay(120);
        }
        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        outtextxy(60,350,"->>Press enter for next");
        setbkcolor(LIGHTMAGENTA);
        getch();
        cleardevice();
    }
    else if(GetAsyncKeyState('Q'))
    {
        settextstyle(DEFAULT_FONT,HORIZ_DIR,5);
        outtextxy(200,200,"Exit");
        getch();
        return 0;
    }
    else if(GetAsyncKeyState('I'))
    {
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(30,20,"* Hangman is a word game where the goal is simply to find the missing word or words.");
        outtextxy(30,60,"* You will be presented with a number of asterisk(*) representing the missing letters you need");
        outtextxy(30,100,"to find.");
        outtextxy(30,140,"* Use the keyboard to guess a letter (I recommend starting with vowels).");
        outtextxy(30,180,"* If your chosen letter exists in the answer, then all places in the answer where that letter");
        outtextxy(30,210,"appear will be revealed.");
        outtextxy(30,240,"* After you've revealed several letters, you may be able to guess what the answer is and fill");
        outtextxy(30,270,"in the remaining letters.");
        outtextxy(30,310,"* Be warned, every time you guess a letter wrong you loose a life and the hangman will continue");
        outtextxy(30,340,"to move closer to the swing.");
        outtextxy(30,370,"* Solve the puzzle before the hangman dies.");
        outtextxy(30,410,"* If you're a fan of word puzzles, make sure you check out our games also.");
        //setbkcolor(WHITEONBLACK);
        getch();
        cleardevice();
        goto a;
    }
    else if(GetAsyncKeyState(VK_LEFT))
    {
        goto q;
    }
    else
    {
        goto a;
    }
    string wordset1[]=
    {
        "tongue","basketball",
        "introduce","currant",
        "forest","watermelon",
        "include","ecology","shoulder","cricket"
    }; /// 1 st level
    string wordset2[]=
    {
        "receptionist","wednesday",
        "cockroach","rockstar",
        "airplane","ambassador","gorilla",
        "parineeta","motorcycle","spring"
    }; ///2nd level
    string wordset3[]=
    {
        "director","bangladesh",
        "descendants","pumpkin",
        "journalist","spaceship","streetlight",
        "confectioner","grandmother","cameroon"
    }; ///3rd level
    string word;
    int x;
    //srand(time(NULL));///initialization
    int level=1,cnt=0,f=0;
    int total_point=0;
b:
    cleardevice();
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    outtextxy(30,30,"->>Press 1 for Easy level. ");
    outtextxy(30,60,"->>press 2 for Medium level.");
    outtextxy(30,90,"->>press 3 for hard level ");
    getch();
    //setbkcolor(WHITE);
    if(GetAsyncKeyState('1'))
    {
        level=1;
        setbkcolor(RED);
    }
    else if(GetAsyncKeyState('2'))
    {
        level=2;
        setbkcolor(GREEN);
    }
    else if(GetAsyncKeyState('3'))
    {
        level=3;
        setbkcolor(BLUE);
    }
    else if(GetAsyncKeyState(VK_LEFT))
    {
        goto a;
    }
    else
    {
        cleardevice();
        goto b;
    }

    L[0]=level;///track level

    cleardevice();///clear windows
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    if(level==1)
    {
        outtextxy(10,20,"-> Easy level running.");
    }
    else if(level==2)
    {
        outtextxy(10,20,"->Medium level running");
    }
    else
    {
        outtextxy(10,20,"->Hard level running");
    }
    char nm[50];
    //outtextxy(5,70,"Enter the name of the player : ");
    bgiout<<"Enter the name of the player : ";
    outstreamxy(10,40);
    cin>>nm;
    modify(nm,tp);
    while(cnt<3)
    {
        cout<<"Enter press: ";
        getch();
        ///select secret word section ///
        srand(time(NULL));
        x=rand()%10;/// form random value
        Word_th[step]=x;///track word;
        if(level==1)
        {
            Max_tries=7;
            word=wordset1[x];
            //if(x==1)
            //cout
        }
        else if(level==2)
        {
            Max_tries=5;
            word=wordset2[x];
        }
        else
        {
            Max_tries=3;
            word=wordset3[x];
        }


        char charecter;
        string confidential(word.size(),'*');///locking word with *

        Confidential[step]=confidential;///track confidential

        int wrong=0;
        int j;///used to denote outstream's y value
        int d;///how much increase or decrease vertics
        if(level==1)
        {
            d=15;
        }
        else if(level==2)
        {
            d=21;
        }
        else
        {
            d=35;
        }
///..............initialization of vertics that is used to draw..................////
        int ax,ay,bx,by,cx,cy,dx,dy,ex,ey,fx,fy,gx,gy,hx,hy,ix,iy,jx,jy,kx,ky,lx,ly,px,py;
        ax=400;
        ay=200;
        ///line(400,200,500,200);/// for ab
        bx=500;
        by=ay;
        ///line(400,200,400,365);///  for ac
        cx=ax;
        cy=ay+165;
        ///line(400,365,650,365);///   for cd
        dx=cx+250;
        dy=cy;
        ///line(450,200,450,240);/// for ef
        ex=ax+50;
        ey=ay;
        fx=ex;
        fy=ey+20;
/// center of head (fx,fy+10) because radius is 10
///ellipse(449,245,0,360,12,6); or ellipse(fx-1,fy+5,0,360,12,6);///roof
///ellipse(449,245,0,360,10,5);or  ellipse(fx-1,fy+5,0,360,10,5);///roof

///arc(555-dx,314,200,340,6);///leap

///line(555-dx,325,555-dx,355);///for body (gh)
        gx=fx+105;
        gy=dy-40;
        hx=gx;
        hy=dy-10;
///line(555-dx,335,542-dx,325);///for pl (left hand)
        px=gx;
        py=gy+10;
        lx=px-13;
        ly=py-10;
///line(555-dx,335,568-dx,325);///for pk (right hand)
        kx=px+13;
        ky=py-10;///ky=ly
///line(555-dx,355,542-dx,365);/// for hi
        ix=hx-13;
        iy=hy+10;
///line(555-dx,355,568-dx,365);/// for hj
        jx=hx+13;
        jy=hy+10;
        int St_i=0;
///...........................................................................////
        while(wrong<Max_tries)
        {

c:
            cleardevice();
            if(level==1)
            {
                //setbkcolor(RED);
                //z=7-wrong;
                bgiout<<"-> Easy level running..."<<endl;
                bgiout<<"Number of maximum wrong guess is: 7"<<endl;
                bgiout<<"Remaining chance: "<<7-wrong<<endl;
                display(nm);///Display name and score
                outstreamxy(40,10);
                setcolor(BLACK);
                ///clues
                if(x==0||x==8)
                    outtextxy(5,100,"****** BODY ******");
                else if(x==1||x==9)
                    outtextxy(5,100,"****** SPORTS ******");
                else if(x==2||x==6)
                    outtextxy(5,100,"****** VERBS ******");
                else if(x==3||x==5)
                    outtextxy(5,100,"****** FRUITS ******");
                else if(x==4||x==7)
                    outtextxy(5,100,"****** NATURE ******");
                setcolor(WHITE);
                ///playing background music
                PlaySound("bmusic.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
            }
            else if(level==2)
            {
                bgiout<<"-> Medium level running..."<<endl;
                bgiout<<"Number of maximum wrong guess is: 5"<<endl;
                bgiout<<"Remaining chance: "<<5-wrong<<endl;
                display(nm);///Display name and score
                outstreamxy(40,10);
                setcolor(BLACK);
                ///clues
                if(x==0||x==5)
                    outtextxy(5,100,"****** PROFESSIONS ******");
                else if(x==1||x==9)
                    outtextxy(5,100,"****** CALENDAR ******");
                else if(x==2||x==6)
                    outtextxy(5,100,"****** ANIMALS ******");
                else if(x==3||x==7)
                    outtextxy(5,100,"****** FILM ******");
                else if(x==4||x==8)
                    outtextxy(5,100,"****** TRANSPORT ******");
                setcolor(WHITE);
                ///playing background music
                PlaySound("bmusic.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
            }
            else
            {
                bgiout<<"-> Hard level running..."<<endl;
                bgiout<<"Number of maximum wrong guess is: 3"<<endl;
                bgiout<<"Remaining chance: "<<3-wrong<<endl;
                display(nm);///Display name and score
                outstreamxy(40,10);
                setcolor(BLACK);
                ///Clues
                if(x==0)
                    outtextxy(5,100,"****** MUSIC ******");
                else if(x==1||x==9)
                    outtextxy(5,100,"****** COUNTRIES ******");
                else if(x==2||x==8)
                    outtextxy(5,100,"****** FAMILY ******");
                else if(x==3)
                    outtextxy(5,100,"****** FOOD ******");
                else if(x==4||x==7)
                    outtextxy(5,100,"****** PROFESSIONS ******");
                else if(x==5)
                    outtextxy(5,100,"****** TRANSPORT ******");
                else if(x==6)
                    outtextxy(5,100,"****** IN THE CITY ******");
                setcolor(WHITE);
                ///playing background music
                PlaySound("bmusic.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
            }
            ///draw structure:
            line(ax,ay,bx,by);///line ab
            line(ax,ay,cx,cy);///line ac
            line(cx,cy,dx,dy);///line cd
            line(ex,ey,fx,fy);///line ef
            ellipse(fx-1,fy+5,0,360,12,6);///roof1
            ellipse(fx-1,fy+5,0,360,10,5);///roof2
            line(555-dx,325,555-dx,355);///body (gh)
            circle(555-dx,315,10);///head
            circle(gx,gy-10,10);///head
            circle(552-dx,311,2);///eye
            circle(558-dx,311,2);///eye
            circle(gx-3,(gy-10)-4,2);///eye
            circle(gx+3,(gy-10)-4,2);///eye
            arc(555-dx,314,200,340,6);///leap
            arc(gx,(gy-10)-1,200,340,6);///leap
            line(gx,gy,hx,hy);///body
            line(px,py,lx,ly);///right hand
            line(px,py,kx,ky);///left hand
            line(hx,hy,ix,iy);/// right leg
            line(hx,hy,jx,jy);/// left leg
            j=120;
            ///drawing keyboard
            rectangle(890,245,1260,365);
            line(930,245,930,365);
            line(970,245,970,365);
            line(1010,245,1010,365);
            line(1050,245,1050,365);
            line(1090,245,1090,365);
            line(1130,245,1130,365);
            line(1175,245,1175,365);
            line(1210,245,1210,365);
            line(890,285,1260,285);
            line(890,325,1260,325);
            settextstyle(EUROPEAN_FONT,HORIZ_DIR,2);
            outtextxy(900,255,"A");
            outtextxy(940,255,"B");
            outtextxy(980,255,"C");
            outtextxy(1020,255,"D");
            outtextxy(1060,255,"E");
            outtextxy(1100,255,"F");
            outtextxy(1140,255,"G");
            outtextxy(1180,255,"H");
            outtextxy(1220,255,"I");
            outtextxy(900,295,"J");
            outtextxy(940,295,"K");
            outtextxy(980,295,"L");
            outtextxy(1020,295,"M");
            outtextxy(1060,295,"N");
            outtextxy(1100,295,"O");
            outtextxy(1140,295,"P");
            outtextxy(1180,295,"Q");
            outtextxy(1220,295,"R");
            outtextxy(900,335,"S");
            outtextxy(940,335,"T");
            outtextxy(980,335,"U");
            outtextxy(1020,335,"V");
            outtextxy(1060,335,"W");
            outtextxy(1100,335,"X");
            outtextxy(1140,335,"Y");
            outtextxy(1180,335,"Z");
            //getch();
            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
            bgiout<<"Secret word: "<<confidential<<endl;
            outstreamxy(10,j);
            j+=20;
            bgiout<<"Enter a character: ";
            outstreamxy(10,j);
            getch();

            cout<<"1,step: "<<step <<" level: "<<L[step]<<" total_point: "<<C[step]<<" wrong: "<<error[step]<<" Confidential "<<Confidential[step]<<"Wordth:"<<Word_th[step]<<endl;

            if(GetAsyncKeyState('A'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(900,255,"A");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='a';
                bgiout<<"a"<<endl;
                //Beep(8000,500);
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("A.wav"),NULL,SND_SYNC);///Tune for A
            }
            else if(GetAsyncKeyState('B'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(940,255,"B");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='b';
                bgiout<<"b"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("B.wav"),NULL,SND_SYNC);///Tune for B
            }
            else if(GetAsyncKeyState('C'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(980,255,"C");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='c';
                bgiout<<"C"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("C.wav"),NULL,SND_SYNC);///Tune for C
            }
            else if(GetAsyncKeyState('D'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1020,255,"D");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='d';
                bgiout<<"d"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("D.wav"),NULL,SND_SYNC);///Tune for D
            }
            else if(GetAsyncKeyState('E'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1060,255,"E");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='e';
                bgiout<<"e"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("E.wav"),NULL,SND_SYNC);///Tune for E
            }
            else if(GetAsyncKeyState('F'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1100,255,"F");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='f';
                bgiout<<"f"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("F.wav"),NULL,SND_SYNC);///Tune for F
            }
            else if(GetAsyncKeyState('G'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1140,255,"G");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='g';
                bgiout<<"g"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("G.wav"),NULL,SND_SYNC);///Tune for G
            }
            else if(GetAsyncKeyState('H'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1180,255,"H");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='h';
                bgiout<<"h"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("H.wav"),NULL,SND_SYNC);///Tune for H
            }
            else if(GetAsyncKeyState('I'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1220,255,"I");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='i';
                bgiout<<"i"<<endl;
                outstreamxy(260,j);
                step++;
                PlaySound(TEXT("I.wav"),NULL,SND_SYNC);///Tune for I
            }
            else if(GetAsyncKeyState('J'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(900,295,"J");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='j';
                bgiout<<"j"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("J.wav"),NULL,SND_SYNC);///Tune for J
            }
            else if(GetAsyncKeyState('K'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(940,295,"K");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='k';
                bgiout<<"k"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("H.wav"),NULL,SND_SYNC);///Tune for K
            }
            else if(GetAsyncKeyState('L'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(980,295,"L");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='l';
                bgiout<<"l"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("B.wav"),NULL,SND_SYNC);///Tune for L
            }
            else if(GetAsyncKeyState('M'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1020,295,"M");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='m';
                bgiout<<"m"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("G.wav"),NULL,SND_SYNC);///Tune for M
            }
            else if(GetAsyncKeyState('N'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1060,295,"N");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='n';
                bgiout<<"n"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("C.wav"),NULL,SND_SYNC);///Tune for N
            }
            else if(GetAsyncKeyState('O'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1100,295,"O");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='o';
                bgiout<<"o"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("J.wav"),NULL,SND_SYNC);///Tune for O
            }
            else if(GetAsyncKeyState('P'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1140,295,"P");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='p';
                bgiout<<"p"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("A.wav"),NULL,SND_SYNC);///Tune for P
            }
            else if(GetAsyncKeyState('Q'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1180,295,"Q");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='q';
                bgiout<<"q"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("F.wav"),NULL,SND_SYNC);///Tune for Q
            }
            else if(GetAsyncKeyState('R'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1220,295,"R");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='r';
                bgiout<<"r"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("H.wav"),NULL,SND_SYNC);///Tune for R
            }
            else if(GetAsyncKeyState('S'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(900,335,"S");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='s';
                bgiout<<"s"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("I.wav"),NULL,SND_SYNC);///Tune for S
            }
            else if(GetAsyncKeyState('T'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(940,335,"T");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='t';
                bgiout<<"t"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("E.wav"),NULL,SND_SYNC);///Tune for T
            }
            else if(GetAsyncKeyState('U'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(980,335,"U");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='u';
                bgiout<<"u"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("J.wav"),NULL,SND_SYNC);///Tune for U
            }
            else if(GetAsyncKeyState('V'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1020,335,"V");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='v';
                bgiout<<"v"<<endl;
                outstreamxy(260,j);
                step++;
                PlaySound(TEXT("C.wav"),NULL,SND_SYNC);///Tune for V
            }
            else if(GetAsyncKeyState('W'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1060,335,"W");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='w';
                bgiout<<"w"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("D.wav"),NULL,SND_SYNC);///Tune for W
            }
            else if(GetAsyncKeyState('X'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1100,335,"X");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='x';
                bgiout<<"x"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("B.wav"),NULL,SND_SYNC);///Tune for X
            }
            else if(GetAsyncKeyState('Y'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1140,335,"Y");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='y';
                bgiout<<"y"<<endl;
                outstreamxy(260,j);
                step++;
                PlaySound(TEXT("A.wav"),NULL,SND_SYNC);///Tune for Y
            }
            else if(GetAsyncKeyState('Z'))
            {
                setcolor(BLACK);
                settextstyle(10,HORIZ_DIR,4);
                outtextxy(1180,335,"Z");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                charecter='z';
                bgiout<<"z"<<endl;
                outstreamxy(260,j);
                step++;
                M_st=step;
                PlaySound(TEXT("E.wav"),NULL,SND_SYNC);///Tune for Z
            }
            else if(GetAsyncKeyState(VK_LEFT))
            {
                St_i=step-1;///step decress for pressing left button
                if(St_i>=0)
                {
                    if(L[St_i]==1)
                    {
                        d=15;
                    }
                    else if( L[St_i]==2)
                    {
                        d=21;
                    }
                    else
                    {
                        d=35;
                    }
                    if(L[St_i]==L[step])///decide to about wrong number either decress or not
                    {
                        if(error[St_i]<error[step])
                        {
                            if(fy-d>=220)

                            {
                                for(i=0; i<=d; i+=2)
                                {
                                    cleardevice();
                                    if(level==1)
                                    {
                                        outtextxy(40,10,"-> Easy level runnig...");
                                    }
                                    else if(level==2)
                                    {
                                        outtextxy(40,10,"-> Medium level runnig...");
                                    }
                                    else
                                    {
                                        outtextxy(40,10,"-> Hard level runnig...");
                                    }
                                    //bgiout<<"secret word: "<<confidential<<endl;
                                    bgiout<<"Back"<<endl;
                                    outstreamxy(10,120);
                                    ////  kichu line likhini ////
                                    line(ax,ay,bx,by);///line ab
                                    line(ax,ay,cx,cy);///line ac
                                    line(cx,cy,dx,dy);///line cd
                                    line(ex,ey,fx,fy-i);///line ef
                                    ellipse(fx-1,fy+5-i,0,360,12,6);///roof1
                                    ellipse(fx-1,fy+5-i,0,360,10,5);///roof2
                                    circle(gx+i,gy-10,10);///head
                                    circle(gx-3+i,(gy-10)-4,2);///eye
                                    circle(gx+3+i,(gy-10)-4,2);///eye
                                    arc(gx+i,(gy-10)-1,200,340,6);///leap
                                    line(gx+i,gy,hx+i,hy);///body
                                    line(px+i,py,lx+i,ly);///right hand
                                    line(px+i,py,kx+i,ky);///left hand
                                    line(hx+i,hy,ix+i,iy);/// right leg
                                    line(hx+i,hy,jx+i,jy);/// left leg

                                    delay(100);
                                }
                                fy-=d;
                                gx+=d;
                                hx+=d;
                                px+=d;
                                lx+=d;
                                kx+=d;
                                ix+=d;
                                jx+=d;
                            }
                        }
                    }
                    else
                    {
                        cout<<"wrong:"<<error[St_i]<<endl;
                        if(error[St_i]>0)
                        {
                            for(i=0; i<=d*error[St_i]; i+=2)
                            {
                                cleardevice();
                                if(level==1)
                                {
                                    outtextxy(40,10,"-> Easy level runnig...");
                                }
                                else if(level==2)
                                {
                                    outtextxy(40,10,"-> Medium level runnig...");
                                }
                                else
                                {
                                    outtextxy(40,10,"-> Hard level runnig...");
                                }
                                //bgiout<<"secret word: "<<confidential<<endl;
                                bgiout<<"Back"<<endl;
                                outstreamxy(10,120);
                                ////  kichu line likhini ////
                                line(ax,ay,bx,by);///line ab
                                line(ax,ay,cx,cy);///line ac
                                line(cx,cy,dx,dy);///line cd
                                line(ex,ey,fx,fy+i);///line ef
                                ellipse(fx-1,fy+5+i,0,360,12,6);///roof1
                                ellipse(fx-1,fy+5+i,0,360,10,5);///roof2
                                circle(gx-i,gy-10,10);///head
                                circle(gx-3-i,(gy-10)-4,2);///eye
                                circle(gx+3-i,(gy-10)-4,2);///eye
                                arc(gx-i,(gy-10)-1,200,340,6);///leap
                                line(gx-i,gy,hx-i,hy);///body
                                line(px-i,py,lx-i,ly);///right hand
                                line(px-i,py,kx-i,ky);///left hand
                                line(hx-i,hy,ix-i,iy);/// right leg
                                line(hx-i,hy,jx-i,jy);/// left leg

                                delay(100);
                            }
                            fy+=d;
                            gx-=d;
                            hx-=d;
                            px-=d;
                            lx-=d;
                            kx-=d;
                            ix-=d;
                            jx-=d;
                        }
                    }
                    {
                        confidential=Confidential[St_i];
                        wrong=error[St_i];
                        total_point=C[St_i];
                        level=L[St_i];
                        x=Word_th[St_i];
                        if(level==1)
                        {
                            word=wordset1[x];
                        }
                        else if(level==2)
                        {
                            word=wordset2[x];
                        }
                        else
                        {
                            word=wordset3[x];
                        }
                    }
                    step=St_i;
                    goto c;
                }
                else
                {
                    goto b;

                }

            }
            else if(GetAsyncKeyState(VK_RIGHT))
            {
                St_i=step+1; ///step decress for pressing left button
                if(St_i<=M_st)
                {
                    if(L[St_i]==1)
                    {
                        d=15;
                    }
                    else if( L[St_i]==2)
                    {
                        d=21;
                    }
                    else
                    {
                        d=35;
                    }
                    if(L[St_i]==L[step])///decide to about wrong number either decress or not
                    {
                        if(error[St_i]>error[step])
                        {
                            if(fy+d<=325)

                            {
                                for(i=0; i<=d; i+=2)
                                {
                                    cleardevice();
                                    if(level==1)
                                    {
                                        outtextxy(40,10,"-> Easy level runnig...");
                                    }
                                    else if(level==2)
                                    {
                                        outtextxy(40,10,"-> Medium level runnig...");
                                    }
                                    else
                                    {
                                        outtextxy(40,10,"-> Hard level runnig...");
                                    }
                                    //bgiout<<"secret word: "<<confidential<<endl;
                                    bgiout<<"Back"<<endl;
                                    outstreamxy(10,120);
                                    ////  kichu line likhini ////
                                    line(ax,ay,bx,by);///line ab
                                    line(ax,ay,cx,cy);///line ac
                                    line(cx,cy,dx,dy);///line cd
                                    line(ex,ey,fx,fy+i);///line ef
                                    ellipse(fx-1,fy+5+i,0,360,12,6);///roof1
                                    ellipse(fx-1,fy+5+i,0,360,10,5);///roof2
                                    circle(gx-i,gy-10,10);///head
                                    circle(gx-3-i,(gy-10)-4,2);///eye
                                    circle(gx+3-i,(gy-10)-4,2);///eye
                                    arc(gx-i,(gy-10)-1,200,340,6);///leap
                                    line(gx-i,gy,hx-i,hy);///body
                                    line(px-i,py,lx-i,ly);///right hand
                                    line(px-i,py,kx-i,ky);///left hand
                                    line(hx-i,hy,ix-i,iy);/// right leg
                                    line(hx-i,hy,jx-i,jy);/// left leg

                                    delay(100);
                                }
                                fy+=d;
                                gx-=d;
                                hx-=d;
                                px-=d;
                                lx-=d;
                                kx-=d;
                                ix-=d;
                                jx-=d;
                            }
                        }
                    }
                    else
                    {
                        confidential=Confidential[St_i];
                        wrong=error[St_i];
                        total_point=C[St_i];
                        level=L[St_i];
                        x=Word_th[St_i];
                        if(level==1)
                        {
                            word=wordset1[x];
                        }
                        else if(level==2)
                        {
                            word=wordset2[x];
                        }
                        else
                        {
                            word=wordset3[x];
                        }
                    }
                    step=St_i;
                    goto c;
                }
                else
                {
                    goto c;
                }

            }
            else
            {
                goto c;
            }
            j+=90;
            if(get_letter(charecter,word,confidential)==0)
            {
                wrong++;
                int i;
                delay(100);
                for(i=0; i<=d; i+=2)
                {
                    cleardevice();
                    if(level==1)
                    {
                        outtextxy(40,10,"-> Easy level runnig...");
                    }
                    else if(level==2)
                    {
                        outtextxy(40,10,"-> Medium level runnig...");
                    }
                    else
                    {
                        outtextxy(40,10,"-> Hard level runnig...");
                    }
                    bgiout<<"secret word: "<<confidential<<endl;
                    bgiout<<"Wrong gess"<<endl;
                    outstreamxy(10,120);
                    ////  kichu line likhini ////
                    line(ax,ay,bx,by);///line ab
                    line(ax,ay,cx,cy);///line ac
                    line(cx,cy,dx,dy);///line cd
                    line(ex,ey,fx,fy+i);///line ef
                    ellipse(fx-1,fy+5+i,0,360,12,6);///roof1
                    ellipse(fx-1,fy+5+i,0,360,10,5);///roof2
                    circle(gx-i,gy-10,10);///head
                    circle(gx-3-i,(gy-10)-4,2);///eye
                    circle(gx+3-i,(gy-10)-4,2);///eye
                    arc(gx-i,(gy-10)-1,200,340,6);///leap
                    line(gx-i,gy,hx-i,hy);///body
                    line(px-i,py,lx-i,ly);///right hand
                    line(px-i,py,kx-i,ky);///left hand
                    line(hx-i,hy,ix-i,iy);/// right leg
                    line(hx-i,hy,jx-i,jy);/// left leg
                    delay(100);
                }
                fy+=d;
                gx-=d;
                hx-=d;
                px-=d;
                lx-=d;
                kx-=d;
                ix-=d;
                jx-=d;
            }
            else
            {
                bgiout<<"Correct gess"<<endl<<"press enter for next"<<endl;
                outstreamxy(10,j);
                getch();
            }
            L[step]=level;
            Confidential[step]=confidential; /// tracking confidential
            error[step]=wrong; /// traking wrong
            Word_th[step]=x;///tracking word_th number
            if(word==confidential)
            {
                cnt++;
                if(level==1)
                {
                    tp=7-wrong;
                }
                else if(level==2)
                {
                    tp=(5-wrong)*2;
                }
                else if(level==3)
                {
                    tp=(3-wrong)*3;
                }
                modify(nm,tp);

                bgiout<<"The word is :"<<word<<endl;
                PlaySound(TEXT("WIN.wav"),NULL,SND_SYNC);///Success Tune
                bgiout<<"Congratulations!!"<<endl;
                bgiout<<"You win the game."<<endl<<endl<<endl<<endl;
                bgiout<<"->>If you want to play again, press enter"<<endl;
                outstreamxy(10,j+=60);
                getch();
                break;
            }

            C[step]=total_point;///tracking point
            cout<<"step: "<<step <<" level: "<<L[step]<<" total_point: "<<C[step]<<" worng: "<<error[step]<<" Confidential "<<Confidential[step]<<"Wordth:"<<Word_th[step]<<endl;



        }
        if(wrong==Max_tries)
        {
            int i;
            PlaySound("LOSE.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);///Failure Tune
            for(i=1; i<=3; i++)
            {
                cleardevice();
                settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                setcolor(RED);
                outtextxy(20,30,"You have loss the game");
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                bgiout<<"Secret word is "<<word<<endl;
                outstreamxy(20,70);
                line(ax,ay,bx,by);///line ab
                line(ax,ay,cx,cy);///line ac
                line(cx,cy,dx,dy);///line cd
                line(ex,ey,fx,fy);///line ef
                ellipse(fx-1,fy+5,0,360,12-i,6-i);///roof1
                ellipse(fx-1,fy+5,0,360,10-i,5-i);///roof2
                circle(gx,gy-10,10);///head
                circle(gx-3,(gy-10)-4,2);///eye
                circle(gx+3,(gy-10)-4,2);///eye
                arc(gx,(gy-10)-1,200,340,6);///leap
                line(gx,gy,hx,hy);///body
                line(px,py,lx,ly);///right hand
                line(px,py,kx,ky);///left hand
                line(hx,hy,ix,iy);/// right leg
                line(hx,hy,jx,jy);/// left leg
                delay(100);

            }
            for(i=1; i<=60; i++)
            {
                cleardevice();
                settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                setcolor(YELLOW);
                outtextxy(20,30,"You have loss the game.");
                delay(10);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                setcolor(WHITE);
                bgiout<<"Secret word is :"<<word<<endl;
                outstreamxy(20,70);
                line(ax,ay,bx,by);///line ab
                line(ax,ay,cx,cy);///line ac
                line(cx,cy,dx,dy);///line cd
                line(ex,ey,fx,gy-20-i);///line ef
                circle(gx,gy-10-i,10);///head
                circle(gx-3,(gy-10)-4-i,2);///eye
                circle(gx+3,(gy-10)-4-i,2);///eye
                arc(gx,(gy-10)-1-i,200,340,6);///leap
                line(gx,gy-i,hx,hy-i);///body
                line(px,py-i,lx,ly-i);///right hand
                line(px,py-i,kx,ky-i);///left hand
                line(hx,hy-i,ix,iy-i);/// right leg
                line(hx,hy-i,jx,jy-i);/// left leg
                delay(100);
            }
            break;
        }
        else if(cnt==3&&level<3)
        {
            step++;
            level++;
            cnt=0;
            wrong=0;
            cleardevice();
            setbkcolor(WHITE);
            if(level==1)
            {
                setbkcolor(RED);
                outtextxy(40,10,"-> Easy level runnig...");
            }
            else if(level==2)
            {
                setbkcolor(GREEN);
                outtextxy(40,10,"-> Medium level runnig...");
            }
            else
            {
                setbkcolor(BLUE);
                outtextxy(40,10,"-> Hard level runnig...");
            }
            getch();
        }
        else if(cnt==3&&level==3)
        {
            step++;
            cleardevice();
            outtextxy(40,10,"You have successfully overcome all level.");
            outtextxy(40,60,"The Game Is Over.");
            getch();
            return 0;
        }
    }
    cin.ignore();
    cin.get();
    return 0;
}
int get_letter(char guess,string word,string &secret)
{
    int x=word.size();
    int i,match=0;
    for(i=0; i<x; i++)
    {
        if(word[i]==guess)
        {
            secret[i] = guess;///unlock the correct match
            match=1;
        }
    }
    return match;
    getch();
}

