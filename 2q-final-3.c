/*2q-final-3
  watanabe.a.aq
  akira watanabe*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define WORD 21//ヌル文字を含める
#define SIZE 1002

typedef struct Node {
  char *data;
  struct Node *next;
} Node;

typedef struct tnode{//二分探索木のノード
  char data[WORD];//文字列配列
  struct tnode *left;//左の子
  struct tnode *right;//右の子
  struct lnode *pos;//ポスティングへのポインタ
}tnode;

typedef struct lnode {//ポスティングのノード
  int docid;//文書番号
  char data[WORD];//単語
  struct lnode *next;//次のノード
}lnode;

typedef struct inode{
  int *data;
  struct inode *next;
}inode;

tnode *insertTerm(tnode *p,char *str,int id);//ノードを二分木に挿入する関数
tnode *createTNode(char *str,int id);//葉に新しいノードを繋げる関数
void freeTree(tnode *p);//二分木のメモリを解放する関数
lnode *insertList(lnode *q,char *str,int id);
lnode *createLNode(char *str,int id);
lnode *search(tnode *p,char *str);
void freeList(lnode *q);
void pushList(inode **firstList,int *a);
//char popList(Node **firstList);
int *doAND(int *l1,int *l2);
int *doOR(int *l1,int *l2);
int countList(lnode *q);//
int *copyList(lnode *q);
int *popList(inode **firstList);
void printList(inode **firstList);
int *combine(int *a,int *b);


int flagprint = 0;

int main(int argc, char **argv){
  int n,count;//countは文書の文字数
  char *fname,*str,word[WORD];
  /*fnameはファイルネーム、strは文書の中の一単語、
  docは一つの文書を格納する、wordは入力した文字列*/
  tnode *root = NULL;//二分木の根
  FILE *fp;//読み込むファイル

  if(argc != 2){            //引数が二つでない時エラー出力
    fprintf(stderr, "Usage: %s prob_file\n", argv[0]);
  }

  fname = argv[1];

  fp = fopen(fname,"r");

  if(fp == NULL){             //指定のファイルがない時エラー出力
    fprintf(stderr, "error opening file!\n");
    return 1;
  }



  while(fscanf(fp,"%d\t",&n) != EOF){
    /*文書番号を読み込んでからタブ文字を読み飛ばす
    ファイルの終わりまで行ったら繰り返し終了*/
    char doc[SIZE] = {0};//
    fgets(doc,SIZE,fp);//docに文書を読みこむ
    count = strlen(doc);//countは文書の文字数
    doc[count-1] = '\0';//文書の最後の改行をナル文字にする


    str = strtok(doc," ");//文書内の単語
    root = insertTerm(root,str,n);//二分探索木への単語の追加


    while(1){
      str = strtok(NULL," ");
      if(str  == NULL)break;
      root = insertTerm(root,str,n);//ファイルの終わりまで二分木に挿入を繰り返す
    }

  }

  inode *firstList = NULL;

  int flag = 0;
  while(scanf("%s",word) != EOF){//文字列を入力
  if(strcmp(word,"STOP") == 0)break;
  flag++;
    if(strcmp(word,"AND") == 0){
    //  if(flag < 2)exit(1);
      pushList(&firstList,doAND(popList(&firstList),popList(&firstList)));
    }else if(strcmp(word,"OR") == 0){
      pushList(&firstList,doOR(popList(&firstList),popList(&firstList)));
    }else{
      pushList(&firstList,(copyList(search(root,word))));
    }
  }

  printList(&firstList);


  freeTree(root);//二分木のメモリ解放

  return 0;
}



tnode *insertTerm(tnode *p,char *str,int id){//ノードを二分木に挿入する関数
  if(p == NULL){
    p = createTNode(str,id);//今見ているのが葉の先ならそこに新しくノードを繋げる
  }else if(strcmp(p->data,str) > 0){
    p->left = insertTerm(p->left,str,id);
    //今見ているノードの文字列が新しい文字より大きいなら新しいノードは左側
  }else if(strcmp(p->data,str) < 0){
    p->right = insertTerm(p->right,str,id);
    //今見ているノードの文字列が新しい文字より小さいなら新しいノードは右側
  }else if(strcmp(p->data,str) == 0){
    p->pos = insertList(p->pos,str,id);
  }
  return p;
}

tnode *createTNode(char *str,int id){//葉に新しいノードを繋げる関数
  tnode *p;
  p = malloc(sizeof(tnode));
  if(p == NULL)exit(1);//メモリが足りないなら異常終了
  strcpy(p->data,str);//新しい文字列をノードにコピー
  p->left = NULL;//ノードの先はNULLにしておく
  p->right = NULL;
  p->pos = createLNode(str,id);
  return p;
}


