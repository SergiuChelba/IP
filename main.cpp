#include <iostream>

#include <graphics.h>

#include <winbgim.h>

#include <conio.h>

#include <string>

#include<fstream>

#include<ctime>

#include<vector>
#include <unistd.h>
#include <chrono>
#include <sstream>
#include <cstdint>
using namespace std;
#define BLUE 1
#define BLUEDR 2
#define BLUEBR 3
#define RED 4
#define REDDR 5
#define REDBR 6
//#define GREEN 7
#define GREENDR 8
#define GREENBR 9
#define PURPLE 10
#define PURPLEDR 11
#define PURPLEBR 12
#define YELLOW 13
#define YELLOWDR 14
#define YELLOWBR 15
#define BLANK 0
#define REFRESH 0
#define ROWS 20
#define COLS 15

// Shapes
#define SHAPE_I  100
#define SHAPE_T  101
#define SHAPE_L  102
#define SHAPE_L2 103
#define SHAPE_O  104
#define SHAPE_S  105
#define SHAPE_S2 106

// Directions
#define RIGHT 201
#define DOWN  203
#define TOP   30
#define LEFT  160

// Keys
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13
#define KEY_SPACE 32



//Functions
void Brick(int x, int y, char Color);
void InitPalette();
int scor_aux;
void PrintScore();
void InitScreenLayout();
void GetImages();    // Draws images and saves them in memory for later use
void DisplayInterface();
void AssignShape(int Shape, int Color); // Gives the shape to the current falling block
int  DetectCollision(int Direction);	// returns 1 when brick collides with something
int  MoveBlock(int Direction);  //Moves the falling block in the direction
void DisplayBlock(int x, int y);
void DisplayNextShape();
void GetNextBlock();
void RotateBlock();
void UpdateScreen();
void CheckForLine();
void RemoveLine(int Number);
int  GetRandomColor();
int  GetRandomShape();
int  IncreaseSpeed();
// Bitmaps
void far *bmpBlueBrick;
void far *bmpRedBrick;
void far *bmpGreenBrick;
void far *bmpYellowBrick;
void far *bmpPurpleBrick;
void far *bmpBlankBrick;
void far *bmpScore;
void far *bmpSpeed;
void far *bmpLevel;
void far *bmpLinesCleared;
void far *bmpScreen;

int BlockMatrix[4][4];      // Stores the shape of the current falling block
int ScreenLayout[COLS][ROWS];	// Will contain the layout with the falling block
int ScreenBackgroundLayout[COLS][ROWS]; //will contain the layout without the falling block
int PreviousScreenLayout[COLS][ROWS];	// Will contain the layout of the previous screen
int LinesCleared=0;
int Level=1;
int LineScore=100;
int Speed = 95;
int CurrentShape;
int NextShape;
int NextColor;
int BlockX = 7;
int BlockY = 0;
int Quit=0;
int GameOver=0;
int SoundOn=1;
char lpszScore[40];
char lpszSpeed[40];
char lpszLevel[40];
char lpszLinesCleared[40];
unsigned long Score=0;

//Shapes of the blocks
int ShapeI[4][4] =
{
    0,1,0,0,
    0,1,0,0,
    0,1,0,0,
    0,1,0,0
};
int ShapeT[4][4] =
{
    0,1,0,0,
    0,1,1,0,
    0,1,0,0,
    0,0,0,0
};
int ShapeL[4][4] =
{
    0,0,1,0,
    1,1,1,0,
    0,0,0,0,
    0,0,0,0
};
int ShapeL2[4][4] =
{
    1,0,0,0,
    1,1,1,0,
    0,0,0,0,
    0,0,0,0
};
int ShapeS[4][4] =
{
    0,1,1,0,
    1,1,0,0,
    0,0,0,0,
    0,0,0,0
};
int ShapeS2[4][4] =
{
    1,1,0,0,
    0,1,1,0,
    0,0,0,0,
    0,0,0,0
};
int ShapeO[4][4] =
{
    1,1,0,0,
    1,1,0,0,
    0,0,0,0,
    0,0,0,0
};


int c_bk=WHITE,c_text=BLACK,c_selectat=LIGHTBLUE,c_text_aux=GREEN;
bool wrap_wrap=false;
string text,text_binar,text_aux;
bool wrap_mode=false;
bool fereastra_deschisa=false;
vector < pair < int, int >> pozitii;


vector<int> y_max_coloana;

string cautatt;
bool text_selectat=false;
int mainWindowHandle=0;
time_t now = time(0);

bool text_cautat=false;

bool inchidere_fereastra = false;
int dif_x=0,dif_y=0;

int x_caret_i=0,y_caret_i=0,pozitie_i=0, x_caret = 0, y_caret = 65,pozitie = 0;

int x1=0,x2=0,y1=0,y2=0;

int active_page=0;

char c, caractere[] = "`~!@#$%^:&*()-_+={}[\\]|?/>.<,'\"''țșăîâ";

int x = 0, y = 65, cnt=0;

int lungime_scroll_vert,pozitie_scroll_vert;
int lungime_scroll_oriz,pozitie_scroll_oriz;
bool mouse_click_vert=false,mouse_click_oriz=false;
int fereastra_fisier,fereastra_editati,fereastra_tema,fereastra_culoare,fereastra_dimensiune,fereastra_wrap;
bool ctrlPressed = false;
bool func_caut=false;
bool hex_view=false;
int dim_x=0,dim_y=0,dim_max_x=0,dim_max_y=65,poz_min_x=0,poz_min_y=65,poz_max_x,poz_max_y;
char aux[3];

void drawToolbar();
void sepLine();
void contor_linie_coloana();

void binar()
{

    vector<int> character; // converting each character to its ascii value

    stringstream ss;

    const std::string s = ss.str();
    for(int i = 0; i < text.size(); i++)
    {
        character.push_back(int(text[i]));
        ss  << hex << character.at(i)<<' ';
        // bytes+=char(hex(character.at(i)));

    }
    text_binar=ss.str();


}
vector <int> aparitii;

void number(string &v,int x)
{

    string v1;
    if(x==0)
    {
        v.push_back(48);
    }
    else
    {

        while(x)
        {
            v1.push_back(x%10+48);
            x/=10;
        }
        for(int i=v1.size()-1; i>=0; i--)
            v.push_back(v1[i]);
    }

}


void contor_linie_coloana()
{
    setcolor(c_bk);
    outtextxy(30+textwidth("Line: "),getmaxy()-30,"100000000");
    outtextxy(getmaxx()/3+30+textwidth("Column: "),getmaxy()-30,"100000000");
    outtextxy(getmaxx()/3*2+30+textwidth("Position: "),getmaxy()-30,"100000000");
    setcolor(MAGENTA);
    int tmp=0;
    setcolor(5);
    setbkcolor(c_bk);
    char *nr;
    string numar;
    if(pozitii.empty())
    {


        tmp=1;
        pozitii.push_back({0,65});
    }

    number(numar,(pozitii[max(0,pozitie-1)].second-65)/21+1);
    nr=&numar[0];

    outtextxy(30+textwidth("Line: "),getmaxy()-30,nr);
    numar.erase(numar.begin(),numar.end());


    number(numar,(pozitii[max(0,pozitie-1)].first)/12+1);
    nr=&numar[0];
    outtextxy(getmaxx()/3+30+textwidth("Column: "),getmaxy()-30,nr);
    numar.erase(numar.begin(),numar.end());


    number(numar,pozitie+1);
    nr=&numar[0];
    outtextxy(getmaxx()/3*2+30+textwidth("Position: "),getmaxy()-30,nr);
}

void replaceAll(std::string& source, const std::string& from, const std::string& to)
{
    std::string newString;
    newString.reserve(source.length());  // avoids a few memory allocations

    std::string::size_type lastPos = 0;
    std::string::size_type findPos;

    while(std::string::npos != (findPos = source.find(from, lastPos)))
    {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    newString += source.substr(lastPos);

    source.swap(newString);
}


void scroll_oriz();

void scroll_vert();

void drawToolbar()///Aceasta functie deseneaza meniul din partea de sus si cel din partea de jos
{
    setbkcolor(c_bk);
    setfillstyle(SOLID_FILL,c_bk);

    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setcolor(LIGHTGRAY);
    bar(0, 0, getmaxx(), getmaxy());

    setcolor(5);

    line(0, getmaxy()-35, getmaxx(), getmaxy()-35);
    line(getmaxx()/3, getmaxy()-35, getmaxx()/3, getmaxy());
    line(getmaxx()/3*2, getmaxy()-35, getmaxx()/3*2, getmaxy());

    rectangle(10, 10, 110, 30);
    setbkcolor(c_bk);

    outtextxy(30, getmaxy()-30, "Line: ");
    outtextxy(getmaxx()/3+30, getmaxy()-30, "Column: ");
    outtextxy(getmaxx()/3*2+30, getmaxy()-30, "Position: ");

    outtextxy(38, 12, "File");

    rectangle(120, 10, 230, 30);
    setcolor(5);
    setbkcolor(c_bk);
    outtextxy(151, 12, "Edit");

    rectangle(240, 10, 350, 30);
    setcolor(5);
    setbkcolor(c_bk);
    outtextxy(265, 12, "Theme");

    rectangle(360, 10, 470, 30);
    setcolor(5);
    setbkcolor(c_bk);
    outtextxy(385, 12, "Color");

    rectangle(480, 10, 590, 30);
    setcolor(5);
    setbkcolor(c_bk);
    outtextxy(499, 12, "Window");

    rectangle(600, 10, 710, 30);
    setcolor(5);
    setbkcolor(c_bk);
    outtextxy(631, 12, "Wrap");
}

void sepLine()///linia de separare intre Toolbar si zona de executie a programului
{
    setcolor(5);
    line(0, 40, getmaxx(), 40);
    if(wrap_mode==true)
    {
        outtextxy((getmaxx()-20)/36*36-18+5,40+5,"Wrap");
        outtextxy((getmaxx()-20)/36*36-18+4,40+5+21,"On");
        y=66+21;
        while(y<getmaxy()-40)
        {
            outtextxy((getmaxx()-20)/36*36-18+4+6,y,"^");
            y+=21;
        }
        line((getmaxx()-20)/36*36-18,40,(getmaxx()-20)/36*36-18,getmaxy()-40);
    }
}

void displayTemaMenu()///meniul pentru optiunea TEMA
{
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);

    setfillstyle(SOLID_FILL, 7);
    setbkcolor(7);
    setcolor(5);
    bar(240, 30, 350, 120);
    //line(240,49, 350, 49);
    rectangle(240, 30, 350, 120);
    outtextxy(250, 50, "Dark");
    //line(240, 69, 350, 69);
    outtextxy(250, 70, "Light");

    outtextxy(250,90,"Gray");


    setfillstyle(SOLID_FILL, c_bk);

    setbkcolor(c_bk);
}

void displayCuloareMenu()///meniul pentru optiunea CULOARE
{
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL, 7);
    setbkcolor(7);
    setcolor(5);
    bar(360, 30, 470, 120);
    rectangle(360, 30, 470, 120);
    outtextxy(370, 50, "Red");
    outtextxy(370, 70, "Cyan");
    outtextxy(370, 90, "Brown");
    setfillstyle(SOLID_FILL, c_bk);

    setbkcolor(c_bk);
}

void displayWrapMenu()///Meniul pentru optiunea WRAP
{

    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL, 7);
    setbkcolor(7);
    setcolor(5);
    bar(600, 30, 710, 100);
    rectangle(600, 30, 710, 100);
    outtextxy(610, 50, "On");
    outtextxy(610, 70, "Off");

    setfillstyle(SOLID_FILL, c_bk);

    setbkcolor(c_bk);
}

void displayDimensiuneMenu()///Meniul pentru optiunea DIMENSIUNE
{
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setfillstyle(SOLID_FILL, 7);
    setbkcolor(7);
    setcolor(5);
    bar(480, 30, 590, 120);
    rectangle(480, 30, 590, 120);
    outtextxy(490, 50, "Maximum");
    outtextxy(490, 70, "Middle");
    outtextxy(490, 90, "Minimum");
    setfillstyle(SOLID_FILL, c_bk);

    setbkcolor(c_bk);
}

void displayFileMenu()///Meniul pentru optiunea FILE
{
    // Display a simple File menu
    //setcolor(LIGHTGRAY);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);

    setfillstyle(SOLID_FILL, 7);
    setbkcolor(7);
    setcolor(5);

    bar(10, 30, 110, 140);
    rectangle(10, 30, 110, 140);

    outtextxy(20, 50, "New");

    outtextxy(20, 70, "Open");
    outtextxy(20, 90, "Save");
    outtextxy(20, 110, "Exit");
    setfillstyle(SOLID_FILL, c_bk);

    setbkcolor(c_bk);
}

void displayEditatiMenu()///Meniul pentru optiunea EDITATI
{
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);

    setfillstyle(SOLID_FILL, 7);
    setbkcolor(7);
    setcolor(5);
    bar(120, 30, 230, 260);

    rectangle(120, 30, 230, 260);
    outtextxy(130, 50, "Undo");
    outtextxy(130, 70, "Redo");
    outtextxy(130, 90, "Copy");
    outtextxy(130, 110, "Paste");
    outtextxy(130, 130, "Cut");
    outtextxy(130, 150, "Replace");
    outtextxy(130, 170, "Find");
    outtextxy(130, 190, "Select");
    outtextxy(130, 210, "Hex view");
    outtextxy(130, 230, "Normal");

    setfillstyle(SOLID_FILL, c_bk);

    setbkcolor(c_bk);

}

struct nod
{
    string text;
    vector<pair<int,int>>pozitii;
    int x_caret=0,y_caret=0,x_caret_i=0,y_caret_i=0,pozitie=0,pozitie_i=0;
    nod *urm,*ant;
}*undo=NULL,*redo=NULL,*undo1=NULL;

struct nod1
{
    string text;
} control_c,control_x;


void initializare_fereastra(int dim_xx,int dim_yy)///afisarea ferestrei principale de executie
{
    ///dim_xx, dim_yy vor fi folosite pentru dimensiunea ferestrei(mic, mediu, maxim)

    mainWindowHandle=initwindow(dim_xx, dim_yy, "Notepad",(getmaxwidth()-dim_xx)/2,(getmaxheight()-dim_yy)/2,false);
    // floodfill(0, 0, c_bk);
    setfillstyle(SOLID_FILL, c_bk);
    bar(0,0,getmaxx(),getmaxy());
    setbkcolor(c_bk);
    cleardevice();
    setactivepage(0);
    cleardevice();
    setactivepage(1);
    cleardevice();
    setvisualpage(1);
    setbkcolor(c_bk);
    setcolor(c_text);

    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    drawToolbar();
    sepLine();
    //lungime_scroll_vert=(getmaxy()-152)/2,pozitie_scroll_vert=76;
    //lungime_scroll_oriz=(getmaxx()-52)/2,pozitie_scroll_oriz=26;
    dim_x=(dim_xx-20)/12*12-24;
    dim_y=(dim_yy-55-65)/21*21+65-21;

    lungime_scroll_vert=(getmaxy()-152)-(max(0,dim_max_y-dim_y))/21;
    lungime_scroll_oriz=(getmaxx()-52)-(max(0,dim_max_x-dim_x))/12;
    pozitie_scroll_vert=76-(poz_min_y-65)/21;
    pozitie_scroll_oriz=26-(poz_min_x)/12;

    poz_min_x=0;
    poz_min_y=65;
    poz_max_x=dim_x;
    poz_max_y=dim_y;

    //lungime_scroll_vert=30/2,pozitie_scroll_vert=76;
    //lungime_scroll_oriz=30/2,pozitie_scroll_oriz=26;

    scroll_oriz();
    scroll_vert();

    contor_linie_coloana();
}

void ctrl_v(nod1 z,int &poz,int &b)
{
    if(!z.text.empty())
    {

        for(int i=0; i<z.text.size(); i++)
        {
            text.insert(text.begin()+b,z.text[i]);
            b++;
        }
        poz+=z.text.size();
    }
}

void delete_selectat(int &e,int&f)
{


    if(e<f)
    {

        if(f==text.size())
            text.erase(text.begin()+e,text.end()),f=e;
        else
            text.erase(text.begin()+e,text.begin()+f), f=e;

    }
    else if(e==text.size())
        text.erase(text.begin()+f,text.end()),e=f;
    else
        text.erase(text.begin()+f,text.begin()+e),e=f;

}


void ctrl_c_x(char c,nod1 &z,int &e,int &f)
{


    z.text.erase(z.text.begin(),z.text.end());

    if(e<f)
        for(int i=e; i<f; i++)
        {
            z.text.push_back(text[i]);

        }
    else
        for(int i=f; i<e; i++)
        {
            z.text.push_back(text[i]);

        }

    if(c=='X')
    {
        if(e<f)
        {

            if(f==text.size())
                text.erase(text.begin()+e,text.end()),f=e;
            else
                text.erase(text.begin()+e,text.begin()+f), f=e;

        }
        else if(e==text.size())
            text.erase(text.begin()+f,text.end()),e=f;
        else
            text.erase(text.begin()+f,text.begin()+e),e=f;





    }
}


void push_stiva(nod *&m,int a,int b,int c,int d,int e,int f,string t, vector<pair<int,int>>p)
{
    nod *z=new nod;
    z->urm=NULL;
    z->ant=NULL;

    z->x_caret=a;
    z->y_caret=b;
    z->x_caret_i=c;
    z->y_caret_i=d;
    z->pozitie=e;
    z->pozitie_i=f;

    for(int i=0; i<t.size(); i++)
        z->text.push_back(t[i]);
    for(int i=0; i<p.size(); i++)
        z->pozitii.push_back({p[i].first,p[i].second});

    if(m==NULL)
        m=z;
    else
    {

        m->urm=z;
        z->ant=m;
        m=m->urm;
    }

}


void utilizare_undo_redo(nod *&a1,nod *& a2,int &a,int &b,int &c,int &d,int &e,int &f,int operatie)
{
    if(a1!=NULL)
    {

        if(operatie==1) push_stiva(a2,a1->x_caret,a1->y_caret,a1->x_caret_i,a1->y_caret_i,a1->pozitie,a1->pozitie_i,a1->text,a1->pozitii);
        text.erase(text.begin(),text.end());
        pozitii.erase(pozitii.begin(),pozitii.end());
        a=a1->x_caret;
        b=a1->y_caret;
        c=a1->x_caret_i;
        d=a1->y_caret_i;
        e=a1->pozitie;
        f=a1->pozitie_i;

        for(int i=0; i<a1->text.size(); i++)
            text.push_back(a1->text[i]);

        for(int i=0; i<a1->pozitii.size(); i++)
            pozitii.push_back({a1->pozitii[i].first,a1->pozitii[i].second});

        if(a1->ant==NULL)
        {
            delete(a1);
            a1=NULL;
        }

        else
        {
            nod *q=new nod;
            q=a1;
            a1=a1->ant;
            a1->urm=NULL;
            delete(q);

        }

    }

}


void inchide_grafica()
{
    closegraph();
}

void echilibrare_pozitii()
{
    if(pozitie!=0)
    {

        if(pozitii[pozitie-1].first>poz_max_x+12)
            while(pozitii[pozitie-1].first>poz_max_x+12)
            {
                poz_min_x+=12;
                poz_max_x+=12;

            }
        else if(pozitii[pozitie-1].first<poz_min_x)
            while(pozitii[pozitie-1].first<poz_min_x)
            {
                poz_min_x-=12;
                poz_max_x-=12;
            }


        if(pozitii[pozitie-1].second>poz_max_y)
            while(pozitii[pozitie-1].second>poz_max_y)
            {
                poz_min_y+=21;
                poz_max_y+=21;

            }
        else if(pozitii[pozitie-1].second<poz_min_y)
            while(pozitii[pozitie-1].second<poz_min_y)
            {
                poz_min_y-=21;
                poz_max_y-=21;
            }
    }
    else
    {
        poz_min_x=0;
        poz_max_x=dim_x;
        poz_min_y=65;
        poz_max_y=dim_y;
    }
}

void echilibrare_caret()
{
    if (pozitie != 0)
    {

        x_caret = pozitii[pozitie-1].first-poz_min_x;
        y_caret=pozitii[pozitie-1].second-poz_min_y+65;


    }
    else
    {
        x_caret = 0;
        y_caret = 65;
    }
}

void doar_text()
{
    setbkcolor(c_bk);
    cleardevice();

    x = 0;
    y = 65;
    pozitii.erase(pozitii.begin(), pozitii.end());

    for (int i = 0; i < text.size(); i++)
    {
        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
        {
            x=0;
            y+=21;
        }
        pozitii.push_back({x,y});
        dim_max_x=max(dim_max_x,x);
        dim_max_y=max(dim_max_y,y);

        if (text[i] == 10||text[i]=='$')
        {
            y = y + 21;
            x = 0;
        }
        else
        {
            pozitii[i].first = x;
            pozitii[i].second = y;
            //aux[0] = text[i];
            x = x + 12;
            //outtextxy(x, y, aux);
        }

        pozitii[i].first = x;
        pozitii[i].second = y;
        dim_max_x=max(dim_max_x,x);
        dim_max_y=max(dim_max_y,y);
    }
    echilibrare_pozitii();
    if(text_selectat==false)
    {

        if(active_page==0)
            active_page=1;
        else
            active_page=0;
        setactivepage(active_page);
        setbkcolor(c_bk);
        cleardevice();
        drawToolbar();

        sepLine();
        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        setbkcolor(c_bk);
        setcolor(c_text);
        text_selectat=false;
        setbkcolor(c_bk);


        x = 0;
        y = 65;

        echilibrare_pozitii();

        for (int i = 0; i < text.size(); i++)
        {
            if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
            {
                x=0;
                y+=21;
            }

            if (text[i] == 10)
            {
                y = y + textheight(aux);

                x = -12;
            }

            if(text[i]=='\n')
                aux[0]=' ';
            else
                aux[0] = text[i];



            if(aux[0]!='\n')
                if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                    outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
            x = x + 12;


        }



        if(mouse_click_oriz==false&&mouse_click_vert==false)
        {
            scroll_oriz();
            scroll_vert();
        }

        setvisualpage(active_page);
        contor_linie_coloana();

    }
    else
    {

        if (pozitie_i != 0)
        {

            x_caret_i = pozitii[pozitie_i-1].first-poz_min_x;
            y_caret_i=pozitii[pozitie_i-1].second-poz_min_y+65;


        }
        else
        {
            x_caret_i = 0;
            y_caret_i = 65;
        }

        echilibrare_pozitii();
        echilibrare_caret();


        if(active_page==0)
            active_page=1;
        else
            active_page=0;
        setactivepage(active_page);
        cleardevice();
        drawToolbar();

        sepLine();
        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        setbkcolor(c_bk);
        setcolor(c_text);
        scroll_oriz();
        scroll_vert();
        text_selectat=true;

        if(pozitie_i<pozitie)
        {
            aux[1] = 0;
            x = 0;
            y = 65;

            for (int i = 0; i < text.size(); i++)
            {
                if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                {
                    x=0;
                    y+=21;
                }
                if(i==0&&x_caret_i==0&&pozitie_i==1)
                    setbkcolor(c_selectat);
                else if(i>=pozitie_i&&i<pozitie)
                    setbkcolor(c_selectat);
                else
                    setbkcolor(c_bk);

                if (text[i] == 10)
                {
                    y = y + textheight(aux);
                    x = -12;
                }

                if(text[i]=='\n')
                    aux[0]=' ';
                else
                    aux[0] = text[i];



                if(aux[0]!='\n')
                    if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                        outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                x = x + 12;
            }
        }
        else
        {


            aux[1] = 0;
            x = 0;
            y = 65;

            for (int i = 0; i < text.size(); i++)
            {
                if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                {
                    x=0;
                    y+=21;
                }
                if(i==0&&x_caret==0&&pozitie==1)
                    setbkcolor(c_selectat);
                else if(i<pozitie_i&&i>=pozitie)
                    setbkcolor(c_selectat);
                else
                    setbkcolor(c_bk);

                if (text[i] == 10)
                {
                    y = y + textheight(aux);
                    x = -12;
                }

                if(text[i]=='\n')
                    aux[0]=' ';
                else
                    aux[0] = text[i];



                if(aux[0]!='\n')
                    if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                        outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);

                x = x + 12;

            }
        }
        setbkcolor(c_bk);
        if(mouse_click_oriz==false&&mouse_click_vert==false)
        {
            scroll_oriz();
            scroll_vert();
        }
        contor_linie_coloana();

        setvisualpage(active_page);
    }
    echilibrare_caret();
}

void scroll_vert() ///functia care afiseaza scrollbar-ul vertical
{
    lungime_scroll_vert=(getmaxy()-152)-(max(0,dim_max_y-dim_y))/21+1;
    //lungime_scroll_oriz=(getmaxx()-52)-(max(0,dim_max_x-dim_x))/12;
    pozitie_scroll_vert=76+(poz_min_y-65)/21;
    //pozitie_scroll_oriz=26;
    lungime_scroll_vert=max(5,lungime_scroll_vert);
    pozitie_scroll_vert=min(getmaxy()-81,pozitie_scroll_vert);
    if(mouse_click_vert==false)
    {
        setcolor(MAGENTA);
        setfillstyle(SOLID_FILL,DARKGRAY);
        bar(getmaxx()-20,70,getmaxx()-5,getmaxy()-70);
        rectangle(getmaxx()-20,70,getmaxx()-5,getmaxy()-70);

        setfillstyle(SOLID_FILL,MAGENTA);
        bar(getmaxx()-20,70,getmaxx()-5,76);
        rectangle(getmaxx()-20,70,getmaxx()-5,76);

        bar(getmaxx()-20,getmaxy()-76,getmaxx()-5,getmaxy()-70);
        rectangle(getmaxx()-20,getmaxy()-76,getmaxx()-5,getmaxy()-70);

        setfillstyle(SOLID_FILL,LIGHTGRAY);
        bar(getmaxx()-19,pozitie_scroll_vert,getmaxx()-6,pozitie_scroll_vert+lungime_scroll_vert);
        rectangle(getmaxx()-19,pozitie_scroll_vert,getmaxx()-6,pozitie_scroll_vert+lungime_scroll_vert);

    }
    int m_poz;
    if(mouse_click_vert==true)
    {
        while(!ismouseclick(WM_LBUTTONUP))
        {
            while(kbhit())
            {
                char temporar;
                temporar=getch();
                if(temporar==0||temporar==224)
                    temporar=getch();
            }

            if((mousey()-(lungime_scroll_vert)/2)<76)
                m_poz=76+(lungime_scroll_vert)/2;
            else if((mousey()+(lungime_scroll_vert)/2)>getmaxy()-76)
                m_poz=getmaxy()-76-(lungime_scroll_vert)/2;
            else
                m_poz=mousey();
            if(active_page==0)
                active_page=1;
            else active_page=0;
            setactivepage(active_page);
            setbkcolor(WHITE);

            poz_min_y=(pozitie_scroll_vert-76)*21+65;
            poz_max_y=poz_min_y+dim_y-65;
            poz_min_x=(pozitie_scroll_oriz-26)*12;
            poz_max_x=poz_min_x+dim_x;
            if(text_selectat==false&&text_cautat==false)
            {

                cleardevice();
                drawToolbar();

                scroll_oriz();

                sepLine();
                settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                setbkcolor(c_bk);
                setcolor(c_text);
                text_selectat=false;
                setbkcolor(c_bk);


                x = 0;
                y = 65;


                for (int i = 0; i < text.size(); i++)
                {
                    if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                    {
                        x=0;
                        y+=21;
                    }
                    if (text[i] == 10)
                    {
                        y = y + textheight(aux);

                        x = -12;
                    }

                    if(text[i]=='\n')
                        aux[0]=' ';
                    else
                        aux[0] = text[i];

                    if(aux[0]!='\n')
                        if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                            outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                    x = x + 12;


                }




                contor_linie_coloana();
            }
            else if(text_cautat==true&&!cautatt.empty())
            {


                string cautare=cautatt;

                cleardevice();
                drawToolbar();

                scroll_oriz();

                sepLine();
                settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                setbkcolor(c_bk);
                setcolor(c_text);
                text_cautat=true;
                setbkcolor(c_bk);

                cnt=0;

                int hau=0;



                cnt=0;
                x = 0;
                y = 65;

                for (int i = 0; i < text.size(); i++)
                {

                    if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                    {
                        x=0;
                        y+=21;
                    }
                    if(cnt<aparitii.size())
                    {
                        if(i>=aparitii[cnt]&&(i<=aparitii[cnt]+cautare.size()-1))

                        {

                            setbkcolor(LIGHTMAGENTA);
                            if(i==aparitii[cnt]+cautare.size()-1)
                            {
                                cnt++;
                            }

                        }
                        else setbkcolor(c_bk);
                    }
                    else setbkcolor(c_bk);
                    if (text[i] == 10)
                    {
                        y = y + textheight(aux);
                        x = -12;
                    }

                    if(text[i]=='\n')
                        aux[0]=' ';
                    else
                        aux[0] = text[i];



                    if(aux[0]!='\n')
                        if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                            outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                    x = x + 12;

                }

                contor_linie_coloana();
            }
            else
            {

                x_caret_i=pozitii[pozitie_i].first;
                y_caret_i=pozitii[pozitie_i].second;


                x_caret=pozitii[pozitie].first;
                y_caret=pozitii[pozitie].second;


                cleardevice();
                drawToolbar();

                sepLine();
                settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                setbkcolor(c_bk);
                setcolor(c_text);
                scroll_oriz();

                text_selectat=true;

                if(pozitie_i<pozitie)
                {
                    aux[1] = 0;
                    x = 0;
                    y = 65;

                    for (int i = 0; i < text.size(); i++)
                    {
                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                        {
                            x=0;
                            y+=21;
                        }
                        if(i==0&&x_caret_i==0&&pozitie_i==1)
                            setbkcolor(c_selectat);
                        else if(i>=pozitie_i&&i<pozitie)
                            setbkcolor(c_selectat);
                        else
                            setbkcolor(c_bk);

                        if (text[i] == 10)
                        {
                            y = y + textheight(aux);
                            x = -12;
                        }

                        if(text[i]=='\n')
                            aux[0]=' ';
                        else
                            aux[0] = text[i];

                        if(aux[0]!='\n')
                            if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                        x = x + 12;
                    }
                }
                else
                {


                    aux[1] = 0;
                    x = 0;
                    y = 65;

                    for (int i = 0; i < text.size(); i++)
                    {
                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                        {
                            x=0;
                            y+=21;
                        }
                        if(i==0&&x_caret==0&&pozitie==1)
                            setbkcolor(c_selectat);
                        else if(i<pozitie_i&&i>=pozitie)
                            setbkcolor(c_selectat);
                        else
                            setbkcolor(c_bk);

                        if (text[i] == 10)
                        {
                            y = y + textheight(aux);
                            x = -12;
                        }

                        if(text[i]=='\n')
                            aux[0]=' ';
                        else
                            aux[0] = text[i];

                        if(aux[0]!='\n')
                            if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                        x = x + 12;
                    }
                }
                setbkcolor(c_bk);
                contor_linie_coloana();

            }






            pozitie_scroll_vert=m_poz-lungime_scroll_vert/2;
            setcolor(MAGENTA);
            setfillstyle(SOLID_FILL,DARKGRAY);
            bar(getmaxx()-20,70,getmaxx()-5,getmaxy()-70);
            rectangle(getmaxx()-20,70,getmaxx()-5,getmaxy()-70);

            setfillstyle(SOLID_FILL,MAGENTA);
            bar(getmaxx()-20,70,getmaxx()-5,76);
            rectangle(getmaxx()-20,70,getmaxx()-5,76);

            bar(getmaxx()-20,getmaxy()-76,getmaxx()-5,getmaxy()-70);
            rectangle(getmaxx()-20,getmaxy()-76,getmaxx()-5,getmaxy()-70);

            setfillstyle(SOLID_FILL,LIGHTRED);
            bar(getmaxx()-19,pozitie_scroll_vert,getmaxx()-6,pozitie_scroll_vert+lungime_scroll_vert);
            rectangle(getmaxx()-19,pozitie_scroll_vert,getmaxx()-6,pozitie_scroll_vert+lungime_scroll_vert);


            scroll_oriz();
            setvisualpage(active_page);
            usleep(10);
        }

        if(ismouseclick(WM_LBUTTONUP))
        {


            clearmouseclick(WM_LBUTTONUP);
            clearmouseclick(WM_LBUTTONDOWN);
        }



    }

    setcolor(MAGENTA);
    setfillstyle(SOLID_FILL,DARKGRAY);
    bar(getmaxx()-20,70,getmaxx()-5,getmaxy()-70);
    rectangle(getmaxx()-20,70,getmaxx()-5,getmaxy()-70);

    setfillstyle(SOLID_FILL,MAGENTA);
    bar(getmaxx()-20,70,getmaxx()-5,76);
    rectangle(getmaxx()-20,70,getmaxx()-5,76);

    bar(getmaxx()-20,getmaxy()-76,getmaxx()-5,getmaxy()-70);
    rectangle(getmaxx()-20,getmaxy()-76,getmaxx()-5,getmaxy()-70);

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(getmaxx()-19,pozitie_scroll_vert,getmaxx()-6,pozitie_scroll_vert+lungime_scroll_vert);
    rectangle(getmaxx()-19,pozitie_scroll_vert,getmaxx()-6,pozitie_scroll_vert+lungime_scroll_vert);


    setcolor(c_text);
    setfillstyle(SOLID_FILL,c_bk);


}

