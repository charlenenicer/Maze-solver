#include "path.h"
#include <queue>
#include <stack>
using namespace std;

path::path(const PNG & im, pair<int,int> s, pair<int,int> e)
   :start(s),end(e),image(im){
    BFS();
}

// used to initialize member variable pathPts.
// called by constructor to create path if it
// exists.
//
// requires: neighbors, good, assemble helpers
//
// See the interfaces for good and assemble
// to get a hint on two auxiliary structures
// you will want to build: predecessor table,
// and visited table.


void path::BFS(){
	// initialize working vectors
	vector<vector<bool>> V(image.height(), vector<bool> (image.width(),false));
	vector<vector<pair<int,int>>> P(image.height(), vector<pair<int,int>> (image.width(),end));
    
    queue<pair<int,int>> Q;
    Q.push(start);
    V[start.second][start.first] = true;

    while(!Q.empty()){
        pair<int,int> itself = Q.front();
        vector<pair<int,int>> n = neighbors (itself);
        for(int i = 0; i <(int) n.size(); i ++){
            if(good(V, itself, n[i])){
                V[n[i].second][n[i].first] = true;
                P[n[i].second][n[i].first] = itself;
                Q.push(n[i]);
            }
        }
        
          Q.pop();
    }
    
//    for(int i = 0; i < (int)P.size(); i++){
//        for(int k = 0; k < (int) P[0].size(); k ++){
//            printf("(%d, %d) ", P[i][k].first, P[i][k].second);
//        }
//        printf("\n");
//    }
    
    

    pathPts = assemble(P,start,end);
}

PNG path::render(){
    PNG copy = image;
    for(unsigned i = 0; i < pathPts.size(); i++){
        RGBAPixel *pixel = copy.getPixel(pathPts[i].first, pathPts[i].second);
        *pixel = RGBAPixel(255,0,0);
    }
    return copy;
}

vector<pair<int,int>> path::getPath() { return pathPts;}

int path::length() { return pathPts.size();}



// tests a neighbor (adjacent vertex) to see if it is
// 1. within the image, 2. unvisited, and 3. close in color to curr.
// An entry in table V is true if a cell has previously been
// visited.
bool path::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){

 if ((next.first >= (int) image.width()) || (next.first < 0))
     return false;
 if ((next.second >=  (int) image.height()) || (next.second < 0))
     return false;
 if (v[next.second][next.first])
     return false;
    
    RGBAPixel *pixel1 = image.getPixel(curr.first, curr.second);
    RGBAPixel *pixel2 = image.getPixel(next.first, next.second);
 if (!closeEnough(*pixel1,*pixel2))
     return false;

     return true;
 
}

vector<pair<int,int>> path::neighbors(pair<int,int> curr) {
	vector<pair<int,int>> n;
    pair<int,int> above = {curr.first, curr.second - 1};
    pair<int,int> below = {curr.first, curr.second + 1};
    pair<int,int> left = {curr.first -1 , curr.second};
    pair<int,int> right = {curr.first + 1, curr.second};

//    n.push_back(left);
//    n.push_back(below);
    n.push_back(right);
    n.push_back(above);
    n.push_back(left);
    n.push_back(below);
    return n;

}

// Assumes the predecessor table, built in the BFS as follows: For each
// location in the image reachable from the start vertex, "loc", the
// table contains the location "pred" from which "loc" was first seen.
// ("pred", "loc") is thus an edge in the shortest path from s to
// "loc".
//
// returns the set of points on the shortest path from s to e, if
// it exists. Call this vector P.
//
// if there is a shortest path: position 0 should contain s,
// and for all 0 < i < size, P[0] to P[i] is the set of points
// on the shortest path from s to point P[i]. P[size-1] == e.

// if no path from s to e exists, then just return a single element
// vector P with P[0] == s.
vector<pair<int,int>> path::assemble(vector<vector<pair<int,int>>> & p,pair<int,int> s, pair<int,int> e) {
    vector<pair<int, int>> P;
    stack<pair<int,int>> S;
    S.push(end);
    S.push(p[e.second][e.first]);
    
    if(p[e.second][e.first] == e){
        P.push_back(s);
        return P;
    }

    while(S.top() != s){
        pair<int,int> top = S.top();
        S.push(p[top.second][top.first]);
    }
    

    
    
    while(!S.empty()){
        P.push_back(S.top());
        S.pop();
    }
    

    return P;
}

bool path::closeEnough(RGBAPixel p1, RGBAPixel p2){
   int dist = (p1.r-p2.r)*(p1.r-p2.r) + (p1.g-p2.g)*(p1.g-p2.g) +
               (p1.b-p2.b)*(p1.b-p2.b);

   return (dist <= 80);
}
