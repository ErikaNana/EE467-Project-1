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

typedef struct code{
int line;
char label[256];
char inst[256];
char tar[256];
struct code *prev;
struct code *next;
}Code;

typedef struct cell{
int index;
char type;
int value;
int bit[16];
struct cell *prev;
struct cell *next;
}Cell;

int hextodec(char *input);
void dectobina(int input, int binary[8]);
int strtodec(char *input);
Code * inputqu(void);
Cell * setmemory(void);


main(){
Cell *memory;
Code *input;
FILE *fp;
char filename[200];
int a[8]={0};
int b[8]={0};
int c[8]={0};
Code *ppt;Cell *pt;
Cell *temp;
int get,i,jump=0;
int value;
int colum,row;
Code *newline;
Cell *newcell;
Code *ct;
Code *tem;

      input=(Code*) malloc(sizeof(Code));
      ppt=(Code*) malloc(sizeof(Code));
      tem=(Code*) malloc(sizeof(Code));
       input=inputqu();
      ppt=input;
       newline = (Code*) malloc(sizeof(Code));
      memory=(Cell*) malloc(sizeof(Cell));
       pt=(Cell*) malloc(sizeof(Cell));
       temp=(Cell*) malloc(sizeof(Cell));
       memory=setmemory();
       pt=memory;
       newcell=(Cell*) malloc(sizeof(Cell));
       while(ppt!=NULL){
            printf("       %s     %s     %s \n\n\n",ppt->label,ppt->inst,ppt->tar);

            newline=ppt;
            ppt=newline->next;
            }
    printf(" Type  index  value  bit  \n");


       ppt=input;
        if(ppt==NULL)printf("error\n");
       while(ppt!=NULL){
         jump=0;
        get=strcmp(ppt->inst,"LDIA");
        if(get==0&&jump==0){ printf("get LDIA\n");
                    value=strtodec(ppt->tar);
                    dectobina(value,a);
                   }
        get=strcmp(ppt->inst,"LDB");
         if(get==0&&jump==0){printf("get LDB\n");
                    value=hextodec(ppt->tar);
                    row=value%16;
                    colum=value/16;
                    pt=memory;
                    while(pt->index!=colum){temp=pt->next;pt=temp;}
                    value=pt->bit[row];
                    dectobina(value,b);
                   }
        get=strcmp(ppt->inst,"ANDIB");
       if(get==0&&jump==0){  printf("get ANDIB\n");
                    value=hextodec(ppt->tar);
                    dectobina(value,c);
                    for(i=0;i<8;i++){
                     if(b[i]==1&&c[i]==1)b[i]=1;
                     else b[i]=0;
                     }
                   }
        get=strcmp(ppt->inst,"JBZ");
         if(get==0&&jump==0){printf("get JBZ\n");
                    ct=input;

                    while(ct!=NULL&&strcmp(ct->label,ppt->tar)!=0){
                           tem=ct->next;
                           ct=tem;
                          }
                  value=0;
                    for(i=0;i<=6;i++)value=(value+b[i])*2;
                    value=value+b[7];
                    if((strcmp(ct->label,ppt->tar)==0)&&(value==0)){
                        ppt=ct->prev;jump=1;
                        }
                     }
        get=strcmp(ppt->inst,"ADDIA");
          if(get==0&&jump==0){printf("get ADDIA\n");
                     value=0;
                     for(i=0;i<=6;i++)value=(value+a[i])*2;
                    value=value+a[7];
                     value=value+strtodec(ppt->tar);
                      dectobina(value,a);
                    }

        get=strcmp(ppt->inst,"SUBIB");
          if(get==0&&jump==0){printf("get SUBIB\n");
                      value=0;
                     for(i=0;i<=6;i++)value=(value+b[i])*2;
                    value=value+b[7];
                       printf("value=%d\n",value);
                       printf("target is %s\n",ppt->tar);
                     value=value-strtodec(ppt->tar);
                      printf("value=%d\n",value);
                      dectobina(value,b);
                    }

        get=strcmp(ppt->inst,"JMP");
         if(get==0&&jump==0){ printf("get JMP\n");
                     ct=input;
                    while(ct!=NULL&&strcmp(ct->label,ppt->tar)!=0){
                           tem=ct->next;
                           ct=tem;
                          }
                     if(strcmp(ct->label,ppt->tar)==0){
                        ppt=ct->prev;jump=1;
                        }
                     }

        get=strcmp(ppt->inst,"STA");
         if(get==0&&jump==0){printf("get STA\n");
                     value=hextodec(ppt->tar);
                    row=value%16;
                    colum=value/16;
                    pt=memory;
                    while(pt->index!=colum){temp=pt->next;pt=temp;}
                    value=0;
                     for(i=0;i<=6;i++)value=(value+a[i])*2;
                    value=value+a[7];
                    pt->bit[row]=value;
                   }
         tem=ppt->next;
         ppt=tem;

  printf("reg A=%d%d%d%d%d%d%d%d   reg B=%d%d%d%d%d%d%d%d \n",a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],b[0],b[1],b[2],b[3],b[4],b[5],b[6],b[7]);
  pt=memory;
  while(pt!=NULL){
  printf("  %c    %d     %d    ",pt->type,pt->index,pt->value);
  printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",pt->bit[0],pt->bit[1],pt->bit[2],pt->bit[3],pt->bit[4],pt->bit[5],pt->bit[6],pt->bit[7],pt->bit[8],pt->bit[9],pt->bit[10],pt->bit[11],pt->bit[12],pt->bit[13],pt->bit[14],pt->bit[15]);
 newcell=pt;
 pt=newcell->next;
 }
}
}