void scroll_oriz()///functia care afiseaza scrollbar-ul orizontal
{
    //lungime_scroll_vert=(getmaxy()-152)-(max(0,dim_max_y-dim_y))/21;
    if(wrap_mode==true)
        lungime_scroll_oriz=(getmaxx()-52);
    else
        lungime_scroll_oriz=(getmaxx()-52)-(max(0,dim_max_x-dim_x))/12+1;
    //pozitie_scroll_vert=76;


    pozitie_scroll_oriz=26+(poz_min_x)/12;
    lungime_scroll_oriz=max(5,lungime_scroll_oriz);
    pozitie_scroll_oriz=min(pozitie_scroll_oriz,getmaxx()-31);

    if(mouse_click_oriz==false)
    {
        setcolor(MAGENTA);
        setfillstyle(SOLID_FILL,DARKGRAY);
        bar(20,getmaxy()-55,getmaxx()-20,getmaxy()-40);
        setfillstyle(SOLID_FILL,DARKGRAY);
        bar(20,getmaxy()-55,getmaxx()-20,getmaxy()-40);
        rectangle(20,getmaxy()-55,getmaxx()-20,getmaxy()-40);

        setfillstyle(SOLID_FILL,MAGENTA);
        bar(20,getmaxy()-55,26,getmaxy()-40);
        rectangle(20,getmaxy()-55,26,getmaxy()-40);

        bar(getmaxx()-26,getmaxy()-55,getmaxx()-20,getmaxy()-40);
        rectangle(getmaxx()-26,getmaxy()-55,getmaxx()-20,getmaxy()-40);

        setfillstyle(SOLID_FILL,LIGHTGRAY);

        bar(pozitie_scroll_oriz,getmaxy()-54,pozitie_scroll_oriz+lungime_scroll_oriz,getmaxy()-41);
        rectangle(pozitie_scroll_oriz,getmaxy()-54,pozitie_scroll_oriz+lungime_scroll_oriz,getmaxy()-41);
    }
    int m_poz;
    if(mouse_click_oriz==true)
    {
        while(!ismouseclick(WM_LBUTTONUP))
        {

            if(kbhit())
            {
                char temporar;
                temporar=getch();
                if(temporar==0||temporar==224)
                    temporar=getch();
            }
            if((mousex()-(lungime_scroll_oriz)/2)<26)
                m_poz=26+(lungime_scroll_oriz)/2;
            else if((mousex()+(lungime_scroll_oriz)/2)>getmaxx()-26)
                m_poz=getmaxx()-26-(lungime_scroll_oriz)/2;
            else
                m_poz=mousex();

            if(active_page==0)
                active_page=1;
            else active_page=0;
            setactivepage(active_page);
            poz_min_y=(pozitie_scroll_vert-76)*21+65;
            poz_max_y=poz_min_y+dim_y-65;
            poz_min_x=(pozitie_scroll_oriz-26)*12;
            poz_max_x=poz_min_x+dim_x;

            if(text_selectat==false&&text_cautat==false)
            {

                cleardevice();
                drawToolbar();

                scroll_vert();

                sepLine();
                settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                setbkcolor(c_bk);
                setcolor(c_text);
                text_selectat=false;
                setbkcolor(c_bk);


                x = 0;
                y = 65;


                for (int i = 0; i < text.size(); i++)
                {
                    if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                    {
                        x=0;
                        y+=21;
                    }
                    if (text[i] == 10)
                    {
                        y = y + textheight(aux);

                        x = -12;
                    }

                    if(text[i]=='\n')
                        aux[0]=' ';
                    else
                        aux[0] = text[i];

                    if(aux[0]!='\n')
                        if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                            outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                    x = x + 12;


                }




                contor_linie_coloana();
            }
            else if(text_cautat==true&&!cautatt.empty())
            {
                cleardevice();
                drawToolbar();

                scroll_vert();

                sepLine();
                settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                setbkcolor(c_bk);
                setcolor(c_text);
                text_selectat=false;
                setbkcolor(c_bk);

                string cautare=cautatt;

                cnt=0;
                int hau=0;

                cnt=0;
                x = 0;
                y = 65;

                for (int i = 0; i < text.size(); i++)
                {

                    if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                    {
                        x=0;
                        y+=21;
                    }
                    if(cnt<aparitii.size())
                    {
                        if(i>=aparitii[cnt]&&(i<=aparitii[cnt]+cautare.size()-1))

                        {

                            setbkcolor(LIGHTMAGENTA);
                            if(i==aparitii[cnt]+cautare.size()-1)
                            {
                                cnt++;
                            }

                        }
                        else setbkcolor(c_bk);
                    }
                    else setbkcolor(c_bk);
                    if (text[i] == 10)
                    {
                        y = y + textheight(aux);
                        x = -12;
                    }

                    if(text[i]=='\n')
                        aux[0]=' ';
                    else
                        aux[0] = text[i];



                    if(aux[0]!='\n')
                        if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                            outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                    x = x + 12;

                }
                contor_linie_coloana();

            }
            else
            {

                x_caret_i=pozitii[pozitie_i].first;
                y_caret_i=pozitii[pozitie_i].second;


                x_caret=pozitii[pozitie].first;
                y_caret=pozitii[pozitie].second;


                cleardevice();
                drawToolbar();

                sepLine();
                settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                setbkcolor(c_bk);
                setcolor(c_text);
                scroll_vert();

                text_selectat=true;

                if(pozitie_i<pozitie)
                {
                    aux[1] = 0;
                    x = 0;
                    y = 65;

                    for (int i = 0; i < text.size(); i++)
                    {
                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                        {
                            x=0;
                            y+=21;
                        }
                        if(i==0&&x_caret_i==0&&pozitie_i==1)
                            setbkcolor(c_selectat);
                        else if(i>=pozitie_i&&i<pozitie)
                            setbkcolor(c_selectat);
                        else
                            setbkcolor(c_bk);

                        if (text[i] == 10)
                        {
                            y = y + textheight(aux);
                            x = -12;
                        }

                        if(text[i]=='\n')
                            aux[0]=' ';
                        else
                            aux[0] = text[i];

                        if(aux[0]!='\n')
                            if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                        x = x + 12;
                    }
                }
                else
                {


                    aux[1] = 0;
                    x = 0;
                    y = 65;

                    for (int i = 0; i < text.size(); i++)
                    {
                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                        {
                            x=0;
                            y+=21;
                        }
                        if(i==0&&x_caret==0&&pozitie==1)
                            setbkcolor(c_selectat);
                        else if(i<pozitie_i&&i>=pozitie)
                            setbkcolor(c_selectat);
                        else
                            setbkcolor(c_bk);

                        if (text[i] == 10)
                        {
                            y = y + textheight(aux);
                            x = -12;
                        }

                        if(text[i]=='\n')
                            aux[0]=' ';
                        else
                            aux[0] = text[i];

                        if(aux[0]!='\n')
                            if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                        x = x + 12;
                    }
                }
                setbkcolor(c_bk);
                contor_linie_coloana();
                contor_linie_coloana();

            }








            pozitie_scroll_oriz=max(26,m_poz-lungime_scroll_oriz/2);
            if(pozitie_scroll_oriz+lungime_scroll_oriz>getmaxx()-26)
                pozitie_scroll_oriz=getmaxx()-26-lungime_scroll_oriz;

            setcolor(MAGENTA);
            setfillstyle(SOLID_FILL,DARKGRAY);
            bar(20,getmaxy()-55,getmaxx()-20,getmaxy()-40);
            setfillstyle(SOLID_FILL,DARKGRAY);
            bar(20,getmaxy()-55,getmaxx()-20,getmaxy()-40);
            rectangle(20,getmaxy()-55,getmaxx()-20,getmaxy()-40);

            setfillstyle(SOLID_FILL,MAGENTA);
            bar(20,getmaxy()-55,26,getmaxy()-40);
            rectangle(20,getmaxy()-55,26,getmaxy()-40);

            bar(getmaxx()-26,getmaxy()-55,getmaxx()-20,getmaxy()-40);
            rectangle(getmaxx()-26,getmaxy()-55,getmaxx()-20,getmaxy()-40);

            setfillstyle(SOLID_FILL,LIGHTRED);

            bar(pozitie_scroll_oriz,getmaxy()-54,pozitie_scroll_oriz+lungime_scroll_oriz,getmaxy()-41);
            rectangle(pozitie_scroll_oriz,getmaxy()-54,pozitie_scroll_oriz+lungime_scroll_oriz,getmaxy()-41);
            scroll_vert();
            contor_linie_coloana();
            setvisualpage(active_page);
            usleep(10);
        }


        mouse_click_oriz==false;
        clearmouseclick(WM_LBUTTONUP);
        clearmouseclick(WM_LBUTTONDOWN);


    }
    setcolor(MAGENTA);
    setfillstyle(SOLID_FILL,DARKGRAY);
    bar(20,getmaxy()-55,getmaxx()-20,getmaxy()-40);
    setfillstyle(SOLID_FILL,DARKGRAY);
    bar(20,getmaxy()-55,getmaxx()-20,getmaxy()-40);
    rectangle(20,getmaxy()-55,getmaxx()-20,getmaxy()-40);

    setfillstyle(SOLID_FILL,MAGENTA);
    bar(20,getmaxy()-55,26,getmaxy()-40);
    rectangle(20,getmaxy()-55,26,getmaxy()-40);

    bar(getmaxx()-26,getmaxy()-55,getmaxx()-20,getmaxy()-40);
    rectangle(getmaxx()-26,getmaxy()-55,getmaxx()-20,getmaxy()-40);

    setfillstyle(SOLID_FILL,LIGHTGRAY);

    bar(pozitie_scroll_oriz,getmaxy()-54,pozitie_scroll_oriz+lungime_scroll_oriz,getmaxy()-41);
    rectangle(pozitie_scroll_oriz,getmaxy()-54,pozitie_scroll_oriz+lungime_scroll_oriz,getmaxy()-41);
    setcolor(c_text);
    setfillstyle(SOLID_FILL,c_bk);
}

