/*calc0
  watanabe.a.aq
  akira watanabe*/

#include <stdio.h>

int main (int argc, char *argv []){
  char *p = argv [1], input ,last_op = '+';
  int  num = 0 , acc = 0 , mem = 0;

  if(argc != 2){            //引数が二つでない時エラー出力
    fprintf(stderr, "Usage: %s prob_file\n", argv[0]);
    return 1;
  }

  /*変数はnum,acc,last_opを用意した。
  それぞれint型,int型,char型
  inputは入力を一文字ずつchar型で繰り返し使用し格納している
  */
  while(1){
    if(*p == '\0')break;
    input = *p++;
    switch (input) {
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
        if(num >= 0){
          num = num * 10 + (input - '0');
        }else{
          num = num * 10 - (input - '0');
        }
        break;
      case '+':
      case '-':
      case '*':
      case '/':
        /*if(num == 0){
          last_op = input;
          break;
        }*/
        switch(last_op){
          case '+':
            acc += num;
            break;
          case '-':
            acc -= num;
            break;
          case '*':
            acc *= num;
            break;
          case '/':
            acc /= num;
            break;
        }
        num = 0;
        last_op = input;
        break;
      case '=':
        switch(last_op){
          case '+':
            acc += num;
            break;
          case '-':
            acc -= num;
            break;
          case '*':
            acc *= num;
            break;
          case '/':
            acc /= num;
            break;
        }
        num = 0;
        last_op = '+';
        printf("%d\n",acc);
        acc = 0;
        break;
      case 'P':
        if(num != 0){
          switch(last_op){
            case '+':
              acc += num;
              break;
              case '-':
              acc -= num;
              break;
            case '*':
              acc *= num;
              break;
           case '/':
             acc /= num;
             break;
          }
        }
        mem += acc;
        num = 0;
        acc = 0;
        last_op = '+';
        break;
      case 'M':
        if(num != 0){
          switch(last_op){
            case '+':
              acc += num;
              break;
              case '-':
              acc -= num;
              break;
            case '*':
              acc *= num;
              break;
           case '/':
             acc /= num;
             break;
          }
        }
        mem -= acc;
        num = 0;
        acc = 0;
        break;
      case 'R':
        num = mem;
        printf("%d\n",mem);
        break;
      case 'C':
        mem = 0;
        break;
      case 'S':
        num = -num;
        break;
      default:
        printf("\"%c\" is wrong.",input);
        return 1;
    }
  }
  return 0;
}
