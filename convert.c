#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define Ture 1
#define False 0

main(){
char input[4]="";
char *hex="";
int dec;
int binary[16]= {False};
int i,j;

printf("please enter the value to be convert:");
while(scanf("%s",input)!=EOF){
dec=0;
if(input[0]=='0'&&input[1]=='x'){
    if (input[4]!='\0')printf("the entered data excess the memory\n");
   else{
         if(input[2]>='0'&&input[2]<='9')dec=(input[2]-'0')*16;
        else if(input[2]>='A'&&input[2]<='F')dec=(input[2]-'A'+10)*16;
          else printf("The input hex value is invalid!\n");

          if(input[3]>='0'&&input[3]<='9')dec=(input[3]-'0')+dec;
          else if(input[3]>='A'&&input[3]<='F')dec=(input[3]-'A'+10)+dec;
          else printf("The input hex value is invalid!\n");
       }
   }
else{ for(i=0;input[i]!='\0';i++){
          if((input[i]-'0')<0||(input[i]-'9')>0){
           printf("The input is invalid value\n");
           break;}
         }
       dec=atoi(input);
      if(dec>255||dec<0)printf("The value is excess limit\n");
  }
j=dec;
printf("The decimal value is %d\n",dec);
for(i=15;i>=0;i--){
   binary[i]=j%2;
  j=j/2;
 }
printf("The binary form is %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n",binary[0],binary[1],binary[2],binary[3],binary[4],binary[5],binary[6],binary[7],binary[8],binary[9],binary[10],binary[11],binary[12],binary[13],binary[14],binary[15]);
printf("please enter the value to be convert:");
}
}