void scriere_text()///coloreaza textul in functie de unde este plasat cursorul mouse-ului
{
    aux[1]=0;
    while (inchidere_fereastra == false)
    {
        if(hex_view==false)
        {
            text_aux=text;
            c_text_aux=c_text;
        }
        if(text_selectat==false&&!kbhit()&&text_cautat==false&&pozitii[pozitie-1].first>=poz_min_x&&pozitii[pozitie-1].first<=poz_max_x+12&&pozitii[pozitie-1].second>=poz_min_y&&pozitii[pozitie-1].second<=poz_max_y) ///desenare caret
        {
            using namespace std::chrono;
            uint64_t after=duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

            if(after%100==0&&after%200!=0)
            {
                setcolor(c_bk);
                line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
            }
            else if(after%200==0)
            {
                setcolor(c_text);
                line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
            }


            setcolor(c_text);
        }


        if(!ismouseclick(WM_LBUTTONDOWN))///daca nu fac click, doar trec cu cursorul
        {
            if(mousey()>=10&&mousey()<=30&&mousex()>=10&&mousex()<=710)///culorile pentru Toolbar
            {
                if(mousex()>=10&&mousex()<=110)///FILE

                {
                    setcolor(LIGHTRED);
                    rectangle(10, 10, 110, 30);
                    setcolor(LIGHTRED);
                    outtextxy(38, 12, "File");
                    while(mousey()>=10&&mousey()<=30&&mousex()>=10&&mousex()<=110&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                    {}
                    setcolor(5);
                    rectangle(10, 10, 110, 30);
                    outtextxy(38, 12, "File");

                }

                else if(mousex()>=120&&mousex()<=230)///EDIT
                {
                    setcolor(LIGHTRED);
                    rectangle(120, 10, 230, 30);
                    setcolor(LIGHTRED);
                    outtextxy(151, 12, "Edit");
                    while(mousey()>=10&&mousey()<=30&&mousex()>=120&&mousex()<=230&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                    {}
                    setcolor(5);
                    rectangle(120, 10, 230, 30);
                    outtextxy(151, 12, "Edit");
                }

                else if(mousex()>=240&&mousex()<=350)///THEME
                {
                    setcolor(LIGHTRED);
                    rectangle(240, 10, 350, 30);
                    setcolor(LIGHTRED);
                    outtextxy(265, 12, "Theme");
                    while(mousey()>=10&&mousey()<=30&&mousex()>=240&&mousex()<=350&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                    {}
                    setcolor(5);
                    rectangle(240, 10, 350, 30);
                    outtextxy(265, 12, "Theme");

                }

                else if(mousex()>=360&&mousex()<=470)///COLOR
                {
                    setcolor(LIGHTRED);
                    rectangle(360, 10, 470, 30);
                    setcolor(LIGHTRED);
                    outtextxy(385, 12, "Color");
                    while(mousey()>=10&&mousey()<=30&&mousex()>=360&&mousex()<=470&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                    {}
                    setcolor(5);
                    rectangle(360, 10, 470, 30);
                    outtextxy(385, 12, "Color");
                }

                else if(mousex()>=480&&mousex()<=590)///WINDOW
                {
                    setcolor(LIGHTRED);
                    rectangle(480, 10, 590, 30);
                    setcolor(LIGHTRED);
                    outtextxy(499, 12, "Window");
                    while(mousey()>=10&&mousey()<=30&&mousex()>=480&&mousex()<=590&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                    {}
                    setcolor(5);
                    rectangle(480, 10, 590, 30);
                    outtextxy(499, 12, "Window");

                }

                else if(mousex()>=600&&mousex()<=710)///WRAP
                {
                    setcolor(LIGHTRED);
                    rectangle(600, 10, 710, 30);
                    setcolor(LIGHTRED);
                    outtextxy(631, 12, "Wrap");
                    while(mousey()>=10&&mousey()<=30&&mousex()>=600&&mousex()<=710&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                    {}
                    setcolor(5);
                    rectangle(600, 10, 710, 30);
                    outtextxy(631, 12, "Wrap");

                }



            }


            if(mousey()>=getmaxy()-40)///culorile pentru meniul de jos(linie, coloana, pozitie)
            {

                int tmp=0;
                char *nr;
                string numar;
                if(pozitii.empty())
                {
                    tmp=1;
                    pozitii.push_back({0,65});
                }

                if(mousex()>=0&&mousex()<=getmaxx()/3)///ne aflam in prima treime:LINIE
                {
                    setcolor(CYAN);
                    number(numar,(pozitii[max(0,pozitie-1)].second-65)/21+1);
                    nr=&numar[0];
                    outtextxy(30, getmaxy()-30, "Line: ");
                    outtextxy(30+textwidth("Line: "),getmaxy()-30,nr);
                    rectangle(0,getmaxy()-35,getmaxx()/3,getmaxy());
                    numar.erase(numar.begin(),numar.end());

                    while(mousey()>=getmaxy()-40&&mousex()>=0&&mousex()<=getmaxx()/3&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())usleep(100);
                    setcolor(5);
                    number(numar,(pozitii[max(0,pozitie-1)].second-65)/21+1);
                    nr=&numar[0];
                    outtextxy(30, getmaxy()-30, "Line: ");
                    outtextxy(30+textwidth("Line: "),getmaxy()-30,nr);
                    rectangle(0,getmaxy()-35,getmaxx()/3,getmaxy());
                    numar.erase(numar.begin(),numar.end());
                }

                if(mousex()>=getmaxx()/3&&mousex()<=getmaxx()/3*2)///ne aflam in a doua treime:COLOANA
                {
                    setcolor(CYAN);
                    number(numar,(pozitii[max(0,pozitie-1)].first)/12+1);
                    nr=&numar[0];
                    rectangle(getmaxx()/3,getmaxy()-35,getmaxx()/3*2,getmaxy());
                    outtextxy(getmaxx()/3+30, getmaxy()-30, "Column: ");
                    outtextxy(getmaxx()/3+30+textwidth("Column: "),getmaxy()-30,nr);
                    numar.erase(numar.begin(),numar.end());
                    while(mousey()>=getmaxy()-40&&mousex()>=getmaxx()/3&&mousex()<=getmaxx()/3*2&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())usleep(100);

                    setcolor(5);
                    number(numar,(pozitii[max(0,pozitie-1)].first)/12+1);
                    nr=&numar[0];
                    rectangle(getmaxx()/3,getmaxy()-35,getmaxx()/3*2,getmaxy());

                    outtextxy(getmaxx()/3+30, getmaxy()-30, "Column: ");
                    outtextxy(getmaxx()/3+30+textwidth("Column: "),getmaxy()-30,nr);
                    numar.erase(numar.begin(),numar.end());
                }

                if(mousex()>=getmaxx()/3*2)///ne aflam in a treia treime: POZITIE
                {
                    setcolor(CYAN);
                    number(numar,pozitie+1);
                    nr=&numar[0];
                    outtextxy(getmaxx()/3*2+30, getmaxy()-30, "Position: ");
                    rectangle(getmaxx()/3*2,getmaxy()-35,getmaxx(),getmaxy());

                    outtextxy(getmaxx()/3*2+30+textwidth("Position: "),getmaxy()-30,nr);
                    numar.erase(numar.begin(),numar.end());
                    while(mousey()>=getmaxy()-40&&mousex()>=getmaxx()/3*2&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())usleep(100);
                    setcolor(5);
                    number(numar,pozitie+1);
                    nr=&numar[0];
                    rectangle(getmaxx()/3*2,getmaxy()-35,getmaxx(),getmaxy());

                    outtextxy(getmaxx()/3*2+30, getmaxy()-30, "Position: ");
                    outtextxy(getmaxx()/3*2+30+textwidth("Position: "),getmaxy()-30,nr);
                    numar.erase(numar.begin(),numar.end());
                }

            }


            if(mousey()>=35&&mousey()<=45)///culoare pentru linia de separare dintre Toolbar si zona de executie
            {
                setcolor(CYAN);
                line(0,40,getmaxx(),40);
                while(mousey()>=35&&mousey()<=45&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())usleep(100);
                setcolor(5);
                line(0,40,getmaxx(),40);
            }

            if(mousey()>=76&&mousey()<=getmaxy()-76&&mousex()>=getmaxx()-20&&mousex()<=getmaxx()-5)///culoare scrollbar vertical
            {

                setcolor(5);
                setfillstyle(SOLID_FILL,DARKGRAY);
                bar(getmaxx()-20,70,getmaxx()-5,getmaxy()-70);
                rectangle(getmaxx()-20,70,getmaxx()-5,getmaxy()-70);

                setfillstyle(SOLID_FILL,5);
                bar(getmaxx()-20,70,getmaxx()-5,76);
                rectangle(getmaxx()-20,70,getmaxx()-5,76);

                bar(getmaxx()-20,getmaxy()-76,getmaxx()-5,getmaxy()-70);
                rectangle(getmaxx()-20,getmaxy()-76,getmaxx()-5,getmaxy()-70);

                setfillstyle(SOLID_FILL,LIGHTRED);
                bar(getmaxx()-19,pozitie_scroll_vert,getmaxx()-6,pozitie_scroll_vert+lungime_scroll_vert);
                rectangle(getmaxx()-19,pozitie_scroll_vert,getmaxx()-6,pozitie_scroll_vert+lungime_scroll_vert);


                while(mousey()>=76&&mousey()<=getmaxy()-76&&mousex()>=getmaxx()-20&&mousex()<=getmaxx()-5&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                    usleep(100);

                setcolor(MAGENTA);
                setfillstyle(SOLID_FILL,DARKGRAY);
                bar(getmaxx()-20,70,getmaxx()-5,getmaxy()-70);
                rectangle(getmaxx()-20,70,getmaxx()-5,getmaxy()-70);

                setfillstyle(SOLID_FILL,MAGENTA);
                bar(getmaxx()-20,70,getmaxx()-5,76);
                rectangle(getmaxx()-20,70,getmaxx()-5,76);

                bar(getmaxx()-20,getmaxy()-76,getmaxx()-5,getmaxy()-70);
                rectangle(getmaxx()-20,getmaxy()-76,getmaxx()-5,getmaxy()-70);

                setfillstyle(SOLID_FILL,LIGHTGRAY);
                bar(getmaxx()-19,pozitie_scroll_vert,getmaxx()-6,pozitie_scroll_vert+lungime_scroll_vert);
                rectangle(getmaxx()-19,pozitie_scroll_vert,getmaxx()-6,pozitie_scroll_vert+lungime_scroll_vert);



            }

            if(mousey()>=getmaxy()-55&&mousey()<=getmaxy()-40&&mousex()>=26&&mousex()<=getmaxx()-26)///culoare scrollbar orizontal
            {

                setcolor(MAGENTA);
                setfillstyle(SOLID_FILL,DARKGRAY);
                bar(20,getmaxy()-55,getmaxx()-20,getmaxy()-40);
                setfillstyle(SOLID_FILL,DARKGRAY);
                bar(20,getmaxy()-55,getmaxx()-20,getmaxy()-40);
                rectangle(20,getmaxy()-55,getmaxx()-20,getmaxy()-40);

                setfillstyle(SOLID_FILL,MAGENTA);
                bar(20,getmaxy()-55,26,getmaxy()-40);
                rectangle(20,getmaxy()-55,26,getmaxy()-40);

                bar(getmaxx()-26,getmaxy()-55,getmaxx()-20,getmaxy()-40);
                rectangle(getmaxx()-26,getmaxy()-55,getmaxx()-20,getmaxy()-40);

                setfillstyle(SOLID_FILL,LIGHTRED);

                bar(pozitie_scroll_oriz,getmaxy()-54,pozitie_scroll_oriz+lungime_scroll_oriz,getmaxy()-41);
                rectangle(pozitie_scroll_oriz,getmaxy()-54,pozitie_scroll_oriz+lungime_scroll_oriz,getmaxy()-41);


                while(mousey()>=getmaxy()-55&&mousey()<=getmaxy()-40&&mousex()>=26&&mousex()<=getmaxx()-26&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())usleep(100);


                setcolor(MAGENTA);
                setfillstyle(SOLID_FILL,DARKGRAY);
                bar(20,getmaxy()-55,getmaxx()-20,getmaxy()-40);
                setfillstyle(SOLID_FILL,DARKGRAY);
                bar(20,getmaxy()-55,getmaxx()-20,getmaxy()-40);
                rectangle(20,getmaxy()-55,getmaxx()-20,getmaxy()-40);

                setfillstyle(SOLID_FILL,MAGENTA);
                bar(20,getmaxy()-55,26,getmaxy()-40);
                rectangle(20,getmaxy()-55,26,getmaxy()-40);

                bar(getmaxx()-26,getmaxy()-55,getmaxx()-20,getmaxy()-40);
                rectangle(getmaxx()-26,getmaxy()-55,getmaxx()-20,getmaxy()-40);

                setfillstyle(SOLID_FILL,LIGHTGRAY);

                bar(pozitie_scroll_oriz,getmaxy()-54,pozitie_scroll_oriz+lungime_scroll_oriz,getmaxy()-41);
                rectangle(pozitie_scroll_oriz,getmaxy()-54,pozitie_scroll_oriz+lungime_scroll_oriz,getmaxy()-41);


            }

            setfillstyle(SOLID_FILL,c_bk);
        }///sfarsit daca nu fac click, doar trec cu cursorul


        if(ismouseclick(WM_LBUTTONDBLCLK))///la dublu click
        {
            clearmouseclick(WM_LBUTTONDOWN);
            while(!ismouseclick(WM_LBUTTONUP));
            clearmouseclick(WM_LBUTTONUP);
            clearmouseclick(WM_LBUTTONDBLCLK);

        }

        if(ismouseclick(WM_LBUTTONDOWN))///click stanga
        {
            mouse_click_vert=false;
            mouse_click_oriz=false;
            if(kbhit())
            {
                char temporar;
                temporar=getch();
                if(temporar==0||temporar==224)
                    temporar=getch();
            }

            if(mousey()>=76&&mousey()<=getmaxy()-76&&mousex()>=getmaxx()-20&&mousex()<=getmaxx()-5)///scroll vertical
            {
                mouse_click_vert=true;
                scroll_vert();
                mouse_click_vert=false;
            }
            else if(mousey()>=getmaxy()-55&&mousey()<=getmaxy()-40&&mousex()>=26&&mousex()<=getmaxx()-26)///scroll orizontal
            {
                mouse_click_oriz=true;
                scroll_oriz();
                mouse_click_oriz=false;
            }

            else if(mousey()>=10&&mousey()<=30)
            {
                if(text_cautat==true)
                {
                    text_cautat=false;
                    doar_text();
                }

                x=mousex();
                y=mousey();
                fereastra_deschisa=true;
                if(ismouseclick(WM_LBUTTONDBLCLK))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    while(!ismouseclick(WM_LBUTTONUP));
                    clearmouseclick(WM_LBUTTONUP);

                    clearmouseclick(WM_LBUTTONDBLCLK);

                }
                else
                {

                    clearmouseclick(WM_LBUTTONDOWN);
                    while(!ismouseclick(WM_LBUTTONUP));
                    clearmouseclick(WM_LBUTTONUP);
                }

                return;
            }
            else
            {
                if(text_cautat==true)
                {
                    text_cautat=false;
                    doar_text();

                }

                setcolor(c_bk);
                line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
                setcolor(c_text);

                x=mousex();
                y=mousey();

                int a = -1, b = -1, max_x = 0, cnt = 0;
///de aici



                x=max(x-12,0);

                if(x<((x/12+1)*12-6))
                    x=x/12*12;
                else
                    x=(x/12+1)*12;

                if(poz_max_x>dim_x)
                    dif_x=poz_max_x-dim_x;
                else
                    dif_x=0;

                if(poz_max_y>dim_y)
                    dif_y=poz_max_y-dim_y;
                else
                    dif_y=0;

                if(!text.empty())
                {

                    if(y+21>65&&y<=max(65+21,pozitii[text.size()-1].second-dif_y))
                    {

                        setcolor(c_bk);//?
                        // line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
                        setcolor(c_text);
                        x_caret = x;
                        y_caret = 65+(y-66) / 21 * 21;

                        if(x==0)
                        {
                            cnt=-1;
                            max_x=0;
                            for (int i = 0; i < text.size(); i++)
                                if(text[i]=='\n')
                                {
                                    if(pozitii[i].second-dif_y==y_caret)
                                    {
                                        pozitie=i+1,cnt=1;
                                        i=text.size();
                                    }
                                }
                                else if(x_caret+12==pozitii[i].first-dif_x&&y_caret==pozitii[i].second-dif_y)
                                {

                                    pozitie=i;
                                    cnt=1;

                                    i=text.size();
                                }
                                else if(y_caret==pozitii[i].second-dif_y)
                                {
                                    a=i;
                                    max_x=pozitii[i].first-dif_x;
                                }

                            if(cnt==-1)
                            {
                                pozitie=a+1;
                                x_caret=max_x;
                            }
                            //contor_linie_coloana();
                        }
                        else
                        {
                            cnt=-1;
                            for (int i = 0; i < text.size(); i++)
                                if (pozitii[i].first-dif_x  == x_caret && pozitii[i].second-dif_y == y_caret)
                                {
                                    pozitie = i + 1;
                                    cnt = 1;
                                    i=text.size();
                                }
                                else if(y_caret==pozitii[i].second-dif_y)
                                {
                                    a=i;
                                    max_x=pozitii[i].first-dif_x;
                                }

                            if(cnt==-1)
                            {
                                pozitie=a+1;
                                x_caret=min(x_caret,max_x);
                            }
                            contor_linie_coloana();
                        }
                    }
                    else if(y+21>=pozitii[text.size()-1].second-dif_y)
                    {
                        y_caret = pozitii[text.size()-1].second-dif_y;
                        if(x<=pozitii[text.size()-1].first-dif_x)
                            for(int i=0; i<text.size(); i++)
                            {
                                if(pozitii[i].second-dif_y==y_caret&&pozitii[i].first-dif_x==x)
                                {
                                    pozitie=i+1;
                                    x_caret=x;
                                    i=text.size();
                                }
                            }
                        else
                        {
                            x_caret=min(x,pozitii[text.size()-1].first-dif_x);
                            pozitie=text.size();
                        }
                        //contor_linie_coloana();
                    }
                }
                else
                {

                    x_caret=0;
                    y_caret=65;
                    pozitie=0;
                    contor_linie_coloana();

                }
                x_caret_i=x_caret,y_caret_i=y_caret;
                pozitie_i=pozitie;


                while(!ismouseclick(WM_LBUTTONUP))
                {



                    usleep(100);







                    contor_linie_coloana();

                    if(mousey()>=46&&mousey()<getmaxy()-55&&mousex()>=12&&mousex()<getmaxx()-20)
                    {
                        a = -1, b = -1, max_x = 0, cnt = 0;


                        x=mousex(),y=mousey();


                        x=max(x-12,0);
                        if(x<((x/12+1)*12-6))
                            x=x/12*12;
                        else
                            x=(x/12+1)*12;


                        if(x<=0)
                        {
                            if(pozitie>=0)
                            {

                                poz_min_x=max(0,poz_min_x-12);
                                poz_max_x=max(dim_x,poz_max_x-12);



                            }
                        }
                        else if(x+12>=(getmaxx()-20)/12*12)
                        {
                            if(pozitie<text.size()&&pozitii[pozitie].second==pozitii[pozitie-1].second)
                            {
                                poz_min_x=poz_min_x+12;
                                poz_max_x=poz_max_x+12;

                            }
                        }


                        if(y<=65)
                        {
                            if(poz_min_y-21>=65)
                            {
                                poz_min_y=max(0,poz_min_y-21);
                                poz_max_y=max(dim_y,poz_max_y-21);
                            }


                        }
                        else if(y>=(getmaxy()-55)/21*21)
                        {

                            if(pozitie<text.size()&&poz_max_y+21<=dim_max_y)
                            {
                                poz_min_y=poz_min_y+21;
                                poz_max_y=poz_max_y+21;

                            }
                        }

                        if(poz_max_x>dim_x)
                            dif_x=poz_max_x-dim_x;
                        else
                            dif_x=0;

                        if(poz_max_y>dim_y)
                            dif_y=poz_max_y-dim_y;
                        else
                            dif_y=0;


                        if(!text.empty())
                        {

                            if(y+21>65&&y<=max(65+21,pozitii[text.size()-1].second-dif_y))
                            {

                                setcolor(c_bk);//?
                                // line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
                                setcolor(c_text);
                                x_caret = x;
                                y_caret = 65+(y-66) / 21 * 21;

                                if(x==0)
                                {
                                    cnt=-1;
                                    max_x=0;
                                    for (int i = 0; i < text.size(); i++)
                                        if(text[i]=='\n')
                                        {
                                            if(pozitii[i].second-dif_y==y_caret)
                                            {
                                                pozitie=i+1,cnt=1;
                                                i=text.size();
                                            }
                                        }
                                        else if(x_caret+12==pozitii[i].first-dif_x&&y_caret==pozitii[i].second-dif_y)
                                        {

                                            pozitie=i;
                                            cnt=1;

                                            i=text.size();
                                        }
                                        else if(y_caret==pozitii[i].second-dif_y)
                                        {
                                            a=i;
                                            max_x=pozitii[i].first-dif_x;
                                        }

                                    if(cnt==-1)
                                    {
                                        pozitie=a+1;
                                        x_caret=max_x;
                                    }
                                    //contor_linie_coloana();
                                }
                                else
                                {
                                    cnt=-1;
                                    for (int i = 0; i < text.size(); i++)
                                        if (pozitii[i].first-dif_x == x_caret && pozitii[i].second-dif_y == y_caret)
                                        {
                                            pozitie = i + 1;
                                            cnt = 1;
                                            i=text.size();
                                        }
                                        else if(y_caret==pozitii[i].second-dif_y)
                                        {
                                            a=i;
                                            max_x=pozitii[i].first-dif_x;
                                        }

                                    if(cnt==-1)
                                    {
                                        pozitie=a+1;
                                        x_caret=min(x_caret,max_x);
                                    }
                                    // contor_linie_coloana();
                                }
                            }
                            else if(y+21>=pozitii[text.size()-1].second-dif_y)
                            {
                                y_caret = pozitii[text.size()-1].second-dif_y;
                                if(x<=pozitii[text.size()-1].first-dif_x)
                                    for(int i=0; i<text.size(); i++)
                                    {
                                        if(pozitii[i].second-dif_y==y_caret&&pozitii[i].first-dif_x==x)
                                        {
                                            pozitie=i+1;
                                            x_caret=x;
                                            i=text.size();
                                        }
                                    }
                                else
                                {
                                    x_caret=min(x,pozitii[text.size()-1].first-dif_x);
                                    pozitie=text.size();
                                }
                                //contor_linie_coloana();
                            }
                        }
                        else
                        {

                            x_caret=0;
                            y_caret=65;
                            pozitie=0;
                            contor_linie_coloana();

                        }


                        //dim_x=(dim_xx-20)/12*12-24;
                        //dim_y=(dim_yy-55-65)/21*21+65-21;


                        //cleardevice();
                        //doar_text();
                        //contor_linie_coloana();
                        //echilibrare_pozitii();

                        if(x_caret!=x_caret_i||y_caret_i!=y_caret)
                        {

                            if(active_page==0)
                                active_page=1;
                            else
                                active_page=0;
                            setactivepage(active_page);
                            cleardevice();
                            drawToolbar();

                            sepLine();
                            settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                            setbkcolor(c_bk);
                            setcolor(c_text);

                            text_selectat=true;

                            if(pozitie_i<pozitie)
                            {
                                aux[1] = 0;
                                x = 0;
                                y = 65;

                                for (int i = 0; i < text.size(); i++)
                                {

                                    if(i==0&&x_caret_i==0&&pozitie_i==1)
                                        setbkcolor(c_selectat);
                                    else if(i>=pozitie_i&&i<pozitie)
                                        setbkcolor(c_selectat);
                                    else
                                        setbkcolor(c_bk);

                                    if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                                    {
                                        x=0;
                                        y+=21;
                                    }
                                    if (text[i] == 10)
                                    {
                                        y = y + textheight(aux);
                                        x = -12;
                                    }

                                    if(text[i]=='\n')
                                        aux[0]=' ';
                                    else
                                        aux[0] = text[i];

                                    if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                        outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                                    x = x + 12;
                                }

                            }
                            else
                            {


                                aux[1] = 0;
                                x = 0;
                                y = 65;

                                for (int i = 0; i < text.size(); i++)
                                {

                                    if(i==0&&x_caret==0&&pozitie==1)
                                        setbkcolor(c_selectat);
                                    else if(i<pozitie_i&&i>=pozitie)
                                        setbkcolor(c_selectat);
                                    else
                                        setbkcolor(c_bk);

                                    if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                                    {
                                        x=0;
                                        y+=21;
                                    }
                                    if (text[i] == 10)
                                    {
                                        y = y + textheight(aux);
                                        x = -12;
                                    }

                                    if(text[i]=='\n')
                                        aux[0]=' ';
                                    else
                                        aux[0] = text[i];

                                    if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                        outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                                    x = x + 12;
                                }
                            }
                            scroll_oriz();
                            scroll_vert();
                            setbkcolor(c_bk);
                            //contor_linie_coloana();
                            setvisualpage(active_page);
                            contor_linie_coloana();


                        }
                        else if(text_selectat==true)
                        {

                            if(active_page==0)
                                active_page=1;
                            else
                                active_page=0;

                            setactivepage(active_page);

                            cleardevice();
                            drawToolbar();
                            sepLine();

                            settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                            setbkcolor(c_bk);
                            setcolor(c_text);
                            text_selectat=false;

                            x = 0;
                            y = 65;

                            for (int i = 0; i < text.size(); i++)
                            {

                                if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                                {
                                    x=0;
                                    y+=21;
                                }
                                if (text[i] == 10)
                                {
                                    y = y + textheight(aux);

                                    x = -12;
                                }

                                if(text[i]=='\n')
                                    aux[0]=' ';
                                else
                                    aux[0] = text[i];

                                if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                    outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                                x = x + 12;
                            }
                            scroll_oriz();
                            scroll_vert();
                            setvisualpage(active_page);
                            contor_linie_coloana();
                        }


                    }
//usleep(10000);


                }


                clearmouseclick(WM_LBUTTONDOWN);


                clearmouseclick(WM_LBUTTONUP);

            }

        }///sfarsit click stanga


        else if (kbhit()&&hex_view==false) ///verificare tasta sau combinatii de taste
        {
            c = getch();
            if(text_cautat==true)
            {
                text_cautat=false;
                doar_text();
            }

            if((c!=1)&&(c!=3)&&(c!=22)&&(c!=24)&&(c!=26)&&(c!=25)&&(c!=6))
            {
                if(c==0||c==224)
                {

                    c=getch();

                    if (c == 72) //sageata sus
                    {
                        text_selectat=false;
                        if (pozitie - 1 >= 0)
                        {
                            y_caret = pozitii[pozitie - 1].second - 21;
                            x_caret = pozitii[pozitie - 1].first;

                            if (y >=65)
                            {
                                if (text[pozitie - 1] == '\n')
                                {
                                    if (pozitie - 2 >= 0)
                                    {
                                        if (text[pozitie - 2] == '\n')
                                            pozitie--;
                                        else
                                        {
                                            x_caret = 0;
                                            int a = 0;

                                            for (int i = 0; i < pozitie - 1; i++)
                                                if (pozitii[i].first == x_caret + 12 && pozitii[i].second == y_caret)
                                                {
                                                    pozitie = i + 1;
                                                    cnt = 1;
                                                    i=text.size();
                                                }
                                                else if (pozitii[i].second == y_caret)
                                                {
                                                    a = i + 1;
                                                    cnt = 2;
                                                }

                                            if (cnt == 2);
                                            pozitie = a;
                                        }
                                    }
                                    else
                                        pozitie = 0;
                                }
                                else
                                {

                                    int a = 0;
                                    cnt = 0;
                                    x_caret = pozitii[pozitie - 1].first;

                                    for (int i = 0; i <= pozitie - 1; i++)
                                        if (pozitii[i].first == x_caret + 12 && pozitii[i].second == y_caret)
                                        {
                                            pozitie = i + 1;
                                            cnt = 1;
                                            i=text.size();
                                        }
                                        else if (pozitii[i].second == y_caret)
                                        {
                                            a = i + 1;
                                            cnt = 2;
                                        }

                                    if (cnt != 1);
                                    pozitie = a;
                                }
                            }
                        }
                        contor_linie_coloana();

                    }
                    else if (c == 80) //sageata jos
                    {
                        text_selectat=false;

                        if (pozitie + 1 <= text.size())
                        {
                            if(pozitie-1>=0)
                            {
                                y_caret = pozitii[pozitie - 1].second + 21;
                                x_caret = pozitii[pozitie - 1].first;
                            }
                            else
                            {
                                x_caret=0;
                                y_caret=65+21;
                            }

                            if (y<= pozitii[text.size() - 1].second)
                            {
                                if (text[pozitie - 1] == '\n')
                                {
                                    if (pozitie < text.size())
                                    {
                                        if (text[pozitie] == '\n'||pozitie==0)
                                            pozitie++;
                                        else
                                        {
                                            x_caret = 0;
                                            int a = text.size();

                                            for (int i = pozitie; i < text.size(); i++)
                                                if (pozitii[i].first == x_caret + 12 && pozitii[i].second == y_caret)
                                                {
                                                    pozitie = i;
                                                    cnt = 1;
                                                    i=text.size();
                                                }
                                                else if (pozitii[i].second == y_caret)
                                                {
                                                    a = i + 1;
                                                    cnt = 2;
                                                }

                                            if (cnt == 2);
                                            pozitie = a;
                                        }
                                    }
                                    else
                                        pozitie = text.size();
                                }
                                else
                                {
                                    int a = text.size();
                                    cnt = 0;
                                    x_caret = pozitii[pozitie - 1].first;

                                    if(pozitie==0)
                                        x_caret=0;

                                    for (int i = pozitie; i < text.size(); i++)
                                        if (pozitii[i].first == x_caret + 12 && pozitii[i].second == y_caret)
                                        {
                                            pozitie = i + 1;
                                            cnt = 1;
                                            i=text.size();
                                        }
                                        else if (pozitii[i].second == y_caret)
                                        {
                                            a = i + 1;
                                            cnt = 2;
                                        }

                                    if (cnt != 1);
                                    pozitie = a;
                                }
                            }
                        }
                        contor_linie_coloana();
                    }
                    else if (c == KEY_DELETE) //tasta delete
                    {


                        if(redo!=NULL)
                        {
                            nod *q=new nod;
                            q=redo;
                            while(q->ant!=NULL)
                            {
                                q=q->ant;
                            }
                            while(undo1!=NULL)
                            {
                                push_stiva(undo,undo1->x_caret,undo1->y_caret,undo1->x_caret_i,undo1->y_caret_i,undo1->pozitie,undo1->pozitie_i,undo1->text,undo1->pozitii);
                                undo1=undo1->ant;
                            }
                            while(q!=NULL)
                            {
                                push_stiva(undo,q->x_caret,q->y_caret,q->x_caret_i,q->y_caret_i,q->pozitie,q->pozitie_i,q->text,q->pozitii);
                                q=q->urm;
                            }
                            delete(undo1);
                            undo1=NULL;
                            delete(redo);
                            redo=NULL;

                        }
                        push_stiva(undo,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,text,pozitii);




                        if(text_selectat==true)
                        {
                            delete_selectat(pozitie_i,pozitie);
                            text_selectat=false;
                        }
                        else if (pozitie < text.size())
                            text.erase(pozitie, 1);
                    }

                    else if (c == 75) //sageata_stanga
                    {
                        text_selectat=false;
                        pozitie = max(0, pozitie - 1);
                    }
                    else if (c == 77) //sageata dreapta
                    {
                        text_selectat=false;
                        pozitie = min((int) text.size(), pozitie + 1);
                    }
                }

                else  if (c == 9) //tab
                {

                    if(text_cautat==true)
                    {
                        text_cautat=false;
                        doar_text();
                    }
                    if(redo!=NULL)
                    {
                        nod *q=new nod;
                        q=redo;
                        while(q->ant!=NULL)
                        {
                            q=q->ant;
                        }
                        while(undo1!=NULL)
                        {
                            push_stiva(undo,undo1->x_caret,undo1->y_caret,undo1->x_caret_i,undo1->y_caret_i,undo1->pozitie,undo1->pozitie_i,undo1->text,undo1->pozitii);
                            undo1=undo1->ant;
                        }
                        while(q!=NULL)
                        {
                            push_stiva(undo,q->x_caret,q->y_caret,q->x_caret_i,q->y_caret_i,q->pozitie,q->pozitie_i,q->text,q->pozitii);
                            q=q->urm;
                        }
                        delete(undo1);
                        undo1=NULL;
                        delete(redo);
                        redo=NULL;

                    }
                    push_stiva(undo,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,text,pozitii);



                    if(text_selectat==true)
                    {
                        delete_selectat(pozitie_i,pozitie);
                        text_selectat=false;
                    }
                    int a = 12 * 8;

                    for (int i = pozitie; i <= pozitie + 7; i++)
                    {
                        text.insert(text.begin() + i, ' ');
                    }

                    pozitie += 8;
                }
                else if (c == 8) //backspace
                {

                    if(redo!=NULL)
                    {
                        nod *q=new nod;
                        q=redo;
                        while(q->ant!=NULL)
                        {
                            q=q->ant;
                        }
                        while(undo1!=NULL)
                        {
                            push_stiva(undo,undo1->x_caret,undo1->y_caret,undo1->x_caret_i,undo1->y_caret_i,undo1->pozitie,undo1->pozitie_i,undo1->text,undo1->pozitii);
                            undo1=undo1->ant;
                        }
                        while(q!=NULL)
                        {
                            push_stiva(undo,q->x_caret,q->y_caret,q->x_caret_i,q->y_caret_i,q->pozitie,q->pozitie_i,q->text,q->pozitii);
                            q=q->urm;
                        }
                        delete(undo1);
                        undo1=NULL;
                        delete(redo);
                        redo=NULL;

                    }
                    push_stiva(undo,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,text,pozitii);



                    if(text_selectat==true)
                    {
                        delete_selectat(pozitie_i,pozitie);
                        text_selectat=false;
                    }
                    else
                    {
                        pozitie = pozitie - 1;

                        if (pozitie >= 0)
                            text.erase(pozitie, 1);
                        else
                            pozitie = 0;
                    }
                }
                else if (c == 13) //enter
                {
                    if(redo!=NULL)
                    {
                        nod *q=new nod;
                        q=redo;
                        while(q->ant!=NULL)
                        {
                            q=q->ant;
                        }
                        while(undo1!=NULL)
                        {
                            push_stiva(undo,undo1->x_caret,undo1->y_caret,undo1->x_caret_i,undo1->y_caret_i,undo1->pozitie,undo1->pozitie_i,undo1->text,undo1->pozitii);
                            undo1=undo1->ant;
                        }
                        while(q!=NULL)
                        {
                            push_stiva(undo,q->x_caret,q->y_caret,q->x_caret_i,q->y_caret_i,q->pozitie,q->pozitie_i,q->text,q->pozitii);
                            q=q->urm;
                        }
                        delete(undo1);
                        undo1=NULL;
                        delete(redo);
                        redo=NULL;

                    }
                    push_stiva(undo,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,text,pozitii);

                    if(text_selectat==true)
                    {
                        delete_selectat(pozitie_i,pozitie);
                        text_selectat=false;
                    }

                    text.insert(text.begin() + pozitie, '\n');
                    pozitie++;
                }
                else if (c == 27) //esc
                {
                    inchidere_fereastra = true;
                    closegraph();
                    return ;
                }
                else if ((c >= '0' && c <= '9' || c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == ' ' || strchr(caractere, c)) && c != 0)
                {
                    if(redo!=NULL)
                    {
                        nod *q=new nod;
                        q=redo;
                        while(q->ant!=NULL)
                        {
                            q=q->ant;
                        }

                        while(undo1!=NULL)
                        {
                            push_stiva(undo,undo1->x_caret,undo1->y_caret,undo1->x_caret_i,undo1->y_caret_i,undo1->pozitie,undo1->pozitie_i,undo1->text,undo1->pozitii);
                            undo1=undo1->ant;
                        }

                        while(q!=NULL)
                        {
                            push_stiva(undo,q->x_caret,q->y_caret,q->x_caret_i,q->y_caret_i,q->pozitie,q->pozitie_i,q->text,q->pozitii);
                            q=q->urm;
                        }
                        delete(undo1);
                        undo1=NULL;
                        delete(redo);
                        redo=NULL;

                    }
                    push_stiva(undo,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,text,pozitii);


                    if(text_selectat==true)
                    {
                        delete_selectat(pozitie_i,pozitie);
                        text_selectat=false;
                    }

                    text.insert(text.begin() + pozitie, c);
                    text_aux=text;
                    pozitie++;
                }


                setbkcolor(c_bk);
                setcolor(c_text);
                if(active_page==0)
                    active_page=1;
                else active_page=0;
                setactivepage(active_page);

                cleardevice();
                drawToolbar();

                sepLine();
                settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                setbkcolor(c_bk);
                setcolor(c_text);

                dim_max_x=0;
                dim_max_y=65;
                x = 0;
                y = 65;
                pozitii.erase(pozitii.begin(), pozitii.end());

                for (int i = 0; i < text.size(); i++)
                {
                    if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                    {
                        x=0;
                        y+=21;
                    }
                    pozitii.push_back({x,y});
                    dim_max_x=max(dim_max_x,x);
                    dim_max_y=max(dim_max_y,y);

                    if (text[i] == 10||text[i]=='$')
                    {
                        y = y + 21;
                        x = 0;
                    }
                    else
                    {
                        pozitii[i].first = x;
                        pozitii[i].second = y;
                        //aux[0] = text[i];
                        x = x + 12;
                        //outtextxy(x, y, aux);
                    }

                    pozitii[i].first = x;
                    pozitii[i].second = y;
                    dim_max_x=max(dim_max_x,x);
                    dim_max_y=max(dim_max_y,y);
                }

                x = 0;
                y = 65;
                if(pozitie!=0)
                {

                    if(pozitii[pozitie-1].first>poz_max_x+12)
                        while(pozitii[pozitie-1].first>poz_max_x+12)
                        {
                            poz_min_x+=12;
                            poz_max_x+=12;

                        }
                    else if(pozitii[pozitie-1].first<poz_min_x)
                        while(pozitii[pozitie-1].first<poz_min_x)
                        {
                            poz_min_x-=12;
                            poz_max_x-=12;
                        }


                    if(pozitii[pozitie-1].second>poz_max_y)
                        while(pozitii[pozitie-1].second>poz_max_y)
                        {
                            poz_min_y+=21;
                            poz_max_y+=21;

                        }
                    else if(pozitii[pozitie-1].second<poz_min_y)
                        while(pozitii[pozitie-1].second<poz_min_y)
                        {
                            poz_min_y-=21;
                            poz_max_y-=21;
                        }
                }
                else
                {
                    poz_min_x=0;
                    poz_max_x=dim_x;
                    poz_min_y=65;
                    poz_max_y=dim_y;
                }



                settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                setbkcolor(c_bk);
                setcolor(c_text);
                x=0;
                y=65;
                for (int i = 0; i < text.size(); i++)
                {
                    //pozitii.push_back({x,y});
                    if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                    {
                        x=0;
                        y+=21;
                    }

                    if (text[i] == 10||text[i]=='$')
                    {
                        y = y + 21;
                        x = 0;
                    }
                    else
                    {
                        //pozitii[i].first = x;
                        //pozitii[i].second = y;
                        aux[0] = text[i];

                        if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                            outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                        x = x + 12;

                    }

                    //pozitii[i].first = x;
                    //pozitii[i].second = y;
                }

                if (pozitie != 0)
                {

                    x_caret = pozitii[pozitie-1].first-poz_min_x;
                    y_caret=pozitii[pozitie-1].second-poz_min_y+65;


                }
                else
                {
                    x_caret = 0;
                    y_caret = 65;
                }
                scroll_oriz();
                scroll_vert();
                contor_linie_coloana();
                setvisualpage(active_page);
                setcolor(c_text);
                line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);

            }
            else
            {
                if(c==1)//ctrl+a
                {


                    if(active_page==0)
                        active_page=1;
                    else
                        active_page=0;
                    setactivepage(active_page);
                    cleardevice();

                    drawToolbar();
                    sepLine();



                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);

                    setcolor(c_text);

                    setbkcolor(c_selectat);
                    x = 0;
                    y = 65;
                    echilibrare_pozitii();

                    for (int i = 0; i < text.size(); i++)
                    {
                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                        {
                            x=0;
                            y+=21;
                        }
                        if (text[i] == 10)
                        {
                            y = y + textheight(aux);
                            x = -12;
                        }

                        if(text[i]=='\n')
                            aux[0]=' ';
                        else
                            aux[0] = text[i];



                        if(aux[0]!='\n')
                            if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                        x = x + 12;
                    }

                    setcolor(c_text);
                    text_selectat=true;
                    setbkcolor(c_bk);
                    scroll_oriz();
                    scroll_vert();
                    setvisualpage(active_page);

                    pozitie_i=0;
                    pozitie=text.size();
                    echilibrare_caret();
                    contor_linie_coloana();
                }
                else if(c==3&&text_selectat==true) //ctrl+c
                {
                    ctrl_c_x('C',control_c,pozitie_i,pozitie);
                }

                else if(c==24&&text_selectat==true) //ctrl+x
                {
                    if(redo!=NULL)
                    {
                        nod *q=new nod;
                        q=redo;
                        while(q->ant!=NULL)
                        {
                            q=q->ant;
                        }
                        while(undo1!=NULL)
                        {
                            push_stiva(undo,undo1->x_caret,undo1->y_caret,undo1->x_caret_i,undo1->y_caret_i,undo1->pozitie,undo1->pozitie_i,undo1->text,undo1->pozitii);
                            undo1=undo1->ant;
                        }
                        while(q!=NULL)
                        {
                            push_stiva(undo,q->x_caret,q->y_caret,q->x_caret_i,q->y_caret_i,q->pozitie,q->pozitie_i,q->text,q->pozitii);
                            q=q->urm;
                        }
                        delete(undo1);
                        undo1=NULL;
                        delete(redo);
                        redo=NULL;

                    }
                    push_stiva(undo,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,text,pozitii);

                    ctrl_c_x('X',control_c,pozitie_i,pozitie);

                    x = 0;
                    y = 65;

                    if(active_page==0)
                        active_page=1;
                    else
                        active_page=0;
                    setactivepage(active_page);
                    cleardevice();



                    drawToolbar();
                    sepLine();
                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                    setbkcolor(c_bk);
                    setcolor(c_text);


                    dim_max_x=0;
                    dim_max_y=65;
                    pozitii.erase(pozitii.begin(), pozitii.end());

                    for (int i = 0; i < text.size(); i++)
                    {
                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                        {
                            x=0;
                            y+=21;
                        }
                        pozitii.push_back({x,y});
                        dim_max_x=max(dim_max_x,x);
                        dim_max_y=max(dim_max_y,y);

                        if (text[i] == 10)
                        {
                            y = y + 21;
                            x = 0;
                        }
                        else
                        {
                            pozitii[i].first = x;
                            pozitii[i].second = y;
                            //aux[0] = text[i];
                            x = x + 12;
                            //outtextxy(x, y, aux);
                        }

                        pozitii[i].first = x;
                        pozitii[i].second = y;
                        dim_max_x=max(dim_max_x,x);
                        dim_max_y=max(dim_max_y,y);
                    }

                    x = 0;
                    y = 65;
                    if(pozitie!=0)
                    {

                        if(pozitii[pozitie-1].first>poz_max_x+12)
                            while(pozitii[pozitie-1].first>poz_max_x+12)
                            {
                                poz_min_x+=12;
                                poz_max_x+=12;

                            }
                        else if(pozitii[pozitie-1].first<poz_min_x)
                            while(pozitii[pozitie-1].first<poz_min_x)
                            {
                                poz_min_x-=12;
                                poz_max_x-=12;
                            }


                        if(pozitii[pozitie-1].second>poz_max_y)
                            while(pozitii[pozitie-1].second>poz_max_y)
                            {
                                poz_min_y+=21;
                                poz_max_y+=21;

                            }
                        else if(pozitii[pozitie-1].second<poz_min_y)
                            while(pozitii[pozitie-1].second<poz_min_y)
                            {
                                poz_min_y-=21;
                                poz_max_y-=21;
                            }
                    }
                    else
                    {
                        poz_min_x=0;
                        poz_max_x=dim_x;
                        poz_min_y=65;
                        poz_max_y=dim_y;
                    }



                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                    setbkcolor(c_bk);
                    setcolor(c_text);
                    for (int i = 0; i < text.size(); i++)
                    {
                        //pozitii.push_back({x,y});
                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                        {
                            x=0;
                            y+=21;
                        }
                        if (text[i] == 10)
                        {
                            y = y + 21;
                            x = 0;
                        }
                        else
                        {
                            //pozitii[i].first = x;
                            //pozitii[i].second = y;
                            aux[0] = text[i];

                            if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                            x = x + 12;

                        }

                        //pozitii[i].first = x;
                        //pozitii[i].second = y;
                    }

                    if (pozitie != 0)
                    {

                        x_caret = pozitii[pozitie-1].first-poz_min_x;
                        y_caret=pozitii[pozitie-1].second-poz_min_y+65;


                    }
                    else
                    {
                        x_caret = 0;
                        y_caret = 65;
                    }
                    contor_linie_coloana();
                    scroll_oriz();
                    scroll_vert();
                    setvisualpage(active_page);
                    setcolor(c_text);
                    line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
                    text_selectat=false;

                }


                else if(c==25) //redo
                {
                    if(redo!=NULL)
                    {
                        nod*q;
                        push_stiva(undo,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,text,pozitii);
                        utilizare_undo_redo(redo,q,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,0);
                    }

                    x = 0;
                    y = 65;

                    if(active_page==0)
                        active_page=1;
                    else active_page=0;
                    setactivepage(active_page);

                    cleardevice();


                    drawToolbar();
                    sepLine();

                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                    setbkcolor(c_bk);
                    setcolor(c_text);
                    dim_max_x=0;
                    dim_max_y=65;
                    pozitii.erase(pozitii.begin(), pozitii.end());

                    for (int i = 0; i < text.size(); i++)
                    {
                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                        {
                            x=0;
                            y+=21;
                        }
                        pozitii.push_back({x,y});
                        dim_max_x=max(dim_max_x,x);
                        dim_max_y=max(dim_max_y,y);

                        if (text[i] == 10)
                        {
                            y = y + 21;
                            x = 0;
                        }
                        else
                        {
                            pozitii[i].first = x;
                            pozitii[i].second = y;
                            //aux[0] = text[i];
                            x = x + 12;
                            //outtextxy(x, y, aux);
                        }

                        pozitii[i].first = x;
                        pozitii[i].second = y;
                        dim_max_x=max(dim_max_x,x);
                        dim_max_y=max(dim_max_y,y);
                    }

                    x = 0;
                    y = 65;
                    if(pozitie!=0)
                    {

                        if(pozitii[pozitie-1].first>poz_max_x+12)
                            while(pozitii[pozitie-1].first>poz_max_x+12)
                            {
                                poz_min_x+=12;
                                poz_max_x+=12;

                            }
                        else if(pozitii[pozitie-1].first<poz_min_x)
                            while(pozitii[pozitie-1].first<poz_min_x)
                            {
                                poz_min_x-=12;
                                poz_max_x-=12;
                            }


                        if(pozitii[pozitie-1].second>poz_max_y)
                            while(pozitii[pozitie-1].second>poz_max_y)
                            {
                                poz_min_y+=21;
                                poz_max_y+=21;

                            }
                        else if(pozitii[pozitie-1].second<poz_min_y)
                            while(pozitii[pozitie-1].second<poz_min_y)
                            {
                                poz_min_y-=21;
                                poz_max_y-=21;
                            }
                    }
                    else
                    {
                        poz_min_x=0;
                        poz_max_x=dim_x;
                        poz_min_y=65;
                        poz_max_y=dim_y;
                    }



                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                    setbkcolor(c_bk);
                    setcolor(c_text);
                    for (int i = 0; i < text.size(); i++)
                    {
                        //pozitii.push_back({x,y});
                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                        {
                            x=0;
                            y+=21;
                        }
                        if (text[i] == 10)
                        {
                            y = y + 21;
                            x = 0;
                        }
                        else
                        {
                            //pozitii[i].first = x;
                            //pozitii[i].second = y;
                            aux[0] = text[i];

                            if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                            x = x + 12;

                        }

                        //pozitii[i].first = x;
                        //pozitii[i].second = y;
                    }

                    if (pozitie != 0)
                    {

                        x_caret = pozitii[pozitie-1].first-poz_min_x;
                        y_caret=pozitii[pozitie-1].second-poz_min_y+65;


                    }
                    else
                    {
                        x_caret = 0;
                        y_caret = 65;
                    }
                    scroll_oriz();
                    scroll_vert();
                    contor_linie_coloana();
                    setvisualpage(active_page);
                    setcolor(c_text);
                    line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);


                }
                else if(c==26)//undo
                {


                    if(undo!=NULL)
                    {


                        nod *q;
                        push_stiva(redo,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,text,pozitii);
                        utilizare_undo_redo(undo,undo1,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,1);
                    }


                    x = 0;
                    y = 65;

                    if(active_page==0)
                        active_page=1;
                    else active_page=0;
                    setactivepage(active_page);

                    cleardevice();

                    drawToolbar();
                    sepLine();

                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                    setbkcolor(c_bk);
                    setcolor(c_text);
                    dim_max_x=0;
                    dim_max_y=65;
                    pozitii.erase(pozitii.begin(), pozitii.end());

                    for (int i = 0; i < text.size(); i++)
                    {
                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                        {
                            x=0;
                            y+=21;
                        }
                        pozitii.push_back({x,y});
                        dim_max_x=max(dim_max_x,x);
                        dim_max_y=max(dim_max_y,y);

                        if (text[i] == 10)
                        {
                            y = y + 21;
                            x = 0;
                        }
                        else
                        {
                            pozitii[i].first = x;
                            pozitii[i].second = y;
                            //aux[0] = text[i];
                            x = x + 12;
                            //outtextxy(x, y, aux);
                        }

                        pozitii[i].first = x;
                        pozitii[i].second = y;
                        dim_max_x=max(dim_max_x,x);
                        dim_max_y=max(dim_max_y,y);
                    }

                    x = 0;
                    y = 65;
                    if(pozitie!=0)
                    {

                        if(pozitii[pozitie-1].first>poz_max_x+12)
                            while(pozitii[pozitie-1].first>poz_max_x+12)
                            {
                                poz_min_x+=12;
                                poz_max_x+=12;

                            }
                        else if(pozitii[pozitie-1].first<poz_min_x)
                            while(pozitii[pozitie-1].first<poz_min_x)
                            {
                                poz_min_x-=12;
                                poz_max_x-=12;
                            }


                        if(pozitii[pozitie-1].second>poz_max_y)
                            while(pozitii[pozitie-1].second>poz_max_y)
                            {
                                poz_min_y+=21;
                                poz_max_y+=21;

                            }
                        else if(pozitii[pozitie-1].second<poz_min_y)
                            while(pozitii[pozitie-1].second<poz_min_y)
                            {
                                poz_min_y-=21;
                                poz_max_y-=21;
                            }
                    }
                    else
                    {
                        poz_min_x=0;
                        poz_max_x=dim_x;
                        poz_min_y=65;
                        poz_max_y=dim_y;
                    }



                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                    setbkcolor(c_bk);
                    setcolor(c_text);
                    for (int i = 0; i < text.size(); i++)
                    {
                        //pozitii.push_back({x,y});
                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                        {
                            x=0;
                            y+=21;
                        }
                        if (text[i] == 10)
                        {
                            y = y + 21;
                            x = 0;
                        }
                        else
                        {
                            //pozitii[i].first = x;
                            //pozitii[i].second = y;
                            aux[0] = text[i];

                            if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                            x = x + 12;

                        }

                        //pozitii[i].first = x;
                        //pozitii[i].second = y;
                    }

                    if (pozitie != 0)
                    {

                        x_caret = pozitii[pozitie-1].first-poz_min_x;
                        y_caret=pozitii[pozitie-1].second-poz_min_y+65;


                    }
                    else
                    {
                        x_caret = 0;
                        y_caret = 65;
                    }
                    contor_linie_coloana();
                    scroll_oriz();
                    scroll_vert();
                    setvisualpage(active_page);
                    setcolor(c_text);
                    line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);







                }
                else if(c==22)//ctrl+v
                {

                    if(redo!=NULL)
                    {
                        nod *q=new nod;
                        q=redo;
                        while(q->ant!=NULL)
                        {
                            q=q->ant;
                        }
                        while(undo1!=NULL)
                        {
                            push_stiva(undo,undo1->x_caret,undo1->y_caret,undo1->x_caret_i,undo1->y_caret_i,undo1->pozitie,undo1->pozitie_i,undo1->text,undo1->pozitii);
                            undo1=undo1->ant;
                        }
                        while(q!=NULL)
                        {
                            push_stiva(undo,q->x_caret,q->y_caret,q->x_caret_i,q->y_caret_i,q->pozitie,q->pozitie_i,q->text,q->pozitii);
                            q=q->urm;
                        }
                        delete(undo1);
                        undo1=NULL;
                        delete(redo);
                        redo=NULL;

                    }
                    push_stiva(undo,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,text,pozitii);



                    if(text_selectat==true)
                    {
                        delete_selectat(pozitie_i,pozitie);
                        text_selectat=false;
                    }

                    ctrl_v(control_c,pozitie_i,pozitie);

                    /*x = 0;
                    y = 65;

                    if(active_page==0)
                        active_page=1;
                    else active_page=0;
                    setactivepage(active_page);

                    cleardevice();

                    drawToolbar();
                    sepLine();

                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                    setbkcolor(c_bk);
                    setcolor(c_text);
                    pozitii.erase(pozitii.begin(), pozitii.end());
                    dim_max_x=0;
                    dim_max_y=65;
                    for (int i = 0; i < text.size(); i++)
                    {
                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                        {
                            x=0;
                            y+=21;
                        }
                        pozitii.push_back({x,y});
                        dim_max_x=max(dim_max_x,x);
                        dim_max_y=max(dim_max_y,y);

                        if (text[i] == 10)
                        {
                            y = y + 21;
                            x = 0;
                        }
                        else
                        {
                            pozitii[i].first = x;
                            pozitii[i].second = y;
                            //aux[0] = text[i];
                            x = x + 12;
                            //outtextxy(x, y, aux);
                        }

                        pozitii[i].first = x;
                        pozitii[i].second = y;
                        dim_max_x=max(dim_max_x,x);
                        dim_max_y=max(dim_max_y,y);
                    }

                    x = 0;
                    y = 65;
                    if(pozitie!=0)
                    {

                        if(pozitii[pozitie-1].first>poz_max_x+12)
                            while(pozitii[pozitie-1].first>poz_max_x+12)
                            {
                                poz_min_x+=12;
                                poz_max_x+=12;

                            }
                        else if(pozitii[pozitie-1].first<poz_min_x)
                            while(pozitii[pozitie-1].first<poz_min_x)
                            {
                                poz_min_x-=12;
                                poz_max_x-=12;
                            }


                        if(pozitii[pozitie-1].second>poz_max_y)
                            while(pozitii[pozitie-1].second>poz_max_y)
                            {
                                poz_min_y+=21;
                                poz_max_y+=21;

                            }
                        else if(pozitii[pozitie-1].second<poz_min_y)
                            while(pozitii[pozitie-1].second<poz_min_y)
                            {
                                poz_min_y-=21;
                                poz_max_y-=21;
                            }
                    }
                    else
                    {
                        poz_min_x=0;
                        poz_max_x=dim_x;
                        poz_min_y=65;
                        poz_max_y=dim_y;
                    }



                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                    setbkcolor(c_bk);
                    setcolor(c_text);
                    for (int i = 0; i < text.size(); i++)
                    {
                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                        {
                            x=0;
                            y+=21;
                        }
                        //pozitii.push_back({x,y});

                        if (text[i] == 10)
                        {
                            y = y + 21;
                            x = 0;
                        }
                        else
                        {
                            //pozitii[i].first = x;
                            //pozitii[i].second = y;
                            aux[0] = text[i];

                            if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                            x = x + 12;

                        }

                        //pozitii[i].first = x;
                        //pozitii[i].second = y;
                    }

                    if (pozitie != 0)
                    {

                        x_caret = pozitii[pozitie-1].first-poz_min_x;
                        y_caret=pozitii[pozitie-1].second-poz_min_y+65;


                    }
                    else
                    {
                        x_caret = 0;
                        y_caret = 65;
                    }
                    scroll_oriz();
                    scroll_vert();
                    contor_linie_coloana();
                    setvisualpage(active_page);
                    setcolor(c_text);
                    line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);*/
                    doar_text();

                }
                ///de refacut
                else if(c==6)//ctrl+f
                {


                    string cautare;
                    int act=true;
                    int j=initwindow(800,50,"Find",(getmaxwidth() - 800) / 2,(getmaxheight() - 50) / 2,false,false);
                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                    setbkcolor(c_bk);
                    setcolor(c_text);
// setfillstyle(COMPLEX_FONT, WHITE);
                    cleardevice();

                    textwidth("Find word: ");
                    while(act)
                    {
                        setcolor(5);
                        outtext("Find word: ");
                        setcolor(c_text);
                        c=getch();
                        char *sir=&cautare[0];

                        if(c==13||c==27)
                        {
                            act=false;
                            closegraph(j);
                            setcurrentwindow(mainWindowHandle);
                        }

                        else  if ((c >= '0' && c <= '9' || c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == ' ' || strchr(caractere, c)) && c != 0)
                        {
                            cleardevice();
                            cautare.push_back(c);
                            outtextxy(textwidth("Find word: "),0,sir);
                            x+=12;
                        }
                        else if(c==8)
                        {
                            if(!cautare.empty())
                            {
                                cleardevice();
                                cautare.pop_back();
                                x-=12;
                                outtextxy(textwidth("Find word: "),0,sir);

                            }
                        }
                    }
                    //  cleardevice();

                    if(active_page==0)
                        active_page=1;
                    else
                        active_page=0;
                    setactivepage(active_page);
                    cleardevice();


                    drawToolbar();
                    sepLine();

                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                    setbkcolor(c_bk);
                    setcolor(c_text);



                    if(!cautare.empty())
                    {

                        cnt=0;
                        int hau=0;
                        aparitii.erase(aparitii.begin(),aparitii.end());
                        while(text.find(cautare,hau)!=string::npos)
                        {
                            aparitii.push_back((int)text.find(cautare,hau));
                            hau=aparitii[cnt]+1;
                            cnt++;
                        }
                        cnt=0;
                        x = 0;
                        y = 65;

                        for (int i = 0; i < text.size(); i++)
                        {

                            if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                            {
                                x=0;
                                y+=21;
                            }
                            if(cnt<aparitii.size())
                            {
                                if(i>=aparitii[cnt]&&(i<=aparitii[cnt]+cautare.size()-1))

                                {

                                    setbkcolor(LIGHTMAGENTA);
                                    if(i==aparitii[cnt]+cautare.size()-1)
                                    {
                                        cnt++;
                                    }

                                }
                                else setbkcolor(c_bk);
                            }
                            else setbkcolor(c_bk);
                            if (text[i] == 10)
                            {
                                y = y + textheight(aux);
                                x = -12;
                            }

                            if(text[i]=='\n')
                                aux[0]=' ';
                            else
                                aux[0] = text[i];



                            if(aux[0]!='\n')
                                if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                    outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                            x = x + 12;
                        }

                        scroll_oriz();
                        scroll_vert();
                        setcolor(c_text);//text_selectat=true;

                        setbkcolor(c_bk);
                        contor_linie_coloana();
                        setvisualpage(active_page);
                        text_cautat=true;
                        cautatt=cautare;
                    }


                }

            }
        }
        else if (kbhit()&&hex_view==true)
        {
            char ll;
            ll=getch();
        }


    }




}

void drawRoundedRectangle(int left, int top, int right, int bottom, int radius,int culoare)
{
    setcolor(culoare);
    /// Desenează partea superioară a dreptunghiului
    line(left + radius, top, right - radius, top);

    /// Desenează colțurile superioare stânga și dreapta
    arc(right - radius, top, 0, 90, radius);
    arc(left + radius, top, 90, 180, radius);

    /// Desenează partea dreaptă a dreptunghiului
    line(right, top + radius, right, bottom - radius);

    /// Desenează colțurile drepte sus și jos
    arc(right, bottom - radius, 270, 360, radius);
    arc(right, top + radius, 0, 90, radius);

    /// Desenează partea de jos a dreptunghiului
    line(right - radius, bottom, left + radius, bottom);

    /// Desenează colțurile de jos stânga și dreapta
    arc(left + radius, bottom, 180, 270, radius);
    arc(right - radius, bottom, 90, 180, radius);

    /// Desenează partea stângă a dreptunghiului
    line(left, bottom - radius, left, top + radius);

    /// Desenează colțurile stângi sus și jos
    arc(left, top + radius, 270, 360, radius);
    arc(left, bottom - radius, 180, 270, radius);
}

void draw_pagina_start()
{

    initwindow(720, getmaxheight()/2, "Notepad",(getmaxwidth()-720)/2,(getmaxheight()-getmaxheight()/2)/2);

    setfillstyle(SOLID_FILL, c_bk);
    setbkcolor(c_bk);
    setcolor(c_text);
    setactivepage(0);
    cleardevice();
    setactivepage(1);
    cleardevice();
    setvisualpage(1);
    setcolor(MAGENTA);
    line(0,80,getmaxx(),80);
    settextstyle(BOLD_FONT,HORIZ_DIR,7);
    outtextxy((getmaxx()-textwidth("TEXT EDITOR"))/2,20,"TEXT EDITOR");

    int star=1, moon=1;
    /* if(star)
      {
          int starCenterX = getmaxx() / 2;  // Center of the menu in the x-axis
          int starCenterY = getmaxy() - 150; // Slightly above the bottom

          setcolor(5);
          line(starCenterX, starCenterY, starCenterX - 50, starCenterY + 80);
          line(starCenterX, starCenterY, starCenterX, starCenterY + 80);
          line(starCenterX, starCenterY + 80, starCenterX - 50, starCenterY + 30);
          line(starCenterX - 50, starCenterY + 30, starCenterX + 30, starCenterY + 30);
          line(starCenterX + 30, starCenterY + 30, starCenterX - 50, starCenterY + 80);

      }
    */


    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    setfillstyle(SOLID_FILL,c_bk);
    bar(30,120,getmaxx()/2,160);
    rectangle(30,120,getmaxx()/2,160);
    outtextxy(80,125,"New file");
    line(getmaxx()/2-60,120,getmaxx()/2-60,160);

    setfillstyle(SOLID_FILL, MAGENTA);

    bar(getmaxx()/2-50,137,getmaxx()/2-10,143);
    rectangle(getmaxx()/2-50,137,getmaxx()/2-10,143);

    bar(getmaxx()/2-34,125,getmaxx()/2-28,155);
    rectangle(getmaxx()/2-34,125,getmaxx()/2-28,155);

    setfillstyle(SOLID_FILL, c_bk);

    bar(30,200,getmaxx()/2,240);
    rectangle(30,200,getmaxx()/2,240);
    outtextxy(80,205,"Open file");
    line(getmaxx()/2-60,200,getmaxx()/2-60,240);


    setfillstyle(SOLID_FILL, MAGENTA);

    bar(getmaxx()/2-50,218,getmaxx()/2-10,233);
    rectangle(getmaxx()/2-50,218,getmaxx()/2-10,233);
    setfillstyle(SOLID_FILL, c_bk);


    bar(getmaxx()/2-50,208,getmaxx()/2-30,218);
    rectangle(getmaxx()/2-50,208,getmaxx()/2-30,218);

    setfillstyle(SOLID_FILL, c_bk);




    bar(30,280,getmaxx()/2,320);
    rectangle(30,280,getmaxx()/2,320);
    outtextxy(80,285,"Exit");
    line(getmaxx()/2-60,280,getmaxx()/2-60,320);



    setfillstyle(SOLID_FILL, MAGENTA);

    //bar(getmaxx()/2-30-10,300-10,getmaxx()/2-30+0,300+10);
    //rectangle(getmaxx()/2-30-20,300-10,getmaxx()/2-30+20,300+10);

    circle(getmaxx()/2-30,300,17);
    floodfill(getmaxx()/2-30,300, MAGENTA);
    setcolor(c_bk);
    setfillstyle(SOLID_FILL, c_bk);
    circle(getmaxx()/2-30,300,14);
    floodfill(getmaxx()/2-30,300, c_bk);


    setfillstyle(SOLID_FILL, MAGENTA);
    setcolor(MAGENTA);

    //bar(getmaxx()/2-30-5,300-5,getmaxx()/2-30+5,300+5);

    drawRoundedRectangle(getmaxx()/2-30-5,300-5,getmaxx()/2-30+5,300+5,1,5);
    floodfill(getmaxx()/2-30,300, MAGENTA);


    setfillstyle(SOLID_FILL, c_bk);

    bar(getmaxx()/2+20,120,getmaxx()-20,320);
    rectangle(getmaxx()/2+20,120,getmaxx()-20,320);


    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    outtextxy(getmaxx()/2+30,130,"Project informations:");

    setcolor(MAGENTA);
    line(getmaxx()/2+20,155,getmaxx()-20,155);
    line(getmaxx()-140,155,getmaxx()-140,320);


    outtextxy(getmaxx()/2+getmaxx()/3,170,"Arseni");
    outtextxy(getmaxx()/2+getmaxx()/3,190,"Costel");
    outtextxy(getmaxx()/2+getmaxx()/3,210,"Ionut");

    //bar(getmaxx()/2+getmaxx()/3,170,getmaxx()/2+getmaxx()/3+textwidth("ARSENI"),210);
    rectangle(getmaxx()/2+getmaxx()/3-5,165,getmaxx()/2+getmaxx()/3+textwidth("ARSENI")+5,235);


    outtextxy(getmaxx()/2+getmaxx()/3,250,"Chelba");
    outtextxy(getmaxx()/2+getmaxx()/3,270,"Sergiu");
    outtextxy(getmaxx()/2+getmaxx()/3,290,"Mihai");
    rectangle(getmaxx()/2+getmaxx()/3-5,245,getmaxx()/2+getmaxx()/3+textwidth("ARSENI")+5,315);

    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    rectangle(getmaxx()/2+25,165,getmaxx()-145,235);
    outtextxy(getmaxx()/2+33,170,"Project number:");
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    outtextxy(getmaxx()/2+90,190,"34");

    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    rectangle(getmaxx()/2+25,245,getmaxx()-145,315);
    outtextxy(getmaxx()/2+50,250,"Team letter:");
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    outtextxy(getmaxx()/2+110,270,"B");


    setfillstyle(SOLID_FILL, MAGENTA);
    bar(0,getmaxy()-10,getmaxx(),getmaxy());
    rectangle(0,getmaxy()-10,getmaxx(),getmaxy());

    bar(0,0,getmaxx(),10);
    rectangle(0,0,getmaxx(),10);
}

void mini_game()
{
    initwindow(630, getmaxheight()/2+60, "Notepad",(getmaxwidth()-630)/2,(getmaxheight()-getmaxheight()/2-60)/2);

    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    outtextxy(30,30,"EXIT");
    rectangle(20,25,40+textwidth("EXIT"),35+textheight("EXIT"));

    outtextxy(30,35+textheight("EXIT")+5,"EXIT");
    rectangle(20,35+textheight("EXIT")+10,40+textwidth("Reset"),35+textheight("EXIT")+10+35+textheight("EXIT"));



    int resetare=0;

    int gd=DETECT, gm;
    int Return=0;
    char Key, ScanCode;
    int Counter=0;

    setbkcolor(c_bk);
    settextstyle(BOLD_FONT,HORIZ_DIR,0);
    cleardevice();

    InitPalette();

    GetImages();

    cleardevice();
    setfillstyle(SOLID_FILL,5);
    bar(0,0,getmaxx(),10);
    bar(0,getmaxy(),getmaxx(),getmaxy()-10);
    setfillstyle(SOLID_FILL,WHITE);
    AssignShape(GetRandomShape(), GetRandomColor());
    NextShape=GetRandomShape();
    NextColor=GetRandomColor();
    DisplayInterface();
    DisplayNextShape();
    MoveBlock(LEFT);
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    outtextxy(30+10,30+5,"Exit");
    rectangle(20,25+5,40+textwidth("RESET"),35+textheight("Exit")+5);

    outtextxy(30,35+5+textheight("RESET")+5,"Reset");
    rectangle(20,35+5+textheight("RESET"),40+textwidth("RESET"),35+textheight("EXIT")+10+textheight("EXIT")+5);

    PrintScore();
    settextstyle(BOLD_FONT,HORIZ_DIR,0);
    while(kbhit()) getch();   //empty the keyboard buffer
    while (!Quit && !GameOver)
    {
        if(ismouseclick(WM_LBUTTONUP))
        {
            if(mousex()>=20&&mousex()<=40+textwidth("EXIT")&&mousey()>=25+5&&mousey()<=35+textheight("EXIT")+5)
            {



                for(int i=0; i<=COLS; i++)
                    for(int j=0; j<=ROWS; j++)
                        PreviousScreenLayout[i][j]=0,ScreenLayout[i][j]=0,ScreenBackgroundLayout[i][j]=0;
                closegraph();

                draw_pagina_start();




                break;
            }
            else if(mousex()>=20&&mousex()<=40+textwidth("EXIT")&&mousey()>=35+5+textheight("RESET")&&mousey()<=35+5+textheight("EXIT")+10+textheight("EXIT"))

            {
                resetare=1;
                break;
            }
            else
            {
                clearmouseclick(WM_LBUTTONDOWN);
                clearmouseclick(WM_LBUTTONUP);
            }
        }
        else
        {
            if(mousex()>=20&&mousex()<=40+textwidth("EXIT")&&mousey()>=25+5&&mousey()<=35+5+textheight("EXIT"))
            {
                settextstyle(BOLD_FONT,HORIZ_DIR,4);
                setcolor(LIGHTRED);
                outtextxy(30+10,30+5,"Exit");
                rectangle(20,25+5,40+textwidth("RESET"),35+textheight("Exit")+5);
                while(mousex()>=20&&mousex()<=40+textwidth("EXIT")&&mousey()>=25+5&&mousey()<=35+5+textheight("EXIT")&&!ismouseclick(WM_LBUTTONUP))usleep(100);

                setcolor(MAGENTA);
                outtextxy(30+10,30+5,"Exit");

                rectangle(20,25+5,40+textwidth("RESET"),35+textheight("Exit")+5);

            }
            else if(mousex()>=20&&mousex()<=40+textwidth("EXIT")&&mousey()>=35+5+textheight("RESET")&&mousey()<=35+5+textheight("EXIT")+10+textheight("EXIT"))
            {
                settextstyle(BOLD_FONT,HORIZ_DIR,4);
                setcolor(LIGHTRED);
                outtextxy(30,35+5+textheight("RESET")+5,"Reset");
                rectangle(20,35+5+textheight("RESET"),40+textwidth("RESET"),35+textheight("EXIT")+10+textheight("EXIT")+5);
                while(mousex()>=20&&mousex()<=40+textwidth("EXIT")&&mousey()>=35+5+textheight("RESET")&&mousey()<=35+5+textheight("EXIT")+10+textheight("EXIT")&&!ismouseclick(WM_LBUTTONUP))usleep(100);

                setcolor(MAGENTA);

                outtextxy(30,35+5+textheight("RESET")+5,"Reset");
                rectangle(20,35+5+textheight("RESET"),40+textwidth("RESET"),35+5+textheight("EXIT")+10+textheight("EXIT"));

            }
        }

        if(++Counter >= Speed)
        {
            Counter=0;
            MoveBlock(DOWN);
        }
        if(kbhit())
        {
            Key = getch();
            if(Key == 0)
            {
                ScanCode = getch();
                if(ScanCode == KEY_UP)
                    RotateBlock();
                else if(ScanCode == KEY_LEFT)
                    Return=MoveBlock(LEFT);
                else if(ScanCode == KEY_RIGHT)
                    Return=MoveBlock(RIGHT);
                else if(ScanCode == KEY_DOWN)
                {


                    MoveBlock(DOWN);
                }
                Return = 0;
            }



        }
        delay(5);
    }
    if(resetare==1)
    {
        for(int i=0; i<=COLS; i++)
            for(int j=0; j<=ROWS; j++)
                PreviousScreenLayout[i][j]=0,ScreenLayout[i][j]=0,ScreenBackgroundLayout[i][j]=0;
        Score=0;
        closegraph();
        mini_game();
    }
    for(int i=0; i<=COLS; i++)
        for(int j=0; j<=ROWS; j++)
            PreviousScreenLayout[i][j]=0,ScreenLayout[i][j]=0,ScreenBackgroundLayout[i][j]=0;
    closegraph();

    draw_pagina_start();


}


int main()
{
    bool exit=false;
    draw_pagina_start();
    while(exit==false)
    {
        while(true)
        {
            if(kbhit())
            {
                char amn;
                amn=getch();
                if(amn==0||amn==224)
                    amn=getch();
            }
            if(ismouseclick(WM_LBUTTONUP))///daca am dat click
            {
                if(mousex()>=0&&mousex()<=getmaxx()&&mousey()>=10&&mousey()<=80)///MINI_GAME
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONUP);
                    closegraph();
                    mini_game();
                }
                else if(mousex()>30&&mousex()<getmaxx()/2)///Ne aflam in meniul cu optiuni
                {
                    if(mousey()>=120&&mousey()<=160)///NEW FILE
                    {

                        closegraph();
                        initializare_fereastra(720,getmaxheight()/2);
                        delete(undo);
                        delete(redo);

                        dim_max_x=0;
                        dim_max_y=0;
                        poz_min_x=0;
                        poz_min_y=65;
                        poz_max_x=dim_x;
                        poz_max_y=dim_y;
                        x_caret=0;
                        y_caret=65;
                        pozitie=0;

                        undo=NULL;
                        redo=NULL;
                        fereastra_fisier=false;
                        fereastra_deschisa=false;
                        cleardevice();


                        drawToolbar();
                        sepLine();
                        scroll_oriz();
                        scroll_vert();
                        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                        setbkcolor(c_bk);
                        setcolor(c_text);


                        // x=0;
                        //y=65;

                        text.erase(text.begin(),text.end());
                        pozitii.erase(pozitii.begin(),pozitii.end());
                        echilibrare_pozitii();
                        echilibrare_caret();
                        contor_linie_coloana();
                        //scriere_text();
                        break;
                    }
                    else if(mousey()>=200&&mousey()<=240)///OPEN FILE
                    {
                        closegraph();
                        initializare_fereastra(720,getmaxheight()/2);
                        char szFile[260];
                        delete(undo);
                        delete(redo);
                        undo=NULL;
                        redo=NULL;
                        OPENFILENAME ofn;

                        ZeroMemory(&ofn, sizeof(ofn));
                        ofn.lStructSize = sizeof(ofn);
                        ofn.hwndOwner = NULL;
                        ofn.lpstrFile = szFile;
                        ofn.nMaxFile = sizeof(szFile);
                        ofn.lpstrFilter = "Fisiere text\0*.txt\0Toate fisierele\0*.*\0";
                        ofn.nFilterIndex = 1;
                        ofn.lpstrFileTitle = NULL;
                        ofn.nMaxFileTitle = 0;
                        ofn.lpstrInitialDir = NULL;
                        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                        ofn.lpstrDefExt = "txt"; // extensia implicită

                        if (GetOpenFileName(&ofn) == TRUE)
                        {
                            text.erase(text.begin(),text.end());
                            ifstream fin(szFile);
                            if (fin.is_open())
                            {
                                char p[10000];
                                while (fin.getline(p, sizeof(p)))
                                {
                                    for (int i = 0; i < strlen(p); i++)
                                    {
                                        text.push_back(p[i]);
                                    }
                                    text.push_back('\n');
                                }

                                fin.close();
                            }

                            x = 0;
                            y = 65;

                            if(active_page==0)
                                active_page=1;
                            else active_page=0;
                            setactivepage(active_page);
                            cleardevice();
                            drawToolbar();
                            scroll_oriz();
                            scroll_vert();
                            sepLine();
                            settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                            setbkcolor(c_bk);
                            setcolor(c_text);
                            pozitie=pozitie_i=0;
                            pozitii.erase(pozitii.begin(), pozitii.end());

                            for (int i = 0; i < text.size(); i++)
                            {
                                pozitii.push_back({x,y});
                                dim_max_x=max(dim_max_x,x);
                                dim_max_y=max(dim_max_y,y);

                                if (text[i] == 10)
                                {
                                    y = y + 21;
                                    x = 0;
                                }
                                else
                                {
                                    pozitii[i].first = x;
                                    pozitii[i].second = y;
                                    //aux[0] = text[i];
                                    x = x + 12;
                                    //outtextxy(x, y, aux);
                                }

                                pozitii[i].first = x;
                                pozitii[i].second = y;
                                dim_max_x=max(dim_max_x,x);
                                dim_max_y=max(dim_max_y,y);
                            }

                            x = 0;
                            y = 65;
                            if(pozitie!=0)
                            {

                                if(pozitii[pozitie-1].first>poz_max_x+12)
                                    while(pozitii[pozitie-1].first>poz_max_x+12)
                                    {
                                        poz_min_x+=12;
                                        poz_max_x+=12;

                                    }
                                else if(pozitii[pozitie-1].first<poz_min_x)
                                    while(pozitii[pozitie-1].first<poz_min_x)
                                    {
                                        poz_min_x-=12;
                                        poz_max_x-=12;
                                    }


                                if(pozitii[pozitie-1].second>poz_max_y)
                                    while(pozitii[pozitie-1].second>poz_max_y)
                                    {
                                        poz_min_y+=21;
                                        poz_max_y+=21;

                                    }
                                else if(pozitii[pozitie-1].second<poz_min_y)
                                    while(pozitii[pozitie-1].second<poz_min_y)
                                    {
                                        poz_min_y-=21;
                                        poz_max_y-=21;
                                    }
                            }
                            else
                            {
                                poz_min_x=0;
                                poz_max_x=dim_x;
                                poz_min_y=65;
                                poz_max_y=dim_y;
                            }
                            setvisualpage(active_page);
                            setcolor(c_text);
                            line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);


                        }


                        contor_linie_coloana();
                        doar_text();
                        break;
                    }
                    else if(mousey()>=280&&mousey()<=320)///EXIT
                    {
                        closegraph();
                        exit=true;
                        break;
                    }

                    else ///Niciuna dintre optiunile de mai sus
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        clearmouseclick(WM_LBUTTONUP);
                    }
                }

                else///nu ne aflam in meniul cu optiuni
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONUP);
                }
            }

            if(!ismouseclick(WM_LBUTTONDOWN))///daca mergem cu cursorul, trebuie sa coloram optiunile
            {
                if(mousex()>30&&mousex()<getmaxx()/2&&mousey()>=120&&mousey()<=160)///NEW FILE
                {
                    settextstyle(BOLD_FONT,HORIZ_DIR,4);
                    setcolor(LIGHTRED);

                    rectangle(30,120,getmaxx()/2,160);

                    outtextxy(80,125,"New file");

                    line(getmaxx()/2-60,120,getmaxx()/2-60,160);
                    setfillstyle(SOLID_FILL,LIGHTRED);
                    bar(getmaxx()/2-50,137,getmaxx()/2-10,143);
                    rectangle(getmaxx()/2-50,137,getmaxx()/2-10,143);
                    bar(getmaxx()/2-34,125,getmaxx()/2-28,155);

                    rectangle(getmaxx()/2-34,125,getmaxx()/2-28,155);


                    setfillstyle(SOLID_FILL, c_bk);


                    while(mousex()>30&&mousex()<getmaxx()/2&&mousey()>=120&&mousey()<=160&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())usleep(100);

                    setcolor(5);

                    rectangle(30,120,getmaxx()/2,160);

                    outtextxy(80,125,"New file");

                    line(getmaxx()/2-60,120,getmaxx()/2-60,160);

                    setfillstyle(SOLID_FILL, 5);

                    setfillstyle(SOLID_FILL,5);
                    bar(getmaxx()/2-50,137,getmaxx()/2-10,143);
                    rectangle(getmaxx()/2-50,137,getmaxx()/2-10,143);
                    bar(getmaxx()/2-34,125,getmaxx()/2-28,155);

                    rectangle(getmaxx()/2-34,125,getmaxx()/2-28,155);

                    setfillstyle(SOLID_FILL, c_bk);


                }

                if(mousex()>30&&mousex()<getmaxx()/2&&mousey()>=200&&mousey()<=240)///OPEN FILE

                {
                    settextstyle(BOLD_FONT,HORIZ_DIR,4);
                    setcolor(LIGHTRED);
                    rectangle(30,200,getmaxx()/2,240);
                    outtextxy(80,205,"Open file");
                    line(getmaxx()/2-60,200,getmaxx()/2-60,240);


                    setfillstyle(SOLID_FILL, LIGHTRED);

                    bar(getmaxx()/2-50,218,getmaxx()/2-10,233);
                    rectangle(getmaxx()/2-50,218,getmaxx()/2-10,233);
                    setfillstyle(SOLID_FILL, c_bk);


                    bar(getmaxx()/2-50,208,getmaxx()/2-30,218);
                    rectangle(getmaxx()/2-50,208,getmaxx()/2-30,218);

                    setfillstyle(SOLID_FILL, c_bk);

                    while(mousex()>30&&mousex()<getmaxx()/2&&mousey()>=200&&mousey()<=240&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())usleep(100);
                    setcolor(5);
                    rectangle(30,200,getmaxx()/2,240);
                    outtextxy(80,205,"Open file");
                    line(getmaxx()/2-60,200,getmaxx()/2-60,240);


                    setfillstyle(SOLID_FILL, MAGENTA);

                    bar(getmaxx()/2-50,218,getmaxx()/2-10,233);
                    rectangle(getmaxx()/2-50,218,getmaxx()/2-10,233);
                    setfillstyle(SOLID_FILL, c_bk);


                    bar(getmaxx()/2-50,208,getmaxx()/2-30,218);
                    rectangle(getmaxx()/2-50,208,getmaxx()/2-30,218);

                    setfillstyle(SOLID_FILL, c_bk);

                }

                setfillstyle(SOLID_FILL, c_bk);

                if(mousex()>30&&mousex()<getmaxx()/2&&mousey()>=280&&mousey()<=320)///EXIT
                {
                    settextstyle(BOLD_FONT,HORIZ_DIR,4);
                    setcolor(LIGHTRED);
                    bar(30,280,getmaxx()/2,320);
                    rectangle(30,280,getmaxx()/2,320);
                    outtextxy(80,285,"Exit");
                    line(getmaxx()/2-60,280,getmaxx()/2-60,320);



                    setfillstyle(SOLID_FILL, LIGHTRED);

                    //bar(getmaxx()/2-30-10,300-10,getmaxx()/2-30+0,300+10);
                    //rectangle(getmaxx()/2-30-20,300-10,getmaxx()/2-30+20,300+10);

                    circle(getmaxx()/2-30,300,17);
                    floodfill(getmaxx()/2-30,300, LIGHTRED);
                    setcolor(c_bk);
                    setfillstyle(SOLID_FILL, c_bk);
                    circle(getmaxx()/2-30,300,14);
                    floodfill(getmaxx()/2-30,300, c_bk);


                    setfillstyle(SOLID_FILL, LIGHTRED);
                    setcolor(MAGENTA);

//bar(getmaxx()/2-30-5,300-5,getmaxx()/2-30+5,300+5);

                    drawRoundedRectangle(getmaxx()/2-30-5,300-5,getmaxx()/2-30+5,300+5,1,LIGHTRED);
                    floodfill(getmaxx()/2-30,300, LIGHTRED);


                    setfillstyle(SOLID_FILL, c_bk);
                    while(mousex()>30&&mousex()<getmaxx()/2&&mousey()>=280&&mousey()<=320&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())usleep(100);
                    setcolor(5);
                    bar(30,280,getmaxx()/2,320);
                    rectangle(30,280,getmaxx()/2,320);
                    outtextxy(80,285,"Exit");
                    line(getmaxx()/2-60,280,getmaxx()/2-60,320);



                    setfillstyle(SOLID_FILL, MAGENTA);

                    //bar(getmaxx()/2-30-10,300-10,getmaxx()/2-30+0,300+10);
                    //rectangle(getmaxx()/2-30-20,300-10,getmaxx()/2-30+20,300+10);

                    circle(getmaxx()/2-30,300,17);
                    floodfill(getmaxx()/2-30,300, MAGENTA);
                    setcolor(c_bk);
                    setfillstyle(SOLID_FILL, c_bk);
                    circle(getmaxx()/2-30,300,14);
                    floodfill(getmaxx()/2-30,300, c_bk);


                    setfillstyle(SOLID_FILL, MAGENTA);
                    setcolor(MAGENTA);

//bar(getmaxx()/2-30-5,300-5,getmaxx()/2-30+5,300+5);

                    drawRoundedRectangle(getmaxx()/2-30-5,300-5,getmaxx()/2-30+5,300+5,1,5);
                    floodfill(getmaxx()/2-30,300, MAGENTA);


                    setfillstyle(SOLID_FILL, c_bk);
                }

                if(mousex()>=getmaxx()/2+getmaxx()/3-5&&mousex()<=687&&mousey()>=165&&mousey()<=235)///Arseni Costel-Ionut
                {
                    setcolor(CYAN);
                    settextstyle(BOLD_FONT,HORIZ_DIR,3);
                    outtextxy(getmaxx()/2+getmaxx()/3,170,"Arseni");
                    outtextxy(getmaxx()/2+getmaxx()/3,190,"Costel");
                    outtextxy(getmaxx()/2+getmaxx()/3,210,"Ionut");

//bar(getmaxx()/2+getmaxx()/3,170,getmaxx()/2+getmaxx()/3+textwidth("ARSENI"),210);
                    rectangle(getmaxx()/2+getmaxx()/3-5,165,getmaxx()/2+getmaxx()/3+textwidth("ARSENI")+5,235);
                    while(mousex()>=getmaxx()/2+getmaxx()/3-5&&mousex()<=687&&mousey()>=165&&mousey()<=235&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())usleep(100);
                    setcolor(MAGENTA);
                    outtextxy(getmaxx()/2+getmaxx()/3,170,"Arseni");
                    outtextxy(getmaxx()/2+getmaxx()/3,190,"Costel");
                    outtextxy(getmaxx()/2+getmaxx()/3,210,"Ionut");

//bar(getmaxx()/2+getmaxx()/3,170,getmaxx()/2+getmaxx()/3+textwidth("ARSENI"),210);
                    rectangle(getmaxx()/2+getmaxx()/3-5,165,getmaxx()/2+getmaxx()/3+textwidth("ARSENI")+5,235);
                }


                if(mousex()>=getmaxx()/2+getmaxx()/3-5&&mousex()<=687&&mousey()>=245&&mousey()<=315)///Chelba Sergiu-Mihai
                {
                    setcolor(CYAN);
                    settextstyle(BOLD_FONT,HORIZ_DIR,3);
                    outtextxy(getmaxx()/2+getmaxx()/3,250,"Chelba");
                    outtextxy(getmaxx()/2+getmaxx()/3,270,"Sergiu");
                    outtextxy(getmaxx()/2+getmaxx()/3,290,"Mihai");
                    rectangle(getmaxx()/2+getmaxx()/3-5,245,687,315);

                    while(mousex()>=getmaxx()/2+getmaxx()/3-5&&mousex()<=687&&mousey()>=245&&mousey()<=315&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())usleep(100);

                    setcolor(MAGENTA);
                    outtextxy(getmaxx()/2+getmaxx()/3,250,"Chelba");
                    outtextxy(getmaxx()/2+getmaxx()/3,270,"Sergiu");
                    outtextxy(getmaxx()/2+getmaxx()/3,290,"Mihai");
                    rectangle(getmaxx()/2+getmaxx()/3-5,245,getmaxx()/2+getmaxx()/3+textwidth("ARSENI")+5,315);

                }


                if(mousex()>=0&&mousex()<=getmaxx()&&mousey()>=10&&mousey()<=80)///TEXT EDITOR
                {
                    setcolor(LIGHTGREEN);
                    line(0,80,146,80);
                    line(578,80,getmaxx(),80);
                    settextstyle(BOLD_FONT,HORIZ_DIR,7);
                    rectangle(0,getmaxy()-10,getmaxx(),getmaxy());
                    rectangle(0,0,getmaxx(),10);
                    outtextxy((getmaxx()-textwidth("TEXT EDITOR"))/2,20,"TEXT EDITOR");

                    setfillstyle(SOLID_FILL, 5);
                    bar(0,getmaxy()-10,getmaxx(),getmaxy());

                    bar(0,0,getmaxx(),10);

                    while(mousex()>=0&&mousex()<=getmaxx()&&mousey()>=10&&mousey()<=80&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())usleep(100);

                    setfillstyle(SOLID_FILL, MAGENTA);
                    bar(0,getmaxy()-10,getmaxx(),getmaxy());
                    rectangle(0,getmaxy()-10,getmaxx(),getmaxy());
                    bar(0,0,getmaxx(),10);
                    rectangle(0,0,getmaxx(),10);
                    setcolor(5);
                    line(0,80,146,80);
                    line(578,80,getmaxx(),80);
                    settextstyle(BOLD_FONT,HORIZ_DIR,7);
                    outtextxy((getmaxx()-textwidth("TEXT EDITOR"))/2,20,"TEXT EDITOR");
                }

                setfillstyle(SOLID_FILL, WHITE);

                if(mousex()>=getmaxx()/2+25&&mousex()<=getmaxx()-145&&mousey()>=165&&mousey()<=235)///Project number
                {
                    setcolor(CYAN);
                    settextstyle(BOLD_FONT,HORIZ_DIR,2);

                    rectangle(getmaxx()/2+25,165,getmaxx()-145,235);
                    rectangle(getmaxx()/2+25,165,getmaxx()-145,235);

                    outtextxy(getmaxx()/2+33,170,"Project number:");
                    settextstyle(BOLD_FONT,HORIZ_DIR,5);
                    outtextxy(getmaxx()/2+90,190,"34");

                    while(mousex()>=getmaxx()/2+25&&mousex()<=getmaxx()-145&&mousey()>=165&&mousey()<=235&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())usleep(100);


                    setcolor(5);

                    settextstyle(BOLD_FONT,HORIZ_DIR,2);
                    rectangle(getmaxx()/2+25,165,getmaxx()-145,235);
                    outtextxy(getmaxx()/2+33,170,"Project number:");
                    settextstyle(BOLD_FONT,HORIZ_DIR,5);
                    outtextxy(getmaxx()/2+90,190,"34");


                }

                if(mousex()>=getmaxx()/2+25&&mousex()<=getmaxx()-145&&mousey()>=245&&mousey()<=315)///Team letter
                {
                    setcolor(CYAN);
                    settextstyle(BOLD_FONT,HORIZ_DIR,2);
                    rectangle(getmaxx()/2+25,245,getmaxx()-145,315);
                    outtextxy(getmaxx()/2+50,250,"Team letter:");
                    settextstyle(BOLD_FONT,HORIZ_DIR,5);
                    outtextxy(getmaxx()/2+110,270,"B");

                    while(mousex()>=getmaxx()/2+25&&mousex()<=getmaxx()-145&&mousey()>=245&&mousey()<=315&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())usleep(100);

                    setcolor(5);
                    settextstyle(BOLD_FONT,HORIZ_DIR,2);
                    rectangle(getmaxx()/2+25,245,getmaxx()-145,315);
                    outtextxy(getmaxx()/2+50,250,"Team letter:");
                    settextstyle(BOLD_FONT,HORIZ_DIR,5);
                    outtextxy(getmaxx()/2+110,270,"B");

                }

                if(mousex()>=getmaxx()/2+20&&mousex()<=getmaxx()-20&&mousey()>=120&&mousey()<=170)///Project informations
                {
                    setcolor(CYAN);
                    rectangle(getmaxx()/2+20,120,getmaxx()-20,320);


                    settextstyle(BOLD_FONT,HORIZ_DIR,3);
                    outtextxy(getmaxx()/2+30,130,"Project informations:");
                    line(getmaxx()/2+20,155,getmaxx()-20,155);
                    line(getmaxx()-140,155,getmaxx()-140,320);

                    while(mousex()>=getmaxx()/2+20&&mousex()<=getmaxx()-20&&mousey()>=120&&mousey()<=170&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())usleep(100);

                    setcolor(5);
                    rectangle(getmaxx()/2+20,120,getmaxx()-20,320);

                    line(getmaxx()/2+20,155,getmaxx()-20,155);
                    line(getmaxx()-140,155,getmaxx()-140,320);
                    settextstyle(BOLD_FONT,HORIZ_DIR,3);
                    outtextxy(getmaxx()/2+30,130,"Project informations:");


                }
            }

        }
        if(exit==false)///daca nu am iesit
        {
            while(inchidere_fereastra==false)
            {
                if(fereastra_deschisa==false)///scriu in partea de sub meniu
                    scriere_text();
                else if((y<10)||(y>30)||(x<10||x>710)||(x>110&&x<120)||(x>230&&x<240)||(x>350 &&x<360)||(x>470&&x<480)||(x>590&&x<600))///daca ies din zona de scriere
                {
                    int j=true;
                    fereastra_deschisa=false;
                }
                else if(x>=10&&x<=110 && fereastra_fisier==false)///daca apas FILE in timp ce ruleaza zona de scriere
                {

                    displayFileMenu();
                    fereastra_fisier=true;

                    while(fereastra_fisier)///FISIER+FISIER_MENU
                    {
                        if(kbhit())///daca apas o tasta
                        {
                            char temporar;
                            temporar=getch();
                            if(temporar==0||temporar==224)
                                temporar=getch();
                        }
                        if(ismouseclick(WM_LBUTTONDBLCLK))///dublu click stanga
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            while(!ismouseclick(WM_LBUTTONUP));
                            clearmouseclick(WM_LBUTTONUP);

                            clearmouseclick(WM_LBUTTONDBLCLK);

                        }

                        if(ismouseclick(WM_LBUTTONDOWN))///click stanga
                        {

                            x=mousex(),y=mousey();

                            if(x>=10&&x<=110)///FISIER_MENU
                            {
                                if(y>=30&&y<=70)///FILA NOUA
                                {
                                    delete(undo);
                                    delete(redo);

                                    dim_max_x=0;
                                    dim_max_y=0;
                                    poz_min_x=0;
                                    poz_min_y=65;
                                    poz_max_x=dim_x;
                                    poz_max_y=dim_y;
                                    x_caret=0;
                                    y_caret=65;
                                    pozitie=0;

                                    undo=NULL;
                                    redo=NULL;
                                    fereastra_fisier=false;
                                    fereastra_deschisa=false;
                                    cleardevice();


                                    drawToolbar();
                                    sepLine();
                                    scroll_oriz();
                                    scroll_vert();
                                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);


                                    // x=0;
                                    //y=65;

                                    text.erase(text.begin(),text.end());
                                    pozitii.erase(pozitii.begin(),pozitii.end());
                                    echilibrare_pozitii();
                                    echilibrare_caret();
                                    contor_linie_coloana();
                                    //scriere_text();

                                }
                                else if(y>=70&&y<=90)///DESCHIDETI FILA EXISTENTA
                                {
                                    char szFile[260];
                                    delete(undo);
                                    delete(redo);
                                    undo=NULL;
                                    redo=NULL;
                                    OPENFILENAME ofn;

                                    ZeroMemory(&ofn, sizeof(ofn));
                                    ofn.lStructSize = sizeof(ofn);
                                    ofn.hwndOwner = NULL;
                                    ofn.lpstrFile = szFile;
                                    ofn.nMaxFile = sizeof(szFile);
                                    ofn.lpstrFilter = "Fisiere text\0*.txt\0Toate fisierele\0*.*\0";
                                    ofn.nFilterIndex = 1;
                                    ofn.lpstrFileTitle = NULL;
                                    ofn.nMaxFileTitle = 0;
                                    ofn.lpstrInitialDir = NULL;
                                    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                                    ofn.lpstrDefExt = "txt"; // extensia implicită

                                    if (GetOpenFileName(&ofn) == TRUE)
                                    {
                                        text.erase(text.begin(),text.end());
                                        ifstream fin(szFile);
                                        if (fin.is_open())
                                        {
                                            char p[10000];
                                            while (fin.getline(p, sizeof(p)))
                                            {
                                                for (int i = 0; i < strlen(p); i++)
                                                {
                                                    text.push_back(p[i]);
                                                }
                                                text.push_back('\n');
                                            }

                                            fin.close();
                                        }


                                        x = 0;
                                        y = 65;

                                        if(active_page==0)
                                            active_page=1;
                                        else active_page=0;
                                        setactivepage(active_page);
                                        cleardevice();
                                        drawToolbar();
                                        scroll_oriz();
                                        scroll_vert();
                                        sepLine();
                                        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                        setbkcolor(c_bk);
                                        setcolor(c_text);
                                        pozitie=pozitie_i=0;
                                        pozitii.erase(pozitii.begin(), pozitii.end());

                                        for (int i = 0; i < text.size(); i++)
                                        {
                                            pozitii.push_back({x,y});
                                            dim_max_x=max(dim_max_x,x);
                                            dim_max_y=max(dim_max_y,y);

                                            if (text[i] == 10)
                                            {
                                                y = y + 21;
                                                x = 0;
                                            }
                                            else
                                            {
                                                pozitii[i].first = x;
                                                pozitii[i].second = y;
                                                //aux[0] = text[i];
                                                x = x + 12;
                                                //outtextxy(x, y, aux);
                                            }

                                            pozitii[i].first = x;
                                            pozitii[i].second = y;
                                            dim_max_x=max(dim_max_x,x);
                                            dim_max_y=max(dim_max_y,y);
                                        }

                                        x = 0;
                                        y = 65;
                                        if(pozitie!=0)
                                        {

                                            if(pozitii[pozitie-1].first>poz_max_x+12)
                                                while(pozitii[pozitie-1].first>poz_max_x+12)
                                                {
                                                    poz_min_x+=12;
                                                    poz_max_x+=12;

                                                }
                                            else if(pozitii[pozitie-1].first<poz_min_x)
                                                while(pozitii[pozitie-1].first<poz_min_x)
                                                {
                                                    poz_min_x-=12;
                                                    poz_max_x-=12;
                                                }


                                            if(pozitii[pozitie-1].second>poz_max_y)
                                                while(pozitii[pozitie-1].second>poz_max_y)
                                                {
                                                    poz_min_y+=21;
                                                    poz_max_y+=21;

                                                }
                                            else if(pozitii[pozitie-1].second<poz_min_y)
                                                while(pozitii[pozitie-1].second<poz_min_y)
                                                {
                                                    poz_min_y-=21;
                                                    poz_max_y-=21;
                                                }
                                        }
                                        else
                                        {
                                            poz_min_x=0;
                                            poz_max_x=dim_x;
                                            poz_min_y=65;
                                            poz_max_y=dim_y;
                                        }
                                        setvisualpage(active_page);
                                        setcolor(c_text);
                                        line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);


                                    }

                                    fereastra_fisier=false;
                                    fereastra_deschisa=false;
                                    contor_linie_coloana();
                                    doar_text();
                                }
                                else if(y>=90&&y<=110)///SALVATI CA
                                {
                                    delete(undo);
                                    delete(redo);
                                    undo=NULL;
                                    redo=NULL;

                                    char szFile[260];


                                    OPENFILENAME ofn;

                                    ZeroMemory(&ofn, sizeof(ofn));
                                    ofn.lStructSize = sizeof(ofn);
                                    ofn.hwndOwner = NULL;
                                    ofn.lpstrFile = szFile;
                                    ofn.nMaxFile = sizeof(szFile);
                                    ofn.lpstrFilter = "Fisiere text\0*.txt\0Toate fisierele\0*.*\0";
                                    ofn.nFilterIndex = 1;
                                    ofn.lpstrFileTitle = NULL;
                                    ofn.nMaxFileTitle = 0;
                                    ofn.lpstrInitialDir = NULL;
                                    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
                                    ofn.lpstrDefExt = "txt"; // extensia implicită

                                    if (GetSaveFileName(&ofn) == TRUE)
                                    {
                                        ofstream fout(szFile);
                                        if (fout.is_open())
                                        {
                                            fout << text;
                                            fout.close();

                                        }

                                    }
                                    else
                                    {

                                    }

                                    fereastra_fisier=false;
                                    fereastra_deschisa=false;
                                    contor_linie_coloana();
                                    if(active_page==0)
                                        active_page=1;
                                    else active_page=0;
                                    setactivepage(active_page);
                                    cleardevice();
                                    drawToolbar();
                                    scroll_oriz();
                                    scroll_vert();
                                    sepLine();
                                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);
                                    doar_text();
                                    setvisualpage(active_page);
                                    setcolor(c_text);
                                    line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);

                                }
                                else if(y>=110&&y<=140)///IESIRE
                                {
                                    fereastra_fisier=false;
                                    fereastra_deschisa=false;
                                    inchidere_fereastra=true;

                                    clearmouseclick(WM_LBUTTONDOWN);
                                    while(ismouseclick(WM_LBUTTONUP));
                                    clearmouseclick(WM_LBUTTONUP);


                                    closegraph();
                                    draw_pagina_start();

                                }
                                else///revenim in zona de scriere
                                {

                                    contor_linie_coloana();
                                    fereastra_fisier=false;
                                    fereastra_deschisa=false;
                                    /* clearmouseclick(WM_LBUTTONDOWN);
                                     while(ismouseclick(WM_LBUTTONUP));
                                     clearmouseclick(WM_LBUTTONUP);

                                                     usleep(1000);*/
                                    doar_text();

                                }
                            }
                            else
                            {
                                int lx=x,ly=y;
                                contor_linie_coloana();
                                fereastra_fisier=false;
                                //fereastra_deschisa=false;
                                doar_text();
                                x=lx;
                                y=ly;
                            }


                        }
                        else///daca doar trec cu cursorul
                        {
                            if(mousex()>=10&&mousex()<=110&&mousey()>=10&&mousey()<=130)///FILE+FILE_MENU
                            {

                                if(mousey()>=10&&mousey()<=30&&!ismouseclick(WM_LBUTTONDOWN))///FILE
                                {

                                    setcolor(LIGHTRED);
                                    setbkcolor(c_bk);
                                    outtextxy(38, 12, "File");
                                    setfillstyle(SOLID_FILL,LIGHTGRAY);
                                    bar(11, 30, 109, 33);
                                    rectangle(10, 10, 110, 30);

                                    while (mousex()>=10&&mousex()<=110&&mousey()>=10&&mousey()<=30&&!ismouseclick(WM_LBUTTONDOWN))
                                        usleep(100);
                                    setcolor(5);


                                    outtextxy(38, 12, "File");


                                    bar(11, 30, 109, 33);
                                    rectangle(10, 10, 110, 30);
                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }

                                if(mousey()>=50&&mousey()<=70&&!ismouseclick(WM_LBUTTONDOWN))///NEW
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(20, 50, "New");
                                    rectangle(11,50,109,70),usleep(100);

                                    while (mousex()>=10&&mousex()<=110&&mousey()>=50&&mousey()<=70&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(11,50,109,70),usleep(100);
                                    setcolor(5);
                                    outtextxy(20, 50, "New");
                                }

                                if(mousey()>70&&mousey()<=90&&!ismouseclick(WM_LBUTTONDOWN))///OPEN
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(20, 70, "Open");
                                    rectangle(11,70,109,90),usleep(100);

                                    while (mousex()>=10&&mousex()<=110&&mousey()>70&&mousey()<=90&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(11,70,109,90),usleep(100);
                                    setcolor(5);
                                    outtextxy(20, 70, "Open");
                                }

                                if(mousey()>90&&mousey()<=110&&!ismouseclick(WM_LBUTTONDOWN))///SAVE
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(20, 90, "Save");
                                    rectangle(11,90,109,110),usleep(100);

                                    while (mousex()>=10&&mousex()<=110&&mousey()>90&&mousey()<=110&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(11,90,109,110),usleep(100);
                                    setcolor(5);
                                    outtextxy(20, 90, "Save");
                                }


                                if(mousey()>110&&mousey()<=130&&!ismouseclick(WM_LBUTTONDOWN))///EXIT
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(20, 110, "Exit");
                                    rectangle(11,110,109,130),usleep(100);

                                    while (mousex()>=10&&mousex()<=110&&mousey()>110&&mousey()<=130&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(11,110,109,130),usleep(100);
                                    setcolor(5);
                                    outtextxy(20, 110, "Exit");
                                }
                            }

                            if(mousey()>=10&&mousey()<=30)
                            {

                                if(mousex()>=120&&mousex()<=230&&!ismouseclick(WM_LBUTTONDOWN))///EDIT
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(151, 12, "Edit");

                                    rectangle(120,10,230,30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=120&&mousex()<=230&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);

                                    rectangle(120,10,230,30);
                                    outtextxy(151, 12, "Edit");




                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }

                                if(mousex()>=230&&mousex()<=350&&!ismouseclick(WM_LBUTTONDOWN))///THEME
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(265, 12, "Theme");

                                    rectangle(240, 10, 350, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=230&&mousex()<=350&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);
                                    bar(241, 30, 349, 33);
                                    rectangle(240, 10, 350, 30);
                                    outtextxy(265, 12, "Theme");




                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }

                                if(mousex()>=360&&mousex()<=470&&!ismouseclick(WM_LBUTTONDOWN))///COLOR
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(385, 12, "Color");

                                    rectangle(360, 10, 470, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=360&&mousex()<=470&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);

                                    bar(361, 30, 469, 33);
                                    rectangle(360, 10, 470, 30);
                                    outtextxy(385, 12, "Color");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }

                                if(mousex()>=480&&mousex()<=590&&!ismouseclick(WM_LBUTTONDOWN))///WINDOW
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(499, 12, "Window");

                                    rectangle(480, 10, 590, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=480&&mousex()<=590&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);

                                    bar(481, 30, 589, 33);
                                    rectangle(480, 10, 590, 30);
                                    outtextxy(499, 12, "Window");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }

                                if(mousex()>=600&&mousex()<=710&&!ismouseclick(WM_LBUTTONDOWN))///WRAP
                                {
                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(631, 12, "Wrap");

                                    rectangle(600, 10, 710, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=600&&mousex()<=710&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);

                                    bar(601, 30, 709, 33);
                                    rectangle(600, 10, 710, 30);
                                    outtextxy(631, 12, "Wrap");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }
                            }
                        }
                    }
                    if(ismouseclick(WM_LBUTTONDBLCLK)&&(y<110||y>140))///dublu click stanga
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        while(!ismouseclick(WM_LBUTTONUP));
                        clearmouseclick(WM_LBUTTONUP);

                        clearmouseclick(WM_LBUTTONDBLCLK);

                    }
                    else if((y<110||y>140))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        while(!ismouseclick(WM_LBUTTONUP));
                        clearmouseclick(WM_LBUTTONUP);
                    }
                }

                else if(x>=120&&x<=230 && fereastra_editati==false)///daca apas EDIT in timp ce ruleaza zona de scriere
                {
                    displayEditatiMenu();
                    fereastra_editati=true;
                    bool cct=false;
                    while(fereastra_editati)///EDIT+EDIT_MENU
                    {
                        if(kbhit())///daca apas o tasta
                        {
                            char temporar;
                            temporar=getch();
                            if(temporar==0||temporar==224)
                                temporar=getch();
                        }

                        if(ismouseclick(WM_LBUTTONDBLCLK))///dublu click stanga
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            while(!ismouseclick(WM_LBUTTONUP));
                            clearmouseclick(WM_LBUTTONUP);

                            clearmouseclick(WM_LBUTTONDBLCLK);

                        }

                        if(ismouseclick(WM_LBUTTONDOWN))///click stanga
                        {
                            x=mousex(),y=mousey();

                            if(x>=120&&x<=230)///EDIT_MENU
                            {
                                if(y>=30&&y<=70&&hex_view==false)///UNDO
                                {

                                    if(undo!=NULL)
                                    {


                                        nod *q;
                                        push_stiva(redo,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,text,pozitii);
                                        utilizare_undo_redo(undo,undo1,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,1);
                                    }


                                    x = 0;
                                    y = 65;

                                    if(active_page==0)
                                        active_page=1;
                                    else active_page=0;
                                    setactivepage(active_page);

                                    cleardevice();

                                    drawToolbar();
                                    sepLine();

                                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);
                                    dim_max_x=0;
                                    dim_max_y=65;
                                    pozitii.erase(pozitii.begin(), pozitii.end());

                                    for (int i = 0; i < text.size(); i++)
                                    {
                                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                                        {
                                            x=0;
                                            y+=21;
                                        }
                                        pozitii.push_back({x,y});
                                        dim_max_x=max(dim_max_x,x);
                                        dim_max_y=max(dim_max_y,y);

                                        if (text[i] == 10)
                                        {
                                            y = y + 21;
                                            x = 0;
                                        }
                                        else
                                        {
                                            pozitii[i].first = x;
                                            pozitii[i].second = y;
                                            //aux[0] = text[i];
                                            x = x + 12;
                                            //outtextxy(x, y, aux);
                                        }

                                        pozitii[i].first = x;
                                        pozitii[i].second = y;
                                        dim_max_x=max(dim_max_x,x);
                                        dim_max_y=max(dim_max_y,y);
                                    }

                                    x = 0;
                                    y = 65;
                                    if(pozitie!=0)
                                    {

                                        if(pozitii[pozitie-1].first>poz_max_x+12)
                                            while(pozitii[pozitie-1].first>poz_max_x+12)
                                            {
                                                poz_min_x+=12;
                                                poz_max_x+=12;

                                            }
                                        else if(pozitii[pozitie-1].first<poz_min_x)
                                            while(pozitii[pozitie-1].first<poz_min_x)
                                            {
                                                poz_min_x-=12;
                                                poz_max_x-=12;
                                            }


                                        if(pozitii[pozitie-1].second>poz_max_y)
                                            while(pozitii[pozitie-1].second>poz_max_y)
                                            {
                                                poz_min_y+=21;
                                                poz_max_y+=21;

                                            }
                                        else if(pozitii[pozitie-1].second<poz_min_y)
                                            while(pozitii[pozitie-1].second<poz_min_y)
                                            {
                                                poz_min_y-=21;
                                                poz_max_y-=21;
                                            }
                                    }
                                    else
                                    {
                                        poz_min_x=0;
                                        poz_max_x=dim_x;
                                        poz_min_y=65;
                                        poz_max_y=dim_y;
                                    }


                                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);
                                    for (int i = 0; i < text.size(); i++)
                                    {
                                        //pozitii.push_back({x,y});
                                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                                        {
                                            x=0;
                                            y+=21;
                                        }
                                        if (text[i] == 10)
                                        {
                                            y = y + 21;
                                            x = 0;
                                        }
                                        else
                                        {
                                            //pozitii[i].first = x;
                                            //pozitii[i].second = y;
                                            aux[0] = text[i];

                                            if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                                outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                                            x = x + 12;

                                        }

                                        //pozitii[i].first = x;
                                        //pozitii[i].second = y;
                                    }

                                    if (pozitie != 0)
                                    {

                                        x_caret = pozitii[pozitie-1].first-poz_min_x;
                                        y_caret=pozitii[pozitie-1].second-poz_min_y+65;


                                    }
                                    else
                                    {
                                        x_caret = 0;
                                        y_caret = 65;
                                    }
                                    contor_linie_coloana();
                                    scroll_oriz();
                                    scroll_vert();
                                    setvisualpage(active_page);
                                    setcolor(c_text);
                                    line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);

                                    fereastra_editati=false;
                                    fereastra_deschisa=false;
                                }
                                else if(y>=70&&y<=90&&hex_view==false)///REDO
                                {


                                    if(redo!=NULL)
                                    {
                                        nod*q;
                                        push_stiva(undo,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,text,pozitii);
                                        utilizare_undo_redo(redo,q,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,0);
                                    }

                                    x = 0;
                                    y = 65;

                                    if(active_page==0)
                                        active_page=1;
                                    else active_page=0;
                                    setactivepage(active_page);

                                    cleardevice();


                                    drawToolbar();
                                    sepLine();

                                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);
                                    dim_max_x=0;
                                    dim_max_y=65;
                                    pozitii.erase(pozitii.begin(), pozitii.end());

                                    for (int i = 0; i < text.size(); i++)
                                    {
                                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                                        {
                                            x=0;
                                            y+=21;
                                        }
                                        pozitii.push_back({x,y});
                                        dim_max_x=max(dim_max_x,x);
                                        dim_max_y=max(dim_max_y,y);

                                        if (text[i] == 10)
                                        {
                                            y = y + 21;
                                            x = 0;
                                        }
                                        else
                                        {
                                            pozitii[i].first = x;
                                            pozitii[i].second = y;
                                            //aux[0] = text[i];
                                            x = x + 12;
                                            //outtextxy(x, y, aux);
                                        }

                                        pozitii[i].first = x;
                                        pozitii[i].second = y;
                                        dim_max_x=max(dim_max_x,x);
                                        dim_max_y=max(dim_max_y,y);
                                    }

                                    x = 0;
                                    y = 65;
                                    if(pozitie!=0)
                                    {

                                        if(pozitii[pozitie-1].first>poz_max_x+12)
                                            while(pozitii[pozitie-1].first>poz_max_x+12)
                                            {
                                                poz_min_x+=12;
                                                poz_max_x+=12;

                                            }
                                        else if(pozitii[pozitie-1].first<poz_min_x)
                                            while(pozitii[pozitie-1].first<poz_min_x)
                                            {
                                                poz_min_x-=12;
                                                poz_max_x-=12;
                                            }


                                        if(pozitii[pozitie-1].second>poz_max_y)
                                            while(pozitii[pozitie-1].second>poz_max_y)
                                            {
                                                poz_min_y+=21;
                                                poz_max_y+=21;

                                            }
                                        else if(pozitii[pozitie-1].second<poz_min_y)
                                            while(pozitii[pozitie-1].second<poz_min_y)
                                            {
                                                poz_min_y-=21;
                                                poz_max_y-=21;
                                            }
                                    }
                                    else
                                    {
                                        poz_min_x=0;
                                        poz_max_x=dim_x;
                                        poz_min_y=65;
                                        poz_max_y=dim_y;
                                    }


                                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);
                                    for (int i = 0; i < text.size(); i++)
                                    {
                                        //pozitii.push_back({x,y});
                                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                                        {
                                            x=0;
                                            y+=21;
                                        }
                                        if (text[i] == 10)
                                        {
                                            y = y + 21;
                                            x = 0;
                                        }
                                        else
                                        {
                                            //pozitii[i].first = x;
                                            //pozitii[i].second = y;
                                            aux[0] = text[i];

                                            if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                                outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                                            x = x + 12;

                                        }

                                        //pozitii[i].first = x;
                                        //pozitii[i].second = y;
                                    }

                                    if (pozitie != 0)
                                    {

                                        x_caret = pozitii[pozitie-1].first-poz_min_x;
                                        y_caret=pozitii[pozitie-1].second-poz_min_y+65;


                                    }
                                    else
                                    {
                                        x_caret = 0;
                                        y_caret = 65;
                                    }
                                    contor_linie_coloana();
                                    scroll_oriz();
                                    scroll_vert();
                                    setvisualpage(active_page);
                                    setcolor(c_text);
                                    line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);


                                    fereastra_editati=false;
                                    fereastra_deschisa=false;
                                }

                                else if(y>=90&&y<=110&&text_selectat==true)///COPIATI
                                {
                                    ctrl_c_x('C',control_c,pozitie_i,pozitie);
                                    if(active_page==0)
                                        active_page=1;
                                    else active_page=0;
                                    setactivepage(active_page);


                                    cleardevice();


                                    drawToolbar();
                                    sepLine();

                                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);
                                    contor_linie_coloana();
                                    scroll_oriz();
                                    scroll_vert();
                                    doar_text();
                                    setvisualpage(active_page);
                                    setcolor(c_text);
                                    fereastra_editati=false;
                                    fereastra_deschisa=false;
                                    //text_selectat=false;
                                }

                                else if(y>=110&&y<=130&&hex_view==false)///LIPITI
                                {

                                    if(redo!=NULL)
                                    {
                                        nod *q=new nod;
                                        q=redo;
                                        while(q->ant!=NULL)
                                        {
                                            q=q->ant;
                                        }
                                        while(undo1!=NULL)
                                        {
                                            push_stiva(undo,undo1->x_caret,undo1->y_caret,undo1->x_caret_i,undo1->y_caret_i,undo1->pozitie,undo1->pozitie_i,undo1->text,undo1->pozitii);
                                            undo1=undo1->ant;
                                        }
                                        while(q!=NULL)
                                        {
                                            push_stiva(undo,q->x_caret,q->y_caret,q->x_caret_i,q->y_caret_i,q->pozitie,q->pozitie_i,q->text,q->pozitii);
                                            q=q->urm;
                                        }
                                        delete(undo1);
                                        undo1=NULL;
                                        delete(redo);
                                        redo=NULL;

                                    }
                                    push_stiva(undo,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,text,pozitii);



                                    if(text_selectat==true)
                                    {
                                        delete_selectat(pozitie_i,pozitie);
                                        text_selectat=false;
                                    }

                                    ctrl_v(control_c,pozitie_i,pozitie);

                                    /* x = 0;
                                     y = 65;

                                     if(active_page==0)
                                         active_page=1;
                                     else active_page=0;
                                     setactivepage(active_page);

                                     cleardevice();

                                     drawToolbar();
                                     sepLine();

                                     settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                     setbkcolor(c_bk);
                                     setcolor(c_text);
                                     dim_max_x=0;
                                     dim_max_y=65;
                                     echilibrare_pozitii();
                                     echilibrare_caret();
                                     pozitii.erase(pozitii.begin(), pozitii.end());
                                    cout<<pozitie<<' ';
                                     for (int i = 0; i < text.size(); i++)
                                     {
                                         if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                                         {
                                             x=0;
                                             y+=21;
                                         }
                                         pozitii.push_back({x,y});
                                         dim_max_x=max(dim_max_x,x);
                                         dim_max_y=max(dim_max_y,y);

                                         if (text[i] == 10)
                                         {
                                             y = y + 21;
                                             x = 0;
                                         }
                                         else
                                         {
                                             pozitii[i].first = x;
                                             pozitii[i].second = y;
                                             //aux[0] = text[i];
                                             x = x + 12;
                                             //outtextxy(x, y, aux);
                                         }

                                         pozitii[i].first = x;
                                         pozitii[i].second = y;
                                         dim_max_x=max(dim_max_x,x);
                                         dim_max_y=max(dim_max_y,y);
                                     }

                                     x = 0;
                                     y = 65;
                                     if(pozitie!=0)
                                     {

                                         if(pozitii[pozitie-1].first>poz_max_x+12)
                                             while(pozitii[pozitie-1].first>poz_max_x+12)
                                             {
                                                 poz_min_x+=12;
                                                 poz_max_x+=12;

                                             }
                                         else if(pozitii[pozitie-1].first<poz_min_x)
                                             while(pozitii[pozitie-1].first<poz_min_x)
                                             {
                                                 poz_min_x-=12;
                                                 poz_max_x-=12;
                                             }


                                         if(pozitii[pozitie-1].second>poz_max_y)
                                             while(pozitii[pozitie-1].second>poz_max_y)
                                             {
                                                 poz_min_y+=21;
                                                 poz_max_y+=21;

                                             }
                                         else if(pozitii[pozitie-1].second<poz_min_y)
                                             while(pozitii[pozitie-1].second<poz_min_y)
                                             {
                                                 poz_min_y-=21;
                                                 poz_max_y-=21;
                                             }
                                     }
                                     else
                                     {
                                         poz_min_x=0;
                                         poz_max_x=dim_x;
                                         poz_min_y=65;
                                         poz_max_y=dim_y;
                                     }


                                     settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                     setbkcolor(c_bk);
                                     setcolor(c_text);
                                     for (int i = 0; i < text.size(); i++)
                                     {
                                         if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                                         {
                                             x=0;
                                             y+=21;
                                         }
                                         //pozitii.push_back({x,y});

                                         if (text[i] == 10)
                                         {
                                             y = y + 21;
                                             x = 0;
                                         }
                                         else
                                         {
                                             //pozitii[i].first = x;
                                             //pozitii[i].second = y;
                                             aux[0] = text[i];

                                             if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                                 outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                                             x = x + 12;

                                         }

                                         //pozitii[i].first = x;
                                         //pozitii[i].second = y;
                                     }

                                     if (pozitie != 0)
                                     {

                                         x_caret = pozitii[pozitie-1].first-poz_min_x;
                                         y_caret=pozitii[pozitie-1].second-poz_min_y+65;


                                     }
                                     else
                                     {
                                         x_caret = 0;
                                         y_caret = 65;
                                     }
                                     contor_linie_coloana();
                                     scroll_oriz();
                                     scroll_vert();
                                     setvisualpage(active_page);
                                     setcolor(c_text);
                                    line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
                                    echilibrare_caret();*/
                                    doar_text();

                                    fereastra_editati=false;
                                    fereastra_deschisa=false;
                                }

                                else if(y>=130&&y<=150&&text_selectat==true&&hex_view==false)///DECUPATI
                                {


                                    if(redo!=NULL)
                                    {
                                        nod *q=new nod;
                                        q=redo;
                                        while(q->ant!=NULL)
                                        {
                                            q=q->ant;
                                        }
                                        while(undo1!=NULL)
                                        {
                                            push_stiva(undo,undo1->x_caret,undo1->y_caret,undo1->x_caret_i,undo1->y_caret_i,undo1->pozitie,undo1->pozitie_i,undo1->text,undo1->pozitii);
                                            undo1=undo1->ant;
                                        }
                                        while(q!=NULL)
                                        {
                                            push_stiva(undo,q->x_caret,q->y_caret,q->x_caret_i,q->y_caret_i,q->pozitie,q->pozitie_i,q->text,q->pozitii);
                                            q=q->urm;
                                        }
                                        delete(undo1);
                                        undo1=NULL;
                                        delete(redo);
                                        redo=NULL;

                                    }
                                    push_stiva(undo,x_caret,y_caret,x_caret_i,y_caret_i,pozitie,pozitie_i,text,pozitii);

                                    ctrl_c_x('X',control_c,pozitie_i,pozitie);

                                    x = 0;
                                    y = 65;

                                    if(active_page==0)
                                        active_page=1;
                                    else
                                        active_page=0;
                                    setactivepage(active_page);
                                    cleardevice();


                                    drawToolbar();
                                    sepLine();
                                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);


                                    dim_max_x=0;
                                    dim_max_y=65;

                                    pozitii.erase(pozitii.begin(), pozitii.end());

                                    for (int i = 0; i < text.size(); i++)
                                    {
                                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                                        {
                                            x=0;
                                            y+=21;
                                        }
                                        pozitii.push_back({x,y});
                                        dim_max_x=max(dim_max_x,x);
                                        dim_max_y=max(dim_max_y,y);

                                        if (text[i] == 10)
                                        {
                                            y = y + 21;
                                            x = 0;
                                        }
                                        else
                                        {
                                            pozitii[i].first = x;
                                            pozitii[i].second = y;
                                            //aux[0] = text[i];
                                            x = x + 12;
                                            //outtextxy(x, y, aux);
                                        }

                                        pozitii[i].first = x;
                                        pozitii[i].second = y;
                                        dim_max_x=max(dim_max_x,x);
                                        dim_max_y=max(dim_max_y,y);
                                    }

                                    x = 0;
                                    y = 65;
                                    if(pozitie!=0)
                                    {

                                        if(pozitii[pozitie-1].first>poz_max_x+12)
                                            while(pozitii[pozitie-1].first>poz_max_x+12)
                                            {
                                                poz_min_x+=12;
                                                poz_max_x+=12;

                                            }
                                        else if(pozitii[pozitie-1].first<poz_min_x)
                                            while(pozitii[pozitie-1].first<poz_min_x)
                                            {
                                                poz_min_x-=12;
                                                poz_max_x-=12;
                                            }


                                        if(pozitii[pozitie-1].second>poz_max_y)
                                            while(pozitii[pozitie-1].second>poz_max_y)
                                            {
                                                poz_min_y+=21;
                                                poz_max_y+=21;

                                            }
                                        else if(pozitii[pozitie-1].second<poz_min_y)
                                            while(pozitii[pozitie-1].second<poz_min_y)
                                            {
                                                poz_min_y-=21;
                                                poz_max_y-=21;
                                            }
                                    }
                                    else
                                    {
                                        poz_min_x=0;
                                        poz_max_x=dim_x;
                                        poz_min_y=65;
                                        poz_max_y=dim_y;
                                    }



                                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);
                                    for (int i = 0; i < text.size(); i++)
                                    {
                                        //pozitii.push_back({x,y});
                                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                                        {
                                            x=0;
                                            y+=21;
                                        }
                                        if (text[i] == 10)
                                        {
                                            y = y + 21;
                                            x = 0;
                                        }
                                        else
                                        {
                                            //pozitii[i].first = x;
                                            //pozitii[i].second = y;
                                            aux[0] = text[i];

                                            if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                                outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                                            x = x + 12;

                                        }

                                        //pozitii[i].first = x;
                                        //pozitii[i].second = y;
                                    }

                                    if (pozitie != 0)
                                    {

                                        x_caret = pozitii[pozitie-1].first-poz_min_x;
                                        y_caret=pozitii[pozitie-1].second-poz_min_y+65;


                                    }
                                    else
                                    {
                                        x_caret = 0;
                                        y_caret = 65;
                                    }
                                    contor_linie_coloana();
                                    scroll_oriz();
                                    scroll_vert();
                                    setvisualpage(active_page);
                                    setcolor(c_text);
                                    line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
                                    text_selectat=false;



                                    fereastra_editati=false;
                                    fereastra_deschisa=false;
                                    text_selectat=false;

                                }

                                else if(y>=150&&y<=170&&hex_view==false)///REPLACE
                                {

                                    clearmouseclick(WM_LBUTTONDOWN);
                                    cct=true;
                                    while(!ismouseclick(WM_LBUTTONUP));
                                    clearmouseclick(WM_LBUTTONUP);

                                    string cautare;
                                    string inlocuire;
                                    int cnt_ent=0;
                                    int act=true;
                                    int j=initwindow(800,100,"Replace",(getmaxwidth() - 800) / 2,(getmaxheight() - 100) / 2,false,false);
                                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);
