#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct Vertex
{
    int degree;
    vector<int> arc;
    Vertex():degree(0), arc({}){;};
};

void updateDegree(vector<vector<int> >& NumofVtxofDeg, vector<Vertex>& V, int index)
{
    int k = V[index].degree;
    for(int i = 0; i < NumofVtxofDeg[k].size(); i++)
    {
        if(NumofVtxofDeg[k][i] == index)
        {
            NumofVtxofDeg[k].erase(NumofVtxofDeg[k].begin()+i);
            V[index].degree--;
            NumofVtxofDeg[k-1].push_back(index);
        }
    }
    return ;
}

void PrintResult(int k, vector<Vertex>& v, vector<int>& CoreValue)
{
    cout << k << "-core" << endl;
    for(int i = 0; i < CoreValue.size(); i++)
    {
        if(CoreValue[i] == k)
        {
            sort(v[i].arc.begin(), v[i].arc.end());
            for(int j = 0; j < v[i].arc.size(); j++)
            {
                if(CoreValue[v[i].arc[j]] == k && v[i].arc[j] > i)
                {
                    cout << i << " " << v[i].arc[j] << endl;
                }
            }
        }
    }
    return ;
}

void BZ_Method(vector<Vertex>& V, int DegreeMax)
{
    vector<int> CoreValue(V.size(), 0);
    vector<vector<int> > NumofVtxofDeg(DegreeMax+1);
    int Ans = 0, RemainingNode = V.size();
    for(int i = 0; i < V.size(); i++)
    {
        NumofVtxofDeg[V[i].degree].push_back(i);
        DegreeMax = max(DegreeMax, V[i].degree);
    }
    for(int i = 0; i <= DegreeMax; i++)
    {
        while(!NumofVtxofDeg[i].empty())
        {
            int k = NumofVtxofDeg[i][0];
            CoreValue[k] = i;
            Ans = max(Ans, CoreValue[k]);
            NumofVtxofDeg[i].erase(NumofVtxofDeg[i].begin());
            V[k].degree = -1;
            RemainingNode--;
            for(int j = 0; j < V[k].arc.size(); j++)
            {
                if(V[V[k].arc[j]].degree > i)
                {
                    updateDegree(NumofVtxofDeg, V, V[k].arc[j]);
                }
            }
        }
        if(RemainingNode == 0)
        {    
            PrintResult(Ans, V, CoreValue);
            return ;
        }
    }
    return ;
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(0), cin.tie(0);
	int A, B;
    int maxDegree = 0; // for BZ method
    ifstream f_in(argv[1]);
	vector<Vertex> V{Vertex()};
    while(cin >> A >> B)
    {
		if(B >= V.size()) V.resize(B+1);
        V[A].degree++;
		V[A].arc.push_back(B);
		V[B].degree++;
		V[B].arc.push_back(A);
        maxDegree = max(V[A].degree, max(V[B].degree, maxDegree));
    }
    BZ_Method(V, maxDegree);
    f_in.close();
	return 0;
}