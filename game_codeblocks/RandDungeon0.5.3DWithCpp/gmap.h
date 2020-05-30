#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <math.h>
#include <algorithm>

#define min(x, y) ((x)>(y)?(y):(x))
#define max(x, y) ((x)>(y)?(x):(y))
#define to_string gametostring

const GLint dx = 41; //
const GLint dy = 41; // display
const GLint constx = 501;
const GLint consty = 501;
GLint x = constx;
GLint y = consty;
const GLint z = 16; // +depth
const GLint deep = 6;
const GLint wallh = 6; // height of walls
const GLint sizemap = 11; // 0 - places(0) & walls(1); 1 - mines (1... stones); 2 - traps; 3 - chest num (1...), nothing(0);
// 4 - create num (1...), nothing (0); 5 - traps pos z; 6 - monsters; 7 - windows && doors; 8 - towers; 9 - markets; 10 - place of monsters
const GLint chmaxnum = 60; // max things num in chest
const GLint chrandnum = 6; // things in chest
const GLint thingsnum = 10; // 47 // things num
const GLint trapsnum = 32;
const GLint randtsum = 1000; // with nothng (trap)
const GLint randtrap = 10; // traps rand
const GLint tsum = 10; // without nothing (things)
const GLint chestrand = 30;
//const GLint cmaxnum = 400;
const GLint chrandsum = 50000; // chestrand + nothing
const GLint minerand = 400;
const GLint minerandnum = 20000;// minerand + nothing
//const GLint blocknum = 10; // 1 - walls; 2 - ground; 3 - stone; 4 - tree; 5 - chest; 6 - create, 7 - create2; 8 - main tower block; 10 - tower update
const GLint startx = 2;
const GLint starty = 2;
const GLint genway = 40;
const GLint genwaymax = 100;


/*const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 1000.0f };*/


const GLfloat towerattackx = 0.4f;
const GLfloat towerattacky = 0.4f;
const GLfloat towerattackz = 0.4f;
const GLfloat squarexm = 0.001f;
const GLfloat squareym = 0.001f;
const GLint stepm = 1;
const GLint step = 1;
const GLfloat squarex = 1.0f;
const GLfloat squarey = 1.0f;
const GLfloat squarez = 1.0f;
const GLfloat ph = 10.0f;
const GLfloat ph2 = 9.0f; // player head
const GLint playerh = 3;
const GLint dx2 = 41;
const GLint dy2 = 41;
const GLint chtree = 8; // tree in chest
const GLint pms = 50; // bag size
const GLint pmx = 10; // menu bag x
const GLint pmy = 5; // menu bag y
const GLfloat viewrconst = 1.0f;
const GLfloat viewtconst = 1.0f;
const GLint mapcreatestrsize = 5;
// jacket size 10
// belt size 10
// trousers size 10
const GLint tnum = 10; // things num
// person: hat, jacket, gloves, belt, trousers, boots, bag
const GLint createnum = 36;
const GLint createnum2 = 30;
const GLint createtables = 1;
const GLint maxlive = 100;
const GLint maxplaylive = 200;
const GLint inttextmax = 6;
const GLint texturenum = 35;
const GLint trapattackn = 3;
const GLint maximum = 1000000LL;
const GLfloat bshadow = 0.2f;
//#define raddm 4// rand add monster
//#define rmaxaddm 1000// rand max add monster
//#define mrandmax 10
const GLint monsternum = 3;
const GLint monstersize = 11;
const GLint monsterpos = 5;
const GLint monstermaxshild = 100;
const GLint playjump = 1;
const GLint distmonster = 5;
const GLint monsterdistx = 10;
const GLint monsterdisty = 10;
const GLint towerdistx = 10;
const GLint towerdisty = 10;
const GLint mrandthingmax = 6;
const GLint mrandthingnum = 6;
const GLint minaddcost = 10;
const GLint maxaddcost = 10;
#define m1 (gamemap[actmap])
const GLint wayrange = 4;
//#define ingamegenm 1
//#define maxingamegenm 10000000LL
const GLint monsterp = 20;
//#define addmonstertime 10
const GLint doorh = 3;
const GLint tparamnum = 4; // 9
const GLint maxtowerlive = 200;
const GLint maxinputsaveload = 32;
const GLint shildconst = 100;
const GLint levelteleportrange = 2;
const GLint peffectnum = 3;
const GLint playerattacktime = 400;
const GLint wtypesnum = 5;// num of types no magic weapon
const GLint maxplaymp = 1000;
const GLint levelconst = 50;
const GLint efsize = 5;
const GLint pefsize = 5;
const GLint createmaxnum = 4;
GLint baselevel = 5;
const GLint mmarketch = 3; // max market changes
const GLint mmarketchup = 0;
const GLint blocksize = 3;
const GLint wavesuplevel = 10;
const GLint maintowerplace = 6;
const GLint wavemonsterplace = 16;
const GLint minbreak = 1;
const GLint maxaddbreak = 1;
const GLint moptionsize = 6;
const GLint mainmplacesize = 5;
const GLint optionsize = 6;
const GLint blocktext = 29;
const GLint mindistmainm = 20;
const GLint ngmmonstert = 600; // new gen main monster time
const GLint ctformulmovetime = 100;
const GLint addtochesttime = 2400;
const GLint addtochestrand  = 80;
const GLint addthingtochest = 4;
const GLint mmainrandthingnum = 15;
const GLint m5mlbn = 5;
const GLint pmovetime = 160;

