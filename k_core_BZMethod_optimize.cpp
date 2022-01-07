#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct Vertex
{
    int degree;
    vector<int> Neighbor;
    Vertex():degree(0), Neighbor({}){;};
};
void BZ_Method(vector<Vertex>& V, int DegreeMax)
{
    vector<int> beginOfDeg(DegreeMax+1);
    vector<int> Position(V.size());
    vector<int> NumofVtxofDeg;
    int Ans = 0, RemainingNode = V.size();
    for(int i = 0; i <= DegreeMax; i++)
    {
        beginOfDeg[i] = NumofVtxofDeg.size();
        for(int j = 0; j < V.size(); j++)
        {
            if(V[j].degree == i)
            {
                NumofVtxofDeg.push_back(j);
                Position[j] = NumofVtxofDeg.size()-1;
            }
        }
    }
    for(int i = 0; i < V.size(); i++)
    {
        int RVtx = NumofVtxofDeg[i];
        for(auto j:V[RVtx].Neighbor)
        {
            if(V[j].degree > V[RVtx].degree)
            {
                int DegJ = V[j].degree, PosJ = Position[j], PosW = beginOfDeg[DegJ], SubW = NumofVtxofDeg[PosW];
                if(j != SubW)
                {
                    NumofVtxofDeg[PosJ] = SubW;
                    NumofVtxofDeg[PosW] = j;
                    Position[j] = PosW;
                    Position[SubW] = PosJ;
                }
                beginOfDeg[DegJ]++;
                V[j].degree--;
            }
        }
    }
    for(auto i:V) Ans = max(Ans, i.degree);
    cout << Ans << "-core" << '\n';
    for(int i = 0; i < V.size(); i++)
    {
        if(V[i].degree == Ans)
        {
            sort(V[i].Neighbor.begin(), V[i].Neighbor.end());
            for(int j = 0; j < V[i].Neighbor.size(); j++)
            {
                if(V[V[i].Neighbor[j]].degree == Ans && V[i].Neighbor[j] > i)
                {
                    cout << i << " " << V[i].Neighbor[j] << '\n';
                }
            }
        }
    }
    return ;
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(0), cin.tie(0);
	int A, B;
    int maxDegree = 0; // for BZ method
    //ifstream f_in(argv[1]);
	vector<Vertex> V;
    while(cin >> A >> B)
    {
        if(A >= V.size()) V.resize(A+1);
        if(B >= V.size()) V.resize(B+1);
        V[A].degree++;
		V[A].Neighbor.push_back(B);
		V[B].degree++;
		V[B].Neighbor.push_back(A);
        maxDegree = max(V[A].degree, max(V[B].degree, maxDegree));
    }
    BZ_Method(V, maxDegree);
    //f_in.close();
	return 0;
}