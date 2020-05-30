#include "GL.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <GL\glut.h>
//#include <tchar.h>
//#include <gl\glaux.h>
//#pragma comment (lib, "GLAUX.lib");
#include <cmath>
#include <ctime>
#include "gmap.h"
#include <algorithm>
#include <set>
//#include "IL\il.h"
//#include "IL\ilu.h"
//#include "IL\ilut.h"


using namespace m;
using namespace std;


//#define CDS_FULLSCREEN 4;

// glutGet(GLUT_ELAPSED_TIME) - time in milliseconds from glutInit() (or first glutGet(GLUT_ELAPSED_TIME))

//map
GLint levelsnum = 10;
//gmap *gamemap;
gmap *gamemap;
// levelsnum
GLint actmap = baselevel;
//GLint levelsnum = 3;
//400, 10000000, 20000, deep, -70 - free map

GLint playermp = 0;
GLint playerlevel = 0;
GLint levelp = 0; // level points
GLint playlevel[2] = {levelconst, levelconst};

const GLint savebufsize = 1000000;
//const unsigned long long loadbufsize = max(1000, y * 2) * max(1000, x * 2) * max(z, sizemap) * levelsnum;

// traps
GLint trapattack[trapattackn][2] = {{0, 0}, {0, 0}, {0, 0}}; // hold, slow, atack; size
// traps

bool startmenu = true;
bool viewrotate = false;
GLfloat viewt[3] = {0.0f, 0.0f, 0.0f}; // view translate
GLfloat viewr[3] = {0.0f, 0.0f, 0.0f}; // view rotate

// time
bool addtime = false;
GLint gametime = 0;
GLint dtime = 0;
GLint mgametime = 0;
GLint handtimer[2] = {0, 0};
// time
bool atackmode = false;
bool atackview = true;
bool atackkey[4] = {false, false, false, false};
GLint pattackrange[4] = {0, 0, 0, 0};
GLfloat atackviewcolor[6] = {1.0f, 0.8f, 0.8f, 1.0f, 0.0f, 0.0f};
bool pause = false;
bool pause2 = false;
bool consol = false;
GLint speed = 0;
GLint pfirstmove = -1;
GLuint texture[texturenum];
//string texturename[texturenum] = {"data/weapon1.bmp", "data/weapon2.bmp"};
//GLint tcn = 0; //thing chest num
GLint live = maxlive;
GLint shild = 0;
GLint **mapsizexy;
//vector<GLint*> tc (0);// thing chest
GLint hand = 0;
bool mbutton[9] = {false, false, false, false, false, false, false, false, false};
//GLint bp = 0;  // bag free place
//GLint bap = 0; // bag all place
GLfloat bcol[4][3] = {{0.5f, 0.5f, 0.5f}, {0.6f, 0.6f, 0.6f}, {1.0f, 1.0f, 1.0f}, {0.6f, 0.6f, 0.4f}}; // button color
pair<GLint, obj> tb; // thing buffer 0 - thing num, 1 - thing place (-1 - -7 - player, -8, -9 - hands, 1 - 80 - bag, jacket, belt, trousers)
// num of things; type of thing (0 - nothing, 1 - 7 - player, 8 - instrument1, 9 - instrument2, 10 - weapon, 11 - create,
// 12 - chest, 13 - create instrument, 14 - 24 - trap( + rand break), 25 - door, 26 - main tower block, 27 - update tower block, 28 - money, 29 - potion, 30 - money elements),
// thing shild(1 - 7) / atack (8 - 10), for effect types of weapon(10) - / 100 - size of effect, % 100 - time of effect/ num for trap + 100 * trap size of atack(14 - 24)/ num of param * 100 + add param to rand(27)/ start live(26) / type of effect (29),
// thing size (1 - 7)/ no rand break 0 - 100 (8 - 10)/ trap time(14 - 24) / add param(27)/ num of level (26, for main block)(0 - nothing) * 100 + range / time of effect (29),
// % 100 - type of attack(type f weapon), / 100 - type of things for atack(0 - nothing)(10), for effect types of weapon - / 100 - num of magic points for attack/ num of max live(26)/ type of effect(-1 - no, 0 - + attack, 1 - + shied, 2 - + lives every second)(1 - 7) / size of effect(29),
//% 100 - range, / 100 - dist of attack(10)

// thing 27 - 0 - / 100 - num of param, % 100 - time; 1 - power; 2 - rand // num of effect(1 - 7)
obj pt[7]; // player things
obj taket[60]; //take things
GLint taketsize = 0;
bool takem = false; // take menu
vector<obj> thing; // from monsters && blocks , 3 - stone, 4 - chest, 5 - wood, 6 - create, 7 - door
obj phand[2]; // player hands
obj pb[pmx][pmy + 3]; // player bag, jacket, belt & trousers
bool mb[3] = {false, false, false}; // mouse buttons: left, middle, right
GLfloat mp[2] = {0, 0}; // mouse position
GLfloat wp[2] = {800, 600}; //window param
GLfloat maxy = 0, maxx = 0, gamey = 0, gamex = 0;
GLint menus = 0; // menu status
GLfloat playpos[3] = {x / 2, y  / 2, deep};
GLfloat playmove[3] = {0.0f, 0.0f, 0.0f};
GLfloat bmap[2];
bool thinghelp = true;
bool  thingtex = true; // menu texture
GLint opentable = 0;
obj mcreate[createnum];
const GLint maxcreateobjnum = 16;
//obj createobj[createtables][createnum2][maxcreateobjnum]; // create objects (complete)
//obj createtext[createtables][createnum2][createnum]; // create textures
GLint ct[createtables][createnum2][createnum]; // create table
obj createtnum[createtables][createnum2][createmaxnum];
string createf[createtables][createnum2]; // formul
//GLint creatething = 0;
GLint openchest = 0;
bool openchest2 = false;
GLint pmove = 0;
GLint *levelpos;
// levelsnum
bool playwin = false;
bool levelpause = false;
GLint *ngmmonster;// new gen main monster
// levelsnum
GLint ctformulmove = 0, ctformultimer = 0;
bool fview = true;
// monsters
vector<vector<vector<vector<GLint> > > > monstermaint(3); // 0 - start, 1 - level add, 2 - rand add, 3 - max
// 3, x, monstersize, 4
vector<vector<GLint> > monstermaintrand(3);
vector<GLint> monstermaintsum(3, 0);
// monster type; 0 - speed, 1 - atack, 2 - type for search player, 3 - max lives, 4 - shild, range, 5 - jump, 6 - search player range, 7 - time (destroy wall), 8 - add to player game level,  9 - range of effect;

class monstereffect
{
	public:
		GLint effect[trapattackn][2];
		GLint mstepl; // monster step length
		GLint dwall; // destroy wall timer
		GLint monstert[monstersize];
		vector<vector<GLint> > bigeffect; // effect for big monster
		monstereffect()
		{
			GLint a = 0;
			mstepl = 0;
			dwall = 0;
			for (GLint i = 0; i < trapattackn; i++)
			{
				effect[i][0] = 0;
				effect[i][1] = 0;
			}
			for (GLint i = 0; i < monstersize; i++)
			{
				monstert[i] = 0;
			}
		}
		monstereffect(GLint level, GLint b)
		{
			GLint a = 0, c = rand() % monstermaintsum[b] + 1;
			mstepl = 0;
			dwall = 0;
			for (GLint i = 0; i < trapattackn; i++)
			{
				effect[i][0] = 0;
				effect[i][1] = 0;
			}
			for (GLint i = 0; i < monstermaintrand[b].size(); i++)
			{
				c -= monstermaintrand[b][i];
				if (c <= 0)
				{
					c = i;
					break;
				}
			}
			for (GLint i = 0; i < monstersize; i++)
			{
				a = rand() % (monstermaint[b][c][i][2] + 1);
				monstert[i] = monstermaint[b][c][i][0] + a + monstermaint[b][c][i][1] * max(baselevel - level, level - baselevel);
				monstert[i] = min(monstert[i], monstermaint[b][c][i][3]);
			}
		}
};

vector<vector<GLfloat> > monster; // 0 - x, 1 - y, 2 - z, 3 - live, 4 - type, 5 - atack player
//6 - move monster, 7 - monster map, 8 - monster type of move and atack player, 9 - monster timer
// (0 - monsters at player map(all, where player(0, 1, 2)); 1... - atack towers monsters(on all levels (1 -> 2))) - monsterpos
vector<monstereffect> emonster;

// from wave to wave, time of wave, monster gen time, num of waves
GLint **levelwavetimer;
// levelsnum, 4
const GLint levelwavetime[5][3] = {{240, -20, 60}, {6, 4, 60}, {1, 0, 1}, {30, 10, 90}, {1, 0, 1}};
// start, increase, max; time from wave to wave, time of wave, gen monster time, rand gen monster (0 - 100), rand gen monster place

vector<vector<vector<GLint> > > atowerbuf (0);

GLint mlevelgen[2][3] = {{240, -10, 60}, {1, 1, 6}}; // gen time, monster rand(0-1000)
GLint mtime = 0;
bool gamewin = false;
//GLint addmtime = addmonstertime;

class tower
{
public:
	GLint posx, posy, tlevel, maxttimer;
	//tparamnum:
	GLint tparam[tparamnum][3]; // atack, range, live, shield, //addlives,  delete monster, slow, hold, atack monster; power, rand, time (for effects)
	vector<mobj> towerb;
	tower()
	{
	}
	tower(GLint px, GLint py, GLint towerlevel, GLint tlive, GLint trange)
	{
		maxttimer = maxtowerlive;
		for (GLint i = 0; i < tparamnum; i++)
		{
			tparam[i][0] = 0;
			tparam[i][1] = 0;
			tparam[i][2] = 0;
		}
		tlevel = towerlevel;
		tparam[0][1] = 100;
		tparam[1][1] = 100;
		tparam[2][1] = 100;
		tparam[1][0] = trange;
		tparam[2][0] = tlive;
		posx = px;
		posy = py;
	}
};

class stone
{
	public:
		GLfloat r, g, b, a; // color
		GLint t; // texture
		bool s;
		stone()
		{
			s = false;
			t = 0;
			r = 0.0f;
			g = 0.0f;
			b = 0.0f;
			a = 0.0f;
		}
};

class model
{
	public:
		GLint n, h; // num of blocks in play block, h of model
		vector<vector<vector<stone> > > m; // model
		model(GLint n2, GLint h2)
		{
			n = n2;
			h = h2;
			m.resize(n, vector<vector<stone> > (n, vector<stone> (h * n)));
		}
};

class sthing
{
	public:
		obj s; // sale thing
		obj b; // bay thing
		GLint nb; // num of bay thing
		GLint ns; // num of sale thing
		GLint n; //num of changed things
		GLint up;
		sthing()
		{
			nb = 0;
			ns = 0;
			n = 0;
			up = 0;
		}
};

class market
{
	public:
		GLint posx, posy, posz, poslevel, type;
		vector<sthing> sale; // sale thing
		market()
		{
		}
		market(const GLint mlevel, GLint px, GLint py)
		{
			GLint n = 0;
			type = rand() % omarket.size();
			posx = px;
			posy = py;
			poslevel = mlevel;
			for (GLint i = 0; i < z; i++)
			{
				if (gamemap[mlevel].block[px][py][i] == 0)
				{
					posz = i;
					break;
				}
			}
			if (mmarketch == 0)
			{
				n = 0;
			}
			else
			{
				n = rand() % mmarketch + 1;
			}
			for (GLint i = 0; i < n; i++)
			{
				sthing a;
				a.n = 0;
				a.s = findobj(&omarket[type], poslevel, &rmarket[type], &markets[type]);
				a.b = findobj(&ochange, poslevel, &rchange, &changes); // money
				a.ns = 1;
				a.nb = a.s.rare / a.b.rare + 1;
				if (mmarketchup == 0)
				{
					a.up = 0;
				}
				else
				{
					a.up = rand() % mmarketchup;
				}
				sale.push_back(a);
			}
			//cout << 1;
		}
};

vector<market> playchange;

vector<tower> playtower;
vector<model> cmodel; // color model
string savename = "autosave.gamesave", loadname = "autosave.gamesave";
GLint salenum = 0;
GLint openchange = 0;
GLint moneynum = 0;
// monsters
//
// glBindTexture (GL_TEXTURE_2D, texture[x]); - set texture x
//
// alpha with masking:
//glEnable (GL_BLEND);
//glDisable (GL_DEPTH_TEST);
//glBlendFunc (GL_DST_COLOR, GL_ZERO);
//draw mask
//glBlendFunc (GL_ONE, GL_ONE);
//dram image
//glEnable (GL_DEPTH_TEST);
//glDisable (GL_BLEND);
//

GLint pmovetimer = 0;

GLint genbmonster[3] = {100, 100, 1000};// gen big monster (0 - 10000); main, level add, max

GLint moptions[moptionsize][optionsize][4];
// monster options: size, rand, time of effect, time, dist, param; main, rand add, level add, max

GLfloat startstring[3] = {0.0f, 0.0f, 0.0f};
GLint *levelmainm; // level main monster

bool gfirstinit = false;

bool printc = false;
bool menusaveload = false;
GLint playeffect[peffectnum][2] = {{0, 0}, {0, 0}, {0, 0}}; // add lives, add attack, add shield
string menuinputs;
GLint menur[2] = {0, 0};
GLint cht = 0; // chest thing
/*GLfloat bc[blocknum][2][3] = {{{0.2f, 0.2f, 0.2f}, {0.4f, 0.4f, 0.4f}}, {{0.5f, 0.5f, 0.5f}, {0.7f, 0.7f, 0.7f}},
{{0.4f, 0.4f, 0.4f}, {0.6f, 0.6f, 0.6f}}, {{0.3f, 0.2f, 0.0f}, {0.5f, 0.4f, 0.0f}},
{{0.5f, 0.3f, 0.0f}, {0.7f, 0.5f, 0.0f}}, {{0.8f, 0.8f, 0.8f}, {1.0f, 1.0f, 1.0f}},
{{0.0f, 0.0f, 0.0f}, {0.2f, 0.2f, 0.2f}}, {{0.3f, 0.6f, 0.6f}, {0.5f, 0.8f, 0.8f}},
{{0.6f, 0.3f, 0.3f}, {0.8f, 0.5f, 0.5f}}}; //block color*/
//map

GL::GL()
{
}

class vertex
{
    public:
        vector<pair<GLint, GLint> > a;
        long b;
        long f;
        long c;
        vertex()
        {
            b = maximum;
            f = 0;
            c = -1;
        }
};

const GLint buttonnum = 1;

const GLfloat buttoncolors[buttonnum][2][3] ={{{0.2f, 0.2f, 0.2f}, {0.5f, 0.5f, 0.5f}}};

GLint m5mbutton = 0;

string m5mstring;

GLint m5mlevel = 0;

// menu animatoion
GLint menus2 = 0;
GLint amenu = 0; // 1 - start animation, -1 - end animation
GLint amtime = 14;
const GLint amactn = 44;
GLint animtimer = 0;
GLint amact = 0;
GLint menus3 = 0;
bool animboolm = true;
GLfloat ampos = 0.0f;

const pair<double, double> partnaddpos = make_pair(0.1f, 0.2f); // part num add pos

const GLint partntime = 100;
GLint partntimer = 0;
const GLint pnmaxstepn = 10;

// way
vector<vertex> makegraph(/*GLint n, GLint m, GLint jump, GLint ***gmap,*/GLint jump, GLint graphlevel = actmap, GLfloat posx = x / 2, GLint posy = y / 2) // make graph
{
	//cout << 1;
	vector<vector<GLint> > gmaph(x, vector<GLint> (y));
	vector<vertex> graph(x * y);
	for (GLint i = posx - wayrange; i < posx + wayrange; i++)
	{
		for (GLint j = posy - wayrange; j < posy + wayrange; j++)
		{
			if (i >= 0 && i < x && j >= 0 && j < y)
			{
				for (GLint k = 0; k < z; k++)
				{
					if (gamemap[graphlevel].block[i][j][k] == 0) // doors - one door
					{
						gmaph[i][j] = k;
						break;
					}
				}
			}
		}
	}
	//cout << 2;
	for (GLint i = posx - wayrange; i < posx + wayrange; i++)
	{
		for(GLint j = posy - wayrange; j < posy + wayrange; j++)
		{
			if (i >= 0 && i < x && j >= 0 && j < y)
			{
				if ((i - 1) >= 0 && gamemap[graphlevel].map[i - 1][j][0] == 0 && gmaph[i][j] + jump >= gmaph[i - 1][j])
				{
					graph[i * y + j].a.push_back(make_pair(y * (i - 1) + j, 1));
				}
				if ((i + 1) < x && gamemap[graphlevel].map[i + 1][j][0] == 0 && gmaph[i][j] + jump >= gmaph[i + 1][j])
				{
					graph[i * y + j].a.push_back(make_pair(y * (i + 1) + j, 1));
				}
				if ((j - 1) >= 0 && gamemap[graphlevel].map[i][j - 1][0] == 0 && gmaph[i][j] + jump >= gmaph[i][j - 1])
				{
					graph[i * y + j].a.push_back(make_pair(i * y + j - 1, 1));
				}
				if ((j + 1) < y && gamemap[graphlevel].map[i][j + 1][0] == 0 && gmaph[i][j] + jump >= gmaph[i][j + 1])
				{
					graph[i * y + j].a.push_back(make_pair(i * y + j + 1, 1));
				}
			}
		}
	}
	/*for (GLint i = 0; i < graph.size(); i++)
	{
		if (graph[i].a.size() > 0)
		{
			cout << graph[i].a.size() << ' ';
			for (GLint j = 0; j < graph[i].a.size(); j++)
			{
				cout << graph[i].a[j].first << ' ';
			}
			cout << '\n';
		}
	}*/
	//cout << 3;
	return graph;
} // not work

GLint way(vector<vertex> &g, GLint from, GLint to) // graph way Dijkstra algorithm
{
	//cout << 4;
	vector<GLint> h;
	GLint answer = 0;
	GLint n = g.size(), m = 0, gx = from, gy = to;
    g[gx].b = 0;
    g[gx].c = -1;
	g[gx].f = 0;
	set<pair<GLint, GLint> > s;
	s.insert(make_pair(0, gx));
	for (GLint i = 0; i < x; i++)//-wayrange; i <= wayrange; i++)
	{
		for (GLint j = 0; j < y; j++)//-wayrange; j <= wayrange; j++)
		{
			if (i != gx)
			{
				g[gx + i * y + j].f = 0;
				g[gx + i * y + j].c = 0;
				g[gx + i * y + j].b = maximum;
				s.insert(make_pair(maximum, gx + i * y + j));
			}
		}
	}
	//cout << 5;
    for (GLint i = 0; i < (wayrange * 2 + 1) * (wayrange * 2 + 1) + 1; i++)
    {
        GLint mn = (*s.begin()).first, pos = (*s.begin()).second;
        /*for (GLint j = 0; j < n; j++)
        {
            if (g[j].f == 0 && g[j].b <= mn)
            {
                mn = g[j].b;
                pos = j;
            }
        }*/
        g[pos].f = 1;
		s.erase(s.begin());
		/*if (pos == gy)
		{
			break;
		}*/
		for (GLint j = 0; j < g[pos].a.size(); j++)
        {
            if (g[g[pos].a[j].first].f == 0)
            {
                if (g[g[pos].a[j].first].b > g[pos].b + g[pos].a[j].second)
                {
                    //cout << pos << ' ' << 'j'g[pos].b << ' ';
					s.erase(make_pair(g[(g[pos].a[j]).first].b, (g[pos].a[j]).first));
					s.insert(make_pair(g[pos].b + (g[pos].a[j]).second, (g[pos].a[j]).first));
                    g[g[pos].a[j].first].c = pos;
                    g[g[pos].a[j].first].b = g[pos].b + g[pos].a[j].second;
                }
            }
        }
    }
	//cout << 6;
    if (g[y].b == maximum)
    {
		//cout << 7;
        return -1;
    }
    else
    {
        //vector<long> h;
        GLint gz = gy;
        answer = g[gy].b;
        for (GLint i = 0; gz != gx && g[gz].c != -1 && i < 3; i++)
        {
            h.push_back(gz);
            gz = g[gz].c;
        }
        h.push_back(gx);
		//cout << 2;
    }
	//cout << 8;
	if (h.size() >= 2)
	{
		return h[h.size() - 2];
	}
	else
	{
		return h[h.size() - 1];
	}
}
// not work
// way
void crload(GLint i, GLint j, GLint k, GLint *a)
{
	if (j == 0)
	{
		if (i == 0)
		{
			ct[i][j][k] = 0;
		}
		else
		{
			ct[i][j][k] = a[ct[i - 1][createnum2 - 1][k]];
		}
	}
	else
	{
		ct[i][j][k] = a[ct[i][j - 1][k]];
	}
}

void freeblock(GLint i, GLint j, GLint k, GLint r)
{
	if (gamemap[i].block[j][k][r] < 0)
	{
		if (-gamemap[i].block[j][k][r] - 1 < gamemap[i].mblock.size() - 1)
		{
			//gamemap[i].block[(GLint)gamemap[i].mblock.back().posx][(GLint)gamemap[i].mblock.back().posy][(GLint)gamemap[i].mblock.back().posz] = gamemap[i].block[j][k][r];
			if (gamemap[i].mblock.back().a.type != 14)
			{
				gamemap[i].block[(GLint)gamemap[i].mblock.back().posx][(GLint)gamemap[i].mblock.back().posy][(GLint)gamemap[i].mblock.back().posz] = gamemap[i].block[j][k][r];
			}
			else
			{
				//gamemap[i].map[(GLint)gamemap[i].mblock.back().posx][(GLint)gamemap[i].mblock.back().posy][5];
				gamemap[i].map[(GLint)gamemap[i].mblock.back().posx][(GLint)gamemap[i].mblock.back().posy][2] = gamemap[i].block[j][k][r];
			}
			swap(gamemap[i].mblock.back(), gamemap[i].mblock[-gamemap[i].block[j][k][r] - 1]);
		}
		m1.mblock.pop_back();
	}
	gamemap[i].block[j][k][r] = 0;
}

void freetrap(GLint i, GLint j, GLint k)
{
	if (gamemap[i].map[j][k][2] < 0)
	{
		if (-gamemap[i].map[j][k][2] - 1 < gamemap[i].mblock.size())
		{
			gamemap[i].block[(GLint)gamemap[i].mblock.back().posx][(GLint)gamemap[i].mblock.back().posy][(GLint)gamemap[i].mblock.back().posz] = -gamemap[i].map[j][k][2] - 1;
			if (gamemap[i].mblock.back().a.type != 14)
			{
				gamemap[i].block[(GLint)gamemap[i].mblock.back().posx][(GLint)gamemap[i].mblock.back().posy][(GLint)gamemap[i].mblock.back().posz] = -gamemap[i].map[j][k][2] - 1;
			}
			else
			{
				gamemap[i].map[(GLint)gamemap[i].mblock.back().posx][(GLint)gamemap[i].mblock.back().posy][2] = -gamemap[i].map[j][k][2] - 1;
			}
			swap(gamemap[i].mblock.back(), gamemap[i].mblock[-gamemap[i].map[j][k][2] - 1]);
		}
		m1.mblock.pop_back();
	}
}

void inputobj(ifstream *c, obj *b)
{
	(*c) >> (*b).attack;
	(*c) >> (*b).bn;
	(*c) >> (*b).t2;
	(*c) >> (*b).color[0];
	(*c) >> (*b).color[1];
	(*c) >> (*b).color[2];
	(*c) >> (*b).dist;
	(*c) >> (*b).edel;
	for (GLint k2 = 0; k2 < trapattackn; k2++)
	{
		for (GLint k3 = 0; k3 < efsize; k3++)
		{
			(*c) >> (*b).ef[k2][k3];
		}
	}
	(*c) >> (*b).live;
	(*c) >> (*b).mpoints;
	//c >> (*b).name; // ?
	for (GLint k2 = 0; k2 < peffectnum; k2++)
	{
		for (GLint k3 = 0; k3 < pefsize; k3++)
		{
			(*c) >> (*b).pef[k2][k3];
		}
	}
	(*c) >> (*b).points;
	(*c) >> (*b).range;
	(*c) >> (*b).rare;
	(*c) >> (*b).shield;
	(*c) >> (*b).size;
	(*c) >> (*b).t;
	(*c) >> (*b).text;
	(*c) >> (*b).timer;
	(*c) >> (*b).type;
	(*c) >> (*b).wtype;
}

void initFog()
{
    GLfloat fogColor[4] = {0.5f, 0.5f, 0.5f, 1.0f};
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.5f);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, 20.0f);
    glFogf(GL_FOG_END, 60.0f);
    glEnable(GL_FOG);

}

void initGL()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(100.0f);
	initFog();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

/*void initLight()
{
	GLfloat a[] = {10000000.0f};
	glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, a);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}*/

void startloadmoptions()
{
	ifstream c;
	c.open("monsteroptions.txt");
	for (GLint i = 0; i < moptionsize; i++)
	{
		for (GLint j = 0; j < optionsize; j++)
		{
			for (GLint k = 0; k < 4; k++)
			{
				c >> moptions[i][j][k];
			}
		}
	}
	c.close();
}

/*void initThing()
{
	thing[3].text = 1;
	thing[4].text = 1;
	thing[5].text = 1;
	thing[6].text = 1;
	thing[7].text = 1;
	thing[4].type = 12;
	thing[6].type = 11;
	thing[7].type = 25;
}*/

void startresettimer()
{
	for (GLint i = 0; i < levelsnum; i++)
	{
		for (GLint j = 0; j < 4; j++)
		{
			levelwavetimer[i][j] = 0;
		}
	}
}

void initplayer()
{
	taketsize = 0;
	obj freeobj;
	GLint i = 0, i2 = 0, i3 = 0;
	for (i = 0; i < 60; i++)
	{
		taket[i].type = -1;
	}
	for (i = 0; i < 7; i++)
	{
		pt[i] = freeobj;
		pt[i].type = i + 1;
	}
	for (i = 0; i < pmx; i++)
	{
		for (i2 = 0; i2 < pmy + 3; i2++)
		{
			pb[i][i2] = freeobj;
			pb[i][i2].type = -1;
		}
	}
	phand[0] = freeobj;
	phand[0].type = -1;
	phand[0].type = 10;
	phand[0].wtype = 0;
	phand[0].dist = 1;
	phand[0].range = 1;
	phand[0].attack = 4;
	phand[0].bn = 12;
	pt[5].size = 16;
	pt[3].size = 4;
	pt[2].size = 4;
	pt[1].size = 4;
	pt[6].shield = 2;
	pt[5].shield = 1;
	pt[4].shield = 6;
	pt[3].shield = 4;
	pt[2].shield = 2;
	pt[1].shield = 3;
	pt[0].shield = 2;
	phand[1] = freeobj;
	phand[1].type = -1;
	phand[1].type = 11;
	phand[1].t = 1;
	phand[1].wtype = 1;
	pb[0][6].type = 8;
	pb[0][6].text = 7;
	pb[0][6].bn = 20;
}

void startinitplayer()
{
	initplayer();
}

void startloadcreate()
{
	ifstream c;
	char a = 0;
	c.open("create.txt");
	for (GLint i = 0; i < createnum; i++)
	{
		for (GLint i2 = 0; i2 < createnum2; i2++)
		{
			for (GLint i3 = 0; i3 < createtables; i3++)
			{
				ct[i3][i2][i] = 0;
			}
		}
		mcreate[i].type = -1;
	}
	for (GLint i = 0; i < createtables; i++) // 2
	{
		for (GLint j = 0; j < createnum2; j++) // 1
		{
			for (GLint k = 3; k >= 0; k--)
			{
				for (GLint r = 0; r < 4; r++)
				{
					c >> ct[i][j][k * 4 + r];
					//cout << ct[i][j][k] << ' ';
				}
			}
			for (GLint k = 16; k < 20; k++)
			{
				c >> ct[i][j][k];
			}
			for (GLint k = 8; k >= 5; k--)
			{
				for (GLint r = 0; r < 4; r++)
				{
					c >> ct[i][j][k * 4 + r];
					//cout << ct[i][j][k] << ' ';
				}
			}
			for (GLint k = 0; k < createmaxnum; k++)
			{
				inputobj(&c, &createtnum[i][j][k]);
			}
			/*for (GLint k = 0; k < maxcreateobjnum; k++)
			{
				inputobj(&c, &createobj[i][j][k]);
			}*/
			c >> createf[i][j];
			/*for (GLint k = 0; k < createnum; k++)
			{
				c >> createtext[i][j][k].text;
			}*/ // ??
			// add formul
		}
	}
	c.close();
}

void inputmultiobj(ifstream *c, multiobj *a)
{
	inputobj(c, &(*a).oadd);
	inputobj(c, &(*a).oaddl);
	inputobj(c, &(*a).omain);
	inputobj(c, &(*a).omax);
}

void startloadmonstert()
{
	ifstream c;
	GLint a = 0, b = 0;
	c.open("monstert.txt");
	for (GLint i = 0; i < 3; i++)
	{
		c >> a;
		monstermaint[i].resize(a);
		for (GLint r = 0; r < a; r++)
		{
			monstermaint[i][r].resize(monstersize);
			for (GLint j = 0; j < monstersize; j++)
			{
				monstermaint[i][r][j].resize(4);
				for (GLint k = 0; k < 4; k++)
				{
					c >> monstermaint[i][r][j][k];
				}
			}
			c >> b;
			monstermaintsum[i] += b;
			monstermaintrand[i].push_back(b);
		}
	}
	c.close();
}

void startloadtrap()
{
	GLint a = 0;
	ifstream c;
	c.open("trap.txt");
	c >> a;
	otrap.resize(a);
	for (GLint i = 0; i < otrap.size(); i++)
	{
		inputmultiobj(&c, &otrap[i]);
	}
	c.close();
}

void startloadchest()
{
	GLint a = 0;
	ifstream c;
	c.open("chest.txt");
	c >> a;
	ochest.resize(a);
	for (GLint i = 0; i < ochest.size(); i++)
	{
		inputmultiobj(&c, &ochest[i]);
	}
	c.close();
}

void startloadmarket()
{
	GLint a = 0, b = 0;
	ifstream c;
	c.open("market.txt");
	c >> a;
	omarket.resize(a);
	for (GLint i = 0; i < omarket.size(); i++)
	{
		c >> b;
		omarket[i].resize(b);
		for (GLint j = 0; j < omarket[i].size(); j++)
		{
			inputmultiobj(&c, &omarket[i][j]);
		}
	}
	c >> a;
	ochange.resize(a);
	for (GLint i = 0; i < ochange.size(); i++)
	{
		inputmultiobj(&c, &ochange[i]);
	}
	c.close();
	rmarket.clear();
	rmarket.resize(omarket.size(), vector<GLint> ());
	markets.clear();
	markets.resize(omarket.size(), -1);
}

void startloadmonster()
{
	GLint a = 0;
	ifstream c;
	c.open("monster.txt");
	c >> a;
	omonster.resize(a);
	for (GLint i = 0; i < omonster.size(); i++)
	{
		inputmultiobj(&c, &omonster[i]);
	}
	c.close();
}

void startloadthing()
{
	GLint a = 0;
	ifstream c;
	c.open("thing.txt");
	c >> a;
	thing.resize(a);
	for (GLint i = 0; i < thing.size(); i++)
	{
		inputobj(&c, &thing[i]);
	}
	oblock.resize(a);
	for (GLint i = 0; i < oblock.size(); i++)
	{
		oblock[i].resize(blocksize);
		for (GLint j = 0; j < blocksize; j++)
		{
			c >> oblock[i][j];
		}
	}
	c.close();

}

void text(string s)
{
	GLint i = 0;
	glLineWidth(40.0f);
	//glTranslatef(startstring[0], startstring[1], startstring[2]);
	for (i = 0; i < s.size(); i++)
	{
		if (s[i] == '\n')
		{
			startstring[1] -= 0.007f;
			glRasterPos3f(startstring[0], startstring[1], startstring[2]);
			//glTranslatef(0.0f, -0.007f, 0.0f);
		}
		else
		{
		    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
			//glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
		}
	}
	//glTranslatef(-startstring[0], -startstring[1], -startstring[2]);
}

void text(GLint s)
{
    text(to_string(s));
	/*GLint i = 0, a = 0, b = 100000LL;
	char c;
	bool d = false;
	glLineWidth(0.04f);
	glTranslatef(startstring[0], startstring[1], startstring[2]);
	for (i = inttextmax; i > 0; i--)
	{
		a = (s / b) % 10;
		c = '0' + a;
		if (a > 0 || d)
		{
			d = true;
			glutStrokeCharacter(GLUT_STROKE_ROMAN, c); //glutBitmapCharacter()
		}
		b /= 10;
	}
	if (d == false)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
	}
	glTranslatef(-startstring[0] + glutStrokeLength(GLUT_STROKE_ROMAN, &s), -startstring[1], -startstring[2]);*/
}

void text(string s, GLfloat tx, GLfloat ty, GLfloat tz)
{
	glRasterPos3f(tx, ty, tz + 0.0001f);
	startstring[0] = tx;
	startstring[1] = ty;
	startstring[2] = tz + 0.01f;
	text(s);
}

void text(GLint s, GLfloat tx, GLfloat ty, GLfloat tz)
{
	glRasterPos3f(tx, ty, tz + 0.0001f);
	startstring[0] = tx;
	startstring[1] = ty;
	startstring[2] = tz + 0.01f;
	text(s);
}

class partnum
{
public:
	pair<GLfloat, GLfloat> startpos;
	pair<GLfloat, GLfloat> pos;
	GLint stepn, pncolorn, pnnum, pnpos;
	partnum(GLint a, GLint b, GLint n)
	{
		pnnum = n;
		pncolorn = b;
		stepn = 0;
		pnpos = a;
		pos = startpos;
	}
	void pnadd()
	{
		pos.first += partnaddpos.first;
		pos.second += partnaddpos.second;
		stepn++;
	}
	void pndraw(GLfloat a, GLfloat b, GLfloat c)
	{
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTranslatef(a, b, c + 16.0f);
		switch(pncolorn)
		{
		case 0:
			glColor3f(1.0f, 0.0f, 0.0f);
			text("-" , pos.first, pos.second, 0.0f);
			break;
		case 1:
			glColor3f(0.0f, 1.0f, 0.0f);
			text("+", pos.first, pos.second, 0.0f);
			break;
		default:
			glColor3f(1.0f, 1.0f, 1.0f);
			text("", pos.first, pos.second, 0.0f);
			break;
		}
		text(pnnum);
		glTranslatef(-a, -b, -c - 16.0f);
	}
	~partnum()
	{
	}
};

vector<partnum> mpartnum;

void addmonster(GLint monsterlevel, GLint i, GLint j, GLint mt = 0, GLint bigefnum = 0)
{
	vector<GLfloat> b;
	vector<GLint> f;
	GLint a = 0;
	monstereffect c(monsterlevel, mt);
	b.push_back(i); // 0
	b.push_back(j); // 1
	b.push_back(deep); // 2
	b.push_back(c.monstert[3]); // 3
	b.push_back(0); // flag for big effect // 4
	b.push_back(0); // 5
	b.push_back(-1); // 6
	b.push_back(monsterlevel); // 7
	b.push_back(mt); // 8
	/*for (GLint k = 0; k < motionsize; k++)
	{
		for (GLint r = 0; r < min(moption[k][1][3], moption[k][1][0] + max(baselevel - monsterlevel, monsterlevel - baselevel) * moptions[k][1][1]); r++)
		{
		}
	}*/
	// add m with rand of effects ??
	if (bigefnum > moptionsize)
	{
		bigefnum = moptionsize;
	}
	vector<GLint> bigef(moptionsize, 0);
	for (GLint k = 0; k < moptionsize; k++)
	{
		bigef[k] = k;
	}
	for (GLint k = 0; k < bigefnum; k++)
	{
		if (bigef.size() > 0)
		{
			vector<GLint> d;
			GLint en = rand() % bigef.size();
			GLint e = bigef[en];
			if (en != bigef.size() - 1)
			{
				swap(bigef[en], bigef.back());
			}
			bigef.pop_back();
			d.push_back(e);
			for (GLint k = 0; k < 6; k++)
			{
				if (moptions[e][k][1] < 0)
				{
					a = -(rand() % (-moptions[e][k][1] + 1));
				}
				else
				{
					a = rand() % (moptions[e][k][1] + 1);
				}
				d.push_back(min(moptions[e][k][0] + a + max(baselevel - monsterlevel, monsterlevel - baselevel) * moptions[e][k][2], moptions[e][k][3]));
			}
			d.push_back(0);
			c.bigeffect.push_back(d);
		}
	}
	b.push_back(0); // 9
	b.push_back(0); // for animation // 10
	b.push_back(0); // 11
	monster.push_back(b);
	emonster.push_back(c);
	//cout << monster.size() << '\n';
	gamemap[monsterlevel].map[i][j][6] = monster.size();
}
// remake effect rand ??