using namespace std;

namespace m
{
    string gametostring(GLint a)
    {
        string s;
        for (;a != 0;)
        {
            s += (a % 10) + '0';
            a /= 10;
        }
        for (long i = 0; i < s.size() / 2; i++)
        {
            swap(s[i], s[s.size() - i - 1]);
        }
        return s;
    }
	class obj
	{
	public:
		string name;
		GLint type; // thing type
		GLint range, attack, dist, bn; // break num
		GLint rare;
		GLint size, text, t2;
		GLint mpoints, points, wtype, shield, live, timer;
		GLfloat color[3];
		GLint t; //0 - can't be at map, 1 - struct, 2 - block
		GLint ef[trapattackn][efsize]; // power, rand, time of effect, timer, time
		GLint pef[peffectnum][pefsize]; // --//--
		GLint edel;
		obj()
		{
			color[0] = 1.0f;
			color[1] = 1.0f;
			color[2] = 1.0f;
			timer = 0;
			live = 0;
			edel = 0;
			rare = 0;
			shield = 0;
			mpoints = 0;
			points = 0;
			wtype = 0;
			t2 = 0;
			text = 0;
			size = 0;
			name  = "a";
			range = 0;
			attack = 0;
			dist = 0;
			type = 0;
			t = 0;
			bn = 0;
			for (GLint i = 0; i < trapattackn; i++)
			{
				for(GLint j = 0; j < efsize; j++)
				{
					ef[i][j] = 0;
				}
			}
			for (GLint i = 0; i < peffectnum; i++)
			{
				for(GLint j = 0; j < pefsize; j++)
				{
					pef[i][j] = 0;
				}
			}
			color[0] = 0.0f;
			color[1] = 0.0f;
			color[2] = 0.0f;
		}
		bool compint (GLfloat a, GLfloat b)
		{
			if (a == b || a == -2 || b == -2)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		bool compint (GLint a, GLint b)
		{
			if (a == b || a == -2 || b == -2)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		bool addb (bool *a, bool b)
		{
			if (b == false)
			{
				*a = false;
			}
			return *a;
		}
		bool cai(bool *a, GLint b, GLint d) // comp add int
		{
			addb(a, compint(b, d));
			return *a;
		}
		bool cai(bool *a, GLfloat b, GLfloat d) // comp add int
		{
			addb(a, compint(b, d));
			return *a;
		}
		void compint2(GLint *a, GLint b)
		{
			if (*a > b)
			{
				*a = b;
			}
		}
		void compfloat(GLfloat *a, GLfloat b)
		{
			if (*a > b)
			{
				*a = b;
			}
		}
		void compobj(obj a)
		{
			compint2(&timer, a.timer);
			compint2(&live, a.live);
			compint2(&edel, a.edel);
			compint2(&rare, a.rare);
			compint2(&shield, a.shield);
			compint2(&mpoints, a.mpoints);
			compint2(&points, a.points);
			//wtype = 0;
			compint2(&t2, a.t2);
			compint2(&text, a.text);
			compint2(&size, a.size);
			//name  = "";
			compint2(&range, a.range);
			compint2(&attack, a.attack);
			compint2(&dist, a.dist);
			//type = 0;
			//t = 0;
			compint2(&bn, a.bn);
			for (GLint i = 0; i < trapattackn; i++)
			{
				for(GLint j = 0; j < efsize; j++)
				{
					compint2(&ef[i][j], a.ef[i][j]);
				}
			}
			for (GLint i = 0; i < peffectnum; i++)
			{
				for(GLint j = 0; j < pefsize; j++)
				{
					compint2(&pef[i][j], a.pef[i][j]);
				}
			}
			compfloat(&color[0], a.color[0]);
			compfloat(&color[1], a.color[1]);
			compfloat(&color[2], a.color[2]);
		}
		void addrand(GLint &num, GLint &a, GLfloat &r, GLint b)
		{
			if (b != 0)
			{
				GLint c = 0;
				if (b < 0)
				{
					c = -(rand() % ((-b + 1) / 2) + rand() % ((GLint)ceil((GLfloat)(-b + 1) / 2)));
				}
				else
				{
					c = rand() % ((b + 1) / 2) + rand() % ((GLint)ceil((GLfloat)(b + 1) / 2));
				}
				a += c;
				r *= num;
				r += (GLfloat) c / b;
				num++;
				r /= num;
			}
		}
		void oaddrand(obj a)
		{
			GLint num = 0;
			GLfloat r = 0;
			//timer += rand() % a.timer;
			addrand(num, live, r, a.live);
			addrand(num, edel, r, a.edel);
			//addrand(num, rare, r, a.rare);
			addrand(num, shield, r, a.shield);
			addrand(num, mpoints, r, a.mpoints);
			addrand(num, points, r, a.points);
			//wtype += a.wtype;
			addrand(num, t2, r, a.t2);
			addrand(num, text, r, a.text);
			addrand(num, size, r, a.size);
			addrand(num, range, r, a.range);
			addrand(num, attack, r, a.attack);
			addrand(num, dist, r, a.dist);
			//type = a.type;
			//t += 0;
			bn += rand() % (a.bn + 1);
			for (GLint i = 0; i < trapattackn; i++)
			{
				for(GLint j = 0; j < efsize; j++)
				{
					addrand(num, ef[i][j], r, a.ef[i][j]);
				}
			}
			for (GLint i = 0; i < peffectnum; i++)
			{
				for(GLint j = 0; j < pefsize; j++)
				{
					addrand(num, pef[i][j], r, a.pef[i][j]);
				}
			}
			//color[0] += rand() % a.color[0];
			//color[1] += rand() % a.color[1];
			//color[2] += rand() % a.color[2];
			rare += (GLint)a.rare * r;
		}
		void oadd(obj a)
		{
			timer += a.timer;
			live += a.live;
			edel += a.edel;
			rare += a.rare;
			shield += a.shield;
			mpoints += a.mpoints;
			points += a.points;
			//wtype += a.wtype;
			if (type == a.type && type == 0 && t2 == a.t2 && t2 == 9)
			{
				if (wtype != a.wtype)
				{
					wtype = 0;
				}
			}
			text += a.text;
			size += a.size;
			range += a.range;
			attack += a.attack;
			dist += a.dist;
			//type = a.type;
			//t += 0;
			bn += a.bn;
			for (GLint i = 0; i < trapattackn; i++)
			{
				for(GLint j = 0; j < efsize; j++)
				{
					ef[i][j] += a.ef[i][j];
				}
			}
			for (GLint i = 0; i < peffectnum; i++)
			{
				for(GLint j = 0; j < pefsize; j++)
				{
					pef[i][j] += a.pef[i][j];
				}
			}
			color[0] += a.color[0];
			color[1] += a.color[1];
			color[2] += a.color[2];
		}
		void od(GLint a) // /
		{
			timer /= a;
			live /= a;
			edel /= a;
			rare /= a;
			shield /= a;
			mpoints /= a;
			points /= a;
			//wtype /= a.wtype;
			//t2 /= a;
			text /= a;
			size /= a;
			range /= a;
			attack /= a;
			dist /= a;
			//type = a.type;
			//t += 0;
			bn /= a;
			for (GLint i = 0; i < trapattackn; i++)
			{
				for(GLint j = 0; j < efsize; j++)
				{
					ef[i][j] /= a;
				}
			}
			for (GLint i = 0; i < peffectnum; i++)
			{
				for(GLint j = 0; j < pefsize; j++)
				{
					pef[i][j] /= a;
				}
			}
			color[0] /= a;
			color[1] /= a;
			color[2] /= a;
		}
		bool operator== (obj b)
		{
			bool a = true;
			cai(&a, timer, b.timer);
			cai(&a, live, b.live);
			cai(&a, edel, b.edel);
			cai(&a, rare, b.rare);
			cai(&a, shield, b.shield);
			cai(&a, mpoints, b.mpoints);
			cai(&a, points, b.points);
			cai(&a, wtype, b.wtype);
			cai(&a, t2, b.t2);
			//cai(&a, text, b.text);
			cai(&a, size, b.size);
			//name;
			cai(&a, range, b.range);
			cai(&a, attack, b.attack);
			cai(&a, dist, b.dist);
			cai(&a, type, b.type);
			cai(&a, t, b.t);
			cai(&a, bn, b.bn);
			for (GLint i = 0; i < trapattackn; i++)
			{
				for(GLint j = 0; j < efsize; j++)
				{
					cai(&a, ef[i][j], b.ef[i][j]);
				}
			}
			for (GLint i = 0; i < peffectnum; i++)
			{
				for(GLint j = 0; j < pefsize; j++)
				{
					cai(&a, pef[i][j], b.pef[i][j]);
				}
			}
			//cai(&a, color[0], b.color[0]);
			//cai(&a, color[1], b.color[1]);
			//cai(&a, color[2], b.color[2]);
			return a;
		}
		obj operator= (obj b)
		{
			obj a;
			a.timer = timer = b.timer;
			a.live = live = b.live;
			a.edel = edel = b.edel;
			a.rare = rare = b.rare;
			a.shield = shield = b.shield;
			a.mpoints = mpoints = b.mpoints;
			a.points = points = b.points;
			a.wtype = wtype = b.wtype;
			a.t2 = t2 = b.t2;
			a.text = text = b.text;
			a.size = size = b.size;
			a.name = name = b.name;
			a.range = range = b.range;
			a.attack = attack = b.attack;
			a.dist = dist = b.dist;
			a.type = type = b.type;
			a.t = t = b.t;
			a.bn = bn = b.bn;
			for (GLint i = 0; i < trapattackn; i++)
			{
				for(GLint j = 0; j < efsize; j++)
				{
					a.ef[i][j] = ef[i][j] = b.ef[i][j];
				}
			}
			for (GLint i = 0; i < peffectnum; i++)
			{
				for(GLint j = 0; j < pefsize; j++)
				{
					a.pef[i][j] = pef[i][j] = b.pef[i][j];
				}
			}
			a.color[0] = color[0] = b.color[0];
			a.color[1] = color[1] = b.color[1];
			a.color[2] = color[2] = b.color[2];
			return a;
		}
	};
	class mobj
	{
	public:
		obj a;
		GLfloat posx, posy, posz;
		mobj()
		{
			posx = 0.0f;
			posy = 0.0f;
			posz = 0.0f;
		}
	};
	class multiobj
	{
	public:
		obj omain;
		obj oadd;
		obj omax;
		obj oaddl;
		multiobj()
		{
		}
	};
	obj findobj(vector<multiobj> *a, GLint level, vector<GLint> *rnum, GLint *num, bool addnum = true)
	{
		GLint sum = 0, b = 0, d = 0;
		obj c;
		if (*num == -1 || addnum == false)
		{
			for (GLint i = 0; i < (*a).size(); i++)
			{
				if (min((*a)[i].omain.rare + (*a)[i].oaddl.rare * max(level - baselevel, baselevel - level), (*a)[i].omax.rare) > 0)
				{
					d = min((*a)[i].omain.rare + (*a)[i].oaddl.rare * max(level - baselevel, baselevel - level), (*a)[i].omax.rare);
					sum += d;
					if (addnum)
					{
						for (GLint j = 0; j < d; j++)
						{
							(*rnum).push_back(i);
						}
					}
				}
			}
			*num = sum;
		}
		if (*num == 0)
		{
			b = 0;
		}
		else
		{
			b = rand() % (*num) + 1;
		}
		if (addnum)
		{
			b = (*rnum)[b - 1];
		}
		else
		{
			for (GLint i = 0; i < (*a).size(); i++)
			{
				if (min((*a)[i].omain.rare + (*a)[i].oaddl.rare * max(level - baselevel, baselevel - level), (*a)[i].omax.rare) > 0)
				{
					b -= min((*a)[i].omain.rare + (*a)[i].oaddl.rare * max(level - baselevel, baselevel - level), (*a)[i].omax.rare);
					if (b <= 0)
					{
						b = i;
						break;
					}
				}
			}
		}
		c = (*a)[b].omain;
		for (GLint i = 0; i < max(baselevel - level, level - baselevel); i++)
		{
			c.oadd((*a)[b].oaddl);
		}
		c.compobj((*a)[b].omax);
		c.oaddrand((*a)[b].oadd);
		return c;
	}
	vector<multiobj> ochest;
	vector<multiobj> otrap;
	vector<multiobj> ochange;
	vector<multiobj> omonster;
	vector<vector<GLint> > oblock;
	//vector<multiobj> oblock;
	vector<vector<multiobj> > omarket;
	vector<GLint> rchest;
	vector<GLint> rtrap;
	vector<GLint> rchange;
	vector<vector<GLint> > rmarket;
	GLint changes = -1, traps = -1, chests = -1; // size
	vector<GLint> markets; // size
	class gmap
	{
	public:
		GLint mainmonsterpos[2];
		GLint levelk;
		GLint levelk2;
		GLint levelkdeep;
		GLint levelkmine;
		GLint levelkchest;
		bool initbool;
		GLint i;
		GLint i2;
		GLint i3;
		GLint nx, ny;
		GLint mapsx, mapsy;
		//GLint ***map;
		GLint map[constx][consty][sizemap];
		GLint block[constx][consty][z];
		//GLint map[constx][consty][sizemap];
		//GLint ***block;
		// break when new map or load
		//GLint block[constx][consty][z];
		//GLint ***mapu0, **mapu1, *mapu2;
		//GLint ***blocku0, **blocku1, *blocku2;
		GLfloat minmap[2];
		GLint t[thingsnum]; // thing
		GLint trap[trapsnum]; // trap rand sum = randtsum (with nothing)
		GLint randt[tsum]; // thing
		GLint randt2[randtsum]; // trap
		GLint chestr;
		GLint chnum;
		GLint addtochesttimer;
		//GLint **chest;
		//obj chest[cmaxnum][chmaxnum];
		vector<vector<obj> > chest;
		vector<GLint> chestsize;
		vector<mobj> mblock;
		GLint mblocksum;
		vector<GLint> mblocknum;
		//GLint ***map;
		//GLint ***block;
		//vector<vector<vector<GLint> > > map;//(x, vector<vector<GLint> > (y, vector<GLint> (size)));
		//vector<vector<vector<GLint> > > block;//(x, vector<vector<GLint> > (y, vector<GLint> (z)));
		/*vector<vector<GLint> > chest;//(cmaxnum, vector<GLint> (chmaxnum + 1));
		vector<GLint> t; //(thingsnum);
		vector<GLint> trap;//(trapsnum);
		vector<GLint> randt;//(tsum);
		vector<GLint> randt2;//(randtsum);*/
		GLint minenum;

		void freeposz(GLint i, GLint i2)
		{
			for (i3 = 0; i3 < z; i3++)
			{
				if (i3 < deep)
				{
					block[i][i2][i3] = 2;
				}
				else
				{
					block[i][i2][i3] = 0;
				}
			}
			map[i][i2][0] = 0;
		}

		void addmainmonsterplace()
		{
			GLint a[2] = {(x - mindistmainm * 2 - 1 - mainmplacesize + 1), (y - mindistmainm * 2 - 1 - mainmplacesize + 1)};
			GLint b[2] = {0, 0};
			GLint c = 0;
			GLint mainmpos[2] = {rand() % a[0], rand() % a[1]};
			if (mainmpos[0] >= a[0] / 2)
			{
				mainmpos[0] += mindistmainm * 2 + 1;
				b[0] = -1;
			}
			else
			{
				b[0] = 1;
			}
			if (mainmpos[1] >= a[1] / 2)
			{
				mainmpos[1] += mindistmainm * 2 + 1;
				b[1] = -1;
			}
			else
			{
				b[1] = 1;
			}
			for (i = mainmpos[0], i2 = mainmpos[1]; i > 0 && i2 > 0 && i < x && i2 < y;)
			{
				c = rand() % 2;
				if (map[i][i2][0] == 0)
				{
					break;
				}
				else
				{
					freeposz(i, i2);
				}
				if (c == 0)
				{
					i += b[0];
				}
				else
				{
					i2 += b[1];
				}
				if (i > 0 && i < x)
				{
					if (map[i][i2][0] == 0)
					{
						break;
					}
					else
					{
						freeposz(i, i2);
					}
				}
				else
				{
					break;
				}
				if (c == 0)
				{
					i2 += b[1];
				}
				else
				{
					i += b[0];
				}
			} // add way
			for (i = mainmpos[0]; i < (mainmpos[0] + mainmplacesize); i++)
			{
				for (i2 = mainmpos[1]; i2 < (mainmpos[1] + mainmplacesize); i2++)
				{
					if (map[i][i2][0] == 1)
					{
						freeposz(i, i2);
					}
				}
			} // add place
			for (i = 0; i < 2; i++)
			{
				mainmonsterpos[i] = mainmpos[i] + mainmplacesize / 2;
			} // add place for main monster
		}

		void thingrand(GLint thingm[thingsnum])
		{
			for (i = 0; i < thingsnum; i++)
			{
				t[i] = thingm[i];
			}
		}

		void squaremove(GLint i, GLint j, GLint &mx, GLint &my)
		{
			//cout << j << ' ' << i << '\n';
			if (j < 2 * i)
			{
				mx++;
			}
			else
			{
				if (j < 4 * i)
				{
					my++;
				}
				else
				{
					if (j < 6 * i)
					{
						mx--;
					}
					else
					{
						my--;
					}
				}
			}
		}

		void f()
		{
			srand((unsigned) time(NULL) * rand()); // add <x & >0 & <y & >0
			for (i = 0; i < x; i++)
			{
				for (GLint j = 0; j < y; j++)
				{
					map[i][j][0] = 1;
				}
			}
			for (i = x / 2 - startx; i <= x / 2 + startx; i++)
			{
				for (GLint j = y / 2 - startx; j <= y / 2 + starty; j++)
				{
					map[i][j][0] = 0;
				}
			}
			for (i = min(startx, starty); i < max(x / 2, y / 2); i++)
			{
				GLint mx = x / 2 - i, my = y / 2 - i;
				bool genlevel = true; // ??
				for (GLint j = 0; j < 8 * i; j++)
				{
					GLint addx = 0, addy = 0;
					//if (i < 5)
					//{
					//cout << mx << ' ' << my << '\n';
					//}
					squaremove(i, j, mx, my);
					squaremove(i, j, addx, addy);
					//cout << addx << ' ' << addy << '\n';
					if (mx < x && mx >= 0 && my < y && my >= 0 && map[mx - addy][my + addx][0] == 0 && ((rand() % 900) < 500 + levelk))
					{
						map[mx][my][0] = 0;
					}
					// add line way
				}
				mx = x / 2 - i;
				my = y / 2 - i;
				for (GLint k = 0; genlevel && k < i * 24; k += 12)
				{
					genlevel = false;
					mx = x / 2 - i;
					my = y / 2 - i;
					for (GLint j = 0; j < 8 * i; j++)
					{
						GLint addx = 0, addy = 0;
						squaremove(i, j, mx, my);
						squaremove(i, j, addx, addy);
						if (mx >= 0 && my >= 0 && my < y && mx < x && map[mx][my][0] == 0)
						{
							if (mx - addx >= 0 && my - addy >= 0 && mx - addx < x && my - addy < y &&
								map[mx - addx][my - addy][0] != 0 && rand() % (genwaymax * 100) < (genway - k) * 100 + levelk2)
							{
								genlevel = true;
								map[mx - addx][my - addy][0] = 0;
							}
							if (mx + addx >= 0 && mx + addx < x && my + addy >= 0 && my + addy < y &&
								map[mx + addx][my + addy][0] != 0 && rand() % (genwaymax) < genway - k + levelk2)
							{
								map[mx + addx][my + addy][0] = 0;
								genlevel = true;
							}
						}
						// add new way
					}
				}
				for (GLint i = 0; i < x; i++)
				{
					map[i][0][0] = 1;
					map[i][y - 1][0] = 1;
				}
				for (GLint i = 1; i < (y - 1); i++)
				{
					map[0][i][0] = 1;
					map[x - 1][i][0] = 1;
				}
				//mx = x / 2 - i;
				//my = y / 2 - i;
			}
		}

		void f (int fx, int fy)
		{
			//srand ((unsigned)time (NULL) * rand ());
			//cout << fx << ' ' << fy << ' ';
			map[fx][fy][0] = 0;
			GLint a[9];
			GLint fi = 0;
			GLint b = 0;
			GLint c = 0;
			GLint e = 0;
			GLint g = 0;
			GLint r = 0;
			GLint s = 0;
			if (fx != 0 && fx != x - 1 && fy != 0 && fy != y - 1)
			{
				if (map[fx - 1][fy][0] == 0)
				{
					a[0] = 0;
				}
				else
				{
					a[0] = 1;
				}
				if (map[fx][fy - 1][0] == 0)
				{
					a[1] = 0;
				}
				else
				{
					a[1] = 1;
				}
				if (map[fx + 1][fy][0] == 0)
				{
					a[2] = 0;
				}
				else
				{
					a[2] = 1;
				}
				if (map[fx][fy + 1][0] == 0)
				{
					a[3] = 0;
				}
				else
				{
					a[3] = 1;
				}
				c = a[0] + a[1] + a[2] + a[3];
				if (c != 0)
				{
					b = rand () % c + 1;
					/*if (c == 1)
					{
						b = 1;
					}
					if (c == 2)
					{
						b = rand () % 5;
						if (b > 2)
						{
							b = 2;
						}
						else
						{
							b = 1;
						}
					}
					if (c == 3)
					{
						b = rand () % 6;
						if (b > 2)
						{
							if (b > 4)
							{
								b = 3;
							}
							else
							{
								b = 2;
							}
						}
						else
						{
							b = 1;
						}
					}
					if (c == 4)
					{
						b = 4;
					}*/
					//cout << c;
					for (i = 0; i < b && c != 0; i++)
					{
						g = 0;
						e = rand () % c;
						//cout << c << ' ' << b << ' ';
						c--;
						if (a[0] == 1)
						{
							if (g == e)
							{
								f(fx - 1, fy);
								a[0] = 0;
							}
							g++;
						}
						if (a[1] == 1)
						{
							if (g == e)
							{
								f(fx, fy - 1);
								a[1] = 0;
							}
							g++;
						}
						if (a[2] == 1)
						{
							if (g == e)
							{
								f(fx + 1, fy);
								a[2] = 0;
							}
							g++;
						}
						if (a[3] == 1)
						{
							if (g == e)
							{
								f(fx, fy + 1);
								a[3] = 0;
							}
							g++;
						}
					}
				}
				else
				{
					e = rand () % 4;
					if (e == 0)
					{
						f (fx - 1, fy);
					}
					if (e == 1)
					{
						 f (fx, fy - 1);
					}
					if (e == 2)
					{
						f (fx + 1, fy);
					}
					if (e == 3)
					{
						f (fx, fy + 1);
					}
				}
			}
		}

		void addtochest()
		{
			bool a = false;
			if (addtochesttimer >= addtochesttime)
			{
				for (i = 0; i < chest.size(); i++)
				{
					if (chestsize[i] >= 0)
					{
						a = true;
						for (i2 = 0; i2 < chmaxnum; i2++)
						{
							if (chest[i][i2].type != -1)
							{
								a = false;
								break;
							}
						}
						if (a)
						{
							for (i2 = 0; i2 < addthingtochest; i2++)
							{
								if (rand() % 100 < addtochestrand)
								{
									chest[i][i2] = findobj(&ochest, levelk, &rchest, &chests);
								}
							}
						}
					}
				}
				addtochesttimer = 0;
			}
		}

		/*void deletemap()
		{
			if (initbool)
			{
				free(mapu2);
				free(mapu1);
				free(mapu0);
				free(blocku2);
				free(blocku1);
				free(blocku0);
				//map = NULL;
				//block = NULL;
			}
		}*/

		/*void newmap()
		{
			GLint *helpcmap;
			mapsx = x;
			mapsy = y;
			mapu0 = (GLint***) malloc(sizeof(GLint) * x * 2);
			mapu1 = (GLint**) malloc(sizeof(GLint) * x * y * 2);
			mapu2 = (GLint*) malloc(sizeof(GLint) * x * y * sizemap * 2);
			helpcmap = mapu2;
			map = mapu0;
			for (GLint i = 0; i < x; i++)
			{
				map[i] = mapu1;
				map[i] += i * y;
				for (GLint j = 0; j < y; j++)
				{
					map[i][j] = helpcmap;
					helpcmap += sizemap;
				}
			}
			blocku0 = (GLint***) malloc(sizeof(GLint) * x * 2);
			blocku1 = (GLint**) malloc(sizeof(GLint) * x * y * 2);
			blocku2 = (GLint*) malloc(sizeof(GLint) * x * y * z * 2);
			helpcmap = blocku2;
			block = blocku0;
			for (GLint i = 0; i < x; i++)
			{
				block[i] = blocku1;
				block[i] += i * y;
				for (GLint j = 0; j < y; j++)
				{
					block[i][j] = helpcmap;
					helpcmap += z;
				}
			}
			initbool = true;
		}*/

		void newgenmap()
		{
			// ????
			//deletemap();
			//newmap();
			// try{} catch (...) {} - all errors
		}

		void initmap (GLint level = 0, GLint level2 = 0, GLint level3 = 0, GLint level4 = 0, GLint level5 = 0)
   		{
			newgenmap();
			//map.clear();
			//block.clear();
			//map.resize(x, vector<vector<GLint> > (y, vector<GLint> (sizemap, 0)));
			//block.resize(x, vector<vector<GLint> > (y, vector<GLint> (z, 0)));
			GLint d = 0;
			addtochesttimer = 0;
			//map.resize(x, vector<vector<GLint> > (y, vector<GLint> (size)));
			//block.resize(x, vector<vector<GLint> > (y, vector<GLint> (z)));
			//chest.resize(cmaxnum, vector<GLint> (chmaxnum + 1));
			//t.resize(thingsnum);
			//trap.resize(trapsnum);
			//randt.resize(tsum);
			//randt2.resize(randtsum);
			mblock.clear();
			levelk = level;
			levelk2 = level2; // gen map
			levelkmine = level3; // mines rand
			levelkdeep = level4; // deep of manes
			levelkchest = level5; // chest rand
			srand ((unsigned int) time(NULL) * rand ());
			minenum = 0;
			chestr = chestrand;
			chnum = 0;
			nx = x;
			ny = y;
			//cout << 4;
			mblocknum.clear();
			chest.clear();
			chestsize.clear();
			mblocksum = 0;
			for (i = 0; i < oblock.size(); i++)
			{
				if (min(oblock[i][0] + oblock[i][1] * max(level - baselevel, baselevel - level), oblock[i][2]) > 0)
				{
					d = min(oblock[i][0] + oblock[i][1] * max(level - baselevel, baselevel - level), oblock[i][2]);
					mblocksum += d;
					for (GLint j = 0; j < d; j++)
					{
						mblocknum.push_back(i);
					}
				}
			}
			minmap[0] = (x - dy) / 2 - 1;
			minmap[1] = (y - dy) / 2 - 1;
			for (i = 0; i < x; i++)
			{
				for (i2 = 0; i2 < y; i2++)
				{
					for (i3 = 0; i3 < z; i3++)
					{
						block[i][i2][i3] = 0;
					}
				}
			}
			for (i = 0; i < x; i++)
			{
				for (i2 = 0; i2 < y; i2++)
				{
					for (GLint r = 0; r < sizemap; r++)
					{
						map[i][i2][r] = 0;
					}
					map[i][i2][0] = 1;
					map[i][i2][5] = deep - 1;
				}
			}
			//map[x / 2 + 1][y / 2 + 1][0] = 0;
			//cout << 1;
			f();
			/*srand ((unsigned int) time(NULL) * rand ());
			f (x / 2, y / 2);
			srand ((unsigned int) time(NULL) * rand ());
			f (x / 2, y / 2);
			srand ((unsigned int) time(NULL) * rand ());
			f (x / 2, y / 2);
			srand ((unsigned int) time(NULL) * rand ());
			f (x / 2, y / 2);*/
			for (i = 0; i < x; i++)
			{
				for (i2 = 0; i2 < y; i2++)
				{
					if (map[i][i2][0] == 0)
					{
						if (rand () % chrandsum < chestr + levelkchest)
						{
							//chestr = chestrand;
							chnum++;
							map[i][i2][3] = chnum;
						}
						else
						{
							//chestr += chestrand;
						}
					}
				}
			}
			for (i = 0; i < x; i++)
			{
				for (i2 = 0; i2 < y; i2++)
				{
					if (map[i][i2][0] == 0)
					{
						if ((rand () % minerandnum) < minerand + levelkmine)
						{
							map[i][i2][1] = rand () % (deep - 1 - levelkdeep) + 1 + levelkdeep;
							if (map[i][i2][1] > deep - 1)
							{
								map[i][i2][1] = deep - 1;
							}
							minenum++;
						}
					}
				}
			}
			chest.resize(chnum, vector<obj> (chmaxnum));
			chestsize.resize(chnum, -1);
			for (i = 0; i < chnum; i++)
			{
				for (i2 = 0; i2 < chmaxnum; i2++)
				{
					chest[i][i2].type = -1;
				}
			}
			for (i = 0; i < x; i++)
			{
				for (i2 = 0; i2 < y; i2++)
				{
					if (map[i][i2][0] == 0)
					{
						if (map[i][i2][3] == 0)
						{
							i3 = rand () % randtsum;
							if (i3 < randtrap)
							{
								mobj otrap2;
								map[i][i2][2] = -mblock.size() - 1;
								otrap2.posx = i;
								otrap2.posy = i2;
								otrap2.posz = deep - 1;
								otrap2.a = findobj(&otrap, level, &rtrap, &traps);
								mblock.push_back(otrap2);
								map[i][i2][5] = deep - 1;
							}
						}
						else
						{
							if (chrandnum <= 0)
							{
								chestsize[map[i][i2][3] - 1] = 0;
							}
							else
							{
								chestsize[map[i][i2][3] - 1] = rand () % chrandnum + 1;
							}
							for(i3 = 0; i3 < chmaxnum; i3++)
							{
								chest[map[i][i2][3] - 1][i3].type = -1;
							}
							for (i3 = 0; i3 < chestsize[map[i][i2][3] - 1]; i3++)
							{
								chest[map[i][i2][3] - 1][i3] = findobj(&ochest, level, &rchest, &chests);
							}
						}
					}
				}
			}
			rchest.clear();
			chests = -1;
			rtrap.clear();
			traps = -1;
			for (i = 0; i < x; i++)
			{
				for (i2 = 0; i2 < y; i2++)
				{
					if (map[i][i2][0] == 1)
					{
						for (i3 = 0; i3 < wallh; i3++)
						{
							block[i][i2][deep + i3] = 1;
						}
					}
					for (i3 = 0; i3 < deep; i3++)
					{
						block[i][i2][i3] = 2;
					}
					if (map[i][i2][1] != 0)
					{
						for (i3 = 1; i3 <= map[i][i2][1]; i3++)
						{
							GLint a = 0;
							if (mblocksum == 0)
							{
								a = 3;
							}
							else
							{
								a = mblocknum[rand() % mblocksum];
							}
							block[i][i2][deep - i3] = a;
		 				}
					}
					if (map[i][i2][3] != 0)
					{
						block[i][i2][deep] = 4;
					}
				}
			}
			addmainmonsterplace();
			//cout << '\n';
			/*for (i = 0; i < x; i++)
			{
				for (i2 = 0; i2 < y; i2++)
				{
					if (map[i][i2][2] == 0)
					{
						if (map[i][i2][3] != 0)
						{
							cout << -(map[i][i2][3]) << ' ';
						}
						else
						{
							cout << ' ' << map[i][i2][0] << ' ';
						}
					}
					else
					{
						cout << '+' << map[i][i2][2] << ' ';
					}
				}
				cout << '\n';
			}*/
			/*for (i = 0; i < x; i++)
			{
				for (i2 = 0; i2 < y; i2++)
				{
					cout << map[i][i2][3] << ' ';
				}
				cout << '\n';
			}*/
			//cout << chnum << ' ' << minenum << '\n';
			/*for (i = 0; i < chnum; i++)
			{
				for (i2 = 0; i2 <= chest[i][0]; i2++)
				{
					cout << chest[i][i2] << ' ';
				}
				cout << '\n';
			}*/
		}

		gmap()
		{
			mapsx = constx;
			mapsy = consty;
			initbool = false;
		}

		~gmap()
		{
			//deletemap();
		}
	};
}
