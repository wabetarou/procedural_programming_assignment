/*2q-final-3
  watanabe.a.aq
  akira watanabe*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define WORD 21//ヌル文字を含める
#define SIZE 1002//改行,NULL文字を含める

typedef struct tnode{//二分探索木のノード
  char data[WORD];//文字列配列
  struct tnode *left;//左の子
  struct tnode *right;//右の子
  struct lnode *pos;//ポスティングへのポインタ
}tnode;

typedef struct lnode {//ポスティングのノード
  int docid;//文書番号
  struct lnode *next;//次のノード
}lnode;

typedef struct rnode {//結果として表示するリストのノード
  struct lnode *list;//リストのノード
  struct rnode *next;//次のノード
}rnode;

tnode *insertTerm(tnode *p,char *str,int id);//ノードを二分木に挿入する
tnode *createTNode(char *str,int id);//葉に新しいノードを繋げる
void freeTree(tnode *p);//二分木のメモリを解放する
lnode *insertList(lnode *q,int id);//ポスティングリストにノードを追加する
lnode *createLNode(int id);//ポスティングリストのノードを作成する
lnode *search(tnode *p,char *str);
//二分探索木を走査しクエリと合致するポスティングリストを検索
void printList(rnode **firstList);//論理式の結果によって表されるリストのIDを全て出力する
void freeList(lnode *q);//ポスティングリストのメモリの開放を行う
void pushList(rnode **firstList,lnode *q);
//与えられたポスティングリストをスタックに格納する
lnode *popList(rnode **firstList);
//スタックからポスティングリストをpopして返す
lnode *doAND(lnode *l1,lnode *l2);
//演算子ANDを行う関数,スタックの上から二つをpopし、lnode型のリストを返す
lnode *doOR(lnode *l1,lnode *l2);
//演算子ORを行う関数,スタックの上から二つをpopし、lnode型のリストを返す
lnode *doNOT(lnode *l1,lnode *l2);
//演算子NOTを行う関数,スタックの上から二つをpopし、lnode型のリストを返す
lnode *combine(lnode *l1,lnode *l2);//第一引数のリストに第二引数のリストをつなげる



int main(int argc, char **argv){
  int n,count;//countは文書の文字数
  char *fname,*str,word[WORD];
  /*fnameはファイルネーム、strは文書の中の一単語、
  docは一つの文書を格納する、wordは入力した文字列*/
  FILE *fp;//読み込むファイル
  tnode *root = NULL;//二分木の根

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
    char doc[SIZE] = {0};//docの初期化
    fgets(doc,SIZE,fp);//docに文書を読みこむ
    count = strlen(doc);//countは文書の文字数
    doc[count-1] = '\0';//文書の最後の改行をナル文字にする


    str = strtok(doc," ");//strは文書内の単語
    root = insertTerm(root,str,n);//二分探索木への単語の追加


    while(1){
      str = strtok(NULL," ");
      if(str  == NULL)break;
      root = insertTerm(root,str,n);//ファイルの終わりまで二分木に挿入を繰り返す
    }

  }

  rnode *firstList = NULL;//スタックの目印


  while(scanf("%s",word) != EOF){//文字列を入力
    if(strcmp(word,"STOP") == 0)break;////////////////////////////
    if(strcmp(word,"AND") == 0){//ANDが入力された場合
      pushList(&firstList,doAND(popList(&firstList),popList(&firstList)));
      /*スタックの上から一番目と二番目の共通ノードによるリストをスタックに入れる
      この時元の一番目と二番目はスタックから消える*/
    }else if(strcmp(word,"OR") == 0){//ORが入力された場合
      pushList(&firstList,doOR(popList(&firstList),popList(&firstList)));
      /*スタックの上から一番目と二番目のリストに含まれる全てのノードを
      要素とするリストをスタックに入れる。この時元の一番目と二番目はスタックから消える*/
    }else{
      pushList(&firstList,(search(root,word)));
      //ANDやOR以外の単語の場合、その単語のリストをスタックに入れる
    }
  }

  printList(&firstList);//論理式の結果によって表されるリストのIDを全て出力する

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
    p->pos = insertList(p->pos,id);
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
  p->pos = createLNode(id);
  return p;
}


void freeTree(tnode *p){//二分木のメモリを解放する関数
  if(p == NULL)return;
  freeTree(p->left);//帰りがけ順になるように再帰する
  freeTree(p->right);
  freeList(p->pos);
  free(p);
}

lnode *insertList(lnode *q,int id){//ポスティングリストにノードを追加する関数
  if(q == NULL){
    q = createLNode(id);//リストの末端なら新たにノードを作成する
  }else if(id != q->docid){
    q->next = insertList(q->next,id);
    //リストの末端でないならリストの末端まで移動するように再帰する
  }
  return q;
}

lnode *createLNode(int id){//ポスティングリストのノードを作成する関数
  lnode *q;
  q = malloc(sizeof(lnode));
  if(q == NULL)exit(1);
  q->docid = id;//文書番号
  q->next = NULL;//次のノードはNULLにしておく
  return q;
}

lnode *search(tnode *p,char *str){
  //二分探索木を走査しクエリと合致するポスティングリストを検索
  while(p != NULL){
    if(strcmp(p->data,str) == 0){//合致したらそのポスティングリストを返す
      return p->pos;
    }else if(strcmp(p->data,str) > 0){//辞書並び的に小さければ左側の枝から探す
      p = p->left;
    }else if(strcmp(p->data,str) < 0){//辞書並び的に大きければ右側の枝から探す
      p = p->right;
    }
  }
  return NULL;//合致する葉がなかった場合NULLを返す
}