void freeTree(tnode *p){//二分木のメモリを解放する関数
  if(p == NULL)return;
  freeTree(p->left);//帰りがけ順になるように再帰する
  freeTree(p->right);
  freeList(p->pos);
  free(p);
}

lnode *insertList(lnode *q,char *str,int id){
  if(q == NULL){
    q = createLNode(str,id);
  }else if(id != q->docid){
    q->next = insertList(q->next,str,id);
  }
  return q;
}

lnode *createLNode(char *str,int id){
  lnode *q;
  q = malloc(sizeof(lnode));
  if(q == NULL)exit(1);
  strcpy(q->data,str);
  q->docid = id;//文書番号
  q->next = NULL;//次のノードはNULLにしておく
  return q;
}

lnode *search(tnode *p,char *str){
  while(p != NULL){
    if(strcmp(p->data,str) == 0){
      return p->pos;
      break;
    }else if(strcmp(p->data,str) > 0){
      p = p->left;
    }else if(strcmp(p->data,str) < 0){
      p = p->right;
    }
  }
  return NULL;
}



void freeList(lnode *q){
  if(q == NULL) return;
  freeList(q->next);
  free(q);
}


void pushList(inode **firstList,int *a){
  //与えられた整数をスタックに格納する
  inode *new = malloc(sizeof(inode));
  if(new == NULL)exit(1);
  new->data = a;
  new->next = *firstList;
  *firstList = new;
}

int *popList(inode **firstList){
  //スタックから整数をpopして標準出力に出力する
  int *v;
  inode *tmp = *firstList;//tmpは*firstのコピー
  if(tmp == NULL) exit(1);
  v = tmp->data;//vにtmpの指す数字をtmp代入
  *firstList = tmp->next;//firstをひとつ戻す
  free(tmp);
  return v;
}

int *doAND(int *l1,int *l2){//演算子ANDを行う関数,新たにlnode型のリストを返す

  if(l1 == NULL || l2 == NULL)return NULL;


  int *new = malloc(sizeof(l1) + sizeof(l2));
  if(new == NULL)exit(1);

  int i = 0,j = 0,n = 0;

  while(1){
    if(*l1 == 0)return l1;
    if(*l2 == 0)return l2;
    if(l1[i] > l2[j]){
      if(l2[j+1] == 0)return new;
      j++;
    }else if(l1[i] < l2[j]){
      if(l1[i+1] == 0)return new;
      i++;
    }else{
      new[n] = l1[i];
      n++;
      if(l1[i+1] == 0 || l2[j+1] == 0)return new;
      i++;
      j++;
    }
  }
}

int *doOR(int *l1,int *l2){

  if(l1 == NULL || l2 == NULL)return NULL;

  int *new = malloc(sizeof(l1) + sizeof(l2));
  if(new == NULL)exit(1);

  int i = 0,j = 0,n = 0;



  while(1){
    if(l1[i] == 0)return l2;
    if(l2[j] == 0)return l1;
    if(l1[i] >= l2[j]){
      new[n] = l2[j];
      n++;
      if(l2[j+1] != 0){
        j++;
      }else{
        return combine(new,l1);
      }
    }else if(l1[i] < l2[j]){
      new[n] = l1[i];
      n++;
      if(l1[i+1] != 0){
        i++;
      }else{
        return combine(new,l2);
      }
    }
  }
}

int countList(lnode *q){
  int count = 0;
  lnode *tmp = q;
  while(tmp != NULL){
    tmp = tmp->next;
    count++;
  }
  return count;
}

int *copyList(lnode *q){
  int i = 0;
  int *v = malloc(sizeof(int) * (countList(q)+1));
  while(q != NULL){
    *(v+i) = q->docid;
    q = q->next;
    i++;
  }
  *(v+i) = 0;
  return v;
}

void printList(inode **firstList){
  //現在のスタックの内容を先頭から順にスペース区切りで標準出力に出力する。
  if(*(*firstList)->data == 0) {//
    printf("Not found");
    return;
  }
  int *tmp = (*firstList)->data;

  int i = 0;


  while(*(tmp+i) != 0){
    printf("%d\n",*(tmp+i));
    i++;
    flagprint++;
  }
}

int *combine(int *a,int *b){
  int *new = malloc(sizeof(a) + sizeof(b));
  if(new == NULL)exit(1);

  int i = 0,n = 0;
  while(a[i] != 0){
    new[n] = a[i];
    n++;
    i++;
  }
  while(b[i] != 0){
    new[n] = a[i];
    n++;
    i++;
  }
  new[n] = 0;
  return new;
}
