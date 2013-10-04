#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


typedef struct code{
int opcode;
int line;
char label[256];
char inst[256];
char tar[256];
struct code *prev;
struct code *next;
}Code;


int hextodec(char *input);
void dectobina(int input, int binary[8]);
int strtodec(char *input);
Code * inputqu(FILE *fp);
int opcode(char inst[256]);
void run(Code *input);
void and(int x[8],int y[8]);
int binatodec(int x[8]);
void simulation(Code *input);

int memory[256];
FILE *fp=NULL;
char filename[200];
int a,b;
Code *input;

main(){
char command[100]="Aloha";
Code *input = NULL;
int abinary[8]={0};
int bbinary[8]={0};
int cbinary[8]={0};
Code *ppt;
Code *ct;
Code *tem;
int get,i,jump=0;
int value,value1;
Code *newline;
char *t; 

printf("\n\n   %s ********  Simulator Instructions  *******   \n\n",KGRN);
printf("%s To load a test file, type%s (load ***.s)\n",KCYN,KYEL);
printf("%s To check the file correctness, type%s (check)\n",KCYN,KYEL);
printf("%s To compile the file, type%s (run)\n",KCYN,KYEL);
printf("%s To simulate the file, type%s (simulation)\n",KCYN,KYEL);
printf("%s To see the value of a register or memory address, type%s (read)\n",KCYN,KYEL);
printf("%s To set the value of a register or memory address, type%s (set)\n",KCYN,KYEL);
printf("%s To initialize registers and memory addresses, type%s (reset)\n",KCYN,KYEL);
printf("%s To quit, type %s(quit)\n",KCYN,KYEL);

while(strcmp(command,"quit")!=0){            
printf("\n%sType a command %s(type 'help' to see instructions) :%s ",KBLU,KMAG,KNRM);
scanf("%s",command);

if(strcmp(command,"help")==0){ 
    printf("\n\n   %s ********  Simulator Instructions  *******   \n\n",KGRN);
    printf("%s To load a test file, type%s (load ***.s)\n",KCYN,KYEL);
    printf("%s To check the file correctness, type%s (check)\n",KCYN,KYEL);
    printf("%s To compile the file, type%s (run)\n",KCYN,KYEL);
    printf("%s To simulate the file, type%s (simulation)\n",KCYN,KYEL);
    printf("%s To see the value of a register or memory address, type%s (read)\n",KCYN,KYEL);
    printf("%s To set the value of a register or memory address, type%s (set)\n",KCYN,KYEL);
    printf("%s To initialize registers and memory addresses, type%s (reset)\n",KCYN,KYEL);
    printf("%s To quit, type %s(quit)\n",KCYN,KYEL);
                               }

else if(strcmp(command,"load")==0){ scanf("%s",filename);input=(Code*) malloc(sizeof(Code));input=NULL;
                               fp=fopen(filename,"r");
               if(fp==NULL) printf("%s Error : %sFile '%s' not found or can't be opened\n",KRED,KNRM,filename);
               else printf(" %sFile '%s' is loaded successfully%s \n",KGRN,filename,KNRM);
                 }
else if(strcmp(command,"check")==0){ input=(Code*) malloc(sizeof(Code));
                                 fp=fopen(filename,"r");
                                 if(fp==NULL)printf("%s Error : %sNo file found, please load file first!\n",KRED,KNRM);
                                 else
                                 input=inputqu(fp);
                              }
else if(strcmp(command,"reset")==0){ a=0;b=0;for(i=0;i<256;i++)memory[i]=0;
                                printf("%s The registers and memory have been reset !%s \n",KGRN,KNRM);}
else if(strcmp(command,"read")==0){ printf("%s Type the target to read %s'A' 'B' 'M 0x**' 'ALL'%s :",KCYN,KYEL,KNRM );
                               scanf("%s",t);
                               if(strcmp(t,"A")==0){printf("%s READ :  Register A = %d   Binary : ",KGRN,a);
                                                    dectobina(a,abinary);
                                                    for(i=0;i<8;i++)printf("%d",abinary[i]);    printf("%s\n",KNRM);
                                                    }
                               else if(strcmp(t,"B")==0){printf("%s READ : Register B = %d   Binary : ",KGRN,b);             
                                                    dectobina(b,bbinary);
                                                    for(i=0;i<8;i++)printf("%d",bbinary[i]);   printf("%s\n",KNRM);
                                                    } 
                               else  if(strcmp(t,"M")==0){
                                                    scanf("%s",t);value=hextodec(t);
                                                    if(value==-1)printf("%s Error :%s The memory address is INVALID!\n",KRED,KNRM);
                                                    else{printf("%s READ : Memory [%s]  = %d   Binary : ",KGRN,t,memory[value]);             
                                                         dectobina(memory[value],cbinary);
                                                         for(i=0;i<8;i++)printf("%d",cbinary[i]);    printf("%s\n",KNRM);
                                                    }
                                                    }
                               else if(strcmp(t,"ALL")==0){
                                                    printf("\n\n%s READ :  Register A = %d   Binary : ",KYEL,a);
                                                    dectobina(a,abinary);
                                                    for(i=0;i<8;i++)printf("%d",abinary[i]);    printf("%s\n",KNRM);
                                                    printf("%s READ : Register B = %d   Binary : ",KYEL,b);
                                                    dectobina(b,bbinary);
                                                    for(i=0;i<8;i++)printf("%d",bbinary[i]);   printf("\n");
                                                    printf(" READ : Memory\n");
                                                    for(i=0;i<16;i++){
                                                      putchar('\t');
                                                     for(value=0;value<16;value++)printf(" %d ",memory[i*16+value]);
                                                      putchar('\n');
                                                      }
                                                     printf("%s\n",KNRM);
                                                       }
                               else printf("%s Error : %sThe target entered is INVALID !!\n",KRED,KNRM);
                          }
else if(strcmp(command,"set")==0){ printf("%s Type the target to set %s'A' 'B' 'M 0x**' %s:",KCYN,KYEL,KNRM );
                               scanf("%s",t);
                               if(strcmp(t,"A")==0){printf("%sEnter the value : ",KYEL);
                                                    scanf("%d",&value);
                                                    if(value>255)printf("%s Error :%s The value exceed 8 bit!\n",KRED,KNRM);
                                                    else{a=value; dectobina(a,abinary);
                                                    printf("%s SET : Register A = %d   Binary : ",KGRN,a);
                                                    for(i=0;i<8;i++)printf("%d",abinary[i]);    printf("%s\n",KNRM);
                                                    }}
                               else if(strcmp(t,"B")==0){printf("%sEnter the value : ",KYEL);
                                                    scanf("%d",&value);
                                                    if(value>255)printf("%s Error :%s The value exceed 8 bit!\n",KRED,KNRM);
                                                    else{b=value; dectobina(b,bbinary);
                                                    printf("%s SET : Register B = %d   Binary : ",KGRN,b);
                                                    for(i=0;i<8;i++)printf("%d",bbinary[i]);    printf("%s\n",KNRM);
                                                    }}
                               else  if(strcmp(t,"M")==0){
                                                    scanf("%s",t);value=hextodec(t);
                                                    if(value==-1)printf("%s Error : %sThe memory address is INVALID!\n",KRED,KNRM);
                                                    else{printf("%sEnter the value : ",KYEL);
                                                         scanf("%d",&value1);
                                                         if(value1>255)printf("%s Error :%s The value exceed 8 bit!\n",KRED,KNRM);
                                                         else{memory[value]=value1; dectobina(memory[value],cbinary);
                                                         printf("%s SET : Memory [%s]  = %d   Binary : ",KGRN,t,memory[value]);
                                                         for(i=0;i<8;i++)printf("%d",cbinary[i]);    printf("%s\n",KNRM);
                                                         }
                                                    }
                                                    }
                               else printf("%s Error : %sThe target entered is INVALID !!\n",KRED,KNRM);
                             }
else if(strcmp(command,"run")==0){ if(input==NULL)printf("%s Error : %sPlease Pass the file check first\n",KRED,KNRM);
                              else run(input);    
                            }    
else if(strcmp(command,"simulation")==0){if(input==NULL)printf("%s Error : %sPlease Pass the file check first\n",KRED,KNRM);
                                    else simulation(input);
                                   }
                                              
else{ if(strcmp(command,"quit")==0) printf("%s\n The simulator is Terminated !%s \n ",KGRN,KNRM);
      else printf("%s Error :%s INVALID command entered \n",KRED,KNRM);
     }
}
}
//------------------------------------------------------------------
void simulation(Code *input){
Code *ppt,*tem,*newline,*ct;
int error=0,jump=0,value,x;
int breakpoint,f=0;
char k;
int abinary[8],bbinary[8],cbinary[8];

printf("%s Press the 'ENTER' key to simulate step by step %s\n",KYEL,KNRM);

ppt=(Code*) malloc(sizeof(Code));
tem=(Code*) malloc(sizeof(Code));
newline = (Code*) malloc(sizeof(Code));
ct= (Code*) malloc(sizeof(Code));
ppt=input;
while(ppt!=NULL){
jump=0;if(getchar()=='\n'){
       if (f==0)f++;
       else{ printf("%sLine %d: ",KYEL,ppt->line);
               if(jump==0&&ppt->opcode==62){printf("Get LDIA  "); a=strtodec(ppt->tar); }
       if(jump==0&&ppt->opcode==57){printf("Get LDB  "); value=hextodec(ppt->tar); b=memory[value]; }
       if(jump==0&&ppt->opcode==117){printf("Get ANDIB  "); value=hextodec(ppt->tar);dectobina(b,bbinary);dectobina(value,cbinary);
                                                            and(bbinary,cbinary);b=binatodec(bbinary);}
       if(jump==0&&ppt->opcode==137){printf("Get JBZ  ");ct=input;while(ct!=NULL&&strcmp(ct->label,ppt->tar)!=0){ tem=ct->next; ct=tem;}
                                     if(ct==NULL){error++,printf("%s Target Label not find%s",KRED,KNRM);}
                                     else{
                                     if((strcmp(ct->label,ppt->tar)==0)&&(b==0)){  ppt=ct->prev;jump=1;}
                                      }}
       if(jump==0&&ppt->opcode==102){printf("Get ADDIA  ");value=strtodec(ppt->tar); a=a+value;}
       if(jump==0&&ppt->opcode==109){printf("Get SUBIB  ");value=strtodec(ppt->tar); b=b-value;}
       if(jump==0&&ppt->opcode==128){printf("Get JMP  ");ct=input;while(ct!=NULL&&strcmp(ct->label,ppt->tar)!=0){ tem=ct->next; ct=tem;}

                                    if(ct==NULL){error++,printf("%sTarget Label not find%s",KRED,KNRM);}
                                   else{   ppt=ct->prev;jump=1;}}
       if(jump==0&&ppt->opcode==26){printf("Get STA  "); value=hextodec(ppt->tar); memory[value]=a;}
      
          printf("%s Reg A=%d  Reg B=%d%s",KBLU,a,b,KNRM);
          if(a>255||a<0){error++;printf("%s Register A exceed limit !%s",KRED,KNRM);}
          if(b>255||b<0){error++;printf("%s Register B exceed limit !%s",KRED,KNRM);}
         putchar('\n');
          tem=ppt->next;
         ppt=tem;}}
}
printf("\n%sThe Simulation is finished !!\n",KGRN);
printf(" %sTotal has %s%d Errors %sfound %s\n", KYEL,KRED,error,KYEL,KNRM);

}


