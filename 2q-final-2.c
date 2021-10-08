/*2q-final-1
 watanabe.a.aq
 akira watanabe*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 21//ヌル文字を含める

typedef struct tnode{//二分探索木のノード
 char data[SIZE];//文字列配列
 struct tnode *left;//左の子
 struct tnode *right;//右の子
}tnode;

tnode *insertTerm(tnode *p,char *str);//ノードを二分木に挿入する関数
tnode *createTNode(char *str);//葉に新しいノードを繋げる関数
void printTree(tnode *p);//ノードの文字列を通りがけ順に出力していく関数
void freeTree(tnode *p);//二分木のメモリを解放する関数


int main(int argc, char **argv){
 char *fname,str[SIZE];
 tnode *root = NULL;
 FILE *input;

 if(argc != 2){            //引数が二つでない時エラー出力
   fprintf(stderr, "Usage: %s prob_file\n", argv[0]);
 }

 fname = argv[1];

 input = fopen(fname,"r");

 if(input == NULL){             //指定のファイルがない時エラー出力
   fprintf(stderr, "error opening file!\n");
   return 1;
 }


 while(fscanf(input,"%s",str) != EOF){
   root = insertTerm(root,str);//ファイルの終わりまで二分木に挿入を繰り返す
 }

 printTree(root);//通りがけ順に二分木のノードを出力
 freeTree(root);//二分木のメモリ解放

 return 0;
}


tnode *insertTerm(tnode *p,char *str){//ノードを二分木に挿入する関数
 if(p == NULL){
   p = createTNode(str);//今見ているのが葉の先ならそこに新しくノードを繋げる
 }else if(strcmp(p->data,str) > 0){
   p->left = insertTerm(p->left,str);
   //今見ているノードの文字列が新しい文字より大きいなら新しいノードは左側
 }else if(strcmp(p->data,str) < 0){
   p->right = insertTerm(p->right,str);
   //今見ているノードの文字列が新しい文字より小さいなら新しいノードは右側
 }
 return p;
}

tnode *createTNode(char *str){//葉に新しいノードを繋げる関数
 tnode *p;
 p = malloc(sizeof(tnode));
 if(p == NULL)exit(1);//メモリが足りないなら異常終了
 strcpy(p->data,str);//新しい文字列をノードにコピー
 p->left = NULL;//ノードの先はNULLにしておく
 p->right = NULL;
 return p;
}

void printTree(tnode *p){//葉に新しいノードを繋げる関数
 if(p == NULL)return;
 printTree(p->left);//通りがけ順になるように再帰する
 printf("%s\n",p->data);
 printTree(p->right);
}

void freeTree(tnode *p){//二分木のメモリを解放する関数
 if(p == NULL)return;
 freeTree(p->left);//帰りがけ順になるように再帰する
 freeTree(p->right);
 free(p);
}