void initmarket(GLint mlevel, GLint mrmaxnum = 1, GLint mrnum = 0)
{
	for (GLint i = 0; i < x; i++)
	{
		for (GLint j = 0; j < y; j++)
		{
			if (gamemap[mlevel].map[i][j][3] == 0 && gamemap[mlevel].map[i][j][0] == 0 && rand() % mrmaxnum < mrnum)
			{
				market a(mlevel, i, j);
				playchange.push_back(a);
				gamemap[mlevel].map[i][j][9] = playchange.size();
			}
			//cout << ' ' << i << ' ' << j << '\n';
		}
	}
	rmarket.clear();
	rmarket.resize(omarket.size(), vector<GLint> ());
	markets.clear();
	markets.resize(omarket.size(), -1);
}

void initmonster(GLint maddmax = 1, GLint madd = 0, GLint monsterlevel = actmap, GLint monsterplace = max(x, y))
{
	srand((unsigned) time(NULL));
	for (GLint i = 0; i < x; i++)
	{
		for (GLint j = 0; j < y; j++)
		{
			if (gamemap[monsterlevel].mainmonsterpos[0] == i && gamemap[monsterlevel].mainmonsterpos[1] == j && levelmainm[monsterlevel] == -1)
			{
				addmonster(monsterlevel, i, j, 2, max(monsterlevel - baselevel, baselevel - monsterlevel) + 2);
				levelmainm[monsterlevel] = 0;
			}
			else
			{
				if (((max(i, (GLint)playpos[0]) - min(i, (GLint)playpos[0]) > distmonster &&
					max(j, (GLint)playpos[1]) - min(j, (GLint)playpos[1]) > distmonster) || monsterlevel != actmap) && (max(j, (GLint)playpos[1]) - min(j, (GLint)playpos[1]), max(i, (GLint)playpos[0]) - min(i, (GLint)playpos[0])) < monsterplace &&
					gamemap[monsterlevel].map[i][j][0] == 0 && rand() % maddmax < madd)
				{
					GLint a = 0;
					if (rand() % 10000 < (min(genbmonster[0] + max(baselevel - monsterlevel, monsterlevel - baselevel) * genbmonster[1], genbmonster[2])))
					{
						a = 1;
					}
					addmonster(monsterlevel, i, j, 0, a);
				}
			}
		}
	}
}

void square(GLfloat X, GLfloat Y, GLfloat Z, GLfloat X2, GLfloat Y2, GLfloat Z2, GLfloat R, GLfloat G, GLfloat B, GLfloat A)
{
	glBegin (GL_QUADS);
	glColor4f (R, G, B, A);
	glVertex3d (X, Y, Z);
	if (X == X2)
	{
		glVertex3d (X, Y2, Z);
		glVertex3d (X2, Y2, Z2);
		glVertex3d (X, Y, Z2);
	}
	if (Y == Y2)
	{
		glVertex3d (X2, Y, Z);
		glVertex3d (X2, Y2, Z2);
		glVertex3d (X, Y, Z2);
	}
	if (Z == Z2)
	{
		glVertex3d (X2, Y, Z);
		glVertex3d (X2, Y2, Z2);
		glVertex3d (X, Y2, Z);
	}
	glEnd ();
}

void square(GLfloat X, GLfloat Y, GLfloat Z, GLfloat X2, GLfloat Y2, GLfloat Z2, GLfloat R, GLfloat G, GLfloat B)
{
	square (X, Y, Z, X2, Y2, Z2, R, G, B, 1.0f);
}

void square(GLfloat X, GLfloat Y, GLfloat Z, GLfloat R, GLfloat G, GLfloat B)
{
	square (0.0f, 0.0f, 0.0f, X, Y, Z, R, G ,B);
}

void square(GLfloat X, GLfloat Y, GLfloat Z, GLfloat R, GLfloat G, GLfloat B, GLfloat A)
{
	square (0.0f, 0.0f, 0.0f, X, Y, Z, R, G, B, A);
}

void square2d(GLfloat X, GLfloat Y, GLfloat X2, GLfloat Y2)
{
	glBegin (GL_QUADS);
	glVertex2d (X, Y);
	glVertex2d (X, Y2);
	glVertex2d (X2, Y2);
	glVertex2d (X2, Y);
	glEnd ();

}

void tsquare(GLint tname, GLfloat X, GLfloat Y, GLfloat Z, GLfloat X2, GLfloat Y2, GLfloat Z2,
			GLfloat X3, GLfloat Y3, GLfloat Z3, GLfloat X4, GLfloat Y4, GLfloat Z4)
{
	glBindTexture(GL_TEXTURE_2D, texture[tname]);
	glBegin(GL_QUADS);
	glTexCoord2f (0.0f, 0.0f); glVertex3d (X, Y, Z);
	glTexCoord2f (0.0f, 1.0f); glVertex3d (X2, Y2, Z2);
	glTexCoord2f (1.0f, 1.0f); glVertex3d (X3, Y3, Z3);
	glTexCoord2f (1.0f, 0.0f); glVertex3d (X4, Y4, Z4);
	glEnd();
}

void tsquare(GLfloat X, GLfloat Y, GLfloat Z,  GLfloat X2, GLfloat Y2, GLfloat Z2)
{
	glBegin (GL_QUADS);
	glTexCoord2f (0.0f, 0.0f); glVertex3d (X, Y, Z);
	if (X == X2)
	{
		glTexCoord2f (0.0f, 1.0f); glVertex3d (X, Y2, Z);
		glTexCoord2f (1.0f, 1.0f); glVertex3d (X, Y2, Z2);
		glTexCoord2f (1.0f, 0.0f); glVertex3d (X, Y, Z2);
	}
	if (Y == Y2)
	{
		glTexCoord2f (0.0f, 1.0f); glVertex3d (X2, Y, Z);
		glTexCoord2f (1.0f, 1.0f); glVertex3d (X2, Y, Z2);
		glTexCoord2f (1.0f, 0.0f); glVertex3d (X, Y, Z2);
	}
	if (Z == Z2)
	{
		glTexCoord2f (0.0f, 1.0f); glVertex3d (X, Y2, Z);
		glTexCoord2f (1.0f, 1.0f); glVertex3d (X2, Y2, Z);
		glTexCoord2f (1.0f, 0.0f); glVertex3d (X2, Y, Z);
	}
	glEnd ();
}

void tsquare(GLfloat X, GLfloat Y, GLfloat X2, GLfloat Y2)
{
	if (X2 < X)
	{
		swap (X, X2);
	}
	if (Y2 < Y)
	{
		swap (Y2, Y);
	}
	glBegin (GL_QUADS);
	glTexCoord2f (0.0f, 0.0f); glVertex2d (X, Y);
	glTexCoord2f (0.0f, 1.0f); glVertex2d (X, Y2);
	glTexCoord2f (1.0f, 1.0f); glVertex2d (X2, Y2);
	glTexCoord2f (1.0f, 0.0f); glVertex2d (X2, Y);
	glEnd ();
}

void line(GLfloat X, GLfloat Y, GLfloat Z, GLfloat X2, GLfloat Y2, GLfloat Z2, GLfloat width)
{
	glLineWidth (width);
	glBegin(GL_LINES);
	glVertex3d(X, Y, Z);
	glVertex3d(X2, Y2, Z2);
	glEnd();
}

void line(GLfloat X, GLfloat Y, GLfloat X2, GLfloat Y2, GLfloat width)
{
	line(X, Y, 0.0f, X2, Y2, 0.0f, width);
}

void squareline(GLfloat X, GLfloat Y, GLfloat X2, GLfloat Y2, GLfloat W)
{
	line (X, Y, X, Y2, W);
	line (X, Y, X2, Y, W);
	line (X2, Y, X2, Y2, W);
	line (X, Y2, X2, Y2, W);
}

void tsquare(GLint tname, GLfloat X, GLfloat Y, GLfloat Z, GLfloat X2, GLfloat Y2, GLfloat Z2)
{
	glBindTexture (GL_TEXTURE_2D, texture[tname]);
	tsquare (X, Y, Z, X2, Y2, Z2);
}

void tsquare(GLint tname1, GLint tname2, GLfloat X, GLfloat Y, GLfloat Z, GLfloat X2, GLfloat Y2, GLfloat Z2)
{
	glEnable (GL_BLEND);
	glDisable (GL_DEPTH_TEST);
	glBlendFunc (GL_DST_COLOR, GL_ZERO);
	glBindTexture (GL_TEXTURE_2D, texture[tname1]);
	tsquare (X, Y, Z, X2, Y2, Z2);
	glBlendFunc (GL_ONE, GL_ONE);
	glBindTexture (GL_TEXTURE_2D, texture[tname2]);
	tsquare (X, Y, Z, X2, Y2, Z2);
	glEnable (GL_DEPTH_TEST);
	glDisable (GL_BLEND);
}

void tsquare(GLint tname, GLfloat X, GLfloat Y, GLfloat X2, GLfloat Y2)
{
	glBindTexture (GL_TEXTURE_2D, texture[tname]);
	tsquare (X, Y, X2, Y2);
}

void tsquare(GLint tname1, GLint tname2, GLfloat X, GLfloat Y, GLfloat X2, GLfloat Y2)
{
	tsquare (tname1, tname2, X, Y, 0.0f, X2, Y2, 0.0f);
}

class button
{
public:
	GLfloat bx, by, bsx, bsy;
	bool clickb;
	GLint bc;
	button(GLfloat bposx, GLfloat bposy, GLfloat bx2, GLfloat by2, GLint bc2 = 0)
	{
		clickb = false;
		bc = bc2;
		bx = bposx;
		by = bposy;
		bsx = bx2;
		bsy = by2;
	}
	bool bclick(GLfloat mx, GLfloat my)
	{
		if (mx >= bx && mx < bsx && my >= by && my < bsy)
		{
			clickb = true;
			if (mb[0])
			{
				mb[0] = false;
				return true;
			}
		}
		return false;
	}
	void drawb()
	{
		GLint clickb2 = 0;
		if (clickb)
		{
			clickb2 = 1;
		}
		glColor3f(buttoncolors[bc][clickb2][0], buttoncolors[bc][clickb2][1], buttoncolors[bc][clickb2][2]);
		square2d(bx, by, bsx, bsy);
	}
	~button()
	{
	}
};

void drawbar(GLfloat X, GLfloat Y, GLfloat X2, GLfloat Y2, GLfloat a, GLfloat maxa, bool b, GLfloat R, GLfloat G, GLfloat B, GLfloat R2 = 0.5f, GLfloat G2 = 0.5f, GLfloat B2 = 0.5f)
{
    glColor3f(R2, G2, B2);
    square2d(X, Y, X2, Y2);
    glColor3f(R, G, B);
    square2d(X, Y, b?X + (X2 - X) * min(1.0f, a / maxa): X2, b? Y2: Y + (Y2 - Y) * min(1.0f, a / maxa));
    glColor3f(0.0f, 0.0f, 0.0f);
    squareline(X, Y, X2, Y2, 2.0f);
}

void newcreatem(bool b = false)
{
	if (!gfirstinit)
	{
		levelpos = (GLint*) malloc(levelsnum * sizeof(GLint));
		levelmainm = (GLint*) malloc(levelsnum * sizeof(GLint));
		ngmmonster = (GLint*) malloc(levelsnum * sizeof(GLint));
		gamemap = (gmap*) malloc(levelsnum * sizeof(gmap));
	}
	else
	{
		for (GLint i = 0; i < levelsnum; i++)
		{
			free(levelwavetimer[i]);
			if (b)
			{
				free(mapsizexy[i]);
			}
		}
		free(levelwavetimer);
		void *m = realloc(levelpos, levelsnum * sizeof(GLint));
		levelpos = static_cast<GLint*>(m);
		m = realloc(levelmainm, levelsnum * sizeof(GLint));
		levelmainm = static_cast<GLint*>(m);
		m = realloc(ngmmonster, levelsnum * sizeof(GLint));
		ngmmonster = static_cast<GLint*>(m);
		m = realloc(gamemap, levelsnum * sizeof(gmap));
		gamemap = static_cast<gmap*>(m);
		if (b)
		{
			free(mapsizexy);
		}
	}
	if (b)
	{
		mapsizexy = (GLint**) malloc(levelsnum * sizeof(GLint));
	}
	levelwavetimer = (GLint**) malloc(levelsnum * sizeof(GLint));
	for (GLint i = 0; i < levelsnum; i++)
	{
		levelwavetimer[i] = (GLint*) malloc(4 * sizeof (GLint));
		if (b)
		{
			mapsizexy[i] = (GLint*) malloc(2 * sizeof(GLint));
		}
	}
}

void newdeletem()
{
	if(gfirstinit)
	{
		for (GLint i = 0; i < levelsnum; i++)
		{
			free(levelwavetimer[i]);
		}
		free(levelwavetimer);
		free(levelpos);
		free(levelmainm);
		free(ngmmonster);
		/*for (GLint i = 0; i < levelsnum; i++)
		{
			gamemap[i].deletemap();
		}*/
		free(gamemap);
	}
}

void playerjump(GLint *a, GLfloat &playz)
{
	if (a[(GLint)playz] != 0)
	{
		playz++;
	}
	else
	{
		GLint i = 0;
		for (i = 0; i <= playz; i++)
		{
			if (a[i] == 0)
			{
				break;
			}
		}
		playz = i;
	}
}

void playerjump(vector<GLint> &a, GLfloat &playz)
{
	if (a[(GLint)playz] != 0)
	{
		playz++;
	}
	else
	{
		GLint i = 0;
		for (i = 0; i <= playz; i++)
		{
			if (a[i] == 0)
			{
				break;
			}
		}
		playz = i;
	}
}

void drawperson()
{
	GLfloat c[2][3] = {{0.0f, 0.3f, 0.0f}, {0.0f, 0.5f, 0.0f}};
	square ( squarex / ph * ph2, squarey / ph, 0.0f, squarex / ph * ph2, squarey / ph * ph2, playerh * squarez, c[0][0], c[0][1], c[0][2]);
	square ( squarex / ph, squarey / ph * ph2, 0.0f, squarex / ph * ph2, squarey / ph * ph2, playerh * squarez, c[0][0], c[0][1], c[0][2]);
	square ( squarex / ph, squarey / ph, 0.0f, squarex / ph, squarey / ph * ph2, playerh * squarez, c[0][0], c[0][1], c[0][2]);
	square ( squarex / ph, squarey / ph, 0.0f, squarex / ph * ph2, squarey / ph, playerh * squarez, c[0][0], c[0][1], c[0][2]);
	square ( squarex / ph, squarey / ph, playerh * squarez, squarex / ph * ph2, squarey / ph * ph2, playerh * squarez, c[1][0], c[1][1], c[1][2]);
}
// add model
void drawplayer()
{
	glBindTexture (GL_TEXTURE_2D, texture[1]);
	//GLfloat color[2][3] = {{0.4f, 0.0f, 0.0f}, {0.6f, 0.0f, 0.0f}};
	drawperson(/*color*/);
}
// ??
GLint randstep(GLfloat posx, GLfloat posy, GLfloat posz, GLfloat p, GLint jump = playjump) // add end of the game place
{
	vector<GLint> a;
	for (GLint i = 0; i < 4; i++)
	{
		if (i != p)
		{
			if ((GLint)posx + (1 - i / 2) * (i % 2 * 2 - 1) >= 0 && (GLint)posx + (1 - i / 2) * (i % 2 * 2 - 1) < x &&
				(GLint)posy + (i / 2) * (i % 2 * 2 - 1) >= 0 && (GLint)posy + (i / 2) * (i % 2 * 2 - 1) < y &&
				m1.map[(GLint)posx + (1 - i / 2) * (i % 2 * 2 - 1)][(GLint)posy + (i / 2) * (i % 2 * 2 - 1)][0] == 0 &&
				m1.block[(GLint)posx + (1 - i / 2) * (i % 2 * 2 - 1)][(GLint)posy + (i / 2) * (i % 2 * 2 - 1)][(GLint)posz + jump] == 0)
			{
				a.push_back(i);
			}
		}
	}
	if (a.size() != 0)
	{
		return a[rand() % (a.size())];
	}
	else
	{
		return p;
	}
}

pair<GLint, GLint> shortway(GLint fromx, GLint fromy, GLint fromz, GLint tox, GLint toy, GLint waylevel, bool &c)
{
	//cout << 2 << '\n';
	GLint a = 0, b = 0;
	if (fromx > tox)
	{
		a = -1;
	}
	else
	{
		if (fromx == tox)
		{
			a = 0;
		}
		else
		{
			a = 1;
		}
	}
	if (fromy > toy)
	{
		b = -1;
	}
	else
	{
		if (fromy == toy)
		{
			b = 0;
		}
		else
		{
			b = 1;
		}
	}
	if (a != 0 && gamemap[waylevel].map[fromx + a][fromy][0] == 0 && gamemap[waylevel].block[fromx + a][fromy][fromz + 1] == 0)
	{
		c = false;
		return make_pair(a, 0);
	}
	else
	{
		if (b != 0 && gamemap[waylevel].map[fromx][fromy + b][0] == 0 && gamemap[waylevel].block[fromx][fromy + b][fromz + 1] == 0)
		{
			c = false;
			return make_pair(0, b);
		}
		else
		{
			if (a != 0 || b != 0 && !(c && max(max(fromx, tox) - min(fromx, tox), max(fromy, toy) - min(fromy, toy)) <= 1))
			{
				//return to way
				c = true;
				return make_pair(a, b);
			}
			else
			{
				c = false;
				return make_pair(0, 0);
			}
		}
	}
}

GLint playsumeffect(GLint a)
{
	GLint b = 0;
	for (GLint i = 0; i < 7; i++)
	{
		b += pt[i].pef[a][0];
	}
	return b;
}

void moptioneffect(GLint i, vector<GLint> *a)
{
	if ((*a)[6] >= (*a)[4])
	{
		switch((*a)[0])
		{
		case 0:
			//live = 0;
			break;
		case 1:
			if (addtime)
			{
				addmonster(monster[i][7], monster[i][0], monster[i][1], 0, 0); // ?? big effect num ??
			}
			break;
		case 2:
			trapattack[0][0] = max(trapattack[0][0], (*a)[1]);
			trapattack[0][1] += (*a)[3];
			break;
		case 3:
			cout << 1;
			trapattack[1][0] = max(trapattack[1][0], (*a)[1]);
			trapattack[1][1] += (*a)[3];
			break;
		case 4:
			trapattack[2][0] = max(trapattack[2][0], (*a)[1]);
			trapattack[2][1] += (*a)[3];
			break;
		default:
			break;
		}
		(*a)[6] = 0;
	}
}

void remakemonster(GLint i)
{
	emonster[i].monstert[3] /= 2;
	gamemap[(GLint)monster[i][7]].map[(GLint)monster[i][0]][(GLint)monster[i][1]][6] = 0;
	monster[i][0] = gamemap[(GLint)monster[i][7]].mainmonsterpos[0];
	monster[i][1] = gamemap[(GLint)monster[i][7]].mainmonsterpos[1];
	playerjump(gamemap[(GLint)monster[i][7]].block[(GLint)monster[i][0]][(GLint)monster[i][1]], monster[i][2]);
	monster[i][3] = emonster[i].monstert[3];
	gamemap[(GLint)monster[i][7]].map[(GLint)monster[i][0]][(GLint)monster[i][1]][6] = i + 1;
}

void findremakebeffect(GLint i, bool &a)
{
	for (long j = 0; j < emonster[i].bigeffect.size(); j++)
	{
		if (emonster[i].bigeffect[j][0] == 5 && emonster[i].monstert[3] > emonster[i].bigeffect[j][5])
		{
			a = false;
		}
	}
}

void delm (bool b, GLint i, GLint a)
{
	if (b)
	{
		vector<GLint> rmonster;
		GLint rnum = -1;
		GLint j = rand() % a + 1;
		for (GLint r = 0; r < j; r++)
		{
			if (taketsize < 60)
			{
				taket[taketsize] = findobj(&omonster, monster[i][7], &rmonster, &rnum, false);
				taketsize++;
			}
		}
	}
	(gamemap[(GLint)monster[i][7]]).map[(GLint)monster[i][0]][(GLint)monster[i][1]][6] = 0;
	if (i < monster.size() - 1)
	{
		swap(emonster.back(), emonster[i]);
		for (GLint k = 0; k < monster[i].size() && k < monster.back().size(); k++)
		{
			swap((monster.back())[k], monster[i][k]);
		}
		(gamemap[(GLint)monster[i][7]]).map[(GLint)monster[i][0]][(GLint)monster[i][1]][6] = i + 1;
	}
	//cout << 't' << 'n';
	//cout << 2 << ' ' << monster.back()[0] << ' ' << monster.back()[1] << '\n' << '\n';
	/*for (GLint k = 0; k < monster.size() - 1; k++)
	{
		/*if (monster[k].back() == 1) //&& monster.back()[0] == monster[k][0])
		{
			cout << 1 << ' ' << monster[k][0] << ' ' << monster[k][1] << '\n';
		}*/
		/*if (monster.back()[0] == monster[k][0] && monster.back()[1] == monster[k][1])
		{
			//cout << 2 << ' ' << monster.back()[0] << ' ' << monster.back()[1] << '\n';
			(gamemap[(GLint)monster.back()[7]]).map[(GLint)monster.back()[0]][(GLint)monster.back()[1]][6] = k + 1;
			//break;
		}
	}*/  // ?????????????
	//swap(monster.back(), monster[i]);
	monster.pop_back();
	emonster.pop_back();
}

void delmonster(bool b, GLint i, GLint c = mrandthingnum)
{
	if (monster[i][3] <= 0)
	{
		bool a = true;
		findremakebeffect(i, a);
		if (a)
		{
			delm(b, i, c);
		}
		else
		{
			emonster[i].monstert[3] /= 2;
			monster[i][3] = emonster[i].monstert[3];
		}
	}
}

void delmainmonster(GLint i, GLint c = mmainrandthingnum)
{
	if (monster[i][3] <= 0)
	{
		bool a = true;
		findremakebeffect(i, a);
		if (a)
		{
			obj a;
			a.t2 = 9;
			levelmainm[(GLint)monster[i][7]] = 1;
			a.wtype = monster[i][7] + 1; // level ??
			if (taketsize < 60)
			{
				taket[taketsize] = a;
				taketsize++;
			}
			if (taketsize < 60)
			{
				taket[taketsize] = a;
				taketsize++;
			}
			delm(true, i, c);
		}
		else
		{
			remakemonster(i);
		}
	}
}

void monsterbigefattack(GLint i)
{
	for (GLint j = 0; j < emonster[i].bigeffect.size(); j++)
	{
		if (actmap == monster[i][7] && max(playpos[0], monster[i][0]) - min(playpos[0], monster[i][0]) <= emonster[i].monstert[10] && max(playpos[1], monster[i][1]) - min(playpos[1], monster[i][1]) <= emonster[i].bigeffect[j][5])
		{
			monster[i][4] = 1;
			moptioneffect(i, &emonster[i].bigeffect[j]);
		}
		if (addtime)
		{
			emonster[i].bigeffect[j][6]++;
		}
	}
}

void firstmonsteratackp(GLint i, bool b)
{
	if (actmap == monster[i][7] && max(playpos[0], monster[i][0]) - min(playpos[0], monster[i][0]) <= emonster[i].monstert[5] && max(playpos[1], monster[i][1]) - min(playpos[1], monster[i][1]) <= emonster[i].monstert[5])
	{
		if (monster[i][5] == 0)
		{
			GLint a = emonster[i].monstert[1] * shildconst / (shildconst + shild * ((GLfloat)(100 + playeffect[2][1] + playsumeffect(2)) / 100));
			if (a > 0)
			{
				partnum pn1(0, 0, a);
				mpartnum.push_back(pn1);
			}
			monster[i][5] = 1;
			live -= a;
		}
	}
	else
	{
		monster[i][5] = 0;
	}
	if (b)
	{
		monster[i][4] = 0;
		monsterbigefattack(i);
	}
}

void monsteratackp(GLint i, bool b)
{
	if (actmap == monster[i][7] && max(playpos[0], monster[i][0]) - min(playpos[0], monster[i][0]) <= emonster[i].monstert[5] && max(playpos[1], monster[i][1]) - min(playpos[1], monster[i][1]) <= emonster[i].monstert[5])
	{
		GLint a = emonster[i].monstert[1] * shildconst / (shildconst + shild * ((GLfloat)(100 + playeffect[2][1] + playsumeffect(2)) / 100));
		if (a > 0)
		{
			partnum pn1(0, 0, a);
			mpartnum.push_back(pn1);
		}
		live -= a;
	}
	if (b)
	{
		monsterbigefattack(i);
	}
}

void meffect(GLint i)
{
	GLint a = 0;
	for (GLint i2 = 0; i2 < trapattackn; i2++)
	{
		if (emonster[i].effect[i2][0] > 0)
		{
			emonster[i].effect[i2][0]--;
			if (emonster[i].effect[i2][0] <= 0)
			{
				emonster[i].effect[i2][0] = 0;
				emonster[i].effect[i2][1] = 0;
			}
		}
	}
	a += (emonster[i].effect[0][1] + emonster[i].effect[2][1]);
	monster[i][3] -= emonster[i].effect[0][1];
	//monster[i][3] -= emonster[i].effect[1][1];
	monster[i][3] -= emonster[i].effect[2][1];
	if (a > 0)
	{
		partnum pn1(i + 1, 0, a);
		mpartnum.push_back(pn1);
	}
}

void mtoweratack(GLint i)
{
	for (GLint i2 = 0; i2 < playtower.size(); i2++)
	{
		if (playtower[i2].tlevel == monster[i][7] && max(playtower[i2].posx, (GLint)monster[i][0]) - min(playtower[i2].posx, (GLint)monster[i][0]) <= emonster[i].monstert[5] && max(playtower[i2].posy, (GLint)monster[i][1]) - min(playtower[i2].posy, (GLint)monster[i][1]) <= emonster[i].monstert[5])
		{
			playtower[i2].tparam[2][0] -= emonster[i].monstert[1] * shildconst / (playtower[i2].tparam[3][0] + shildconst);
		}
	}
}

/*void mgoanim(GLint i)
{
	if (monster[i][10] != 0)
	{
		if (monster[i][11] + (GLint)(1000 / emonster[i].monstert[0]) > glutGet(GLUT_ELAPSED_TIME) && monster[i][10] != 1)
		{
			if ()
			{

			}
			else
			{

			}
		}
		else
		{
			if ()
			{
				monster[i][0] = (GLint)monster[i][0] + ...; // add
			}
			else
			{
				monster[i][1] = (GLint)monster[i][1] + ...; // add
			}
		}
	}
}*/

GLint findtowerinrange(GLint i)
{
	GLint monstertowern = -1;
	for (GLint i2 = 0; i2 < playtower.size(); i2++)
	{
		if (playtower[i2].tlevel == (GLint)monster[i][7] && max(playtower[i2].posx, (GLint)monster[i][0]) - min(playtower[i2].posx, (GLint)monster[i][0]) <= emonster[i].monstert[7] && max(playtower[i2].posy, (GLint)monster[i][1]) - min(playtower[i2].posy, (GLint)monster[i][1]) <= emonster[i].monstert[7])
		{
			monstertowern = i2;
		}
	}
	return monstertowern;
}

void breakwall(GLint i, GLint wposx, GLint wposy)
{
	if (emonster[i].dwall >= emonster[i].monstert[8])
	{
		emonster[i].dwall = 0;
		for (GLint j = 0; j < z; j++)
		{
			if (j < deep)
			{
				gamemap[(GLint)monster[i][7]].block[wposx][wposy][j] = 2;
			}
			else
			{
				gamemap[(GLint)monster[i][7]].block[wposx][wposy][j] = 0;
			}
		}
	}
	else
	{
		emonster[i].dwall++;
	}
}

void monsterbreakwall(GLint i, pair<GLint, GLint> a) // num of monster, monster add pos
{
	if (a.first != 0 && a.second != 0)
	{
		if (gamemap[(GLint)monster[i][7]].map[(GLint)monster[i][0] + a.first][(GLint)monster[i][1]][0] == 1) // strong wall
		{
			if (gamemap[(GLint)monster[i][7]].map[(GLint)monster[i][0]][(GLint)monster[i][1] + a.second][8] == 0) // !(tower)
			{
				breakwall(i, (GLint)monster[i][0], (GLint)monster[i][1] + a.second);
				// break wall
			}
			else
			{
				// break tower
			}
		}
		else
		{
			if (gamemap[(GLint)monster[i][7]].map[(GLint)monster[i][0]][(GLint)monster[i][1] + a.second][0] == 1) // strong wall
			{
				if (gamemap[(GLint)monster[i][7]].map[(GLint)monster[i][0] + a.first][(GLint)monster[i][1]][8] == 0) // !(tower)
				{
					breakwall(i, (GLint)monster[i][0] + a.first, (GLint)monster[i][1]);
					// break wall
				}
				else
				{
					// break tower
				}
			}
			else
			{
				if (gamemap[(GLint)monster[i][7]].map[(GLint)monster[i][0] + a.first][(GLint)monster[i][1]][8] != 0) // tower
				{
					if (gamemap[(GLint)monster[i][7]].map[(GLint)monster[i][0]][(GLint)monster[i][1] + a.second][8] == 0) // !(tower 2)
					{
						if (emonster[i].monstert[2] == 3 || emonster[i].monstert[2] == 5)
						{
							breakwall(i, (GLint)monster[i][0], (GLint)monster[i][1] + a.second);
							// break wall
						}
						else
						{
							// break tower
						}
						// break tower or wall
					}
					else
					{
						// break tower
					}
				}
				else
				{
					if (gamemap[(GLint)monster[i][7]].map[(GLint)monster[i][0]][(GLint)monster[i][1] + a.second][8] != 0) // tower 2
					{
						if (emonster[i].monstert[2] == 3 || emonster[i].monstert[2] == 5)
						{
							breakwall(i, (GLint)monster[i][0] + a.first, (GLint)monster[i][1]);
							// break wall
						}
						else
						{
							// break tower
						}
						// break tower or wall
					}
					else
					{
						GLint r = rand() % 2;
						if (r == 0)
						{
							breakwall(i, (GLint)monster[i][0] + a.first, (GLint)monster[i][1]);
						}
						else
						{
							breakwall(i, (GLint)monster[i][0], (GLint)monster[i][1] + a.second);
						}
						// break wall
					}
				}
			}
		}
	}
	else
	{
		if (a.first != 0)
		{
			if (gamemap[(GLint)monster[i][7]].map[(GLint)monster[i][0] + a.first][(GLint)monster[i][1]][8] == 0) // !(tower)
			{
				breakwall(i, (GLint)monster[i][0] + a.first, (GLint)monster[i][1]);
				// break wall
			}
			else
			{
				// break tower
			}
		}
		else
		{
			if (gamemap[(GLint)monster[i][7]].map[(GLint)monster[i][0]][(GLint)monster[i][1] + a.second][8] == 0) // !(tower)
			{
				breakwall(i, (GLint)monster[i][0], (GLint)monster[i][1] + a.second);
				// break wall
			}
			else
			{
				// break tower
			}
		}
	}
}

bool mshortway(GLfloat mposx, GLfloat mposy, GLint i)
{
	bool b = false;
	pair<GLint, GLint> d;
	if ((GLint)monster[i][6] != -1)
	{
		// ??
		gamemap[(GLint)monster[i][7]].map[(GLint)(monster[i][0] - (1 - (GLint)monster[i][6] / 2) * ((GLint)monster[i][6] % 2 * 2 - 1))][(GLint)(monster[i][1] - ((GLint)monster[i][6] / 2) * ((GLint)monster[i][6] % 2 * 2 - 1))][0] = 2;
	}
	d = shortway(monster[i][0], monster[i][1], monster[i][2], mposx, mposy, monster[i][7], b);
	if (monster[i][6] != -1)
	{
		// ??
		gamemap[(GLint)monster[i][7]].map[(GLint)(monster[i][0] - (1 - (GLint)monster[i][6] / 2) * ((GLint)monster[i][6] % 2 * 2 - 1))][(GLint)(monster[i][1] - ((GLint)monster[i][6] / 2) * ((GLint)monster[i][6] % 2 * 2 - 1))][0] = 0;
	}
	if (b)
	{
		return false;
	}
	else
	{
		//??
		GLint a = 0;
		if (d.first == 1)
		{
			a = 1;
		}
		else
		{
			if (d.first == -1)
			{
				a = 0;
			}
			else
			{
				if (d.second == 1)
				{
					a = 3;
				}
				else
				{
					a = 2;
				}
			}
		}
		monster[i][6] = a;
		monster[i][0] += d.first;
		monster[i][1] += d.second;
		playerjump((gamemap[(GLint)monster[i][7]]).block[(GLint)monster[i][0]][(GLint)monster[i][1]], monster[i][2]);
	}
	return true;
}

void monstermove1(GLint i, GLint monstertowern, GLint a, bool c = true)
{
	if (emonster[i].effect[0][0] == 0)
	{
		//cout << emonster[i].effect[1][1] << ' ' << emonster[i].effect[1][1] << '\n';
		if (emonster[i].mstepl >= emonster[i].effect[1][1])
		{
			(gamemap[(GLint)monster[i][7]]).map[(GLint)monster[i][0]][(GLint)monster[i][1]][6] = 0;
			if (max(playpos[0], monster[i][0]) - min(playpos[0], monster[i][0]) <= emonster[i].monstert[7] && max(playpos[1], monster[i][1]) - min(playpos[1], monster[i][1]) <= emonster[i].monstert[7])
			{
				if (mshortway(playpos[0], playpos[1], i) == false)
				{
					goto gtmonstermove1;
				}
			}
			else
			{
				if (monstertowern != -1)
				{
					if(mshortway(playtower[monstertowern].posx, playtower[monstertowern].posy, i) == false)
					{
						goto gtmonstermove1;
					}
					/*bool b = true;
					pair<GLint, GLint> d;
					d = shortway(monster[i][0], monster[i][1], monster[i][2], playtower[monstertowern].posx, playtower[monstertowern].posy, monster[i][7], b);
					if (b)
					{
						goto gtmonstermove2;
					}
					else
					{
						monster[i][0] += d.first;
						monster[i][1] += d.second;
						playerjump((gamemap[(GLint)monster[i][7]]).block[(GLint)monster[i][0]][(GLint)monster[i][1]], monster[i][2]);
					}*/
				}
				else
				{
					gtmonstermove1:;
					//(gamemap[(GLint)monster[i][7]]).map[(GLint)monster[i][0]][(GLint)monster[i][1]][6] = 0;
					if (c)
					{
						switch(emonster[i].monstert[2])
						{
						case 0:
							a = randstep(monster[i][0], monster[i][1], monster[i][2], monster[i][6], emonster[i].monstert[6]);
							//cout << a;
							// ?
							monster[i][6] = a;

							monster[i][0] += (1 - a / 2) * (a % 2 * 2 - 1);
							monster[i][1] += (a / 2) * (a % 2 * 2 - 1);
							playerjump((gamemap[(GLint)monster[i][7]]).block[(GLint)monster[i][0]][(GLint)monster[i][1]], monster[i][2]);
							//go to rand way
							break;
						case 1:
							gtmonsterway1:;
							a = monster[i][6];
							if (a != -1 && (gamemap[(GLint)monster[i][7]]).map[(GLint)monster[i][0] + (1 - a / 2) * (a % 2 * 2 - 1)][(GLint)monster[i][1] + (a / 2) * (a % 2 * 2 - 1)][0] == 0 &&
								(GLint)monster[i][0] + (1 - a / 2) * (a % 2 * 2 - 1) >= 0 &&
								(GLint)monster[i][0] + (1 - a / 2) * (a % 2 * 2 - 1) < x &&
								(gamemap[(GLint)monster[i][7]]).block[(GLint)monster[i][0] + (1 - a / 2) * (a % 2 * 2 - 1)][(GLint)monster[i][1] + (a / 2) * (a % 2 * 2 - 1)][(GLint)monster[i][2] + playjump] == 0 && (GLint)monster[i][1] + (a / 2) * (a % 2 * 2 - 1) < y && (GLint)monster[i][1] + (a / 2) * (a % 2 * 2 - 1) >= 0)
							{
								monster[i][0] += (1 - a / 2) * (a % 2 * 2 - 1);
								monster[i][1] += (a / 2) * (a % 2 * 2 - 1);
								playerjump((gamemap[(GLint)monster[i][7]]).block[(GLint)monster[i][0]][(GLint)monster[i][1]], monster[i][2]);
							}
							else
							{
								a = randstep(monster[i][0], monster[i][1], monster[i][2], monster[i][6], emonster[i].monstert[6]);
								monster[i][6] = a;

								// ?
								monster[i][0] += (1 - a / 2) * (a % 2 * 2 - 1);
								monster[i][1] += (a / 2) * (a % 2 * 2 - 1);
								playerjump((gamemap[(GLint)monster[i][7]]).block[(GLint)monster[i][0]][(GLint)monster[i][1]], monster[i][2]);
							}
							//go to way
							break;
						case 2: // not work
							// go to player
							//cout << 0 << i << '\n';
							/*if (monster[i][7] == actmap && max(max(playpos[0], monster[i][0]) - min(playpos[0], monster[i][0]), max(playpos[1], monster[i][1]) - min(playpos[1], monster[i][1])) <= wayrange)
							{
								//cout << 2;
								a = way(makegraph(monstert[(GLint)monster[i][4]][6], (GLint)monster[i][7], monster[i][0], monster[i][1]),
									(GLint)(monster[i][0] * y + monster[i][1]), (GLint)(playpos[0] * y + playpos[1]));
								//cout << 0;
								//cout << '\n' << monster[i][0] << ' ' << monster[i][1] << ' ' << a << '\n';
								cout << a;
								if (a == -1)
								{
									goto gtnomonsterway;
								}
								else
								{
									monster[i][1] = a / y;
									monster[i][0] = a % y;
								}
							}
							else
							{
								gtnomonsterway:;
								goto gtmonsterway1;
							} */
							break; // not work
						default:
							break;
						}
					}
					else
					{
						if (mshortway(gamemap[(GLint)monster[i][7]].mainmonsterpos[0], gamemap[(GLint)monster[i][7]].mainmonsterpos[1], i) == false)
						{
							// effects
						}
					}
					//(gamemap[(GLint)monster[i][7]]).map[(GLint)monster[i][0]][(GLint)monster[i][1]][6] = i + 1;
				}
			}
			(gamemap[(GLint)monster[i][7]]).map[(GLint)monster[i][0]][(GLint)monster[i][1]][6] = i + 1;
			emonster[i].mstepl = 0;
		}
		else
		{
			emonster[i].mstepl++;
		}
	}
}

