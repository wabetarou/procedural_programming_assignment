/*calc1
  watanabe.a.aq
  akira watanabe*/

#include <stdio.h>

int main (int argc, char *argv []){
  char *p = argv [1], last_op = '+';

  if(argc != 2){            //引数が二つでない時エラー出力
    fprintf(stderr, "Usage: %s prob_file\n", argv[0]);
    return 1;
  }

  /*acc//現在の計算結果を保持。最後の結果はこれを出力。(%eax)
    num//現在、入力中の数値を保持。(%ebx)
    mem//メモリ機能で記憶する値を保持。(%ecx)
    last_op//最後に見えた演算子を保持。
    sflag//numの正負を判断する。正なら１、負なら−１。*/

  int sflag = 1;
  printf (".data\n"
          "L_fmt:\n"
          "\t.ascii \"%%d\\n\\0\"\n"
          ".text\n"
          ".globl _main\n"
          "_main:\n"
          "\tpushl %%ebp\n"
          "\tmovl %%esp, %%ebp\n");
  printf ("\tmovl  $0, %%eax\n");//acc　= 0
  printf ("\tmovl  $0, %%ebx\n");//num = 0
  printf ("\tmovl  $0, %%ecx\n");//mem = 0

  while(1){
    if(*p == '\0')break;
    switch (*p) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        printf ("\timull  $10, %%ebx\n");//num *= 10
        if(sflag == 1){
          printf ("\taddl  $%c, %%ebx\n",*p);//num += '入力'
        }else{
          printf ("\tsubl  $%c, %%ebx\n",*p);//num -= '入力'
        }
        break;
      case '+':
      case '-':
      case '*':
      case '/':
        sflag = 1;
        switch(last_op){
          case '+':
            printf("\taddl %%ebx, %%eax\n");//acc += num
            break;
          case '-':
            printf("\tsubl %%ebx, %%eax\n");//acc -= num
            break;
          case '*':
            printf("\timull %%ebx, %%eax\n");//acc *= num
            break;
          case '/':
            printf("\tcltd\n");
            printf("\tidivl %%ebx\n");//acc /= num
            break;
        }
        printf("\tmovl $0, %%ebx\n");//num = 0
        last_op = *p;
        break;
      case '=':
        switch(last_op){
          case '+':
            printf("\taddl %%ebx, %%eax\n");//acc += num
            break;
          case '-':
            printf("\tsubl %%ebx, %%eax\n");//acc -= num
            break;
          case '*':
            printf("\timull %%ebx, %%eax\n");//acc *= num
            break;
          case '/':
            printf("\tcltd\n");
            printf("\tidivl %%ebx\n");//acc /= num
            break;
        }
        printf ("\tpushl %%eax\n"
                "\tpushl $L_fmt\n"
                "\tcall  _printf\n"
                "\tleave\n"
                "\tret\n");//printf("%d\n",acc);
        break;
      case 'P':
        sflag = 1;
        switch(last_op){
          case '+':
            printf("\taddl %%ebx, %%eax\n");//acc += num
            break;
          case '-':
            printf("\tsubl %%ebx, %%eax\n");//acc -= num
            break;
          case '*':
            printf("\timull %%ebx, %%eax\n");//acc *= num
            break;
          case '/':
            printf("\tcltd\n");
            printf("\tidivl %%ebx\n");//acc /= num
            break;
        }
        printf("\taddl %%eax, %%ecx\n");//mem += acc;
        printf("\tmovl  $0, %%eax\n");//acc　= 0
        printf("\tmovl  $0, %%ebx\n");//num = 0
        last_op = '+';
        break;
      case 'M':
        sflag = 1;
        switch(last_op){
          case '+':
            printf("\taddl %%ebx, %%eax\n");//acc += num
            break;
          case '-':
            printf("\tsubl %%ebx, %%eax\n");//acc -= num
            break;
          case '*':
            printf("\timull %%ebx, %%eax\n");//acc *= num
            break;
          case '/':
            printf("\tcltd\n");
            printf("\tidivl %%ebx\n");//acc /= num
            break;
        }
        printf ("\tsubl %%eax, %%ecx\n");//mem -= acc;
        printf ("\tmovl  $0, %%eax\n");//acc　= 0
        printf ("\tmovl  $0, %%ebx\n");//num = 0
        break;
      case 'R':
        printf ("\tpushl %%ecx\n"
                "\tpushl $L_fmt\n"
                "\tcall  _printf\n"
                "\tleave\n"
                "\tret\n");//printf("%d\n",mem);
        break;
      case 'C':
        printf("\tmovl  $0, %%ecx\n");//mem = 0;
        break;
      case 'S':
        printf("\tneg %%ebx\n");//num = -num;
        sflag *= -1;
        break;
      default:
        printf("\"%c\" is wrong.",*p);
        return 1;
    }
    p++;
  }
  return 0;
}
