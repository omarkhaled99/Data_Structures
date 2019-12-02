#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct node
{
    char word[100];
    struct  node* left;
    struct  node* right;
} node;
typedef struct
{
    node * root;
} BSTtree;
node**arr;
int arrIndex = 0;
int Max ( int  a, int b)
{
    return(a>b)? a: b ;
}
node* constructNode(char * data)
{
    node*p = (node*)malloc(sizeof(node));
    strcpy(p->word,data);
    p ->right = NULL;
    p->left = NULL;
    return p;
}
void initialiseTree(BSTtree * tree )
{
    tree->root = NULL;
}
node * insert (node*BSTnode,char*data)
{

    if(BSTnode == NULL)
    {
        BSTnode=constructNode(data);

    }
    else if(strcmp(data,(BSTnode)->word)<0)
    {

        BSTnode -> left = insert((BSTnode)->left,data);

    }
    else if(strcmp(data,(BSTnode)->word)>0)
    {

        BSTnode -> right= insert((BSTnode)->right,data);

    }
    return BSTnode;
}
int isEmpty(BSTtree * tree)
{
    return tree->root==NULL;
}
int isLeaf(node *treeNode)
{
    return (treeNode -> right == NULL)&&(treeNode->left == NULL );
}
int height(node * BSTroot)
{
    return (BSTroot==NULL)? -1 : 1 + Max(height(BSTroot->left),height(BSTroot->right));
}
int size(node * BSTroot)
{
    return (BSTroot == NULL)? 0 : 1 + size(BSTroot->right) + size(BSTroot->left);
}
node* addFileToTree(node * p,char *fileName)
{
    char word[100];
    FILE* fp = fopen(fileName,"r");
    if(fp==NULL)
    {
        printf("error opening the file");
    }

    while(!feof(fp))
    {

        fscanf(fp,"%s\n",word);
        p  = insert(p,word);

    }
    return p;
}

char* findWord(node * p,char word[255])
{
    if(p==NULL){
        return 0;
    }
    if(strcmp(p->word,word)==0)
     {   arr[arrIndex]= p;
         arrIndex++;
        return 1;
     }
    else if(strcmp(p->word,word)>0)
      {  arr[arrIndex]= p;
         arrIndex++;
        return findWord(p->left,word);
      }
    else if(strcmp(p->word,word)<0)
       {
         arr[arrIndex]= p;
         arrIndex++;
        return findWord(p->right,word);
       }
}
void suggest(){
int j = arrIndex-1;
int flag = 0;
char*current= malloc(sizeof(char)*50);
strcpy(current,arr[j]->word);
char*successor =  malloc(sizeof(char)*50);;
char*predeccessor =  malloc(sizeof(char)*50);
while(1){
if(isLeaf(arr[j])){
if(arr[j]==arr[j-1]->left&&flag==0)
{
    strcpy(successor,arr[j-1]->word);
    flag = 1;
    break;

}else if(arr[j-1]->right==arr[j])
{
      j--;
      while(arr[j-1]->right == arr[j])
      {
          j--;
      }
      strcpy(successor,arr[j-1]->word);
      break;
}
}else{

    node*p = arr[j];
    node*temp = p;
if(p->right!=NULL){
       temp = p->right;
    while(temp->left!=NULL){
    temp = temp ->left;
    }
}

strcpy(successor,temp->word);
break;
}

}
j=arrIndex-1;
flag = 0;
while(1)
{
    if(isLeaf(arr[j])){
 if(arr[j]==arr[j-1]->right&&flag==0)
{
    strcpy(predeccessor,arr[j-1]->word);
    flag = 1;
    break;

}else if(arr[j-1]->left==arr[j])
{
      j--;
      while(arr[j-1]->left == arr[j]&&j>1)
      {
          j--;
      }
      strcpy(predeccessor,arr[j-1]->word);
      break;
}
}else{

    node*p = arr[j];
    node*temp = p;
if(p->left!=NULL){
       temp = p->left;
    while(temp->right!=NULL){
    temp = temp ->right;
    }
}

strcpy(predeccessor,temp->word);
break;
}
}
printf("%s, %s, %s\n",current,successor,predeccessor);

arrIndex = 0;
}

int main()
{
    BSTtree tree;
    initialiseTree(&tree);
    tree.root = addFileToTree(tree.root,"EN-US-randomized-unique updated.txt");
    char sentence[255];
    int treeHeight = height(tree.root) ;
    printf("Height of Tree = %d\n",treeHeight);
    printf("Size of Tree = %d\n",size(tree.root));
    printf("Input Sentence: ");
    arr = (node *) malloc(sizeof(node) * treeHeight);
    while(fgets(sentence,255,stdin)!=NULL)
    {
        sentence[strlen(sentence)-1]='\0';
        char * token = strtok(sentence," ");
        printf("Output:\n");
        while(token!=NULL)
        {
            printf("  * %s - ",token);
            if(findWord(tree.root,token)==1)
                printf("Correct\n");
            else
                {
                suggest();
                }
            token = strtok(NULL," ");

        }
         printf("Input Sentence: ");

    }

    return 0;
}