void monstermove2(GLint i)
{
	if (levelpos[(GLint)monster[i][7]] == 1)
	{
		if (emonster[i].effect[0][0] == 0)
		{
			if (emonster[i].effect[1][1] <= emonster[i].mstepl)
			{
				gamemap[(GLint)monster[i][7]].map[(GLint)monster[i][0]][(GLint)monster[i][1]][6] = 0;
				GLint a = 0;
				bool c = false;
				pair<GLint, GLint> b;
				switch (emonster[i].monstert[2])
				{
				case 3: // destroy towers
				case 4:
					a = findtowerinrange(i);
					if (a != -1)
					{
						c = true;
						b = shortway(monster[i][0], monster[i][1], monster[i][2], playtower[a].posx, playtower[a].posy, monster[i][7], c);
						if (!c)
						{
							emonster[i].dwall = 0;
							monster[i][0] += b.first;
							monster[i][1] += b.second;
							playerjump(gamemap[(GLint)monster[i][7]].block[(GLint)monster[i][0]][(GLint)monster[i][1]], monster[i][2]);
						}
						else
						{
							if (emonster[i].monstert[8] >= 0)
							{
								monsterbreakwall(i, b);
							}
							// add timer
							// delete wall
						}
						break;
					}
				case 5: // move to main tower
				case 6:
					a = gamemap[(GLint)monster[i][7]].map[x / 2][y / 2][8] - 1;
					if (a >= 0)
					{
						c = true;
						b = shortway(monster[i][0], monster[i][1], monster[i][2], playtower[a].posx, playtower[a].posy, monster[i][7], c);
						if (!c)
						{
							emonster[i].dwall = 0;
							monster[i][0] += b.first;
							monster[i][1] += b.second;
							// add new pos to monster
							playerjump(gamemap[(GLint)monster[i][7]].block[(GLint)monster[i][0]][(GLint)monster[i][1]], monster[i][2]);
						}
						else
						{
							if (emonster[i].monstert[8] >= 0)
							{
								monsterbreakwall(i, b);
							}
							// add timer
							// delete wall
						}
					}
					break;
				default:
					break;
				}
				gamemap[(GLint)monster[i][7]].map[(GLint)monster[i][0]][(GLint)monster[i][1]][6] = i + 1;
				emonster[i].mstepl = 0;
			}
			else
			{
				emonster[i].mstepl++;
			}
		}
	}
	else
	{
		cout << monster[i][7] << '\n' << levelpos[(GLint)monster[i][7]] << '\n' << '\n';
		monster[i][3] = 0;
	}
}

void monstermove3(GLint i, GLint monstertowern)
{
	GLint a = 0;
	monstermove1(i, monstertowern, a, false);
}

void monsterstep()
{
	GLint a = 0;
	for(GLint i = 0; i < monster.size(); i++)
	{
		switch((GLint)monster[i][8])
		{
		case 0:
			if (monster[i][7] == actmap)
			{
				delmonster(true, i);
				if (i >= monster.size())
				{
					goto gtmonsterm;
				}
				firstmonsteratackp(i, true);
				mgametime = glutGet(GLUT_ELAPSED_TIME);
				if (addtime || (mgametime >= monster[i][9] + 1000 / emonster[i].monstert[0]))
				{
					monster[i][9] = mgametime;
					mtoweratack(i);
					GLint monstertowern = findtowerinrange(i);
					monsteratackp(i, true);
					monstermove1(i, monstertowern, a, true);
					meffect(i);
				}
			}
			break;
		case 1:
			delmonster(false, i);
			if (i >= monster.size())
			{
				goto gtmonsterm;
			}
			firstmonsteratackp(i, false);
			mgametime = glutGet(GLUT_ELAPSED_TIME);
			if (addtime || (mgametime >= monster[i][9] + 1000 / emonster[i].monstert[0]))
			{
				monster[i][9] = mgametime;
				mtoweratack(i);
				monsteratackp(i, false);
				monstermove2(i);
				meffect(i);
			}
			// monster attack (main tower)
			break;
		case 2:
			delmainmonster(i);
			firstmonsteratackp(i, true);
			mgametime = glutGet(GLUT_ELAPSED_TIME);
			if (addtime || (mgametime >= monster[i][9] + 1000 / emonster[i].monstert[0]))
			{
				monster[i][9] = mgametime;
				monsteratackp(i, true);
				GLint monstertowern = findtowerinrange(i);
				monstermove3(i, monstertowern);
				meffect(i);
			}
			break;
		default:
			break;
		}
	}
	gtmonsterm:;
}

void addmonsterstep()
{
	if (addtime)
	{
		for (GLint i = 0; i < levelsnum; i++)
		{
			if (ngmmonster[i] >= ngmmonstert)
			{
				addmonster(i, gamemap[i].mainmonsterpos[0], gamemap[i].mainmonsterpos[1] , 2, max(i - baselevel, baselevel - i) + 2);
				levelmainm[i] = 2;
				ngmmonster[i] = 0;
				// gen main monster
			}
			if (levelmainm[i] == 1)
			{
				ngmmonster[i]++;
			}
		}
		mtime++;
	}
	if (mtime >= max(mlevelgen[0][0] + mlevelgen[0][1] * max(actmap - baselevel, baselevel - actmap), mlevelgen[0][2]))
	{
		//cout << max(mlevelgen[0][0] + mlevelgen[0][1] * max(actmap - baselevel, baselevel - actmap), mlevelgen[0][2]) << ' ';
		initmonster(1000, min(mlevelgen[1][0] + mlevelgen[1][1] * max(actmap - baselevel, baselevel - actmap), mlevelgen[1][2]), actmap, monsterp);
		mtime = 0;
	}
}

void deltower(GLint i)
{
	gamemap[playtower[i].tlevel].map[playtower[i].posx][playtower[i].posy][8] = 0;
	gamemap[playtower[i].tlevel].map[playtower[i].posx][playtower[i].posy][7] = 0;
	for (GLint j = 0; j < z; j++)
	{
		freeblock(playtower[i].tlevel, playtower[i].posx, playtower[i].posy, j);
		gamemap[playtower[i].tlevel].block[playtower[i].posx][playtower[i].posy][j] = 0;
	}
	freetrap(playtower[i].tlevel, playtower[i].posx, playtower[i].posy);
	for (GLint j = 0; j < deep; j++)
	{
		gamemap[playtower[i].tlevel].block[playtower[i].posx][playtower[i].posy][j] = 2;
	}
	if (i != playtower.size() - 1)
	{
		swap(playtower[i], playtower.back());
		gamemap[playtower[i].tlevel].map[playtower[i].posx][playtower[i].posy][8] = i + 1; // ?? +1
	}
	playtower.pop_back();
}
// ??

void addtonum(GLint &k, GLint a)
{
	k++;
	if (k >= a)
	{
		k = 0;
	}
}

void towerstep()
{
	GLint k = 0;
	atowerbuf.clear();
	atowerbuf.resize(playtower.size());
	bool b = false;
	bool c = false;
	if(addtime)
	{
		b = false;
		for (GLint i = 0; i < playtower.size(); i++)
		{
			GLint d = 0;
			atowerbuf[i].resize(z);
			if (playtower[i].tlevel == actmap)
			{
				b = true;
			}
			vector<GLint> etowermonster;
			for (GLint j = 0; j < playtower[i].towerb.size(); j++)
			{
				if (playtower[i].towerb[j].a.pef[0][3] >= playtower[i].towerb[j].a.pef[0][4])
				{
					d += playtower[i].towerb[j].a.pef[0][0];
					playtower[i].tparam[2][0] += playtower[i].towerb[j].a.pef[0][0];
					playtower[i].towerb[j].a.pef[0][3] = 0;
				}
				else
				{
					playtower[i].towerb[j].a.pef[0][3]++;
				}
			}
			if (d > 0)
			{
				partnum pn1(-i - 1, 1, d);
				mpartnum.push_back(pn1);
			}
			if (playtower[i].tparam[2][0] >= playtower[i].maxttimer)
			{
				playtower[i].tparam[2][0] = playtower[i].maxttimer;
			}
			//cout << playtower[i].tparam[2][0] << ' ';
			if (playtower[i].tparam[2][0] <= 0)
			{
				deltower(i);
				if (i == playtower.size())
				{
					break;
				}
			}
			for (GLint j = 0; j < monster.size(); j++)
			{
				if (max(max(monster[j][0] - playtower[i].posx, playtower[i].posx - monster[j][0]), max(monster[j][1] - playtower[i].posy, playtower[i].posy - monster[j][1])) <= playtower[i].tparam[1][0] && monster[j][7] == playtower[i].tlevel && (monster[j][8] == 1 || (monster[j][7] == actmap && monster[j][8] != 2)))
				{
					// can attack main monster ???
					etowermonster.push_back(j);
					/*if (etowermonster.size() <= 1)
					{
						monster[j][3] -= playtower[i].tparam[0][0] * shildconst / (shildconst + emonster[j].monstert[4]);
					}*/
				}
			}
			if (etowermonster.size() > 0)
			{
				for (GLint j = 0, k = 0; j < playtower[i].towerb.size(); j++)
				{
					GLint d = playtower[i].towerb[j].a.attack * shildconst / (shildconst + emonster[etowermonster[k]].monstert[4]);
					c = true;
					if (rand() % 100 < playtower[i].towerb[j].a.edel)
					{
						monster[etowermonster[k]][3] = 0;
						if (monster[etowermonster[k]][3] > 0 && b)
						{
							atowerbuf[i][playtower[i].towerb[j].posz].push_back(etowermonster[k]);
						}
						addtonum(k, etowermonster.size());
					}
					if (d > 0)
					{
						partnum pn1(etowermonster[k] + 1, 0, d);
						mpartnum.push_back(pn1);
					}
					monster[etowermonster[k]][3] -= d;
					if (monster[etowermonster[k]][3] > 0 && b)
					{
						atowerbuf[i][playtower[i].towerb[j].posz].push_back(etowermonster[k]);
					}
					c = false;
					if (monster[etowermonster[k]][3] <= 0)
					{
						addtonum(k, etowermonster.size());
						c = true;
					}
					for (GLint k2 = 0; k2 < trapattackn; k2++)
					{
						if (playtower[i].towerb[j].a.ef[k2][3] >= playtower[i].towerb[j].a.ef[k2][4])
						{
							if (rand() % 100 < playtower[i].towerb[j].a.ef[k2][1])
							{
								emonster[etowermonster[k]].effect[k2][0] += playtower[i].towerb[j].a.ef[k2][2];
								emonster[etowermonster[k]].effect[k2][1] = max(playtower[i].towerb[j].a.ef[k2][0], emonster[etowermonster[k]].effect[k2][1]);
								if (monster[etowermonster[k]][3] > 0 && b)
								{
									atowerbuf[i][playtower[i].towerb[j].posz].push_back(etowermonster[k]);
								}
								c = false;
							}
						}
						else
						{
							playtower[i].towerb[j].a.ef[k2][3]++;
						}
					}
					addtonum(k, etowermonster.size());
				}
			}
		}
	}
}

// can attack main monster ???
void loadtexture()
{
	GLint i = 0; // LPCSTR (glaux)
	char *a[texturenum] = {"data/nothing.bmp", "data/pt1.bmp",
		"data/pt2.bmp", "data/pt3.bmp", "data/pt4.bmp",
		"data/pt5.bmp", "data/pt6.bmp", "data/pt7.bmp",
		"data/inst1.bmp", "data/inst2-1.bmp", "data/w0.bmp",
		"data/w1.bmp", "data/w2.bmp", "data/w3.bmp", "data/w4.bmp", "data/w5.bmp",
		"data/thing0-0.bmp", "data/material.bmp", "data/cr1.bmp", "data/potion1.bmp",
		"data/thing0-6.bmp", "data/thing0-7.bmp", "data/thing0-8.bmp",
		"data/coin1.bmp", "data/mthing.bmp", "data/wood6.bmp",  "data/tower1.bmp",
		"data/tower3.bmp", "data/createt.bmp", "data/chest.bmp",
		"data/stone3.bmp", "data/stone6.bmp", "data/stone8.bmp",
		"data/stone10.bmp", "data/menut3.bmp"};
	//AUX_RGBImageRec *addtexture; (glaux)
	for (i = 0; i < texturenum; i++)
	{
		int imagepos = 0, imagew = 0, imageh = 0, imagesize = 0;
		unsigned char imagedata_s[54];
		unsigned char *imagedata;
		FILE *imagefile = fopen(a[i], "rb");
		fread (imagedata_s, sizeof(char), 54, imagefile);
		imagew = *(int*)&(imagedata_s[0x12]);
		imageh = *(int*)&(imagedata_s[0x16]);
		imagesize = *(int*)&(imagedata_s[0x22]);
		imagepos = *(int*)&(imagedata_s[0x0A]);
		if (imagesize == 0)
		{
			imagesize = imagew * imageh * 4;// RGBA
		}
		if (imagepos == 0)
		{
			imagepos = 54;
		}
		imagedata = (unsigned char*)malloc(imagesize * sizeof(unsigned char));
		fread (imagedata, sizeof(char), imagesize, imagefile);
		for (GLint i = 0; (i + 2) < imagesize; i+=4)
		{
			swap(imagedata[i], imagedata[i + 2]);
		}
		fclose(imagefile);
		glGenTextures(1, &texture[i]);
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, imagew, imageh, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagedata);
		free(imagedata);
		/*ILuint textimage;(DevIL)
		ilGenImages(1, &textimage);
		ilBindImage(textimage);
		ilLoadImage(a[i]);
		//cout << i;
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		// T - IL_BMP, IL_PNG, IL_JPG
		// reinterpret_cast<const ILstring> - convert name to ILstring
		GLint textw = ilGetInteger(IL_IMAGE_WIDTH);
		GLint texth = ilGetInteger(IL_IMAGE_HEIGHT);
		//unsigned int texttype = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
		unsigned char *textdata = ilGetData();
		glGenTextures(1, &texture[i]);
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textw, texth, 0, GL_RGBA, GL_UNSIGNED_BYTE, textdata);
		ilDeleteImages(1, &textimage);*/
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexImage2D (GL_TEXTURE_2D, 0, 4, textw, texth, 0, texttype, GL_UNSIGNED_BYTE, textdata);
		//gluBuild2DMipmaps(GL_TEXTURE_2D, texttype, textw, texth, GL_UNSIGNED_BYTE, texttype, textdata);
		/*addtexture = auxDIBImageLoad (a[i]); (glaux)
		glGenTextures (1, &texture[i]);
		glBindTexture (GL_TEXTURE_2D, texture[i]);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR ; GL_NEAREST
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_LINEAR ; GL_NEAREST
		glTexImage2D (GL_TEXTURE_2D, 0, 4, addtexture->sizeX, addtexture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, addtexture->data);*/
	}
}

void outobj(obj a)
{
	text(" \nattack: ");
	text(a.attack);
	text(" bn: ");
	text(a.bn);
	text(" \nt2: ");
	text(a.t2);
	text(" dist: ");
	text(a.dist);
	text(" \nedel: ");
	text(a.edel);
	text(" effects: \n");
	for (GLint k2 = 0; k2 < trapattackn; k2++)
	{
		for (GLint k3 = 0; k3 < efsize; k3++)
		{
			text(" ");
			text(a.ef[k2][k3]);
		}
		text("\n");
	}
	text(" live: ");
	text(a.live);
	text(" mpoints: ");
	text(a.mpoints);
	//c >> (*b).name; // ?
	text(" \npeffects: \n");
	for (GLint k2 = 0; k2 < peffectnum; k2++)
	{
		for (GLint k3 = 0; k3 < pefsize; k3++)
		{
			text(" ");
			text(a.pef[k2][k3]);
		}
		text("\n");
	}
	text(" points: ");
	text(a.points);
	text(" range: ");
	text(a.range);
	//text(" \nrare: ");
	//text(a.rare);
	text(" \nshield: ");
	text(a.shield);
	text(" size: ");
	text(a.size);
	text(" \nt: ");
	text(a.t);
	text(" texture: ");
	text(a.text);
	//text(" timer: ");
	//text(a.timer);
	text(" \ntype: ");
	switch(a.type)
	{
		case 0:
			switch(a.t2)
			{
			case 0:
				text("thing");
				break;
			case 1:
				text("material");
				break;
			case 2:
				text("crystal element");
				break;
			case 3:
				text("crystal");
				break;
			case 4:
				text("thing"); // ??
				break;
			case 5:
				text("wood");
				break;
			case 6:
				text("handle");
				break;
			case 7:
				text("arrow");
				break;
			case 8:
				text("stick");
				break;
			case 9:
				text("magic thing");
				if (a.wtype != 0)
				{
					text("\nfor complete level ");
					text((a.wtype - 1));
				}
				break;
			default:
				break;
			}
			break;
		case 1:
			text("boots");
			break;
		case 2:
			text("pants");
			break;
		case 3:
			text("belt");
			break;
		case 4:
			text("jacket");
			break;
		case 5:
			text("shield");
			break;
		case 6:
			text("bag");
			break;
		case 7:
			text("hat");
			break;
		case 8:
			text("instrument");
			break;
		case 9:
			text("break instrument");
			break;
		case 10:
			text("weapon");
			break;
		case 11:
			text("create table");
			break;
		case 12:
			text("chest");
			break;
		case 13:
			text("instrument for create");
			break;
		case 14:
			text("trap");
			break;
		case 25:
			text("door");
			break;
		case 26:
			text("main tower block");
			break;
		case 27:
			text("add tower block");
			break;
		case 28:
			text("coin");
			break;
		case 29:
			text("potion");
			break;
		case 30:
			text("coin part");
			break;
		default:
			text("trap");
			break;
	}
	//text(a.type); // remake
	if (a.type == 10)
	{
		text("\n wtype: ");
		switch(a.wtype)
		{
		case 0:
			text("knight");
			break;
		case 1:
			text("spear");
			break;
		case 2:
			text("mace");
			break;
		case 3:
			text("bow");
			break;
		case 4:
			text("arbalest");
			break;
		case 5:
			text("magic"); // ??
			break;
		default:
			break;
		}
	}
	else
	{
		if (a.type == 26 && a.wtype != 0)
		{
			text("\nlevel: ");
			text(a.wtype);
		}
	}
}

void saveobj(obj *a, GLint *buf, GLint *it)
{
	buf[*it] = (*a).attack;
	(*it)++;
	buf[*it] = (*a).bn;
	(*it)++;
	buf[*it] = (*a).t2;
	(*it)++;
	buf[*it] = (*a).color[0];
	(*it)++;
	buf[*it] = (*a).color[1];
	(*it)++;
	buf[*it] = (*a).color[2];
	(*it)++;
	buf[*it] = (*a).dist;
	(*it)++;
	buf[*it] = (*a).edel;
	(*it)++;
	for (GLint i = 0; i < trapattackn; i++)
	{
		for (GLint j = 0; j < efsize; j++)
		{
			buf[*it] = (*a).ef[i][j];
			(*it)++;
		}
	}
	buf[*it] = (*a).live;
	(*it)++;
	buf[*it] = (*a).mpoints;
	(*it)++;
	/*buf[*it] = (*a).name.size();
	(*it)++;
	for (GLint i = 0; i < (*a).name.size(); i++)
	{
		buf[*it] = (GLint)(*a).name[i];
		(*it)++;
	}*/
	for (GLint i = 0; i < trapattackn; i++)
	{
		for (GLint j = 0; j < pefsize; j++)
		{
			buf[*it] = (*a).pef[i][j];
			(*it)++;
		}
	}
	buf[*it] = (*a).points;
	(*it)++;
	buf[*it] = (*a).range;
	(*it)++;
	buf[*it] = (*a).rare;
	(*it)++;
	buf[*it] = (*a).shield;
	(*it)++;
	buf[*it] = (*a).size;
	(*it)++;
	buf[*it] = (*a).t;
	(*it)++;
	buf[*it] = (*a).text;
	(*it)++;
	buf[*it] = (*a).timer;
	(*it)++;
	buf[*it] = (*a).type;
	(*it)++;
	buf[*it] = (*a).wtype;
	(*it)++;
}

void loadobj(obj *a, GLint *buf, GLint *it)
{
	GLint b = 0;
	(*a).attack = buf[*it];
	(*it)++;
	(*a).bn = buf[*it];
	(*it)++;
	(*a).t2 = buf[*it];
	(*it)++;
	(*a).color[0] = buf[*it];
	(*it)++;
	(*a).color[1] = buf[*it];
	(*it)++;
	(*a).color[2] = buf[*it];
	(*it)++;
	(*a).dist = buf[*it];
	(*it)++;
	(*a).edel = buf[*it];
	(*it)++;
	for (GLint i = 0; i < trapattackn; i++)
	{
		for (GLint j = 0; j < efsize; j++)
		{
			(*a).ef[i][j] = buf[*it];
			(*it)++;
		}
	}
	(*a).live = buf[*it];
	(*it)++;
	(*a).mpoints = buf[*it];
	(*it)++;
	/*b = buf[*it];
	(*it)++;
	(*a).name.resize(b, '-');
	for (GLint i = 0; i < (*a).name.size(); i++)
	{
		(*a).name[i] = (char)buf[*it];
		(*it)++;
	}*/
	for (GLint i = 0; i < trapattackn; i++)
	{
		for (GLint j = 0; j < pefsize; j++)
		{
			(*a).pef[i][j] = buf[*it];
			(*it)++;
		}
	}
	(*a).points = buf[*it];
	(*it)++;
	(*a).range = buf[*it];
	(*it)++;
	(*a).rare = buf[*it];
	(*it)++;
	(*a).shield = buf[*it];
	(*it)++;
	(*a).size = buf[*it];
	(*it)++;
	(*a).t = buf[*it];
	(*it)++;
	(*a).text = buf[*it];
	(*it)++;
	(*a).timer = buf[*it];
	(*it)++;
	(*a).type = buf[*it];
	(*it)++;
	(*a).wtype = buf[*it];
	(*it)++;
}

void savef()
{
	GLint *savebuf;
	char *sname = (char*) malloc((savename.size() + 1) * sizeof(char));
	for (GLint i = 0; i < savename.size(); i++)
	{
		sname[i] = savename[i];
	}
	sname[savename.size()] = 0;
	savebuf = (GLint*) malloc(sizeof(GLint) * savebufsize);
	FILE *f = fopen(sname, "wb");
	GLint it = 0;
	//taket[0] = 0;
	//menus = 0;
	for (GLint i = 0; i < peffectnum; i++)
	{
		savebuf[it] = playeffect[i][0];
		it++;
		savebuf[it] = playeffect[i][1];
		it++;
	}
	for (GLint i = 0; i < trapattackn; i++)
	{
		savebuf[it] = trapattack[i][0];
		it++;
		savebuf[it] = trapattack[i][1];
		it++;
	}
	savebuf[it] = levelsnum;
	it++;
	savebuf[it] = live;
	it++;
	savebuf[it] = actmap;
	it++;
	savebuf[it] = m1.minmap[0];
	it++;
	savebuf[it] = m1.minmap[1];
	it++;
	savebuf[it] = playpos[0];
	it++;
	savebuf[it] = playpos[1];
	it++;
	savebuf[it] = playpos[2];
	it++;
	savebuf[it] = playermp;
	it++;
	savebuf[it] = playerlevel;
	it++;
	savebuf[it] = levelp;
	it++;
	savebuf[it] = playlevel[0];
	it++;
	savebuf[it] = playlevel[1];
	it++;
	savebuf[it] = viewt[0];
	it++;
	savebuf[it] = viewt[1];
	it++;
	savebuf[it] = viewt[2];
	it++;
	savebuf[it] = viewr[0];
	it++;
	savebuf[it] = viewr[1];
	it++;
	savebuf[it] = viewr[2];
	it++;
	savebuf[it] = viewrotate;
	it++;
	/*for (GLint i = 0; i < trapattackn; i++)
	{
		savebuf[it] = trapattack[i][0];
		it++;
		savebuf[it] = trapattack[i][1];
		it++;
	}*/
	savebuf[it] = monster.size();
	it++;
	for (GLint i = 0; i < monster.size(); i++)
	{
		savebuf[it] = monster[i].size();
		it++;
		for (GLint j = 0; j < monster[i].size(); j++)
		{
			savebuf[it] = monster[i][j];
			it++;
		}
	}
	fwrite(savebuf, sizeof(GLint), it, f);
	it = 0;
	savebuf[it] = emonster.size();
	it++;
	for (GLint i = 0; i < emonster.size(); i++)
	{
		savebuf[it] = emonster[i].dwall;
		it++;
		savebuf[it] = emonster[i].mstepl;
		it++;
		for (GLint j = 0; j < trapattackn; j++)
		{
			savebuf[it] = emonster[i].effect[j][0];
			it++;
			savebuf[it] = emonster[i].effect[j][1];
			it++;
		}
		for (GLint j = 0; j < monstersize; j++)
		{
			savebuf[it] = emonster[i].monstert[j];
			it++;
		}
		savebuf[it] = emonster[i].bigeffect.size();
		it++;
		for(GLint j = 0; j < emonster[i].bigeffect.size(); j++)
		{
			savebuf[it] = emonster[i].bigeffect[j].size();
			it++;
			for (GLint k = 0; k < emonster[i].bigeffect[j].size(); k++)
			{
				savebuf[it] = emonster[i].bigeffect[j][k];
				it++;
			}
		}
	}
	fwrite(savebuf, sizeof(GLint), it, f);
	it = 0;
	savebuf[it] = playtower.size();
	it++;
	for (GLint i = 0; i < playtower.size(); i++)
	{
		savebuf[it] = playtower[i].posx;
		it++;
		savebuf[it] = playtower[i].posy;
		it++;
		savebuf[it] = playtower[i].tlevel;
		it++;
		savebuf[it] = playtower[i].maxttimer;
		it++;
		for (GLint j = 0; j < tparamnum; j++)
		{
			for (GLint k = 0; k < 3; k++)
			{
				savebuf[it] = playtower[i].tparam[j][k];
				it++;
			}
		}
		savebuf[it] = playtower[i].towerb.size();
		it++;
		for (GLint j = 0; j < playtower[i].towerb.size(); j++)
		{
			saveobj(&playtower[i].towerb[j].a, savebuf, &it);
			savebuf[it] = playtower[i].towerb[j].posx;
			it++;
			savebuf[it] = playtower[i].towerb[j].posy;
			it++;
			savebuf[it] = playtower[i].towerb[j].posz;
			it++;
		}
	}
	fwrite(savebuf, sizeof(GLint), it, f);
	it = 0;
	savebuf[it] = playchange.size();
	it++;
	for (GLint i = 0; i < playchange.size(); i++)
	{
		savebuf[it] = playchange[i].sale.size();
		it++;
		savebuf[it] = playchange[i].poslevel;
		it++;
		savebuf[it] = playchange[i].posx;
		it++;
		savebuf[it] = playchange[i].posy;
		it++;
		savebuf[it] = playchange[i].posz;
		it++;
		savebuf[it] = playchange[i].type;
		it++;
		for (GLint j = 0; j < playchange[i].sale.size(); j++)
		{
			savebuf[it] = playchange[i].sale[j].n;
			it++;
			saveobj(&playchange[i].sale[j].b, savebuf, &it);
			savebuf[it] = playchange[i].sale[j].nb;
			it++;
			savebuf[it] = playchange[i].sale[j].ns;
			it++;
			saveobj(&playchange[i].sale[j].s, savebuf, &it);
			savebuf[it] = playchange[i].sale[j].up;
			it++;
		}
	}
	fwrite(savebuf, sizeof(GLint), it, f);
	it = 0;
	saveobj(&phand[0], savebuf, &it);
	saveobj(&phand[1], savebuf, &it);
	for (GLint i = 0; i < 7; i++)
	{
		saveobj(&pt[i], savebuf, &it);
	}
	for (GLint i = 0; i < pmx; i++)
	{
		for (GLint j = 0; j < pmy + 3; j++)
		{
			saveobj(&pb[i][j], savebuf, &it);
		}
	}
	fwrite(savebuf, sizeof(GLint), it, f);
	it = 0;
	for (GLint i = 0; i < levelsnum; i++)
	{
		savebuf[it] = gamemap[i].addtochesttimer;
		it++;
		savebuf[it] = ngmmonster[i];
		it++;
		savebuf[it] = levelpos[i];
		it++;
		savebuf[it] = levelmainm[i];
		it++;
		savebuf[it] = mapsizexy[i][0];
		it++;
		savebuf[it] = mapsizexy[i][1];
		it++;
		for (GLint j = 0; j < mapsizexy[i][0]; j++)
		{
			for (GLint j2 = 0; j2 < mapsizexy[i][1]; j2++)
			{
				for (GLint k = 0; k < sizemap; k++)
				{
					savebuf[it] = gamemap[i].map[j][j2][k];
					it++;
				}
			}
			fwrite(savebuf, sizeof(GLint), it, f);
			it = 0;
		}
		//fwrite(savebuf, sizeof(GLint), it, f);
		//it = 0;
		for (GLint j = 0; j < mapsizexy[i][0]; j++)
		{
			for (GLint j2 = 0; j2 < mapsizexy[i][1]; j2++)
			{
				for (GLint j3 = 0; j3 < z; j3++)
				{
					savebuf[it] = gamemap[i].block[j][j2][j3];
					it++;
				}
			}
			fwrite(savebuf, sizeof(GLint), it, f);
			it = 0;
		}
		//fwrite(savebuf, sizeof(GLint), it, f);
		//it = 0;
		savebuf[it] = gamemap[i].chest.size();
		it++;
		for (GLint j = 0; j < gamemap[i].chest.size(); j++)
		{
			for (GLint k = 0; k < chmaxnum; k++)
			{
				saveobj(&gamemap[i].chest[j][k], savebuf, &it);
			}
			fwrite(savebuf, sizeof(GLint), it, f);
			it = 0;
		}
		savebuf[it] = gamemap[i].mblock.size();
		it++;
		for (GLint j = 0; j < gamemap[i].mblock.size(); j++)
		{
			saveobj(&gamemap[i].mblock[j].a, savebuf, &it);
			savebuf[it] = gamemap[i].mblock[j].posx;
			it++;
			savebuf[it] = gamemap[i].mblock[j].posy;
			it++;
			savebuf[it] = gamemap[i].mblock[j].posz;
     		it++;
			if (j % 1000 == 999)
			{
				fwrite(savebuf, sizeof(GLint), it, f);
				it = 0;
			}
		}
		for (GLint j = 0; j < 4; j++)
		{
			savebuf[it] = levelwavetimer[i][j];
     		it++;
		}
		fwrite(savebuf, sizeof(GLint), it, f);
		it = 0;
		//cout << ' ' << (i + 1);
	}
	//fwrite(a, sizeof(GLint), it, f);
	//it = 0;
	free(savebuf);
	free(sname);
	fclose(f);
	cout << "\nsaved\n";
} // remake

void newgame()
{
	pfirstmove = 0;
	mpartnum.clear();
	pmovetimer = 0;
	menus3 = 0;
	ampos = 0.0f;
	menus2 = 0;
	amenu = 0;
	animtimer = 0;
	amact = 0;
	atowerbuf.clear();
	ctformulmove = 0;
	ctformultimer = 0;
	gamewin = false;
	startmenu = false;
	viewrotate = false;
	viewt[0] = 0.0f;
	viewt[1] = 0.0f;
	viewt[2] = 0.0f;
	viewr[0] = 0.0f;
	viewr[1] = 0.0f;
	viewr[2] = 0.0f;
	//actmap = 0;
	actmap = levelsnum / 2;
	x = mapsizexy[actmap][0];
	y = mapsizexy[actmap][1];
	newcreatem();
	mgametime = 0;
	playerlevel = 0;
	levelp = 0;
	baselevel = levelsnum / 2;
	playlevel[0] = levelconst;
	playlevel[1] = levelconst;
	handtimer[0] = 0;
	handtimer[1] = 0;
	GLint playeffect2[peffectnum][2] = {{0, 0}, {0, 0}, {0, 0}};
	GLint trapattack2[trapattackn][2] = {{0, 0}, {0, 0}, {0, 0}};
	for (GLint i = 0; i < trapattackn; i++)
	{
		trapattack[i][0] = trapattack2[i][0];
		trapattack[i][1] = trapattack2[i][1];
	}
	for (GLint i = 0; i < peffectnum; i++)
	{
		playeffect[i][0] = playeffect2[i][0];
		playeffect[i][1] = playeffect2[i][1];
	}
	addtime = false;
	gametime = 0;
	dtime = 0;
	atackmode = false;
	atackview = false;
	startresettimer();
	for (GLint i = 0; i < 4; i++)
	{
		pattackrange[i] = 0;
		atackkey[i] = false;
	}
	pause = false;
	pause2 = false;
	consol = false;
	speed = 0;
	live = maxlive;
	shild = 0;
	hand = 0;
	for (GLint i = 0; i < 9; i++)
	{
		mbutton[i] = false;
	}
	tb.first = 0;
	tb.second.type = -1;
	for (GLint i = 0; i < 3; i++)
	{
		mb[i] = false;
	}
	for(GLint i = 0; i < createnum; i++)
	{
		mcreate[i].type = -1;
	}
	taketsize = 0; //take things
	takem = false; // take menu
	mp[0] = 0;
	mp[1] = 0; // mouse position
	//wp[0] = 800;
	//wp[1] = 600; //window param
	maxy = 0;
	maxx = 0;
	gamey = 0;
	gamex = 0;
	menus = 0; // menu status
	playpos[0] = x / 2;
	playpos[1] = y / 2;
	playpos[2] = deep;
	playmove[0] = 0.0f;
	playmove[1] = 0.0f;
	playmove[2] = 0.0f;
	opentable = 0;
	openchest = 0;
	openchest2 = false;
	pmove = 0;
	levelpause = false;
	monster.clear();
	emonster.clear();
	//GLint createmtime2[levelsnum][3][2] = {{{20, 0}, {2, 0}, {0, 0}}}; // time from wave to wave, length of wave, time of gen monsters in wave;
	//GLint createmrandmax2[levelsnum][4] = {{100, 0, 0, 0}}; // max rand for monster, add to max rand, rand no monsters, add to rand no monsters
	//GLint createmrand2[levelsnum][monsternum][2] = {{{0, 0}, {0, 0}, {100, 0}}}; // rand for monster, add for monster rand
	for (GLint i = 0; i < levelsnum; i++)
	{
		levelpos[i] = 0;
		for (GLint j = 0; j < 4; j++)
		{
			levelwavetimer[i][j] = 0;
		}
	}
	mtime = 0;
	playchange.clear();
	playtower.clear();
	savename = "autosave.gamesave";
	loadname = "autosave.gamesave";
	salenum = 0;
	openchange = 0;
	moneynum = 0;
	printc = false;
	menusaveload = false;
	menuinputs.clear();
	menur[0] = 0;
	menur[1] = 0;
	cht = 0; // chest thing
	dtime = time(NULL);
	playwin = false;
	for(GLint i = 0; i < levelsnum; i++)
	{
		x = mapsizexy[i][0];
		y = mapsizexy[i][1];
		levelmainm[i] = -1;
		ngmmonster[i] = 0;
		levelpos[i] = 0;
		cout << 1;
		gamemap[i].initmap(i, max(0, i - baselevel) * 10, max(0, i - baselevel) * 400, max(0, i - baselevel) * 1, max(0, baselevel - i) * 100);
		cout << 2;
		initmarket(i, 1000, 1);
		initmonster(1000, min(mlevelgen[1][0] + mlevelgen[1][1] * max(i - baselevel, baselevel - i), mlevelgen[1][2]), i);
	}
	x = mapsizexy[actmap][0];
	y = mapsizexy[actmap][1];
	startinitplayer();
	gfirstinit = true;
}

