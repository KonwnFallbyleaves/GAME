#include<graphics.h>
#include<conio.h>
#include<string>
#include<iostream>
#include<vector>
#include<windows.h>
#include<stdio.h>
#include<time.h>
//extern "C"
#define width 12
#define heigh 12
using namespace std;

struct atk_juli//攻击距离类型
{
	int up = 0;//上
	int down = 0;//下
	int left = 0;//左
	int right = 0;//右
	int left_up = 0;//左上
	int right_up = 0;//右上
	int left_down = 0;//左下
	int right_down = 0;//右下

};
struct move_juli//移动距离类型
{
	int up = 0;//上
	int down = 0;//下
	int left = 0;//左
	int right = 0;//右
	int left_up = 0;//左上
	int right_up = 0;//右上
	int left_down = 0;//左下
	int right_down = 0;//右下
};
struct buff;//提前声明

struct player;
void get_bjcard(int, int, int, int, player*);
//struct map_wg;
struct chess
{
	int jcno;
	int xs_x;//像素x坐标
	int xs_y;//像素y坐标
	int master;//两种方案，用int或用player类型
	player* master_1;
	int x;//棋盘数组x坐标
	int y;//棋盘数组y坐标
	int ATK;
	float atk_ts = 0.0;//攻击力提升
	int max_HP;
	float mhp_tx = 0.0;//最大血量提升
	int HP;
	int NP;
	int NP_ts = 0;//NP提升
	std::string name;
	int NO;
	int star;
	int job;
	int lv = 1;//等级
	int zicong = 0;//自充
	float zc_ts = 0.0;//自充提升
	bool pd_move;//判断是否能移动
	bool pd_atk;//判断是否能攻击
	float def = 0.0;//伤害减免
	void* bd = NULL;//任意类型指针
	LPCTSTR kamian_lc;//卡面地址,LPCTSTR是文件类型，可由const char 自动转化
	LPCTSTR qimian_lc;//棋面地址
	IMAGE kamian;//卡面的图片
	IMAGE qimian;//棋面的图片
	chess* zxzj = this;
	bool bd_isornot = false;//被动是否触发了？,默认为false
	int zt = 0;//状态0为正常，状态为1为无敌状态
	int magic_occu;//资源占用
	int magic_cost;//法力花费
	string ms;
	vector< buff >buff;
	chess(int a, int mh, int h, int np, std::string s, int n, int p,
		int d, int zc, bool pm, bool pa, int mo, int mc, void* bd, LPCTSTR sl, LPCTSTR ql);//构造函数声明
	chess() = default;
	atk_juli aj;//攻击距离
	move_juli mj;//移动距离
	int dq_hao;//当前的号
	int zh_hh = 0;//召唤回合
	void hh_move(int& round) {
		if (round - zh_hh > 0) {
			this->pd_move = true;
		}
	};//判断一回合后移动的函数
	void hh_atk(int& round) {
		if (round - zh_hh > 0) {
			this->pd_atk = true;
		}
	}
	void gj_zc() {//攻击自充，即攻击时自从获得NP值
		if (this->NP < 100)
			this->NP = this->NP + (int)(zicong*(1+zc_ts));
	}
	void ss_zc() {
		//受伤自充，即受到伤害时的自充值
		if (this->NP < 100)
			this->NP = this->NP + (int)(zicong*(1 + zc_ts) );
	}
	void elevate();
};
void chess::elevate() {
	if (NP > 100) {
		if (lv < 5) {
			lv++;
			ATK += (int)(ATK * 0.1);
			max_HP += (int)(max_HP * 0.2);
			HP += (int)(max_HP * 0.2);
			get_bjcard(NO, lv, 1, NP - 100, master_1);
			NP = 0;
			
		}
	}
}
chess::chess(int a, int mh, int h, int np, std::string s, int n, int p,
	int d, int zc, bool pm, bool pa, int mc, int mo, void* b, LPCTSTR sl, LPCTSTR ql)
{

	ATK = a;
	max_HP = mh;
	HP = h;
	NP = np;

	name = s;//英灵的名字
	NO = n;//编号
	star = p;
	job = d;
	zicong = zc;
	pd_move = pm;
	pd_atk = pa;

	magic_cost = mc;
	magic_occu = mo;

	bd = b;

	kamian_lc = sl;//在手牌上的图片的地址
	qimian_lc = ql;//在棋盘上的图片的地址

	loadimage(&kamian, kamian_lc);
	loadimage(&qimian, qimian_lc);


}
void init_mj(chess* qizi, int a, int b, int c, int d, int e, int f, int g, int h)
{
	qizi->mj.up = a;
	qizi->mj.down = b;
	qizi->mj.left = c;
	qizi->mj.right = d;
	qizi->mj.left_up = e;
	qizi->mj.left_down = f;
	qizi->mj.right_up = g;
	qizi->mj.right_down = h;
}
void init_aj(chess* qizi, int a, int b, int c, int d, int e, int f, int g, int h)
{
	qizi->aj.up = a;
	qizi->aj.down = b;
	qizi->aj.left = c;
	qizi->aj.right = d;
	qizi->aj.left_up = e;
	qizi->aj.left_down = f;
	qizi->aj.right_up = g;
	qizi->aj.right_down = h;
}
struct map_wg;
struct magic {//法术牌
	int jl;//释放距离
	int magic_cost;
	std::string name;
	IMAGE kamian;
	LPCTSTR kamian_lc;//卡面地址
	int xgc = 0;//效果数量
	double sz[5] = { 0,0,0,0,0 };//数值
	int use_object[5] = { 0,0,0,0,0 };//该法术使用的对象,0代表无对象，1代表我方，2代表对方,3代表我方角色，4代表敌方角色,5代表敌我双方
	bool is_all = false;//是否能对英雄使用
	bool is_click[5] = { false,false,false,false,false };
	int range_h;
	int range_w;
	void* skill[5];
	int dq_sf = 0;//记录当前释放第几个效果
	map_wg* mb[5];
	magic() = default;
	magic(int j, int mc, std::string n, int xc, double* s, int* uo, bool ia, int rh, int rw, void** sk, bool* ic, LPCTSTR kamian_lc);
};
magic::magic(int j, int mc, std::string n, int xc, double* s, int* uo, bool ia, int rh, int rw, void** sk, bool* ic, LPCTSTR kamian_lc) {//法术牌的构造函数
	is_all = ia;
	jl = j;
	magic_cost = mc;
	name = n;
	xgc = xc;
	range_h = rh;
	range_w = rw;
	for (int i = 0; i < xgc; i++) {
		sz[i] = s[i];
		use_object[i] = uo[i];

		skill[i] = sk[i];
		is_click[i] = ic[i];
	}
	loadimage(&kamian, kamian_lc);
}
struct kacao//卡槽
{
	int max_c = 4;//最大手牌数
	//unsigned int count = 0;//记录牌数
	int sb_zq = -1;//当前鼠标抓取的牌
	std::vector<chess> ka;
	int count() {
		return this->ka.size();
	}
};
struct magic_kacao {//法术牌卡槽
	int max_c = 8;
	std::vector<magic> ka;
	int count() {
		return this->ka.size();
	}


};
struct gz_buff;
struct map_wg//棋盘上的网格，用以放置棋子
{
	bool pd = true;//判断是否为空,true为可放置状态。false为不可放置状态
	chess* qizi = NULL;//棋子
	int hj = 0;//环境
	float atk_ts1=0.0;
	float zc_ts1=0.0;
	float def1=0.0;
	float atk_ts2 = 0.0;
	float zc_ts2 = 0.0;
	float def2 = 0.0;
	void xgatk(float sz,int master) {
		if (master == 1) {
			atk_ts1 += sz;
			return;
		}
		atk_ts2 += sz;
		return;
	}
	void xgzc(float sz, int master) {
		if (master == 1) {
			zc_ts1 += sz;
			return;
		}
		zc_ts2 += sz;
		return;
	}
	void xgdef(float sz, int master) {
		if (master == 1) {
			def1 += sz;
			return;
		}
		def2 += sz;
		return;
	}
	float atk_ts(int master) {
		if (master == 1) {
			return atk_ts1;
		}
		return atk_ts2;
	}
	float zc_ts(int master) {
		if (master == 1) {
			return zc_ts1;
		}
		return zc_ts2;
	}
	float def_ts(int master) {
		if (master == 1) {
			return def1;
		}
		return def2;
	}
	vector<gz_buff> buff;

};
struct mouse//记录鼠标的各种状态
{
	int mouse_zt = 1;//，默认为1,1即为空；3为已抓取东西,2为点击在场的棋子
	int dq_hao = -1;//当前鼠标抓住卡片的序号,-1为没有卡片(用在英灵卡上)
	int dq_fshao = -1;//用在法术卡上，记录序号
	chess* dq_ka = NULL;//当前鼠标抓取的卡牌
	magic* dq_fska = NULL;//当前的法术卡
	map_wg* gz = NULL;//在状态2下，记录移动前棋子在棋盘上的格子
};

struct Flag
{
	int i = -1;
	int j = -1;
	map_wg* wg = NULL;
	int zt = 0;//状态
	int sy_zt = 0;//使用状态
	chess* qz = NULL;
};


