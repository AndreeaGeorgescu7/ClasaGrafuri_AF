#include <bits/stdc++.h>

using namespace std;

ifstream fin("graf.in");

class Graf{
protected:
    int n,m;
    vector<int> graf[10000];
    vector<int> graf_t[10000];
    vector<int> componente[10000];
    int viz[100001],grad_int[10000];
    stack <int>stiva ;
public:
       static int nrcomp;
       Graf();
      ~Graf(){}
       Graf(int n,int m, vector<int> graf[10000]);
       Graf(const Graf& g);
       void bfs(int nod); ///complexitate:O(n+m)
       void dfs(int s);  ///complexitate:O(n+m)
       int conex();      ///complexitate:O(n+m)
       void init();
       virtual void adauga_muchii(int x,int y)=0;
       friend ostream& operator<<(ostream& out,const  Graf& g);
       virtual ostream& AfisareVirtuala(ostream& out)const;
       friend ifstream& operator>> (ifstream& fin, Graf & g);
       virtual ifstream& CitireVirtuala (ifstream& fin);


};
int Graf::nrcomp=0;

Graf::Graf()
{
    this->n=0;
    this->m=0;


}
Graf:: Graf(int n,int m, vector<int> graf[10000])
     {
    this->n=n;
    this->m=m;
    for(int i=1;i<=n;i++)
      for(vector<int>::iterator it1=graf[i].begin(); it1!=graf[i].end(); ++it1)
        {
            this->graf[i].push_back(*it1);
            this->graf_t[*it1].push_back(i);
            grad_int[*it1]++;
        }



     }
Graf:: Graf(const Graf &g)
 {
   this->n=g.n;
   this->m=g.m;
   for(int i=1;i<=n;i++)
     for(vector<int>::const_iterator it1=g.graf[i].begin(); it1!=g.graf[i].end(); ++it1)
      this->graf[i].push_back(*it1);

}
void Graf::init()
{
    for(int i=1;i<=n;i++)
        viz[i]=0;
}

ostream& Graf::AfisareVirtuala(ostream& out) const{

for(int i=1;i<=n;i++)
 {
   out << i << ": ";
   for(vector<int>::const_iterator it1=graf[i].begin(); it1!=graf[i].end(); ++it1)out<<*it1 <<" ";
   out<<"\n";

}
    return out;
}
 ostream& operator<<(ostream & out,const Graf& g)
{
    return g.AfisareVirtuala(out);
}

ifstream& operator>>(ifstream & fin,Graf & g)
{
    return g.CitireVirtuala(fin);
}

ifstream& Graf::CitireVirtuala(ifstream& fin){
int x,y;

    fin>>this->n;
    fin>>this->m;
    for(int i=0;i<this->m;i++)
    {
        fin>>x>>y;
    //g.graf.adauga_muchii(x,y);
    }

    return fin;
}
void Graf:: bfs(int nod)
{queue<int> coada;
 bool visited[n];
 vector <int> distanta;
for(int i = 0; i <=n; i++)
        {
        visited[i] = 0;
        distanta.push_back(-1);
        }
///marcam ca vizitat nodul de plecare
visited[nod] = 1;
distanta[nod] = 0;
coada.push(nod);

 while(!coada.empty())
    {
       int s = coada.front();

      ///luam pe rand toate elementele la care se poate ajunge din s si le adaugam in coada
        vector<int>::iterator it;
        for ( it = graf[s].begin(); it != graf[s].end(); ++it)
        {
            if (!visited[*it])
            {
                distanta[*it] = distanta[s] + 1; ///distanta va fi egala cu distanta tatalui +1
                visited[*it] = 1;
                coada.push(*it);
            }


        }
            coada.pop(); ///eliminam din coada nodul curent
    }

    int m=distanta.size();
    for(int i=1;i<m;i++)
        cout<<distanta[i]<<" ";

}

void Graf:: dfs(int s)
{
  viz[s]=1;
  //cout<<s<<" ";
 vector<int>::iterator it;
    for ( it = graf[s].begin(); it != graf[s].end(); ++it)
       if (!viz[*it]) dfs(*it);

///ne trebuie la ctc deoarece trebuie sa pornim in ordinea inversa a aparitiei in parcurgere
  stiva.push(s);
}

int Graf:: conex( )
{ int i;
  for(i=1;i<=n;i++)
    if (viz[i]==0) { nrcomp++; dfs(i);}

    return nrcomp;

}

