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

struct atk_juli//������������
{
	int up = 0;//��
	int down = 0;//��
	int left = 0;//��
	int right = 0;//��
	int left_up = 0;//����
	int right_up = 0;//����
	int left_down = 0;//����
	int right_down = 0;//����

};
struct move_juli//�ƶ���������
{
	int up = 0;//��
	int down = 0;//��
	int left = 0;//��
	int right = 0;//��
	int left_up = 0;//����
	int right_up = 0;//����
	int left_down = 0;//����
	int right_down = 0;//����
};
struct buff;//��ǰ����

struct player;
void get_bjcard(int, int, int, int, player*);
//struct map_wg;
struct chess
{
	int jcno;
	int xs_x;//����x����
	int xs_y;//����y����
	int master;//���ַ�������int����player����
	player* master_1;
	int x;//��������x����
	int y;//��������y����
	int ATK;
	float atk_ts = 0.0;//����������
	int max_HP;
	float mhp_tx = 0.0;//���Ѫ������
	int HP;
	int NP;
	int NP_ts = 0;//NP����
	std::string name;
	int NO;
	int star;
	int job;
	int lv = 1;//�ȼ�
	int zicong = 0;//�Գ�
	float zc_ts = 0.0;//�Գ�����
	bool pd_move;//�ж��Ƿ����ƶ�
	bool pd_atk;//�ж��Ƿ��ܹ���
	float def = 0.0;//�˺�����
	void* bd = NULL;//��������ָ��
	LPCTSTR kamian_lc;//�����ַ,LPCTSTR���ļ����ͣ�����const char �Զ�ת��
	LPCTSTR qimian_lc;//�����ַ
	IMAGE kamian;//�����ͼƬ
	IMAGE qimian;//�����ͼƬ
	chess* zxzj = this;
	bool bd_isornot = false;//�����Ƿ񴥷��ˣ�,Ĭ��Ϊfalse
	int zt = 0;//״̬0Ϊ������״̬Ϊ1Ϊ�޵�״̬
	int magic_occu;//��Դռ��
	int magic_cost;//��������
	string ms;
	vector< buff >buff;
	chess(int a, int mh, int h, int np, std::string s, int n, int p,
		int d, int zc, bool pm, bool pa, int mo, int mc, void* bd, LPCTSTR sl, LPCTSTR ql);//���캯������
	chess() = default;
	atk_juli aj;//��������
	move_juli mj;//�ƶ�����
	int dq_hao;//��ǰ�ĺ�
	int zh_hh = 0;//�ٻ��غ�
	void hh_move(int& round) {
		if (round - zh_hh > 0) {
			this->pd_move = true;
		}
	};//�ж�һ�غϺ��ƶ��ĺ���
	void hh_atk(int& round) {
		if (round - zh_hh > 0) {
			this->pd_atk = true;
		}
	}
	void gj_zc() {//�����Գ䣬������ʱ�Դӻ��NPֵ
		if (this->NP < 100)
			this->NP = this->NP + (int)(zicong*(1+zc_ts));
	}
	void ss_zc() {
		//�����Գ䣬���ܵ��˺�ʱ���Գ�ֵ
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

	name = s;//Ӣ�������
	NO = n;//���
	star = p;
	job = d;
	zicong = zc;
	pd_move = pm;
	pd_atk = pa;

	magic_cost = mc;
	magic_occu = mo;

	bd = b;

	kamian_lc = sl;//�������ϵ�ͼƬ�ĵ�ַ
	qimian_lc = ql;//�������ϵ�ͼƬ�ĵ�ַ

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
struct magic {//������
	int jl;//�ͷž���
	int magic_cost;
	std::string name;
	IMAGE kamian;
	LPCTSTR kamian_lc;//�����ַ
	int xgc = 0;//Ч������
	double sz[5] = { 0,0,0,0,0 };//��ֵ
	int use_object[5] = { 0,0,0,0,0 };//�÷���ʹ�õĶ���,0�����޶���1�����ҷ���2����Է�,3�����ҷ���ɫ��4����з���ɫ,5�������˫��
	bool is_all = false;//�Ƿ��ܶ�Ӣ��ʹ��
	bool is_click[5] = { false,false,false,false,false };
	int range_h;
	int range_w;
	void* skill[5];
	int dq_sf = 0;//��¼��ǰ�ͷŵڼ���Ч��
	map_wg* mb[5];
	magic() = default;
	magic(int j, int mc, std::string n, int xc, double* s, int* uo, bool ia, int rh, int rw, void** sk, bool* ic, LPCTSTR kamian_lc);
};
magic::magic(int j, int mc, std::string n, int xc, double* s, int* uo, bool ia, int rh, int rw, void** sk, bool* ic, LPCTSTR kamian_lc) {//�����ƵĹ��캯��
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
struct kacao//����
{
	int max_c = 4;//���������
	//unsigned int count = 0;//��¼����
	int sb_zq = -1;//��ǰ���ץȡ����
	std::vector<chess> ka;
	int count() {
		return this->ka.size();
	}
};
struct magic_kacao {//�����ƿ���
	int max_c = 8;
	std::vector<magic> ka;
	int count() {
		return this->ka.size();
	}


};
struct gz_buff;
struct map_wg//�����ϵ��������Է�������
{
	bool pd = true;//�ж��Ƿ�Ϊ��,trueΪ�ɷ���״̬��falseΪ���ɷ���״̬
	chess* qizi = NULL;//����
	int hj = 0;//����
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
struct mouse//��¼���ĸ���״̬
{
	int mouse_zt = 1;//��Ĭ��Ϊ1,1��Ϊ�գ�3Ϊ��ץȡ����,2Ϊ����ڳ�������
	int dq_hao = -1;//��ǰ���ץס��Ƭ�����,-1Ϊû�п�Ƭ(����Ӣ�鿨��)
	int dq_fshao = -1;//���ڷ������ϣ���¼���
	chess* dq_ka = NULL;//��ǰ���ץȡ�Ŀ���
	magic* dq_fska = NULL;//��ǰ�ķ�����
	map_wg* gz = NULL;//��״̬2�£���¼�ƶ�ǰ�����������ϵĸ���
};

struct Flag
{
	int i = -1;
	int j = -1;
	map_wg* wg = NULL;
	int zt = 0;//״̬
	int sy_zt = 0;//ʹ��״̬
	chess* qz = NULL;
};


struct cardstrone {//�ƿ�
	int lx;//1Ϊ�����ƣ�2Ϊ������
	vector<chess> ck;
	vector<magic> mk;
	vector<magic> bj;//������
	int  chesscard_size() {
		return ck.size();
	}
	int magiccard_size() {
		return mk.size();
	}

};
struct player
{
	int pl;//����1Ϊ�����һ��λ�������·�������2Ϊ��Ҷ���Ϊ�����Ϸ�
	int NO;
	string name;
	int tx_x;//ͷ��λ��x����
	int tx_y;//ͷ��λ��y����
	int tx_zx_x;//ͷ�������x����
	int tx_zx_y;//ͷ�������y����
	int tx_wz;//��¼�洢ͷ��ͼƬ������±꣬�Ȳ�������ô��������
	int HP = 10000;
	int max_hp = 10000;
	int max_magc;
	int dq_magc;
	int max_resource;//�������Դ��������
	int dq_resource;//��ǰ������Դ
	int fs_jlts = 0;//�����˺�����
	float fs_shts = 0.0;//�����˺�����
	int zt = 0;//״̬
	cardstrone paiku;//�ƿ�
	chess* dq_chess = new chess[99];//��ǰ�������ϵ�����
	map_wg* (*dq_gz) = new map_wg * [99];//��¼��Ӧ�±��������ڵĸ���
	//map_wg* dq_gz[99];
	int dq_count = 0;
	void chess_push(chess n, map_wg* m) {
		if (dq_count < 100) {
			dq_chess[dq_count] = n;
			dq_gz[dq_count] = m;//ԭ��д��n.dq
			dq_chess[dq_count].dq_hao = dq_count;//n.dq_hao��¼��������ĸ�λ��,ԭ��д��n.dq_hao=dq_count���bug���˺ܾ�
			dq_count++;//�������µĸ���
		}
	}

	kacao yl;//����ҵĿ���
	magic_kacao fs;//��������
	bool be_atk = false;//�ж��Ƿ񱻹���
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
//buff����
struct buff {
	float sz;
	int round;//���õĻغ�
	int time;//�����Ļغ�
	bool sf = false;//�ж��Ƿ񷢶���
	int lx = 0;

	void xg(chess* d) {
		//����1������������������2ΪHPÿ�غ����ӵ�Ч��������3ΪNPÿ�غ����ӡ�����4Ϊ�Գ�����
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
	int round;//���õĻغ�
	int time;//�����Ļغ�
	bool sf = false;//�ж��Ƿ񷢶���
	int lx = 0;//����1Ϊ����������������2Ϊ�ָ�HP������3Ϊ�ָ�NP������4Ϊ�Գ�
	bool py;//�Ƿ�Ϊƾ�����͸���buff,trueΪƾ��
	chess* pyqz=NULL;//ƾ������
	int ly;
	int master = 0;
	//int fw;

	void xg(map_wg *gz) {
		//����1������������������2ΪHPÿ�غ����ӵ�Ч��������3ΪNPÿ�غ����ӡ�����4Ϊ�Գ�����,����5Ϊ��������
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
		if (!py&&r == this->round + this->time) {//��roundΪgz_buff��
			this->remove(gz);
			gz->buff.erase(gz->buff.begin() + w);
			return true;
		}
		else if (py&&pyqz != NULL && ((abs(x - pyqz->x) > time) || (abs(y - pyqz->y) > time))) {//ƾ��buff��timeΪ��Χ
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
gz_buff::gz_buff(float s, int t, int r, int l, bool fd,bool p,chess* q,int ma) {//��Ϊƾ��buffʱ��tΪfw���β�
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


void bd0(player* p, Flag* f, chess* from,map_wg**gz, int ms) {//�ձ�������û����
	return;
}
void bd1(player* p, Flag* f, chess* from, map_wg** gz, int ms) {//msΪģʽ��=1ʱΪ��ӱ�����=2ʱΪȥ������=3Ϊ��ģʽ

	if (from->bd_isornot == false && ms == 1) {//falseʱ��û��������
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
	//�������if����ǰ�ͷ��ں��кܴ���
	if (f->sy_zt == 1 && f->qz != NULL) {//�����������ʱ����
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
void disp_jl(int x, int y, map_wg** cb, move_juli& jl, int map_jx_x, int map_jx_y)//��ʾ����
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
void disp_al(int& x, int& y, map_wg** cb, atk_juli& jl, int map_jx_x, int map_jx_y)//��ʾ��������
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
void zhandou(chess* h1, chess* h2,map_wg*gz1,map_wg*gz2) {//ս��
	//h2->HP = h2->HP - ( (int)( h1->ATK + (int)(h1->ATK * h1->atk_ts) + (int)(h1->ATK * gz1->atk_ts(h1->master)) )*(1 - gz2->def_ts(h2->master)) );
	h2->HP = h2->HP - (int)((h1->ATK * (1 + h1->atk_ts + gz1->atk_ts(h1->master))) * (1 - gz2->def_ts(h2->master)));
	h1->NP += (int)(h1->zicong * (1 + h1->zc_ts + gz1->zc_ts(h1->master)) * 1.5);
	//h1->gj_zc(gz1);
	if (h1->job == 1 && h2->HP > 0) {//ְ��Ϊ1
		//h2->ss_zc(gz2);
		h2->NP += (int)(h2->zicong * (1 + h2->zc_ts + gz2->zc_ts(h2->master)));
		h1->HP = h1->HP - (int)((h2->ATK * (1 + h2->atk_ts + gz2->atk_ts(h2->master))) * (1 - gz1->def_ts(h1->master)));
	}
	h1->pd_atk = false;
}
void zhandou(chess* h1, player* h2,map_wg *gz) {//ս����������
	h2->HP = h2->HP - (int)(h1->ATK * (1 + h1->atk_ts +gz->atk_ts(h1->master)));
	h1->NP += (int)(h1->zicong * (1 + h1->zc_ts + gz->zc_ts(h1->master)) * 1.5);
	//h1->gj_zc(gz);
	h1->pd_atk = false;
}


void death(player* p, player* dp, Flag* f, map_wg** cb) {//�����ж�
	for (int i = 0; i < p->dq_count; i++) {
		if (p->dq_chess[i].HP <= 0 && i != p->dq_count - 1) {
			((void(*)(player*, Flag*, chess*, int))p->dq_chess[i].bd)(p, f, &p->dq_chess[i], 2);//ɾ������
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
			((void(*)(player*, Flag*, chess*, int))p->dq_chess[i].bd)(p, f, &p->dq_chess[i], 2);//ɾ������
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


//����˺�
void damage(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {//�˺�

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
	if (uob == 2) {//�ж�2Ϊֻ�Եз��˺�
		for (int j = 0; j < range_h; j++) {
			for (int k = 0; k < range_w; k++) {
				if (cb[y + j][x + k].pd == false && cb[y + j][x + k].hj == 4 && cb[y + j][x + k].qizi->master != dq_player&& cb[y + j][x + k].qizi->zt!=1)
					cb[y + j][x + k].qizi->HP -= ((int)sh- (int)(sh*(cb[y + j][x + k].qizi->def)));
			}
		}
	}

}

void all_damage(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {//�Եз�ȫ���˺�
	for (int i = 0; i < dp->dq_count; i++) {
		if(dp->dq_chess[i].zt != 1)
			dp->dq_chess[i].HP -= ((int)sh - (int)(sh * (dp->dq_chess[i].def)));
	}
	dp->HP -= (int)sh;
}
void frozen(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {//����
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
//�õ�������buff
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
	//��ʱsh���ݵڼ�����uob����NO��round���ݶ�����˺���NP-100)
	
	int w = no*lv;
	if (w < p->paiku.bj.size()) {
		magic c = p->paiku.bj[w - 1];
		p->fs.ka.push_back(c);
	}
}
void ym(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	dp->HP = 0;
}
//�õ��޵�buff
void get_wdbuff(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	if (uob == 3) {
		buff b(0, (int)sh, round, 5, true);
		for (int j = 0; j < range_h; j++)
			for (int k = 0; k < range_w; k++) {
				if (cb[y + j][x + k].pd == false && cb[y + j][x + k].hj == 4) {
					if (cb[y + j][x + k].qizi != NULL && cb[y + j][x + k].qizi->master == dq_player) {
						cb[y + j][x + k].qizi->buff.push_back(b);
						cb[y + j][x + k].qizi->buff.back().provid(cb[y + j][x + k].qizi);//����buff
					}

				}
			}
	}
}//
//�õ�HPbuff
void get_hbuff(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	if (uob == 3) {
		buff b(sh, 4, round, 2, true);
		for (int j = 0; j < range_h; j++)
			for (int k = 0; k < range_w; k++) {
				if (cb[y + j][x + k].pd == false && cb[y + j][x + k].hj == 4) {
					if (cb[y + j][x + k].qizi != NULL && cb[y + j][x + k].qizi->master == dq_player) {
						cb[y + j][x + k].qizi->buff.push_back(b);
						cb[y + j][x + k].qizi->buff.back().provid(cb[y + j][x + k].qizi);//����buff
						
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
						cb[y + j][x + k].qizi->buff.back().provid(cb[y + j][x + k].qizi);//����buff
					}
				}
			}
	}
}
//�������ֵ����
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
//��Ⱦ�Է�
void de_fl(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	for (int i = 0; i < dp->fs.ka.size(); i++) {
		dp->fs.ka[i].magic_cost += (int)sh;
	}
}

void get_defgzbuff(double sh, int uob, int x, int y, map_wg** cb, int& range_h, int& range_w, int& dq_player, int round, map_wg** mb, int n, player* p, player* dp) {
	//float s, int t, int r, int l, bool fd,bool p,chess* q
	
	gz_buff b((float)sh, uob, round, 5, true, false,NULL, p->pl);//��ƾ��buff���ɻغϿ���
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



//ȫ�ֱ���
int i, j;
int step = 50;
int kamian_step_h = 300;//����ĸ�
int kamian_step_w = 175;//����Ŀ�
int p_high = 340; int p_width = 600;//���۵ĳ���
int p2_high = 200;//����2�ĸ�
int p2_width = 600;//����2�Ŀ�

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

//player p1(1, "ʿ��", 0, 10000, 10000, 300, 550, 100, 100,pk);//������ɫ1

//player p2(2, "���", 1, 10000, 10000, 300, 50, 100, 100,pk);//������ɫ2


player* p;//����һ��ָ��������͵�ָ�룬�����Ժ��д�غ���ʱ
player* dp;//ͬ�ϣ���¼�ж�p

int player_temp;
int dq_player;//��ǰ���
int dq_ddplayer;//��ǰ�ж����


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
	int jcno = 0;//������ţ�Ψһ
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
	player p1(1, "ʿ��", 0, 10000, 10000, 300, 550, 100, 100, pk);//������ɫ1

	player p2(2, "���", 1, 10000, 10000, 300, 50, 100, 100, pk);//������ɫ2

	IMAGE background;
	loadimage(&background, "D:\\agame\\background.png");
	


	vector<IMAGE> txpt;//ͷ��ͼƬ����
	int round = 1;//�غ�
	p1.pl = 1;//��1,2Ϊͷ�����ڵ�λ��
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



	map_wg** chess_board = new map_wg * [heigh];//�������̵ĸ�������
	for (i = 0; i < heigh; i++)
		chess_board[i] = new map_wg[width];
	/*int a, int mh, int h, int np, std::string s, int n, int p,
		int d, int zc, bool pm, bool pa, int mo, int mc, void* bd, LPCTSTR sl, LPCTSTR ql*/
	chess arthuria(1200, 2000, 2000, 0, "����������", 1, 5, 1, 20, false, false, 80, 20, bd1, _T("D:\\agame\\kamian.png"), _T("D:\\agame\\qimian.png"));//δ��ɣ���Ϊԭ��Ҫ���ص�����
	init_mj(&arthuria, 2, 2, 2, 2, 2, 2, 2, 2);//���ƶ����븳ֵ
	init_aj(&arthuria, 2, 2, 2, 2, 2, 2, 2, 2);//���������븳ֵ
	arthuria.ms = string("�ҷ�ȫ�幥��������20%");
	chess al(1000, 2000, 2000, 0, "����", 2, 5, 2, 10, false, false, 50, 15, bd2, _T("D:\\agame\\ailei.png"), _T("D:\\agame\\aileik.png"));//δ��ɣ���Ϊԭ��Ҫ���ص�����
	init_mj(&al, 3, 3, 2, 2, 2, 2, 2, 2);//���ƶ����븳ֵ
	init_aj(&al, 4, 4, 2, 2, 2, 2, 2, 2);//���������븳ֵ
	al.ms = string("ڤ��ӻ�����Χ���ѷ���ӻ�ù������ӳ�");
	chess arthur(1200, 2000, 2000, 0, "��ɪ", 1, 5, 1, 20, false, false, 80, 40, bd3, _T("D:\\agame\\ark.png"), _T("D:\\agame\\arq.png"));//δ��ɣ���Ϊԭ��Ҫ���ص�����
	init_mj(&arthur, 2, 2, 2, 2, 2, 2, 2, 2);//���ƶ����븳ֵ
	init_aj(&arthur, 2, 2, 2, 2, 2, 2, 2, 2);//���������븳ֵ
	arthur.ms = string("�������֣�������ս���������ҷ�����ɪ�ڳ�ʱ����������5��");
	chess eliya(800, 1500, 1500, 0, "������", 3, 5, 1, 20, false, false, 50, 20, bd4, _T("D:\\agame\\eliyak.png"), _T("D:\\agame\\eliyaq.png"));//δ��ɣ���Ϊԭ��Ҫ���ص�����
	init_mj(&eliya, 5, 5, 1, 1, 2, 2, 2, 2);//���ƶ����븳ֵ
	init_aj(&eliya, 5, 5, 1, 1, 1, 1, 1, 1);//���������븳ֵ
	eliya.ms = string("����ħ����ÿ����ʹ��һ�ŷ������������һ���㷨���Ƶ�����������");


	double sz[5] = { 2000 };
	int uo[5] = { 2 };
	bool ia = true;
	void* sk[5] = { damage };
	bool ic[5] = { true };
	magic f1(12, 40, "������", 1, sz, uo, ia, 2, 2, sk, ic, "D:\\agame\\fs.png");
	double sz1[5] = { 1 };
	int uo1[5] = { 5 };
	bool ia1 = false;
	void* sk1[5] = { frozen };
	bool ic1[5] = { true };
	magic f2(12, 20, "��ѩ�籩", 1, sz1, uo1, ia1, 2, 4, sk1, ic1, "D:\\agame\\fs1.png");
	double sz2[5] = { 0,0,0 };
	int uo2[5] = { 5 ,5,5};
	bool ia2 = false;
	void* sk2[5] = { get_che,get_che,swap_che };
	bool ic2[5] = { true, true,false };
	magic f3(12, 50, "�û���", 3, sz2, uo2, ia2, 1, 1, sk2, ic2, "D:\\agame\\fs2.png");
	double sz3[5] = { 0.5 };
	int uo3[5] = { 3 };
	bool ia3 = false;
	void* sk3[5] = { get_abuff };
	bool ic3[5] = { true };
	magic f4(12, 50, "�������", 1, sz3, uo3, ia3, 4, 4, sk3, ic3, "D:\\agame\\fs3.png");
	double sz4[5] = { 0 ,0,0};
	int uo4[5] = { 3,6,3 };
	bool ia4 = false;
	void* sk4[5] = { get_che,get_che,sjyd };
	bool ic4[5] = { true,true,false };
	magic f5(10, 10, "˲���ƶ�", 3, sz4, uo4, ia4, 1, 1, sk4, ic4, "D:\\agame\\fs4.png");
	double sz5[5] = { 0 };
	int uo5[5] = { 3};
	bool ia5 = false;
	void* sk5[5] = {get_wdbuff };
	bool ic5[5] = { true };
	magic f6(8, 20, "ħ������", 1, sz5, uo5, ia5, 1, 1, sk5, ic5, "D:\\agame\\fs5.png");
	double sz6[5] = { 1000,80 };
	int uo6[5] = { 3,3 };
	bool ia6 = false;
	void* sk6[5] = { get_hbuff,get_nbuff };
	bool ic6[5] = { true,false };
	magic f7(6, 70, "δȻ��Ȼ��������", 2, sz6, uo6, ia6, 6, 6, sk6,ic6, "D:\\agame\\fs6.png");
	double sz7[5] = { 10 };
	int uo7[5] = { 3};
	bool ia7 = false;
	void* sk7[5] = { de_fl };
	bool ic7[5] = { true };
	magic f8(12, 50, "������Ⱦ", 1, sz7, uo7, ia7, 1, 1, sk7, ic7, "D:\\agame\\fs7.png");
	double sz8[5] = { 1000 };
	int uo8[5] = { 3 };
	bool ia8 = false;
	void* sk8[5] = { grow_maxHP };
	bool ic8[5] = { true };
	magic f9(8, 40, "����֮��", 1, sz8, uo8, ia8, 2, 6, sk8, ic8, "D:\\agame\\fs8.png");
	double sz9[5] = { 0.5 };
	int uo9[5] = { 3 };//�غ���
	bool ia9 = false;
	void* sk9[5] = { get_defgzbuff };
	bool ic9[5] = { true };
	magic f10(7, 50, "�û����", 1, sz9, uo9, ia9, 4, 5, sk9, ic9, "D:\\agame\\fs9.png");





	//���1
	arthuria.master = p1.pl;
	arthuria.master_1 = &p1;
	al.master = p1.pl;
	al.master_1 = &p1;
	arthur.master = p1.pl;
	arthur.master_1 = &p1;
	eliya.master = p1.pl;
	eliya.master_1 = &p1;
	p1.yl.ka.push_back(arthuria);//�൱�ڳ鿨��ȥ
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
	//���2
	arthuria.master = p2.pl;
	arthuria.master_1 = &p2;
	p2.yl.ka.push_back(arthuria);//�൱�ڳ鿨��ȥ
	p2.yl.ka.push_back(arthuria);
	p2.fs.ka.push_back(f1);
	p2.fs.ka.push_back(f1);
	p2.fs.ka.push_back(f2);
	//p2.yl.count = 2;


	int board_x = -1;//�ǵ����ó�ʼ��
	int board_y = -1;
	mouse mou;//�������״̬
	MOUSEMSG m;//���������Ϣ
	auto m_old_x = -1;//���������
	auto m_old_y = -1;
	IMAGE kamian;//��ǰ����ͼƬ
	int ka_x; int ka_y;//������ʼλ��
	//loadimage(&kamian, _T("D:\\kamian.png"));//300,175;
	int wg_x, wg_y;//���Դ�����������Ͻ�����
	Flag flag;//��־����־1Ϊ����״̬
	startup();

	//��������
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
		//��ӡͷ��
		//clearrectangle(720, 50, 1400, 90);
		putimage(p->tx_x, p->tx_y, &txpt[p->tx_wz]);
		putimage(dp->tx_x, dp->tx_y, &txpt[dp->tx_wz]);
		outtextxy(690, 50, "ATK:");
		outtextxy(690, 70, "HP:");
		outtextxy(690, 90, "NP:");
		outtextxy(800, 90, "����:");
		outtextxy(800, 70, "��ǰ�غϷ���ֵ:");
		outtextxy(1000, 70, "��ǰ��������:");
		outtextxy(1000, 50, "��������:");
		outtextxy(800, 50, "��ǰ�غ����Ϊ:");
		outtextxy(1100, 50, "�ÿ��Ʒ������ĺͷ�����Դռ��:");
		for (i = 0; i < heigh; i++)//�������
			for (j = 0; j < width; j++)
			{
				if (chessboard[j][i] == 1)
				{
					if (j == board_y && i == board_x)//board_y��board_x�������µ�����
					{
						setfillcolor(YELLOW);
						if (mou.mouse_zt == 3 && m.uMsg == WM_LBUTTONDOWN && chess_board[j][i].pd == true)//����������
						{
							//p->dq_magc -= mou.dq_ka->magic_cost;
							p->chess_push(*(mou.dq_ka), &chess_board[j][i]);
							chess_board[j][i].qizi = &p->dq_chess[p->dq_count - 1];
							chess_board[j][i].pd = false;//�������������ӣ���Ϊ���ɷ���״̬
							chess_board[j][i].qizi->x = i;
							chess_board[j][i].qizi->y = j;
							chess_board[j][i].qizi->xs_x = (i + 1) * step;
							chess_board[j][i].qizi->xs_y = (j + 1) * step;
							chess_board[j][i].qizi->jcno = jcno;
							jcno++;

							flag.qz = chess_board[j][i].qizi;
							flag.sy_zt = 1;//ʹ��״̬��Ϊ1
							p->yl.ka.erase(p->yl.ka.begin() + mou.dq_hao);//�ӿ����п��Ƶ�����ɾ��
							//�������״̬�ָ�
							mou.dq_hao = -1;
							mou.dq_ka = NULL;
							mou.mouse_zt = 1;
							//������Ŀ���
							clearrectangle(m.x, m.y, m.x + 175, m.y + 300);
						}
						else if (mou.mouse_zt == 2 && m.uMsg == WM_LBUTTONDOWN)//�ƶ�����
						{
							if (chess_board[j][i].hj == 2 && (chess_board[j][i].pd == true))//����ʾ��ɫ�ģ�������ƶ�
							{
								//outtextxy(720, 300, _T("�ƶ��ɹ�"));
								chess_board[j][i].qizi = mou.dq_ka;
								chess_board[j][i].qizi->x = board_x;
								chess_board[j][i].qizi->y = board_y;
								chess_board[j][i].qizi->xs_x = (i + 1) * step;
								chess_board[j][i].qizi->xs_y = (j + 1) * step;
								p->dq_gz[mou.dq_ka->dq_hao] = &chess_board[j][i];//���¶�Ӧ����ĸ�������
								chess_board[j][i].pd = false;//��������������,��Ϊ���ɷ���״̬
								chess_board[j][i].qizi->pd_move = false;
								mou.gz->pd = true;//��ԭ���������ڵ������Ϊ�ɷ���״̬
								mou.gz->qizi = NULL;/*ʹ�����������������Ϊ���ƶ�����ʱԭ���ĸ��ӵ�����ָ���գ�����Ϊ��elseifԭ���Ѿ�ִ����һ����֧��
													�����������ڲ�ͬλ�ú��ִ��flag=0�ķ�֧���ų��ˣ���������flag=1ʱ�����еĺ�����ȴ����flag�����ԭ����
													�ӵ�����ָ�뱻����ˣ������˴��󣬸��ֶ����flag=0��*/
								flag.zt = 0;
								flag.sy_zt = 1;//��ζ�ŷ���������
								//�����״̬�ָ�Ϊ1
								mou.dq_hao = -1;
								mou.dq_ka = NULL;
								mou.mouse_zt = 1;
							}
							else if (chess_board[j][i].hj == 2 && ((chess_board[j][i].qizi) == mou.dq_ka))//ԭ���ƶ�
							{

								//�����״̬�ָ�Ϊ1
								mou.dq_hao = -1;
								mou.dq_ka = NULL;
								mou.mouse_zt = 1;
							}
						}
						//����Ϊ����ʱ
						else if (chess_board[j][i].pd == false && m.uMsg == WM_LBUTTONDOWN && chess_board[j][i].qizi->master == dq_player && chess_board[j][i].qizi->pd_move == false && chess_board[j][i].qizi->pd_atk == true) {
							mou.mouse_zt = 4;//���ģʽ4Ϊ����״̬
							mou.dq_ka = chess_board[j][i].qizi;
							flag.zt = 2;//flag״̬2��������״̬��Ҫ��ʾ������Χ
							flag.wg = &chess_board[j][i];
							flag.i = i;
							flag.j = j;
							flag.sy_zt = 2;//��ζ�Ž��й���
						}
						else if (mou.mouse_zt == 4 && m.uMsg == WM_LBUTTONDOWN && chess_board[j][i].hj == 3 && chess_board[j][i].pd == false && chess_board[j][i].qizi->master == dq_ddplayer) {
							zhandou(mou.dq_ka, chess_board[j][i].qizi,flag.wg,&chess_board[j][i]);
							//outtextxy(800, 300, "!!!!");
							//�����ԭ��
							mou.dq_ka = NULL;
							mou.mouse_zt = 1;
							//flag���ԭ��
							flag.zt = 0;
							flag.wg = NULL;
						}

						else if (chess_board[j][i].pd == false && m.uMsg == WM_LBUTTONDOWN && chess_board[j][i].qizi->master == dq_player && chess_board[j][i].qizi->pd_move == true)
						{
							mou.mouse_zt = 2;
							mou.dq_ka = chess_board[j][i].qizi;//ץȡ�������ϵ�����
							mou.dq_hao = -1;
							mou.gz = &chess_board[j][i];//�洢ԭ����ָ��
						}
						else if (chess_board[j][i].pd == false && mou.mouse_zt == 1)//������Ƶ������ӵĸ���ʱ&& mou.mouse_zt != 4&&
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
								disp_fs(i, j, chess_board, mou.dq_fska->range_w, mou.dq_fska->range_h, width, heigh);//��ʾ�����ķ�Χ
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
								p->fs.ka.erase(p->fs.ka.begin() + mou.dq_fshao);//�ӷ��������п��Ƶ�����ɾ��
								mou.mouse_zt = 1;//�����Ѿ��ͷŷ���
								mou.dq_fska = NULL;
								mou.dq_fshao = -1;
								flag.sy_zt = 3;//��ζʹ���˷���
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
					if (chess_board[j][i].pd == false) {//��������Ϊ���ɷ���״̬����Ϊ������
						putimage(wg_x, wg_y, &chess_board[j][i].qizi->qimian);
					}
					if (chess_board[j][i].pd == false && chess_board[j][i].hj == 3 && chess_board[j][i].qizi->master == dq_ddplayer)//���Ӹ�����ͼ��
						putimage(chess_board[j][i].qizi->xs_x + 13, chess_board[j][i].qizi->xs_y + 13, &atk_tb);

				}
				//�Ը����ϵ�buff�����ͷ�
				/*int k = 0;
				while (k < chess_board[j][i].buff.size()) {
					//chess_board[j][i].buff[k].ly = chess_board[j][i].buff[k].pyqz->dq_hao;
					chess_board[j][i].buff[k].xg(&chess_board[j][i]);
					if (!chess_board[j][i].buff[k].tremove(round, &chess_board[j][i], k,i,j)) {//int r, map_wg* gz, int w,int x,int y
						k++;//ֻ��û����buffɾ�����j++����Ϊɾ��ʱ�����j+1��Ϊj
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
							disp_fs(i, j, chess_board, mou.dq_fska->range_w, mou.dq_fska->range_h, width, heigh);//��ʾ�����ķ�Χ
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
							p->fs.ka.erase(p->fs.ka.begin() + mou.dq_fshao);//�ӷ��������п��Ƶ�����ɾ��
							mou.mouse_zt = 1;//�����Ѿ��ͷŷ���
							mou.dq_fska = NULL;
							mou.dq_fshao = -1;
							flag.sy_zt = 3;//��ζʹ���˷���
						}

					}
				}



			}
			//֮���ԷŽ����棬��Ϊ
		for (int i = 0; i < heigh; i++) {
			for (int j = 0; j < width; j++) {
				int k = 0;
				while (k < chess_board[j][i].buff.size()) {
						//chess_board[j][i].buff[k].ly = chess_board[j][i].buff[k].pyqz->dq_hao;
					chess_board[j][i].buff[k].xg(&chess_board[j][i]);
					if (!chess_board[j][i].buff[k].tremove(round, &chess_board[j][i], k, i, j)) {//int r, map_wg* gz, int w,int x,int y
						k++;//ֻ��û����buffɾ�����j++����Ϊɾ��ʱ�����j+1��Ϊj
					}
				}
			}
		}
		//death(p, dp);
		line(13 * step + 20, 0, 13 * step + 20, 720);
		//fillrectangle(680, 370, p_width + 680, p_high + 370);//���۵����Ͻ�����Ϊ(680,370)
		//fillrectangle(680, 120, 680 + p2_width, 170 + p2_high);//����2�����Ͻ�ͼ��Ϊ(680,120),p2_width=600,p2_high=250;
		death(p, dp, &flag,chess_board);
		//���ƿ�
		for (i = 0; i < p->yl.ka.size(); i++)
		{
			if (mou.dq_hao != i)//���ץȡ���ĸ����ĸ��Ͳ���ӡ,ע�⣬i�Ǵ�1��ʼ��
				putimage(700 + i * 30, 400, &p->yl.ka[i].kamian);//x��700��ʼ
		}
		//�������ƿ�
		for (i = 0; i < p->fs.ka.size(); i++) {
			if (mou.dq_fshao != i)
				putimage(700 + i * 30, 120, &p->fs.ka[i].kamian);
		}





		//���ĸ���״̬
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)
		{
			board_x = (m.x / step) - 1;
			board_y = (m.y / step) - 1;

		}

		else if (p->yl.ka.size() != 0 && m.uMsg == WM_LBUTTONDOWN && m.x >= 700 && m.x <= 1440 && m.y >= 400 && m.y <= 700)//(m.x-700)/kamian_step_w&&(m.y-400)/kamian_step_h==)
		{
			int sj_mw = 700 + (p->yl.ka.size() * 30);
			int temp = (m.x - 700) / 30;//��700����Ϊ������700���ص�x�����п�ʼ��ʾ,���е�һ���ƿ϶���730��ʼ��ʾ
			
			if (temp < p->yl.ka.size())
			{
				//string nb = to_string(temp);
				//char* hao = (char*)nb.data();
				//outtextxy(1300, 50, hao);
				char* ms = (char*)p->yl.ka[temp].ms.data();

				if ((p->dq_magc - (p->yl.ka[temp].magic_cost) >= 0) && (p->dq_resource - p->yl.ka[temp].magic_occu >= 0)) {
					mou.mouse_zt = 3;//3���������ץȡ����
					mou.dq_hao = temp;//�õ������еĵڼ���,��1��ʼ
					mou.dq_ka = &p->yl.ka[mou.dq_hao];
				}
				else
					outtextxy(850, 90, "��������");

				//yl.count--;//��������1
			}
			/*else if ((m.x > (sj_mw - 145) && m.x < sj_mw)) {
				mou.mouse_zt = 3;//3���������ץȡ����
				mou.dq_hao = p->yl.ka.size() - 1;
				mou.dq_ka = &p->yl.ka[mou.dq_hao];
			}*/
		}
		else if (p->fs.ka.size() != 0 && m.uMsg == WM_LBUTTONDOWN && m.x >= 700 && m.x <= 1440 && m.y >= 120 && m.y <= 370) {
			int temp = (m.x - 700) / 30;
			if (temp < p->fs.ka.size()) {
				if (p->dq_magc - (p->fs.ka[temp].magic_cost)) {
					mou.mouse_zt = 5;//״̬5Ϊ����ץס������
					mou.dq_fshao = temp;
					mou.dq_fska = &p->fs.ka[mou.dq_fshao];

				}
				else
					outtextxy(850, 90, "��������");
			}
		}
		else if (m.uMsg == WM_RBUTTONDOWN && mou.mouse_zt == 5) {
			mou.mouse_zt = 1;
			mou.dq_fshao = -1;
			mou.dq_fska = NULL;
			flag.zt = 0;
		}
		else if (m.uMsg == WM_RBUTTONDOWN && mou.mouse_zt == 3)//��״̬3����ץס��Ƭʱ��������Ҽ�����������п�Ƭ�Ż�ȥ
		{
			clearrectangle(m.x, m.y, m.x + 175, m.x + 300);
			mou.mouse_zt = 1;
			mou.dq_hao = -1;
			mou.dq_ka = NULL;
			//yl.count++;//��������1
		}
		else if (m.uMsg == WM_RBUTTONDOWN && mou.mouse_zt == 2)//��ζ�������ʱץȡ�������ϵ����ӣ�ͬʱ�������Ҽ�
		{
			mou.mouse_zt = 1;//�����״̬��Ϊ1
			//mou.dq_hao=-1;
			mou.dq_ka = NULL;
		}
		else if (m.uMsg == WM_RBUTTONDOWN && mou.mouse_zt == 4) {//�����״̬Ϊ4�����Ҽ�ʱ,����ȡ��
			mou.dq_ka = NULL;
			mou.mouse_zt = 1;
		}
		else if (m.uMsg == WM_LBUTTONDOWN && mou.mouse_zt == 4 && dp->be_atk == true && (m.x > dp->tx_x && m.x<dp->tx_zx_x && m.y>dp->tx_y && m.y < dp->tx_zx_y)) {//�����з���ɫ�ж�
			zhandou(mou.dq_ka, dp,flag.wg);
			dp->be_atk = false;//����Ϊfalse
			mou.dq_ka = NULL;
			mou.gz = NULL;
			mou.mouse_zt = 1;
			mou.dq_hao = -1;
		}


		if (mou.mouse_zt == 3 && mou.dq_ka != NULL)//���״̬3����ζ���������ץȡ�˿�Ƭ
		{
			if (m_old_x != m.x && m_old_y != m.y)
			{
				clearrectangle(m_old_x, m_old_y, m_old_x + 175, m_old_y + 300);
				m_old_x = m.x;//��¼�ɵ����״̬�����ƶ�ʱ��������Ķ���
				m_old_y = m.y;
			}
			putimage(m.x, m.y, &((*mou.dq_ka).kamian));
		}
		//��������if�������Ż��ȱ��
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

		if (flag.zt == 1 && mou.mouse_zt != 4)//������־��״̬Ϊ1����ζ�����ָ��ĳ���ӣ���ʱҪ��ʾ���ǵ��ƶ�����,����disp_jl���������ȼӸ�mou.mouse_zt!=4
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
		//ĳ������Ӱ��ȫ��ı���������
		for (int i = 0; i < p->dq_count; i++) {
			((void(*)(player*, Flag*, chess*, map_wg**, int))(p->dq_chess[i].bd))(p, &flag, &p->dq_chess[i],chess_board, 1);//Flag *f,chess* from,int ms
		}
		//��һ�غ�
		char input;
		if (_kbhit())
		{
			input = _getch();
			if (input == 'n')
			{
				mou.mouse_zt = 1;
				p->dq_magc = p->max_magc;
				round++;// �غ�������
				for (int i = 0; i < p->dq_count; i++) {

					int j = 0;
					while (j < p->dq_chess[i].buff.size()) {
						p->dq_chess[i].buff[j].xg(&p->dq_chess[i]);
						if (!p->dq_chess[i].buff[j].tremove(round, &p->dq_chess[i], j)) {
							j++;//ֻ��û����buffɾ�����j++����Ϊɾ��ʱ�����j+1��Ϊj
						}
					}
				}
				swap(dq_player, dq_ddplayer);//�ж�����뵱ǰ��ҽ���
				swap(p, dp);
				//���¶���chess���ƶ�״̬�͹���״̬
				for (int i = 0; i < dp->dq_count; i++) {
					dp->dq_chess[i].hh_move(round);
					dp->dq_chess[i].hh_atk(round);
				}
			}
		}
		//����ǰ��ҵ����ӱ����ɫ

		//setfillcolor(GREEN);
		//float long_t;
		int zy = p->max_resource;
		for (int i = 0; i < p->dq_count; i++)//���ж���
		{
			zy -= p->dq_chess[i].magic_occu;
			p->dq_chess[i].elevate();//����Ƿ�����
			clearrectangle(p->dq_chess[i].xs_x, p->dq_chess[i].xs_y + 46, p->dq_chess[i].xs_x + 50, p->dq_chess[i].xs_y + 50);
			setfillcolor(GREEN);
			fillrectangle(p->dq_chess[i].xs_x, p->dq_chess[i].xs_y + 46, p->dq_chess[i].xs_x + 50, p->dq_chess[i].xs_y + 50);
		}
		p->dq_resource = zy;
		//����ǰ��ҵ����ӱ�Ǻ�ɫ
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
		flag.sy_zt = 0;//��0
		flag.qz = NULL;//���
		FlushBatchDraw();


	}
	EndBatchDraw();





	delete[]chess_board;
	_getch();
	closegraph();
	return 0;
}