//Project1 Normal

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXNODES 30
#define BADVALUE -1 //If a function returns BADVALUE, it tells the program that the test is false and to terminate immediately
#define NULLPOS -1 //If the index of a node is assigned as NULLPOS, it means this node is a leaf(null)
#define INTMAX 2147483647

/* The function TestCase is to
 * receive input and judge whether
 * it is a Red-Black Tree. the 
 * parameter nodes are used to
 * store the data. It prints
 * "Yes" or "No" to show the result.*/
void TestCase(int nodes[]);

/* The function Input is to
 * receive input, store them
 * in the array-type variable 
 * "nodes", and return the
 * size of the input*/
int InPut(int nodes[]);

/* This is the core function
 * of this program to judge if
 * the search tree put in is a subtree of
 * Red-Black Tree. Actually, The
 * tree is stored in an array
 * rather than a linked structure,
 * thus, extra operations are
 * needed to find the left and
 * right children. 
 * 
 * The function will be recursively 
 * called by itself with argument
 * RootIndex being the index of the root of a
 * subtree. 
 * 
 * Argument size tells the function
 * the size of nodes;
 * 
 * Argument UpBound assign the
 * least up bound of current
 * subtree;
 * 
 * Argument ReturnRightBoundIndex is a pointer
 * given by the calling function,
 * and is expected to return the
 * right bound of the tree in the
 * called function.
 */
int Judge(int nodes[],int RootIndex,int size,int UpBound,int * ReturnRightBoundIndex);

int main(){
    int nodes[MAXNODES];
    int k;
    scanf("%d",&k);
    while (k--){
        TestCase(nodes);
        if(k) putchar('\n');
    }
    return 0;
}

void TestCase(int nodes[]){
    int size=InPut(nodes);
    int buf;//It is only used to fullfil the fourth parameter(ReturnRightBoundIndex) of function Judge.
    int flag= (nodes[0]<0)? BADVALUE: Judge(nodes,0,size,INTMAX,&buf);
    if(flag!=BADVALUE) printf("Yes");
    else printf("No");
}

int InPut(int nodes[]){
    int size , i;
    scanf("%d",& size);
    for(i=0;i< size ;i++) scanf("%d", nodes +i);

    return size;
}

int Judge(int nodes[],int RootIndex,int size,int UpBound,int * ReturnRightBoundIndex){
    int LeftBlackNodes,RightBlackNodes,LeftChildIndex,RightChildIndex;
    /* LeftBlackNodes: the number of black nodes in the left subtree
     * RightBlackNodes: the number of black nodes in the right subtree
     * LeftChildIndex: the index of left child
     * RightChildIndex: the index of right child*/

    /*The root's children are both leaves(null)*/
    if(RootIndex>=size-1){
        *ReturnRightBoundIndex=NULLPOS;
        return 1+(nodes[RootIndex]>0);
    } 

    /* Judge whether root’s left child is a leaf(null) */
    if(abs(nodes[RootIndex+1])>abs(nodes[RootIndex])) LeftBlackNodes=1,LeftChildIndex=NULLPOS,RightChildIndex=RootIndex+1;

    else
    {
        LeftChildIndex=RootIndex+1;
        if(nodes[RootIndex]<0 && nodes[LeftChildIndex]<0) return BADVALUE;//Red Node's left child is not black
        LeftBlackNodes=Judge(nodes,LeftChildIndex,size,abs(nodes[RootIndex]),&RightChildIndex);
        if(LeftBlackNodes==BADVALUE) return BADVALUE;//subtree violates the rule
    }

    if(RightChildIndex==NULLPOS || abs(nodes[RightChildIndex])>=UpBound){//right child is found a leaf(null)
        RightBlackNodes=1;
        if(RightChildIndex!=NULLPOS) *ReturnRightBoundIndex=RightChildIndex;
    }
    else{
        if(nodes[RootIndex]<0 && nodes[RightChildIndex]<0) return BADVALUE;//Red Node's left child is not black
        RightBlackNodes=Judge(nodes,RightChildIndex,size,UpBound,ReturnRightBoundIndex);
        if(RightBlackNodes==BADVALUE) return BADVALUE;//subtree violates the rule
    }

    /*The property cannot be met that the numbers of black nodes
     in all simple path from the i_th node to an arbitrary decendant
     leaf are not equal.
    */
    if(LeftBlackNodes!=RightBlackNodes) return BADVALUE;
    
    return LeftBlackNodes+(nodes[RootIndex]>0);// return the number of black nodes in the simple path from the i_th node to one of its leaf.
}
