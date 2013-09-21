#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

typedef struct cell{
int index;
char type;
int value;
int binary[16];
struct cell *prev;
struct cell *next;
}Cell;


main(){
Cell *head;
Cell *tail;
Cell *new;
Cell *ppt;
Cell *pt;
int i;
int j;
head=tail=NULL;

for(i=0;i<=15;i++){
       new = (Cell *) malloc(sizeof(Cell));
        new->next=NULL;
        new->value=0;
        new->index=i;
        for(j=0;j<16;j++){new->binary[j]=0;}
        if(i<4)new->type='C';
        if(i>=4&&i<8)new->type='I';
        if(i>7) new->type='D';

      if(head==NULL){
           head=new;
           tail=new;

          }
       else{
          new->prev=tail;
          tail->next=new;
          tail=new;
          }
}
ppt=head;
printf("\n-----Data Storage-------------\n");
printf(" Type  index  value  binary  \n");
while(ppt!=NULL){
  printf("  %c    %d     %d    ",ppt->type,ppt->index,ppt->value);
  printf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n",ppt->binary[0],ppt->binary[1],ppt->binary[2],ppt->binary[3],ppt->binary[4],ppt->binary[5],ppt->binary[6],ppt->binary[7],ppt->binary[8],ppt->binary[9],ppt->binary[10],ppt->binary[11],ppt->binary[12],ppt->binary[13],ppt->binary[14],ppt->binary[15]);
 pt=ppt;
 ppt=pt->next;
 }
}
