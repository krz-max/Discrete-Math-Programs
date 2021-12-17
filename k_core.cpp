#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Vertex
{
    int deg;
    vector<int> arc;
    Vertex():deg(0), arc({}){;};
};

struct Edge
{
    int start;
    int dest;
    Edge(int s, int d):start(s), dest(d){;};
};

void test(int k, vector<Vertex>& v)
{
    cout << k-1 << "-core" << endl;
    vector<Edge> E;
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i].deg > 0)
        {
            for(int j = 0; j < v[i].arc.size(); j++)
            {
                if(v[v[i].arc[j]].deg > 0 && v[i].arc[j] > i) E.push_back(Edge(i, v[i].arc[j]));
            }
        }
    }
    for(int i = 0; i < E.size(); i++)
    {
        cout << E[i].start << " " << E[i].dest << endl;
    }
    /*
    cout << k-1 << "-core" << endl;
    cout << "Vertex: " << endl;
    vector<Edge> E;
    for(int i = 0; i < v.size(); i++)
    {
        cout << i << " " << v[i].deg << endl;
		for(int j = 0; j < v[i].arc.size(); j++)
		{
			cout << v[i].arc[j] << " ";
		}
		cout << endl;
        if(v[i].deg > 0)
        {
            for(int j = 0; j < v[i].arc.size(); j++)
            {
                if(v[v[i].arc[j]].deg > 0 && v[i].arc[j] > i) E.push_back(Edge(i, v[i].arc[j]));
            }
        }
    }
    cout << "Edge: " << endl;
    for(int i = 0; i < E.size(); i++)
    {
        cout << "Edge " << i << ": " << E[i].start << " " << E[i].dest << endl;
    }
    */
    return ;
}

int main(int argc, char** argv)
{
	ifstream f_in(argv[1]);
	int A, B;
	vector<Vertex> V{Vertex()};
	while(f_in >> A >> B)
	{
		while(B >= V.size())
			V.push_back(Vertex());
		V[A].deg++;
		V[A].arc.push_back(B);
		V[B].deg++;
		V[B].arc.push_back(A);
	}
	test(1, V);
    int k = 1;
    int RemainingNode = V.size();
    vector<Vertex> dup;
    while(RemainingNode > 0) 
    {
        dup = V;
        bool repeat = true;
        while(repeat)
        {
            repeat = false;
            for(int i = 0; i < V.size(); i++)
            {
                if(V[i].deg >= 0 && V[i].deg < k)
                {
                    V[i].deg = -1;
                    cout << "Remove: " << i << endl;
                    RemainingNode--;
                    for(int j = 0; j < V[i].arc.size(); j++)
                    {
                        if(V[V[i].arc[j]].deg > 0) V[V[i].arc[j]].deg--;
                        repeat = (V[V[i].arc[j]].deg < k) ? true : repeat;
                    }
                }
            }
        }
        if(RemainingNode == 0)
        {
            test(k, dup);
            return 0;
        }
        k++;
        test(k, V);
    }
	return 0;
}
/*
using Edge (hasn't pass)
int main(int argc, char** argv){
    ifstream f_in(argv[1]);
    int A, B;
    vector<Edge> E;
    while(f_in >> A >> B)
    {
        E.push_back(Edge(A, B));
    }
    vector<Vertex> V(E[E.size()-1].dest+1, Vertex());
    for(int i = 0; i < E.size(); i++)
    {
        V[E[i].start].deg++;
        V[E[i].dest].deg++;
    }
    while(!E.empty())
    {
        vector<Edge> dup = E;
        bool repeat = true;
        while(repeat)
        {
            repeat = false;
            for(int i = 0; i < E.size(); i++)
            { 
                if(V[E[i].start].deg >= 0 && V[E[i].start].deg < k)
                {
                    V[E[i].start].deg = -1;
                    cout << "Remove: " << E[i].start << endl;
                    int del = E[i].start;
                    int j = i;
                    //Use BFS to delete edges
                    //So I need edges in Node
                    while(j < E.size() && E[j].start == del)
                    {
                        V[E[j].dest].deg--;
                        repeat = (V[E[j].dest].deg < k) ? true : repeat;
                        E.erase(E.begin()+j);
                    }
                    while(j < E.size())
                    {
                        if(E[j].dest == del) 
                        {
                            V[E[j].start].deg--;
                            repeat = (V[E[j].start].deg < k) ? true : repeat;
                            E.erase(E.begin()+j);
                            j--;
                        }
                        j++;
                    }
                    i--;
                    continue;
                }
                if(V[E[i].dest].deg >= 0 && V[E[i].dest].deg < k)
                {
                    V[E[i].dest].deg = -1;
                    cout << "Remove: " << E[i].dest << endl;
                    int del = E[i].dest;
                    int j = i;
                    while(j < E.size() && E[j].dest == del)
                    {
                        V[E[j].start].deg--;
                        repeat = (V[E[j].start].deg < k) ? true : repeat;
                        E.erase(E.begin()+j);
                    }
                    while(j < E.size() && E[j].start != del) j++;
                    while(j < E.size() && E[j].start == del)
                    {
                        V[E[j].dest].deg--;
                        repeat = (V[E[j].dest].deg < k) ? true : repeat;
                        E.erase(E.begin()+j);
                    }
                    i--;
                    continue;
                }
            }
            if(E.empty())
            {
                cout << "---The End" << endl;
                test(k, V, dup);
                return 0;
            }
        }
        cout << "-----" << endl;
        cout << "k: " << k << endl;
        test(k, V, E);
        k++;
    } 
    return 0;
}
*/