//------------------------------------------------------------------
void run(Code *input){
Code *ppt,*tem,*newline,*ct;
int jump=0,value,x;
int breakpoint=0;
char k;
int abinary[8],bbinary[8],cbinary[8];


ppt=(Code*) malloc(sizeof(Code));
tem=(Code*) malloc(sizeof(Code));
newline = (Code*) malloc(sizeof(Code));
ct= (Code*) malloc(sizeof(Code));
ppt=input;
while(ppt!=NULL&&breakpoint!=1){
jump=0;
       if(jump==0&&ppt->opcode==62){ a=strtodec(ppt->tar); }
       if(jump==0&&ppt->opcode==57){ value=hextodec(ppt->tar); b=memory[value]; }
       if(jump==0&&ppt->opcode==117){ value=hextodec(ppt->tar);dectobina(b,bbinary);dectobina(value,cbinary);
                                                            and(bbinary,cbinary);b=binatodec(bbinary);}
       if(jump==0&&ppt->opcode==137){ct=input;while(ct!=NULL&&strcmp(ct->label,ppt->tar)!=0){ tem=ct->next; ct=tem;}
                                     if(ct==NULL)breakpoint=1;
                                     else{
                                     if((strcmp(ct->label,ppt->tar)==0)&&(b==0)){  ppt=ct->prev;jump=1;} 
                                      }}
       if(jump==0&&ppt->opcode==102){value=strtodec(ppt->tar); a=a+value;}
       if(jump==0&&ppt->opcode==109){value=strtodec(ppt->tar); b=b-value;}
       if(jump==0&&ppt->opcode==128){ct=input;while(ct!=NULL&&strcmp(ct->label,ppt->tar)!=0){ tem=ct->next; ct=tem;}
                                    
                                    if(ct==NULL)breakpoint=1;
                                   else{   ppt=ct->prev;jump=1;}}
       if(jump==0&&ppt->opcode==26){ value=hextodec(ppt->tar); memory[value]=a;}
         if (a>255||a<0||b>255||b<0)breakpoint=1;
        if(breakpoint!=1){
          tem=ppt->next;
         ppt=tem;}
}
if(breakpoint==1){printf("%s BREAK : %sThe breakpoint occurs at line %d \n",KRED,KNRM,ppt->line);}
if(breakpoint==0)printf("%s The Code Compiles correctly! %s\n",KGRN,KNRM);
}
//--------------------------------------------------------------------
int binatodec(int x[8]){
int y=0,i;
for(i=0;i<8;i++)y=y*2+x[i];
return y;
    
}
//--------------------------------------------------------------------------
void and(int x[8],int y[8]){
int i;
for(i=0;i<8;i++){if(x[i]==1&&y[i]==1)x[i]=1;
                 else x[i]=0;
                }
return ;
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
   }
 else dec=-1;
 return dec;
}