// setfillstyle(COMPLEX_FONT, WHITE);
                                    floodfill(0, 0, c_bk);

                                    while(act)
                                    {
                                        setcolor(MAGENTA);
                                        outtextxy(0,0,"Find word: ");
                                        outtextxy(0,41,"Replace word: ");
                                        setcolor(c_text);
                                        c=getch();
                                        char *sir=&cautare[0],*sir1=&inlocuire[0];

                                        if(c==13||c==27)
                                        {
                                            cnt_ent++;
                                            if(cnt_ent>1)
                                            {


                                                act=false;
                                                closegraph(j);
                                                setcurrentwindow(mainWindowHandle);
                                            }
                                        }

                                        else  if ((c >= '0' && c <= '9' || c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == ' ' || strchr(caractere, c)) && c != 0)
                                        {
                                            cleardevice();
                                            if(cnt_ent==0)
                                            {
                                                cautare.push_back(c);
                                            }
                                            else
                                                inlocuire.push_back(c);

                                            outtextxy(textwidth("Find word: "),0,sir);
                                            outtextxy(textwidth("Replace word: "),41,sir1);

                                        }
                                        else if(c==8)
                                        {
                                            if(cnt_ent==0)
                                            {

                                                if(!cautare.empty())
                                                {
                                                    cleardevice();
                                                    cautare.pop_back();

                                                    outtextxy(textwidth("Find word: "),0,sir);

                                                }
                                            }
                                            else
                                            {
                                                if(!inlocuire.empty())
                                                {
                                                    cleardevice();
                                                    inlocuire.pop_back();
                                                    outtextxy(textwidth("Find word: "),0,sir);
                                                    outtextxy(textwidth("Replace word: "),41,sir1);
                                                }
                                            }
                                        }
                                    }
                                    //  cleardevice();

                                    if(active_page==0)
                                        active_page=1;
                                    else
                                        active_page=0;
                                    setactivepage(active_page);
                                    cleardevice();


                                    drawToolbar();
                                    sepLine();

                                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);



                                    if(!cautare.empty())
                                    {
                                        cct=true;
                                        replaceAll(text,cautare,inlocuire);
                                        pozitie=text.size();
                                    }

                                    x = 0;
                                    y = 65;
                                    setbkcolor(c_bk);
                                    setcolor(c_text);
                                    if(active_page==0)
                                        active_page=1;
                                    else active_page=0;
                                    setactivepage(active_page);
                                    cleardevice();
                                    drawToolbar();
                                    sepLine();

                                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);
                                    echilibrare_pozitii();
                                    dim_max_x=0;
                                    dim_max_y=65;
                                    pozitii.erase(pozitii.begin(), pozitii.end());

                                    for (int i = 0; i < text.size(); i++)
                                    {
                                        if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                                        {
                                            x=0;
                                            y+=21;
                                        }
                                        pozitii.push_back({x,y});

                                        if (text[i] == 10)
                                        {
                                            y = y + textheight(aux);
                                            x = 0;
                                        }
                                        else
                                        {
                                            pozitii[i].first = x;
                                            pozitii[i].second = y;
                                            aux[0] = text[i];
                                            if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                                outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                                            x = x + 12;

                                        }

                                        pozitii[i].first = x;
                                        pozitii[i].second = y;
                                    }

                                    if (pozitie != 0)
                                    {
                                        x_caret = pozitii[pozitie - 1].first;
                                        y_caret = pozitii[pozitie - 1].second;
                                    }
                                    else
                                    {
                                        x_caret = 0;
                                        y_caret = 65;
                                    }
                                    contor_linie_coloana();
                                    doar_text();
                                    contor_linie_coloana();
                                    scroll_oriz();
                                    scroll_vert();
                                    setvisualpage(active_page);
                                    setcolor(c_text);
                                    line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);

                                    fereastra_editati=false;
                                    fereastra_deschisa=false;
                                }

                                else if(y>=170&&y<=190)///FIND
                                {

                                    clearmouseclick(WM_LBUTTONDOWN);
                                    while(!ismouseclick(WM_LBUTTONUP));
                                    clearmouseclick(WM_LBUTTONUP);
                                    cct=true;
                                    string cautare;
                                    int act=true;
                                    int j=initwindow(800,50,"Find",(getmaxwidth() - 800) / 2,(getmaxheight() - 50) / 2,false,false);
                                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);
                                    cleardevice();

                                    textwidth("Find word: ");
                                    while(act)
                                    {
                                        setcolor(5);
                                        outtext("Find word: ");
                                        setcolor(c_text);
                                        c=getch();
                                        char *sir=&cautare[0];

                                        if(c==13||c==27)
                                        {
                                            act=false;
                                            closegraph(j);
                                            setcurrentwindow(mainWindowHandle);
                                        }

                                        else  if ((c >= '0' && c <= '9' || c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == ' ' || strchr(caractere, c)) && c != 0)
                                        {
                                            cleardevice();
                                            cautare.push_back(c);
                                            outtextxy(textwidth("Find word: "),0,sir);
                                            x+=12;
                                        }
                                        else if(c==8)
                                        {
                                            if(!cautare.empty())
                                            {
                                                cleardevice();
                                                cautare.pop_back();
                                                x-=12;
                                                outtextxy(textwidth("Find word: "),0,sir);

                                            }
                                        }
                                    }
                                    //  cleardevice();



                                    if(active_page==0)
                                        active_page=1;
                                    else
                                        active_page=0;
                                    setactivepage(active_page);
                                    cleardevice();


                                    drawToolbar();
                                    sepLine();

                                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);
                                    if(!cautare.empty())
                                    {
                                        cct=true;


                                        cnt=0;
                                        int hau=0;
                                        aparitii.erase(aparitii.begin(),aparitii.end());
                                        while(text.find(cautare,hau)!=string::npos)
                                        {
                                            aparitii.push_back((int)text.find(cautare,hau));
                                            hau=aparitii[cnt]+1;
                                            cnt++;
                                        }
                                        cnt=0;
                                        x = 0;
                                        y = 65;

                                        for (int i = 0; i < text.size(); i++)
                                        {

                                            if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                                            {
                                                x=0;
                                                y+=21;
                                            }
                                            if(cnt<aparitii.size())
                                            {
                                                if(i>=aparitii[cnt]&&(i<=aparitii[cnt]+cautare.size()-1))

                                                {

                                                    setbkcolor(LIGHTMAGENTA);
                                                    if(i==aparitii[cnt]+cautare.size()-1)
                                                    {
                                                        cnt++;
                                                    }

                                                }
                                                else setbkcolor(c_bk);
                                            }
                                            else setbkcolor(c_bk);
                                            if (text[i] == 10)
                                            {
                                                y = y + textheight(aux);
                                                x = -12;
                                            }

                                            if(text[i]=='\n')
                                                aux[0]=' ';
                                            else
                                                aux[0] = text[i];



                                            if(aux[0]!='\n')
                                                if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                                    outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                                            x = x + 12;
                                        }


                                        text_cautat=true;
                                        cautatt=cautare;
                                    }

                                    scroll_oriz();
                                    scroll_vert();
                                    setcolor(c_text);//text_selectat=true;
                                    if(text_cautat==false)
                                        doar_text();
                                    setbkcolor(c_bk);
                                    contor_linie_coloana();
                                    setvisualpage(active_page);


                                    fereastra_editati=false;
                                    fereastra_deschisa=false;
                                }

                                else if(y>=190&&y<=210)///SELECT
                                {

                                    clearmouseclick(WM_LBUTTONDOWN);
                                    while(!ismouseclick(WM_LBUTTONUP));
                                    clearmouseclick(WM_LBUTTONUP);
                                    cct=true;
                                    if(!text.empty())
                                    {

                                        string cautare;
                                        string inlocuire;
                                        int cnt_ent=0;
                                        int act=true;
                                        int j=initwindow(800,100,"Select",(getmaxwidth() - 800) / 2,(getmaxheight() - 100) / 2,false,false);
                                        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                        setbkcolor(c_bk);
                                        setcolor(c_text);
// setfillstyle(COMPLEX_FONT, WHITE);
                                        floodfill(0, 0, c_bk);

                                        while(act)
                                        {
                                            setcolor(MAGENTA);
                                            outtextxy(0,0,"Starting position: ");
                                            outtextxy(0,41,"End position: ");
                                            setcolor(c_text);
                                            c=getch();
                                            char *sir=&cautare[0],*sir1=&inlocuire[0];

                                            if(c==13||c==27)
                                            {
                                                cnt_ent++;
                                                if(cnt_ent>1)
                                                {


                                                    act=false;
                                                    closegraph(j);
                                                    setcurrentwindow(mainWindowHandle);
                                                }
                                            }

                                            else  if (c >= '0' && c <= '9')
                                            {
                                                cleardevice();
                                                if(cnt_ent==0)
                                                {
                                                    cautare.push_back(c);
                                                }
                                                else
                                                    inlocuire.push_back(c);

                                                outtextxy(textwidth("Starting position: "),0,sir);
                                                outtextxy(textwidth("End position: "),41,sir1);

                                            }
                                            else if(c==8)
                                            {
                                                if(cnt_ent==0)
                                                {

                                                    if(!cautare.empty())
                                                    {
                                                        cleardevice();
                                                        cautare.pop_back();

                                                        outtextxy(textwidth("Starting position: "),0,sir);

                                                    }
                                                }
                                                else
                                                {
                                                    if(!inlocuire.empty())
                                                    {
                                                        cleardevice();
                                                        inlocuire.pop_back();
                                                        outtextxy(textwidth("Starting position: "),0,sir);
                                                        outtextxy(textwidth("End position: "),41,sir1);
                                                    }
                                                }
                                            }
                                        }
                                        //  cleardevice();

                                        if(active_page==0)
                                            active_page=1;
                                        else
                                            active_page=0;
                                        setactivepage(active_page);
                                        cleardevice();


                                        drawToolbar();
                                        sepLine();
                                        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                        setbkcolor(c_bk);
                                        setcolor(c_text);

                                        int aux1=0;
                                        if(!cautare.empty()&&!inlocuire.empty())
                                        {
                                            for(int i=0; i<cautare.size(); i++)
                                                aux1=aux1*10+cautare[i]-48;

                                            pozitie_i=min((int)text.size(),aux1);

                                            aux1=0;
                                            for(int i=0; i<inlocuire.size(); i++)
                                                aux1=aux1*10+inlocuire[i]-48;

                                            pozitie=min((int)text.size(),aux1);


                                        }
                                        else if(!cautare.empty())
                                        {
                                            for(int i=0; i<cautare.size(); i++)
                                                aux1=aux1*10+cautare[i]-48;
                                            pozitie_i=min((int)text.size(),aux1);
                                            pozitie=0;
                                        }
                                        else if(!inlocuire.empty())
                                        {
                                            for(int i=0; i<inlocuire.size(); i++)
                                                aux1=aux1*10+inlocuire[i]-48;
                                            pozitie=min((int)text.size(),aux1);
                                            pozitie_i=0;
                                        }
                                        else pozitie_i=pozitie;
                                        x_caret_i=pozitii[pozitie_i].first;
                                        y_caret_i=pozitii[pozitie_i].second;


                                        x_caret=pozitii[pozitie].first;
                                        y_caret=pozitii[pozitie].second;

                                        if(active_page==0)
                                            active_page=1;
                                        else
                                            active_page=0;
                                        setactivepage(active_page);
                                        cleardevice();
                                        drawToolbar();

                                        sepLine();
                                        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                        setbkcolor(c_bk);
                                        setcolor(c_text);

                                        text_selectat=true;

                                        if(pozitie_i<pozitie&&!text.empty())
                                        {
                                            if(x+36==(getmaxx()-20)/36*36&&wrap_mode==true)
                                            {
                                                x=0;
                                                y+=21;
                                            }
                                            aux[1] = 0;
                                            x = 0;
                                            y = 65;

                                            for (int i = 0; i < text.size(); i++)
                                            {
                                                if(i==0&&x_caret_i==0&&pozitie_i==1)
                                                    setbkcolor(c_selectat);
                                                else if(i>=pozitie_i&&i<pozitie)
                                                    setbkcolor(c_selectat);
                                                else
                                                    setbkcolor(c_bk);

                                                if (text[i] == 10)
                                                {
                                                    y = y + textheight(aux);
                                                    x = -12;
                                                }

                                                if(text[i]=='\n')
                                                    aux[0]=' ';
                                                else
                                                    aux[0] = text[i];



                                                if(aux[0]!='\n')
                                                    if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                                        outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                                                x = x + 12;

                                            }
                                        }
                                        else if(!text.empty())
                                        {


                                            aux[1] = 0;
                                            x = 0;
                                            y = 65;

                                            for (int i = 0; i < text.size(); i++)
                                            {
                                                if(i==0&&x_caret==0&&pozitie==1)
                                                    setbkcolor(c_selectat);
                                                else if(i<pozitie_i&&i>=pozitie)
                                                    setbkcolor(c_selectat);
                                                else
                                                    setbkcolor(c_bk);

                                                if (text[i] == 10)
                                                {
                                                    y = y + textheight(aux);
                                                    x = -12;
                                                }

                                                if(text[i]=='\n')
                                                    aux[0]=' ';
                                                else
                                                    aux[0] = text[i];



                                                if(aux[0]!='\n')
                                                    if(x>=poz_min_x&&x<=poz_max_x&&y>=poz_min_y&&y<=poz_max_y)
                                                        outtextxy(x-poz_min_x+12, y-poz_min_y+65, aux);
                                                x = x + 12;

                                            }
                                        }

                                        setbkcolor(c_bk);
                                        if(cautare.empty())
                                            doar_text();
                                        contor_linie_coloana();
                                        scroll_oriz();
                                        scroll_vert();
                                        setvisualpage(active_page);
                                        doar_text();

                                    }
                                    else
                                    {

                                        doar_text();
                                        contor_linie_coloana();
                                        scroll_oriz();
                                        scroll_vert();
                                        setvisualpage(active_page);
                                    }
                                    fereastra_editati=false;
                                    fereastra_deschisa=false;

                                }

                                else if(y>=210&&y<=230)///HEX
                                {
                                    text_selectat=false;
                                    hex_view=true;
                                    c_text=GREEN;

                                    text=text_aux;
                                    binar();
                                    pozitie=text.size();
                                    text=text_binar;
                                    wrap_mode=true;
                                    poz_max_x=((getmaxx()-20)/36*36-36);
                                    dim_x=poz_max_x;
                                    poz_min_x=0;
                                    doar_text();
                                    fereastra_editati=false;
                                    fereastra_deschisa=false;




                                }

                                else if(y>=230&&y<=260)///NORMAL
                                {
                                    c_text=c_text_aux;
                                    hex_view=false;
                                    text_selectat=false;
                                    text=text_aux;
                                    wrap_mode=false;
                                    if(wrap_wrap==true)
                                        wrap_mode=true;
                                    doar_text();
                                    fereastra_editati=false;
                                    fereastra_deschisa=false;

                                    fereastra_editati=false;
                                    fereastra_deschisa=false;
                                    pozitie=text.size();
                                    doar_text();
                                }
                                else
                                {

                                    contor_linie_coloana();
                                    fereastra_editati=false;
                                    fereastra_deschisa=false;
                                    doar_text();
                                }
                            }
                            else
                            {
                                int lx=x,ly=y;
                                contor_linie_coloana();
                                fereastra_editati=false;
                                //fereastra_deschisa=false;
                                doar_text();
                                x=lx;
                                y=ly;

                            }
                        }
                        else///doar trec cu cursorul
                        {
                            if(mousex()>=120&&mousex()<=230&&mousey()>=10&&mousey()<=250)///EDIT
                            {

                                if(mousey()>=10&&mousey()<=30&&!ismouseclick(WM_LBUTTONDOWN))///EDIT
                                {

                                    setcolor(LIGHTRED);
                                    setbkcolor(c_bk);
                                    outtextxy(151, 12, "Edit");
                                    setfillstyle(SOLID_FILL,LIGHTGRAY);
                                    bar(121,30,229,33);
                                    rectangle(120,10,230,30);

                                    while (mousex()>=120&&mousex()<=230&&mousey()>=10&&mousey()<=30&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);


                                    outtextxy(151, 12, "Edit");


                                    bar(121,30,229,33);
                                    rectangle(120,10,230,30);
                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }

                                if(mousey()>=50&&mousey()<=70&&!ismouseclick(WM_LBUTTONDOWN))///UNDO
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(130, 50, "Undo");
                                    rectangle(121,50,229,70);

                                    while (mousex()>=120&&mousex()<=230&&mousey()>=50&&mousey()<=70&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(121,50,229,70);
                                    setcolor(5);
                                    outtextxy(130, 50, "Undo");
                                }

                                if(mousey()>70&&mousey()<=90&&!ismouseclick(WM_LBUTTONDOWN))///REDO
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(130, 70, "Redo");
                                    rectangle(121,70,229,90),usleep(100);

                                    while (mousex()>=120&&mousex()<=230&&mousey()>70&&mousey()<=90&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(121,70,229,90),usleep(100);
                                    setcolor(5);
                                    outtextxy(130, 70, "Redo");
                                }

                                if(mousey()>90&&mousey()<=110&&!ismouseclick(WM_LBUTTONDOWN))///COPY
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(130, 90, "Copy");
                                    rectangle(121,90,229,110),usleep(100);

                                    while (mousex()>=120&&mousex()<=230&&mousey()>90&&mousey()<=110&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(121,90,229,110),usleep(100);
                                    setcolor(5);
                                    outtextxy(130, 90, "Copy");
                                }


                                if(mousey()>110&&mousey()<=130&&!ismouseclick(WM_LBUTTONDOWN))///PASTE
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(130, 110, "Paste");
                                    rectangle(121,110,229,130),usleep(100);

                                    while (mousex()>=120&&mousex()<=230&&mousey()>110&&mousey()<=130&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(121,110,229,130),usleep(100);
                                    setcolor(5);
                                    outtextxy(130, 110, "Paste");
                                }


                                if(mousey()>130&&mousey()<=150&&!ismouseclick(WM_LBUTTONDOWN))///CUT
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(130, 130, "Cut");
                                    rectangle(121,130,229,150),usleep(100);

                                    while (mousex()>=120&&mousex()<=230&&mousey()>130&&mousey()<=150&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(121,130,229,150),usleep(100);
                                    setcolor(5);
                                    outtextxy(130, 130, "Cut");
                                }


                                if(mousey()>150&&mousey()<=170&&!ismouseclick(WM_LBUTTONDOWN))///REPLACE
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(130, 150, "Replace");
                                    rectangle(121,150,229,170),usleep(100);

                                    while (mousex()>=120&&mousex()<=230&&mousey()>150&&mousey()<=170&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(121,150,229,170),usleep(100);
                                    setcolor(5);
                                    outtextxy(130, 150, "Replace");
                                }


                                if(mousey()>170&&mousey()<=190&&!ismouseclick(WM_LBUTTONDOWN))///FIND
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(130, 170, "Find");
                                    rectangle(121,170,229,190),usleep(100);

                                    while (mousex()>=120&&mousex()<=230&&mousey()>170&&mousey()<=190&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(121,170,229,190),usleep(100);
                                    setcolor(5);
                                    outtextxy(130, 170, "Find");
                                }


                                if(mousey()>190&&mousey()<=210&&!ismouseclick(WM_LBUTTONDOWN))///SELECT
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(130, 190, "Select");
                                    rectangle(121,190,229,210),usleep(100);

                                    while(mousex()>=120&&mousex()<=230&&mousey()>190&&mousey()<=210&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(121,190,229,210),usleep(100);
                                    setcolor(5);
                                    outtextxy(130, 190, "Select");
                                }

                                else if(mousey()>=210&&mousey()<=230&&!ismouseclick(WM_LBUTTONDOWN)) ///HEX
                                {

                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(130, 210, "Hex view");
                                    rectangle(121,210,229,230),usleep(100);

                                    while (mousex()>=120&&mousex()<=230&&mousey()>=210&&mousey()<=230&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);
                                    setbkcolor(LIGHTGRAY);

                                    outtextxy(130, 210, "Hex view");
                                    setcolor(LIGHTGRAY);
                                    rectangle(121,210,229,230),usleep(100);
                                    setcolor(5);

                                }
                                else if(mousey()>=230&&mousey()<=250&&!ismouseclick(WM_LBUTTONDOWN)) ///NORMALbi
                                {

                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(130, 230, "Normal");
                                    rectangle(121,230,229,250),usleep(100);

                                    while (mousex()>=120&&mousex()<=230&&mousey()>=230&&mousey()<=250&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);

                                    setcolor(5);
                                    setbkcolor(LIGHTGRAY);

                                    outtextxy(130, 230, "Normal");
                                    setcolor(LIGHTGRAY);
                                    rectangle(121,230,229,250),usleep(100);
                                    setcolor(5);

                                }
                            }
                            if(mousey()>=10&&mousey()<=30)///sunt inca in Toolbar
                            {
                                if(mousex()>=10&&mousex()<=110&&!ismouseclick(WM_LBUTTONDOWN))///FILE
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(38, 12, "File");

                                    rectangle(10, 10, 110, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=10&&mousex()<=110&&!ismouseclick(WM_LBUTTONDOWN))
                                        usleep(100);
                                    setcolor(5);


                                    bar(11, 30, 109, 33);
                                    rectangle(10, 10, 110, 30);

                                    outtextxy(38, 12, "File");

                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }

                                if(mousex()>=230&&mousex()<=350&&!ismouseclick(WM_LBUTTONDOWN))///THEME
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(265, 12, "Theme");

                                    rectangle(240, 10, 350, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=230&&mousex()<=350&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);

                                    bar(241, 30, 349, 33);
                                    rectangle(240, 10, 350, 30);
                                    outtextxy(265, 12, "Theme");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }

                                if(mousex()>=360&&mousex()<=470&&!ismouseclick(WM_LBUTTONDOWN))///COLOR
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(385, 12, "Color");

                                    rectangle(360, 10, 470, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=360&&mousex()<=470&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);

                                    bar(361, 30, 469, 33);
                                    rectangle(360, 10, 470, 30);
                                    outtextxy(385, 12, "Color");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }

                                if(mousex()>=480&&mousex()<=590&&!ismouseclick(WM_LBUTTONDOWN))///WINDOW
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(499, 12, "Window");

                                    rectangle(480, 10, 590, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=480&&mousex()<=590&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);
                                    bar(481, 30, 589, 33);
                                    rectangle(480, 10, 590, 30);

                                    outtextxy(499, 12, "Window");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }

                                if(mousex()>=600&&mousex()<=710&&!ismouseclick(WM_LBUTTONDOWN))///WRAP
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(631, 12, "Wrap");

                                    rectangle(600, 10, 710, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=600&&mousex()<=710&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);

                                    bar(601, 30, 709, 33);
                                    rectangle(600, 10, 710, 30);
                                    outtextxy(631, 12, "Wrap");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }
                            }
                        }

                    }
                    if(ismouseclick(WM_LBUTTONDBLCLK)&&cct==false)
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        while(!ismouseclick(WM_LBUTTONUP));
                        clearmouseclick(WM_LBUTTONUP);

                        clearmouseclick(WM_LBUTTONDBLCLK);
                    }
                    else if(cct==false)
                    {

                        clearmouseclick(WM_LBUTTONDOWN);
                        while(!ismouseclick(WM_LBUTTONUP));
                        clearmouseclick(WM_LBUTTONUP);
                    }
                }

                else if(x>=240&&x<=350&&fereastra_tema==false)///daca apas THEME in timp ce ruleaza zona de scriere
                {
                    displayTemaMenu();

                    fereastra_tema=true;
                    while(fereastra_tema)
                    {
                        if(kbhit())
                        {
                            char temporar;
                            temporar=getch();
                            if(temporar==0||temporar==224)
                                temporar=getch();
                        }
                        if(ismouseclick(WM_LBUTTONDBLCLK))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            while(!ismouseclick(WM_LBUTTONUP));
                            clearmouseclick(WM_LBUTTONUP);

                            clearmouseclick(WM_LBUTTONDBLCLK);

                        }
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {


                            x=mousex(),y=mousey();


                            if(x>=240&&x<=350)
                            {


                                if(y>=30&&y<=70)///dark
                                {

                                    c_bk=BLACK;
                                    c_text=WHITE;
                                    c_selectat=8;
                                    setfillstyle(SOLID_FILL, c_bk);
                                    bar(0,0,getmaxx(),getmaxy());
                                    setbkcolor(c_bk);
                                    cleardevice();
                                    setactivepage(0);
                                    cleardevice();
                                    setactivepage(1);
                                    cleardevice();
                                    setvisualpage(1);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);
                                    if(active_page==0)
                                        active_page=1;
                                    else active_page=0;
                                    setactivepage(active_page);
                                    setfillstyle(SOLID_FILL, c_bk);
                                    bar(0,0,getmaxx(),getmaxy());
                                    setbkcolor(c_bk);
                                    cleardevice();
                                    setactivepage(0);
                                    cleardevice();
                                    setactivepage(1);
                                    cleardevice();
                                    setvisualpage(1);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);
                                    c_bk=BLACK;
                                    c_text=WHITE;
                                    c_selectat=8;
                                    setbkcolor(c_bk);
                                    cleardevice();
                                    setfillstyle(SOLID_FILL,c_bk);
                                    bar(0,0,getmaxx(),getmaxy());
                                    doar_text();
                                    contor_linie_coloana();
                                    fereastra_tema=false;
                                    fereastra_deschisa=false;

                                }
                                else if(y>=70&&y<=90)///light
                                {

                                    c_bk=WHITE;
                                    c_text=BLACK;
                                    c_selectat=LIGHTBLUE;

                                    cleardevice();
                                    setfillstyle(SOLID_FILL, c_bk);

                                    bar(0,0,getmaxx(),getmaxy());
                                    if(active_page==0)
                                        active_page=1;
                                    else
                                        active_page=0;
                                    cleardevice();
                                    setactivepage(active_page);
                                    cleardevice();

                                    setfillstyle(SOLID_FILL, c_bk);

                                    bar(0,0,getmaxx(),getmaxy());
                                    setvisualpage(active_page);


                                    fereastra_tema=false;
                                    doar_text();
                                    contor_linie_coloana();
                                    fereastra_deschisa=false;
                                }
                                else if(y>=90 && y<=110)///gray
                                {
                                    c_bk=LIGHTGRAY;
                                    c_text=14;
                                    c_selectat=BLACK;

                                    cleardevice();
                                    setfillstyle(SOLID_FILL, c_bk);

                                    bar(0,0,getmaxx(),getmaxy());
                                    if(active_page==0)
                                        active_page=1;
                                    else
                                        active_page=0;
                                    cleardevice();
                                    setactivepage(active_page);
                                    cleardevice();

                                    setfillstyle(SOLID_FILL, c_bk);

                                    bar(0,0,getmaxx(),getmaxy());
                                    setvisualpage(active_page);


                                    fereastra_tema=false;
                                    doar_text();
                                    contor_linie_coloana();
                                    fereastra_deschisa=false;
                                }
                                else
                                {
                                    fereastra_tema=false;
                                    fereastra_deschisa=false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                            }
                            else
                            {
                                int lx=x,ly=y;
                                contor_linie_coloana();
                                fereastra_tema=false;
                                //fereastra_deschisa=false;
                                doar_text();
                                x=lx;
                                y=ly;
                            }
                        }
                        else
                        {
                            if(mousex()>=240&&mousex()<=350&&mousey()>=10&&mousey()<=90)
                            {


                                if(mousey()>=10&&mousey()<=30&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(LIGHTRED);
                                    setbkcolor(c_bk);
                                    outtextxy(265, 12, "Theme");
                                    setfillstyle(SOLID_FILL,LIGHTGRAY);
                                    bar(241, 30, 349, 33);
                                    rectangle(240, 10, 350, 30);

                                    while (mousex()>=240&&mousex()<=350&&mousey()>=10&&mousey()<=30&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);


                                    outtextxy(265, 12, "Theme");


                                    bar(241, 30, 349, 33);
                                    rectangle(240, 10, 350, 30);
                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }



                                if(mousey()>=50&&mousey()<=70&&!ismouseclick(WM_LBUTTONDOWN))
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(250, 50, "Dark");
                                    rectangle(241,50,349,70),usleep(100);

                                    while (mousex()>=240&&mousex()<=350&&mousey()>=50&&mousey()<=70&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(241,50,349,70),usleep(100);
                                    setcolor(5);
                                    outtextxy(250, 50, "Dark");
                                }



                                if(mousey()>70&&mousey()<=90&&!ismouseclick(WM_LBUTTONDOWN))
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(250, 70, "Light");
                                    rectangle(241,70,349,90),usleep(100);


                                    while (mousex()>=240&&mousex()<=350&&mousey()>70&&mousey()<=90&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(241,70,349,90),usleep(100);

                                    setcolor(5);
                                    outtextxy(250, 70, "Light");
                                }


                            }

                            if(mousey()>=10&&mousey()<=30)
                            {
                                if(mousex()>=10&&mousex()<=110&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(38, 12, "File");

                                    rectangle(10, 10, 110, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=10&&mousex()<=110&&!ismouseclick(WM_LBUTTONDOWN))
                                        usleep(100);
                                    setcolor(5);

                                    bar(11, 30, 109, 33);
                                    rectangle(10, 10, 110, 30);
                                    outtextxy(38, 12, "File");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }


                                if(mousex()>=120&&mousex()<=230&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(151, 12, "Edit");

                                    rectangle(120,10,230,30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=120&&mousex()<=230&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);

                                    bar(121,30,229,33);
                                    rectangle(120,10,230,30);
                                    outtextxy(151, 12, "Edit");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }



                                if(mousex()>=360&&mousex()<=470&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(385, 12, "Color");

                                    rectangle(360, 10, 470, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=360&&mousex()<=470&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);
                                    bar(361, 30, 469, 33);
                                    rectangle(360, 10, 470, 30);

                                    outtextxy(385, 12, "Color");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }



                                if(mousex()>=480&&mousex()<=590&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(499, 12, "Window");

                                    rectangle(480, 10, 590, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=480&&mousex()<=590&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);

                                    bar(481, 30, 589, 33);
                                    rectangle(480, 10, 590, 30);
                                    outtextxy(499, 12, "Window");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }
                                if(mousex()>=600&&mousex()<=710&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(631, 12, "Wrap");

                                    rectangle(600, 10, 710, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=600&&mousex()<=710&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);

                                    bar(601, 30, 709, 33);
                                    rectangle(600, 10, 710, 30);
                                    outtextxy(631, 12, "Wrap");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }
                            }
                        }


                    }

                    if(ismouseclick(WM_LBUTTONDBLCLK))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        while(!ismouseclick(WM_LBUTTONUP));
                        clearmouseclick(WM_LBUTTONUP);

                        clearmouseclick(WM_LBUTTONDBLCLK);

                    }
                    else
                    {

                        clearmouseclick(WM_LBUTTONDOWN);
                        while(!ismouseclick(WM_LBUTTONUP));
                        clearmouseclick(WM_LBUTTONUP);
                    }
                }

                else if(x>=360 &&x<=470&&fereastra_culoare==false)///daca apas COLOR in timp ce ruleaza zona de scriere
                {
                    displayCuloareMenu();
                    fereastra_culoare=true;

                    while(fereastra_culoare)
                    {
                        if(kbhit())
                        {
                            char temporar;
                            temporar=getch();
                            if(temporar==0||temporar==224)
                                temporar=getch();
                        }
                        if(ismouseclick(WM_LBUTTONDBLCLK))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            while(!ismouseclick(WM_LBUTTONUP));
                            clearmouseclick(WM_LBUTTONUP);

                            clearmouseclick(WM_LBUTTONDBLCLK);

                        }

                        if(ismouseclick(WM_LBUTTONDOWN))
                        {


                            x=mousex(),y=mousey();
                            //clearmouseclick(WM_LBUTTONDOWN);
                            //clearmouseclick(WM_LBUTTONDOWN);

                            if(x>=360&&x<=470)
                            {
                                if(y>=30&&y<=70&&hex_view==false)//rosu
                                {
                                    c_text=RED;
                                    c_selectat=13;
                                    fereastra_culoare=false;
                                    fereastra_deschisa=false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                                else if(y>=70&&y<=90&hex_view==false)//negru
                                {
                                    c_text=CYAN;
                                    c_selectat=10;
                                    fereastra_culoare=false;
                                    fereastra_deschisa=false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                                else if(y>=90&&y<=120&hex_view==false)//maro
                                {
                                    c_text=BROWN;
                                    c_selectat=1;
                                    fereastra_culoare=false;
                                    fereastra_deschisa=false;
                                    doar_text();
                                    contor_linie_coloana();
                                }

                                else
                                {
                                    fereastra_culoare=false;
                                    fereastra_deschisa=false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                            }
                            else
                            {
                                int lx=x,ly=y;
                                contor_linie_coloana();
                                fereastra_culoare=false;
                                //fereastra_deschisa=false;
                                doar_text();
                                x=lx;
                                y=ly;
                            }
                            //clearmouseclick(WM_LBUTTONDOWN);
                            //while(!ismouseclick(WM_LBUTTONUP));
                            //clearmouseclick(WM_LBUTTONDOWN);
                        }
                        else
                        {
                            if(mousex()>=360&&mousex()<=470&&mousey()>=10&&mousey()<=110)
                            {


                                if(mousey()>=10&&mousey()<=30&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(LIGHTRED);
                                    setbkcolor(c_bk);
                                    outtextxy(385, 12, "Color");
                                    setfillstyle(SOLID_FILL,LIGHTGRAY);
                                    bar(361, 30, 469, 33);
                                    rectangle(360, 10, 470, 30);

                                    while (mousex()>=360&&mousex()<=470&&mousey()>=10&&mousey()<=30&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);


                                    outtextxy(385, 12, "Color");


                                    bar(361, 30, 469, 33);
                                    rectangle(360, 10, 470, 30);
                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }

                                if(mousey()>=50&&mousey()<=70&&!ismouseclick(WM_LBUTTONDOWN))
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(370, 50, "Red");
                                    rectangle(361,50,469,70),usleep(100);

                                    while (mousex()>=360&&mousex()<=470&&mousey()>=50&&mousey()<=70&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(361,50,469,70),usleep(100);
                                    setcolor(5);
                                    outtextxy(370, 50, "Red");
                                }


                                if(mousex()>=360&&mousex()<=470&&mousey()>70&&mousey()<=90&&!ismouseclick(WM_LBUTTONDOWN))
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(370, 70, "Cyan");
                                    rectangle(361,70,469,90),usleep(100);

                                    while (mousey()>70&&mousey()<=90&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(361,70,469,90),usleep(100);
                                    setcolor(5);
                                    outtextxy(370, 70, "Cyan");
                                }

                                if(mousex()>=360&&mousex()<=470&&mousey()>=90&&mousey()<=110&&!ismouseclick(WM_LBUTTONDOWN))
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(370, 90, "Brown");
                                    rectangle(361,90,469,110),usleep(100);

                                    while(mousey()>=90&&mousey()<=110&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(361,90,469,110),usleep(100);
                                    setcolor(5);
                                    outtextxy(370, 90, "Brown");
                                }


                            }


                            if(mousey()>=10&&mousey()<=30)
                            {
                                if(mousex()>=10&&mousex()<=110&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(38, 12, "File");

                                    rectangle(10, 10, 110, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=10&&mousex()<=110&&!ismouseclick(WM_LBUTTONDOWN))
                                        usleep(100);
                                    setcolor(5);
                                    bar(11, 30, 109, 33);
                                    rectangle(10, 10, 110, 30);

                                    outtextxy(38, 12, "File");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }


                                if(mousex()>=120&&mousex()<=230&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(151, 12, "Edit");

                                    rectangle(120,10,230,30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=120&&mousex()<=230&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);

                                    bar(121,30,229,33);
                                    rectangle(120,10,230,30);
                                    outtextxy(151, 12, "Edit");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }


                                if(mousex()>=230&&mousex()<=350&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(265, 12, "Theme");

                                    rectangle(240, 10, 350, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=230&&mousex()<=350&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);

                                    bar(241, 30, 349, 33);
                                    rectangle(240, 10, 350, 30);
                                    outtextxy(265, 12, "Theme");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }

                                if(mousex()>=480&&mousex()<=590&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(499, 12, "Window");

                                    rectangle(480, 10, 590, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=480&&mousex()<=590&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);

                                    bar(481, 30, 589, 33);
                                    rectangle(480, 10, 590, 30);
                                    outtextxy(499, 12, "Window");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }
                                if(mousex()>=600&&mousex()<=710&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(631, 12, "Wrap");

                                    rectangle(600, 10, 710, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=600&&mousex()<=710&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);

                                    bar(601, 30, 709, 33);
                                    rectangle(600, 10, 710, 30);
                                    outtextxy(631, 12, "Wrap");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }
                            }

                        }
                    }
                    //while(ismouseclick(WM_LBUTTONDOWN));

                    if(ismouseclick(WM_LBUTTONDBLCLK))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        while(!ismouseclick(WM_LBUTTONUP));
                        clearmouseclick(WM_LBUTTONUP);

                        clearmouseclick(WM_LBUTTONDBLCLK);

                    }
                    else
                    {

                        clearmouseclick(WM_LBUTTONDOWN);
                        while(!ismouseclick(WM_LBUTTONUP));
                        clearmouseclick(WM_LBUTTONUP);
                    }


                }

                else if(x>=480&&x<=590&&fereastra_dimensiune==false)///daca apas DIMENSIUNE in timp ce ruleaza zona de scriere
                {
                    displayDimensiuneMenu();
                    fereastra_dimensiune=true;
                    while(fereastra_dimensiune)
                    {
                        if(kbhit())
                        {
                            char temporar;
                            temporar=getch();
                            if(temporar==0||temporar==224)
                                temporar=getch();
                        }
                        if(ismouseclick(WM_LBUTTONDBLCLK))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            while(!ismouseclick(WM_LBUTTONUP));
                            clearmouseclick(WM_LBUTTONUP);

                            clearmouseclick(WM_LBUTTONDBLCLK);

                        }
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {


                            x=mousex(),y=mousey();

                            if(x>=480&&x<=590)
                            {


                                if(y>=30&&y<=70)//full
                                {


                                    clearmouseclick(WM_LBUTTONDOWN);
                                    while(!ismouseclick(WM_LBUTTONUP));
                                    clearmouseclick(WM_LBUTTONUP);
                                    closegraph();
                                    initializare_fereastra(getmaxwidth(),getmaxheight());
                                    if(wrap_mode==true)
                                    {
                                        poz_max_x=((getmaxx()-20)/36*36-36);
                                        dim_x=poz_max_x;
                                        poz_min_x=0;

                                    }
                                    echilibrare_pozitii();
                                    echilibrare_caret();

                                    setfillstyle(SOLID_FILL, c_bk);
                                    cleardevice();

                                    bar(0,0,getmaxx(),getmaxy());
//bar(0,40,getmaxx(),getmaxy());
                                    if(active_page==0)
                                        active_page=1;
                                    else
                                        active_page=0;
                                    setactivepage(active_page);

                                    setfillstyle(SOLID_FILL, c_bk);
                                    cleardevice();

                                    bar(0,0,getmaxx(),getmaxy());
//bar(0,40,getmaxx(),getmaxy());
                                    setvisualpage(active_page);


                                    fereastra_dimensiune=false;
                                    fereastra_deschisa=false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                                else if(y>=70&&y<=90)//medium
                                {

                                    clearmouseclick(WM_LBUTTONDOWN);
                                    while(!ismouseclick(WM_LBUTTONUP));
                                    clearmouseclick(WM_LBUTTONUP);
                                    closegraph();
                                    initializare_fereastra(getmaxwidth()/4*3,getmaxheight()/4*3+5);
                                    if(wrap_mode==true)
                                    {
                                        poz_max_x=((getmaxx()-20)/36*36-36);
                                        dim_x=poz_max_x;
                                        poz_min_x=0;

                                    }
                                    echilibrare_pozitii();
                                    echilibrare_caret();
                                    setfillstyle(SOLID_FILL, c_bk);
                                    cleardevice();

                                    bar(0,0,getmaxx(),getmaxy());
//bar(0,40,getmaxx(),getmaxy());
                                    if(active_page==0)
                                        active_page=1;
                                    else
                                        active_page=0;
                                    setactivepage(active_page);

                                    setfillstyle(SOLID_FILL, c_bk);
                                    cleardevice();

                                    bar(0,0,getmaxx(),getmaxy());
//bar(0,40,getmaxx(),getmaxy());
                                    setvisualpage(active_page);

                                    fereastra_dimensiune=false;
                                    fereastra_deschisa=false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                                else if(y>=90&&y<=120)//minim
                                {


                                    clearmouseclick(WM_LBUTTONDOWN);
                                    while(!ismouseclick(WM_LBUTTONUP));
                                    clearmouseclick(WM_LBUTTONUP);
                                    closegraph();
                                    initializare_fereastra(720,getmaxheight()/2);
                                    if(wrap_mode==true)
                                    {
                                        poz_max_x=((getmaxx()-20)/36*36-36);
                                        dim_x=poz_max_x;
                                        poz_min_x=0;

                                    }
                                    echilibrare_pozitii();
                                    echilibrare_caret();


                                    setfillstyle(SOLID_FILL, c_bk);
                                    cleardevice();

                                    bar(0,0,getmaxx(),getmaxy());
//bar(0,40,getmaxx(),getmaxy());
                                    if(active_page==0)
                                        active_page=1;
                                    else
                                        active_page=0;
                                    setactivepage(active_page);

                                    setfillstyle(SOLID_FILL, c_bk);
                                    cleardevice();

                                    bar(0,0,getmaxx(),getmaxy());
//bar(0,40,getmaxx(),getmaxy());
                                    setvisualpage(active_page);


                                    fereastra_dimensiune=false;
                                    fereastra_deschisa=false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                                else
                                {

                                    clearmouseclick(WM_LBUTTONDOWN);
                                    while(!ismouseclick(WM_LBUTTONUP));
                                    clearmouseclick(WM_LBUTTONUP);
                                    fereastra_dimensiune=false;
                                    fereastra_deschisa=false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                            }
                            else
                            {

                                clearmouseclick(WM_LBUTTONDOWN);
                                while(!ismouseclick(WM_LBUTTONUP));
                                clearmouseclick(WM_LBUTTONUP);
                                int lx=x,ly=y;
                                contor_linie_coloana();
                                fereastra_dimensiune=false;
                                //fereastra_deschisa=false;
                                doar_text();
                                x=lx;
                                y=ly;

                            }
                        }

                        else
                        {
                            if(mousex()>=480&&mousex()<=590&&mousey()>=10&&mousey()<=110)
                            {



                                if(mousey()>=10&&mousey()<=30&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(LIGHTRED);
                                    setbkcolor(c_bk);
                                    outtextxy(499, 12, "Window");
                                    setfillstyle(SOLID_FILL,LIGHTGRAY);
                                    bar(481, 30, 589, 33);
                                    rectangle(480, 10, 590, 30);

                                    while (mousex()>=480&&mousex()<=590&&mousey()>=10&&mousey()<=30&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);


                                    outtextxy(499, 12, "Window");


                                    bar(481, 30, 589, 33);
                                    rectangle(480, 10, 590, 30);
                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }
                                if(mousey()>=50&&mousey()<=70&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(490, 50, "Maximum");
                                    rectangle(481,50,589,70),usleep(100);

                                    while (mousex()>=480&&mousex()<=590&&mousey()>=50&&mousey()<=70&&!ismouseclick(WM_LBUTTONDOWN))
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(481,50,589,70),usleep(100);
                                    setcolor(5);
                                    outtextxy(490, 50, "Maximum");
                                }



                                if(mousey()>70&&mousey()<=90&&!ismouseclick(WM_LBUTTONDOWN))
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(490, 70, "Middle");
                                    rectangle(481,70,589,90),usleep(100);
                                    while (mousex()>=480&&mousex()<=590&&mousey()>70&&mousey()<=90&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(481,70,589,90),usleep(100);
                                    setcolor(5);
                                    outtextxy(490, 70, "Middle");
                                }


                                if(mousey()>=90&&mousey()<=110&&!ismouseclick(WM_LBUTTONDOWN))
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(490, 90, "Minimum");
                                    rectangle(481,90,589,110),usleep(100);

                                    while (mousex()>=480&&mousex()<=590&&mousey()>=90&&mousey()<=110&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(481,90,589,110),usleep(100);
                                    setcolor(5);
                                    outtextxy(490, 90, "Minimum");
                                }

                            }


                            if(mousey()>=10&&mousey()<=30)
                            {
                                if(mousex()>=10&&mousex()<=110&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(38, 12, "File");

                                    rectangle(10, 10, 110, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=10&&mousex()<=110&&!ismouseclick(WM_LBUTTONDOWN))
                                        usleep(100);
                                    setcolor(5);
                                    bar(11, 30, 109, 33);
                                    rectangle(10, 10, 110, 30);
                                    outtextxy(38, 12, "File");




                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }


                                if(mousex()>=120&&mousex()<=230&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(151, 12, "Edit");

                                    rectangle(120,10,230,30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=120&&mousex()<=230&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);
                                    bar(121,30,229,33);
                                    rectangle(120,10,230,30);

                                    outtextxy(151, 12, "Edit");




                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }


                                if(mousex()>=230&&mousex()<=350&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(265, 12, "Theme");

                                    rectangle(240, 10, 350, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=230&&mousex()<=350&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);
                                    bar(241, 30, 349, 33);
                                    rectangle(240, 10, 350, 30);
                                    outtextxy(265, 12, "Theme");




                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }


                                if(mousex()>=360&&mousex()<=470&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(385, 12, "Color");

                                    rectangle(360, 10, 470, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=360&&mousex()<=470&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);
                                    bar(361, 30, 469, 33);
                                    rectangle(360, 10, 470, 30);

                                    outtextxy(385, 12, "Color");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }



                                if(mousex()>=600&&mousex()<=710&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(631, 12, "Wrap");

                                    rectangle(600, 10, 710, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=600&&mousex()<=710&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);
                                    bar(601, 30, 709, 33);
                                    rectangle(600, 10, 710, 30);

                                    outtextxy(631, 12, "Wrap");



                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }
                            }
                        }

                    }


                }

                else if(x>=600&&x<=710&&fereastra_wrap==false)///daca apas WRAP in timp ce ruleaza zona de scriere
                {

                    displayWrapMenu();
                    fereastra_wrap=true;
                    while(fereastra_wrap)
                    {
                        if(kbhit())
                        {
                            char temporar;
                            temporar=getch();
                            if(temporar==0||temporar==224)
                                temporar=getch();
                        }
                        if(ismouseclick(WM_LBUTTONDBLCLK))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            while(!ismouseclick(WM_LBUTTONUP));
                            clearmouseclick(WM_LBUTTONUP);

                            clearmouseclick(WM_LBUTTONDBLCLK);

                        }
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {


                            x=mousex(),y=mousey();

                            if(x>=600&&x<=710)
                            {


                                if(y>=30&&y<=70)//on
                                {

                                    wrap_mode=true;
                                    wrap_wrap=true;
                                    poz_max_x=((getmaxx()-20)/36*36-36);
                                    dim_x=poz_max_x;
                                    poz_min_x=0;

                                    fereastra_wrap=false;
                                    fereastra_deschisa=false;
                                    doar_text();
                                    contor_linie_coloana();

                                }
                                else if(y>=70&&y<=100)//off
                                {
                                    wrap_mode=false;
                                    wrap_wrap=false;
                                    fereastra_wrap=false;
                                    if(hex_view==true)
                                    {

                                        poz_max_x=((getmaxx()-20)/36*36-36);
                                        dim_x=poz_max_x;
                                        poz_min_x=0;
                                        wrap_mode=true;
                                    }

                                    fereastra_deschisa=false;
                                    doar_text();
                                    contor_linie_coloana();
                                }

                                else
                                {
                                    fereastra_wrap=false;
                                    fereastra_deschisa=false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                            }
                            else
                            {
                                int lx=x,ly=y;
                                contor_linie_coloana();
                                fereastra_wrap=false;
                                //fereastra_deschisa=false;
                                doar_text();
                                x=lx;
                                y=ly;
                            }

                        }
                        else
                        {
                            if(mousex()>=600&&mousex()<=710&&mousey()>=10&&mousey()<=110)
                            {



                                if(mousey()>=10&&mousey()<=30&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(LIGHTRED);
                                    setbkcolor(c_bk);
                                    outtextxy(631, 12, "Wrap");
                                    setfillstyle(SOLID_FILL,LIGHTGRAY);
                                    bar(601, 30, 709, 33);
                                    rectangle(600, 10, 710, 30);

                                    while (mousex()>=600&&mousex()<=710&&mousey()>=10&&mousey()<=30&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);


                                    outtextxy(631, 12, "Wrap");


                                    bar(601, 30, 709, 33);
                                    rectangle(600, 10, 710, 30);
                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }


                                if(mousey()>=50&&mousey()<=70&&!ismouseclick(WM_LBUTTONDOWN))
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(610, 50, "On");
                                    rectangle(601,50,709,70),usleep(100);

                                    while (mousex()>=600&&mousex()<=710&&mousey()>=50&&mousey()<=70&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(601,50,709,70),usleep(100);
                                    setcolor(5);
                                    outtextxy(610, 50, "On");
                                }




                                if(mousey()>70&&mousey()<=90&&!ismouseclick(WM_LBUTTONDOWN))
                                {
                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    outtextxy(610, 70, "Off");
                                    rectangle(601,70,709,90),usleep(100);

                                    while(mousex()>=600&&mousex()<=710&&mousey()>70&&mousey()<=90&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(LIGHTGRAY);
                                    rectangle(601,70,709,90),usleep(100);
                                    setcolor(5);
                                    outtextxy(610, 70, "Off");
                                }


                            }

                            if(mousey()>=10&&mousey()<=30)
                            {
                                if(mousex()>=10&&mousex()<=110&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(38, 12, "File");

                                    rectangle(10, 10, 110, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=10&&mousex()<=110&&!ismouseclick(WM_LBUTTONDOWN))
                                        usleep(100);
                                    setcolor(5);
                                    bar(11, 30, 109, 33);
                                    rectangle(10, 10, 110, 30);
                                    outtextxy(38, 12, "File");




                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }


                                if(mousex()>=120&&mousex()<=230&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(151, 12, "Edit");

                                    rectangle(120,10,230,30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=120&&mousex()<=230&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);
                                    bar(121,30,229,33);
                                    rectangle(120,10,230,30);

                                    outtextxy(151, 12, "Edit");




                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }


                                if(mousex()>=230&&mousex()<=350&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(265, 12, "Theme");

                                    rectangle(240, 10, 350, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=230&&mousex()<=350&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);
                                    setcolor(5);
                                    bar(241, 30, 349, 33);
                                    rectangle(240, 10, 350, 30);
                                    outtextxy(265, 12, "Theme");




                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }


                                if(mousex()>=360&&mousex()<=470&&!ismouseclick(WM_LBUTTONDOWN))
                                {

                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(385, 12, "Color");
                                    rectangle(360, 10, 470, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=360&&mousex()<=470&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);

                                    setcolor(5);
                                    bar(361, 30, 469, 33);
                                    rectangle(360, 10, 470, 30);
                                    outtextxy(385, 12, "Color");
                                    setfillstyle(SOLID_FILL,c_bk);

                                }

                                if(mousex()>=480&&mousex()<=590&&!ismouseclick(WM_LBUTTONDOWN))
                                {
                                    setcolor(GREEN);
                                    setbkcolor(c_bk);
                                    outtextxy(499, 12, "Window");
                                    rectangle(480, 10, 590, 30);

                                    while (mousey()>=10&&mousey()<=30&&mousex()>=480&&mousex()<=590&&!ismouseclick(WM_LBUTTONDOWN)&&!kbhit())
                                        usleep(100);

                                    setcolor(5);
                                    bar(481, 30, 589, 33);
                                    rectangle(480, 10, 590, 30);
                                    outtextxy(499, 12, "Window");




                                    //rectangle(121,29,229,28);
                                    setfillstyle(SOLID_FILL,c_bk);

                                }
                            }

                        }

                    }
                    if(ismouseclick(WM_LBUTTONDBLCLK))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        while(!ismouseclick(WM_LBUTTONUP));
                        clearmouseclick(WM_LBUTTONUP);

                        clearmouseclick(WM_LBUTTONDBLCLK);

                    }
                    else
                    {

                        clearmouseclick(WM_LBUTTONDOWN);
                        while(!ismouseclick(WM_LBUTTONUP));
                        clearmouseclick(WM_LBUTTONUP);
                    }
                }
                else///altfel
                {
                    fereastra_fisier=false;
                    fereastra_deschisa=false;
                    fereastra_editati=false;
                    fereastra_tema=false;
                    fereastra_culoare=false;
                    fereastra_dimensiune=false;
                    fereastra_wrap=false;


                    contor_linie_coloana();

                    doar_text();

                }

            }

        }
        inchidere_fereastra=false;;


    }
}

