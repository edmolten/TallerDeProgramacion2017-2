#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>

#define MAX_CHAR 603

using namespace std;

struct SuffixTreeNode {
    struct SuffixTreeNode *children[MAX_CHAR];
    struct SuffixTreeNode *suffixLink;
    int start;
    int *end;
    int suffixIndex;
};

typedef struct SuffixTreeNode Node;

char text[603];
Node *root;
Node *lastNewNode;
Node *activeNode;
int activeEdge;
int activeLength;
int remainingSuffixCount;
int leafEnd;
int *rootEnd;
int *splitEnd;
int size;
int size1;

Node *newNode(int start, int *end){
    Node *node =(Node*) malloc(sizeof(Node));
    int i;
    for (i = 0; i < MAX_CHAR; i++)
        node->children[i] = nullptr;
    node->suffixLink = root;
    node->start = start;
    node->end = end;
    node->suffixIndex = -1;
    return node;
}

int edgeLength(Node *n) {
    if(n == root)
        return 0;
    return *(n->end) - (n->start) + 1;
}

int walkDown(Node *currNode){
    if (activeLength >= edgeLength(currNode)){
        activeEdge += edgeLength(currNode);
        activeLength -= edgeLength(currNode);
        activeNode = currNode;
        return 1;
    }
    return 0;
}

void extendSuffixTree(int pos){
    leafEnd = pos;
    remainingSuffixCount++;
    lastNewNode = nullptr;
    while(remainingSuffixCount > 0) {
        if (activeLength == 0)
            activeEdge = pos;
        if (activeNode->children[text[activeEdge]] == nullptr) {
            activeNode->children[text[activeEdge]] =
                    newNode(pos, &leafEnd);
            if (lastNewNode != nullptr) {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = nullptr;
            }
        }
        else {
            Node *next = activeNode->children[text[activeEdge]];
            if (walkDown(next)){
                continue;
            }
            if (text[next->start + activeLength] == text[pos]){
                if(lastNewNode != nullptr && activeNode != root) {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = nullptr;
                }
                activeLength++;
                break;
            }
            splitEnd = (int*) malloc(sizeof(int));
            *splitEnd = next->start + activeLength - 1;
            Node *split = newNode(next->start, splitEnd);
            activeNode->children[text[activeEdge]] = split;
            split->children[text[pos]] = newNode(pos, &leafEnd);
            next->start += activeLength;
            split->children[text[next->start]] = next;
            if (lastNewNode != nullptr){
                lastNewNode->suffixLink = split;
            }
            lastNewNode = split;
        }

        remainingSuffixCount--;
        if (activeNode == root && activeLength > 0)
        {
            activeLength--;
            activeEdge = pos - remainingSuffixCount + 1;
        }
        else if (activeNode != root)
        {
            activeNode = activeNode->suffixLink;
        }
    }
}

void setSuffixIndexByDFS(Node *n, int labelHeight){
    if (n == nullptr)  return;
    int leaf = 1;
    int i;
    for (i = 0; i < MAX_CHAR; i++)    {
        if (n->children[i] != nullptr)        {
            leaf = 0;
            setSuffixIndexByDFS(n->children[i], labelHeight +
                                                edgeLength(n->children[i]));
        }
    }
    if (leaf == 1){
        for(i= n->start; i<= *(n->end); i++) {
            if(text[i] == '#'){
                n->end = (int*) malloc(sizeof(int));
                *(n->end) = i;
            }
        }
        n->suffixIndex = size - labelHeight;
    }
}

void freeSuffixTreeByPostOrder(Node *n){
    if (n == nullptr)
        return;
    int i;
    for (i = 0; i < MAX_CHAR; i++) {
        if (n->children[i] != nullptr) {
            freeSuffixTreeByPostOrder(n->children[i]);
        }
    }
    if (n->suffixIndex == -1)
        free(n->end);
    free(n);
}

void buildSuffixTree()
{
    size = strlen(text);
    int i;
    rootEnd = (int*) malloc(sizeof(int));
    *rootEnd = - 1;
    root = newNode(-1, rootEnd);
    activeNode = root;
    for (i=0; i<size; i++)
        extendSuffixTree(i);
    int labelHeight = 0;
    setSuffixIndexByDFS(root, labelHeight);
}

int search(Node *n, int labelHeight, int *maxHeight, vector<int> *substringStartIndexes) {
    if(n == nullptr){
        return 0;
    }
    int i=0;
    int ret;
    if(n->suffixIndex < 0) {
        for (i = 0; i < MAX_CHAR; i++){
            if(n->children[i] != nullptr){
                ret = search(n->children[i], labelHeight +
                                             edgeLength(n->children[i]),
                             maxHeight, substringStartIndexes);

                if(n->suffixIndex == -1)
                    n->suffixIndex = ret;
                else if((n->suffixIndex == -2 && ret == -3) ||
                        (n->suffixIndex == -3 && ret == -2) ||
                        n->suffixIndex == -4){
                    n->suffixIndex = -4;//Mark node as XY
                    //Keep track of deepest node
                    if(*maxHeight < labelHeight) {
                        *maxHeight = labelHeight;
                        substringStartIndexes->clear();
                        substringStartIndexes->push_back(*(n->end) -    labelHeight + 1);
                    }
                    else if(*maxHeight == labelHeight){
                        substringStartIndexes->push_back(*(n->end) -    labelHeight + 1);
                    }
                }
            }
        }
    }
    else if(n->suffixIndex > -1 && n->suffixIndex < size1)//suffix of X
        return -2;//Mark node as X
    else if(n->suffixIndex >= size1)//suffix of Y
        return -3;//Mark node as Y
    return n->suffixIndex;
}

void getLongestCommonSubstring() {
    int maxHeight = 0;
    vector<int> substringStartIndexes;
    search(root, 0, &maxHeight, &substringStartIndexes);
    if(maxHeight == 0){
        cout << "No common sequence." << endl << endl;
        return;
    }
    int i = 0;
    string subs[600];
    for(vector<int>::iterator it = substringStartIndexes.begin(); it != substringStartIndexes.end(); it++){
        string s(text + *it, maxHeight); //?
        bool found = false;
        for (int ii = 0 ; ii < i; ii++){
            if (subs[ii] == s){
                found = true;
                break;
            }
        }
        if (!found){
            subs[i] = s;
            i++;
        }
    }
    sort(subs, subs + i);
    for(int j = 0; j < i; j++){
        cout << subs[j] << endl;
    }
    cout << endl;
}

int main(int argc, char *argv[]){
    string a, b;
    string sep;
    while(getline(cin,a)){
        getline(cin,b);
        getline(cin,sep);
        root = nullptr;
        lastNewNode = nullptr;
        activeNode = nullptr;
        activeEdge = -1;
        activeLength = 0;
        remainingSuffixCount = 0;
        leafEnd = -1;
        rootEnd = nullptr;
        splitEnd = nullptr;
        size = -1;
        string str = a + "#" + b + "$";
        size1 = a.length();
        strcpy(text, str.c_str());
        buildSuffixTree();
        getLongestCommonSubstring();
        freeSuffixTreeByPostOrder(root);
    }
    return 0;
}