class GrafOrientat:public Graf
{
public:
    ~GrafOrientat(){}
    GrafOrientat(int n,int m, vector<int> graf[10000]):Graf(n, m,graf){}
    GrafOrientat():Graf(){}
    GrafOrientat(const GrafOrientat& g):Graf(g){};
    virtual ostream& AfisareVirtuala(ostream& out)const;
    virtual ifstream& CitireVirtuala (ifstream& fin);
    void adauga_muchii(int x,int y);
    void dfst(int s);
    void sortare_top();  ///complexitate:O(n+m)
    void ctc();          ///complexitate:O(n+m)


};
ostream& GrafOrientat::AfisareVirtuala(ostream& out) const{

    Graf::AfisareVirtuala(out);
    return out;

}
ifstream& GrafOrientat::CitireVirtuala(ifstream& fin){

    Graf::CitireVirtuala(fin);
    return fin;

}
void GrafOrientat ::adauga_muchii(int x,int y)
{
if(x==0&&y==0)
  cin>>x>>y;

graf[x].push_back(y);
 m++;

if(x>n)
   n++;
else
    if(y>n)
      n++;

}
///dfs pe graful transpus
void GrafOrientat::dfst(int s)
{viz[s] = 2; ///marcam ca vizitat si in transpusa

///adaugam nodul la componenta curenta
componente[nrcomp].push_back(s);

 vector<int>::iterator it;
      for ( it = graf_t[s].begin(); it != graf_t[s].end(); ++it)
       if (viz[*it]==1)  ///cautam prin vecinii din transpusa si daca au mai fost vizitati pornim un dfst din ei
           dfst(*it);

}
void GrafOrientat::ctc()
{int nod;
nrcomp=0;
    for(int i=1;i<=n;i++)
        if(!viz[i])
           dfs(i);
    /*for(int i=1;i<=n;i++)
            {int x=stiva.top();
             cout<<x<<" ";
               stiva.pop();}*/

    while(!stiva.empty())
        {
        nod = stiva.top();
       // cout << nod << " ";
        if (viz[nod] == 1)
        {///daca nodul a fost vizitat o singura data si nu de 2 ori inseamna ca am mai gasit o CTC
            nrcomp++;
            dfst(nod);
        }
        stiva.pop();
    }
    cout<<nrcomp<<"\n";
    for (int i=1;i<=nrcomp;i++)
   {
   for(vector<int>::iterator it1= componente[i].begin(); it1!= componente[i].end(); ++it1)cout<<*it1 <<" ";
   cout<<"\n";}

}
void GrafOrientat::sortare_top()
{int sortat[10000]={0};
  int i, x,poz=0; vector<int>::iterator it;

    for(i = 1; i <= n; i++)
       if(grad_int[i] == 0) ///va exista cel putin un nod cu grad_int=0 deoarece graful trebuie sa fie aciclic
          sortat[++poz] = i;

///luam pe rand elementele ulterior adaugate in vectorul "sortat"
    for(i = 1; i <= n; i++)
        {
            x = sortat[i];
            for(it = graf[x].begin(); it != graf[x].end(); ++it)
            {
                grad_int[*it]--; ///deoarece "eliminam" nodul tata acestora le scade grad_int
                if(grad_int[*it] == 0)  ///daca este egal cu 0 nu depinde de nimeni deci poate fi adaugat in vector
                    sortat[++poz] = *it;
            }
        }
    for(i=1;i<=n;i++)
        cout<<sortat[i]<<" ";


}

class GrafNeorientat:public Graf
{private:
    int time = 1;
    vector<vector<int>> solutie;
    vector <int> time_stamp;
    vector <int> current_time_stamp;
public:
    GrafNeorientat():Graf(){}
    ~GrafNeorientat(){}
    GrafNeorientat(int n,int m, vector<int> graf[10000]):Graf(n, m,graf){}
    GrafNeorientat(const GrafNeorientat& g):Graf(g){}
    virtual ifstream& CitireVirtuala (ifstream& fin);
    virtual ostream& AfisareVirtuala(ostream& out)const;
    void adauga_muchii(int x,int y);
     vector<vector<int>>  criticalConnections(int n,  vector<int> graf[10000]);
     void dfs_crt(int nod, int prev);
};
ostream& GrafNeorientat::AfisareVirtuala(ostream& out) const{

     Graf::AfisareVirtuala(out);
    return out;


}
ifstream& GrafNeorientat::CitireVirtuala(ifstream& fin){

    Graf::CitireVirtuala(fin);

    return fin;


}

void GrafNeorientat::adauga_muchii(int x,int y)
{if(x==0&&y==0)
cin>>x>>y;

       graf[x].push_back(y);
        graf[y].push_back(x);
        m++;
        if(x>n)
            n++;
        else if(y>n)
            n++;

}
vector<vector<int>>  GrafNeorientat::criticalConnections(int n,vector<int> graf[10000])
{///avem nevoie de astea pentru ca nu avem copy constructor
///sunt puse invers
time_stamp = vector<int>(n);   ///1 2 3 4
current_time_stamp = vector<int>(n); ///1 1 1 4

int ok=0,x=0;
 vector<int>::iterator it;

for(int i=1;i<=n&&ok==0;i++)
    for ( it = graf[i].begin(); it != graf[i].end()&&ok==0; ++it)
        {
        x=*it;
        ok=1;
        //cout<<x<<endl;
        }

dfs_crt(x, -1);
/*cout<<"\n";
for(int i=1;i<=n;i++)
    cout<<time_stamp[i]<<" ";
cout<<"\n";
for(int i=1;i<=n;i++)
    cout<<current_time_stamp[i]<<" ";
*/
return solutie;
}

