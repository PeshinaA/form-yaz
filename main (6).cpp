#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
class Rule
{
public:
    char* l_symb;
    int l_s_count;
    char* r_symb;
    int r_s_count;
    
    Rule()
    {
        l_s_count = 1;
        r_s_count = 1;
    }
    
    friend ostream& operator<<(ostream&, Rule);
};
ostream& operator<<(ostream& stream, Rule r)
{
    for (int i=0; i<r.l_s_count; i++) 
    {
        stream<<r.l_symb[i];
    }
    stream<<"->";
    for (int i=0; i<r.r_s_count; i++) 
    {
        stream<<r.r_symb[i];
    }
    stream<<endl;
    return stream;
}
class Grammar
{
public:
	char* nt_symb;
	int nt_count;
	char* t_symb;
	int t_count;
	char e;//пустой символ
	Rule *r;
	
	Grammar()
	{
	    nt_symb = {};
	    nt_count = 0;
	    t_symb = {};
	    t_count = 0;
	}
	void init();
	void init_l_symb(Rule& r);
    void init_r_symb(Rule& r);
    bool check_l(Rule& r);
    bool check_r(Rule& r);
    bool check_ks_grammar(Rule& r);
	friend ostream& operator<<(ostream&, Grammar);
};

void Grammar::init()
{
        cout<<"count nt symb: ";
        cin>>nt_count;
        nt_symb = new char[nt_count];
        
        cout<<"------------nt symb------------"<<endl;
        for (int i=0; i<nt_count; i++)
        {
            cout<<i+1<<". ";
            cin>>nt_symb[i];
        }
        
        cout<<"count t symb: ";
        cin>>t_count;
        t_symb = new char[t_count];
        
        cout<<"------------t symb------------"<<endl;
        for (int i=0; i<t_count; i++)
        {
            cout<<i+1<<". ";
            cin>>t_symb[i];
        }
        
        cout<< "e = ";
        cin>>e;
}
ostream& operator<<(ostream& stream, Grammar g)
{
    stream<<"------------------------Grammar------------------------"<<endl;
    stream<<"G=({";
    for (int i=0; i<g.nt_count; i++) 
    {
        if(g.nt_symb[i]!=g.e)
            stream<<g.nt_symb[i];
    }
    stream<<"},{";
    for (int i=0; i<g.t_count; i++) 
    {
        stream<<g.t_symb[i];
    }
    stream<<"},P,";
    if(g.nt_symb!=NULL)
    {
        stream<<g.nt_symb[0];
    }
    stream<<')'<<endl;
    return stream;
}

void Grammar::init_l_symb(Rule& r)
{
    cout<<"count l symb: ";
    cin>>r.l_s_count;
    r.l_symb = new char[r.l_s_count];
    cout<<"l symb:"<<endl;
    for (int i=0; i<r.l_s_count; i++)
    {
        cout<<i+1<<". ";
        cin>>r.l_symb[i];
        if(!check_l(r))
        {
            throw"no symbol in grammar";
        }
    }
}

void Grammar::init_r_symb(Rule& r)
{
    cout<<"count r symb: ";
    cin>>r.r_s_count;
    r.r_symb = new char[r.r_s_count];
    cout<<"r_symb:"<<endl;
    for (int i=0; i<r.r_s_count; i++)
    {
        cout<<i+1<<". ";
        cin>>r.r_symb[i];
        if(!check_r(r))
        {
            throw"no symbol in grammar";
        }
    }
}
bool Grammar::check_l(Rule& r)
{
    for(int j=0; j<r.r_s_count; j++)
    {
        for (int i=0; i<nt_count; i++)
        {
            if (r.l_symb[j] == nt_symb[i])
            {
                return true;
            }
        }
    }
    return false;
}
bool Grammar::check_r(Rule& r)
{
    for(int j=0; j<r.r_s_count; j++)
    {
        for (int i=0; i<t_count; i++)
        {
            if (r.r_symb[j] == t_symb[i])
            {
                return true;
            }
        }
        for (int i=0; i<nt_count; i++)
        {
            if (r.r_symb[j] == nt_symb[i])
            {
                return true;
            }
        }
        for(int j=0; j<r.r_s_count; j++)
        {
            if (r.r_symb[j] == e)
            {
                return true;
            }
        }
    }
    return false;
}
bool Grammar::check_ks_grammar(Rule& r)
{
    if(r.l_s_count>1)
    {
        return false;
    }
    return true;
}

