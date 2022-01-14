#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Vertex
{
    int degree;
    int Max;
    vector<int> Neighbor;
    Vertex():degree(0), Max(0), Neighbor({}){;};
};

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(0), cin.tie(0);
	int A, B;
    int maxDegree = 0;
	vector<Vertex> V;
    while(cin >> A >> B)
    {
        if(B >= V.size()) V.resize(B+1);
        V[A].degree++;
		V[A].Neighbor.push_back(B);
		V[B].degree++;
		V[B].Neighbor.push_back(A);
        V[A].Max = max(V[A].Max, B);
        V[B].Max = max(V[B].Max, A);
        maxDegree = max(V[A].degree, max(V[B].degree, maxDegree));
    }
    vector<int> beginOfDeg(maxDegree+1);
    vector<int> Position(V.size());
    vector<int> NumofVtxofDeg;
    for(int i = 0; i <= maxDegree; i++)
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
    int RVtx = NumofVtxofDeg[0];
    for(int i = 0; i < V.size(); i++)
    {
        RVtx = NumofVtxofDeg[i];
        for(auto j:V[RVtx].Neighbor)
        {
            if(V[j].degree > V[RVtx].degree)
            {
                int DegJ = V[j].degree, PosJ = Position[j], PosW = beginOfDeg[DegJ], SubW = NumofVtxofDeg[PosW];
                //swap the neighbor with the beginning of its degree
                if(j != SubW)
                {
                    NumofVtxofDeg[PosJ] = SubW;
                    NumofVtxofDeg[PosW] = j;
                    Position[j] = PosW;
                    Position[SubW] = PosJ;
                }
                //beginning of its degree++ so that the neighbor's degree is subtracted by 1
                beginOfDeg[DegJ]++;
                V[j].degree--;
            }
        }
    }
    A = V[RVtx].degree;
    cout << A << "-core\n";
    for(int i = 0; i < V.size(); i++)
    {
        if(V[i].degree == A)
        {
            if(V[i].Neighbor.size() < 250)
                sort(V[i].Neighbor.begin(), V[i].Neighbor.end());
            else{
                vector<int> temp(V[i].Max+1, 0);
                for(auto j:V[i].Neighbor) temp[j]++;
                B = 0;
                for(int j = 0; j < temp.size(); j++){
                    if(temp[j]) V[i].Neighbor[B++] = j;
                }
            }
            for(auto x:V[i].Neighbor)
            {
                if(V[x].degree == A && x > i)
                {
                    cout << i << " " << x << '\n';
                }
            }
        }
    }
	return 0;
}