#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define CONSTANT 100

typedef int elementtype; 

struct list_el{
    elementtype element;
    struct list_el *next;
    struct list_el *prev;
};
typedef struct list_el dblist;

void makeNullList(dblist **root,dblist **cur,dblist **tail){
    *root=NULL;
    *cur=NULL;
    *tail=NULL;
}

dblist* makeNewNode(elementtype data){
    dblist *New = (dblist*)malloc(sizeof(dblist));
    New->element=data;
    New->next = NULL;
    New->prev = NULL;
    return New;
}

void displayNode(dblist* p){ //Must fix
    if(p==NULL){
        printf("ERROR pointer NULL\n");
        return;
    }
    printf(", %d",p->element);
}

void traverseList(dblist *root){
	dblist *cur;
    for(cur=root;cur!=NULL;cur=cur->next)
        displayNode(cur);
}

void appendList(elementtype data,dblist **root,dblist **cur,dblist **tail){
	dblist* New=makeNewNode(data);
    if((*root)==NULL){
   	    (*root)=New;
 		(*tail)=New;
 		(*cur)=(*root);
 		New->next = New->prev = NULL;
    } else if(!((*tail)->element==New->element)){
  	        New->prev=(*tail);
  	        (*tail)->next=New;
  	        (*tail)=(*cur)=New;
  	        New->next = NULL;
	}
}

void freeNode(dblist **root){
	dblist *to_free;
	for(to_free=*root;to_free!=NULL;to_free=*root){
    *root=to_free->next;
    free(to_free);
  }
}

//BST

typedef struct elm{
	char word[50];
	int appearCount;
	dblist *rootLine, *curLine, *tailLine;
}elmType;

typedef struct node_type{
    elmType element;
    struct node_type *left,*right;
}nodeType;

typedef nodeType *treetype;//treetype a <=> nodeType* a

void makeNullTree(treetype* N){
    (*N)=NULL;
}

nodeType* Create_Node(elmType data){
    nodeType* New = (nodeType*)malloc(sizeof(nodeType));
    if(New!=NULL){
	    New->element=data;
	    New->left=NULL;
	    New->right=NULL;
    }
    return New;
}

int isEmptyTree(treetype N){
	return N==NULL;
}

int isLeaf(treetype N){
	if(isEmptyTree(N)){
		return 0;
	}
	else return(N->left==NULL&&N->right==NULL);
}

int compare(elmType a, elmType b){
	if(strcmp(a.word,b.word	)>0)return 1;
	else if(strcmp(a.word,b.word)<0) return -1;
	else return 0;
}

void insertNode(treetype* T,elmType data){
	if(*T==NULL) (*T)=Create_Node(data);
	else {
		if(compare(data,(*T)->element)==1)insertNode(&(*T)->right,data);
		else insertNode(&(*T)->left,data);
	}
}

void inOrderPrint(treetype T){
	if(T!=NULL){
		inOrderPrint(T->left);
		printf("%s %d", T->element.word, T->element.appearCount);
		traverseList(T->element.rootLine);
		printf("\n");
		inOrderPrint(T->right);
		
	}
}

treetype searchT(treetype T, elmType x){//Search
	if(T==NULL) return T;
	if(compare(x,T->element)==0) return T;
	else if(isLeaf(T))return NULL;
	else if(compare(x,T->element)==1)return searchT(T->right,x);
	else return searchT(T->left,x);
}

void freeTree(treetype T){
	if(T==NULL) return;
	freeTree(T->left);
	freeTree(T->right);
	freeNode(&(T->element.rootLine));
	free((void*)T);
}


treetype searchTbyWord(treetype T, char* word){//Search
	elmType wordData;
	strcpy(wordData.word, word);
	return searchT(T, wordData);
}

void addWord(treetype* wordTree ,char *word, int line){
	treetype curWord = searchTbyWord(*wordTree, word);
	if(curWord==NULL){//new
		elmType wordData;
		strcpy(wordData.word, word);
		wordData.appearCount=1;
		makeNullList(&(wordData.rootLine), &(wordData.curLine), &(wordData.tailLine));
		appendList(line, &(wordData.rootLine), &(wordData.curLine), &(wordData.tailLine));
		insertNode(wordTree, wordData);
	}
	else{
		curWord->element.appearCount++;
		appendList(line, &(curWord->element.rootLine), &(curWord->element.curLine), &(curWord->element.tailLine));
	}
}

void readFile(char* fileName ,treetype* wordTree, treetype* stopWTree){
	char c, prevC;
	int count, line;
	char word[20];
	bool idvN, isWord;
	FILE *f=fopen(fileName,"r");
	if(f==NULL){
		printf("Cannot open %s\n", fileName);
		return;
	}
    count=0, line=1, isWord = false, idvN = false;
	for(prevC='z';(c=fgetc(f))!=EOF; prevC = c){
		if('A'<=c&&c<='Z'){
			c+=32;
			if(prevC<'a'||prevC>'z'){
				idvN=true;
			}
		}

		if((c<'a' || c>'z')&&c!='\''){
			if(!idvN && isWord){
				word[count]='\0';
				if(searchTbyWord(*stopWTree, word)==NULL){
					addWord(wordTree, word, line);
				}
			}

			count=0;
			idvN=false;
			isWord=false;

			if(c=='\n'){
				line++;
			}
		} else {
			if(!isWord) isWord=true;
			word[count++]=c;
		}
	}
	fclose(f);
}

int main(int argc, char *argv[]){
	treetype wordTree, stopWTree;
	makeNullTree(&wordTree);
	makeNullTree(&stopWTree);
	if(argc<3) printf("Wrong command! Please try again\n");
	readFile(argv[1], &stopWTree, &wordTree);

	readFile(argv[2], &wordTree, &stopWTree);

	inOrderPrint(wordTree);

	freeTree(wordTree);
	freeTree(stopWTree);
	return 0;
}