void Brick(int x, int y, char Color)
{
    int utri[6] = { x,y,  x+20,y,  x,y+20 };
    int ltri[6] = { x+20,y+20,  x+20,y,  x,y+20 };
    switch(Color)
    {
    case BLUE:
        setcolor(BLUEBR);
        setfillstyle(1,BLUEBR);
        fillpoly(3, utri);
        setcolor(BLUEDR);
        setfillstyle(1,BLUEDR);
        fillpoly(3, ltri);
        setcolor(BLUE);
        setfillstyle(1,BLUE);
        bar(x+5, y+5, x+15, y+15);
        break;
    case RED:
        setcolor(REDBR);
        setfillstyle(1,REDBR);
        fillpoly(3, utri);
        setcolor(REDDR);
        setfillstyle(1,REDDR);
        fillpoly(3, ltri);
        setcolor(RED);
        setfillstyle(1,RED);
        bar(x+5, y+5, x+15, y+15);
        break;
    case GREEN:
        setcolor(GREENBR);
        setfillstyle(1,GREENBR);
        fillpoly(3, utri);
        setcolor(GREENDR);
        setfillstyle(1,GREENDR);
        fillpoly(3, ltri);
        setcolor(GREEN);
        setfillstyle(1,GREEN);
        bar(x+5, y+5, x+15, y+15);
        break;
    case PURPLE:
        setcolor(PURPLEBR);
        setfillstyle(1,PURPLEBR);
        fillpoly(3, utri);
        setcolor(PURPLEDR);
        setfillstyle(1,PURPLEDR);
        fillpoly(3, ltri);
        setcolor(PURPLE);
        setfillstyle(1,PURPLE);
        bar(x+5, y+5, x+15, y+15);
        break;
    case YELLOW:
        setcolor(YELLOWBR);
        setfillstyle(1,YELLOWBR);
        fillpoly(3, utri);
        setcolor(YELLOWDR);
        setfillstyle(1,YELLOWDR);
        fillpoly(3, ltri);
        setcolor(YELLOW);
        setfillstyle(1,YELLOW);
        bar(x+5, y+5, x+15, y+15);
        break;
    }
}