void newmgame()
{
	pfirstmove = 0;
	mpartnum.clear();
	pmovetimer = 0;
	menus3 = 0;
	ampos = 0.0f;
	menus2 = 0;
	amenu = 0;
	animtimer = 0;
	amact = 0;
	atowerbuf.clear();
	//savename = "autosave.gamesave";
	//savef();
	ctformulmove = 0;
	ctformultimer = 0;
	gamewin = false;
	playerlevel = 0;
	levelp = 0;
	playlevel[0] = levelconst;
	playlevel[1] = levelconst;
	startmenu = false;
	//actmap = 0;
	actmap = levelsnum / 2;
	GLint mgametime = 0;
	handtimer[0] = 0;
	handtimer[1] = 0;
	addtime = false;
	gametime = 0;
	dtime = 0;
	atackmode = false;
	atackview = false;
	for (GLint i = 0; i < 4; i++)
	{
		pattackrange[i] = 0;
		atackkey[i] = false;
	}
	pause = false;
	pause2 = false;
	consol = false;
	speed = 0;
	live = maxlive;
	shild = 0;
	hand = 0;
	for (GLint i = 0; i < 9; i++)
	{
		mbutton[i] = false;
	}
	tb.first = 0;
	tb.second.type = -1;
	for (GLint i = 0; i < 3; i++)
	{
		mb[i] = false;
	}
	for(GLint i = 0; i < createnum; i++)
	{
		mcreate[i].type = -1;
	}
	taketsize = 0; //take things
	takem = false; // take menu
	mp[0] = 0;
	mp[1] = 0; // mouse position
	//wp[0] = 800;
	//wp[1] = 600; //window param
	maxy = 0;
	maxx = 0;
	gamey = 0;
	gamex = 0;
	menus = 0; // menu status
	playmove[0] = 0.0f;
	playmove[1] = 0.0f;
	playmove[2] = 0.0f;
	opentable = 0;
	openchest = 0;
	openchest2 = false;
	pmove = 0;
	levelpause = false;
	monster.clear();
	emonster.clear();
	mtime = 0;
	playchange.clear();
	playtower.clear();
	savename = "autosave.gamesave";
	loadname = "autosave.gamesave";
	salenum = 0;
	openchange = 0;
	moneynum = 0;
	printc = false;
	menusaveload = false;
	menuinputs.clear();
	menur[0] = 0;
	menur[1] = 0;
	cht = 0; // chest thing
	dtime = time(NULL);
} // remake

void loadf()
{
	newmgame();
	GLint *loadbuf;
	GLint a = 0, b = 0, c = 0, it = 0;
	char* lname = (char*) malloc ((loadname.size() + 1) * sizeof(char));
	for (GLint i = 0; i < loadname.size(); i++)
	{
		lname[i] = loadname[i];
	}
	lname[loadname.size()] = 0;
	//puts(lname);
	FILE *f = fopen(lname, "rb");
	fseek(f, 0, SEEK_END);
	GLint sizefile = ftell(f);
	fclose(f);
	f = fopen(lname, "rb");
	loadbuf = (GLint*)malloc (sizefile);
	fread(loadbuf, sizeof(GLint), sizefile / sizeof(GLint), f);
	//cout << r;
	it = 0;
	menus = 0;
	for (GLint i = 0; i < createnum; i++)
	{
		mcreate[i].type = -1;
	}
	for (GLint i = 0; i < peffectnum; i++)
	{
		playeffect[i][0] = loadbuf[it];
		it++;
		playeffect[i][1] = loadbuf[it];
		it++;
	}
	for (GLint i = 0; i < trapattackn; i++)
	{
		trapattack[i][0] = loadbuf[it];
		it++;
		trapattack[i][1] = loadbuf[it];
		it++;
	}
	levelsnum = loadbuf[it];
	it++;
	newcreatem(true);
	live = loadbuf[it];
	it++;
	actmap = loadbuf[it];
	it++;
	m1.minmap[0] = loadbuf[it];
	it++;
	m1.minmap[1] = loadbuf[it];
	it++;
	playpos[0] = loadbuf[it];
	it++;
	playpos[1] = loadbuf[it];
	it++;
	playpos[2] = loadbuf[it];
	it++;
	playermp = loadbuf[it];
	it++;
	playerlevel = loadbuf[it];
	it++;
	levelp = loadbuf[it];
	it++;
	playlevel[0] = loadbuf[it];
	it++;
	playlevel[1] = loadbuf[it];
	it++;
	viewt[0] = loadbuf[it];
	it++;
	viewt[1] = loadbuf[it];
	it++;
	viewt[2] = loadbuf[it];
	it++;
	viewr[0] = loadbuf[it];
	it++;
	viewr[1] = loadbuf[it];
	it++;
	viewr[2] = loadbuf[it];
	it++;
	viewrotate = loadbuf[it];
	it++;
	/*for (GLint i = 0; i < trapattackn; i++)
	{
		trapattack[i][0] = loadbuf[it];
		it++;
		trapattack[i][1] = loadbuf[it];
		it++;
	}*/
	a = loadbuf[it];
	it++;
	monster.resize(a);
	for (GLint i = 0; i < monster.size(); i++)
	{
		a = loadbuf[it];
		it++;
		monster[i].resize(a);
		for (GLint j = 0; j < monster[i].size(); j++)
		{
			monster[i][j] = loadbuf[it];
			it++;
		}
	}
	//r = fread(loadbuf, sizeof(int), 10000000LL, f);
	//cout << r;
	//it = 0;
	a = loadbuf[it];
	it++;
	emonster.resize(a);
	for (GLint i = 0; i < emonster.size(); i++)
	{
		emonster[i].dwall = loadbuf[it];
		it++;
		emonster[i].mstepl = loadbuf[it];
		it++;
		for (GLint j = 0; j < trapattackn; j++)
		{
			emonster[i].effect[j][0] = loadbuf[it];
			it++;
			emonster[i].effect[j][1] = loadbuf[it];
			it++;
		}
		for (GLint j = 0; j < monstersize; j++)
		{
			emonster[i].monstert[j] = loadbuf[it];
			it++;
		}
		c = loadbuf[it];
		it++;
		emonster[i].bigeffect.resize(c);
		for (GLint j = 0; j < emonster[i].bigeffect.size(); j++)
		{
			c = loadbuf[it];
			it++;
			emonster[i].bigeffect[j].resize(c);
			for (GLint k = 0; k < emonster[i].bigeffect[j].size(); k++)
			{
				emonster[i].bigeffect[j][k] = loadbuf[it];
				it++;
			}
		}
	}
	a = loadbuf[it];
	it++;
	for (GLint i = 0; i < a; i++)
	{
		tower playtower2;
		playtower2.posx = loadbuf[it];
		it++;
		playtower2.posy = loadbuf[it];
		it++;
		playtower2.tlevel = loadbuf[it];
		it++;
		playtower2.maxttimer = loadbuf[it];
		it++;
		for (GLint j = 0; j < tparamnum; j++)
		{
			for (GLint k = 0; k < 3; k++)
			{
				playtower2.tparam[j][k] = loadbuf[it];
				it++;
			}
		}
		b = loadbuf[it];
		it++;
		playtower2.towerb.resize(b);
		for (GLint j = 0; j < b; j++)
		{
			loadobj(&playtower2.towerb[j].a, loadbuf, &it);
			playtower2.towerb[j].posx = loadbuf[it];
			it++;
			playtower2.towerb[j].posy = loadbuf[it];
			it++;
			playtower2.towerb[j].posz = loadbuf[it];
			it++;
		}
		playtower.push_back(playtower2);
	}
	a = loadbuf[it];
	it++;
	for (GLint i = 0; i < a; i++)
	{
		market playchange2;
		b = loadbuf[it];
		it++;
		playchange2.poslevel = loadbuf[it];
		it++;
		playchange2.posx = loadbuf[it];
		it++;
		playchange2.posy = loadbuf[it];
		it++;
		playchange2.posz = loadbuf[it];
		it++;
		playchange2.type = loadbuf[it];
		it++;
		for (GLint j = 0; j < b; j++)
		{
			sthing sale2;
			sale2.n = loadbuf[it];
			it++;
			loadobj(&sale2.b, loadbuf, &it);
			sale2.nb = loadbuf[it];
			it++;
			sale2.ns = loadbuf[it];
			it++;
			loadobj(&sale2.s, loadbuf, &it);
			sale2.up = loadbuf[it];
			it++;
			playchange2.sale.push_back(sale2);
		}
		playchange.push_back(playchange2);
	}
	loadobj(&phand[0], loadbuf, &it);
	loadobj(&phand[1], loadbuf, &it);
	for (GLint i = 0; i < 7; i++)
	{
		loadobj(&pt[i], loadbuf, &it);
	}
	for (GLint i = 0; i < pmx; i++)
	{
		for (GLint j = 0; j < pmy + 3; j++)
		{
			loadobj(&pb[i][j], loadbuf, &it);
		}
	}
	for (GLint i = 0; i < levelsnum; i++)
	{
		gamemap[i].addtochesttimer = loadbuf[it];
		it++;
		ngmmonster[i] = loadbuf[it];
		it++;
		levelpos[i] = loadbuf[it];
		it++;
		levelmainm[i] = loadbuf[it];
		it++;
		mapsizexy[i][0] = loadbuf[it];
		it++;
		mapsizexy[i][1] = loadbuf[it];
		it++;
		x = mapsizexy[i][0];
		y = mapsizexy[i][1];
		gamemap[i].newgenmap();
		for (GLint j = 0; j < mapsizexy[i][0]; j++)
		{
			for (GLint j2 = 0; j2 < mapsizexy[i][1]; j2++)
			{
				for (GLint k = 0; k < sizemap; k++)
				{
					gamemap[i].map[j][j2][k] = loadbuf[it];
					it++;
				}
			}
		}
		for (GLint j = 0; j < mapsizexy[i][0]; j++)
		{
			for (GLint j2 = 0; j2 < mapsizexy[i][1]; j2++)
			{
				for (GLint j3 = 0; j3 < z; j3++)
				{
					gamemap[i].block[j][j2][j3] = loadbuf[it];
					it++;
				}
			}
		}
		a = loadbuf[it];
		it++;
		gamemap[i].chest.resize(a, vector<obj>(chmaxnum));
		for (GLint j = 0; j < gamemap[i].chest.size(); j++)
		{
			for (GLint k = 0; k < chmaxnum; k++)
			{
				loadobj(&gamemap[i].chest[j][k], loadbuf, &it);
			}
		}
		c = loadbuf[it];
		it++;
		gamemap[i].mblock.resize(c);
		for (GLint j = 0; j < gamemap[i].mblock.size(); j++)
		{
			loadobj(&gamemap[i].mblock[j].a, loadbuf, &it);
			gamemap[i].mblock[j].posx = loadbuf[it];
			it++;
			gamemap[i].mblock[j].posy = loadbuf[it];
			it++;
			gamemap[i].mblock[j].posz = loadbuf[it];
			it++;
		}
		for (GLint j = 0; j < 4; j++)
		{
			levelwavetimer[i][j] = loadbuf[it];
			it++;
		}
		//cout << ' ' << (i + 1);
	}
	cout << "loaded\n";
	free(loadbuf);
	free(lname);
	fclose(f);
	x = mapsizexy[actmap][0];
	y = mapsizexy[actmap][1];
} // remake

void searchmpos(GLfloat *mx, GLfloat *my)
{
	GLfloat mp2[2] = {mp[0], mp[1]};
	if (wp[0] / 8.0f > wp[1] / 6.0f)
	{
		mp2[0] -= (wp[0] - wp[1] / 6.0f * 8.0f) * 0.5f;
		if (mp2[0] < 0)
		{
			mp2[0] = 0;
		}
		if (mp2[0] > wp[0] - (wp[0] - wp[1] / 6.0f * 8.0f) * 0.5)
		{
			mp2[0] = wp[0] - (wp[0] - wp[1] / 6.0f * 8.0f) * 0.5;
		}
		*mx = mp2[0] / (wp[1] / 6.0f * 8.0f) * 0.2f - 0.01f;
		*my = -mp2[1] / wp[1] * 0.148f + 0.146f;
	}
	else
	{
		if (wp[0] / 8.0f < wp[1] / 6.0f)
		{
			mp2[1] -= (wp[1] - wp[0] / 8.0f * 6.0f) * 0.5f;
			if (mp2[1] < 0)
			{
				mp2[1] = 0;
			}
			if (mp2[1] > wp[1] - (wp[1] - wp[0] / 8.0f * 6.0f) * 0.5f)
			{
				mp2[1] = wp[1] - (wp[1] - wp[0] / 8.0f * 6.0f) * 0.5f;
			}
			*mx = mp2[0] / wp[0] * 0.2f - 0.01f;
			*my = -mp2[1] / (wp[0]  / 8.0f * 6.0f) * 0.148f + 0.146f;
		}
		else
		{
			*mx = mp2[0] / wp[0] * 0.2f - 0.01f;
			*my = -mp2[1] / wp[1] * 0.148f + 0.146f;
		}
	}
}

void bsearchmpos(GLfloat *mx, GLfloat *my)
{
	GLfloat mp2[2] = {mp[0], mp[1]};
	if (wp[0] / 8.0f > wp[1] / 6.0f)
	{
		mp2[0] -= (wp[0] - wp[1] / 6.0f * 8.0f) * 0.5f;
		if (mp2[0] < 0)
		{
			mp2[0] = 0;
		}
		if (mp2[0] > wp[0] - (wp[0] - wp[1] / 6.0f * 8.0f) * 0.5)
		{
			mp2[0] = wp[0] - (wp[0] - wp[1] / 6.0f * 8.0f) * 0.5;
		}
		*mx = (mp2[0] / (wp[1] / 6.0f * 8.0f) * 0.2f - 0.1f) / 0.18f * 33.0f;
		*my = (-mp2[1] / wp[1] * 0.148f + 0.074f) / 0.18f * 33.0f;
	}
	else
	{
		if (wp[0] / 8.0f < wp[1] / 6.0f)
		{
			mp2[1] -= (wp[1] - wp[0] / 8.0f * 6.0f) * 0.5f;
			if (mp2[1] < 0)
			{
				mp2[1] = 0;
			}
			if (mp2[1] > wp[1] - (wp[1] - wp[0] / 8.0f * 6.0f) * 0.5f)
			{
				mp2[1] = wp[1] - (wp[1] - wp[0] / 8.0f * 6.0f) * 0.5f;
			}
			*mx = (mp2[0] / wp[0] * 0.2f - 0.1f) / 0.18f * 33.0f;
			*my = (-mp2[1] / (wp[0] / 8.0f * 6.0f) * 0.148f + 0.074f) / 0.18f * 33.0f;
		}
		else
		{
			*mx = (mp2[0] / wp[0] * 0.2f - 0.1f) / 0.18f * 33.0f;
			*my = (-mp2[1] / wp[1] * 0.148f + 0.074f) / 0.18f * 33.0f;
		}
	}
}

