#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Vertex
{
    int degree;
    vector<int> arc;
    Vertex():degree(0), arc({}){;};
};

void PrintResult(int k, vector<Vertex>& v)
{
    cout << k << "-core" << '\n';
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i].degree > 0)
        {
            sort(v[i].arc.begin(), v[i].arc.end());
            for(int j = 0; j < v[i].arc.size(); j++)
            {
                if(v[v[i].arc[j]].degree > 0 && v[i].arc[j] > i)
                {
                    cout << i << " " << v[i].arc[j] << '\n';
                }
            }
        }
    }
    return ;
}

void NaiveMethod(vector<Vertex>& V, int DegreeMax)
{
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
                if(V[i].degree >= 0 && V[i].degree < k)
                {
                    V[i].degree = -1;
                    RemainingNode--;
                    for(int j = 0; j < V[i].arc.size(); j++)
                    {
                        if(V[V[i].arc[j]].degree > 0) V[V[i].arc[j]].degree--;
                        repeat = (V[V[i].arc[j]].degree < k) ? true : repeat;
                    }
                }
            }
        }
        if(RemainingNode == 0)
        {
            PrintResult(k-1, dup);
            return ;
        }
        k++;
    }
    return ;
}


int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(0), cin.tie(0);
	int A, B;
    int maxDegree = 0; // for BZ method
	vector<Vertex> V{Vertex()};
	while(cin >> A >> B)
	{
		if(B >= V.size()) V.resize(B+1);
		if(A >= V.size()) V.resize(A+1);
		V[A].degree++;
		V[A].arc.push_back(B);
		V[B].degree++;
		V[B].arc.push_back(A);
        maxDegree = max(V[A].degree, max(V[B].degree, maxDegree));
	}
    NaiveMethod(V, maxDegree);
	return 0;
}