//----------------------------------------------------------------------------

void dectobina(int dec,int binary[8]){
int i,j;

 if(dec>255||dec<0)printf("The value is excess limit\n");

j=dec;
//printf("The decimal value is %d\n",dec);
for(i=7;i>=0;i--){
   binary[i]=j%2;
  j=j/2;
 }
return;
}

//-----------------------------------------------------------------

Code * inputqu(FILE *fp){

int i=0,m=0;
int size=0;
int f,y;
Code *head;
Code *tail;
Code *newline;
Code *ppt;
char label[100][100];
char read[256];
int comma=0;
char k;
char *r;
int error=0;
head=tail=NULL;
char line[256]="";
y=0;
while(fscanf(fp,"%c",&k)!=EOF){
  if(k=='\n'){                             
       newline = (Code*) malloc(sizeof(Code));
       
 //     printf("line %s readed \n",line);
      strcpy(read,strtok(line," \t"));
      for(i=0;read[i]!='\0';i++){
      if(read[i]==':'){comma=1;read[i]='\0';continue;}}
      if(comma==1){strcpy(newline->label,read);
                     f=0;
//                     printf("Label : %s \n",read);
                   for(i=0;i<m;i++){ if(strcmp(read,label[i])==0){
                                         error++;
                                        printf("%s Error %d :%s Line %d %s Multiple uses of same label: '%s' !\n",KRED,error,KYEL,size,KNRM,read);
                                         f=1;i=m;                       
                                          }
                                      }
                   if(f==0){
                            strcpy(label[m],read);
                            m++;}
                   strcpy(read,strtok(NULL," \t"));
                   comma=0;
                  }

      strcpy(newline->inst,read);
//       printf("Inst: %s \n",read);
      newline->opcode=opcode(newline->inst);
      if(newline->opcode==-1){error++; printf("%s Error %d :%s Line %d%s has Invalid instruction used '%s'!\n",KRED,error,KYEL,size,KNRM,read); }
      strcpy(read,strtok(NULL," \t"));
      strcpy(newline->tar,read);
//       printf("Target : %s \n",read);
      r=strtok(NULL," \t");
      if(r!=NULL){
               strcpy(read,r);
             if(read[0]!='/'){error++; printf("%s Error %d :%s Line %d%s has too many parameter !\n",KRED, error,KYEL,size,KNRM);}
               }
      for(i=0;i<=y;i++)line[i]='\0'; 
      y=0;
      newline->line=size;
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
  else { line[y]=k;
         y++;
      }
}
printf("\n%s Result :  Total %d Errors are detected %s\n",KYEL,error,KNRM);
if(error==0)printf("%s The input file is correct!%s\n",KGRN,KNRM);
if(error!=0)printf("%s Error founded Please check the errors and check again ! \n%s",KRED,KNRM);
fclose(fp);
if(head==NULL){printf("%s Error :%s read the target file\n",KRED,KNRM);return(NULL);}
if(error!=0){return NULL;}
else{return head;}

}
//------------------------------------------------------------------------------------------

int opcode(char inst[256])
{
        if(strcmp(inst, "LDA") == 0)  return 58;
        if(strcmp(inst, "LDIA") == 0)  return 62;
        if(strcmp(inst, "LDB") == 0) return 57;
        if(strcmp(inst, "LDIB") == 0) return 61;
        if(strcmp(inst, "STA") == 0)  return 26;
        if(strcmp(inst, "STB") == 0)    return 25;
        if(strcmp(inst, "TAB") == 0)  return 33;
        if(strcmp(inst, "TBA") == 0)  return 34;
        if(strcmp(inst, "ADDA") == 0) return 98;
        if(strcmp(inst, "ADDIA") == 0) return 102;
        if(strcmp(inst, "ADDB") == 0) return 97;
        if(strcmp(inst, "ADDIB") == 0) return 101;
        if(strcmp(inst, "SUBA") == 0)  return 106;
        if(strcmp(inst, "SUBIA") == 0) return 110;
        if(strcmp(inst, "SUBB") == 0) return 105;
        if(strcmp(inst, "SUBIB") == 0) return 109;
        if(strcmp(inst, "ANDA") == 0) return 114;
        if(strcmp(inst, "ANDIA") == 0) return 118;
        if(strcmp(inst, "ANDB") == 0) return 113;
        if(strcmp(inst, "ANDIB") == 0) return 117;
        if(strcmp(inst, "ORA") == 0)  return 122;
        if(strcmp(inst, "ORIA") == 0) return 126;
        if(strcmp(inst, "ORB") == 0)  return 121;
        if(strcmp(inst, "ORIB") == 0) return 125;
        if(strcmp(inst, "JMP") == 0)  return 128;
        if(strcmp(inst, "JBZ") == 0)  return 137;
        if(strcmp(inst, "JBNZ") == 0) return 153;
        return -1;
}