void thingtext(GLfloat mx, GLfloat my, obj thingtextpos)
{
	if (thingtextpos.type != -1 && thinghelp)
	{
		glTranslatef(0.0f, 0.0f, 0.001f);
		glColor3f(0.2f, 0.6f, 0.2f);
		//text("", mx, my, 0.0f);
		if (mx <= 0.09f)
		{
			square2d(0.12f, -1.0f, 1.0f, 1.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			text("", 0.125f, 0.125f, 0.0f);
		}
		else
		{
			square2d(-1.0f, -1.0f, 0.06f, 1.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			text("", -0.005f, 0.125f, 0.0f);
		}
		outobj(thingtextpos);
		glTranslatef(0.0f, 0.0f, -0.001f);
		//text(thingtextpos.name, mx, my, 0.0f);
	}
}

void square2dt(obj textthingnum, GLfloat X1, GLfloat Y1, GLfloat X2, GLfloat Y2)
{
	GLint a = 0;
	glBindTexture (GL_TEXTURE_2D, texture[1]);
	glColor3f(bcol[1][0], bcol[1][1], bcol[1][2]);
	square2d(X1, Y1, X2, Y2);
	//tsquare(0, X1, Y1, X2, Y2);
	if (textthingnum.type != -1)
	{
		//tsquare(textthingnum.text, X1, Y1, X2, Y2);
		if (textthingnum.type >= 1 && textthingnum.type <= 7)
		{
			tsquare(textthingnum.type, X1, Y1, X2, Y2);
		}
		else
		{
			if (textthingnum.type == 8)
			{
				tsquare(8, X1, Y1, X2, Y2);
			}
			else
			{
				if (textthingnum.type == 9)
				{
					tsquare(9, X1, Y1, X2, Y2);
				}
				else
				{
					if (textthingnum.type == 10)
					{
						a = textthingnum.wtype % 100 + 10;
						tsquare(a, X1, Y1, X2, Y2);
					}
					else
					{
						if (textthingnum.type == 0)
						{
							switch(textthingnum.t2)
							{
								case 0:
									a = 16;
									break;
								case 1:
									a = 17;
									break;
								case 2:
									a = 18;
									break;
								case 3:
									a = 18;
									break;
								case 4:
									break;
								case 5:
									a = 25;
									break;
								case 6:
									a = 20;
									break;
								case 7:
									a = 21;
									break;
								case 8:
									a = 22;
									break;
								case 9:
									a = 24;
									break;
								default:
									a = 16;
									break;
							}
							tsquare(a, X1, Y1, X2, Y2);
						}
						else
						{
							switch (textthingnum.type)
							{
								case 28:
									a = 23;
									break;
								case 30:
									a = 23;
									break;
								case 29:
									a = 19;
									break;
								case 26:
									a = blocktext - 2;
									break;
								case 27:
									a = blocktext - 3;
									break;
								case 11:
									a = blocktext - 1;
									break;
								case 12:
									a = blocktext;
									break;
								default:
									a = 16;
									break;
							}
							tsquare(a, X1, Y1, X2, Y2);
						}
					}
				}
			}
		}
	}
	glBindTexture (GL_TEXTURE_2D, texture[1]);
}

void thingplace(GLint a, GLfloat mx , GLfloat my) // thing with type a
{
	if (mb[0])
	{
		obj b;
		if (tb.second.type != -1)
		{
			if (tb.second.type == a)
			{
				b = pt[a - 1];
				pt[a - 1] = tb.second;
				tb.second = b;
			}
		}
		else
		{
			tb.second = pt[a - 1];
			tb.first = -a;
			pt[a - 1].type = -1;
		}
	}
	else
	{
		thingtext(mx, my, pt[a - 1]);
	}
} // player

void thingplace2(GLint b, GLfloat mx, GLfloat my) // jacket, belt, trousers
{
	obj a;
	if (mb[0])
	{
		if (tb.second.type == -1)
		{
			tb.first = pms + 10 * b + (GLint)((mx - 0.07f) / 0.01f);
		}
		a = pb[(GLint)((mx - 0.07f) / 0.01f)][pmy + b];
		pb[(GLint)((mx - 0.07f) / 0.01f)][pmy + b] = tb.second;
		tb.second = a;
	}
	else
	{
		thingtext(mx, my, pb[(GLint)((mx - 0.07f) / 0.01f)][pmy + b]);
	}
}

void thingplace3(GLint a, obj *m2, GLfloat m3[3])
{
	if (m2[a].type == -1)
	{
		glColor3f (m3[0], m3[1], m3[2]);
	}
	else
	{
		glColor3f (m2[a].color[0], m2[a].color[1], m2[a].color[2]);
	}
}

void thingplace4(GLint a, GLfloat sy)
{
	int i = 0;
	for (i = 0; i < pmx; i++)
	{
		if (pb[i][pmy + a].type != -1)
		{
			if (thingtex)
			{
				square2dt(pb[i][pmy + a], 0.07f + i * 0.01f, sy, 0.08f + i * 0.01f, sy + 0.01f);
			}
			else
			{
				glColor3f (pb[i][pmy + a].color[0], pb[i][pmy + a].color[1], pb[i][pmy + a].color[2]);
				square2d (0.07f + i * 0.01f, sy, 0.08f + i * 0.01f, sy + 0.01f);
			}
		}
	}
}

void thingplace5(GLint a, bool c, GLfloat mx, GLfloat my)
{
	obj b;
	if (mb[0])
	{
		if (tb.second.type == -1)
		{
			tb.first = 1;
			tb.second = mcreate[a];
			mcreate[a].type = -1;
		}
		else
		{
			if (c)
			{
				b = tb.second;
				tb.second = mcreate[a];
				mcreate[a] = b;
			}
		}
	}
	else
	{
		thingtext(mx, my, mcreate[a]);
	}
}

void addmplace(GLfloat X, GLfloat Y)
{
	glColor3f (0.3f, 0.2f, 0.0f);
	square2d (X, Y, X + 0.025f, Y + 0.025f);
	glColor3f (0.8f, 0.8f, 0.6f);
	square2d (X + 0.01f, Y + 0.01f, X + 0.015f, Y + 0.015f);
	glColor3f (0.3f, 0.2f ,0.0f);
	squareline (X, Y, X + 0.025f, Y + 0.025f, 2.0f);
}

void mplace4(GLfloat X, GLfloat Y, GLint a, const GLint &k, const GLint &r)
{
	obj b;
	b.type = -1;
	addmplace(X, Y);
	if (ct[k][r][a] < 0)
	{
		square2dt(b, X, Y, X + 0.01f, Y + 0.01f);
	}
	else
	{
		square2dt(createtnum[k][r][ct[k][r][a]], X, Y, X + 0.01f, Y + 0.01f);
		if (fview)
		{
			glColor3f(1.0f, 1.0f, 1.0f);
			text(ct[k][r][a], X + 0.004f, Y + 0.004f, 0.0f);
		}
	}
	if (ct[k][r][a + 1] < 0)
	{
		square2dt(b, X + 0.015f, Y, X + 0.025f, Y + 0.01f);
	}
	else
	{
		square2dt(createtnum[k][r][ct[k][r][a + 1]], X + 0.015f, Y, X + 0.025f, Y + 0.01f);
		if (fview)
		{
			glColor3f(1.0f, 1.0f, 1.0f);
			text(ct[k][r][a + 1], X + 0.019f, Y + 0.004f, 0.0f);
		}
	}
	if (ct[k][r][a + 4] < 0)
	{
		square2dt(b, X, Y + 0.015f, X + 0.01f, Y + 0.025f);
	}
	else
	{
		square2dt(createtnum[k][r][ct[k][r][a + 4]], X, Y + 0.015f, X + 0.01f, Y + 0.025f);
		if (fview)
		{
			glColor3f(1.0f, 1.0f, 1.0f);
			text(ct[k][r][a + 4], X + 0.004f, Y + 0.019f, 0.0f);
		}
	}
	if (ct[k][r][a + 5] < 0)
	{
		square2dt(b, X + 0.015f, Y + 0.015f, X + 0.025f, Y + 0.025f);
	}
	else
	{
		square2dt(createtnum[k][r][ct[k][r][a + 5]], X + 0.015f, Y + 0.015f, X + 0.025f, Y + 0.025f);
		if (fview)
		{
			glColor3f(1.0f, 1.0f, 1.0f);
			text(ct[k][r][a + 5], X + 0.019f, Y + 0.019f, 0.0f);
		}
	}
}

void mplace4(GLfloat X, GLfloat Y, GLint a, obj *createm = mcreate)
{
	addmplace(X, Y);
	if (thingtex)
	{
		square2dt(createm[a], X, Y, X + 0.01f, Y + 0.01f);
		square2dt(createm[a + 1], X + 0.015f, Y, X + 0.025f, Y + 0.01f);
		square2dt(createm[a + 4], X, Y + 0.015f, X + 0.01f, Y + 0.025f);
		square2dt(createm[a + 5], X + 0.015f, Y + 0.015f, X + 0.025f, Y + 0.025f);
	}
	else
	{
		thingplace3 (a, createm, bcol[1]);
		square2d (X, Y, X + 0.01f, Y + 0.01f);
		thingplace3 (a + 1, createm, bcol[1]);
		square2d (X + 0.015f, Y, X + 0.025f, Y + 0.01f);
		thingplace3 (a + 4, createm, bcol[1]);
		square2d (X, Y + 0.015f, X + 0.01f, Y + 0.025f);
		thingplace3 (a + 5, createm, bcol[1]);
		square2d (X + 0.015f, Y + 0.015f, X + 0.025f, Y + 0.025f);
	}
}

void cplace4(GLfloat X, GLfloat Y, GLint a, bool b, GLfloat mx, GLfloat my, bool c = true)
{
	if (mx < (X + 0.01f) && mx >= X && my < (Y + 0.01f) && my >= Y)
	{
		if (c)
		{
			thingplace5 (a, b, mx, my);
		}
		else
		{
			if (ct[menur[0]][menur[1]][a] >= 0)
			{
				thingtext(mx, my, createtnum[menur[0]][menur[1]][ct[menur[0]][menur[1]][a]]);
			}
		}
	}
	if (mx < (X + 0.025f) && mx >= (X + 0.015f) && my < (Y + 0.01f) && my >= Y)
	{
		if (c)
		{
			thingplace5 (a + 1, b, mx, my);
		}
		else
		{
			if (ct[menur[0]][menur[1]][a + 1] >= 0)
			{
				thingtext(mx, my, createtnum[menur[0]][menur[1]][ct[menur[0]][menur[1]][a + 1]]);
			}
		}
	}
	if (mx < (X + 0.01f) && mx >= X && my < (Y + 0.025f) && my >= (Y + 0.015f))
	{
		if (c)
		{
			thingplace5 (a + 4, b, mx, my);
		}
		else
		{
			if (ct[menur[0]][menur[1]][a + 4] >= 0)
			{
				thingtext(mx, my, createtnum[menur[0]][menur[1]][ct[menur[0]][menur[1]][a + 4]]);
			}
		}
	}
	if (mx < (X + 0.025f) && mx >= (X + 0.015f) && my < (Y + 0.025f) && my >= (Y + 0.015f))
	{
		if (c)
		{
			thingplace5 (a + 5, b, mx, my);
		}
		else
		{
			if (ct[menur[0]][menur[1]][a + 5] >= 0)
			{
				thingtext(mx, my, createtnum[menur[0]][menur[1]][ct[menur[0]][menur[1]][a + 5]]);
			}
		}
	}
}

void buttoncolor(GLint a)
{
	if (mbutton[a] == true)
	{
		glColor3f (0.4f, 0.4f, 0.4f);
		mbutton[a] = false;
	}
	else
	{
		glColor3f (0.2f, 0.2f, 0.2f);
	}
}

void addmplace(GLint i, bool b)
{
	bool d = true;
	for (GLint j = x / 2 - wavemonsterplace; d && j <= x / 2 + wavemonsterplace; j++)
	{
		for (GLint k = y / 2 - wavemonsterplace; d && k <= y / 2 + wavemonsterplace; k++)
		{
			bool c = true;
			for (GLint j2 = j - 1; c && j2 <= j + 1; j2++)
			{
				for (GLint k2 = k - 1; c && k2 <= k + 1; k2++)
				{
					if (j2 >= 0 && j2 < x && k2 >= 0 && k2 < y && gamemap[i].map[j2][k2][10] == 1) // place of monsters
					{
						c = false;
					}
				}
			}
			if (c && rand () % 100 < levelwavetime[4][0] + min(levelwavetime[4][2], (max(i - baselevel, baselevel - i)) * levelwavetime[4][1]) && !(max(max(j, x / 2) - min(j, x / 2), max(k, y / 2) - min(k , y / 2)) <= maintowerplace))
			{
				if (gamemap[i].map[j][k][8] != 0)
				{
					deltower(gamemap[i].map[j][k][8] - 1);
				}
				else
				{
					for (GLint r = 0; r < z; r++)
					{
						freeblock(i, j, k, r);
						if (r < deep)
						{
							gamemap[i].block[j][k][r] = 2;
						}
						else
						{
							gamemap[i].block[j][k][r] = 0;
						}
					}
					freetrap(i, j, k);
					for (GLint r = 0; r < sizemap; r++)
					{
						gamemap[i].map[j][k][r] = 0;
					}
				}
				gamemap[i].map[j][k][5] = deep - 1;
				gamemap[i].map[j][k][0] = 1;
				gamemap[i].map[j][k][10] = 1;
				gamemap[i].block[j][k][deep - 1] = 1; // block of monster place
				// add place with monsters
				if (b)
				{
					d = false;
				}
			}
		}
	}
}

void wavegen()
{
	if (addtime)
	{
		for (GLint i = 0; i < levelsnum; i++)
		{
			if (levelpos[i] == 1)
			{
				//cout << i;
				if (levelwavetimer[i][0] >= levelwavetime[0][0] + min(levelwavetime[0][2], (max(i - baselevel, baselevel - i) + levelwavetimer[i][3] / wavesuplevel) * levelwavetime[0][1]))
				{
					//cout << 1;
					if (levelwavetimer[i][1] >= levelwavetime[1][0] + min(levelwavetime[1][2], (max(i - baselevel, baselevel - i) + levelwavetimer[i][3] / wavesuplevel) * levelwavetime[1][1]))
					{
						//cout << 2;
						for (GLint j = 0; j < 3; j++)
						{
							levelwavetimer[i][j] = 0;
						}
						levelwavetimer[i][3]++;
						addmplace(i, true);
						// add new monster place
					}
					else
					{
						//cout << 3;
						levelwavetimer[i][1]++;
						if (levelwavetimer[i][2] >= levelwavetime[2][0] + min(levelwavetime[2][2], (max(i - baselevel, baselevel - i) + levelwavetimer[i][3] / wavesuplevel) * levelwavetime[2][1]))
						{
							// gen new monsters
							//cout << -2;
							for (GLint j = x / 2 - wavemonsterplace; j <= x / 2 + wavemonsterplace; j++)
							{
								for (GLint k = y / 2 - wavemonsterplace; k <= y / 2 + wavemonsterplace; k++)
								{
									//cout << -1;
									if (gamemap[i].map[j][k][10] == 1)
									{
										 //cout << 0;
										if (rand() % 100 < levelwavetime[3][0] + min(levelwavetime[3][2], (max(i - baselevel, baselevel - i) + levelwavetimer[i][3] / wavesuplevel) * levelwavetime[3][1]))
										{
											//cout << 1 << ' ' << '\n';
											addmonster(i, j, k, 1, 0);
											/*monstereffect a(i, 1);
											vector<GLfloat> b;
											b.push_back(j);
											b.push_back(k);
											b.push_back(deep);
											b.push_back(a.monstert[3]);
											b.push_back(0); // ?
											b.push_back(0);
											b.push_back(-1);
											b.push_back(i);
											b.push_back(1);
											emonster.push_back(a);
											monster.push_back(b);
											gamemap[i].map[j][k][6] = monster.size();*/
										}
									}
								}
							}
							levelwavetimer[i][2] = 0;
						}
						else
						{
							//cout << 5;
							levelwavetimer[i][2]++;
						}
					}
				}
				else
				{
					//cout << '\n' << levelwavetime[0][0];
					//cout << ' ' << levelwavetime[0][2];
					//cout << ' ' << (max(i - baselevel, baselevel - i) /*+ /*levelwavetimer[i][3] / wavesuplevel*/) * levelwavetime[0][1];
					//cout << 4;
					levelwavetimer[i][0]++;
				}
			}
			else
			{
				/*for (long j = 0; j < 4; j++)
				{
					levelwavetimer[i][j] = 0;
				}*/
			}
		}
	}
}

void mpgen()
{
	if (addtime)
	{
		playermp += playerlevel;
	}
	if (playermp > maxplaymp * playerlevel)
	{
		playermp = maxplaymp * playerlevel;
	}
	if (levelp >= playlevel[0])
	{
		playerlevel++;
		GLint a = 0;
		levelp -= playlevel[0];
		for (GLint i = 0; i < 2; i++)
		{
			a = playlevel[0];
			playlevel[0] = playlevel[1];
			playlevel[1] = playlevel[0] + a;
		}
	}
}

void leveltowerstep()
{
	gamewin = true;
	for (GLint i = 0; i < levelsnum; i++)
	{
		bool b = false;
		for (GLint j = 0; j < z; j++)
		{
			if (gamemap[i].block[x / 2][y / 2][j] >= 0 && gamemap[i].block[x / 2][y / 2][j] >= thing.size())
			{
				gamemap[i].block[x / 2][y / 2][j] = 0;
			}
			if ((gamemap[i].block[x / 2][y / 2][j] < 0 && gamemap[i].mblock.size() <= -gamemap[i].block[x / 2][y / 2][j] - 1))
			{
				gamemap[i].block[x / 2][y / 2][j] = 0;
			}
			//cout << gamemap[i].block[x / 2][y / 2][j];
			if ((gamemap[i].block[x / 2][y / 2][j] >= 0 && thing[gamemap[i].block[x / 2][y / 2][j]].wtype == i + 1 && thing[gamemap[i].block[x / 2][y / 2][j]].type == 26) || (gamemap[i].block[x / 2][y / 2][j] < 0 && gamemap[i].mblock[-gamemap[i].block[x / 2][y / 2][j] - 1].a.wtype == i + 1 && gamemap[i].mblock[-gamemap[i].block[x / 2][y / 2][j] - 1].a.type == 26))
			{
				b = true;
				break;
			}
		}
		if (!b)
		{
			gamewin = false;
		}
		if (levelmainm[i] == 0)
		{
			gamewin = false;
		}
		if (b)
		{
			if (levelpos[i] == 0)
			{
				// create new
				for (GLint j = x / 2 - wavemonsterplace; j <= x / 2 + wavemonsterplace; j++)
				{
					for (GLint k = y / 2 - wavemonsterplace; k <= y / 2 + wavemonsterplace; k++)
					{
						if (gamemap[i].map[j][k][0] == 1)
						{
							for (GLint r = 0; r < z; r++)
							{
								// delete blocks
								if (r < deep)
								{
									gamemap[i].block[j][k][r] = 2;
								}
								else
								{
									gamemap[i].block[j][k][r] = 0;
								}
							}
							gamemap[i].map[j][k][0] = 0;
						}
					}
				}
			}
			if (levelpos[i] != 1)
			{
				addmplace(i, false);
				startresettimer();
				levelpos[i] = 1;
			}
		}
		else
		{
			if (levelpos[i] == 1)
			{
				for (GLint j = 0; j < 4; j++)
				{
					levelwavetimer[i][j] = 0;
				}
				levelpos[i] = 2;
				for (GLint j = x / 2 - wavemonsterplace; j <= x / 2 + wavemonsterplace; j++)
				{
					for (GLint k = y / 2 - wavemonsterplace; k <= y / 2 + wavemonsterplace; k++)
					{
						if (gamemap[i].map[j][k][8] != 0)
						{
							deltower(gamemap[i].map[j][k][8] - 1);
						}
						else
						{
							for (GLint r = 0; r < z; r++)
							{
								freeblock(i, j, k, r);
								if (r < deep)
								{
									gamemap[i].block[j][k][r] = 2;
								}
								else
								{
									gamemap[i].block[j][k][r] = 0;
								}
							}
							freetrap(i, j, k);
							if (gamemap[i].map[j][k][8] != 0)
							{
								deltower(gamemap[i].map[j][k][8] - 1);
							}
							for (GLint r = 0; r < sizemap; r++)
							{
								gamemap[i].map[j][k][r] = 0;
							}
						}
						gamemap[i].map[j][k][5] = deep - 1;
					}
				}
			}
		}
	}
	if (gamewin)
	{
		if (!startmenu)
		{
			startmenu = true;
			menus = -4;
		}
	}
}
// remake
void copentable(bool c, GLint a) // click
{
	GLint b = 0;
	GLfloat mx = 0.0f, my = 0.0f;
	searchmpos(&mx, &my);
	if (tb.second.type != -1)
	{
		//if (thingtex)
		//{
		square2dt(tb.second, -0.005f + mx, -0.005f + my, 0.005f + mx, 0.005f + my);
		/*}
		else
		{
			glColor3f (tcolor[tb[0]][0], tcolor[tb[0]][1], tcolor[tb[0]][2]);
			square2d (-0.005f + mx, -0.005f + my, 0.005f + mx, 0.005f + my);
		}*/
	}
	if (mx < 0.175f && mx >= 0.165f && my < 0.03f && my >= 0.015f) // >>
	{
		if (mb[0])
		{
			cht++;
			if (cht > 2)
			{
				cht = 0;
			}
		}
		mbutton[1] = true;
	}
	if (mx < 0.015f && mx >= 0.005f && my < 0.03f && my >= 0.015f) // <<
	{
		if (mb[0])
		{
			cht--;
			if (cht < 0)
			{
				cht = 2;
			}
		}
		mbutton[2] = true;
	}
	if (mx < 0.13f && mx >= 0.05f && my < 0.0125f && my >= 0.0025f)
	{
		if (mb[0])
		{
			menus = 1;
			if (tb.second.type != -1)
			{
				if (tb.first <= 0)
				{
					tb.first = -tb.first;
					if ((((tb.first / 10 == 2) || (tb.first / 10 == 0)) && (tb.second.type < 8 || tb.second.type > 10)) || (tb.first / 10 == 1 && tb.second.type >= 8 && tb.second.type <= 10))
					{
						pb[tb.first % 10][pmy + tb.first / 10] = tb.second;
					}
					else
					{
						if (taketsize < 60)
						{
							taketsize;
							taket[taketsize] = tb.second;
						}
					}
				}
				else
				{
					if (c)
					{
						m1.chest[a][tb.first] = tb.second;
					}
					else
					{
						if (taketsize < 60)
						{
							taketsize++;
							taket[taketsize] = tb.second;
						}
					}
				}
				tb.second.type = -1;
				tb.first = 0;
			}
			cht = 0;
		}
		mbutton[3] = true;
	}
	if (mx < 0.165f && mx >= 0.015f && my < 0.03f && my >= 0.015f && pt[3 - cht].size > (mx - 0.015f) / 0.015f && ((((cht == 2) || (cht == 0)) && (tb.second.type < 8 || tb.second.type > 10)) || (cht == 1 && ((tb.second.type >= 8 && tb.second.type <= 10) || tb.second.type == -1))))
	{
		if (mb[0])
		{
			obj c;
			if (tb.second.type == -1)
			{
				tb.first = -(10 * cht + (GLint)((mx - 0.015f) / 0.015f));
			}
			c = tb.second;
			tb.second = pb[(GLint)((mx - 0.015f) / 0.015f)][pmy + cht];
			pb[(GLint)((mx - 0.015f) / 0.015f)][pmy + cht] = c;
		}
		else
		{
			thingtext(mx, my, pb[(GLint)((mx - 0.015f) / 0.015f)][pmy + cht]);
		}
	}
}

void mopentable() // menu
{
	GLint i = 0;
	glTranslatef (0.0f, 0.0f, -0.18f);
	glColor3f (0.6f, 0.6f, 0.6f);
	square2d (-0.075f, -0.0575f, 0.075f, -0.0425f);
	for (i = 0; i < pt[3 - cht].size; i++)
	{
		if (pb[i][cht + pmy].type != -1)
		{
			square2dt(pb[i][cht + pmy], -0.075f + 0.015f * i, -0.0575f, -0.06f + 0.015f * i, -0.0425f);
		}
	}
	glColor3f(0.2f, 0.2f, 0.2f);
	for (i = 0; i < 11; i++)
	{
		//line (-0.075f + i * 0.015f, 0.0625f, -0.075f + i * 0.015f, -0.0275f, 3.0f);
		line (-0.075f + i * 0.015f, -0.0425f, -0.075f + i * 0.015f, -0.0575f, 3.0f);
	}
	for (i = 7; i < 9; i++)
	{
		line (-0.075f, 0.0625f - i * 0.015f, 0.075f, 0.0625f - i * 0.015f, 3.0f);
	}
	buttoncolor (3);
	square2d (-0.04f, -0.07f, 0.04f, -0.06f);
	buttoncolor (1);
	square2d (0.0875f, -0.0575f, 0.0775f, -0.0425);
	buttoncolor (2);
	square2d (-0.0875f, -0.0575f, -0.0775f, -0.0425f);
	glTranslatef (0.0f, 0.0f, 0.18f);
	glColor3f (1.0f, 1.0f, 1.0f);
	text (">>", 0.08f, -0.051f, -0.18f);
	text ("<<", -0.085f, -0.051f, -0.18f);
	//text ("Chest", -0.005f, 0.065f, -0.18f);
	text ("Back", -0.005f, -0.0675f, -0.18f);
	switch (cht)
	{
		case 0:
			text ("Jacket", -0.005f, -0.04f, -0.18f);
			break;
		case 1:
			text ("Belt", -0.005f, -0.04f, -0.18f);
			break;
		case 2:
			text ("Pants", -0.005f, -0.04f, -0.18f);
			break;
	}
}

void addopentable(GLint b, bool c)
{
	GLint i = 0, i2 = 0;
	GLint a = 0;
	if (m1.map[(GLint)playpos[0]][(GLint)playpos[1]][b] > 0)
	{
		a = m1.map[(GLint)playpos[0]][(GLint)playpos[1]][b];
	}
	/*for (i = -1; i < 2; i++)
	{
		for (i2 = -1; i2 < 2; i2++)
		{
			if (m1.map[(GLint)playpos[0] + i][(GLint)playpos[1] + i2][b] > 0)
			{
				a = m1.map[(GLint)playpos[0] + i][(GLint)playpos[1] + i2][b];
			}
		}
	}*/ // ??
	if (a > 0 && mb[0])
	{
		if (c)
		{
			openchest = a - 1;
			menus = 3;
			openchest2 = true;
		}
		else
		{
			opentable  = a - 1;
			menus = 4;
		}
	}
}

void addmodel(string s)
{
	GLint n = 0;
	GLint h = 0;
	GLint b = 0;
	ifstream add;
	add.open(s);
	add >> n >> h;
	model a(n, h);
	for (GLint i = 0; i < n * h; i++)
	{
		for (GLint j = 0 ; j < n; j++)
		{
			for (GLint k = 0; k < n; k++)
			{
				add >> b;
				if (b == 1)
				{
					a.m[j][k][i].s = true;
				}
			}
		}
	}
	for (GLint i = 0; i < n * h; i++)
	{
		for (GLint j = 0 ; j < n; j++)
		{
			for (GLint k = 0; k < n; k++)
			{
				add >> a.m[j][k][i].r;
				add >> a.m[j][k][i].g;
				add >> a.m[j][k][i].b;
				add >> a.m[j][k][i].a;
			}
		}
	}
	for (GLint i = 0; i < n * h; i++)
	{
		for (GLint j = 0 ; j < n; j++)
		{
			for (GLint k = 0; k < n; k++)
			{
				add >> a.m[j][k][i].t;
			}
		}
	}
	cmodel.push_back(a);
	add.close();
} // ???

void drawmodel(GLint num, bool d)
{
	GLfloat a = 0, b = 0, c = 0;
	glBindTexture (GL_TEXTURE_2D, texture[1]);
	for (GLint i = 0; i < cmodel[num].n * cmodel[num].h; i++)
	{
		for (GLint j = 0; j < cmodel[num].n; j++)
		{
			for (GLint k = 0; k < cmodel[num].n; k++)
			{
				if (cmodel[num].m[j][k][i].s)
				{
					if (j == 0 || !cmodel[num].m[j - 1][k][i].s)
					{
						if (d)
						{
							square(a, b, c, a, b + 1.0f * squarey / cmodel[num].n, c + 1.0f * squarez / cmodel[num].n, cmodel[num].m[j][k][i].r - bshadow, cmodel[num].m[j][k][i].g - bshadow, cmodel[num].m[j][k][i].b - bshadow, cmodel[num].m[j][k][i].a);
						}
						else
						{
							glColor4f(cmodel[num].m[j][k][i].r, cmodel[num].m[j][k][i].g, cmodel[num].m[j][k][i].b, cmodel[num].m[j][k][i].a);
							tsquare(cmodel[num].m[j][k][i].t, a, b, c, a, b + 1.0f * squarey / cmodel[num].n, c + 1.0f * squarez / cmodel[num].n);
						}
					}
					if (k == 0 || !cmodel[num].m[j][k - 1][i].s)
					{
						if (d)
						{
							square(a, b, c, a + 1.0f * squarex / cmodel[num].n, b, c + 1.0f * squarez / cmodel[num].n, cmodel[num].m[j][k][i].r - bshadow, cmodel[num].m[j][k][i].g - bshadow, cmodel[num].m[j][k][i].b - bshadow, cmodel[num].m[j][k][i].a);
						}
						else
						{
							tsquare(cmodel[num].m[j][k][i].t, a, b, c, a + 1.0f * squarex / cmodel[num].n, b, c + 1.0f * squarez / cmodel[num].n);
						}
					}
					if (i == 0 || !cmodel[num].m[j][k][i - 1].s)
					{
						if (d)
						{
							square(a, b, c, a + 1.0f * squarex / cmodel[num].n, b + 1.0f * squarey / cmodel[num].n, c, cmodel[num].m[j][k][i].r, cmodel[num].m[j][k][i].g, cmodel[num].m[j][k][i].b, cmodel[num].m[j][k][i].a);
						}
						else
						{
							tsquare(cmodel[num].m[j][k][i].t, a, b, c, a + 1.0f * squarex / cmodel[num].n, b + 1.0f * squarey / cmodel[num].n, c);
						}
					}
					c +=  1.0f * squarez / cmodel[num].n;
					a +=  1.0f * squarex / cmodel[num].n;
					b +=  1.0f * squarey / cmodel[num].n;
					if (j + 1 == cmodel[num].n || !cmodel[num].m[j + 1][k][i].s)
					{
						if (d)
						{
							square(a, b, c, a, b - 1.0f * squarey / cmodel[num].n, c - 1.0f * squarez / cmodel[num].n, cmodel[num].m[j][k][i].r - bshadow, cmodel[num].m[j][k][i].g - bshadow, cmodel[num].m[j][k][i].b - bshadow, cmodel[num].m[j][k][i].a);
						}
						else
						{
							tsquare(cmodel[num].m[j][k][i].t, a, b, c, a, b - 1.0f * squarey / cmodel[num].n, c - 1.0f * squarez / cmodel[num].n);
						}
					}
					if (k + 1 == cmodel[num].n || !cmodel[num].m[j][k + 1][i].s)
					{
						if (d)
						{
							square(a, b, c, a - 1.0f * squarex / cmodel[num].n, b, c - 1.0f * squarez / cmodel[num].n, cmodel[num].m[j][k][i].r - bshadow, cmodel[num].m[j][k][i].g - bshadow, cmodel[num].m[j][k][i].b - bshadow, cmodel[num].m[j][k][i].a);
						}
						else
						{
							tsquare(cmodel[num].m[j][k][i].t, a, b, c, a - 1.0f * squarex / cmodel[num].n, b, c - 1.0f * squarez / cmodel[num].n);
						}
					}
					if (i + 1 == cmodel[num].n * cmodel[num].h || !cmodel[num].m[j][k][i + 1].s)
					{
						if (d)
						{
							square(a, b, c, a - 1.0f * squarex / cmodel[num].n, b - 1.0f * squarey / cmodel[num].n, c, cmodel[num].m[j][k][i].r, cmodel[num].m[j][k][i].g, cmodel[num].m[j][k][i].b, cmodel[num].m[j][k][i].a);
						}
						else
						{
							tsquare(cmodel[num].m[j][k][i].t, a, b, c, a - 1.0f * squarex / cmodel[num].n, b - 1.0f * squarey / cmodel[num].n, c);
						}
					}
					c -=  1.0f * squarez / cmodel[num].n;
					a -=  1.0f * squarex / cmodel[num].n;
					//b += 1.0f * squarey / cmodel[num].n;
				}
				else
				{
					b += 1.0f * squarey / cmodel[num].n;
				}
			}
			b -= 1.0f;
			a += 1.0f * squarex / cmodel[num].n;
		}
		a -= 1.0f;
		c += 1.0f * squarez / cmodel[num].n;
	}
	c -= 1.0f;
}

void drawmonster(GLint i)
{
	drawmodel((GLint)monster[i][8] + 1, true);
}

void drawmarket()
{
	drawmodel(0, true);
}

void compstring(bool *a, GLint *b, string s, string s2, GLint *c, bool d = false)
{
	if (d)
	{
		if (s == s2 && *a)
		{
			//cout << s << ' ' << (*c) << '\n';
			*b = *c;
			*a = false;
		}
	}
	else
	{
		if (s == s2 && *a)
		{
			*c = *b;
			*a = false;
		}
	}
}

void compobjstring(obj *a, string s, GLint *b, bool d)
{
	bool c = true;
	compstring(&c, b, s, "timer", &(*a).timer, d);
	compstring(&c, b, s, "live", &(*a).live, d);
	compstring(&c, b, s, "edel", &(*a).edel, d);
	compstring(&c, b, s, "rare", &(*a).rare, d);
	compstring(&c, b, s, "shield", &(*a).shield, d);
	compstring(&c, b, s, "mpoints", &(*a).mpoints, d);
	compstring(&c, b, s, "points", &(*a).points, d);
	compstring(&c, b, s, "wtype", &(*a).wtype, d);
	compstring(&c, b, s, "t2", &(*a).t2, d);
	compstring(&c, b, s, "text", &(*a).text, d);
	compstring(&c, b, s, "size", &(*a).size, d);
	// name
	compstring(&c, b, s, "range", &(*a).range, d);
	compstring(&c, b, s, "attack", &(*a).attack, d);
	compstring(&c, b, s, "dist", &(*a).dist, d);
	compstring(&c, b, s, "type", &(*a).type, d);
	compstring(&c, b, s, "t", &(*a).t, d);
	compstring(&c, b, s, "bn", &(*a).bn, d);
	for (GLint i = 0; i < trapattackn; i++)
	{
		for(GLint j = 0; j < efsize; j++)
		{
			compstring(&c, b, s, "ef[" + to_string((long long)i) + "][" + to_string((long long)j) + "]", &(*a).ef[i][j], d);
		}
	}
	for (GLint i = 0; i < peffectnum; i++)
	{
		for(GLint j = 0; j < pefsize; j++)
		{
			compstring(&c, b, s, "pef[" + to_string((long long)i) + "][" + to_string((long long)j) + "]", &(*a).pef[i][j], d);
		}
	}
	// color[0]
	// color[1]
	// color[2]
}

void clickact(GLint mx2, GLint my2)
{
	GLint a = 0, i = 0, i2 = 0, i3 = 0;
	bool d = true, createchestb = true;
	if (phand[hand].type == 29)
	{
		for (i = 0; i < trapattackn; i++)
		{
			playeffect[i][0] += phand[hand].pef[i][2];
			if (playeffect[i][1] > 0)
			{
				playeffect[i][1] = min(playeffect[i][1], phand[hand].pef[i][0]);
			}
			else
			{
				playeffect[i][1] = phand[hand].pef[i][0];
			}
		}
		phand[hand].type = -1;
	}
	else
	{
		if (m1.map[mx2][my2][6] == 0)
		{
			if (m1.map[mx2][my2][9] == 0)
			{
				GLint window = m1.map[mx2][my2][7];
				for (i = 0; i < (deep + wallh + doorh); i++)
				{
					if (m1.block[mx2][my2][i] == 0)
					{
						if (window > 0)
						{
							window--;
						}
						else
						{
							if (phand[hand].type == -1)
							{
								/*if (m1.map[mx2][my2][9] != 0)
								{
									openchange = m1.map[mx2][my2][9] - 1;
									salenum = 0;
									moneynum = 0;
									for (GLint j = 0; j < pmx; j++)
									{
										for (GLint k = 0; k < pmy + 3; k++)
										{
											if (pb[j][k] == playchange[openchange].sale[salenum].b)
											{
												moneynum++;
											}
										}
									}
									menus = 6;
								}*/
								switch (m1.block[mx2][my2][i - 1])
								{
									case 4:
										openchest = m1.map[mx2][my2][3] - 1;
										menus = 3;
										break;
									case 6:
										opentable = m1.map[mx2][my2][4] - 1;
										menus = 4;
										break;
									default:
										break;
								}
							}
							else
							{
								if (phand[hand].t == 1)
								{
									if (i < (deep + wallh))
									{
										if (phand[hand].type == 12)
										{
											if (m1.map[mx2][my2][3] == 0)
											{
												m1.block[mx2][my2][i] = 4; // chest, thing
												createchestb = true;
												for (i2 = 0; i2 < m1.chest.size(); i2++)
												{
													if (m1.chestsize[i2] == -1)
													{
														createchestb = false;
														break;
													}
												}
												if (createchestb == true)
												{
													m1.chest.push_back(vector<obj> (chmaxnum));
													m1.chestsize.push_back(0);
												}
												for (i3 = 0; i3 < chmaxnum; i3++)
												{
													m1.chest[i2][i3].type = -1;
												}
												//m1.chest[i2][0] = 0;
												m1.map[mx2][my2][3] = i2 + 1;
											}
											else
											{
												d = false;
											}
										}
										else
										{
											if (phand[hand].type == 11)
											{
												if (m1.map[mx2][my2][4] == 0)
												{
													m1.map[mx2][my2][4] = phand[hand].wtype;
													m1.block[mx2][my2][i] = 6; // create, thing
												}
												else
												{
													d = false;
												}
											}
											else
											{
												if (phand[hand].type == 25)
												{
													if  ((i + doorh - 1) <= wallh + deep)
													{
														m1.map[mx2][my2][7] += doorh;
													}
												}
												else
												{
													if (phand[hand].type == 14) //&& phand[hand].type <= 24)
													{
														if (m1.map[mx2][my2][2] == 0)
														{
															mobj addobj;
															addobj.a = phand[hand];
															addobj.posx = mx2;
															addobj.posy = my2;
															addobj.posz = i - 1;
															m1.map[mx2][my2][2] = -m1.mblock.size() - 1;
															m1.mblock.push_back(addobj);
															m1.map[mx2][my2][5] = i - 1;
														}
													}
													else
													{
														if (phand[hand].type == 26)
														{
															if (m1.map[mx2][my2][8] == 0)
															{
																// = thing[phand[hand]][3];
																m1.map[mx2][my2][8] = playtower.size() + 1;
																tower a(mx2, my2, actmap, phand[hand].live, phand[hand].range);
																a.tparam[0][0] = phand[hand].attack;
																a.tparam[3][0] = phand[hand].shield;
																playtower.push_back(a);
																mobj addobj;
																//a.maxttimer = phand[hand].live + 100 * max(actmap - baselevel, baselevel - actmap);
																addobj.a = phand[hand];
																addobj.posx = mx2;
																addobj.posy = my2;
																addobj.posz = i;
																m1.block[mx2][my2][i] = -m1.mblock.size() - 1;
																m1.mblock.push_back(addobj);
															}
															else
															{
																d = false;
															}
														}
														else
														{
															if (phand[hand].type == 27)
															{
																mobj addobj;
																addobj.a = phand[hand];
																addobj.posx = mx2;
																addobj.posy = my2;
																addobj.posz = i;
																m1.block[mx2][my2][i] = -m1.mblock.size() - 1;
																m1.mblock.push_back(addobj);
																if (m1.map[mx2][my2][8] != 0)
																{
																	playtower[m1.map[mx2][my2][8] - 1].tparam[0][0] += phand[hand].range;
																	playtower[m1.map[mx2][my2][8] - 1].tparam[0][0] += phand[hand].live;
																	playtower[m1.map[mx2][my2][8] - 1].tparam[0][0] += phand[hand].shield;
																	m1.mblock.push_back(addobj);
																	playtower[m1.map[mx2][my2][8] - 1].towerb.push_back(addobj);
																}
															}
															else
															{
																m1.block[mx2][my2][i] = phand[hand].wtype;
															}
														}
													}
												}
											}
										}
										if (d)
										{
											if (mx2 == (GLint)playpos[0] && my2 == (GLint)playpos[1] && phand[hand].type != 25)
											{
												playpos[2]++;
											}
											phand[hand].type = -1;

											//bp++;
											if (hand == 0)
											{
												for (i2 = 0; i2 < pt[1].size; i2++)
												{
													if (pb[i2][pmy + 2].type != -1)
													{
														phand[0] = pb[i2][pmy + 2];
														pb[i2][pmy + 2].type = -1;
														break;
													}
												}
											}
											else
											{
												for (i2 = 0; i2 < pt[3].size; i2++)
												{
													if (pb[i2][pmy].type != -1)
													{
														phand[1] = pb[i2][pmy];
														pb[i2][pmy].type = -1;
														break;
													}
												}
											}
										}
									}
								}
								else
								{
									if (phand[hand].type >= 8 && phand[hand].type <= 9 && m1.block[mx2][my2][i - 1] != 2)
									{
										if (m1.block[mx2][my2][i - 1] == 4) // chest
										{
											if (phand[hand].type == 8)
											{
												if (taketsize < 60)
												{
													taket[taketsize] = thing[4];
													taketsize++;
												}
											}
											else
											{
												if (phand[hand].type == 9)
												{
													for (i2 = 0; i2 < chtree; i2++)
													{
														if (taketsize < 60)
														{
															taket[taketsize] = thing[5];
															taketsize++;
														}
													}
												}
											}
											for (i2 = 0; i2 < chmaxnum; i2++)
											{
												if (taketsize < 60 && m1.chest[m1.map[mx2][my2][3] - 1][i2].type != -1)
												{
													taket[taketsize] = m1.chest[m1.map[mx2][my2][3] - 1][i2];
													taketsize++;
												}
											}
											m1.chestsize[m1.map[mx2][my2][3] - 1] = -1;
											m1.map[mx2][my2][3] = 0;
											m1.block[mx2][my2][i - 1] = 0;
											if (mx2 = playpos[0] && my2 == playpos[1])
											{
												playpos[2]--;
											}
										}
										else
										{
											if (phand[hand].type == 8)
											{
												if (m1.block[mx2][my2][i - 1] == 6)
												{
													m1.map[mx2][my2][4] = 0;
												}
												if (m1.block[mx2][my2][i - 1] == 7)
												{
													m1.map[mx2][my2][7] -= doorh;
													if (m1.map[mx2][my2][7] < 0)
													{
														m1.map[mx2][my2][7] = 0;
													}
												}
												if (m1.block[mx2][my2][i - 1] < 0 && m1.mblock[-m1.block[mx2][my2][i - 1] - 1].a.type == 26)
												{
													bool b = true;
													for (GLint j = 0; j < z; j++)
													{
														if (m1.block[mx2][my2][j] < 0 && m1.mblock[-m1.block[mx2][my2][j] - 1].a.type == 26 && j != (i - 1))
														{
															b = false;
															break;
														}
													}
													if (b)
													{
														if (m1.map[mx2][my2][8] != playtower.size())
														{
															m1.map[playtower.back().posx][playtower.back().posy][8] = m1.map[mx2][my2][8] - 1;
															swap(playtower.back(), playtower[m1.map[mx2][my2][8] - 1]);
														}
														m1.map[mx2][my2][8] = 0;
														playtower.pop_back();
													}
												}
												if (m1.block[mx2][my2][i - 1] < 0 && m1.mblock[-m1.block[mx2][my2][i - 1] - 1].a.type == 27 && m1.map[mx2][my2][8] != 0)
												{
													playtower[m1.map[mx2][my2][8] - 1].tparam[0][0] -= m1.mblock[-m1.block[mx2][my2][i - 1] - 1].a.attack;
													playtower[m1.map[mx2][my2][8] - 1].tparam[1][0] -= m1.mblock[-m1.block[mx2][my2][i - 1] - 1].a.range;
													playtower[m1.map[mx2][my2][8] - 1].tparam[2][0] -= m1.mblock[-m1.block[mx2][my2][i - 1] - 1].a.live;
													playtower[m1.map[mx2][my2][8] - 1].tparam[3][0] -= m1.mblock[-m1.block[mx2][my2][i - 1] - 1].a.shield;
													playtower[m1.map[mx2][my2][8] - 1].towerb.pop_back();
												}
												if (taketsize < 60)
												{
													if (m1.block[mx2][my2][i - 1] < 0)
													{
														taket[taketsize] = m1.mblock[-m1.block[mx2][my2][i - 1] - 1].a;
													}
													else
													{
														taket[taketsize] = thing[m1.block[mx2][my2][i - 1]];
													}
													taketsize++;
												}
												freeblock(actmap, mx2, my2, i - 1);
												if (mx2 == playpos[0] && my2 == playpos[1] && m1.block[mx2][my2][i - 1] != 7) // door
												{
													playpos[2]--;
												}
												m1.block[mx2][my2][i - 1] = 0;
											}
										}
										srand ((unsigned int) time (NULL) * rand());
										if (phand[hand].bn != -1)
										{
											phand[hand].bn -= minbreak + rand() % (maxaddbreak + 1);
											if (phand[hand].bn <= 0)
											{
												phand[hand].type = -1;
											}
										}
									}
								}
							}
							break;
						}
					}
				}
			}
			else
			{
				/*if (m1.map[mx2][my2][9] != 0)
				{
					openchange = m1.map[mx2][my2][9] - 1;
					salenum = 0;
					moneynum = 0;
					for (GLint j = 0; j < pmx; j++)
					{
						for (GLint k = 0; k < pmy + 3; k++)
						{
							if (pb[j][k] == playchange[openchange].sale[salenum].b)
							{
								moneynum++;
							}
						}
					}
					menus = 6;
				}*/ // remake
			}
		}
	}
}
// remake delete tower
void mclick1() // menu
{
	GLfloat mx = 0.0f, my = 0.0f;
	searchmpos(&mx, &my);
	obj a;
	GLint i = 0, i2 = 0;
	if (mx < 0.175f && mx >= 0.16f && my < 0.020f && my >= 0.005f)
	{
		if (m1.map[(GLint)playpos[0]][(GLint)playpos[1]][9] != 0 && mb[0])
		{
			openchange = m1.map[(GLint)playpos[0]][(GLint)playpos[1]][9] - 1;
			salenum = 0;
			moneynum = 0;
			for (GLint j = 0; j < pmx; j++)
			{
				for (GLint k = 0; k < pmy + 3; k++)
				{
					if (pb[j][k].t2 == playchange[openchange].sale[salenum].b.t2 && pb[j][k].type == 28)
					{
						moneynum++;
					}
				}
			}
			menus = 6;
		}
		else
		{
			addopentable (3, true);
			addopentable (4, false);
		}
		mbutton[0] = true;
	}
	else
	{
		mbutton[0] = false;
		//if (mb[0])
		//{
		if (tb.second.type == -1 || tb.second.type < 8 || tb.second.type > 10)
		{
			if (mx < 0.02f && mx >= 0.005f && my < 0.02f && my >= 0.005f)
			{
				thingplace (1, mx, my);
			}
			if (mx < 0.055f && mx >= 0.04f && my < 0.04f && my >= 0.025f)
			{
				thingplace (2, mx, my);
			}
			if (mx < 0.055f && mx >= 0.04f && my < 0.06f && my >= 0.045f)
			{
				thingplace (3, mx, my);
			}
			if (mx < 0.055f && mx >= 0.04f && my < 0.08f && my >= 0.065f)
			{
				thingplace (4, mx, my);
			}
			if (mx < 0.02f && mx >= 0.005f && my < 0.1f && my >= 0.085f)
			{
				thingplace (5, mx, my);
			}
			if (mx < 0.055f && mx >= 0.04f && my < 0.12f && my >= 0.105f)
			{
				thingplace (6, mx, my);
			}
			if (mx < 0.02f && mx >= 0.005f && my < 0.14f && my >= 0.125f)
			{
				thingplace (7, mx, my);
			}

			/*if (mx < 0.09f && mx >= 0.075f && my < 0.02f && my >= 0.005f)
			{
				if (tb[0] == 0)
				{
					tb[1] = -8;
				}
				a = tb[0];
				tb[0] = phand[0];
				phand[0] = a;
			}
			if (mx < 0.15f && mx >= 0.135f && my < 0.02f && my >= 0.005f)
			{
				if (tb[0] == 0)
				{
					tb[1] = -9;
				}
				a = tb[0];
				tb[0] = phand[1];
				phand[1] = a;
			}*/

			if (mx < 0.17f && mx >= 0.07f && my < 0.035f && my >= 0.025f && pt[1].type != -1 && pt[1].size > (GLint)((mx - 0.07f) / 0.01f))
			{
				thingplace2 (2, mx, my);
			}
			/*if (mx < 0.17f && mx >= 0.07f && my < 0.055f && my >= 0.045f && thing[pt[2]][2] > (GLint)((mx - 0.07f) / 0.01f))
			{
				thingplace2 (a, 1, mx);
			}*/
			if (mx < 0.17f && mx >= 0.07f && my < 0.075f && my >= 0.065f && pt[3].type != -1 && pt[3].size > (GLint)((mx - 0.07f) / 0.01f))
			{
				thingplace2 (0, mx, my);
			}
			/*if (mx < 0.17f && mx >= 0.07f && my < 0.135f && my >= 0.085f && thing[pt[5]][2] > (GLint)((mx - 0.07f) / 0.01f - 10 * (GLint)((my - 0.135f) / 0.01f)))
			{
				if (tb[0] == 0)
				{
					tb[1] = 10 * (GLint)((my - 0.085f) / 0.01f) + (GLint)((mx - 0.07f) / 0.01f);
				}
				a = pb[(GLint)((mx - 0.07f) / 0.01f)][(GLint)((my - 0.085f) / 0.01f)];
				pb[(GLint)((mx - 0.07f) / 0.01f)][(GLint)((my - 0.085f) / 0.01f)]= tb[0];
				tb[0] = a;
			}*/
		}
		if (tb.second.type == -1 || tb.second.type >= 8 && tb.second.type <= 10)
		{
			if (mx < 0.17f && mx >= 0.07f && my < 0.055f && my >= 0.045f && pt[2].type != -1 && pt[2].size > (GLint)((mx - 0.07f) / 0.01f))
			{
				thingplace2 (1, mx, my);
			}
		}
		if (mx < 0.17f && mx >= 0.07f && my < 0.135f && my >= 0.085f && pt[5].type != -1 && pt[5].size > (GLint)((mx - 0.07f) / 0.01f - 10 * (GLint)((my - 0.135f) / 0.01f)))
		{
			if (mb[0])
			{
				if (tb.second.type == -1)
				{
					tb.first = 10 * (GLint)((my - 0.085f) / 0.01f) + (GLint)((mx - 0.07f) / 0.01f);
				}
				a = pb[(GLint)((mx - 0.07f) / 0.01f)][(GLint)((my - 0.085f) / 0.01f)];
				pb[(GLint)((mx - 0.07f) / 0.01f)][(GLint)((my - 0.085f) / 0.01f)] = tb.second;
				tb.second = a;
			}
			else
			{
				thingtext(mx, my, pb[(GLint)((mx - 0.07f) / 0.01f)][(GLint)((my - 0.085f) / 0.01f)]);
			}
		}
		if (mx < 0.09f && mx >= 0.075f && my < 0.02f && my >= 0.005f)
		{
			if (mb[0])
			{
				if (tb.second.type == -1)
				{
					tb.first = -8;
				}
				a = tb.second;
				tb.second = phand[0];
				phand[0] = a;
			}
			else
			{
				thingtext(mx, my, phand[0]);
			}
		}
		if (mx < 0.15f && mx >= 0.135f && my < 0.02f && my >= 0.005f)
		{
			if (mb[0])
			{
				if (tb.second.type == -1)
				{
					tb.first = -9;
				}
				a = tb.second;
				tb.second = phand[1];
				phand[1] = a;
			}
			else
			{
				thingtext(mx, my, phand[1]);
			}
		}
		if (mx < 0.07f && mx >= 0.055f && my < 0.02f && my >= 0.005f)
		{
			/*if (tb[0] != 0)
			{
				bp++;
			}*/
			if (mb[0])
			{
				tb.second.type = -1;
				tb.first = 0;
			}
			else
			{
				//thingtext(mx, my, "Recycle Bin");
			}
		}
		//}
		mb[0] = false;
	}
	if (tb.second.type != -1)
	{
		if (!thingtex)
		{
			glColor3f(tb.second.color[0], tb.second.color[0], tb.second.color[0]);
			square2d(mx - 0.005f, my - 0.005f, mx + 0.005f, my + 0.005f);
		}
		else
		{
			square2dt(tb.second, mx - 0.005f, my - 0.005f, mx + 0.005f, my + 0.005f);
		}
	}
}

void mclick2(GLint a)
{
	GLfloat mx = 0.0f, my = 0.0f;
	searchmpos(&mx, &my);
	if (mx < 0.13f && my >= 0.0725f - 0.02f * (a + taketsize / 20) - 0.0125f && mx >= 0.05f && my < 0.0725f - 0.02f * (a + taketsize / 20) + 0.0025f)
	{
		glColor3f(0.4f, 0.4f, 0.4f);
		if (mb[0])
		{
			taketsize = 0;
		}
	}
	else
	{
		glColor3f(0.2f, 0.2f, 0.2f);
	}
}

void mclick3(GLint a)
{
	obj b;
	GLfloat mx = 0.0f, my = 0.0f;
	searchmpos(&mx, &my);
	copentable(true, a);
	if (mx < 0.165f && mx >= 0.015f && my < 0.135f && my >= 0.045f)
	{
		if (mb[0])
		{
			if (tb.second.type == -1)
			{
				tb.first = (GLint)(6.0f - (my - 0.045f) / 0.015f) * 10 + (GLint)((mx - 0.015f) / 0.015f);
			}
			b = tb.second;
			tb.second = m1.chest[a][(GLint)((GLint)(6.0f - (my - 0.045f) / 0.015f) * 10 + (GLint)((mx - 0.015f) / 0.015f))];
			m1.chest[a][(GLint)((GLint)(6.0f - (my - 0.045f) / 0.015f) * 10 + (GLint)((mx - 0.015f) / 0.015f))] = b;
		}
		thingtext(mx, my, m1.chest[a][(GLint)((GLint)(6.0f - (my - 0.045f) / 0.015f) * 10 + (GLint)((mx - 0.015f) / 0.015f))]);
	}
	mb[0] = false;
}

void mclick4()
{
	vector<GLint> bcreateact (createmaxnum, 0);
	vector<obj> createact (createmaxnum);
	GLint i = 0, i2 = 0, i3 = 0;
	GLfloat b = 0;
	//GLint *createhelp;
	bool a = false;
	GLfloat mx = 0.0f, my = 0.0f;
	searchmpos(&mx, &my);
	copentable (false, 0);
	if (mx < 0.115f && mx >= 0.06f && my < 0.09f && my >= 0.08f)
	{
		if (mb[0])
		{
			for (i = 0; i < createnum2; i++)
			{
				a = false;
				for (i2 = 0; i2 < createnum - 16; i2++)
				{
					if (ct[opentable][i][i2] >= 0)
					{
						if (mcreate[i2] == createtnum[opentable][i][ct[opentable][i][i2]])
						{
							createact[ct[opentable][i][i2]].oadd(mcreate[i2]);
							bcreateact[ct[opentable][i][i2]]++;
						}
						else
						{
							a = true;
							break;
						}
					}
					else
					{
						if (ct[opentable][i][i2] == -1 && mcreate[i2].type != -1)
						{
							a = true;
							break;
						}
					}
				}
				for (i2 = 0; i2 < createact.size(); i2++)
				{
					if (bcreateact[i2] != 0)
					{
						createact[i2].od(bcreateact[i2]);
					}
				}
				if (a == false)
				{
					for (i2 = 0; i2 < createnum - 20; i2++)
					{
						mcreate[i2].type = -1;
					}
					for (i2 = createnum - 20; i2 < createnum - 16; i2++)
					{
						if (ct[opentable][i][i2] >= 0 && mcreate[i2].bn <= rand () % 100)
						{
							mcreate[i2].type = -1;
						}
					}
					for (i2 = createnum - 16; i2 < createnum; i2++)
					{
						if (ct[opentable][i][i2] >= 0)
						{
							mcreate[i2] = createtnum[opentable][i][ct[opentable][i][i2]];
						}
						else
						{
							mcreate[i2].type = -1;
						}
					}
					i2 = 25;
					GLint f = 0, d = 0, e = 0, fsum = 0;
					string s;
					char ch = 0, f2 = '+';
					bool xnum = false;
					for (i3 = 0; i3 < createf[opentable][i].size(); i3++)
					{
						ch = createf[opentable][i][i3];
						switch(f)
						{
						case -1:
							fsum += d;
							compobjstring(&mcreate[i2], s, &fsum, false);
							s.clear();
							d = 0;
							e = 0;
							f2 = '+';
							fsum = 0;
							f = 0;
							break;
						case 0:
							if (ch == ':')
							{
								f = 1;
							}
							else
							{
								s += ch;
							}
							break;
						case 1:
							switch(ch)
							{
							case '+':
								fsum += d;
								d = 0;
								f2 = '+';
								break;
							case '-':
								fsum += d;
								d = 0;
								f2 = '-';
								break;
							case '*':
								f2 = '*';
								break;
							case '/':
								f2 = '/';
								break;
							default:
								f2 = '+';
								break;
							}
							f = 2;
							break;
						case 2:
							e = 0;
							if (createf[opentable][i][i3] == 'x')
							{
								i3++;
								xnum = true;
							}
							for (; createf[opentable][i][i3] <= '9' && createf[opentable][i][i3] >= '0'; i3++)
							{
								e *= 10;
								e += createf[opentable][i][i3] - '0';
							}
							if (xnum)
							{
								compobjstring(&createact[e], s, &e, true);
								xnum = false;
							}
							switch (f2)
							{
							case '+':
								d += e;
								break;
							case '-':
								d -= e;
								break;
							case '*':
								d *= e;
								break;
							case '/':
								d /= e;
								break;
							default:
								break;
							}
							if (createf[opentable][i][i3] == ';')
							{
								f = -1;
							}
							else
							{
								f = 1;
							}
							i3--;
							break;
						default:
							break;
						}
					}
					break;
				}
			}
		}
		mbutton[4] = true;
	}
		for (i = 0; i < 4; i++)
		{
			if (mx < 0.07f + 0.015f * i && mx >= 0.06f + 0.015f * i && my < 0.11f && my >= 0.1f)
			{
				if (mb[0])
				{
					if (tb.second.type == -1)
					{
						tb.first = 1;
					}
					if (tb.second.type == -1 || tb.second.type == 13)
					{
						obj c;
						c = tb.second;
						tb.second = mcreate[i + 16];
						mcreate[i + 16] = c;
					}
				}
				else
				{
					thingtext(mx, my, mcreate[i + 16]);
				}
			}
		}
		cplace4 (0.005f, 0.07f, 0, true, mx, my);
		cplace4 (0.03f, 0.07f, 2, true, mx, my);
		cplace4 (0.005f, 0.095f, 8, true, mx, my);
		cplace4 (0.03f, 0.095f, 10, true, mx, my);
		cplace4 (0.12f, 0.07f, 20, false, mx, my);
		cplace4 (0.145f, 0.07f, 22, false, mx, my);
		cplace4 (0.12f, 0.095f, 28, false, mx, my);
		cplace4 (0.145f, 0.095f, 30, false, mx, my);
	mb[0] = false;
}

void mclick5()
{
	GLfloat mx = 0.0f, my = 0.0f;
	searchmpos(&mx, &my);
	if (mx >= 0.01f && mx < 0.045f && my >= 0.02f && my < 0.06f)
	{
		mbutton[5] = true;
		if (mb[0])
		{
			menur[1]--;
			if (menur[1] < 0)
			{
				menur[1] = createnum2 - 1;
			}
		}
	}
	if (mx >= 0.135f && mx < 0.17f && my >= 0.02f && my < 0.06f)
	{
		mbutton[6] = true;
		if (mb[0])
		{
			menur[1]++;
			if (menur[1] >= createnum2)
			{
				menur[1] = 0;
			}
		}
	}
	if (mx >= 0.055f && mx < 0.125f && my >= 0.015f && my < 0.0375f)
	{
		mbutton[7] = true;
		if (mb[0])
		{
			menur[0]--;
			if (menur[0] < 0)
			{
				menur[0] = createtables - 1;
			}
		}
	}
	if (mx >= 0.055f && mx < 0.125f && my >= 0.0425f && my < 0.065f)
	{
		mbutton[8] = true;
		if (mb[0])
		{
			menur[0]++;
			if (menur[0] >= createtables)
			{
				menur[0] = 0;
			}
		}
	}
	for (GLint i = 0; i < 4; i++)
	{
		if (mx < 0.07f + 0.015f * i && mx >= 0.06f + 0.015f * i && my < 0.11f && my >= 0.1f)
		{
			if (ct[menur[0]][menur[1]][16 + i] >= 0)
			{
				thingtext(mx, my, createtnum[menur[0]][menur[1]][ct[menur[0]][menur[1]][16 + i]]);
			}
		}
	}
	cplace4 (0.005f, 0.07f, 0, true, mx, my, false);
	cplace4 (0.03f, 0.07f, 2, true, mx, my, false);
	cplace4 (0.005f, 0.095f, 8, true, mx, my, false);
	cplace4 (0.03f, 0.095f, 10, true, mx, my, false);
	cplace4 (0.12f, 0.07f, 20, true, mx, my, false);
	cplace4 (0.145f, 0.07f, 22, true, mx, my, false);
	cplace4 (0.12f, 0.095f, 28, true, mx, my, false);
	cplace4 (0.145f, 0.095f, 30, true, mx, my, false);
	mb[0] = false;
}

void mclick6()
{
	GLfloat mx = 0.0f, my = 0.0f;
	searchmpos(&mx, &my);
	GLint a = 0;
	if (mx > 0.075f && my > 0.07f && mx <= 0.115f && my <= 0.09f)
	{
		a = playchange[openchange].sale[salenum].nb;
		mbutton[0] = true;
		if (mb[0])
		{
			if (moneynum >= playchange[openchange].sale[salenum].nb)
			{
				playchange[openchange].sale[salenum].n++;
				moneynum -= playchange[openchange].sale[salenum].nb;
				for (GLint i = 0; i < pmx && a > 0; i++)
				{
					for (GLint j = 0; j < pmy + 3 && a > 0; j++)
					{
						if (pb[i][j].type == 28 && pb[i][j].t2 == playchange[openchange].sale[salenum].b.t2 && a > 0)
						{
							pb[i][j].type = -1;
							a--;
						}
					}
				}
				if (taketsize < 60)
				{
					taketsize++;
					taket[taketsize] = playchange[openchange].sale[salenum].s;
				}
				if (playchange[openchange].sale[salenum].up != 0 && playchange[openchange].sale[salenum].n / playchange[openchange].sale[salenum].up >= 1)
				{
					playchange[openchange].sale[salenum].n = 0;
					playchange[openchange].sale[salenum].nb++;
				}
			}
		}
	}
	if (mx > 0.0185f && my > 0.06f && mx <= 0.031f && my <= 0.085f)
	{
		a = 0;
		mbutton[1] = true;
		if (mb[0])
		{
			salenum--;
			if (salenum < 0)
			{
				salenum = playchange[openchange].sale.size() - 1;
			}
			for (GLint i = 0; i < pmx; i++)
			{
				for (GLint j = 0; j < pmy + 3; j++)
				{
					if (pb[i][j].t2 == playchange[openchange].sale[salenum].b.t2 && pb[i][j].type == 28)
					{
						a++;
					}
				}
			}
			moneynum = a;
		}
	}
	if (mx > 0.152f && my > 0.06f && mx <= 0.1645f && my <= 0.085f)
	{
		a = 0;
		mbutton[2] = true;
		if (mb[0])
		{
			salenum++;
			if(salenum >= playchange[openchange].sale.size())
			{
				salenum = 0;
			}
			for (GLint i = 0; i < pmx; i++)
			{
				for (GLint j = 0; j < pmy + 3; j++)
				{
					if (pb[i][j].type == 28 && pb[i][j].t2 == playchange[openchange].sale[salenum].b.t2)
					{
						a++;
					}
				}
			}
			moneynum = a;
		}
	}
	if (mx > 0.045f && my > 0.07f && mx <= 0.065f && my <= 0.09f)
	{
		thingtext(mx, my, playchange[openchange].sale[salenum].b);
	}
	if (mx > 0.085f && my > 0.04f && mx <= 0.105f && my <= 0.06f)
	{
		thingtext(mx, my, playchange[openchange].sale[salenum].b);
	}
	if (mx > 0.125f && my > 0.07f && mx <= 0.145f && my <= 0.09f)
	{
		thingtext(mx, my, playchange[openchange].sale[salenum].s);
	}
	mb[0] = false;
}
// nothing about things??
void bclick() // block
{
	GLint i = 0, i2 = 0, i3 = 0;
	GLint a = 0;
	glTranslatef (0.0f, 0.0f, -33.0f);
	glColor3f (0.0f, 1.0f, 0.0f);
	GLfloat mx = 0.0f;
	GLfloat my = 0.0f;
	bsearchmpos(&mx, &my);
	GLint mx2 = (GLint) (mx + playpos[0]/* + 1/*+ (GLint)bmap[0]*/), my2 = (GLint) (my + playpos[1]/* - 42/*+ (GLint)bmap[1]*/);
	//square2d ((GLint)mx, (GLint)my, (GLint)mx + 1.0f, (GLint)my + 1.0f);
	/*if (thing[phand[hand]][0] == 10)
	{
		a = 0;
		for (GLint i = 0; i < 9; i++)
		{
			if (m1.map[mx2 - 1 + i / 3][my2 - 1 + i % 3][6] != 0)
			{
				a = m1.map[mx2 - 1 + i / 3][my2 - 1 + i % 3][6];
				break;
			}
		}
		if (a != 0)
		{
			monster[a - 1][3] -= thing[phand[hand]][1] * shildconst / (shildconst + monstert[(GLint)monster[a - 1][4]][4]);
		}
	}*/ // atack with cursor
	if (viewrotate == false && mb[0] && m1.map[mx2][my2][0] == 0/*m1.block[mx2][my2][deep] != 1*/ && mx > -4 && mx <= 4 && my > -4 && my <= 4)
	{
		clickact(mx2, my2);
	}
	mb[0] = false;
	glTranslatef ( 0.0f, 0.0f, 33.0f);
}

void mclickm1()
{
	GLfloat mx = 0.0f, my = 0.0f;
	searchmpos(&mx, &my);
	if (mx >= 0.0525f && my >= 0.025f && mx < 0.1375f && my < 0.045f)
	{
		mbutton[5] = true;
		if (mb[0])
		{
			startmenu = true;
			menus = -3;
			//exit(0);
		}
	}
	if (mx >= 0.0525f && my >= 0.05f && mx < 0.1375f && my < 0.07f)
	{
		mbutton[6] = true;
		if (mb[0])
		{
			menus = 0;
			pause2 = false;
		}
	}
	if (mx >= 0.0525f && my >= 0.075f && mx < 0.1375f && my < 0.095f)
	{
		mbutton[7] = true;
		if (mb[0])
		{
			menuinputs.clear();
			menus = -2;
			menusaveload = false;
		}
	}
	if (mx >= 0.0525f && my >= 0.1f && mx < 0.1375f && my < 0.12f)
	{
		mbutton[8] = true;
		if (mb[0])
		{
			menuinputs.clear();
			menus = -2;
			menusaveload = true;
		}
	}
	mb[0] = false;
}

void mclickm2()
{
	GLfloat mx = 0.0f, my = 0.0f;
	searchmpos(&mx, &my);
	if (mx >= 0.04f && my >= 0.055f && mx < 0.0875f && my < 0.07f)
	{
		mbutton[7] = true;
		if (mb[0])
		{
			if (startmenu)
			{
				menus = -3;
			}
			else
			{
				menus = 0;
				pause2 = false;
			}
		}
	}
	if (mx >= 0.0925f && my >= 0.055f && mx < 0.14f && my < 0.07f)
	{
		mbutton[8] = true;
		if (mb[0])
		{
			menuinputs += ".gamesave";
			if (menusaveload)
			{
				savename = menuinputs;
				savef();
			}
			else
			{
				loadname = menuinputs;
				loadf();
			}
			menus = 0;
			pause2 = false;
			startmenu = false;
		}
	}
	mb[0] = false;
}

void mclickm3()
{
	GLfloat mx = 0.0f, my = 0.0f;
	searchmpos(&mx, &my);
	if (mx >= 0.035f && my >= 0.0875f && mx < 0.145f && my < 0.1075f)
	{
		mbutton[0] = true;
		if (mb[0])
		{
			menus = -5;
			m5mbutton = -1;
			m5mlevel = -1;
			m5mstring.clear();
			if (gfirstinit)
			{
				for (GLint i = 0; i < levelsnum; i++)
				{
					free(mapsizexy[i]);
				}
				free(mapsizexy);
			}
			levelsnum = 10;
			mapsizexy = (GLint**) malloc(sizeof(GLint) * levelsnum);
			for (GLint i = 0; i < levelsnum; i++)
			{
				mapsizexy[i] = (GLint*) malloc(sizeof(GLint) * 2);
				mapsizexy[i][0] = constx;
				mapsizexy[i][1] = consty;
			}
		}
	}
	if (mx >= 0.035f && my >= 0.0625f && mx < 0.145f && my < 0.0825f)
	{
		mbutton[1] = true;
		if (mb[0])
		{
			menus = -2;
			menusaveload = false;
		}
	}
	if (mx >= 0.035f && my >= 0.0375f && mx < 0.145f && my < 0.0575f)
	{
		mbutton[2] = true;
		if (mb[0])
		{
			exit(0);
		}
	}
	mb[0] = false;
}

void mclickm4()
{
	if (mb[0])
	{
		menus = -3;
	}
	mb[0] = false;
}

void mclickm5()
{
	GLint a = 0, b = 0, c = 0, d = 0, r = 0, m5ml = 0;
	GLint **mapsizexy2;
	GLfloat mx = 0.0f, my = 0.0f;
	searchmpos(&mx, &my);
	glTranslatef(-0.09f, -0.07f, -0.18f);
	//glColor3f(0.0f, 0.5f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	//square2d(0.0f, 0.0f, 0.18f, 0.14f);
	tsquare(34, 0.0f, 0.0f, 0.18f, 0.14f);
	glBindTexture (GL_TEXTURE_2D, texture[0]);
	button newgameb(0.04f, 0.01f, 0.1f, 0.04f);
	//button helpb();
	button posxb(0.01f, 0.0625f, 0.1f, 0.0775f);
	button posyb(0.01f, 0.0425f, 0.1f, 0.0575f);
	button lnumb(0.01f, 0.0825f, 0.1f, 0.0975f);
	button levelallb(0.06f, 0.11f, 0.1f, 0.125f);
	button cancelb(0.01f, 0.11f, 0.05f, 0.125f);
	vector<button> lbutton;
	if (m5mlevel == -1)
	{
		b = 0;
		c = levelsnum;
	}
	else
	{
		b = m5mlevel;
		c = m5mlevel + 1;
	}
	if (mb[0])
	{
		for (GLint i = 0; i < m5mstring.size(); i++)
		{
			a *= 10;
			a += m5mstring[i] - '0';
		}
		for (GLint i = b; i < c; i++)
		{
			switch (m5mbutton)
			{
			case 0:
				if (a < 51)
				{
					a = 51;
				}
				mapsizexy[i][0] = a;
				break;
			case 1:
				if (a < 51)
				{
					a = 51;
				}
				mapsizexy[i][1] = a;
				break;
			case 2:
				if (a < 1)
				{
					a = 1;
				}
				mapsizexy2 = (GLint**) malloc(sizeof(GLint) * levelsnum);
				for (long i = 0; i < levelsnum; i++)
				{
					mapsizexy2[i] = (GLint*) malloc(sizeof(GLint) * 2);
					mapsizexy2[i][0] = mapsizexy[i][0];
					mapsizexy2[i][1] = mapsizexy[i][1];
					free(mapsizexy[i]);
				}
				free(mapsizexy);
				mapsizexy = (GLint**) malloc(sizeof(GLint) * a);
				for (GLint i = 0; i < a; i++)
				{
					mapsizexy[i] = (GLint*) malloc(sizeof(GLint) * 2);
					if (a > levelsnum)
					{
						mapsizexy[i][0] = constx;
						mapsizexy[i][1] = consty;
					}
					else
					{
						mapsizexy[i][0] = mapsizexy2[i][0];
						mapsizexy[i][1] = mapsizexy2[i][1];
					}
				}
				for (GLint i = 0; i < levelsnum; i++)
				{
					free(mapsizexy2[i]);
				}
				m5mlevel = a / 2;
				free(mapsizexy2);
				levelsnum = a;
				break;
			default:
				break;
			}
		}
		m5mstring.clear();
	}
	d = m5mlevel;
	if (d == -1)
	{
		d = 0;
	}
	if (m5mlevel >= 0)
	{
		m5ml = m5mlevel;
	}
	else
	{
		m5ml = levelsnum / 2;
	}
	for (GLint i = -m5mlbn / 2; i < m5mlbn - m5mlbn / 2; i++)
	{
		if (m5ml - i < levelsnum && m5ml - i >= 0)
		{
			button newlbutton(0.12f, 0.06f - 0.02f * i, 0.17f, 0.07f - 0.02f * i + 0.005f);
			lbutton.push_back(newlbutton);
		}
	}
	for (GLint i = -m5mlbn / 2; i < m5mlbn - m5mlbn / 2; i++)
	{
		if (m5ml - i >= 0 && m5ml - i < levelsnum)
		{
			if (i == 0 && m5mlevel != -1)
			{
				lbutton[r].clickb = true;
			}
			if (lbutton[r].bclick(mx, my))
			{
				m5mlevel = m5ml - i;
				m5mbutton = -1;
				break;
			}
			r++;
		}
	}
	//vector<button> lnumb;
	if (newgameb.bclick(mx, my))
	{
		newgame();
		menus = 0;
		m5mbutton = -1;
		startmenu = false;
		pause2 = false;
	}
	if (levelallb.bclick(mx, my))
	{
		m5mbutton = -1;
		m5mlevel = -1;
		//m5mlevel = levelsnum / 2;
	}
	if (posxb.bclick(mx, my))
	{
		m5mbutton = 0;
		m5mstring = to_string((long long)mapsizexy[d][0]);
	}
	if (posyb.bclick(mx, my))
	{
		m5mbutton = 1;
		m5mstring = to_string((long long)mapsizexy[d][1]);
	}
	if (lnumb.bclick(mx, my))
	{
		m5mbutton = 2;
		m5mstring = to_string((long long)levelsnum);
	}
	if (cancelb.bclick(mx, my))
	{
		menus = -3;
	}
	r = 0;
	if (mb[0])
	{
		m5mbutton = -1;
		mb[0] = false;
	}
	switch(m5mbutton)
	{
	case 0:
		posxb.clickb = true;
		break;
	case 1:
		posyb.clickb = true;
		break;
	case 2:
		lnumb.clickb = true;
	default:
		break;
	}
	glColor3f(1.0f, 1.0f, 1.0f);
	text("x: ", 0.015f, 0.07f, 0.0f);
	if (m5mbutton == 0)
	{
		text(m5mstring);
	}
	else
	{
		text(mapsizexy[d][0]);
	}
	text("y: ", 0.015f, 0.05f, 0.0f);
	if (m5mbutton == 1)
	{
		text(m5mstring);
	}
	else
	{
		text(mapsizexy[d][1]);
	}
	text("level: ", 0.015f, 0.09f, 0.0f);
	if (m5mbutton == 2)
	{
		text(m5mstring);
	}
	else
	{
		text(levelsnum);
	}
	text("Levels:", 0.135f, 0.12f, 0.0f);
	text("Create Game", 0.055f, 0.022f, 0.0f);
	text("cancel", 0.022f, 0.114f, 0.0f);
	text("all levels", 0.07f, 0.114f, 0.0f);
	newgameb.drawb();
	posxb.drawb();
	posyb.drawb();
	lnumb.drawb();
	levelallb.drawb();
	cancelb.drawb();
	r = 0;
	for (GLint i = -m5mlbn / 2; i < (m5mlbn - m5mlbn / 2); i++)
	{
		if (m5ml - i < levelsnum && m5ml - i >= 0)
		{
			glColor3f(1.0f, 1.0f, 1.0f);
			text(m5ml - i, 0.115f, 0.064f - i * 0.02f, 0.0f);
			lbutton[r].drawb();
			r++;
		}
	}
	glTranslatef(0.09f, 0.07f, 0.18f);
}

void playertick()
{
	shild = 0;
	GLint i = 0;
	for (i = 0; i < 7; i++)
	{
		shild += pt[i].shield;
	}
	shild *= (GLfloat)(100 + playsumeffect(2) + playeffect[2][1]) / 100;
}

void deletepn(GLint &i)
{
	if (i < (mpartnum.size() - 1))
	{
		swap(mpartnum[i], mpartnum.back());
		i--;
	}
	mpartnum.pop_back();
}

// menu anim time ??

/*GLint partcompfsn(const partnum &a, const partnum &b) // first pos, second pos, num
{
	return )a.pos.first > b.pos.first || (a.pos.second > b.pos.second && a.pos.first == b.pos.first) || (a.pnnum > b.pnnum && a.pos.second == b.pos.second && a.pos.first == b.pos.first));
}*/

void menu()
{
	// effect parts
	//sort(mpartnum.begin(), mpartnum.end(), partcompfsn);
	for (GLint i = 0; i < mpartnum.size(); i++)
	{
		GLint a = mpartnum[i].pnpos;
		if (menus == 0)
		{
			GLfloat b = 0.0f, c = 0.0f, d = 0.0f;
			bool e = false;
			if (a > 0) // monsters
			{
				if (a <= monster.size())// && mpartnum[i].stepn != -2)
				{
					b = monster[a - 1][0] - playpos[0];
					c = monster[a - 1][1] - playpos[1];
					d = monster[a - 1][2];
					if (monster[a - 1][7] == actmap)
					{
						e = true;
					}
				}
			}
			else
			{
				if (a == 0) // player
				{
					b = 0.0f;
					c = 0.0f;
					d = playpos[2];
					e = true;
				}
				else
				{
					b = playtower[-a - 1].posx;
					c = playtower[-a - 1].posy;
					d = deep + 3;
					if (playtower[-a - 1].tlevel == actmap)
					{
						e = true;
					}
				}
			}
			if (e)
			{
				mpartnum[i].pndraw(b, c, d - 44);
			}
		}
		if (partntimer + partntime <= glutGet(GLUT_ELAPSED_TIME))
		{
			mpartnum[i].pnadd();
			if (mpartnum[i].stepn >= pnmaxstepn) // || mpartnum == -1)
			{
				deletepn(i);
			}
		}
	}
	if (partntimer + partntime <= glutGet(GLUT_ELAPSED_TIME))
	{
		partntimer = glutGet(GLUT_ELAPSED_TIME);
	}
	// menu animation
	if (animboolm)
	{
		if (amact >= amactn)
		{
			if (amenu == -1)
			{
				menus2 = 0;
				menus = menus3;
			}
			if (amenu == 1 || (menus3 == 0 && amenu == -1))
			{
				menus2 = menus3;
				menus = menus3;
			}
			amenu = 0;
			animtimer = 0;
			amact = 0;
			ampos = 0.0f;
		}
		if (menus != menus2 && amenu == 0)
		{
			if (menus2 != 0)
			{
				amtime = 14;
				animtimer = 0;
				amact = 0;
				amenu = -1;
				ampos = 0.0f;
				menus3 = menus;
			}
			else
			{
				if (menus != 0)
				{
					amtime = 14;
					animtimer = 0;
					amact = 0;
					amenu = -1;
					amenu = 1;
					ampos = 0.15f;
					if (startmenu == false)
					{
						ampos /= 4;
						// ?? not add all ??
					}
					menus3 = menus;
				}
			}
		}
		if (animtimer + amtime <= glutGet(GLUT_ELAPSED_TIME))
		{
			animtimer = glutGet(GLUT_ELAPSED_TIME);
			amact++;
			if (startmenu == false)
			{
				amact += 3;
			}
			if (amenu == -1)
			{
				amact = amactn - amact;
			}
			if (amact <= 32)
			{
				ampos -= 0.005f * amenu;
			}
			else
			{
				if (amact <= 40)
				{
					amtime = 24;
					ampos += 0.0025f * amenu;
				}
				else
				{
					ampos -= 0.0025f * amenu;
				}
			}
			if (amenu == -1)
			{
				amact = amactn - amact;
			}
		}
		if (amenu == -1)
		{
			menus = menus2;
		}
		if (amenu == 1)
		{
			menus = menus3;
		}
		if (amenu != 0)
		{
			mb[0] = false;
			mb[1] = false;
			mb[2] = false;
			mp[0] = 0.0f;
			mp[1] = 0.0f;
			if (startmenu)
			{
				glTranslatef(0.0f, ampos, 0.0f);
			}
			else
			{
				glTranslatef(0.0f, ampos * 4.0f, 0.0f);
			}
		}
	}
	else
	{
		ampos = 0;
		amact = 0;
		amenu = 0;
		amtime = 0;
		animtimer = 0;
		menus2 = menus;
		menus3 = menus;
	}
	obj emptyobj;
	emptyobj.type = -1;
	GLint i = 0, i2 = 0, a = 0;
	GLfloat mx = 0, my = 0, trappos = 0, mtextpos = 0;
	//bap = thing[pt[1]][2] + thing[pt[2]][2] + thing[pt[3]][2] + thing[pt[5]][2] + 2;
	playertick();
	glBindTexture (GL_TEXTURE_2D, texture[0]);
	if (startmenu)
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -0.1801f);
		square2d(-0.4f, -0.4f, 0.4f, 0.4f);
		//glColor3f(1.0f, 1.0f, 1.0f);
		//tsquare(34, -0.15f, -0.15f, 0.15f, 0.15f);
		glTranslatef(0.0f, 0.0f, 0.1801f);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
	}
	if (taketsize > 0)
	{
		for (i = pmy - 1; i >= 0; i--) // only things in bag
		{
			for (i2 = 0; i2 < pmx; i2++)
			{
				if (i2 + (pmy - 1 - i) * pmx < pt[5].size)
				{
					if (pb[i2][i].type == -1 && taketsize > 0)
					{

						taketsize--;
						//if (taket[taket[0]] <= 10)
						//{
							pb[i2][i] = taket[taketsize];
							taket[taketsize].type = -1;
						//}
					}
				}
				else
				{
					break;
				}
			}
		}
		if (taketsize > 0)
		{
			takem = true;
		}
		else
		{
			takem = false;
		}
	}
	if (menus == 0 && takem)
	{
		menus = 2;
	}
	/*if (menus > 0)
	{
			glTranslatef (0.0f, 0.0f, -0.18f);
			glColor3f (0.0f, 0.5f, 0.0f);
			square2d (-0.09f, -0.0725f, 0.09f, 0.0725f);
			glTranslatef (0.0f, 0.0f, 0.18f);
	}*/
	switch (menus) // m > 0 - person menu, m < 0 game menu
	{
		case -5:
			mclickm5();
			break;
		case -4:
			glTranslatef(0.0f, 0.0f, -0.18f);
			text("YOU WIN!", -0.01f, 0.0f, 0.0f);
			glTranslatef(0.0f, 0.0f, 0.18f);
			mclickm4();
			break;
		case -3:
			glTranslatef(-0.09f, -0.0725f, -0.18f);
			//glColor3f(0.0f, 0.5f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			//square2d(0.03f, 0.0325f, 0.15f, 0.1125f);
			tsquare(34, 0.03f, 0.0325f, 0.15f, 0.1125f);
			glBindTexture (GL_TEXTURE_2D, texture[0]);
			buttoncolor(0);
			square2d(0.035f, 0.0875f, 0.145f, 0.1075f);
			buttoncolor(1);
			square2d(0.035f, 0.0625f, 0.145f, 0.0825f);
			buttoncolor(2);
			square2d(0.035f, 0.0375f, 0.145f, 0.0575f);
			glColor3f(1.0f, 1.0f, 1.0f);
			text("New Game", 0.08f, 0.0975f, 0.0f);
			text("Load", 0.085f, 0.0725f, 0.0f);
			text("Exit", 0.085f, 0.0475f, 0.0f);
			glTranslatef(0.085f, 0.0725f, 0.18f);
			mclickm3();
			break;
		case -2:
			glTranslatef(-0.09f, -0.0725f, -0.18f);
			//glColor3f(0.0f, 0.5f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			//square2d(0.035f, 0.05f, 0.145f, 0.095f);
			tsquare(34, 0.035f, 0.05f, 0.145f, 0.095f);
			glBindTexture (GL_TEXTURE_2D, texture[0]);
			buttoncolor(7);
			square2d(0.04f, 0.055f, 0.0875f, 0.07f);
			buttoncolor(8);
			square2d(0.0925f, 0.055f, 0.14f, 0.07f);
			glColor3f(1.0f, 1.0f, 1.0f);
			text("cancel", 0.055f, 0.061f, 0.0f);
			if (menusaveload)
			{
				text("save", 0.11f, 0.061f, 0.0f);
			}
			else
			{
				text("load", 0.11f, 0.061f, 0.0f);
			}
			text(menuinputs, 0.0425f, 0.08f, 0.0f);
			mclickm2();
			glTranslatef(0.09f, 0.0725f, 0.18f);
			break;
		case -1:
			glTranslatef(-0.09f, -0.0725f, -0.18f);
			//glColor3f(0.0f, 0.5f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			//square2d(0.0475f, 0.02f, 0.1425f, 0.125f);
			tsquare(34, 0.0475f, 0.02f, 0.1425f, 0.125f);
			glBindTexture (GL_TEXTURE_2D, texture[0]);
			buttoncolor(5);
			square2d(0.0525f, 0.025f, 0.1375f, 0.045f);
			buttoncolor(6);
			square2d(0.0525f, 0.05f, 0.1375f, 0.07f);
			buttoncolor(7);
			square2d(0.0525f, 0.075f, 0.1375f, 0.095f);
			buttoncolor(8);
			square2d(0.0525f, 0.1f, 0.1375f, 0.12f);
			glColor3f(1.0f, 1.0f, 1.0f);
			text("exit", 0.0875f, 0.03435f, 0.0f);
			text("return", 0.085f, 0.0585f, 0.0f);
			text("load", 0.0875f, 0.0835f, 0.0f);
			text("save", 0.0875f, 0.1085f, 0.0f);
			mclickm1();
			glTranslatef(0.09f, 0.0725f, 0.18f);
			break;
		case 0:
			//bclick(); ??
			glTranslatef(-0.09f, -0.0725f, -0.18f);
			if (!thingtex)
			{
				thingplace3 (1 - hand, phand, bcol[1]);
				square2d (0.035f, 0.0f, 0.05f, 0.02f);
				thingplace3 (hand, phand, bcol[1]);
				square2d (0.055f, 0.0f, 0.08f, 0.025f);
			}
			else
			{
				square2dt(phand[1 - hand], 0.035f, 0.0f, 0.05f, 0.015f);
				square2dt(phand[hand], 0.055f, 0.0f, 0.08f, 0.025f);
			}
			/*if (hand == 0)
			{
				glColor3f (0.0f, 0.5f, 0.0f);
			}
			else
			{*/
				glColor3f (0.3f, 0.2f, 0.0f);
			//}
			squareline (0.035f, 0.0f, 0.05f, 0.015f, 3.0f);
			//if (hand == 1)
			//{
				//glColor3f (0.0f, 0.5f, 0.0f);
			/*}
			else // add q
			{*/
				glColor3f (0.3f, 0.2f, 0.0f);
			//}
			squareline (0.055f, 0.0f, 0.08f, 0.025f, 3.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
            text(playerlevel, 0.008f, 0.128f, 0.0f);
            glColor3f(0.0f, 0.15f, 0.0f);
			square2d(0.0f, 0.12f, 0.02f, 0.14f);
			glColor3f(0.0f, 0.2f, 0.0f);
			square2d(0.002f, 0.122f, 0.018f, 0.138f);
			drawbar(0.085f, 0.0f, 0.18f, 0.008f, live, maxplaylive, true, 0.3f, 0.0f, 0.0f, 0.1f, 0.0f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			text(live, 0.09f, 0.002f, 0.0f);
			text(" / ");
			text(maxplaylive);
			drawbar(0.085f, 0.01f, 0.18f, 0.018f, playermp, maxplaymp * playerlevel, true, 0.0f, 0.0f, 0.3f, 0.0f, 0.0f, 0.1f);
			glColor3f(1.0f, 1.0f, 1.0f);
			text(playermp, 0.09f, 0.012f, 0.0f);
			text(" / ");
			text(maxplaymp * playerlevel);
			drawbar(0.02f, 0.14f, 0.14f, 0.134f, levelp, playlevel[0], true, 0.0f, 0.4f, 0.0f, 0.0f, 0.2f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			text(levelp, 0.025f, 0.135f, 0.0f);
			text(" / ");
			text(playlevel[0]);
			/*glColor3f (0.0f, 0.0f, 0.0f);
			square2d (-0.001f, 0.021f, 0.181f, 0.036f);
			glColor3f (0.4f, 0.4f, 0.4f);
			square2d (0.01f, 0.022f, 0.18f, 0.035f);
			glColor3f (0.5f, 0.0f, 0.0f);
			square2d (0.0f, 0.022f, 0.18f * ((GLfloat)live / maxlive), 0.035f);*/
			glTranslatef (0.09f, 0.0725f, 0.18f);
			glColor3f (1.0f, 1.0f, 1.0f);
			/*text("live:", -0.09f, -0.07f, -0.18f);
			text(live, -0.08f, -0.07f, -0.18f);
			text("shield:", 0.0675f, -0.07f, -0.18f);
			text((shild * (100 + playeffect[2][1])) / 100, 0.085f, -0.07f, -0.18f);
            text("    level: ", -0.0175f, -0.0455f, -0.18f);
			text(actmap);
			text("\nmagic points: ");
			text(playermp);
			text("\n      xp: ");
			text(levelp);
			text("\nmagic level:");
			text(playerlevel);*/
			text("map: ", -0.09f, -0.07f, -0.18f);
			text(actmap + 1);
			trappos = 0.0f;
			if (trapattack[0][0] > 0)
			{
				glColor3f(0.0f, 0.0f, 0.5f);
				text("HOLD", 0.07f, -0.06f + trappos, -0.18f);
				text(trapattack[0][0], 0.09f, -0.06f + trappos, -0.18f);
				trappos += 0.007f;
			}
			if (trapattack[1][0] > 0)
			{
				glColor3f(0.5f, 0.5f, 1.0f);
				text("SLOW", 0.07f, -0.06f + trappos, -0.18f);
				text(trapattack[1][0], 0.09f, -0.06f + trappos, -0.18f);
				trappos += 0.007f;
			}
			if (trapattack[2][0] > 0)
			{
				glColor3f(0.5f, 0.0f, 0.0f);
				text("ATTACK", 0.063f, -0.06f + trappos, -0.18f);
				text(trapattack[2][0], 0.09f, -0.06f + trappos, -0.18f);
				trappos += 0.007f;
			}
			if (playeffect[0][0] > 0)
			{
				glColor3f(0.0f, 0.5f, 0.0f);
				text("HEALTH", 0.063f, -0.06f + trappos, -0.18f);
				text(playeffect[0][0], 0.09f, -0.06f + trappos, -0.18f);
				trappos += 0.007f;
			}
			if (playeffect[1][0] > 0)
			{
				glColor3f(0.0f, 0.0f, 0.5f);
				text("ATTACK", 0.063f, -0.06f + trappos, -0.18f);
				text(playeffect[1][0], 0.09f, -0.06f + trappos, -0.18f);
				trappos += 0.007f;
			}
			if (playeffect[2][0] > 0)
			{
				glColor3f(0.8f, 0.8f, 0.8f);
				text("SHIELD", 0.063f, -0.06f + trappos, -0.18f);
				text(playeffect[2][0], 0.09f, -0.06f + trappos, -0.18f);
				trappos += 0.007f;
			}
			mtextpos = 0;
			glColor3f(1.0f, 1.0f, 1.0f);
			for (GLint i = 0; i < monster.size(); i++)
			{
				if (0.06f - mtextpos >= -0.038f && monster[i][7] == actmap && max(monster[i][0] - playpos[0], playpos[0] - monster[i][0]) <= monsterdistx && max(monster[i][1] - playpos[1], playpos[1] - monster[i][1]) <= monsterdisty)
				{
					text("MONSTER", -0.09f, 0.04f - mtextpos, -0.18f);
					text(monster[i][3], -0.058f, 0.04f - mtextpos, -0.18f);
					mtextpos += 0.007f;
				}
			}
			mtextpos = 0;
			for (i = 0; i < playtower.size(); i++)
			{
				if (0.06f - mtextpos >= -0.038f && playtower[i].tlevel == actmap && max(playtower[i].posx - playpos[0], playpos[0] - playtower[i].posx) <= towerdistx && max(playtower[i].posy - playpos[1], playpos[1] - playtower[i].posy) <= towerdisty)
				{
					text("TOWER", 0.058f, 0.06f - mtextpos, -0.18f);
					text(playtower[i].tparam[2][0], 0.082f, 0.06f - mtextpos, -0.18f);
					mtextpos += 0.007f;
				}
			}
			text("Z pos:", -0.09f, -0.06f, -0.18f);
			text("Y pos:", -0.09f, -0.053f, -0.18f);
			text("X pos:", -0.09f, -0.046f, -0.18f);
			text(playpos[2], -0.0725f, -0.06f, -0.18f);
			text(playpos[1], -0.0725f, -0.053f, -0.18f);
			text(playpos[0], -0.0725f, -0.046f, -0.18f);
			//cout << levelpos[actmap];
			if (levelpos[actmap] == 1)
			{
				text("NEXT WAVE:", -0.035f, 0.065f, -0.18f);
				text((min(levelwavetime[0][2], levelwavetime[0][0] + levelwavetime[0][1] * max(baselevel - actmap, actmap - baselevel)) - levelwavetimer[actmap][0]) / 60, 0.007f, 0.065f, -0.18f);
				text(":", 0.01f, 0.065f, -0.18f);
				text((min(levelwavetime[0][2], levelwavetime[0][0] + levelwavetime[0][1] * max(baselevel - actmap, actmap - baselevel)) - levelwavetimer[actmap][0]) % 60, 0.012f, 0.065f, -0.18f);
			}
			break;
		case 1:
			glTranslatef(-0.09f, -0.0725f, -0.18f);
			//glColor3f(0.0f, 0.5f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			//square2d(0.0f, 0.0f, 0.18f, 0.15f);
			tsquare(34, 0.0f, 0.0f, 0.18f, 0.15f);
			glBindTexture (GL_TEXTURE_2D, texture[0]);
			if (thingtex)
			{
				square2dt (pt[0], 0.005f, 0.005f, 0.02f, 0.02f);
				square2dt (pt[1], 0.04f, 0.025f, 0.055f, 0.04f);
				square2dt (pt[2], 0.04f, 0.045f, 0.055f, 0.06f);
				square2dt (pt[3], 0.04f, 0.065f, 0.055f, 0.08f);
				square2dt (pt[4], 0.005f, 0.085f, 0.02f, 0.1f);
				square2dt (pt[5], 0.04f, 0.105f, 0.055f, 0.12f);
				square2dt (pt[6], 0.005f, 0.125f, 0.02f, 0.140f);
			}
			else
			{
				thingplace3 (0, pt, bcol[0]);
				square2d (0.005f, 0.005f, 0.02f, 0.02f);
				thingplace3 (1, pt, bcol[0]);
				square2d (0.04f, 0.025f, 0.055f, 0.04f);
				thingplace3 (2, pt, bcol[0]);
				square2d (0.04f, 0.045f, 0.055f, 0.06f);
				thingplace3 (3, pt, bcol[0]);
				square2d (0.04f, 0.065f, 0.055f, 0.08f);
				thingplace3 (4, pt, bcol[0]);
				square2d (0.005f, 0.085f, 0.02f, 0.1f);
				thingplace3 (5, pt, bcol[0]);
				square2d (0.04f, 0.105f, 0.055f, 0.12f);
				thingplace3 (6, pt, bcol[0]);
				square2d (0.005f, 0.125f, 0.02f, 0.140f);
			}
			if (thingtex)
			{
				square2dt (phand[0], 0.075f, 0.005f, 0.09f, 0.02f);
				square2dt (phand[1], 0.135f, 0.005f, 0.15f, 0.02f);
			}
			else
			{
				thingplace3 (0, phand, bcol[1]);
				square2d (0.075f, 0.005f, 0.09f, 0.02f);
				thingplace3 (1, phand, bcol[1]);
				square2d (0.135f, 0.005f, 0.15f, 0.02f);
			}
			glColor3f (1.0f, 1.0f, 1.0f);
			square2d (0.055f, 0.005f, 0.07f, 0.02f);

			glColor3f (0.6f, 0.6f, 0.6f);
			square2d (0.07f, 0.025f, 0.17f, 0.035f);
			square2d (0.07f, 0.045f, 0.17f, 0.055f);
			square2d (0.07f, 0.065f, 0.17f, 0.075f);
			square2d (0.07f, 0.085f, 0.17f, 0.135f);
			thingplace4 (0, 0.065f);
			thingplace4 (1, 0.045f);
			thingplace4 (2, 0.025f);
			for (i = 0; i < pmy; i++)
			{
				thingplace4 (i - pmy, 0.085f + 0.01f * i);
			}
			buttoncolor (0);
			square2d (0.16f, 0.005f, 0.175f, 0.02f);
			glColor3f (0.2f, 0.2f, 0.2f);
			for (i = 0; i < 11; i++)
			{
				line (0.07f + i * 0.01f, 0.085f, 0.07f + i * 0.01f, 0.135f, 2.0f);
				line (0.07f + i * 0.01f, 0.025f, 0.07f + i * 0.01f, 0.035f, 2.0f);
				line (0.07f + i * 0.01f, 0.045f, 0.07f + i * 0.01f, 0.055f, 2.0f);
				line (0.07f + i * 0.01f, 0.065f, 0.07f + i * 0.01f, 0.075f, 2.0f);
			}
			for (i = 0; i < 12; i++)
			{
				line (0.07f, 0.025f + i * 0.01f, 0.17f, 0.025f + i * 0.01f, 2.0f);
			}
			//mclick1 ();
			glTranslatef (0.09f, 0.0725f, 0.18f);
			glColor3f (1.0f, 1.0f, 1.0f);
			text("Hands", 0.01f, -0.059f, -0.18f);
			if (phand[0].type == 10 || phand[1].type == 10)
			{
				text("attack: ", 0.001f, -0.066f, -0.18f);
			}
			if (phand[0].type == 10)
			{
				text(phand[0].attack * (GLfloat)(100 + playsumeffect(0) + playeffect[1][1]) / 100);
			}
			if (phand[0].type == 10 && phand[1].type == 10)
			{
				text(" / ", 0.001f, -0.066f, -0.18f);
			}
			if (phand[1].type == 10)
			{
				text(phand[1].attack * (GLfloat)(100 + playsumeffect(0) + playeffect[1][1]) / 100);
			}
			text("Boots", -0.065f, -0.059f, -0.18f);
			text("shield:", -0.065f, -0.066f, -0.18f);
			text(pt[0].shield, -0.048f, -0.066f, -0.18f);
			text("Shield", -0.065f, 0.021f, -0.18f);
			text("shield:", -0.065f, 0.014f, -0.18f);
			text(pt[4].shield, -0.048f, 0.014f, -0.18f);
			text("Hat", -0.065f, 0.061f, -0.18f);
			text("shield:", -0.065f, 0.054f, -0.18f);
			text(pt[6].shield, -0.048f, 0.054f, -0.18f);
			text("Pants", -0.085f, -0.039f, -0.18f);
			text("shield:", -0.085f, -0.046f, -0.18f);
			text(pt[1].shield, -0.068f, -0.046f, -0.18f);
			text("Belt", -0.085f, -0.019f, -0.18f);
			text("shield:", -0.085f, -0.026f, -0.18f);
			text(pt[2].shield, -0.068f, -0.026f, -0.18f);
			text("Jacket", -0.085f, 0.001f, -0.18f);
			text("shield:", -0.085f, -0.006f, -0.18f);
			text(pt[3].shield, -0.068f, -0.006f, -0.18f);
			text("Bag", -0.085f, 0.041f, -0.18f);
			text("shield:", -0.085f, 0.034f, -0.18f);
			text(pt[5].shield, -0.068f, 0.034f, -0.18f);
			glTranslatef (-0.09f, -0.0725f, -0.18f);
			mclick1 ();
			glTranslatef (0.09f, 0.0725f, 0.18f);
			break;
		case 2: // take things
			glTranslatef (0.0f, 0.0f, -0.18f);
			//glColor3f (0.0f, 0.5f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			a = 0;
			if (taketsize / 10 % 2 == 1 || taketsize % 10 != 0)
			{
				a++;
			}
			//square2d(-0.09f, -0.02f * (a + taketsize / 20) - 0.015f, 0.09f, 0.005f + 0.02f * (a + taketsize / 20));
			tsquare(34, -0.09f, -0.02f * (a + taketsize / 20) - 0.015f, 0.09f, 0.005f + 0.02f * (a + taketsize / 20));
			glBindTexture (GL_TEXTURE_2D, texture[0]);
			my = 0.065f; // 0.025f
			mx = -0.079f;
			for (i = 0, i2 = 0; i < 60; i++)
			{
				if (i / 10 > (3 - a - taketsize / 20) && i / 10 < (4 + a + taketsize / 20))
				{
					if (i2 < taketsize)
					{
						square2dt(taket[i2], mx, my, mx + 0.015f, my + 0.015f);
					}
					i2++;
				}
				if (i % 10 == 9)
				{
					mx = -0.084f;
					my -= 0.02f;
				}
				else
				{
					mx += 0.016f;
				}
			}
			mclick2 (a);
			square2d ( -0.04f, -0.02f * (a + taketsize / 20) - 0.0125f, 0.04f, -0.02f * (a + taketsize / 20) + 0.0025f);
			//glColor3f (1.0f, 1.0f, 1.0f);
			//text ("Delete things?", -0.035f, -0.02f * (a + taket[0] / 20) - 0.0075f, -0.18f);
			if (taketsize == 0)
			{
				taketsize = 0;
				takem = false;
				menus = 0;
			}
			glTranslatef (0.0f, 0.0f, 0.18f);
			glColor3f (1.0f, 1.0f, 1.0f);
			text ("Delete all things", -0.02f, -0.02f * (a + taketsize / 20) - 0.0075f, -0.18f);
			break;
		case 3: // chest
			glTranslatef (0.0f, 0.0f, -0.18f);
			//glColor3f (0.0f, 0.5f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			//square2d(-0.09f, -0.0725f, 0.09f, 0.0725f);
			tsquare(34, -0.09f, -0.0725f, 0.09f, 0.0725f);
			glBindTexture (GL_TEXTURE_2D, texture[0]);
			if (openchest2)
			{
				i = 0;
				i2 = 0;
				switch (pmove)
				{
					case -2:
						i2 = -1;
						break;
					case -1:
						i = -1;
						break;
					case 0:
						break;
					case 1:
						i = 1;
						break;
					case 2:
						i2 = 1;
					default:
						break;
				}
				if (m1.map[(GLint)playpos[0] + i][(GLint)playpos[1] + i2][3] != 0)
				{
					a = m1.map[(GLint)playpos[0] + i][(GLint)playpos[1] + i2][3] - 1;
					openchest = a;
				}
				else
				{
					a = openchest;
				}
				openchest2 = false;
			}
			else
			{
				a = openchest;
			}
			glColor3f (0.6f, 0.6f, 0.6f);
			square2d (-0.075f, -0.0275f, 0.075f, 0.0625f);
			//square2d (-0.075f, -0.0575f , 0.075f, -0.0425f);
			for (i = 1; i <= 60; i++)
			{
				if (thingtex)
				{
					square2dt(m1.chest[a][i - 1], (i - 1) % 10 * 0.015f - 0.075f, -(i - 1) / 10 * 0.015f + 0.0475f, (i - 1) % 10 * 0.015f - 0.06f, -(i - 1) / 10 * 0.015f + 0.0625f);
				}
				/*else
				{
					if (m1.chest[a][i] != 0)
					{
						glColor3f (tcolor[m1.chest[a][i]][0], tcolor[m1.chest[a][i]][1], tcolor[m1.chest[a][i]][2]);
						square2d ((i - 1) % 10 * 0.015f - 0.075f, -(i - 1) / 10 * 0.015f + 0.0475f, (i - 1) % 10 * 0.015f - 0.06f, -(i - 1) / 10 * 0.015f + 0.0625f);
					}
				}*/
			}
			glColor3f (0.2f, 0.2f, 0.2f);
			for (i = 0; i < 11; i++)
			{
				line (-0.075f + i * 0.015f, 0.0625f, -0.075f + i * 0.015f, -0.0275f, 3.0f);
				//line (-0.075f + i * 0.015f, -0.0425f, -0.075f + i * 0.015f, -0.0575f, 3.0f);
			}
			for (i = 0; i < 7; i++)
			{
				line (-0.075f, 0.0625f - i * 0.015f, 0.075f, 0.0625f - i * 0.015f, 3.0f);
			}
			glTranslatef (0.0f, 0.0f, 0.18f);
			text ("Chest", -0.005f, 0.065f, -0.18f);
			mopentable ();
			glTranslatef (-0.09f, -0.0725f, -0.18f);
			mclick3 (a);
			glTranslatef (0.09f, 0.0725f, 0.18f);
			break;
		case 4: // create
			glTranslatef (-0.09f, -0.0725f, -0.18f);
			//glColor3f(0.0f, 0.5f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			//square2d(0.0f, 0.0f, 0.18f, 0.145f);
			tsquare(34, 0.0f, 0.0f, 0.18f, 0.145f);
			glBindTexture (GL_TEXTURE_2D, texture[0]);
			mplace4 (0.005f, 0.07f, 0);
			mplace4 (0.03f, 0.07f, 2);
			mplace4 (0.005f, 0.095f, 8);
			mplace4 (0.03f, 0.095f, 10);
			mplace4 (0.12f, 0.07f, 20);
			mplace4 (0.145f, 0.07f, 22);
			mplace4 (0.12f, 0.095f, 28);
			mplace4 (0.145f, 0.095f, 30);
			/*glColor3f (0.8f, 0.8f, 0.6f);
			for (i = 0; i < 18; i++)
			{
				if (creatething > i)
				{
					square2d (0.06f + (i / 3) * 0.01f, 0.09f + 0.01f * (i % 3), 0.065f + (i / 3) * 0.01f, 0.095f + 0.01f * (i % 3));
				}
			}*/
			for (i = 0; i < 4; i++)
			{
				thingplace3 (16 + i, mcreate, bcol[3]);
				square2d (0.06f + 0.015f * i, 0.1f, 0.07f + 0.015f * i, 0.11f);
			}
			buttoncolor (4);
			square2d (0.06f, 0.08f, 0.115f, 0.09f);
			glTranslatef (0.09f, 0.0725f, 0.18f);
			glColor3f (1.0f, 1.0f, 1.0f);
			text ("Create", -0.009f, 0.01f, -0.18f);
			mopentable ();
			glTranslatef (-0.09f, -0.0725f, -0.18f);
			mclick4 ();
			glTranslatef (0.09f, 0.0725f, 0.18f);
			break;
		case 5:
			glTranslatef(-0.09f, -0.0725f, -0.18f);
			//glColor3f(0.0f, 0.5f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			//square2d(0.0f, 0.0f, 0.18f, 0.145f);
			tsquare(34, 0.0f, 0.0f, 0.18f, 0.145f);
			glBindTexture (GL_TEXTURE_2D, texture[0]);
			mplace4 (0.005f, 0.07f, 0, menur[0], menur[1]);
			mplace4 (0.03f, 0.07f, 2, menur[0], menur[1]);
			mplace4 (0.005f, 0.095f, 8, menur[0], menur[1]);
			mplace4 (0.03f, 0.095f, 10, menur[0], menur[1]);
			mplace4 (0.12f, 0.07f, 20, menur[0], menur[1]);
			mplace4 (0.145f, 0.07f, 22, menur[0], menur[1]);
			mplace4 (0.12f, 0.095f, 28, menur[0], menur[1]);
			mplace4 (0.145f, 0.095f, 30, menur[0], menur[1]);
			for (i = 0; i < 4; i++)
			{
				if (ct[menur[0]][menur[1]][16 + i] >= 0)
				{
					square2dt(createtnum[menur[0]][menur[1]][ct[menur[0]][menur[1]][16 + i]], 0.06f + 0.015f * i, 0.1f, 0.07f + 0.015f * i, 0.11f);
				}
				else
				{
					square2dt(emptyobj, 0.06f + 0.015f * i, 0.1f, 0.07f + 0.015f * i, 0.11f);
				}
			}
			buttoncolor(5);
			square2d(0.01f, 0.02f, 0.045f, 0.06f);
			buttoncolor(6);
			square2d(0.135f, 0.02f, 0.17f, 0.06f);
			buttoncolor(7);
			square2d(0.055f, 0.015f, 0.125f, 0.0375f);
			buttoncolor(8);
			square2d(0.055f, 0.0425f, 0.125f, 0.065f);
			mclick5();
			mgametime = glutGet(GLUT_ELAPSED_TIME);
			if (ctformulmovetime + ctformultimer <= mgametime && fview)
			{
				ctformultimer = mgametime;
				ctformulmove++;
			}
			if (createf[menur[0]][menur[1]].size() != 0)
			{
				ctformulmove = ctformulmove % createf[menur[0]][menur[1]].size();
			}
			else
			{
				ctformulmove = 0;
			}
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef (0.09f, 0.0725f, 0.18f);
			text("create:", 0.01f, 0.06f, -0.18f);
			text(menur[0] + 1, 0.03f, 0.06f, -0.18f);
			text("recept:", -0.03f, 0.06f, -0.18f);
			text(menur[1] + 1, -0.01f, 0.06f, -0.18f);
			if (fview)
			{
				text(createf[menur[0]][menur[1]].substr(ctformulmove, min(60, createf[menur[0]][menur[1]].size() - ctformulmove)) +
				createf[menur[0]][menur[1]].substr(0, min(ctformulmove, 60 - min(60, createf[menur[0]][menur[1]].size() - ctformulmove))),
				-0.0012f * min(60, createf[menur[0]][menur[1]].size()), 0.052f, -0.18f);
			}
			break;
		case 6: // market
			glTranslatef(-0.09f, -0.0725f, -0.18f);
			//glColor3f(0.0f, 0.5f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			//square2d(0.0f, 0.0325f, 0.18f, 0.1125f);
			tsquare(34, 0.0f, 0.0325f, 0.18f, 0.1125f);
			glBindTexture (GL_TEXTURE_2D, texture[0]);
			buttoncolor(0);
			square2d(0.075f, 0.07f, 0.115f, 0.09f);
			buttoncolor(1);
			square2d(0.0185f, 0.06f, 0.031f, 0.085f);
			buttoncolor(2);
			square2d(0.152f, 0.06f, 0.1645f, 0.085f);
			square2dt(playchange[openchange].sale[salenum].b, 0.045f, 0.07f, 0.065f, 0.09f);
			square2dt(playchange[openchange].sale[salenum].b, 0.085f, 0.04f, 0.105f, 0.06f);
			square2dt(playchange[openchange].sale[salenum].s, 0.125f, 0.07f, 0.145f, 0.09f);
			glColor3f(1.0f, 1.0f, 1.0f);
			text(playchange[openchange].sale[salenum].nb, 0.035f, 0.08f, 0.0f);
			text(moneynum, 0.075f, 0.0475f, 0.0f);
			text("change:", 0.085f, 0.1f, 0.0f);
			text(salenum + 1, 0.105f, 0.1f, 0.0f);
			text("buy", 0.09f, 0.0785f, 0.0f);
			glTranslatef(0.09f, 0.0725f, 0.18f);
			mclick6();
			break;
		default:
			break;
	}
	if (amenu != 0)
	{
		if (startmenu)
		{
			glTranslatef(0.0f, -ampos, 0.0f);
		}
		else
		{
			glTranslatef(0.0f, -ampos * 4.0f, 0.0f);
		}
	}
	glColor3f (0.0f, 0.0f, 0.0f);
	glTranslatef (0.0f, 0.0f, -0.18f);
	square2d (-0.1f, -1.0f, -1.0f, 1.0f);
	square2d (0.1f, -1.0f, 1.0f, 1.0f);
	square2d (-0.1f, 0.074f, 0.1f, 1.0f);
	square2d (-0.1f, -0.074f, 0.1f, -1.0f);
	glTranslatef (0.0f, 0.0f, 0.18f);
}

// num part - sort and add in one pos

void playermove()
{
	GLint k = 0;
	if (playmove[0] == 1 && playmove[1] == 1)
	{
		playmove[1] = 0;
	}
	if (pfirstmove != 0)
	{
		if ((GLint)(max(pfirstmove, -pfirstmove) / 2) == 1)
		{
			GLint a = 0, b = 0;
			if (pfirstmove > 0)
			{
				b = (GLint)m1.minmap[0];
				a = (GLint)playpos[0];
			}
			else
			{
				b = ceil(m1.minmap[0]);
				a = ceil(playpos[0]);
			}
			pfirstmove /= 2;
			if (m1.map[a + stepm * pfirstmove][(GLint)playpos[1]][0] == 0 && m1.block[a + stepm * pfirstmove][(GLint)playpos[1]][(GLint)playpos[2] + playjump] == 0)
			{
				m1.minmap[0] = stepm * pfirstmove + b;
				playpos[0] = stepm * pfirstmove + a;
			}
			else
			{
				playpos[0] = a;
				m1.minmap[0] = b;
			}
			playpos[1] = (GLint)playpos[1];
		}
		else
		{
			GLint a = 0, b = 0;
			if (pfirstmove > 0)
			{
				b = (GLint)m1.minmap[1];
				a = (GLint)playpos[1];
			}
			else
			{
				b = ceil(m1.minmap[1]);
				a = ceil(playpos[1]);
			}
			if (m1.map[(GLint)playpos[0]][a + (GLint)stepm * pfirstmove][0] == 0 && m1.block[(GLint)playpos[0]][a + (GLint)stepm * pfirstmove][(GLint)playpos[2] + playjump] == 0)
			{
				m1.minmap[1] = stepm * pfirstmove + b;
				playpos[1] = stepm * pfirstmove + a;
			}
			else
			{
				playpos[1] = a;
				m1.minmap[1] = b;
			}
			playpos[0] = (GLint)playpos[0];
		}
		playerjump(m1.block[(GLint)playpos[0]][(GLint)playpos[1]], playpos[2]);
		pfirstmove = 0;
	}
	if (playmove[0] != 0 && trapattack[0][0] == 0)
	{
		if (playpos[0] != (GLint)playpos[0] && playmove[0] < 0)
		{
			k++;
		}
		if (menus == 0 && !((playmove[0] > 0 && playpos[0] == x - 1) || (playmove[0] < 0 && playpos[0] == 0)) &&
		   /*(playpos[1] == (GLint)playpos[1] || m1.block[(GLint)(playpos[0] + playmove[0] + k)][(GLint)(playpos[1] + 1)][(GLint)playpos[2]] == 0) &&*/
		   m1.block[(GLint)(playpos[0] + playmove[0] + k)][(GLint)playpos[1]][(GLint)playpos[2] + playjump] == 0 &&
		   m1.map[(GLint)(playpos[0] + playmove[0] + k)][(GLint)playpos[1]][0] == 0)
		{
			if (trapattack[1][0] == 0 || speed >= trapattack[1][1])
			{
				GLfloat a = 0.0f;
				if (glutGet(GLUT_ELAPSED_TIME) < pmovetimer + pmovetime)
				{
					a = playmove[0] * stepm * (GLfloat)(glutGet(GLUT_ELAPSED_TIME) - pmovetimer) / (GLfloat)pmovetime;
				}
				else
				{
					a = playmove[0] * stepm;
				}
				if (playmove[0] > 0)
				{
					m1.minmap[0] = (GLint)m1.minmap[0];
					playpos[0] = (GLint)playpos[0];
				}
				else
				{
					m1.minmap[0] = ceil(m1.minmap[0]);
					playpos[0] = ceil(playpos[0]);
				}
				playerjump(m1.block[(GLint)(playpos[0] + playmove[0] + k)][(GLint)playpos[1]], playpos[2]);
				m1.minmap[0] += a;
				playpos[0] += a;
				pmove = playmove[0];
				speed = 0;
			}
			else
			{
				if (trapattack[1][0] > 0)
				{
					speed++;
				}
			}
			if (pmovetimer + pmovetime <= glutGet(GLUT_ELAPSED_TIME))
			{
				playmove[0] = 0;
			}
		}
		else
		{
			playmove[0] = 0;
		}
	}
	k = 0;
	if (playmove[1] != 0 && trapattack[0][0] == 0)
	{
		if (playmove[1] < 0 && playpos[1] != (GLint)playpos[1])
		{
			k++;
		}
		if (menus == 0 && !((playmove[1] > 0 && playpos[1] == y - 1) || (playmove[1] < 0 && playpos[1] == 0)) &&
		   /*(playpos[0] == (GLint)playpos[0] || m1.block[(GLint)(playpos[0] + 1)][(GLint)(playpos[1] + playmove[1] + k)][(GLint)playpos[2]] == 0) &&*/
		   m1.block[(GLint)playpos[0]][(GLint)(playpos[1] + playmove[1] + k)][(GLint)playpos[2] + playjump] == 0 &&
		   m1.map[(GLint)playpos[0]][(GLint)(playpos[1] + playmove[1] + k)][0] == 0)
		{
			if (trapattack[1][0] == 0 || speed >= trapattack[1][1] )
			{
				/*if (m1.block[(GLint)playpos[0]][(GLint)(playpos[1] + playmove[1] + k)][(GLint)playpos[2]] != 0)
				{
					playpos[2]++;
				}
				else
				{
					GLint i = 0;
					for (i = 0; i <= playpos[2]; i++)
					{
						if (m1.block[(GLint)playpos[0]][(GLint)(playpos[1] + playmove[1] + k)][i] == 0)
						{
							break;
						}
					}
					playpos[2] = i;
				}*/
				GLfloat a = 0.0f;
				if (glutGet(GLUT_ELAPSED_TIME) < pmovetimer + pmovetime)
				{
					a = playmove[1] * stepm * (GLfloat)(glutGet(GLUT_ELAPSED_TIME) - pmovetimer) / (GLfloat)pmovetime;
				}
				else
				{
					a = playmove[1] * stepm;
				}
				if (playmove[1] > 0)
				{
					m1.minmap[1] = (GLint)m1.minmap[1];
					playpos[1] = (GLint)playpos[1];
				}
				else
				{
					m1.minmap[1] = ceil(m1.minmap[1]);
					playpos[1] = ceil(playpos[1]);
				}
				playerjump(m1.block[(GLint)playpos[0]][(GLint)(playpos[1] + playmove[1] + k)], playpos[2]);
				m1.minmap[1] += a;
				playpos[1] += a;
				pmove = playmove[1] * 2;
				speed = 0;
			}
			else
			{
				if (trapattack[1][0] > 0)
				{
					speed++;
				}
			}
			if (pmovetimer + pmovetime <= glutGet(GLUT_ELAPSED_TIME))
			{
				playmove[1] = 0;
			}
		}
		else
		{
			playmove[1] = 0;
		}
	}
}
 // go to x and y ???
// move timer ??

void settime()
{
	if (time(NULL) > dtime)
	{
		dtime = time(NULL);
		addtime = true;
		dtime = time(NULL);
	}
}

void breaktime()
{
	addtime = false;
}

void playertrap()
{
	if (m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] != 0 && m1.map[(GLint)playpos[0]][(GLint)playpos[1]][5] + 1 == playpos[2])
	{
		//cout << '\n' << thing[m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] + 11][0] << ' ' << m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2];
		//cout << m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] + 11 << ' ' << thing[m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] + 11][1] / 100 << '\n';
		for (GLint i = 0; i < trapattackn; i++)
		{
			trapattack[i][0] += m1.mblock[-m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] - 1].a.ef[i][2];
			trapattack[i][1] = max(m1.mblock[-m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] - 1].a.ef[i][0], trapattack[i][1]);
		}
		//trapattack[thing[m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] + 131][1] % 100][0] += thing[m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] + 131][2];
		//trapattack[thing[m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] + 131][1] % 100][1] = max(thing[m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] + 131][1] / 100, trapattack[thing[m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] + 131][1] % 100][1]);
		if (rand() % 100 < m1.mblock[-m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] - 1].a.bn) // ?
		{
			if (taketsize < 60)
			{
				taket[taketsize] = m1.mblock[-m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] - 1].a;
				taketsize++;
			}
		}
		if (m1.mblock.size() - 1 != -m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] - 1)
		{
			if (m1.mblock.back().a.type != 14)
			{
				m1.block[(GLint)m1.mblock.back().posx][(GLint)m1.mblock.back().posy][(GLint)m1.mblock.back().posz] = m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2];
			}
			else
			{
				m1.map[(GLint)m1.mblock.back().posx][(GLint)m1.mblock.back().posy][2] = m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2];
			}
			swap(m1.mblock[-m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] - 1], m1.mblock.back());
			// add traps
		}
		m1.mblock.pop_back();
		//delete mblock
		m1.map[(GLint)playpos[0]][(GLint)playpos[1]][2] = 0;
		m1.map[(GLint)playpos[0]][(GLint)playpos[1]][5] = 0;
	}
}

