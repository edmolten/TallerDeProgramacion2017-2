#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
#define MAX_CHAR 1002

struct SuffixTreeNode {
    struct SuffixTreeNode *children[MAX_CHAR];


    struct SuffixTreeNode *suffixLink;

    int start;
    int *end;


    int suffixIndex;
};

typedef struct SuffixTreeNode Node;

char text[MAX_CHAR];
Node *root = nullptr;


Node *lastNewNode = nullptr;
Node *activeNode = nullptr;

int activeEdge = -1;
int activeLength = 0;


int remainingSuffixCount = 0;
int leafEnd = -1;
int *rootEnd = nullptr;
int *splitEnd = nullptr;
int size = -1;

Node *newNode(int start, int *end)
{
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
    if (activeLength >= edgeLength(currNode))
    {
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
        if (activeNode->children[text[activeEdge]] == nullptr)
        {
            activeNode->children[text[activeEdge]] =
                    newNode(pos, &leafEnd);

            if (lastNewNode != nullptr)
            {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = nullptr;
            }
        }

        else
        {
            Node *next = activeNode->children[text[activeEdge]];
            if (walkDown(next))
            {
                continue;
            }
            if (text[next->start + activeLength] == text[pos])            {

                if(lastNewNode != nullptr && activeNode != root)                {
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

            if (lastNewNode != nullptr)
            {

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
    if (leaf == 1)   {
        n->suffixIndex = size - labelHeight;
    }
}

void freeSuffixTreeByPostOrder(Node *n)
{
    if (n == nullptr)
        return;
    int i;
    for (i = 0; i < MAX_CHAR; i++)
    {
        if (n->children[i] != nullptr)
        {
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

int get_number_of_children(Node * n){
    int r = 0;
    for(int i = 0; i < MAX_CHAR; i++){
        if(n->children[i] != nullptr) {
            r++;
        }
    }
    return r;
}

void doTraversal(Node *n, int labelHeight, int* maxHeight,
                 int* substringStartIndex, int* number, Node * parent){
    if(n == nullptr)
    {
        return;
    }
    int i=0;
    if(n->suffixIndex == -1)
    {
        for (i = 0; i < MAX_CHAR; i++)
        {
            if(n->children[i] != nullptr)
            {
                doTraversal(n->children[i], labelHeight +
                                            edgeLength(n->children[i]), maxHeight,
                            substringStartIndex, number, n);
            }
        }
    }
    else if(n->suffixIndex > -1 &&
            (*maxHeight < labelHeight - edgeLength(n)))
    {
        *maxHeight = labelHeight - edgeLength(n);
        *substringStartIndex = n->suffixIndex;
        *number = get_number_of_children(parent);
    }
}



void getLongestRepeatedSubstring(){
    int maxHeight = 0;
    int substringStartIndex = 0;
    int number = 0;
    doTraversal(root, 0, &maxHeight, &substringStartIndex, &number, nullptr);
    int k;
    bool found = true;
    for (k=0; k<maxHeight; k++)
        printf("%c", text[k + substringStartIndex]);
    if(k == 0){
        printf("No repetitions found!\n");
        found = false;
    }
    if(found) {
        printf(" %d\n", number);
    }
}

int main(int argc, char *argv[]){
    int reps;
    cin >> reps;
    string s;
    for(int i = 0; i<reps; i++) {
        cin >> s ;
        s+= "$";
        strcpy(text, s.c_str());
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
        buildSuffixTree();
        getLongestRepeatedSubstring();
        freeSuffixTreeByPostOrder(root);
    }
    return 0;
}