void freeList(lnode *q){
  if(q == NULL) return;
  freeList(q->next);
  free(q);
}


void pushList(rnode **firstList,lnode *q){
  //与えられたポスティングリストをスタックに格納する
  rnode *new = malloc(sizeof(lnode));
  if(new == NULL)exit(1);
  new->list = q;
  new->next = *firstList;
  *firstList = new;
}

lnode *popList(rnode **firstList){
  //スタックからポスティングリストをpopして返す
  lnode *q = malloc(sizeof(lnode));
  if(q == NULL)exit(1);
  rnode *tmp = *firstList;//tmpは*firstのコピー
  if(tmp == NULL) exit(1);
  q = tmp->list;//vにtmpの指す数字をtmp代入
  *firstList = tmp->next;//firstをひとつ戻す
  free(tmp);
  return q;
}

lnode *doAND(lnode *l1,lnode *l2){//演算子ANDを行う関数,新たにlnode型のリストを返す

  if(l1 == NULL || l2 == NULL)return NULL;//どちらかリストなしならNULLを返す

  lnode *new = malloc(sizeof(lnode));//結果として返すリスト
  if(new == NULL)exit(1);
  new = NULL;

  while(1){
    if(l1->docid > l2->docid){//IDの小さい方を見て
      if(l2->next == NULL)return new;//先がもうないならnewを返す
      l2 = l2->next;//先があれば次と比べる
    }else if(l1->docid < l2->docid){
      if(l1->next == NULL)return new;
      l1 = l1->next;
    }else{//IDが同じ場合
      new = insertList(new,l1->docid);//newに同じIDのノードをつなげる
      if(l1->next == NULL || l2->next == NULL)return new;
      //どちらかの続きがなければnewを返す
      l1 = l1->next;//続きがあれば次に動く
      l2 = l2->next;
    }
  }
}


lnode *doOR(lnode *l1,lnode *l2){//演算子ORを行う関数,新たにlnode型のリストを返す

  if(l1 == NULL)return l2;//l1がNULL、もしくは両方NULLならl2を返す
  if(l2 == NULL)return l1;//l2がNULLならl1を返す


  lnode *new = malloc(sizeof(lnode));//結果として返すリスト
  if(new == NULL)exit(1);
  new = NULL;

  while(1){
    if(l1->docid > l2->docid){//IDの小さい方を見て
      new = insertList(new,l2->docid);//newにノードつなげる
      if(l2->next != NULL){//l2に続きがあるなら次へ動く
        l2 = l2->next;
      }else{
        return combine(new,l1);//l2に続きがないならnewにl1の残りを全てつなげる
      }
    }else if(l1->docid < l2->docid){//上と同様
      new = insertList(new,l1->docid);
      if(l1->next != NULL){
        l1 = l1->next;
      }else{
        return combine(new,l2);
      }
    }else{//IDが同じ場合
      new = insertList(new,l1->docid);//ノードを追加して
      if(l1->next == NULL && l2->next == NULL)return new;
      //どちらも続きがなければnewを返す
      if(l1->next != NULL){
        l1 = l1->next;//続きがあれば次へ行く
      }
      if(l2->next != NULL){
        l2 = l2->next;
      }
    }
  }
}

lnode *combine(lnode *l1,lnode *l2){//第一引数のリストに第二引数のリストをつなげる
  if(l1->next != NULL)exit(1);
  //l1の先がNULLでない場合は止める
  lnode *tmp = l1;
  while(l2 != NULL){
    tmp = tmp->next;
    tmp->docid = l2->docid;
    l2 = l2->next;
  }
  return l1;
}

lnode *doNOT(lnode *l1,lnode *l2){//演算子NOTを行う関数,新たにlnode型のリストを返す

  if(l1 == NULL)return NULL;//どちらかリストなしならNULLを返す
  if(l2 == NULL)return l1;//

  lnode *new = malloc(sizeof(lnode));//結果として返すリスト
  if(new == NULL)exit(1);
  new = NULL;

  while(1){
    if(l1->docid > l2->docid){//l2のIDの方が小さい時はl2を次に動かす
      l2 = l2->next;
      if(l2 == NULL)return combine(new,l1);
      //l2がNULLになった時はl1の残りをnewにつなげる
    }
    if(l1->docid < l2->docid){//l1のIDの方が小さい時はそのIDをnewに入れる
      new = insertList(new,l1->docid);
      l1  = l1->next;
      if(l1 == NULL)return new;//l1がNULLになった時はnewを返す
    }
    if(l1->docid == l2->docid){//同じ時はl1とl2をそのまま次に動かす
      l1 = l1->next;
      if(l1 == NULL)return new;
      l2 = l2->next;
      if(l2 == NULL)return combine(new,l1);
    }
  }
}

void printList(rnode **firstList){
  //論理式の結果によって表されるリストのIDを全て出力する
  int v;
  if((*firstList)->list == NULL) {//リストがなければNot found
    printf("Not found");
    return;
  }
  lnode *q = (*firstList)->list;
  if(q==NULL)exit(1);
  while(q != NULL){//リストがあればIDを改行区切りで順に出力していく
    v = q->docid;
    printf("%d\n",v);
    q = q->next;
  }
}