void atrapstep()
{
	if (addtime)
	{
		GLint a = 0;
		for (long i = 0; i < trapattackn; i++)
		{
			if (trapattack[i][0] > 0)
			{
				trapattack[i][0]--;
				if (i != 1)
				{
					a += trapattack[i][1];
					live -= trapattack[i][1];
				}
			}
			else
			{
				trapattack[i][0] = 0;
				trapattack[i][1] = 0;
			}
		}
		if (a > 0)
		{
			partnum pn1(0, 0, a);
			mpartnum.push_back(pn1);
		}
	}
	//trapattack[0][0] > 0 - do not move
	/*if (trapattack[2][0] > 0 && addtime) // atack every second
	{
		live -= trapattack[2][1];
	}*/
	if (live <= 0) // lose
	{
		playermp = 0;
		playpos[0] = x / 2;
		playpos[1] = y / 2;
		m1.minmap[0] = (x - dy) / 2 - 1;
		m1.minmap[1] = (y - dy) / 2 - 1;
		playpos[2] = deep;
		initplayer();
		live = 100;
		menus = 0;
		taketsize = 0;
		tb.second.type = -1;
		tb.first = 0;
		for (GLint i = 0; i < trapattackn; i++)
		{
			trapattack[i][0] = 0;
			trapattack[i][1] = 0;
		}
		playerjump(m1.block[x / 2][y / 2], playpos[2]);
		for (GLint i = 0; i < mpartnum.size(); i++)
		{
			if (mpartnum[i].pnpos == 0)
			{
				deletepn(i);
			}
		}
	}
}