void InitPalette()
{
    //Blue Colors
    setpalette(BLUE,1);  //Normal
    setpalette(BLUEDR,8);  //Dark
    setpalette(BLUEBR,9);  //Bright
    //Red Colors
    setpalette(RED,4);  //Normal
    setpalette(REDDR,32);  //Dark
    setpalette(REDBR,36);  //Bright
    //Green Colors
    setpalette(GREEN,2);  //Normal
    setpalette(GREENDR,16);  //Dark
    setpalette(GREENBR,18);  //Bright
    //Purple Colors
    setpalette(PURPLE,13);  //Normal
    setpalette(PURPLEDR,33);  //Dark
    setpalette(PURPLEBR,61);  //Bright
    //Yellow Colors
    setpalette(YELLOW,6);  //Normal
    setpalette(YELLOWDR,48);  //Dark
    setpalette(YELLOWBR,62);  //Bright
}

void GetImages()
{

    Brick(100,100,BLUE);
    Brick(130,100,RED);
    Brick(160,100,GREEN);
    Brick(190,100,YELLOW);
    Brick(220,100,PURPLE);

    bmpBlueBrick   = malloc(imagesize(0,0,20,20));
    bmpRedBrick    = malloc(imagesize(0,0,20,20));
    bmpGreenBrick  = malloc(imagesize(0,0,20,20));
    bmpYellowBrick = malloc(imagesize(0,0,20,20));
    bmpPurpleBrick = malloc(imagesize(0,0,20,20));
    bmpBlankBrick  = malloc(imagesize(0,0,20,20));
    bmpScore       = malloc(imagesize(501,51,607,69));
    bmpSpeed       = malloc(imagesize(501,51,607,69));
    bmpLevel       = malloc(imagesize(501,51,607,69));
    bmpLinesCleared= malloc(imagesize(501,51,607,69));
    bmpScreen      = malloc(imagesize(0,0,640,480));

    getimage(100,100,120,120,bmpBlueBrick);
    getimage(130,100,150,120,bmpRedBrick);
    getimage(160,100,180,120,bmpGreenBrick);
    getimage(190,100,210,120,bmpYellowBrick);
    getimage(220,100,240,120,bmpPurpleBrick);
    getimage(0,0,20,20,bmpBlankBrick);
    getimage(501,51,607,69,bmpScore);
    getimage(501,51,607,69,bmpSpeed);
    getimage(501,51,607,69,bmpLevel);
    getimage(501,51,607,69,bmpLinesCleared);
}