class Eq_transf
{
public:
    void non_generative_symb(Grammar& g, int r_count, Rule *r);
    void mixed_chains(Grammar& g, int r_count, Rule* r);
    void long_chains(Grammar& g, int r_count, Rule* r);
    void unattainable_symb(Grammar& g, int r_count, Rule* r);
};
void Eq_transf::non_generative_symb(Grammar& g, int r_count, Rule* r)
{
    int q = 0;
    int x = 0;
    int gen_nt_count = 0;
    char *gen_nt_symb  = new char[gen_nt_count];
    gen_nt_symb = {};
    for(int i=0; i<r_count; i++)
    {
        cout<<1;
        for(int j=0; j<r[i].r_s_count; j++)
        {
            cout<<2;
            for(int k=0; k<g.nt_count; k++)
            {
                cout<<3;
                if(r[i].r_symb[j] == g.nt_symb[k])
                {
                    cout<<4;
                    q++;
                }
            }
        }
        if(q==r[i].r_s_count)
        {
            cout<<5;
            gen_nt_count++;
            gen_nt_symb[gen_nt_count-1] = r[i].l_symb[0];
        }
        for(int j=0; j<r[i].r_s_count; j++)
        {
            cout<<6;
            for(int k=0; k<gen_nt_count; k++)
            {
                cout<<7;
                if(r[i].r_symb[j] == gen_nt_symb[k])
                {
                    cout<<8;
                    x++;
                }
            }
        }
        if(x==r[i].r_s_count)
        {
            cout<<9;
            gen_nt_count++;
            gen_nt_symb[gen_nt_count-1] = r[i].l_symb[0];
        }
    }
    if(gen_nt_count!=0)
    {
        cout<<10;
        for(int i=0; i<g.nt_count; i++)
        {
            cout<<11;
            g.nt_symb[i] = NULL;
        }
        g.nt_count-=gen_nt_count;
        for(int i=0; i<g.nt_count; i++)
        {
            cout<<12;
            g.nt_symb[i]=gen_nt_symb[i];
        }
    }
/*    for(int i=0; i<r_count; i++)
    {
        for(int j=0;j<g.nt_count; j++)
        {
            if((r[i].l_symb[0]!=g.nt_symb[j])&&(gen_nt_count!=0))
            {
                for(int k=0; k<r[i].r_s_count; k++)
                {
                    r[i].r_symb[k] = g.e;
                }
            }
        }
    }*/
    delete [] gen_nt_symb;
/*    int n_i = r_count;
    char del_symb;
    for(int i=0; i<r_count; i++)
    {
        for(int j=0; j<r[i].r_s_count; j++)
        {
            if(r[i].r_symb[j] == r[i].l_symb[0])
            {
                cout<<"non generative symb: "<<r[i].l_symb[0]<<endl;
                del_symb = r[i].l_symb[0];
                n_i--;
            }
        }
        if(n_i != r_count)
        {
            for(int j=0; j<r[i].r_s_count; j++)
            {
                r[i].r_symb[j] = g.e;
            }
            for(int j=0; j<g.nt_count; j++)
            {
                if(g.nt_symb[j] == r[i].l_symb[0])
                {
                    g.nt_symb[j] = g.e;
                }
            }
        }
    }*/
}
void Eq_transf::unattainable_symb(Grammar& g, int r_count, Rule* r)
{
    int nat_nt_count = 1;
    char *nat_nt_symb  = new char[nat_nt_count];
    gen_nt_sym[0] = 'S';
    for(int i=0; i<r_count; i++)
    {
        for(int j=0; j<r[i].r_s_count; j++)
        {
            for(int k=0; k<nat_nt_count; k++)
            {
                if(r[i].l_symb==nat_nt_symb[k])
                {
                    nat_nt_count++;
                    for(int l=0; l<r[i].r_s_count; l++)
                    {
                        for(int a=0; a<g.nt_count; a++)
                        {
                            if(r[i].r_symb[l] == g.nt_symb[a])
                            {
                                nat_nt_symb[nat_nt_count-1] = r[i].r_symb[l];
                            }
                        }
                    }
                }
            }
        }
    }
    if(gen_nt_count!=0)
    {
        cout<<10;
        for(int i=0; i<g.nt_count; i++)
        {
            cout<<11;
            g.nt_symb[i] = NULL;
        }
        g.nt_count-=gen_nt_count;
        for(int i=0; i<g.nt_count; i++)
        {
            cout<<12;
            g.nt_symb[i]=gen_nt_symb[i];
        }
    }
    delete [] gen_nt_symb;
    
}
void Eq_transf::mixed_chains(Grammar& g, int r_count, Rule* r)
{
/*
    int t = 0;
    int n = 0;
//    int new_r_count;
    for(int i=0; i<r_count; i++)
    {
        if(r[i].r_s_count>1)
        {
            for(int j=0; j<r[i].r_s_count; j++)
            {
                for (int k=0; k<g.t_count; k++)
                {
                    if ((r[i].r_symb[j] == g.t_symb[k])||(r[i].r_symb[j] == g.e))
                    {
                        t++;
                    }
                }
                for (int k=0; k<g.nt_count; k++)
                {
                    if (r[i].r_symb[j] == g.nt_symb[k])
                    {
                        n++;
                    }
                }
            }
            if((t!=0)&&(n!=0))
            {
                
            }else
            {
   //             new_r_count = r_count;
                for(int j=0; j<r[i].r_s_count; j++)
                {
                    
                }
            }
        }
    }*/
}
void Eq_transf::long_chains(Grammar& g, int r_count, Rule* r)
{
/*    int count_new_r = 0;
    char *new_nt_symb = new char[count_new_r];
    for(int i=0; i<r_count; i++)
    {
        if(r[i].r_s_count>2)
        {
            count_new_r++;
            cout<<i+1<<" long chain"<<endl;
            cout<<"Enter new nt symb: ";
            cin>>new_nt_symb[count_new_r];
        }
    }  
    cout<<count_new_r<<endl;
    if(count_new_r!=0)
    {
        r_count+=count_new_r;
        for(int i=r_count-count_new_r; i<r_count; i++)
        {
            for(int n=0; n<count_new_r; n++)
            {
                for(int j=0; j<r[i].r_s_count; j++)
                {
                    //for(int k=0; k<g.nt_count; k++)
                    //{
                     //   if(r[i].r_symb[j] != g.nt_symb[k])
                     //   {
                            cout<<'1'<<endl;
                            r[i].l_symb[j] = new_nt_symb[n];
                       // }
                    //}
                }
            }
        }
        g.nt_count+=count_new_r;
        for(int j=0; j<count_new_r; j++)
        {    
            for(int i=g.nt_count-count_new_r; i<g.nt_count; i++)
            {
                cout<<'2'<<endl;
                g.nt_symb[i]=new_nt_symb[j];
            }
        }
    }*/
}