void playereffect()
{
	if (addtime)
	{
		GLint a = 0;
		for (GLint i = 0; i < peffectnum; i++)
		{
			if (playeffect[i][0] > 0)
			{
				playeffect[i][0]--;
			}
			else
			{
				if (playeffect[i][0] <= 0)
				{
					playeffect[i][1] = 0;
				}
			}
		}
		a += playeffect[0][1];
		live += playeffect[0][1];
		for (GLint i = 0; i < 7; i++)
		{
			if (pt[i].pef[0][3] >= pt[i].pef[0][4])
			{
				a += pt[i].pef[0][0];
				live += pt[i].pef[0][0];
				pt[i].pef[0][3] = 0;
			}
			else
			{
				pt[i].pef[0][3]++;
			}
		}
		if (a > 0)
		{
			partnum pn1(0, 1, a);
			mpartnum.push_back(pn1);
		}
		//live += playsumeffect(2);
	}
	if (live > maxplaylive)
	{
		live = maxplaylive;
	}
}

void drawtowerattack(GLfloat X, GLfloat Y, GLfloat Z, GLfloat X2, GLfloat Y2, GLfloat Z2)
{
	glColor3f(0.5f, 0.0f, 0.5f);
	//cout << X << ' ' << Y << ' ' << Z << ' ' << X2 << ' ' << Y2 << ' ' << Z2 << '\n';
	line(X, Y, Z, X2, Y2, Z2, 100000);
}

void playeratack(obj atackt, GLint atackposx, GLint atackposy, GLint akey, GLint akey2, GLint akey3, GLint akey4, GLint skey) // 1 - up, 2 - down, 3 - left, 4 - right
{
	mgametime = glutGet(GLUT_ELAPSED_TIME);
	if (mgametime >= handtimer[hand] + playerattacktime)
	{
		handtimer[hand] = mgametime;
		GLint a = atackposx - pattackrange[akey2];
		GLint b = atackposy - pattackrange[akey3];
		bool atackmonster = false;
		GLint atacktpos[2] = {0, 0};
		//atackkey[skey] = true;
		//cout << thing[atackt][4] << '\n';
		if (atackt.points == 0)
		{
			atackmonster = true;
		}
		else
		{
			if (phand[hand].wtype < wtypesnum)
			{
				for (GLint i = 0; i < pmx && atackmonster == false; i++)
				{
					for (GLint j = 0; j < pmy + 3 && atackmonster == false; j++)
					{
						if (pb[i][j].type == 0 && pb[i][j].t2 == atackt.points) // ??
						{
							atackmonster = true;
							atacktpos[0] = i;
							atacktpos[1] = j;
						}
					}
				}
			}
		}
		if (atackt.mpoints <= playermp)
		{
			atackmonster = true;
			playermp -= atackt.mpoints;
		}
		else
		{
			atackmonster = false;
		}
		if (atackmonster)
		{
			atackkey[skey] = true;
			for (GLint i = 0; i <= (pattackrange[akey] + pattackrange[akey2]); i++)
			{
				if (i + a >= 0 && i + a < x)
				{
					for (GLint j = 0; j <= (pattackrange[akey3] + pattackrange[akey4]); j++)
					{
						if (j + b >= 0 && j + b < y)
						{
							if (m1.map[i + a][j + b][6] != 0)
							{
								GLint c = m1.map[i + a][j + b][6] - 1;
								if (phand[hand].wtype < wtypesnum)
								{
									GLint d = (phand[hand].attack * shildconst * ((GLfloat)(100 + playeffect[1][1] + playsumeffect(1)) / 100)) / (shildconst + emonster[c].monstert[4]);
									if (d > 0)
									{
										partnum pn1(c + 1, 0, d);
										mpartnum.push_back(pn1);
									}
									monster[c][3] -= d;
									if (monster[c][3] <= 0)
									{
										levelp += emonster[i].monstert[9];
									}
								}
								else
								{
									for (GLint i2 = 0; i2 < trapattackn; i2++)
									{
										emonster[c].effect[i][0] += phand[hand].ef[i][2];
										emonster[c].effect[i][1] = phand[hand].ef[i][0];
									}
								}
							}
						}
					}
				}
			}
			if (atackt.points != -1)
			{
				pb[atacktpos[0]][atacktpos[1]].type = -1;
			}
			if (phand[hand].bn != -1)
			{
				phand[hand].bn -= minbreak + rand() % (maxaddbreak + 1);
				if(phand[hand].bn == 0)
				{
					phand[hand].type = -1;
				}
			}
		}
	}
}

GLint playerattackt(obj *athingpos, GLint akey, GLint akey2, GLint akey3, GLint akey4) // player attack types, return dist & init range
{
	GLint a = 0, i = 0;
	for (i = 0; i < 4; i++)
	{
		pattackrange[i] = 0;
	}
	switch((*athingpos).wtype)
	{
	case 0: // sword(1)
		a = 1;
		pattackrange[akey3] = 1;
		pattackrange[akey4] = 1;
		break;
	case 1: // spear(line)
		a = max((*athingpos).dist, (*athingpos).range);
		pattackrange[akey2] = max((*athingpos).range, (*athingpos).dist) - 1;
		break;
	case 2: // mace(cicle)
		a = 1;
		for (i = 0; i < 4; i++)
		{
			pattackrange[i] = (*athingpos).range;
		}
		break;
	case 3: // bow(shoot line)
		a = (*athingpos).dist;
		pattackrange[akey] = (*athingpos).range;
		break;
	case 4: // arbalest(shoot cicle)
		a = (*athingpos).dist;
		for (i = 0; i < 4; i++)
		{
			pattackrange[i] = (*athingpos).range;
		}
		break;
	case 5:
		a = (*athingpos).dist;
		for (i = 0; i < 4; i++)
		{
			pattackrange[i] = (*athingpos).range;
		}
		break;
	case 6:
		a = (*athingpos).dist;
		for (i = 0; i < 4; i++)
		{
			pattackrange[i] = (*athingpos).range;
		}
		break;
	case 7:
		a = (*athingpos).dist;
		for (i = 0; i < 4; i++)
		{
			pattackrange[i] = (*athingpos).range;
		}
		break;
	default:
		break;
	}
	return a;
}

