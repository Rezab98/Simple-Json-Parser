#include <iostream>
#include <string>

int nodes[100];
int nodes[100];
int expressionLength = expression.length()
bool CheckIfParanthesIsBalanced(string expression){
    int sum = 0
    for(int i = 0; i < expression.length(); i++){
        if(expression[i] == '(')
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
    int node = 0;
    for(int i = 0; i < expressionLength; i++){
        if(expression[i] == '(')
            node++;
        nodes[i] = node;
    }
}

void CountDepth(string expression){
    int depth = 0;
    for(int i = 0; i < expressionLength; i++){
        if(expression[i] == '(')
            depth++;
        nodes[i] = node;
    }
}


int main(){



}