void GrafNeorientat::dfs_crt(int nod, int prev)
{time_stamp[nod] = current_time_stamp[nod] = time;
///daca nu exista muchii critice, timpii de final sunt interschimbabili (graful contine un ciclu)
time++;///timpul de final

    for (auto vecin: graf[nod])
            {if (time_stamp[vecin] == 0) ///daca e 0 nodul nu a fost vizitat inca
             {
                dfs_crt(vecin, nod);
                current_time_stamp[nod] = min(current_time_stamp[nod], current_time_stamp[vecin]);
            }
           else ///daca mai are si alti vecini alegem minimul
            if (vecin != prev)
                current_time_stamp[nod] = min(current_time_stamp[nod], time_stamp[vecin]);
            ///daca vecinul nu poate fi vizitat fara sa trecem prin nod atunci muchia este critica
            if (current_time_stamp[vecin] > time_stamp[nod])
               {cout<<"{"<<nod<<","<<vecin<<"}  ";
                solutie.push_back({nod, vecin});}
        }
    }

///sortam in ordine descescatoare vectorul
bool sort_HH (int i,int j) { return (i>j); }

///complexitate:O(n^2)
bool HH(vector<int> v, int n)
{int ok=1,x;
	while (ok)
	{
		sort(v.begin(), v.end(),sort_HH);
		///toate elementele sunt/au devenit 0 deci ne putem opri=>CORECT
		if (v[0] == 0)
			return true;

		x= v[0];
        v.erase(v.begin() + 0);
       ///daca gradul cel mai mare > lungime vector =>GRESIT
		if (x > v.size())
			return false;

		for (int i = 0; i < x; i++)
		{ ///am "eliminat" primul element deci scadem gradul
			v[i]--;
          ///elemente <0 inseamna ca alt grad era prea mare=>GRESIT
			if (v[i] < 0)
				return false;
		}
	}
}

int main()
{
vector<int> graf[10000];
int n,m;
int x,y,tasta,k=1;
bool comanda;
cout<<"Apasati 1 pentru Orientat / 0 pentru Neorientat\n";
cin>>comanda;
if(comanda==1)
{fin>>n>>m;
for(int i=0;i<m;i++)
    {fin>>x>>y;
    graf[x].push_back(y);

    }
      GrafOrientat gf(n,m,graf);

while(k==1)
{cout<<"\nTasta 1: bfs\nTasta 2:CTC\nTasta 3:sortare topologica\nTasta 4:Havel Hakimi\nTasta 5:adaugare muchie\nTasta 6:afisare graf\nTasta 7:sfarsit\n";
cin>>tasta;
switch(tasta)
{
case 1:{ int s; cout<<"\nNodul sursa: ";cin >>s; gf.bfs(s); break;}

case 2:{gf.ctc(); break;}

case 3:{gf.sortare_top();break;}

case 4:{cout<<"Introduceti nr de noduri si gradele";
int l,gr;
vector <int> v1;
cin>>l;
 for(int i=1;i<=l;i++)
 {
     cin>>gr;
     v1.push_back(gr);
 }
   if(HH(v1,l)==0)
    cout<<"false";
    else cout<<"true";
   break;}

case 5:{cout<<"\nIntre ce noduri?";int a,b;cin>>a>>b; gf.adauga_muchii(a,b);break;}

case 6:{cout<<gf;break;}

case 7: {k=0; break;}
}
}
}
else
{fin>>n>>m;
for(int i=0;i<m;i++)
    {fin>>x>>y;
    graf[x].push_back(y);
    graf[y].push_back(x);
    }
    GrafNeorientat gf(n,m,graf);
while(k==1)
{cout<<"\nTasta 1: bfs\nTasta 2:dfs\nTasta 3:muchii critice\nTasta 5:adaugare muchie\nTasta 6:afisare graf\nTasta 7:sfarsit\n";
cin>>tasta;
switch(tasta)
{
case 1:{ int s; cout<<"\nNodul sursa: ";cin >>s; gf.bfs(s); break;}

case 2:{cout<<gf.conex(); break;}

case 3:{gf.criticalConnections(n,graf) ;break;}

case 5:{cout<<"\nIntre ce noduri?";int a,b;cin>>a>>b; gf.adauga_muchii(a,b);break;}

case 6:{cout<<gf;break;}

case 7: {k=0; break;}
}
}
}



     return 0;
}
