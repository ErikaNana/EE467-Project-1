#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

typedef struct code{
int line;
char label[256];
char inst[256];
char tar[256];
struct code *prev;
struct code *next;
}Code;

main()
{
FILE *fp;
char filename[200];
int i=0,j=0,r=0;
char word;
int size=0;
Code *head;
Code *tail;
Code *newline;
Code *ppt;
char readline[256]="";
int comma=0;


printf("Enter assemble code file name: ");
scanf("%s",filename);
fp=fopen(filename,"r");
if(fp==NULL){
   printf("File '%s' not found or can't be opened\n",filename);
//   return(NULL);
   }
head=tail=NULL;

while(fscanf(fp,"%c",&word)!=EOF){
if(word!='\n'){readline[i]=word;
               i++;}
else{   newline = (Code*) malloc(sizeof(Code));
        for(j=0;j<=i;j++){if(readline[j]==':'){comma=1;break;}
                          else comma=0;}

       r=0;j=0;i=0;
        if(comma==1){
                        while(readline[r]!=':'){newline->label[r]=readline[r];
                                                r++;}

                     }

        while((readline[r]==':'||readline[r]=='\t'||readline[r]==' ')&&(readline[r]!='\0')){r++;}
        while(readline[r]!=' '&&readline[r]!='\t' &&readline[r]!='\0'){
                                                  newline->inst[i]=readline[r];
                                                  i++;
                                                  r++;
                                                  }
       while((readline[r]==':'||readline[r]==' '||readline[r]=='\t')&&(readline[r]!='\0')){r++;}
       while(readline[r]!=' '&&readline[r]!='\t' &&readline[r]!='\0'){
                                                  newline->tar[j]=readline[r];
                                                  j++;
                                                  r++;
                                                  }
      strcpy(readline,"");
      i=0;j=0;r=0;
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

}
fclose(fp);
if(head==NULL)printf("Error read the target file\n");
//return(head);

printf(" \n\n Total %d lines of code readed\n \n",size);

ppt=head;
while(ppt!=NULL){
    printf("       %s     %s     %s \n\n\n",ppt->label,ppt->inst,ppt->tar);
     newline=ppt;
     ppt=newline->next;
    }
}

                                                                                     