void InitScreenLayout()
{
    for(int x=0; x<COLS; x++)
        for(int y=0; y<ROWS; y++)
        {
            ScreenLayout[x][y] = BLANK;
            PreviousScreenLayout[x][y] = BLANK;
            ScreenBackgroundLayout[x][y] = BLANK;
        }
}

void DisplayInterface()
{
    settextstyle(BOLD_FONT,HORIZ_DIR,0);

    setcolor(5);
    rectangle(158,28,476,450);
    outtextxy(510,280,"Next:");
    rectangle(478+5,255-20,620,450);
    outtextxy(20,265-20,"KEYS:");
    rectangle(10,255-20,150,382+6+18*3+18+10-20);

    settextstyle(BOLD_FONT,HORIZ_DIR,1);
    setcolor(5);
    outtextxy(20,310-20,"Left   :");
    setcolor(LIGHTRED);
    outtextxy(20,322+6-20,"Left arrow");
    setcolor(5);
    outtextxy(20,330+18-20,"Right  :");
    setcolor(LIGHTRED);
    outtextxy(20,342+6+18-20,"Right arrow");
    setcolor(5);
    outtextxy(20,350+18+18-20,"Rotate :");
    setcolor(LIGHTRED);
    outtextxy(20,362+6+18+18-20,"Up arrow");
    setcolor(5);

    outtextxy(20,370+18*3-20,"Drop   :");
    setcolor(LIGHTRED);
    outtextxy(20,382+6+18*3-20,"Down arrow");
    setcolor(5);


}