//------------------------------------------------------------------------------
int hextodec(char *input){
int dec;
int i,j;

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
    return dec;
   }
else{printf("the Hex value is invalid!\n");return 0;
}
}

//----------------------------------------------------------------------------

int strtodec(char *input){
int dec=0,i,j=0;
 for(i=0;input[i]!='\0';i++){
          if((input[i]-'0')<0||(input[i]-'9')>0){
           printf("The input is invalid value\n");
           j=1;
           break;}
         }
 if(j==1){printf("The decimal value error!\n");return 0;}
 else {dec=atoi(input);return dec;}

}

//----------------------------------------------------------------------------

void dectobina(int dec,int binary[8]){
int i,j;

 if(dec>255||dec<0)printf("The value is excess limit\n");

j=dec;
printf("The decimal value is %d\n",dec);
for(i=7;i>=0;i--){
   binary[i]=j%2;
  j=j/2;
 }
return;
}

//-----------------------------------------------------------------------------


Code * inputqu(void){
char filename[200];
FILE *fp;
int i=0;
int size=0;
Code *head;
Code *tail;
Code *newline;
Code *ppt;
char read[256];
int comma=0;
head=tail=NULL;

printf("Enter assemble code file name: ");
scanf("%s",filename);
fp=fopen(filename,"r");
if(fp==NULL){
   printf("File '%s' not found or can't be opened\n",filename);
   return(NULL);
   }

while(fscanf(fp,"%s",read)!=EOF){
      printf("%s \n",read);
      for(i=0;read[i]!='\0';i++){
      if(read[i]==':'){comma=1;read[i]='\0';continue;}}
      newline = (Code*) malloc(sizeof(Code));
      if(comma==1){strcpy(newline->label,read);
                   fscanf(fp,"%s",read);
                   comma=0;
                  }
      strcpy(newline->inst,read);
      fscanf(fp,"%s",read);
      strcpy(newline->tar,read);
      size++;
      newline->next=NULL;

        if(head==NULL){
           head=newline;
           tail=newline;
          }
        else{
          newline->prev=tail;
          tail->next=newline;
          tail=newline;
          }



}

fclose(fp);
if(head==NULL){printf("Error read the target file\n");return(NULL);}
return head;
}


//----------------------------------------------------------------------------

Cell * setmemory(void){
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
        for(j=0;j<16;j++){
          if(i==4&&j==0){new->bit[j]=5;}
          else  new->bit[j]=0;}
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
if(head==NULL)printf("Error occured when create memory\n");
return head;
}