int main()
{
    Grammar g;
    g.init();
    int r_count = 0;
    cout<<"count rules: ";
    cin>>r_count;
    Rule *r = new Rule[r_count];
    for(int i=0; i<r_count; i++)
    {
        cout<<i+1<<". ";
        g.init_l_symb(r[i]);
        g.init_r_symb(r[i]);
        cout<<"------------"<<endl;
    }
    cout<<g;
    cout<<"------------P------------"<<endl;
    for(int i=0; i<r_count; i++)
    {
        cout<<i+1<<". ";
        cout<<r[i];
    }
    
    int m = 0;
    for(int i=0; i<r_count; i++)
    {
        if(!g.check_ks_grammar(r[i]))
        {
            m++;
        }
    }
    
    Eq_transf t;
    int new_r_count = r_count;
    Rule *new_r = new Rule[new_r_count];
    if(m!=0)
    {
        cout<<"Grammar not KS"<<endl;
    }else 
    {
        cout<<"Grammar KS"<<endl;
        t.non_generative_symb(g, r_count, r);
        t.long_chains(g, r_count, r);
        t.unattainable_symb(g, r_count, r);
        cout<<g;
    cout<<"------------P------------"<<endl;
    for(int i=0; i<r_count; i++)
    {
        cout<<i+1<<". ";
        cout<<r[i];
    }
    
    }
    delete [] r;
    return 0;
}