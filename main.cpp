#include <iostream>
#include <string>
#include <algorithm>
#include <utility> 
using namespace std;
class JSONParser{
    
    string expression;
    int nodes[100], depths[100], reducedNodesDepths[100], 
    bfs[100], lpar[10000], parent[100], count[100], nchild[100], alloc[100], 
    result[100], resultLength;
    public:
        JSONParser(string s){
            expression = s;
        }

        bool CheckIfParanthesIsBalanced(string expression){
            int sum = 0;
            for(int i = 0; i < expression.length(); i++){
                if(expression[i] == '[')
                    sum++;
                else
                    sum--;    
            }
            if(sum == 0)
                return true;
            else
                return false;
        }

        void CountNodes(string expression){
            int node = 1;
            nodes[0] = 0;
            for(int i = 1; i < expression.length(); i++){
                nodes[i] = node;
                if(expression[i] == '[')
                    node++;
                
            }
        }

        void CountDepth(string expression){
            int depth = 1;
            depths[0] = 0;
            for(int i = 1; i < expression.length(); i++){
                depths[i] = depth;
                if(expression[i] == '[')
                    depth++;
                else
                    depth--;
                
            }
        }

        int ReduceToNodes(int depths[], string expression){
            int i = 0;
            int j = 0;
            while(j < expression.length()){
                if(expression[j] == '['){
                    reducedNodesDepths[i] = depths[j];
                    i++;
                }
                j++;
            }
            return i;
        }

        void SorthByDepth(int reducedNodesDepths[]){
            int nodesCount = ReduceToNodes(depths, expression);
            pair<int, int> p;
            pair<int, int> depthAndIndex[100];
            for(int i = 0; i < nodesCount; i++){
                p = make_pair(reducedNodesDepths[i], i);
                depthAndIndex[i] = p;
            }
            sort(depthAndIndex, depthAndIndex + nodesCount);
            for(int i = 0; i < nodesCount; i++){
                bfs[depthAndIndex[i].second] = i;
            }
                

        }
        void FindParentOfLeftMostCHild(int bfs[],int reducedNodesDepths[]){
            int nodesCount = ReduceToNodes(depths, expression);
            lpar[0] = -1;
            for(int i = 1; i < nodesCount ; i++)
                lpar[i] = -1;
            for(int i = 1; i < nodesCount ; i++)
                if((reducedNodesDepths[i] - reducedNodesDepths[i - 1]) == 1)
                    lpar[bfs[i]] = bfs[i - 1];
            
        }

        void FindParentOfNodes(int lpar[]){
            int nodesCount = ReduceToNodes(depths, expression);
            int tmp = 1;
            count[0] = -1;
            parent[0] = -1;
            for(int i = 1; i < nodesCount; i++){
                if(lpar[i] == -1){
                    parent[i] = parent[i - 1];
                    tmp++;
                    count[i] = tmp;
                    
                }
                else{
                    parent[i] = lpar[i];
                    tmp = 1;
                    count[i] = tmp;
                }
            }
        }
        void FindNumberOfChildren(int parent[], int count[]){
            int nodesCount = ReduceToNodes(depths, expression);
            for(int i = 0; i < nodesCount; i++)
                nchild[i] = 0;
            
            for(int i = 1; i < nodesCount - 1; i++)
                if(parent[i] != parent[i + 1])
                    nchild[parent[i]] = count[i];
            nchild[parent[nodesCount - 1]] = count[nodesCount - 1];

        }

        void BuildAllocArray(int nchild[]){
            int nodesCount = ReduceToNodes(depths, expression);
            alloc[0] = 0;
            for(int i = 1; i < nodesCount; i++)
                alloc[i] = alloc[i - 1] + nchild[i - 1] + 1;
        }

        int FindMaximumAllocated(int alloc[]){
            int nodesCount = ReduceToNodes(depths, expression);
            int max = 0;
            for(int i = 0; i < nodesCount; i++)
                if(alloc[i] > max)
                    max = alloc[i];
            return max;
        }

        int BuildResultArray(int alloc[], int nchild[], int parent[]){
            int nodesCount = ReduceToNodes(depths, expression);
            result[0] = nchild[0];
            for(int i = 1; i < nodesCount; i ++)
                result[alloc[i]] = nchild[i];
                
            for(int i = 1; i < nodesCount; i ++)
                result[alloc[parent[i]] + count[i]] = alloc[i];
            
        }

        void GenerateFinalResult(){
            if(CheckIfParanthesIsBalanced(expression)){
                CountNodes(expression);
                CountDepth(expression);
                ReduceToNodes(depths, expression);
                SorthByDepth(reducedNodesDepths);
                FindParentOfLeftMostCHild(bfs, reducedNodesDepths);
                FindParentOfNodes(lpar);
                FindNumberOfChildren(parent, count);
                BuildAllocArray(nchild);
                BuildResultArray(alloc, nchild, parent);
                resultLength = FindMaximumAllocated(alloc);
                for(int i = 0; i < resultLength + 1; i ++)
                    cout << i << "\t" << result[i] << endl;
            }
            else
                cout << "Input is not balanced!" << endl;
        }
};


int main(){
    JSONParser jp("[[][[][][[]]][][]]");
    jp.GenerateFinalResult();
    
    /*
    for(int i = 0; i < 18 ;i ++){
        cout << jp.nodes[i] << " ";  
    }
    cout << endl;
    for(int i = 0; i < 18 ;i ++){
        cout << jp.depths[i] << " "; 
    }
    cout << endl;
    for(int i = 0; i < 9 ;i ++){
        cout << jp.reducedNodesDepths[i] << " ";  
    }
    cout << endl;
    for(int i = 0; i < 9 ;i ++){
        cout << jp.bfs[i] << " ";    
    }
    cout << endl;
    for(int i = 0; i < 9 ;i ++){
        cout << jp.lpar[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < 9 ;i ++){
        cout << jp.parent[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < 9 ;i ++){
        cout << jp.nchild[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < 9 ;i ++){
        cout << jp.count[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < 9 ;i ++){
        cout << jp.alloc[i] << " ";
    }
    cout << endl;
    */
    
}