void minimap()
{
	GLint i = 0, i2 = 0, i3 = 0;
	glBindTexture (GL_TEXTURE_2D, texture[1]);
	glTranslatef (0.068f, 0.04f, -0.2f);
	//square (0.01f, 0.01f, 0.0f, r, g, b);
	square (-squarexm, -squareym, 0.0f, squarexm * (dy + 2), squareym * (dy + 2), 0.0f, 0.2f, 0.2f, 0.2f);
	for (i = (GLint)m1.minmap[0]; i < ((GLint)m1.minmap[0] + dx); i++)
	{
		for (i2 = (GLint)m1.minmap[1]; i2 < ((GLint)m1.minmap[1] + dy); i2++)
		{
			if (i < x && i2 < y && i >= 0 && i2 >= 0)
			{
				if (m1.map[i][i2][9] != 0)
				{
					square(0.0f, 0.0f, 0.0f, squarexm, squareym, 0.0f, 0.0f, 0.0f, 0.5f);
				}
				else
				{
					if (m1.map[i][i2][6] != 0)
					{
						square(0.0f, 0.0f, 0.0f, squarexm, squareym, 0.0f, 0.5f, 0.0f, 0.0f);
					}
					else
					{
						if (m1.map[i][i2][3] != 0)
						{
							square(0.0f, 0.0f, 0.0f, squarexm, squareym, 0.0f, 0.5f, 0.4f, 0.0f);
						}
						else
						{
							if (m1.map[i][i2][0] == 0)
							{
								square(0.0f, 0.0f, 0.0f, squarexm, squareym, 0.0f, 0.6f, 0.6f, 0.6f);
							}
							else
							{
								square(0.0f, 0.0f, 0.0f, squarexm, squareym, 0.0f, 0.0f, 0.0f, 0.0f);
							}
						}
					}
				}
			}
			else
			{
				square(0.0f, 0.0f, 0.0f, squarexm, squareym, 0.0f, 0.0f, 0.0f, 0.0f);
			}
			glTranslatef (0.0f, squareym, 0.0f);
		}
		glTranslatef (squarexm, -(dy * squareym), 0.0f);
	}
	glTranslatef (-(squarexm * dx), 0.0f, 0.0f);
	square((playpos[0] - (GLint)m1.minmap[0]) * squarexm, (playpos[1] - (GLint)m1.minmap[1]) * squareym,
		0.0f, squarexm + squarexm * (playpos[0] - (int)m1.minmap[0]),
		squareym + squarexm * (playpos[1] - (int)m1.minmap[1]), 0.0f, 0.0f, 0.5f, 0.0f);
	glTranslatef (-0.068f, -0.04f, 0.2f);
}

void bigmap()
{
	GLint i = 0, i2 = 0, i3 = 0, blocktexture = 0;
	GLfloat r[2], g[2], b[2], a[2];
	bool atackviewpos = false;
	bmap[0] = (GLint)(playpos[0] - dx2 / 2);
	bmap[1] = (GLint)(playpos[1] - dy2 / 2);
	glTranslatef(0.0f, 0.0f, (playpos[2] - 44 + deep - 1) * squarez);
	drawplayer();
	glTranslatef(0.0f, 0.0f, (-playpos[2] + 44 - deep + 1) * squarez);
	for (GLint i = 0; i < monster.size(); i++)
	{
		if (monster[i][7] == actmap && monster[i][0] >= bmap[0] && monster[i][0] < bmap[0] + dx2 && monster[i][1] >= bmap[1] && monster[i][1] < bmap[1] + dy2)
		{
			glTranslatef((monster[i][0] - playpos[0]) * squarex, (monster[i][1] - playpos[1]) * squarey, (monster[i][2] - 44 + deep - 1) * squarez);
			drawmonster(i);
			glTranslatef((-monster[i][0] + playpos[0]) * squarex, (-monster[i][1] + playpos[1]) * squarey, (-monster[i][2] + 44 - deep + 1) * squarez);
		}
	}
	glTranslatef (-playpos[0] * squarex + bmap[0], -playpos[1] * squarey + bmap[1], deep * squarez - 44); //playpos[2] * squarez - 44);
	for (i = 0; i < z; i++)
	{
		for (i2 = bmap[0]; i2 < bmap[0] + dx2; i2++)
		{
			for (i3 = bmap[1]; i3 < bmap[1] + dy2; i3++)
			{
				atackviewpos = false;
				if (i2 < x && i2 >= 0 && i3 < y && i3 >= 0)
				{
					/*if (i2 == playpos[0] && i3 == playpos[1] && i == playpos[2] - 1)
					{
						//square (squarex, squarey, 0.0f, 1.0f, 0.0f, 0.0f);
						drawplayer();
					}*/
					/*if (m1.map[i2][i3][6] != 0 && monster[m1.map[i2][i3][6] - 1][2] == i + 1)
					{
						drawmonster(m1.map[i2][i3][6] - 1);
						//drawmonster(monstercolor[monster[j][4]]);
					}*/
					if (m1.map[i2][i3][9] != 0 && playchange[m1.map[i2][i3][9] - 1].posz == i + 1)
					{
						drawmarket();
					}
					if (m1.block[i2][i3][i] != 0)
					{
						if (m1.block[i2][i3][i] > 0)
						{
							// ??
							if (m1.block[i2][i3][i] > thing.size() || m1.block[i2][i3][i] < 0)
							{
								m1.block[i2][i3][i] = 0;
								//cout << m1.block[i2][i3][i] << '\n';
							}
							else
							{
								if (thing[m1.block[i2][i3][i]].type == 11)
								{
									blocktexture = blocktext - 1;
								}
								else
								{
									if (thing[m1.block[i2][i3][i]].type == 12)
									{
										blocktexture = blocktext;
									}
									else
									{
										blocktexture = thing[m1.block[i2][i3][i]].text + blocktext;
									}
								}
								if (i2 == x / 2 && i3 == y / 2  && i == deep - 1)
								{
									r[0] = 0.0f;
									g[0] = 0.0f;
									b[0] = 0.8f;
									a[0] = 1.0f;
									r[1] = 0.0f;
									g[1] = 0.0f;
									b[1] = 1.0f;
									a[1] = 1.0f;
								}
								else
								{
									r[0] = thing[m1.block[i2][i3][i] - 1].color[0] - 0.3f;
									g[0] = thing[m1.block[i2][i3][i] - 1].color[1] - 0.3f;
									b[0] = thing[m1.block[i2][i3][i] - 1].color[2] - 0.3f;
									a[0] = 1.0f;
									r[1] = thing[m1.block[i2][i3][i] - 1].color[0] - 0.1f;
									g[1] = thing[m1.block[i2][i3][i] - 1].color[1] - 0.1f;
									b[1] = thing[m1.block[i2][i3][i] - 1].color[2] - 0.1f;
									a[1] = 1.0f;
								}
							}
							// remake
						}
						else
						{
							if (m1.mblock[-m1.block[i2][i3][i] - 1].a.type == 26)
							{
								blocktexture = blocktext - 2;
							}
							else
							{
								if (m1.mblock[-m1.block[i2][i3][i] - 1].a.type == 27)
								{
									blocktexture = blocktext - 3;
								}
								else
								{
									blocktexture = 16;
								}
							}
							if (i2 == x / 2 && i3 == y / 2 && i == deep - 1)
							{
								r[0] = 0.0f;
								g[0] = 0.0f;
								b[0] = 0.8f;
								a[0] = 1.0f;
								r[1] = 0.0f;
								g[1] = 0.0f;
								b[1] = 1.0f;
								a[1] = 1.0f;
							}
							else
							{
								r[0] = 0.8f;//m1.mblock[-m1.block[i2][i3][i] - 1].a.color[0] - 0.3f;
								g[0] = 0.8f;//m1.mblock[-m1.block[i2][i3][i] - 1].a.color[1] - 0.3f;
								b[0] = 0.8f;//m1.mblock[-m1.block[i2][i3][i] - 1].a.color[2] - 0.3f;
								a[0] = 1.0f;
								r[1] = 1.0f;//m1.mblock[-m1.block[i2][i3][i] - 1].a.color[0] - 0.1f;
								g[1] = 1.0f;//m1.mblock[-m1.block[i2][i3][i] - 1].a.color[1] - 0.1f;
								b[1] = 1.0f;//m1.mblock[-m1.block[i2][i3][i] - 1].a.color[2] - 0.1f;
								a[1] = 1.0f;
							}
						}
						if (m1.map[i2][i3][2] != 0 && m1.map[i2][i3][5] == i)
						{
							r[1] -= 0.05f;
							g[1] -= 0.05f;
							b[1] -= 0.05f; // ??
						}
						//cout << 1 << '\n';
						if (phand[hand].type == 10 && atackview && m1.map[i2][i3][0] != 1)
						{
							//cout << 1;
							playerattackt(&phand[hand], 1, 3, 0, 2);
							//cout << 2;
							if (i2 >= playpos[0] + phand[hand].dist - pattackrange[3] &&
							i2 <= playpos[0] + phand[hand].dist + pattackrange[1] &&
							i3 <= playpos[1] + pattackrange[0] &&
							i3 >= playpos[1] - pattackrange[2])
							{
								if (atackkey[0])
								{
									r[1] = atackviewcolor[3];
									g[1] = atackviewcolor[4];
									b[1] = atackviewcolor[5];
									a[1] = 1.0f;
									atackviewpos = true;
									//atackkey[0] = false;
								}
								else
								{
									if (atackviewpos == false)
									{
										r[1] = atackviewcolor[0];
										g[1] = atackviewcolor[1];
										b[1] = atackviewcolor[2];
										a[1] = 0.2f;
									}
								}
							}
							playerattackt(&phand[hand], 0, 2, 1, 3);
							if (i2 >= playpos[0] - pattackrange[3] &&
							i2 <= playpos[0] + pattackrange[1] &&
							i3 <= playpos[1] + pattackrange[0] + phand[hand].dist &&
							i3 >= playpos[1] - pattackrange[2] + phand[hand].dist)
							{
								if (atackkey[1])
								{
									r[1] = atackviewcolor[3];
									g[1] = atackviewcolor[4];
									b[1] = atackviewcolor[5];
									a[1] = 1.0f;
									atackviewpos = true;
									//atackkey[1] = false;
								}
								else
								{
									if (atackviewpos == false)
									{
										r[1] = atackviewcolor[0];
										g[1] = atackviewcolor[1];
										b[1] = atackviewcolor[2];
										a[1] = 0.2f;
									}
								}
							}
							playerattackt(&phand[hand], 1, 3, 0, 2);
							if (i2 >= playpos[0] - pattackrange[1] - phand[hand].dist &&
								i2 <= playpos[0] + pattackrange[3] - phand[hand].dist &&
							i3 <= playpos[1] + pattackrange[0] &&
							i3 >= playpos[1] - pattackrange[2])
							{
								if (atackkey[2])
								{
									r[1] = atackviewcolor[3];
									g[1] = atackviewcolor[4];
									b[1] = atackviewcolor[5];
									a[1] = 1.0f;
									atackviewpos = true;
									//atackkey[2] = false;
								}
								else
								{
									if (atackviewpos == false)
									{
										r[1] = atackviewcolor[0];
										g[1] = atackviewcolor[1];
										b[1] = atackviewcolor[2];
										a[1] = 0.2f;
									}
								}
							}
							playerattackt(&phand[hand], 0, 2, 1, 3);
							if (i2 >= playpos[0] - pattackrange[3] &&
							i2 <= playpos[0] + pattackrange[1] &&
							i3 <= playpos[1] + pattackrange[2] - phand[hand].dist &&
							i3 >= playpos[1] - pattackrange[0] - phand[hand].dist)
							{
								if (atackkey[3])
								{
									r[1] = atackviewcolor[3];
									g[1] = atackviewcolor[4];
									b[1] = atackviewcolor[5];
									a[1] = 1.0f;
									atackviewpos = true;
									//atackkey[3] = false;
								}
								else
								{
									if (atackviewpos == false)
									{
										r[1] = atackviewcolor[0];
										g[1] = atackviewcolor[1];
										b[1] = atackviewcolor[2];
										a[1] = 0.2f;
									}
								}
							}
						}
						//glColor3f(0.8f, 0.8f, 0.8f);
						glColor3f(r[0], g[0], b[0]);
						//cout << 2 << ' ';
						if (i2 > 0 && m1.block[i2 - 1][i3][i] == 0)
						{
							if (thingtex)
							{
								tsquare(blocktexture, 0.0f, 0.0f, 0.0f, 0.0f, squarey, -squarez);
							}
							else
							{
								square(0.0f, squarey, -squarez, r[0], g[0], b[0], a[0]);
							}
						}
						if (i3 > 0 && m1.block[i2][i3 - 1][i] == 0)
						{
							if (thingtex)
							{
								tsquare(blocktexture, 0.0f, 0.0f, 0.0f, squarex, 0.0f, -squarez);
							}
							else
							{
								square(squarex, 0.0f, -squarez, r[0], g[0], b[0], a[0]);
							}
						}
						if (i + 1 < z && m1.block[i2][i3][i + 1] == 0)
						{
							if (thingtex)
							{
								glColor3f(r[1], g[1], b[1]);
								tsquare(blocktexture, 0.0f, 0.0f, 0.0f, squarex, squarey, 0.0f);
							}
							else
							{
								square(squarex, squarey, 0.0f, r[1], g[1], b[1], a[1]);
							}
						}
						if (m1.map[i2][i3][8] != 0 && atowerbuf.size() > (m1.map[i2][i3][8] - 1) && atowerbuf[m1.map[i2][i3][8] - 1].size() > i)
						{
							for (GLint j = 0; j < atowerbuf[m1.map[i2][i3][8] - 1][i].size(); j++)
							{
								if (atowerbuf[m1.map[i2][i3][8] - 1][i][j] < monster.size() && atowerbuf[m1.map[i2][i3][8] - 1][i][j] < monster.size())
								{
									GLint c = monster[atowerbuf[m1.map[i2][i3][8] - 1][i][j]][1] - i3, d = monster[atowerbuf[m1.map[i2][i3][8] - 1][i][j]][0] - i2;
									if (max(c, -c) <= playtower[m1.map[i2][i3][8]].tparam[1][0] + 1 && max(d, -d) <= playtower[m1.map[i2][i3][8]].tparam[1][0] + 1)
									{
										drawtowerattack(squarex / 2, squarey / 2, squarez / 2, (monster[atowerbuf[m1.map[i2][i3][8] - 1][i][j]][0] - i2) * squarex + squarex / 2, (monster[atowerbuf[m1.map[i2][i3][8] - 1][i][j]][1] - i3) * squarey + squarey / 2, (monster[atowerbuf[m1.map[i2][i3][8] - 1][i][j]][2] - i) * squarez + squarez / 2 + (squarez * cmodel[monster[atowerbuf[m1.map[i2][i3][8] - 1][i][j]][8] + 1].h) / 2);
									}
								}
							}
						}
						glTranslatef (squarex, squarey, -squarez);
						glColor3f(r[0], g[0], b[0]);
						if (i2 + 1 < x && m1.block[i2 + 1][i3][i] == 0)
						{
							if (thingtex)
							{
								tsquare(blocktexture, 0.0f, 0.0f, 0.0f, 0.0f, -squarey, squarez);
							}
							else
							{
								square(0.0f, -squarey, squarez, r[0], g[0], b[0], a[0]);
							}
						}
						if (i3 + 1 < y && m1.block[i2][i3 + 1][i] == 0)
						{
							if (thingtex)
							{
								tsquare(blocktexture, 0.0f, 0.0f, 0.0f, -squarex, 0.0f, squarez);
							}
							else
							{
								square (-squarex, 0.0f, squarez, r[0], g[0], b[0], a[0]);
							}
						}
						if (i > 0 && m1.block[i2][i3][i - 1] == 0)
						{
							if (thingtex)
							{
								glColor3f(r[1], g[1], b[1]);
								tsquare(blocktexture, 0.0f, 0.0f, 0.0f, -squarex, -squarey, 0.0f);
							}
							else
							{
								square(-squarex, -squarey, 0.0f, r[1], g[1], b[1], a[1]);
							}
						}
						glTranslatef (-squarex, 0.0f, squarez);
						//glTranslatef (-squarex, -squarey, 0.0f);
					}
					else
					{
						//glTranslatef (0.0f, 0.0f, -squarez);
						glTranslatef (0.0f, squarey, 0.0f);
					}
				}
				else
				{
					glTranslatef (0.0f, squarey, 0.0f);
				}
			}
			glTranslatef (squarex, -dy2 * squarey, 0.0f);
			//glTranslatef (squarex, 0.0f, z * squarez);
		}
		glTranslatef (-dx2 * squarex, 0.0f, squarez);
		//glTranslatef ((-x) * squarex, squarey, 0.0f);
	}
	glTranslatef (0.0f, 0.0f, -z * squarez);
	glTranslatef (playpos[0] * squarex - bmap[0], playpos[1] * squarey - bmap[1], deep * (-squarez) + 44);//playpos[2] * (-squarez) + 44);
}
// remake tower attack ??
void display(void)
{
	GLint i = 0;
	GLint i2 = 0;
	GLint i3 = 0;
	GLint k = 0;
	GLfloat r[2], g[2], b[2];
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	// Draw
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*glDisable (GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	//glDisable (GL_DEPTH_TEST);
	//glEnable (GL_ALPHA_TEST);
	//glAlphaFunc (GL_GREATER, 0.8f);
	glTranslatef (0.0f, 0.0f, -0.18f);
	tsquare ((GLint)0, (GLint)1, -0.02f, -0.02f, 0.0f, 0.02f, 0.02f, 0.0f);
	glTranslatef (0.0f, 0.0f, 0.18f);
	//glDisable (GL_ALPHA_TEST);
	glDisable (GL_BLEND);
	glEnable (GL_DEPTH_TEST);*/
	mgametime = glutGet(GLUT_ELAPSED_TIME);
	settime();
	if (addtime && gfirstinit && startmenu == false)
	{
		for (GLint i = 0; i < levelsnum; i++)
		{
			gamemap[i].addtochesttimer++;
			gamemap[i].addtochest();
		}
	}
	if (pause == false)
	{
		if (pause2 == false)
		{
			for (GLint i = 0; consol; i++)
			{
				string str;
				cin >> str;
				if (str == "save")
				{
					cin >> savename;
					if (savename == "0")
					{
						savename = "autosave.gamesave";
					}
					savename += "gamesave";
					savef();
				}
				if (str == "load")
				{
					cin >> loadname;
					if (loadname == "0")
					{
						loadname = "autosave.gamesave";
					}
					loadname += ".gamesave";
					loadf();
				}
				if (str == "exit")
				{
					exit(0);
				}
				if (str == "help")
				{
					cout << '\n' << "end" << '\n' << "load name" << '\n' << "save name" << '\n' << "exit" << '\n';
				}
				if (str == "end")
				{
					consol = false;
				}
			}
			playermove();
			towerstep();
			monsterstep();
			addmonsterstep();
			playertrap();
			atrapstep();
			playereffect();
			leveltowerstep();
			wavegen();
			mpgen();
		}
		menu();
	}
	if (startmenu == false && gfirstinit)
	{
		minimap();
		if (viewrotate)
		{
			glTranslatef(viewt[0], viewt[1], -viewt[2]);
			glRotatef(viewr[0], 1.0f, 0.0f, 0.0f);
			glRotatef(viewr[1], 0.0f, 1.0f, 0.0f);
			glRotatef(viewr[2], 0.0f, 0.0f, 1.0f);
		}
		bigmap();
		if (viewrotate)
		{
			glTranslatef(-viewt[0], -viewt[1], viewt[2]);
			glRotatef(-viewr[0], 1.0f, 0.0f, 0.0f);
			glRotatef(-viewr[1], 0.0f, 1.0f, 0.0f);
			glRotatef(-viewr[2], 0.0f, 0.0f, 1.0f);
		}
	}
	breaktime();
	/*//	glTranslatef (0.0f, 0.0f, -0.18f);
	//glColor3f(0.0f, 0.0f, 0.0f);
	//square2d(-0.02f, -0.02f, 0.02f, 0.02f);
	//glTranslatef (0.0f, 0.0f, 0.18f);
	glDisable (GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	//glDisable (GL_DEPTH_TEST);
	//glEnable (GL_ALPHA_TEST);
	//glAlphaFunc (GL_GREATER, 0.8f);
	glTranslatef (0.0f, 0.0f, -0.18f);
	//glColor3f(0.0f, 0.0f, 0.0f);
	//square2d(-0.02f, -0.02f, 0.02f, 0.02f);
	tsquare ((GLint)0, (GLint)1, -0.02f, -0.02f, 0.0f, 0.02f, 0.02f, 0.0f);
	glTranslatef (0.0f, 0.0f, 0.18f);
	//glDisable (GL_ALPHA_TEST);
	//glDisable (GL_BLEND);
	glEnable (GL_DEPTH_TEST);*/
	// Draw
	glutSwapBuffers();
	glFlush();
}

void addpfm() // add player first move
{
	if (playmove[1] != 0)
	{
		pfirstmove = playmove[1];
	}
	else
	{
		if (playmove[0] != 0)
		{
			pfirstmove = playmove[0] * 2;
		}
	}
}

void keyboard(unsigned char button, int kx, int ky)
{
	GLint i = 0, i2 = 0;
	for (i = 0; i < 4; i++)
	{
		atackkey[i] = false;
		pattackrange[i] = 0;
	}
	if (menus == -4)
	{
		menus = -3;
	}
	else
	{
		if (menus != -2 && !(menus == -5 && m5mbutton >= 0) && button == 'A')
		{
			animboolm = !animboolm;
		}
		else
		{
			if (menus != -2 && startmenu == false && !(menus == -5 && m5mbutton >= 0))
			{
				switch (button)
				{
					case 'E':
						if (viewrotate)
						{
							viewr[0] += viewrconst;
						}
						break;
					case 'R':
						if (viewrotate)
						{
							viewr[1] += viewrconst;
						}
						break;
					case 'T':
						if (viewrotate)
						{
							viewr[2] += viewrconst;
						}
						break;
					case 'Y':
						if (viewrotate)
						{
							viewt[0] += viewtconst;
						}
						break;
					case 'U':
						if (viewrotate)
						{
							viewt[1] += viewtconst;
						}
						break;
					case 'I':
						if (viewrotate)
						{
							viewt[2] -= viewtconst;
						}
						break;
					case 'D':
						if (viewrotate)
						{
							viewr[0] -= viewrconst;
						}
						break;
					case 'F':
						if (viewrotate)
						{
							viewr[1] -= viewrconst;
						}
						break;
					case 'G':
						if (viewrotate)
						{
							viewr[2] -= viewrconst;
						}
						break;
					case 'H':
						if (viewrotate)
						{
							viewt[0] -= viewtconst;
						}
						break;
					case 'J':
						if (viewrotate)
						{
							viewt[1] -= viewtconst;
						}
						break;
					case 'K':
						if (viewrotate)
						{
							viewt[2] += viewtconst;
						}
						break;
					case 27:
						menus = -1;
						pause2 = true;
						break;
					case 'v':
						atackview = !atackview;
						break;
					// atack
					case 'w':
						if (pmovetimer + pmovetime <= glutGet(GLUT_ELAPSED_TIME))// && playmove[1] == 0)
						{
							pmovetimer = glutGet(GLUT_ELAPSED_TIME);
							addpfm();
							playmove[1] = 1;
						}
						break;
					case 's':
						if (pmovetimer + pmovetime <= glutGet(GLUT_ELAPSED_TIME))// && playmove[1] == 0)
						{
							pmovetimer = glutGet(GLUT_ELAPSED_TIME);
							addpfm();
							playmove[1] = -1;
						}
						break;
					case 'd':
						if (pmovetimer + pmovetime <= glutGet(GLUT_ELAPSED_TIME))// && playmove[0] == 0)
						{
							pmovetimer = glutGet(GLUT_ELAPSED_TIME);
							addpfm();
							playmove[0] = 1;
						}
						break;
					case 'a':
						if (pmovetimer + pmovetime <= glutGet(GLUT_ELAPSED_TIME))// && playmove[0] == 0)
						{
							pmovetimer = glutGet(GLUT_ELAPSED_TIME);
							addpfm();
							playmove[0] = -1;
						}
						atackmode = false;
						break;
					// attack
					case 'z': // to up level
						if (actmap + 1 < levelsnum && (levelpos[actmap] == 1 || levelpos[actmap + 1] == 1) && max(max(playpos[0], x / 2) - min(playpos[0], x / 2), max(playpos[1], y / 2) - min(playpos[1], y / 2)) <= levelteleportrange && gamemap[actmap + 1].map[(GLint)playpos[0]][(GLint)playpos[1]][0] == 0 && gamemap[actmap + 1].block[(GLint)playpos[0]][(GLint)playpos[1]][(GLint)playpos[2] + 1] == 0)
						{
							actmap++;
							x = mapsizexy[actmap][0];
							y = mapsizexy[actmap][1];
							playerjump(m1.block[(GLint)playpos[0]][(GLint)playpos[1]], playpos[2]);
						}
						break;
					case 'x': // to down level
						if (actmap > 0 && (levelpos[actmap] == 1 || levelpos[actmap - 1] == 1) && max(max(playpos[0], x / 2) - min(playpos[0], x / 2), max(playpos[1], y / 2) - min(playpos[1], y / 2)) <= levelteleportrange && gamemap[actmap - 1].map[(GLint)playpos[0]][(GLint)playpos[1]][0] == 0 && gamemap[actmap - 1].block[(GLint)playpos[0]][(GLint)playpos[1]][(GLint)playpos[2] + 1] == 0)
						{
							actmap--;
							x = mapsizexy[actmap][0];
							y = mapsizexy[actmap][1];
							playerjump(m1.block[(GLint)playpos[0]][(GLint)playpos[1]], playpos[2]);
						}
						break;
					case 32: // space
						if (phand[hand].type != 10 && m1.map[(GLint)playpos[0]][(GLint)playpos[1]][0] != 1)
						{
							clickact(playpos[0], playpos[1]);
						}
						break;
					case 'p':
						pause = !pause;
						break;
					case 'f':
						fview = !fview;
						break;
					case 'c':
						consol = true;
						break;
					case 'k':
						savename = "autosave.gamesave";
						savef();
						break;
					case 'l':
						loadname = "autosave.gamesave";
						loadf();
						break;
					case 'r':
						if (menus == 0)
						{
							menus = 5;
						}
						else
						{
							if (menus == 5)
							{
								menus = 0;
								menur[0] = 0;
								menur[1] = 0;
							}
						}
						break;
					case 'e':
						if (menus == 0 || menus == 2)
						{
							menus = 1;
						}
						else
						{
							if (menus > 0)
							{
								for (i = 0; i < pmy; i++)
								{
									for (i2 = 0; i2 < pmx; i2++)
									{
										if (pb[i2][i].type != -1)
										{
											if (i >= pmy)
											{
												if (i2 < pt[3 - (i - pmy)].size)
												{
													if (taketsize < 60)
													{
														taket[taketsize] = pb[i2][i];
														taketsize++;
													}
													pb[i2][i].type = -1;
												}
											}
											else
											{
												if ((pmy - 1 - i) * 10 + i2 >= pt[5].size)
												{
													if (taketsize < 60)
													{
														taket[taketsize] = pb[i2][i];
														taketsize++;
													}
													pb[i2][i].type = -1;
												}
											}
										}
									}
								}
								for (i = 0; i < createnum; i++)
								{
									if (mcreate[i].type != -1)
									{
										if (taketsize < 60)
										{
											taket[taketsize] = mcreate[i];
											taketsize++;
										}
										mcreate[i].type = -1;
									}
								}
								if (tb.second.type != -1)
								{
									switch (menus)
									{
									case 1:
										if (tb.first < 0)
										{
											if (tb.first < -7)
											{
												phand[-tb.first - 8] = tb.second;
											}
												else
											{
												if (tb.second.type == -tb.first)
													{
														pt[-tb.first - 1] = tb.second;
													}
												else
												{
													//bp++;
													if (taketsize < 60)
													{
														taket[taketsize] = tb.second;
														taketsize++;
													}
												}
											}
										}
										else
										{
											if ((tb.first / 10 < pmy && tb.first < pt[5].size) || (tb.first / 10 >= pmy && (tb.first - (pmx * pmy)) < pt[3 - (tb.first / 10 - pmy)].size && ((((tb.first / 10 - pmy == 2) || (tb.first / 10 - pmy == 0)) && (tb.second.type < 8 || tb.second.type > 10)) || (tb.first / 10 - pmy == 1 && tb.second.type >= 8 && tb.second.type <= 10))))
											{
												pb[tb.first % 10][tb.first / 10] = tb.second;
											}
											else
											{
												//bp++;
												if (taketsize < 60)
												{
													taket[taketsize] = tb.second;
													taketsize++;
												}
											}
										}
										break;
									case 3:
										if (taketsize < 60)
										{
											taket[taketsize] = tb.second;
											taketsize++;
										}
										tb.second.type = -1;
										tb.first = 0;
										/*if (tb[0] <= 0)
										{
											tb[1] = tb[1]; // at menu
											if ((((tb[1] / 10 == 2) || (tb[1] / 10 == 0)) && (thing[tb[0]][0] < 8 || thing[tb[0]][0] > 10)) || (tb[1] / 10 == 1 && thing[tb[0]][0] >= 8 && thing[tb[0]][0] <= 10))
											{
												pb[tb[1] % 10][pmy + tb[1] / 10] = tb[0];
											}
											else
											{
												taket[0]++;
												taket[taket[0]] = tb[0];
											}
										}
										else
										{
											m1.chest[openchest][tb[1]] = tb[0];
											tb[0] = 0;
											tb[1] = 0;
										}*/
										break;
									}
								}
								tb.second.type = -1;
								tb.first = 0;
								if (menus != 2)
								{
									menus = 0;
								}
							}
						}
						cht = 0;
						break;
					case 'q': // menu options
					    hand = 1 - hand;
						/*if (menus == 0)
						{
							menus = -1;
							pause2 = true;
						}
						else
						{
							if (menus < 0)
							{
								menus = 0;
								pause2 = false;
							}
						}*/
						break;
					case 't': // teleport
						live = 0;
						break;
					case '>':
						printc = !printc;
						break;
					case '1':
						hand = 0;
						break;
					case '2':
						hand = 1;
						break;
					default:
						break;
				}
			}
			else
			{
				if (button == 8 /*backspace*/ || button == 127 /*delete*/)
				{
					if (menus == -5)
					{
						if (m5mstring.size() != 0)
						{
							m5mstring.pop_back();
						}
					}
					else
					{
						if (menuinputs.size() != 0)
						{
							menuinputs.pop_back();
						}
					}
				}
				else
				{
					if (menus == -5)
					{
						if (button <= '9' && button >= '0')
						{
							if (m5mstring.size() < mapcreatestrsize)
							{
								m5mstring += button;
							}
						}
					}
					else
					{
						if (menuinputs.size() < maxinputsaveload)
						{
							menuinputs += button;
						}
					}
				}
			}
		}
	}
	if (printc)
	{
		cout << button << " - " << (int)button << '\n';
	}
}

void keyboards(int button, int kxs, int kys) //special keyboard
{
	for (GLint i = 0; i < 4; i++)
	{
		atackkey[i] = false;
		pattackrange[i] = 0;
	}
	switch (button)
	{
		case GLUT_KEY_UP:
			if (phand[hand].type == 10)
			{
				//playerattackt(phand[hand], 1, 3, 0, 2);
				playeratack(phand[hand], playpos[0], playpos[1] + playerattackt(&phand[hand], 1, 3, 0, 2), 0, 2, 3, 1, 1);
			}
			else
			{
				if (playpos[1] < (y - 1) && m1.map[(GLint)playpos[0]][(GLint)playpos[1] + 1][0] != 1)
				{
					clickact(playpos[0], playpos[1] + 1);
				}
			}
			break;
		case GLUT_KEY_DOWN:
			if (phand[hand].type == 10)
			{
				//playerattackt(phand[hand], 1, 3, 0, 2);
				playeratack(phand[hand], playpos[0], playpos[1] - playerattackt(&phand[hand], 3, 1, 0, 2), 2, 0, 3, 1, 3);
			}
			else
			{
				if (playpos[1] > 0 && m1.map[(GLint)playpos[0]][(GLint)playpos[1] - 1][0] != 1)
				{
					clickact(playpos[0], playpos[1] - 1);
				}
			}
			break;
		case GLUT_KEY_RIGHT:
			if (phand[hand].type == 10)
			{
				playeratack(phand[hand], playpos[0] + playerattackt(&phand[hand], 0, 2, 1, 3), playpos[1], 0, 2, 1, 3, 0);
			}
			else
			{
				if (playpos[0] < (x - 1) && m1.map[(GLint)playpos[0] + 1][(GLint)playpos[1]][0] != 1)
				{
					clickact(playpos[0] + 1, playpos[1]);
				}
			}
			break;
		case GLUT_KEY_LEFT:
			if (phand[hand].type == 10)
			{
				playeratack(phand[hand], playpos[0] - playerattackt(&phand[hand], 0, 2, 1, 3), playpos[1], 2, 0, 3, 1, 2);
			}
			else
			{
				if (playpos[0] > 0 && m1.map[(GLint)playpos[0] - 1][(GLint)playpos[1]][0] != 1)
				{
					clickact(playpos[0] - 1, playpos[1]);
				}
			}
			break;
		case GLUT_KEY_F1:
			exit(0);
			break;
		case GLUT_KEY_F2:
			viewrotate = !viewrotate;
			break;
		case GLUT_KEY_F3:
			thinghelp = !thinghelp;
			break;
		default:
			break;
	} // add atack keys combination
}

void mouse(int button, int click, int mx, int my)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (click == GLUT_DOWN)
			{
				mb[0] = true;
			}
			else
			{
				mb[0] = false;
			}
			break;
		case GLUT_MIDDLE_BUTTON:
			if (click == GLUT_DOWN)
			{
				mb[1] = true;
			}
			else
			{
				mb[1] = false;
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (click == GLUT_DOWN)
			{
				mb[2] = true;
			}
			else
			{
				mb[2] = false;
			}
			break;
		default:
			break;
	}
	mp[0] = mx;
	mp[1] = my;
}

void pmotion(GLint mx, GLint my)
{
	mp[0] = mx;
	mp[1] = my;
	//mb[0] = false;
	//mb[1] = false;
	//mb[2] = false;
}

void amotion(GLint mx, GLint my)
{
	mp[0] = mx;
	mp[1] = my;
	//mb[0] = false;
	//mb[1] = false;
	//mb[2] = false;
}

void window(GLint w, GLint h)
{
	if (h == 0)
	{
		h = 1;
	}
	wp[0] = w;
	wp[1] = h;
	GLfloat view = w * 1.0f / h;
	maxy = 1 / sin (67.5) * cos (67.5); // maxy * dist
	maxx = maxy * view;
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glViewport (0, 0, w, h);
	//glFrustum (-0.1f, 0.1f, -0.074f, 0.074f, 0.09f, 100.f);
	gluPerspective (45, view, 0.01f, 100.0f);
	glMatrixMode (GL_MODELVIEW);
	//glEnable (GL_DEPTH_TEST);
}

int main(int argc, char **argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("Game");

	/*ilInit();
	iluInit();
	ilutInit();

	ilutRenderer(ILUT_OPENGL);
	ilSetInteger(IL_KEEP_DXTC_DATA, IL_TRUE);
	ilutEnable(ILUT_GL_AUTODETECT_TEXTURE_TARGET);
	ilutEnable(ILUT_OPENGL_CONV);
	ilutEnable(ILUT_GL_USE_S3TC);*/

	// init
	cout << "Copyright (c) 2017, Purpure Bacterium\n";
	loadtexture();
	/*dtime = time(NULL);
	for(GLint i = 0; i < levelsnum; i++)
	{
		initmarket(i, levelrm[i][0], levelrm[i][1]);
		initmonster(mlevelgen[i][0], mlevelgen[i][1], i);
	}
	initplayer();*/
	startloadmonstert();
	startloadcreate();
	startloadtrap();
	startloadchest();
	startloadmarket();
	startloadmonster();
	startloadthing();
	startloadmoptions();
	//initThing();
	//newgame();
	startinitplayer();
	startmenu = true;
	pause2 = true;
	menus = -3;
	addmodel("marketm.txt");
	addmodel("monsterm1.txt");
	addmodel("monsterm2.txt");
	addmodel("monsterm3.txt");
	//initmenu ();
	// init
	gamey = 1 / sin (67.5) * cos (67.5);
	gamex = gamey * 800 / 600;
	initGL();
	//initLight();
	//glOrtho (-100.f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);

	/*glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);*/

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboards);
	glutMouseFunc(mouse);
	glutMotionFunc(amotion);
	glutPassiveMotionFunc(pmotion);
	glutReshapeFunc(window);
	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutMainLoop();
}

GL::~GL()
{
}