struct cardstrone {//牌库
	int lx;//1为棋子牌，2为法术牌
	vector<chess> ck;
	vector<magic> mk;
	vector<magic> bj;//宝具牌
	int  chesscard_size() {
		return ck.size();
	}
	int magiccard_size() {
		return mk.size();
	}

};
struct player
{
	int pl;//等于1为在玩家一，位于棋盘下方。等于2为玩家二，为棋盘上方
	int NO;
	string name;
	int tx_x;//头像位置x坐标
	int tx_y;//头像位置y坐标
	int tx_zx_x;//头像的右下x坐标
	int tx_zx_y;//头像的右下y坐标
	int tx_wz;//记录存储头像图片数组的下标，迫不得已这么做！！！
	int HP = 10000;
	int max_hp = 10000;
	int max_magc;
	int dq_magc;
	int max_resource;//最大法术资源（供给）
	int dq_resource;//当前法术资源
	int fs_jlts = 0;//法术伤害提升
	float fs_shts = 0.0;//法术伤害提升
	int zt = 0;//状态
	cardstrone paiku;//牌库
	chess* dq_chess = new chess[99];//当前在棋盘上的棋子
	map_wg* (*dq_gz) = new map_wg * [99];//记录对应下标棋子所在的格子
	//map_wg* dq_gz[99];
	int dq_count = 0;
	void chess_push(chess n, map_wg* m) {
		if (dq_count < 100) {
			dq_chess[dq_count] = n;
			dq_gz[dq_count] = m;//原来写成n.dq
			dq_chess[dq_count].dq_hao = dq_count;//n.dq_hao记录在数组的哪个位置,原来写成n.dq_hao=dq_count造成bug找了很久
			dq_count++;//更新最新的个数
		}
	}

	kacao yl;//该玩家的卡槽
	magic_kacao fs;//法术卡槽
	bool be_atk = false;//判断是否被攻击
	player(int no, string n, int dz, int hp, int mh, int x, int y, int max_m, int max_r,cardstrone pk);
};
player::player(int no, string n, int dz, int hp, int mh, int x, int y, int max_m, int max_r, cardstrone pk) {

	NO = no;
	name = n;
	tx_wz = dz;
	HP = hp;
	max_hp = mh;
	tx_x = x;
	tx_y = y;
	max_magc = max_m;
	dq_magc = max_m;
	max_resource = max_r;
	dq_resource = max_r;
	paiku = pk;
	tx_zx_x = tx_x + 50 * 2;
	tx_zx_y = tx_x + 50 * 2;

}
//buff类型
struct buff {
	float sz;
	int round;//放置的回合
	int time;//持续的回合
	bool sf = false;//判断是否发动了
	int lx = 0;

	void xg(chess* d) {
		//类型1，攻击力提升。类型2为HP每回合增加的效果。类型3为NP每回合增加。类型4为自充提升
		if (this->lx == 2 && sf == true) {
			if (d->HP + (int)sz <= d->max_HP)
				d->HP += (int)sz;
			else
				d->HP = d->max_HP;
		}
		else if (this->lx == 3 && sf == true) {
			d->NP += (int)sz;
		}
		
	}
	void provid(chess* d) {
		if (this->lx == 1 && sf == true) {//
			d->atk_ts += sz;

		}
		else if (this->lx == 4 && sf == true) {
			d->zc_ts += sz;
		}
		else if (this->lx == 5 && sf == true) {
			d->zt = 1;
		}
	}
	void remove(chess* d) {
		if (this->lx == 1 && sf == true) {
			d->atk_ts -= sz;
		}
		else if (this->lx == 2 && sf == true) {
			return;
		}
		else if (this->lx == 3 && sf == true) {
			return;
		}
		else if (this->lx == 4 && sf == true) {
			d->zc_ts -= sz;
		}
		else if (this->lx == 5 && sf == true) {
			d->zt = 0;
		}
	}
	bool tremove(int r, chess* d, int w) {
		if (r == round + time) {
			this->remove(d);
			d->buff.erase(d->buff.begin() + w);
			return true;
		}
		else
			return false;
	}
	buff(float s, int t, int r, int l,bool fd);
};
buff::buff(float s, int t, int r, int l,bool fd) {
	sz = s;
	time = t;
	round = r;
	lx = l;
	sf = fd;
}

struct gz_buff {
	float sz;
	int round;//放置的回合
	int time;//持续的回合
	bool sf = false;//判断是否发动了
	int lx = 0;//类型1为提升攻击力，类型2为恢复HP，类型3为恢复NP，类型4为自充
	bool py;//是否为凭依类型格子buff,true为凭依
	chess* pyqz=NULL;//凭依棋子
	int ly;
	int master = 0;
	//int fw;

	void xg(map_wg *gz) {
		//类型1，攻击力提升。类型2为HP每回合增加的效果。类型3为NP每回合增加。类型4为自充提升,类型5为防御减免
		if (gz->qizi!=NULL&&this->lx == 2 && sf == true&&gz->qizi->master==master) {
			if (gz->qizi->HP + (int)sz <= gz->qizi->max_HP)
				gz->qizi->HP += (int)sz;
			else
				gz->qizi->HP = gz->qizi->max_HP;
		}
		else if (gz->qizi != NULL && this->lx == 3 && sf == true && gz->qizi->master == master) {
			gz->qizi->NP += (int)sz;
		}

	}
	void provid(map_wg* gz) {
		if (this->lx == 1 && sf == true ) {//
			if(this->py)
				gz->xgatk(sz,master);
		}
		else if (this->lx == 4 && sf == true) {
			gz->xgzc(sz,master);
		}
		else if (this->lx == 5 && sf == true ) {
			//outtextxy(1300, 50, "!!!!");
			gz->xgdef(sz,master);
		}
	}
	void remove(map_wg* gz) {
		if (this->lx == 1 && sf == true) {
			gz->xgatk(-sz, master);
		}
		
		else if (this->lx == 4 && sf == true ) {
			gz->xgzc(-sz, master);
		}
		else if (this->lx == 5 && sf == true) {
			gz->xgdef(-sz, master);
		}
		
	}
	bool tremove(int r, map_wg* gz, int w,int x,int y) {
		if (!py&&r == this->round + this->time) {//此round为gz_buff的
			this->remove(gz);
			gz->buff.erase(gz->buff.begin() + w);
			return true;
		}
		else if (py&&pyqz != NULL && ((abs(x - pyqz->x) > time) || (abs(y - pyqz->y) > time))) {//凭依buff，time为范围
			this->remove(gz);
			gz->buff.erase(gz->buff.begin() + w);
			//outtextxy(1300, 50, "!!!!");
			return true;
		}
		else if (py && pyqz != NULL && pyqz->HP <= 0) {
			this->remove(gz);
			gz->buff.erase(gz->buff.begin() + w);
			//outtextxy(1300, 50, "!!!!");
			return true;
		}
		else
			return false;
	}
	
	gz_buff(float s, int t, int r, int l, bool fd,bool p,chess*q,int ma);
};
gz_buff::gz_buff(float s, int t, int r, int l, bool fd,bool p,chess* q,int ma) {//当为凭依buff时，t为fw的形参
	sz = s;
	time = t;
	round = r;
	lx = l;
	sf = fd;
	py = p;
	if (p) {
		this->pyqz = q;
		ly = q->jcno;
		master = q->master;
		//outtextxy(1300, 50, "!!!!");
	}
	else {
		ly = -1;
		master = ma;
	}
		
}


void bd0(player* p, Flag* f, chess* from,map_wg**gz, int ms) {//空被动，即没被动
	return;
}
void bd1(player* p, Flag* f, chess* from, map_wg** gz, int ms) {//ms为模式，=1时为添加被动，=2时为去除被动=3为新模式

	if (from->bd_isornot == false && ms == 1) {//false时即没发动被动
		for (int i = 0; i < p->dq_count; i++) {
			p->dq_chess[i].atk_ts += 0.2;
		}
		from->bd_isornot = true;
	}
	else if (from->bd_isornot == true && ms == 2) {
		for (int i = 0; i < p->dq_count; i++) {
			p->dq_chess[i].atk_ts -= 0.2;
		}
		from->bd_isornot = false;
	}
	//下面这个if放在前和放在后有很大差别
	if (f->sy_zt == 1 && f->qz != NULL) {//后面加入棋子时触发
		if (f->qz->bd_isornot == false)
			f->qz->atk_ts += 0.2;
	}
}
void bd2(player* p, Flag* f, chess* from, map_wg** gz, int ms) {
	gz_buff b(0.2, 2, 0, 1, true, true, from,p->pl);
	if (ms == 1) {
		for (int i = 0; i < 2*2; i++) {
			for (int j = 0; j < 2*2; j++) {
				int x = from->x - 2 + j; int y = from->y - 2 + i;
				if (x >= 0 && x < width && y >= 0 && y < heigh) {
					int flag = 0;
					for (int k = 0; k < gz[y][x].buff.size(); k++) {
						if (gz[y][x].buff[k].ly == from->jcno) {
							flag = 1;
						}
					}
					if (flag == 0) {
						gz[y][x].buff.push_back(b);
						gz[y][x].buff.back().provid(&gz[y][x]);
					}
				}
				
			}
		}
	}
	else if (ms == 2) {
		for (int i = 0; i < 2 * 2; i++) {
			for (int j = 0; j < 2 * 2; j++) {
				int x = from->x - 2 + j; int y = from->y - 2 + i;
				if (x >= 0 && x < width && y >= 0 && y < heigh) {
					int wz = -1;
					for (int k = 0; k < gz[y][x].buff.size(); k++) {
						if (gz[y][x].buff[k].ly == from->jcno) {
							wz = k;
							break;
						}
					}
					if (wz != -1)
						gz[y][x].buff.erase(gz[y][x].buff.begin() + wz);
				}
			}
		}
	}
}
void bd3(player* p, Flag* f, chess* from, map_wg** gz, int ms) {
	if (from->bd_isornot == false && ms == 1) {
		if (p->dq_count == 1) {
			from->ATK += from->ATK * 4;
			from->bd_isornot = true;
		}
	}
	else if (from->bd_isornot == true && ms == 1) {
		if (p->dq_count > 1) {
			//outtextxy(1300, 50, "!!!!");
			from->ATK -= (from->ATK)*4/5;
			from->bd_isornot = false;
		}
	}
}
void bd4(player* p, Flag* f, chess* from, map_wg** gz, int ms) {
	if (f->sy_zt == 3) {
		srand((unsigned)time(NULL));
		int sj = rand() % p->fs.ka.size();
		p->fs.ka.push_back(p->fs.ka[sj]);
	}
}

