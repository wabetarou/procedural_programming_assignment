/*calc3
  watanabe.a.aq
  akira watanabe*/

#include <stdio.h>

int main (int argc, char *argv []){
  char *p = argv [1], last_op = '+';

  if(argc != 2){            //引数が二つでない時エラー出力
    fprintf(stderr, "Usage: %s prob_file\n", argv[0]);
    return 1;
  }

  int sflag = 1;
  printf (".data\n"
          "L_fmt:\n"
          "\t.ascii \"%%d\\n\\0\"\n"
          ".text\n"

          ".globl _mul\n"//acc *= num
          "_mul:\n"
          "\tpushl %%ebp\n"
          "\tmovl %%esp, %%ebp\n"
          "\tmovl $1, %%edx\n"
          "\tcmpl $0, %%eax\n"
          "\tjge Lm1\n"
          "\tneg %%eax\n"
          "\tneg %%edx\n"
          "Lm1:\n"
          "\tcmpl $0, %%ebx\n"
          "\tjge Lm2\n"
          "\tneg %%ebx\n"
          "\tneg %%edx\n"
          "Lm2:\n"
          "\tpushl %%eax\n"//(%esp)
          "\tmovl $0, %%eax\n"//acc = 0
          "Lm3:\n"
          "\tshr %%ebx\n"
          "\tjnc Lm4\n"
          "\taddl (%%esp), %%eax\n"
          "Lm4:\n"
          "\tsall (%%esp)\n"
          "\tcmpl $0, %%ebx\n"
          "\tjne Lm3\n"
          "\tcmpl $1, %%edx\n"
          "\tje Lm5\n"
          "\tneg %%eax\n"
          "Lm5:\n"
          "\tleave\n"
          "\tret\n"

          ".globl _div\n"//acc /= num
          "_div:\n"
          "\tpushl %%ebp\n"
          "\tmovl %%esp, %%ebp\n"
          "\tmovl $1, %%edx\n"
          "\tcmpl $0, %%eax\n"
          "\tjge Ld1\n"
          "\tneg %%eax\n"
          "\tneg %%edx\n"
          "Ld1:\n"
          "\tcmpl $0, %%ebx\n"
          "\tjge Ld2\n"
          "\tneg %%ebx\n"
          "\tneg %%edx\n"
          "Ld2:\n"
          "\tpushl %%edx\n"//12(%esp)
          "\tpushl %%eax\n"//8(%esp)
          "\tpushl %%eax\n"//4(%esp)
          "\tpushl $0\n"//(%esp)
          "\tmovl $0, %%eax\n"//acc = 0
          "\tmovl $0, %%edx\n"
          "Ld3:\n"
          "\tsall 4(%%esp)\n"//分母を左シフト
          "\tjnc Ld4\n"
          "\tinc %%eax\n"//CF=1なら%eaxをインクリメント
          "\tinc %%edx\n"//%%edxも
          "Ld4:\n"
          "\tcmp %%ebx, %%eax\n"
          "\tjnge Ld5\n"//if(num>(%eax))ならジャンプ
          "\tincl (%%esp)\n"//割れたら商をインクリメント
          "\tsubl %%ebx, %%eax\n"//筆算の引く部分
          "Ld5:\n"
          "\tcmpl 8(%%esp), %%edx\n"
          "\tje Ld6\n"
          "\tsal %%eax\n"//筆算右の余り部分を左シフト
          "\tsal %%edx\n"//分母の進み具合を左シフト
          "\tsall (%%esp)\n"//商を左シフト
          "\tjmp Ld3\n"
          "Ld6:\n"
          "\tcmpl $1, 12(%%esp)\n"
          "\tje Ld7\n"
          "\tnegl (%%esp)\n"
          "Ld7:"
          "\tpopl %%eax\n"
          "\tleave\n"
          "\tret\n"

          /*_main
            acc//現在の計算結果を保持。最後の結果はこれを出力。(%eax)
            num//現在、入力中の数値を保持。(%ebx)
            mem//メモリ機能で記憶する値を保持。(%ecx)
            last_op//最後に見えた演算子を保持。
            sflag//numの正負を判断する。正なら１、負なら−１。*/

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
        printf ("\tsal %%ebx\n"
                "\tpushl %%ebx\n"
                "\tsal %%ebx\n"
                "\tsal %%ebx\n"
                "\taddl %%ebx, (%%esp)\n"
                "\tpopl %%ebx\n");//num *= 10
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
            printf("\tcall _mul\n");
            break;
          case '/':
            printf("\tcall _div\n");//acc /= num
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
            printf("\tcall _mul\n");//acc *= num
            break;
          case '/':
            printf("\tcall _div\n");//acc /= num
            break;
        }
        printf ("\tpushl %%eax\n"
                "\tpushl $L_fmt\n"
                "\tcall  _printf\n"
                "\tleave\n"
                "\tret\n");//printf("%d\n",acc);
        printf ("\tmovl  $0, %%eax\n");//acc = 0;
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
            printf("\tcall _mul\n");//acc *= num
            break;
          case '/':
            printf("\tcall _div\n");//acc /= num
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
            printf("\tcall _mul\n");//acc *= num
            break;
          case '/':
            printf("\tcall _div\n");//acc /= num
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
      /*default:
        printf("\"%c\" is wrong.",input);
        return 1;*/
    }
    p++;
  }
  return 0;
}