void AssignShape(int Shape, int Color)
{
    int i,j;
    CurrentShape = Shape;
    switch(Shape)
    {
    case SHAPE_I:
        for(i=0; i<4; i++)
            for(j=0; j<4; j++)
                BlockMatrix[j][i] = ShapeI[i][j]*Color;
        break;
    case SHAPE_T:
        for(i=0; i<4; i++)
            for(j=0; j<4; j++)
                BlockMatrix[j][i] = ShapeT[i][j]*Color;
        break;
    case SHAPE_L:
        for(i=0; i<4; i++)
            for(j=0; j<4; j++)
                BlockMatrix[j][i] = ShapeL[i][j]*Color;
        break;
    case SHAPE_L2:
        for(i=0; i<4; i++)
            for(j=0; j<4; j++)
                BlockMatrix[j][i] = ShapeL2[i][j]*Color;
        break;
    case SHAPE_O:
        for(i=0; i<4; i++)
            for(j=0; j<4; j++)
                BlockMatrix[j][i] = ShapeO[i][j]*Color;
        break;
    case SHAPE_S:
        for(i=0; i<4; i++)
            for(j=0; j<4; j++)
                BlockMatrix[j][i] = ShapeS[i][j]*Color;
        break;
    case SHAPE_S2:
        for(i=0; i<4; i++)
            for(j=0; j<4; j++)
                BlockMatrix[j][i] = ShapeS2[i][j]*Color;
        break;
    default:
        break;
    }
}

int GetRandomColor()
{
    int Color = rand() % 5;
    switch(Color)
    {
    case 0 :
        return BLUE;
    case 1:
        return RED;
    case 2:
        return GREEN;
    case 3:
        return YELLOW;
    case 4:
        return PURPLE;
    }
    return 0;
}

int GetRandomShape()
{
    int Shape = rand() % 7;
    switch(Shape)
    {
    case 0 :
        return SHAPE_I;
    case 1:
        return SHAPE_L;
    case 2:
        return SHAPE_T;
    case 3:
        return SHAPE_O;
    case 4:
        return SHAPE_S;
    case 5:
        return SHAPE_S2;
    case 6:
        return SHAPE_L2;
    }
    return 0;
}

int MoveBlock(int Direction)
{
    switch(Direction)
    {
    case LEFT:
        if(DetectCollision(LEFT))
            return 1;
        DisplayBlock(--BlockX, BlockY);
        break;
    case RIGHT:
        if(DetectCollision(RIGHT))
            return 1;
        DisplayBlock(++BlockX, BlockY);
        break;
    case DOWN:
        if(DetectCollision(DOWN))
        {
            GetNextBlock();
            return 1;
        }
        DisplayBlock(BlockX, ++BlockY);
        break;
    case REFRESH:
        DisplayBlock(BlockX, BlockY);
        break;
    }
    return 0;
}

void RotateBlock()
{
    // Code to rotate the falling block
    int TempBlockMatrix[4][4];
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            TempBlockMatrix[i][j] = BlockMatrix[i][j];
    switch(CurrentShape)
    {
    case SHAPE_O:
        return;
    case SHAPE_L:
    case SHAPE_L2:
    case SHAPE_S:
    case SHAPE_S2:
    case SHAPE_T:
        BlockMatrix[0][0] = TempBlockMatrix[2][0];
        BlockMatrix[0][2] = TempBlockMatrix[0][0];
        BlockMatrix[2][2] = TempBlockMatrix[0][2];
        BlockMatrix[2][0] = TempBlockMatrix[2][2];

        BlockMatrix[0][1] = TempBlockMatrix[1][0];
        BlockMatrix[1][2] = TempBlockMatrix[0][1];
        BlockMatrix[2][1] = TempBlockMatrix[1][2];
        BlockMatrix[1][0] = TempBlockMatrix[2][1];
        break;
    case SHAPE_I:
        BlockMatrix[0][1] = TempBlockMatrix[1][0];
        BlockMatrix[1][0] = TempBlockMatrix[0][1];

        BlockMatrix[1][2] = TempBlockMatrix[2][1];
        BlockMatrix[2][1] = TempBlockMatrix[1][2];

        BlockMatrix[1][3] = TempBlockMatrix[3][1];
        BlockMatrix[3][1] = TempBlockMatrix[1][3];
        break;
    }
    if(DetectCollision(REFRESH))
    {
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                BlockMatrix[i][j] = TempBlockMatrix[i][j];
        return;
    }
    MoveBlock(REFRESH);
}

void DisplayBlock(int x, int y)
{
    int i, j;
    for(i=0; i<ROWS; i++)
        for(j=0; j<COLS; j++)
            ScreenLayout[j][i] = ScreenBackgroundLayout[j][i];

    for(i=0; i<4; i++)
    {
        if((x+i)<0 || (x+i) > COLS)
            continue;
        for(j=0; j<4; j++)
        {
            if((y+j)>ROWS)
                continue;
            if(BlockMatrix[i][j] == 0)
                continue;
            ScreenLayout[x+i][y+j] = BlockMatrix[i][j];
        }
    }
    UpdateScreen();
}

int DetectCollision(int Direction)
{
    int x,y;
    int Bx=BlockX;
    int By=BlockY;
    switch(Direction)
    {
    case LEFT:
        --Bx;
        break;
    case RIGHT:
        ++Bx;
        break;
    case DOWN:
        By++;
        break;
    default:
        break;
    }

    // Left Boundry check
    if(Bx < 0)
    {
        for(x=0; (x+Bx)<0; x++)
            for(y=0; y<4; y++)
                if(BlockMatrix[x][y]!=0)
                    return 1;
    }
    // Right Boundry check
    if(Bx > COLS-4)
    {
        for(x=Bx+3; x>=COLS; x--)
            for(y=0; y<4; y++)
                if(BlockMatrix[x-Bx][y]!=0)
                    return 1;
    }
    // Bottom boundry check
    for(x=0; x<4; x++)
        for(y=3; y>=0; y--)
        {
            if((ScreenBackgroundLayout[Bx+x][By+y]!=BLANK &&
                    BlockMatrix[x][y]!=BLANK) ||
                    ((By+y)>=ROWS && BlockMatrix[x][y]!=BLANK))
                return 1;
        }

    return 0;
}

void GetNextBlock()
{
    for(int x=0; x<4; x++)
        for(int y=0; y<4; y++)
            if(BlockMatrix[x][y] != BLANK)
                ScreenBackgroundLayout[BlockX+x][BlockY+y] = BlockMatrix[x][y];
    CheckForLine();
    AssignShape(NextShape, NextColor);
    NextShape = GetRandomShape();
    NextColor = GetRandomColor();
    DisplayNextShape();
    BlockX = 7;
    BlockY = 0;
    if(MoveBlock(LEFT))
    {
        GameOver=1;
        setcolor(RED);
        settextstyle(BOLD_FONT,HORIZ_DIR,9);
        setfillstyle(SOLID_FILL,c_bk);
        bar((getmaxx()-textwidth("GAME OVER!"))/2-50,(getmaxy()-textheight("GAME OVER!"))/2-10,(getmaxx()-textwidth("GAME OVER!"))/2+50+textwidth("GAME OVER!"),(getmaxy()-textheight("GAME OVER!"))/2+50+textheight("GAME OVER!"));
        rectangle((getmaxx()-textwidth("GAME OVER!"))/2-50,(getmaxy()-textheight("GAME OVER!"))/2-10,(getmaxx()-textwidth("GAME OVER!"))/2+50+textwidth("GAME OVER!"),(getmaxy()-textheight("GAME OVER!"))/2+50+textheight("GAME OVER!"));


        outtextxy((getmaxx()-textwidth("GAME OVER!"))/2,(getmaxy()-textheight("GAME OVER!"))/2,"GAME OVER!");

        int mm1=textheight("A");
        settextstyle(BOLD_FONT,HORIZ_DIR,0);
        outtextxy((getmaxx()-textwidth("Press any key to return menu"))/2,(getmaxy()-mm1)/2+mm1,"Press any key to return menu");
        getch();
    }
}

void DisplayNextShape()
{
    int NextTop = 340;
    int NextLeft = 520;
    int TempMatrix[4][4];
    int i,j;

    switch(NextShape)
    {
    case SHAPE_I:
        for(i=0; i<4; i++)
            for(j=0; j<4; j++)
                TempMatrix[j][i] = ShapeI[i][j]*NextColor;
        break;
    case SHAPE_T:
        for(i=0; i<4; i++)
            for(j=0; j<4; j++)
                TempMatrix[j][i] = ShapeT[i][j]*NextColor;
        break;
    case SHAPE_L:
        for(i=0; i<4; i++)
            for(j=0; j<4; j++)
                TempMatrix[j][i] = ShapeL[i][j]*NextColor;
        break;
    case SHAPE_L2:
        for(i=0; i<4; i++)
            for(j=0; j<4; j++)
                TempMatrix[j][i] = ShapeL2[i][j]*NextColor;
        break;
    case SHAPE_O:
        for(i=0; i<4; i++)
            for(j=0; j<4; j++)
                TempMatrix[j][i] = ShapeO[i][j]*NextColor;
        break;
    case SHAPE_S:
        for(i=0; i<4; i++)
            for(j=0; j<4; j++)
                TempMatrix[j][i] = ShapeS[i][j]*NextColor;
        break;
    case SHAPE_S2:
        for(i=0; i<4; i++)
            for(j=0; j<4; j++)
                TempMatrix[j][i] = ShapeS2[i][j]*NextColor;
        break;
    default:
        break;
    }

    for(int x=0; x<4; x++)
        for(int y=0; y<4; y++)
        {
            switch(TempMatrix[x][y])
            {
            case BLUE:
                putimage(NextLeft+x*21, NextTop+y*21, bmpBlueBrick, 0);
                break;
            case RED:
                putimage(NextLeft+x*21, NextTop+y*21, bmpRedBrick, 0);
                break;
            case GREEN:
                putimage(NextLeft+x*21, NextTop+y*21, bmpGreenBrick, 0);
                break;
            case YELLOW:
                putimage(NextLeft+x*21, NextTop+y*21, bmpYellowBrick, 0);
                break;
            case PURPLE:
                putimage(NextLeft+x*21, NextTop+y*21, bmpPurpleBrick, 0);
                break;
            default:
                putimage(NextLeft+x*21, NextTop+y*21, bmpBlankBrick, 0);
            }
        }
}

void UpdateScreen()
{
    for(int x=0; x<COLS; x++)
        for(int y=0; y<ROWS; y++)
        {
            if(PreviousScreenLayout[x][y] == ScreenLayout[x][y])
                continue;   //No need to draw the same image again
            PreviousScreenLayout[x][y] = ScreenLayout[x][y];
            switch(ScreenLayout[x][y])
            {
            case BLUE:
                putimage(LEFT+x*21, TOP+y*21, bmpBlueBrick, 0);
                break;
            case RED:
                putimage(LEFT+x*21, TOP+y*21, bmpRedBrick, 0);
                break;
            case GREEN:
                putimage(LEFT+x*21, TOP+y*21, bmpGreenBrick, 0);
                break;
            case YELLOW:
                putimage(LEFT+x*21, TOP+y*21, bmpYellowBrick, 0);
                break;
            case PURPLE:
                putimage(LEFT+x*21, TOP+y*21, bmpPurpleBrick, 0);
                break;
            default:
                putimage(LEFT+x*21, TOP+y*21, bmpBlankBrick, 0);
            }
        }
}

void CheckForLine()
{
    int RemoveLines[10];
    int Remove;
    int x,y;
    int factor=1;
    for(y=0; y<ROWS; y++)
    {
        Remove=1;
        for(x=0; x<COLS; x++)
        {
            if(ScreenLayout[x][y] == BLANK)
                Remove=0;
        }
        if(Remove)
        {
            RemoveLine(y);

            Score += LineScore*factor;
            PrintScore();
            factor++;
        }
    }
    while (kbhit()) getch(); //Empty the keyboard buffer...
}

void RemoveLine(int LineNumber)
{
    int i,j;
    int count=0;
    int Temp[COLS];
    for(i=0; i<COLS; i++)
    {
        Temp[i]=ScreenLayout[i][LineNumber];
    }
    for(j=0; j<6; j++)
    {
        for(i=0; i<COLS; i++)
        {
            ScreenLayout[i][LineNumber]=(count ? Temp[i] : BLANK);
        }
        count = !count;
        UpdateScreen();
        delay(50);
    }
    for(i=LineNumber; i>0; i--)
        for(j=0; j<COLS; j++)
        {
            ScreenBackgroundLayout[j][i] = ScreenBackgroundLayout[j][i-1];
        }
    for(j=0; j<COLS; j++)
        ScreenBackgroundLayout[j][0] = BLANK;
    for(i=0; i<COLS; i++)
        for(j=0; j<ROWS; j++)
            ScreenLayout[i][j] = ScreenBackgroundLayout[i][j];
    ++LinesCleared;

    if(!(LinesCleared % 20))
        IncreaseSpeed();
}

int IncreaseSpeed()
{
    if(Speed-5 <= 0)
        return 1;
    Speed -= 5;  //increase the speed... lower the number, higher the speed
    Level++;

    return 0;
}

void PrintScore()
{

    sprintf(lpszScore, "%i", Score);
    int sssss=Score,counttt=0;
    if(sssss==0)
        counttt=1;
    while(sssss)
    {
        counttt++;
        sssss/=10;
    }

    counttt*=(textwidth("a"));
    outtextxy(getmaxx()-40-textwidth("RESET")+10,30+5,"Score");
    rectangle(getmaxx()-40-textwidth("RESET"),25+5,getmaxx()-20,35+textheight("EXIT")+10+textheight("EXIT")+5);

    outtextxy(getmaxx()-40-textwidth("RESET")+(20+textwidth("RESET")-counttt)/2,35+5+textheight("RESET")+5,lpszScore);

}