chess kong;
void disp_jl(int x, int y, map_wg** cb, move_juli& jl, int map_jx_x, int map_jx_y)//显示距离
{
	cb[y][x].hj = 2;
	for (int i = 1; i <= jl.up; i++)
	{
		if (y + i < map_jx_y) {
			cb[y + i][x].hj = 2;
			if (cb[y + i][x].pd == false)
				break;
		}

	}
	for (int i = 1; i <= jl.down; i++)
	{
		if (y - i >= 0) {
			cb[y - i][x].hj = 2;
			if (cb[y - i][x].pd == false)
				break;
		}

	}
	for (int i = 1; i <= jl.left; i++)
	{
		if (x + i < map_jx_x) {
			cb[y][x + i].hj = 2;
			if (cb[y][x + i].pd == false)
				break;
		}

	}
	for (int i = 1; i <= jl.right; i++)
	{
		if (x - i >= 0) {
			cb[y][x - i].hj = 2;
			if (cb[y][x - i].pd == false)
				break;
		}

	}
	for (int i = 1; i <= jl.left_up; i++)
	{
		if (y - i >= 0 && x - i >= 0) {
			cb[y - i][x - i].hj = 2;
			if (cb[y - i][x - i].pd == false)
				break;
		}

	}
	for (int i = 1; i <= jl.left_down; i++)
	{
		if (y + i < map_jx_y && x - i >= 0) {
			cb[y + i][x - i].hj = 2;
			if (cb[y + i][x - i].pd == false)
				break;
		}

	}
	for (int i = 1; i <= jl.right_up; i++)
	{
		if (y - i >= 0 && x + i < map_jx_x) {
			cb[y - i][x + i].hj = 2;
			if (cb[y - i][x + i].pd == false)
				break;
		}

	}
	for (int i = 1; i <= jl.right_down; i++)
	{
		if (y + i < map_jx_y && x + i < map_jx_x) {
			cb[y + i][x + i].hj = 2;
			if (cb[y + i][x + i].pd == false)
				break;
		}

	}
}
void disp_al(int& x, int& y, map_wg** cb, atk_juli& jl, int map_jx_x, int map_jx_y)//显示攻击距离
{

	for (int i = 1; i <= jl.up; i++)
	{
		if (y + i < map_jx_y) {
			cb[y + i][x].hj = 3;
			if (cb[y + i][x].pd == false)
				break;
		}

	}
	for (int i = 1; i <= jl.down; i++)
	{
		if (y - i >= 0) {
			cb[y - i][x].hj = 3;
			if (cb[y - i][x].pd == false)
				break;
		}

	}
	for (int i = 1; i <= jl.left; i++)
	{
		if (x + i < map_jx_x) {
			cb[y][x + i].hj = 3;
			if (cb[y][x + i].pd == false)
				break;
		}

	}
	for (int i = 1; i <= jl.right; i++)
	{
		if (x - i >= 0) {
			cb[y][x - i].hj = 3;
			if (cb[y][x - i].pd == false)
				break;
		}

	}
	for (int i = 1; i <= jl.left_up; i++)
	{
		if (y - i >= 0 && x - i >= 0) {
			cb[y - i][x - i].hj = 3;
			if (cb[y - i][x - i].pd == false)
				break;
		}

	}
	for (int i = 1; i <= jl.left_down; i++)
	{
		if (y + i < map_jx_y && x - i >= 0) {
			cb[y + i][x - i].hj = 3;
			if (cb[y + i][x - i].pd == false)
				break;
		}

	}
	for (int i = 1; i <= jl.right_up; i++)
	{
		if (y - i >= 0 && x + i < map_jx_x) {
			cb[y - i][x + i].hj = 3;
			if (cb[y - i][x + i].pd == false)
				break;
		}

	}
	for (int i = 1; i <= jl.right_down; i++)
	{
		if (y + i < map_jx_y && x + i < map_jx_x) {
			cb[y + i][x + i].hj = 3;
			if (cb[y + i][x + i].pd == false)
				break;
		}

	}
}
void disp_fs(int& x, int& y, map_wg** cb, int range_x, int range_y, int map_jx_x, int map_jx_y) {
	int i, j;
	for (i = 0; i < range_x; i++)
		for (j = 0; j < range_y; j++) {
			if (x+i < map_jx_x && y+j < map_jx_y)
				cb[y + j][x + i].hj = 4;
		}

}
void zhandou(chess* h1, chess* h2,map_wg*gz1,map_wg*gz2) {//战斗
	//h2->HP = h2->HP - ( (int)( h1->ATK + (int)(h1->ATK * h1->atk_ts) + (int)(h1->ATK * gz1->atk_ts(h1->master)) )*(1 - gz2->def_ts(h2->master)) );
	h2->HP = h2->HP - (int)((h1->ATK * (1 + h1->atk_ts + gz1->atk_ts(h1->master))) * (1 - gz2->def_ts(h2->master)));
	h1->NP += (int)(h1->zicong * (1 + h1->zc_ts + gz1->zc_ts(h1->master)) * 1.5);
	//h1->gj_zc(gz1);
	if (h1->job == 1 && h2->HP > 0) {//职介为1
		//h2->ss_zc(gz2);
		h2->NP += (int)(h2->zicong * (1 + h2->zc_ts + gz2->zc_ts(h2->master)));
		h1->HP = h1->HP - (int)((h2->ATK * (1 + h2->atk_ts + gz2->atk_ts(h2->master))) * (1 - gz1->def_ts(h1->master)));
	}
	h1->pd_atk = false;
}
void zhandou(chess* h1, player* h2,map_wg *gz) {//战斗函数重载
	h2->HP = h2->HP - (int)(h1->ATK * (1 + h1->atk_ts +gz->atk_ts(h1->master)));
	h1->NP += (int)(h1->zicong * (1 + h1->zc_ts + gz->zc_ts(h1->master)) * 1.5);
	//h1->gj_zc(gz);
	h1->pd_atk = false;
}


void death(player* p, player* dp, Flag* f, map_wg** cb) {//死亡判断
	for (int i = 0; i < p->dq_count; i++) {
		if (p->dq_chess[i].HP <= 0 && i != p->dq_count - 1) {
			((void(*)(player*, Flag*, chess*, int))p->dq_chess[i].bd)(p, f, &p->dq_chess[i], 2);//删除被动
			for (int j = i; j < p->dq_count - 1; j++) {
				p->dq_gz[j]->pd = true;
				p->dq_gz[j]->qizi = NULL;
				p->dq_chess[j] = p->dq_chess[j + 1];
				p->dq_gz[j + 1]->qizi = &p->dq_chess[j];
				p->dq_gz[j] = p->dq_gz[j + 1];
				p->dq_chess[j].dq_hao--;
			}
			p->dq_count--;
			//outtextxy(1200, 50, "!!!!");
		}
		else if (p->dq_chess[i].HP <= 0 && i == p->dq_count - 1) {
			((void(*)(player*, Flag*, chess*, int))p->dq_chess[i].bd)(p, f, &p->dq_chess[i], 2);//删除被动
			p->dq_gz[i]->pd = true;
			p->dq_gz[i]->qizi = NULL;
			p->dq_count--;
		}
	}
	for (int i = 0; i < dp->dq_count; i++) {
		if (dp->dq_chess[i].HP <= 0 && i != dp->dq_count - 1) {
			((void(*)(player*, Flag*, chess*, int))dp->dq_chess[i].bd)(dp, f, &dp->dq_chess[i], 2);
			for (int j = i; j < dp->dq_count - 1; j++) {
				dp->dq_gz[j]->pd = true;
				dp->dq_gz[j]->qizi = NULL;
				dp->dq_chess[j] = dp->dq_chess[j + 1];
				dp->dq_gz[j + 1]->qizi = &dp->dq_chess[j];
				dp->dq_gz[j] = dp->dq_gz[j + 1];
				dp->dq_chess[j].dq_hao--;
			}
			dp->dq_count--;
		}
		else if (dp->dq_chess[i].HP <= 0 && i == dp->dq_count - 1) {
			((void(*)(player*, Flag*, chess*, map_wg **, int))dp->dq_chess[i].bd)(dp, f, &dp->dq_chess[i],cb, 2);
			dp->dq_gz[i]->pd = true;
			dp->dq_gz[i]->qizi = NULL;
			dp->dq_count--;
		}
	}
	if (p->HP <= 0 || dp->HP <= 0) {
		f->zt = 10;
	}
}


//造成伤害
void damage(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {//伤害

	if (y >= 10 && y < 12 && x >= 5 && x < 7) {
		if (p->pl == 1)
			p->HP -= (int)sh;
		else
			dp->HP -= (int)sh;
	}
	else if (y >= 0 && y < 2 && x >= 5 && x < 7) {
		if (p->pl == 2)
			p->HP -= (int)sh;
		else
			dp->HP -= (int)sh;
	}
	if (uob == 2) {//判断2为只对敌方伤害
		for (int j = 0; j < range_h; j++) {
			for (int k = 0; k < range_w; k++) {
				if (cb[y + j][x + k].pd == false && cb[y + j][x + k].hj == 4 && cb[y + j][x + k].qizi->master != dq_player&& cb[y + j][x + k].qizi->zt!=1)
					cb[y + j][x + k].qizi->HP -= ((int)sh- (int)(sh*(cb[y + j][x + k].qizi->def)));
			}
		}
	}

}

void all_damage(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {//对敌方全体伤害
	for (int i = 0; i < dp->dq_count; i++) {
		if(dp->dq_chess[i].zt != 1)
			dp->dq_chess[i].HP -= ((int)sh - (int)(sh * (dp->dq_chess[i].def)));
	}
	dp->HP -= (int)sh;
}
void frozen(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {//冻结
	if (uob == 5) {
		for (int j = 0; j < range_h; j++)
			for (int k = 0; k < range_w; k++) {
				if (cb[y + j][x + k].pd == false && cb[y + j][x + k].hj == 4) {
					cb[y + j][x + k].qizi->zh_hh = round + (int)sh;
					cb[y + j][x + k].qizi->pd_move = false;
					cb[y + j][x + k].qizi->pd_atk = false;
				}
			}
	}
}
void get_che(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	if (uob == 5)
		mb[n] = &cb[y][x];
	else if (uob == 3) {
		if (cb[y][x].qizi!=NULL&&cb[y][x].qizi->master == dq_player)
			mb[n] = &cb[y][x];
	}
	else if (uob == 6) {
		if (cb[y][x].pd != false)
			mb[n] = &cb[y][x];
	}

}
void swap_che(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	swap(mb[0]->qizi->x, mb[1]->qizi->x);
	swap(mb[0]->qizi->y, mb[1]->qizi->y);
	swap(mb[0]->qizi->xs_x, mb[1]->qizi->xs_x);
	swap(mb[0]->qizi->xs_y, mb[1]->qizi->xs_y);
	swap(mb[0]->qizi, mb[1]->qizi);
	if (mb[0]->qizi->master_1==p) {
		if (mb[1]->qizi->master_1 == p) {
			swap(p->dq_gz[mb[0]->qizi->dq_hao], p->dq_gz[mb[1]->qizi->dq_hao]);
			return;
		}
		else {
			swap(p->dq_gz[mb[0]->qizi->dq_hao], dp->dq_gz[mb[1]->qizi->dq_hao]);
			return;
		}

	}
	else if(mb[0]->qizi->master_1 == dp){
		if (mb[1]->qizi->master_1 == dp) {
			swap(dp->dq_gz[mb[0]->qizi->dq_hao], dp->dq_gz[mb[1]->qizi->dq_hao]);
			return;
		}
		else {
			swap(dp->dq_gz[mb[0]->qizi->dq_hao], p->dq_gz[mb[1]->qizi->dq_hao]);
			return;
		}
	}
	
}
void sjyd(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	mb[1]->qizi = mb[0]->qizi;
	mb[1]->qizi->x = x;
	mb[1]->qizi->y = y;
	mb[1]->qizi->xs_x = (x+1)*50;
	mb[1]->qizi->xs_y =(y+1)*50;
	if (mb[0]->qizi->master_1 == p) {
		p->dq_gz[mb[0]->qizi->dq_hao] = mb[1];
	}
	else {
		dp->dq_gz[mb[0]->qizi->dq_hao] = mb[1];
	}
	mb[1]->pd = false;
	mb[0]->pd = true;
	mb[0]->qizi = NULL;

}
//得到攻击力buff
void get_abuff(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	if (uob == 3) {
		buff b(sh, 3, round, 1,true);
		for (int j = 0; j < range_h; j++)
			for (int k = 0; k < range_w; k++) {
				if (cb[y + j][x + k].pd == false && cb[y + j][x + k].hj == 4) {
					if (cb[y + j][x + k].qizi != NULL && cb[y + j][x + k].qizi->master == dq_player) {
						cb[y + j][x + k].qizi->buff.push_back(b);
						cb[y + j][x + k].qizi->buff.back().provid(cb[y + j][x + k].qizi);
					}
					
				}
			}
	}
}
void get_ylcard(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	
}
void get_fscard(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {

}
void get_bjcard(int no,int lv,int lx,int dy,player*p) {
	//这时sh传递第几级，uob传递NO，round传递多出的伤害（NP-100)
	
	int w = no*lv;
	if (w < p->paiku.bj.size()) {
		magic c = p->paiku.bj[w - 1];
		p->fs.ka.push_back(c);
	}
}
void ym(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	dp->HP = 0;
}
//得到无敌buff
void get_wdbuff(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	if (uob == 3) {
		buff b(0, (int)sh, round, 5, true);
		for (int j = 0; j < range_h; j++)
			for (int k = 0; k < range_w; k++) {
				if (cb[y + j][x + k].pd == false && cb[y + j][x + k].hj == 4) {
					if (cb[y + j][x + k].qizi != NULL && cb[y + j][x + k].qizi->master == dq_player) {
						cb[y + j][x + k].qizi->buff.push_back(b);
						cb[y + j][x + k].qizi->buff.back().provid(cb[y + j][x + k].qizi);//启动buff
					}

				}
			}
	}
}//
//得到HPbuff
void get_hbuff(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	if (uob == 3) {
		buff b(sh, 4, round, 2, true);
		for (int j = 0; j < range_h; j++)
			for (int k = 0; k < range_w; k++) {
				if (cb[y + j][x + k].pd == false && cb[y + j][x + k].hj == 4) {
					if (cb[y + j][x + k].qizi != NULL && cb[y + j][x + k].qizi->master == dq_player) {
						cb[y + j][x + k].qizi->buff.push_back(b);
						cb[y + j][x + k].qizi->buff.back().provid(cb[y + j][x + k].qizi);//启动buff
						
					}
				}
			}
	}
}
void get_nbuff(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	if (uob == 3) {
		buff b(sh, 4, round, 3, true);
		for (int j = 0; j < range_h; j++)
			for (int k = 0; k < range_w; k++) {
				if (cb[y + j][x + k].pd == false && cb[y + j][x + k].hj == 4) {
					if (cb[y + j][x + k].qizi != NULL && cb[y + j][x + k].qizi->master == dq_player) {
						cb[y + j][x + k].qizi->buff.push_back(b);
						cb[y + j][x + k].qizi->buff.back().provid(cb[y + j][x + k].qizi);//启动buff
					}
				}
			}
	}
}
//最大生命值提升
void grow_maxHP(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	if (uob == 3) {
		
		for (int j = 0; j < range_h; j++)
			for (int k = 0; k < range_w; k++) {
				if (cb[y + j][x + k].pd == false && cb[y + j][x + k].hj == 4) {
					if (cb[y + j][x + k].qizi != NULL && cb[y + j][x + k].qizi->master == dq_player) {
						cb[y + j][x + k].qizi->max_HP+=sh;
						cb[y + j][x + k].qizi->HP += sh;
					}

				}
			}
	}
}
//污染对方
void de_fl(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	for (int i = 0; i < dp->fs.ka.size(); i++) {
		dp->fs.ka[i].magic_cost += (int)sh;
	}
}

void get_defgzbuff(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	//float s, int t, int r, int l, bool fd,bool p,chess* q
	
	gz_buff b((float)sh, uob, round, 5, true, false,NULL, p->pl);//非凭依buff，由回合控制
	for (int i = 0; i < range_h; i++) {
		for (int j = 0; j < range_w; j++) {
			int xx = x + i;
			int yy = y + j;
			if (xx < width && yy < heigh) {
				//outtextxy(1300, 50, "!!!!");
				cb[yy][xx].buff.push_back(b);
				cb[yy][xx].buff.back().provid(&cb[yy][xx]);
			}
			//
		}
	}
}



//全局变量
int i, j;
int step = 50;
int kamian_step_h = 300;//卡面的高
int kamian_step_w = 175;//卡面的宽
int p_high = 340; int p_width = 600;//卡槽的长宽
int p2_high = 200;//卡槽2的高
int p2_width = 600;//卡槽2的宽

//cardstrone pk;
int chessboard[heigh][width] = {
	{1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{-1, -1, -1, 1, 1, 1, 1, 1, 1, -1, -1, -1},
	{-1, -1, -1, 1, 1, 1, 1, 1, 1, -1, -1, -1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1}
};
IMAGE atk_tb;

//player p1(1, "士郎", 0, 10000, 10000, 300, 550, 100, 100,pk);//创建角色1

//player p2(2, "绮礼", 1, 10000, 10000, 300, 50, 100, 100,pk);//创建角色2


player* p;//创建一个指向玩家类型的指针，便于以后编写回合数时
player* dp;//同上，记录敌对p

int player_temp;
int dq_player;//当前玩家
int dq_ddplayer;//当前敌对玩家


void startup()
{
	initgraph(1440, 720);
	setbkcolor(WHITE);
	cleardevice();
	setlinestyle(PS_SOLID, 2);
	setcolor(RGB(0, 0, 0));
	loadimage(&atk_tb, "D:\\agame\\atk.png");
}
int main()
{
	int jcno = 0;//进场序号，唯一
	double bsz[5] = { 300 };
	int buo[5] = { 2 };
	bool bia = false;
	void* bsk[5] = { all_damage };
	bool bic[5] = { true };
	//int j, int mc, std::string n, int xc, double* s, int* uo, bool ia, int rh, int rw, void** sk, bool* ic, LPCTSTR kamian_lc
	magic bj1(12, 70, "Exculibar", 1, bsz, buo, bia, 1, 1, bsk, bic, "D:\\agame\\bj1.png");
	cardstrone pk;
	pk.bj.push_back(bj1);
	pk.bj.push_back(bj1);
	bj1.sz[0] = 500;
	pk.bj.push_back(bj1);
	pk.bj.push_back(bj1);
	bj1.skill[0] = ym;
	pk.bj.push_back(bj1);
	player p1(1, "士郎", 0, 10000, 10000, 300, 550, 100, 100, pk);//创建角色1

	player p2(2, "绮礼", 1, 10000, 10000, 300, 50, 100, 100, pk);//创建角色2

	IMAGE background;
	loadimage(&background, "D:\\agame\\background.png");
	


	vector<IMAGE> txpt;//头像图片数组
	int round = 1;//回合
	p1.pl = 1;//此1,2为头像所在的位置
	p2.pl = 2;
	dq_player = p1.pl;
	dq_ddplayer = p2.pl;
	p = &p1;
	dp = &p2;
	IMAGE tx;
	loadimage(&tx, "D:\\sl.png");
	txpt.push_back(tx);
	loadimage(&tx, "D:\\ql.png");
	txpt.push_back(tx);



	map_wg** chess_board = new map_wg * [heigh];//创建棋盘的各个网格
	for (i = 0; i < heigh; i++)
		chess_board[i] = new map_wg[width];
	/*int a, int mh, int h, int np, std::string s, int n, int p,
		int d, int zc, bool pm, bool pa, int mo, int mc, void* bd, LPCTSTR sl, LPCTSTR ql*/
	chess arthuria(1200, 2000, 2000, 0, "阿尔托莉雅", 1, 5, 1, 20, false, false, 80, 20, bd1, _T("D:\\agame\\kamian.png"), _T("D:\\agame\\qimian.png"));//未完成，此为原本要加载的内容
	init_mj(&arthuria, 2, 2, 2, 2, 2, 2, 2, 2);//给移动距离赋值
	init_aj(&arthuria, 2, 2, 2, 2, 2, 2, 2, 2);//给攻击距离赋值
	arthuria.ms = string("我方全体攻击力增加20%");
	chess al(1000, 2000, 2000, 0, "艾蕾", 2, 5, 2, 10, false, false, 50, 15, bd2, _T("D:\\agame\\ailei.png"), _T("D:\\agame\\aileik.png"));//未完成，此为原本要加载的内容
	init_mj(&al, 3, 3, 2, 2, 2, 2, 2, 2);//给移动距离赋值
	init_aj(&al, 4, 4, 2, 2, 2, 2, 2, 2);//给攻击距离赋值
	al.ms = string("冥界庇护：周围的友方随从获得攻击力加成");
	chess arthur(1200, 2000, 2000, 0, "亚瑟", 1, 5, 1, 20, false, false, 80, 40, bd3, _T("D:\\agame\\ark.png"), _T("D:\\agame\\arq.png"));//未完成，此为原本要加载的内容
	init_mj(&arthur, 2, 2, 2, 2, 2, 2, 2, 2);//给移动距离赋值
	init_aj(&arthur, 2, 2, 2, 2, 2, 2, 2, 2);//给攻击距离赋值
	arthur.ms = string("巨龙猎手：孤身挑战巨龙，当我方仅亚瑟在场时，攻击力翻5倍");
	chess eliya(800, 1500, 1500, 0, "伊莉雅", 3, 5, 1, 20, false, false, 50, 20, bd4, _T("D:\\agame\\eliyak.png"), _T("D:\\agame\\eliyaq.png"));//未完成，此为原本要加载的内容
	init_mj(&eliya, 5, 5, 1, 1, 2, 2, 2, 2);//给移动距离赋值
	init_aj(&eliya, 5, 5, 1, 1, 1, 1, 1, 1);//给攻击距离赋值
	eliya.ms = string("幻象魔法：每当你使用一张法术，随机复制一张你法术牌到法术手牌中");


	double sz[5] = { 2000 };
	int uo[5] = { 2 };
	bool ia = true;
	void* sk[5] = { damage };
	bool ic[5] = { true };
	magic f1(12, 40, "诅咒结界", 1, sz, uo, ia, 2, 2, sk, ic, "D:\\agame\\fs.png");
	double sz1[5] = { 1 };
	int uo1[5] = { 5 };
	bool ia1 = false;
	void* sk1[5] = { frozen };
	bool ic1[5] = { true };
	magic f2(12, 20, "冰雪风暴", 1, sz1, uo1, ia1, 2, 4, sk1, ic1, "D:\\agame\\fs1.png");
	double sz2[5] = { 0,0,0 };
	int uo2[5] = { 5 ,5,5};
	bool ia2 = false;
	void* sk2[5] = { get_che,get_che,swap_che };
	bool ic2[5] = { true, true,false };
	magic f3(12, 50, "置换术", 3, sz2, uo2, ia2, 1, 1, sk2, ic2, "D:\\agame\\fs2.png");
	double sz3[5] = { 0.5 };
	int uo3[5] = { 3 };
	bool ia3 = false;
	void* sk3[5] = { get_abuff };
	bool ic3[5] = { true };
	magic f4(12, 50, "振奋人心", 1, sz3, uo3, ia3, 4, 4, sk3, ic3, "D:\\agame\\fs3.png");
	double sz4[5] = { 0 ,0,0};
	int uo4[5] = { 3,6,3 };
	bool ia4 = false;
	void* sk4[5] = { get_che,get_che,sjyd };
	bool ic4[5] = { true,true,false };
	magic f5(10, 10, "瞬间移动", 3, sz4, uo4, ia4, 1, 1, sk4, ic4, "D:\\agame\\fs4.png");
	double sz5[5] = { 0 };
	int uo5[5] = { 3};
	bool ia5 = false;
	void* sk5[5] = {get_wdbuff };
	bool ic5[5] = { true };
	magic f6(8, 20, "魔法屏障", 1, sz5, uo5, ia5, 1, 1, sk5, ic5, "D:\\agame\\fs5.png");
	double sz6[5] = { 1000,80 };
	int uo6[5] = { 3,3 };
	bool ia6 = false;
	void* sk6[5] = { get_hbuff,get_nbuff };
	bool ic6[5] = { true,false };
	magic f7(6, 70, "未然绝然的理想乡", 2, sz6, uo6, ia6, 6, 6, sk6,ic6, "D:\\agame\\fs6.png");
	double sz7[5] = { 10 };
	int uo7[5] = { 3};
	bool ia7 = false;
	void* sk7[5] = { de_fl };
	bool ic7[5] = { true };
	magic f8(12, 50, "法术污染", 1, sz7, uo7, ia7, 1, 1, sk7, ic7, "D:\\agame\\fs7.png");
	double sz8[5] = { 1000 };
	int uo8[5] = { 3 };
	bool ia8 = false;
	void* sk8[5] = { grow_maxHP };
	bool ic8[5] = { true };
	magic f9(8, 40, "生命之力", 1, sz8, uo8, ia8, 2, 6, sk8, ic8, "D:\\agame\\fs8.png");
	double sz9[5] = { 0.5 };
	int uo9[5] = { 3 };//回合数
	bool ia9 = false;
	void* sk9[5] = { get_defgzbuff };
	bool ic9[5] = { true };
	magic f10(7, 50, "幻化结界", 1, sz9, uo9, ia9, 4, 5, sk9, ic9, "D:\\agame\\fs9.png");





	//玩家1
	arthuria.master = p1.pl;
	arthuria.master_1 = &p1;
	al.master = p1.pl;
	al.master_1 = &p1;
	arthur.master = p1.pl;
	arthur.master_1 = &p1;
	eliya.master = p1.pl;
	eliya.master_1 = &p1;
	p1.yl.ka.push_back(arthuria);//相当于抽卡进去
	p1.yl.ka.push_back(arthuria);
	p1.yl.ka.push_back(al);
	p1.yl.ka.push_back(arthur);
	p1.yl.ka.push_back(eliya);
	p1.fs.ka.push_back(f1);
	p1.fs.ka.push_back(f1);
	p1.fs.ka.push_back(f2);
	p1.fs.ka.push_back(f3);
	p1.fs.ka.push_back(f4);
	p1.fs.ka.push_back(f5);
	p1.fs.ka.push_back(f6);
	p1.fs.ka.push_back(f7);
	p1.fs.ka.push_back(f8);
	p1.fs.ka.push_back(f9);
	p1.fs.ka.push_back(f10);
	//p1.yl.count = 2;
	//玩家2
	arthuria.master = p2.pl;
	arthuria.master_1 = &p2;
	p2.yl.ka.push_back(arthuria);//相当于抽卡进去
	p2.yl.ka.push_back(arthuria);
	p2.fs.ka.push_back(f1);
	p2.fs.ka.push_back(f1);
	p2.fs.ka.push_back(f2);
	//p2.yl.count = 2;


	int board_x = -1;//记得设置初始化
	int board_y = -1;
	mouse mou;//定义鼠标状态
	MOUSEMSG m;//定义鼠标消息
	auto m_old_x = -1;//旧鼠标坐标
	auto m_old_y = -1;
	IMAGE kamian;//当前鼠标的图片
	int ka_x; int ka_y;//手牌起始位置
	//loadimage(&kamian, _T("D:\\kamian.png"));//300,175;
	int wg_x, wg_y;//用以储存网格的左上角坐标
	Flag flag;//标志，标志1为各种状态
	startup();

	//设置字体
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 10;
	f.lfWidth = 7;
	settextstyle(&f);

	string sgjl;
	string shp;
	string snp;
	string jl;
	string fl;
	string hc1;
	string bs;
	string xh;


	while (1)
	{
		BeginBatchDraw();
		putimage(0, 0, &background);
		//打印头像
		//clearrectangle(720, 50, 1400, 90);
		putimage(p->tx_x, p->tx_y, &txpt[p->tx_wz]);
		putimage(dp->tx_x, dp->tx_y, &txpt[dp->tx_wz]);
		outtextxy(690, 50, "ATK:");
		outtextxy(690, 70, "HP:");
		outtextxy(690, 90, "NP:");
		outtextxy(800, 90, "描述:");
		outtextxy(800, 70, "当前回合法力值:");
		outtextxy(1000, 70, "当前法力供给:");
		outtextxy(1000, 50, "法术距离:");
		outtextxy(800, 50, "当前回合玩家为:");
		outtextxy(1100, 50, "该卡牌法力消耗和法力资源占用:");
		for (i = 0; i < heigh; i++)//描绘棋盘
			for (j = 0; j < width; j++)
			{
				if (chessboard[j][i] == 1)
				{
					if (j == board_y && i == board_x)//board_y和board_x是鼠标更新的坐标
					{
						setfillcolor(YELLOW);
						if (mou.mouse_zt == 3 && m.uMsg == WM_LBUTTONDOWN && chess_board[j][i].pd == true)//放在棋盘上
						{
							//p->dq_magc -= mou.dq_ka->magic_cost;
							p->chess_push(*(mou.dq_ka), &chess_board[j][i]);
							chess_board[j][i].qizi = &p->dq_chess[p->dq_count - 1];
							chess_board[j][i].pd = false;//该网格中有棋子，变为不可放置状态
							chess_board[j][i].qizi->x = i;
							chess_board[j][i].qizi->y = j;
							chess_board[j][i].qizi->xs_x = (i + 1) * step;
							chess_board[j][i].qizi->xs_y = (j + 1) * step;
							chess_board[j][i].qizi->jcno = jcno;
							jcno++;

							flag.qz = chess_board[j][i].qizi;
							flag.sy_zt = 1;//使用状态变为1
							p->yl.ka.erase(p->yl.ka.begin() + mou.dq_hao);//从卡槽中卡牌的数组删除
							//以下鼠标状态恢复
							mou.dq_hao = -1;
							mou.dq_ka = NULL;
							mou.mouse_zt = 1;
							//清除鼠标的卡牌
							clearrectangle(m.x, m.y, m.x + 175, m.y + 300);
						}
						else if (mou.mouse_zt == 2 && m.uMsg == WM_LBUTTONDOWN)//移动棋子
						{
							if (chess_board[j][i].hj == 2 && (chess_board[j][i].pd == true))//即显示绿色的，代表可移动
							{
								//outtextxy(720, 300, _T("移动成功"));
								chess_board[j][i].qizi = mou.dq_ka;
								chess_board[j][i].qizi->x = board_x;
								chess_board[j][i].qizi->y = board_y;
								chess_board[j][i].qizi->xs_x = (i + 1) * step;
								chess_board[j][i].qizi->xs_y = (j + 1) * step;
								p->dq_gz[mou.dq_ka->dq_hao] = &chess_board[j][i];//更新对应保存的格子引用
								chess_board[j][i].pd = false;//该网格中有棋子,变为不可放置状态
								chess_board[j][i].qizi->pd_move = false;
								mou.gz->pd = true;//将原来棋子所在的网格变为可放置状态
								mou.gz->qizi = NULL;/*使用这个会引发错误，因为在移动棋子时原来的格子的棋子指针变空，但因为是elseif原因已经执行了一个分支，
													下面的因鼠标在不同位置后该执行flag=0的分支被排除了，继续触发flag=1时该运行的函数，却又因flag保存的原来格
													子的棋子指针被变空了，引发了错误，该手动添加flag=0；*/
								flag.zt = 0;
								flag.sy_zt = 1;//意味着放置了棋子
								//将鼠标状态恢复为1
								mou.dq_hao = -1;
								mou.dq_ka = NULL;
								mou.mouse_zt = 1;
							}
							else if (chess_board[j][i].hj == 2 && ((chess_board[j][i].qizi) == mou.dq_ka))//原地移动
							{

								//将鼠标状态恢复为1
								mou.dq_hao = -1;
								mou.dq_ka = NULL;
								mou.mouse_zt = 1;
							}
						}
						//下面为攻击时
						else if (chess_board[j][i].pd == false && m.uMsg == WM_LBUTTONDOWN && chess_board[j][i].qizi->master == dq_player && chess_board[j][i].qizi->pd_move == false && chess_board[j][i].qizi->pd_atk == true) {
							mou.mouse_zt = 4;//鼠标模式4为攻击状态
							mou.dq_ka = chess_board[j][i].qizi;
							flag.zt = 2;//flag状态2，代表攻击状态，要显示攻击范围
							flag.wg = &chess_board[j][i];
							flag.i = i;
							flag.j = j;
							flag.sy_zt = 2;//意味着进行攻击
						}
						else if (mou.mouse_zt == 4 && m.uMsg == WM_LBUTTONDOWN && chess_board[j][i].hj == 3 && chess_board[j][i].pd == false && chess_board[j][i].qizi->master == dq_ddplayer) {
							zhandou(mou.dq_ka, chess_board[j][i].qizi,flag.wg,&chess_board[j][i]);
							//outtextxy(800, 300, "!!!!");
							//鼠标变回原来
							mou.dq_ka = NULL;
							mou.mouse_zt = 1;
							//flag变回原来
							flag.zt = 0;
							flag.wg = NULL;
						}

						else if (chess_board[j][i].pd == false && m.uMsg == WM_LBUTTONDOWN && chess_board[j][i].qizi->master == dq_player && chess_board[j][i].qizi->pd_move == true)
						{
							mou.mouse_zt = 2;
							mou.dq_ka = chess_board[j][i].qizi;//抓取了棋盘上的棋子
							mou.dq_hao = -1;
							mou.gz = &chess_board[j][i];//存储原来的指针
						}
						else if (chess_board[j][i].pd == false && mou.mouse_zt == 1)//当鼠标移到有棋子的格子时&& mou.mouse_zt != 4&&
						{
							if (chess_board[j][i].qizi->master == dq_player) {
								flag.zt = 1;
								flag.wg = &chess_board[j][i];
								flag.i = i;
								flag.j = j;
							}
							//clearrectangle(720, 50, 1200, 90);
							sgjl = to_string(int(chess_board[j][i].qizi->ATK + (chess_board[j][i].qizi->atk_ts * chess_board[j][i].qizi->ATK)+ (chess_board[j][i].atk_ts(chess_board[j][i].qizi->master)* chess_board[j][i].qizi->ATK)));
							shp = to_string(chess_board[j][i].qizi->HP);
							snp = to_string(chess_board[j][i].qizi->NP);
							string gzsz = to_string(chess_board[j][i].def1);
							char* gjl = (char*)sgjl.data();
							char* dq_hp = (char*)shp.data();
							char* np = (char*)snp.data();
							char* ms = (char*)chess_board[j][i].qizi->ms.data();
							char* gz = (char*)gzsz.data();

							outtextxy(720, 50, gjl);
							outtextxy(720, 70, dq_hp);
							outtextxy(720, 90, np);
							outtextxy(830, 90, ms);
							outtextxy(1300, 50, gz);
						}
						else if (mou.mouse_zt == 5 && mou.dq_fska->dq_sf < mou.dq_fska->xgc && ((p->pl == 1 && j >= heigh - (mou.dq_fska->jl + p->fs_jlts)) || (p->pl == 2 && j <= mou.dq_fska->jl + p->fs_jlts))) {
							jl = to_string(mou.dq_fska->jl);
							char* JL = (char*)jl.data();
							outtextxy(1070, 50, JL);
							if (mou.dq_fska->is_click[mou.dq_fska->dq_sf] == true) {
								disp_fs(i, j, chess_board, mou.dq_fska->range_w, mou.dq_fska->range_h, width, heigh);//显示法术的范围
								if (m.uMsg == WM_LBUTTONDOWN) {
									((void(*)(double, int, int, int, map_wg**, int&, int&, int&, int, map_wg**, int, player*, player*))mou.dq_fska->skill[mou.dq_fska->dq_sf])(mou.dq_fska->sz[mou.dq_fska->dq_sf], mou.dq_fska->use_object[mou.dq_fska->dq_sf], i, j, chess_board, mou.dq_fska->range_h, mou.dq_fska->range_w, dq_player, round, mou.dq_fska->mb, mou.dq_fska->dq_sf, p, dp);
									if (mou.dq_fska->dq_sf < mou.dq_fska->xgc)
										mou.dq_fska->dq_sf++;
								}
							}
							if (mou.dq_fska->dq_sf < mou.dq_fska->xgc && mou.dq_fska->is_click[mou.dq_fska->dq_sf] == false) {
								((void(*)(double, int, int, int, map_wg**, int&, int&, int&, int, map_wg**, int, player*, player*))mou.dq_fska->skill[mou.dq_fska->dq_sf])(mou.dq_fska->sz[mou.dq_fska->dq_sf], mou.dq_fska->use_object[mou.dq_fska->dq_sf], i, j, chess_board, mou.dq_fska->range_h, mou.dq_fska->range_w, dq_player, round, mou.dq_fska->mb, mou.dq_fska->dq_sf, p, dp);
								if (mou.dq_fska->dq_sf < mou.dq_fska->xgc)
									mou.dq_fska->dq_sf++;
							}

							if (mou.dq_fska->dq_sf == mou.dq_fska->xgc) {
								p->fs.ka.erase(p->fs.ka.begin() + mou.dq_fshao);//从法术卡槽中卡牌的数组删除
								mou.mouse_zt = 1;//代表已经释放法术
								mou.dq_fska = NULL;
								mou.dq_fshao = -1;
								flag.sy_zt = 3;//意味使用了法术
							}

						}
						else if ((i != flag.i || j != flag.j) && mou.mouse_zt != 2 && mou.mouse_zt != 4)
							flag.zt = 0;


					}
					else
						setfillcolor(WHITE);
					if (chess_board[j][i].hj == 2)
						setfillcolor(GREEN);
					if (chess_board[j][i].hj == 3)
						setfillcolor(RED);
					if (chess_board[j][i].hj == 4)
						setfillcolor(BLUE);
					wg_x = (i + 1) * step;   wg_y = (j + 1) * step;
					fillrectangle(wg_x, wg_y, wg_x + step, wg_y + step);
					//death(&chess_board[j][i], p, dp, dq_player, dq_ddplayer);
					if (chess_board[j][i].pd == false) {//若格子上为不可放置状态，即为有棋子
						putimage(wg_x, wg_y, &chess_board[j][i].qizi->qimian);
					}
					if (chess_board[j][i].pd == false && chess_board[j][i].hj == 3 && chess_board[j][i].qizi->master == dq_ddplayer)//增加个攻击图标
						putimage(chess_board[j][i].qizi->xs_x + 13, chess_board[j][i].qizi->xs_y + 13, &atk_tb);

				}
				//对格子上的buff进行释放
				/*int k = 0;
				while (k < chess_board[j][i].buff.size()) {
					//chess_board[j][i].buff[k].ly = chess_board[j][i].buff[k].pyqz->dq_hao;
					chess_board[j][i].buff[k].xg(&chess_board[j][i]);
					if (!chess_board[j][i].buff[k].tremove(round, &chess_board[j][i], k,i,j)) {//int r, map_wg* gz, int w,int x,int y
						k++;//只有没触发buff删除后才j++；因为删除时后面的j+1变为j
					}
				}*/
					
				if ((chessboard[j][i] == 2 || chessboard[j][i] == 3) && chess_board[j][i].hj == 3 && dq_player == p->pl)
				{
					dp->be_atk = true;
					putimage(dp->tx_x + 37, dp->tx_y + 37, &atk_tb);
				}
				else if (j == board_y && i == board_x && chessboard[j][i] == 2 && mou.mouse_zt == 1) {
					clearrectangle(720, 50, 820, 90);
					string h_p = to_string(p2.HP);
					char* h_pp = (char*)h_p.data();
					outtextxy(720, 70, h_pp);
				}
				else if (j == board_y && i == board_x && chessboard[j][i] == 3 && mou.mouse_zt == 1) {
					clearrectangle(720, 50, 820, 90);
					string h_p = to_string(p1.HP);
					char* h_pp = (char*)h_p.data();
					outtextxy(720, 70, h_pp);
				}
				else if (j == board_y && i == board_x && (chessboard[j][i] == 2 || chessboard[j][i] == 3)) {
					if (mou.dq_fska!=NULL&&mou.dq_fska->is_all && mou.mouse_zt == 5 && mou.dq_fska->dq_sf < mou.dq_fska->xgc && ((p->pl == 1 && j >= heigh - (mou.dq_fska->jl + p->fs_jlts)) || (p->pl == 2 && j <= mou.dq_fska->jl + p->fs_jlts))) {
						jl = to_string(mou.dq_fska->jl);
						char* JL = (char*)jl.data();
						outtextxy(1030, 50, JL);
						if (mou.dq_fska->is_click[mou.dq_fska->dq_sf] == true) {
							disp_fs(i, j, chess_board, mou.dq_fska->range_w, mou.dq_fska->range_h, width, heigh);//显示法术的范围
							if (m.uMsg == WM_LBUTTONDOWN) {
								((void(*)(double, int, int, int, map_wg**, int&, int&, int&, int, map_wg**, int, player*, player*))mou.dq_fska->skill[mou.dq_fska->dq_sf])(mou.dq_fska->sz[mou.dq_fska->dq_sf], mou.dq_fska->use_object[mou.dq_fska->dq_sf], i, j, chess_board, mou.dq_fska->range_h, mou.dq_fska->range_w, dq_player, round, mou.dq_fska->mb, mou.dq_fska->dq_sf, p, dp);
								if (mou.dq_fska->dq_sf < mou.dq_fska->xgc)
									mou.dq_fska->dq_sf++;
							}
						}
						/*else*/ if (mou.dq_fska->dq_sf < mou.dq_fska->xgc && mou.dq_fska->is_click[mou.dq_fska->dq_sf] == false) {
							((void(*)(double, int, int, int, map_wg**, int&, int&, int&, int, map_wg**, int, player*, player*))mou.dq_fska->skill[mou.dq_fska->dq_sf])(mou.dq_fska->sz[mou.dq_fska->dq_sf], mou.dq_fska->use_object[mou.dq_fska->dq_sf], i, j, chess_board, mou.dq_fska->range_h, mou.dq_fska->range_w, dq_player, round, mou.dq_fska->mb, mou.dq_fska->dq_sf, p, dp);
							if (mou.dq_fska->dq_sf < mou.dq_fska->xgc)
								mou.dq_fska->dq_sf++;
						}

						if (mou.dq_fska->dq_sf == mou.dq_fska->xgc) {
							p->fs.ka.erase(p->fs.ka.begin() + mou.dq_fshao);//从法术卡槽中卡牌的数组删除
							mou.mouse_zt = 1;//代表已经释放法术
							mou.dq_fska = NULL;
							mou.dq_fshao = -1;
							flag.sy_zt = 3;//意味使用了法术
						}

					}
				}



			}
			//之所以放进上面，因为
		for (int i = 0; i < heigh; i++) {
			for (int j = 0; j < width; j++) {
				int k = 0;
				while (k < chess_board[j][i].buff.size()) {
						//chess_board[j][i].buff[k].ly = chess_board[j][i].buff[k].pyqz->dq_hao;
					chess_board[j][i].buff[k].xg(&chess_board[j][i]);
					if (!chess_board[j][i].buff[k].tremove(round, &chess_board[j][i], k, i, j)) {//int r, map_wg* gz, int w,int x,int y
						k++;//只有没触发buff删除后才j++；因为删除时后面的j+1变为j
					}
				}
			}
		}
		//death(p, dp);
		line(13 * step + 20, 0, 13 * step + 20, 720);
		//fillrectangle(680, 370, p_width + 680, p_high + 370);//卡槽的右上角坐标为(680,370)
		//fillrectangle(680, 120, 680 + p2_width, 170 + p2_high);//卡槽2的右上角图标为(680,120),p2_width=600,p2_high=250;
		death(p, dp, &flag,chess_board);
		//手牌框
		for (i = 0; i < p->yl.ka.size(); i++)
		{
			if (mou.dq_hao != i)//鼠标抓取了哪个，哪个就不打印,注意，i是从1开始的
				putimage(700 + i * 30, 400, &p->yl.ka[i].kamian);//x从700开始
		}
		//法术手牌框
		for (i = 0; i < p->fs.ka.size(); i++) {
			if (mou.dq_fshao != i)
				putimage(700 + i * 30, 120, &p->fs.ka[i].kamian);
		}





		//鼠标的各种状态
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)
		{
			board_x = (m.x / step) - 1;
			board_y = (m.y / step) - 1;

		}

		else if (p->yl.ka.size() != 0 && m.uMsg == WM_LBUTTONDOWN && m.x >= 700 && m.x <= 1440 && m.y >= 400 && m.y <= 700)//(m.x-700)/kamian_step_w&&(m.y-400)/kamian_step_h==)
		{
			int sj_mw = 700 + (p->yl.ka.size() * 30);
			int temp = (m.x - 700) / 30;//减700是因为卡槽在700像素的x坐标中开始显示,若有第一张牌肯定是730开始显示
			
			if (temp < p->yl.ka.size())
			{
				//string nb = to_string(temp);
				//char* hao = (char*)nb.data();
				//outtextxy(1300, 50, hao);
				char* ms = (char*)p->yl.ka[temp].ms.data();

				if ((p->dq_magc - (p->yl.ka[temp].magic_cost) >= 0) && (p->dq_resource - p->yl.ka[temp].magic_occu >= 0)) {
					mou.mouse_zt = 3;//3代表鼠标在抓取东西
					mou.dq_hao = temp;//得到卡牌中的第几张,从1开始
					mou.dq_ka = &p->yl.ka[mou.dq_hao];
				}
				else
					outtextxy(850, 90, "法力不足");

				//yl.count--;//手牌数减1
			}
			/*else if ((m.x > (sj_mw - 145) && m.x < sj_mw)) {
				mou.mouse_zt = 3;//3代表鼠标在抓取东西
				mou.dq_hao = p->yl.ka.size() - 1;
				mou.dq_ka = &p->yl.ka[mou.dq_hao];
			}*/
		}
		else if (p->fs.ka.size() != 0 && m.uMsg == WM_LBUTTONDOWN && m.x >= 700 && m.x <= 1440 && m.y >= 120 && m.y <= 370) {
			int temp = (m.x - 700) / 30;
			if (temp < p->fs.ka.size()) {
				if (p->dq_magc - (p->fs.ka[temp].magic_cost)) {
					mou.mouse_zt = 5;//状态5为正在抓住法术牌
					mou.dq_fshao = temp;
					mou.dq_fska = &p->fs.ka[mou.dq_fshao];

				}
				else
					outtextxy(850, 90, "法力不足");
			}
		}
		else if (m.uMsg == WM_RBUTTONDOWN && mou.mouse_zt == 5) {
			mou.mouse_zt = 1;
			mou.dq_fshao = -1;
			mou.dq_fska = NULL;
			flag.zt = 0;
		}
		else if (m.uMsg == WM_RBUTTONDOWN && mou.mouse_zt == 3)//在状态3（即抓住卡片时）点鼠标右键，即把鼠标中卡片放回去
		{
			clearrectangle(m.x, m.y, m.x + 175, m.x + 300);
			mou.mouse_zt = 1;
			mou.dq_hao = -1;
			mou.dq_ka = NULL;
			//yl.count++;//手牌数加1
		}
		else if (m.uMsg == WM_RBUTTONDOWN && mou.mouse_zt == 2)//意味着鼠标这时抓取了棋盘上的棋子，同时点击鼠标右键
		{
			mou.mouse_zt = 1;//将鼠标状态变为1
			//mou.dq_hao=-1;
			mou.dq_ka = NULL;
		}
		else if (m.uMsg == WM_RBUTTONDOWN && mou.mouse_zt == 4) {//当鼠标状态为4并点右键时,代表取消
			mou.dq_ka = NULL;
			mou.mouse_zt = 1;
		}
		else if (m.uMsg == WM_LBUTTONDOWN && mou.mouse_zt == 4 && dp->be_atk == true && (m.x > dp->tx_x && m.x<dp->tx_zx_x && m.y>dp->tx_y && m.y < dp->tx_zx_y)) {//攻击敌方角色判断
			zhandou(mou.dq_ka, dp,flag.wg);
			dp->be_atk = false;//复变为false
			mou.dq_ka = NULL;
			mou.gz = NULL;
			mou.mouse_zt = 1;
			mou.dq_hao = -1;
		}


		if (mou.mouse_zt == 3 && mou.dq_ka != NULL)//鼠标状态3，意味着鼠标正在抓取了卡片
		{
			if (m_old_x != m.x && m_old_y != m.y)
			{
				clearrectangle(m_old_x, m_old_y, m_old_x + 175, m_old_y + 300);
				m_old_x = m.x;//记录旧的鼠标状态便于移动时擦除后面的东西
				m_old_y = m.y;
			}
			putimage(m.x, m.y, &((*mou.dq_ka).kamian));
		}
		//下面两个if可能能优化先标记
		if (p->yl.ka.size() != 0 && m.x >= 700 && m.x <= 1440 && m.y >= 400 && m.y <= 700) {
			int temp = (m.x - 700) / 30;
			if (temp < p->yl.ka.size()) {
				putimage(700 + temp * 30, 400, &p->yl.ka[temp].kamian);
				xh=to_string(p->yl.ka[temp].magic_cost)+" "+to_string(p->yl.ka[temp].magic_occu);
				char* xhh = (char*)xh.data();
				char* m = (char*)p->yl.ka[temp].ms.data();
				outtextxy(1310, 50, xhh);
				outtextxy(830, 90, m);
				
			}
		}
		if (p->fs.ka.size() != 0 && m.x >= 700 && m.x <= 1440 && m.y >= 170 && m.y <= 370) {
			int temp = (m.x - 700) / 30;
			if (temp < p->fs.ka.size()) {
				putimage(700 + temp * 30, 120, &p->fs.ka[temp].kamian);
				xh = to_string(p->fs.ka[temp].magic_cost);
				char *xhh = (char*)xh.data();
				outtextxy(1310, 50, xhh);
			}
		}

		if (flag.zt == 1 && mou.mouse_zt != 4)//遇到标志的状态为1，意味着鼠标指着某棋子，这时要显示他们的移动距离,由于disp_jl引发错误，先加个mou.mouse_zt!=4
		{
			disp_jl(flag.wg->qizi->x, flag.wg->qizi->y, chess_board, flag.wg->qizi->mj, width, heigh);
		}
		else if (flag.zt == 2) {
			disp_al(flag.wg->qizi->x, flag.wg->qizi->y, chess_board, flag.wg->qizi->aj, width, heigh);
		}
		else if (flag.zt == 3) {
			disp_fs(flag.i, flag.j, chess_board, mou.dq_fska->range_w, mou.dq_fska->range_h, width, heigh);
		}
		else if (flag.zt == 0)
		{
			for (i = 0; i < heigh; i++)
				for (j = 0; j < width; j++)
				{
					chess_board[j][i].hj = 0;
				}
		}
		else if (flag.zt == 10) {
			break;
		}
		//某棋子能影响全体的被动触发器
		for (int i = 0; i < p->dq_count; i++) {
			((void(*)(player*, Flag*, chess*, map_wg**, int))(p->dq_chess[i].bd))(p, &flag, &p->dq_chess[i],chess_board, 1);//Flag *f,chess* from,int ms
		}
		//下一回合
		char input;
		if (_kbhit())
		{
			input = _getch();
			if (input == 'n')
			{
				mou.mouse_zt = 1;
				p->dq_magc = p->max_magc;
				round++;// 回合数增加
				for (int i = 0; i < p->dq_count; i++) {

					int j = 0;
					while (j < p->dq_chess[i].buff.size()) {
						p->dq_chess[i].buff[j].xg(&p->dq_chess[i]);
						if (!p->dq_chess[i].buff[j].tremove(round, &p->dq_chess[i], j)) {
							j++;//只有没触发buff删除后才j++；因为删除时后面的j+1变为j
						}
					}
				}
				swap(dq_player, dq_ddplayer);//敌对玩家与当前玩家交换
				swap(p, dp);
				//更新对手chess的移动状态和攻击状态
				for (int i = 0; i < dp->dq_count; i++) {
					dp->dq_chess[i].hh_move(round);
					dp->dq_chess[i].hh_atk(round);
				}
			}
		}
		//给当前玩家的棋子标记绿色

		//setfillcolor(GREEN);
		//float long_t;
		int zy = p->max_resource;
		for (int i = 0; i < p->dq_count; i++)//卡有多少
		{
			zy -= p->dq_chess[i].magic_occu;
			p->dq_chess[i].elevate();//检测是否升级
			clearrectangle(p->dq_chess[i].xs_x, p->dq_chess[i].xs_y + 46, p->dq_chess[i].xs_x + 50, p->dq_chess[i].xs_y + 50);
			setfillcolor(GREEN);
			fillrectangle(p->dq_chess[i].xs_x, p->dq_chess[i].xs_y + 46, p->dq_chess[i].xs_x + 50, p->dq_chess[i].xs_y + 50);
		}
		p->dq_resource = zy;
		//给当前玩家的棋子标记红色
		//setfillcolor(RED);
		zy = dp->max_resource;
		for (int i = 0; i < dp->dq_count; i++)//
		{
			zy -= dp->dq_chess[i].magic_occu;
			dp->dq_chess[i].elevate();
			clearrectangle(dp->dq_chess[i].xs_x, dp->dq_chess[i].xs_y + 46, dp->dq_chess[i].xs_x + 50, dp->dq_chess[i].xs_y + 50);
			setfillcolor(RED);
			fillrectangle(dp->dq_chess[i].xs_x, dp->dq_chess[i].xs_y + 46, dp->dq_chess[i].xs_x + 50, dp->dq_chess[i].xs_y + 50);
		}
		dp->dq_resource = zy;


		hc1 = to_string(p->dq_resource) + "/" + to_string(p->max_resource);
		char* flzy = (char*)hc1.data();
		outtextxy(1100, 70, flzy);
		bs = to_string(dq_player);
		char* dqwj = (char*)bs.data();
		fl = to_string(p->dq_magc) + "/" + to_string(p->max_magc);
		char* flz = (char*)fl.data();

		outtextxy(900, 50, dqwj);
		outtextxy(930, 70, flz);
		flag.sy_zt = 0;//归0
		flag.qz = NULL;//归空
		FlushBatchDraw();


	}
	EndBatchDraw();





	delete[]chess_board;
	_getch();
	closegraph();
	return 0;
}