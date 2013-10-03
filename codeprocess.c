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

int regA, regB, PC = 0;
int memory[256];
char bufferA[33];
char bufferB[33];
char cmd[33];
char add[33];

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
int jump_flag=0;
char target_label[256];

printf("\n\n                               Welcome to EE 260 Computer Simulator\n\n\n"); 

while(1) {
printf("Enter assembly code file name: ");
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

if(size>64) {
	printf("Error: The file is larger than the code space\n\nExiting...\n\n");
	exit(1);
	}

printf(" \n\n %d lines of code loaded...\n \n",size);
	
printf("                                ----- Options -----\n\n"); 
printf("                                step: Step through program\n");      
printf("                                display: Displays memory address\n"); 
printf("                                help: Displays options\n");
printf("                                exit: Exits the simulator\n\n"); 

ppt=head;

while(ppt!=NULL){
    
	if(jump_flag > 0) {
		jump_flag = 0;
		PC=0;	
		ppt=head;
	
        	while(ppt!=NULL) {
			if(strncmp(ppt->label,target_label,strlen(ppt->label))==0 && strlen(ppt->label) > 0) {
				printf("                              Next Instruction: %s %s %s \n",ppt->label,ppt->inst,ppt->tar);
				printf("\n");
				break;
				}
			else {
				newline=ppt;
				ppt=newline->next;
				PC++;	
				}	
			}
   		}

    printf("Enter command: ");    
    scanf("%s",cmd);
		
    if(strcmp(cmd,"display")==0) {
	printf("Enter memory address in hexidecimal: ");	
	scanf("%s",add);	
	printf("\n");
	printf("The value stored in address %s is %d\n\n",add,memory[strtol(add,0,16)]);	
	}    
    else if(strcmp(cmd,"help")==0) {
 	printf("\n\n");	
	printf("                             ----- Options -----\n\n"); 
    	printf("                             step: Step through program\n");      
    	printf("                             display: Displays memory address\n"); 
	printf("                             help: Displays options\n");
    	printf("                             exit: Exits the simulator\n\n"); 
   	} 
    else if(strcmp(cmd,"exit")==0) exit(0);
    else if(strcmp(cmd,"step")==0) { 
     
    	printf("\n                             Current Instruction: %s %s %s\n",ppt->label,ppt->inst,ppt->tar);
    
    	if(strcmp(ppt->inst,"LDA")==0) regA = strtol(ppt->tar,0,16); 
    	else if(strcmp(ppt->inst,"LDIA")==0) regA = strtol(ppt->tar,0,10);
    	else if(strcmp(ppt->inst,"LDB")==0) regB = strtol(ppt->tar,0,16); 
    	else if(strcmp(ppt->inst,"LDIB")==0) regB = strtol(ppt->tar,0,10);
    	else if(strcmp(ppt->inst,"STA")==0) memory[strtol(ppt->tar,0,16)] = regA;
    	else if(strcmp(ppt->inst,"STB")==0) memory[strtol(ppt->tar,0,16)] = regB;
    	else if(strcmp(ppt->inst,"TAB")==0) regB = regA;
    	else if(strcmp(ppt->inst,"TBA")==0) regA = regB;
    	else if(strcmp(ppt->inst,"ADDA")==0) regA = regA + memory[strtol(ppt->tar,0,16)];
    	else if(strcmp(ppt->inst,"ADDIA")==0) regA = regA + strtol(ppt->tar,0,10); 
    	else if(strcmp(ppt->inst,"ADDB")==0) regB = regB + memory[strtol(ppt->tar,0,16)];
    	else if(strcmp(ppt->inst,"ADDIB")==0) regB = regB + strtol(ppt->tar,0,10); 
    	else if(strcmp(ppt->inst,"SUBA")==0) regA = regA - memory[strtol(ppt->tar,0,16)];
    	else if(strcmp(ppt->inst,"SUBIA")==0) regA = regA - strtol(ppt->tar,0,10); 
    	else if(strcmp(ppt->inst,"SUBB")==0) regB = regB - memory[strtol(ppt->tar,0,16)];
    	else if(strcmp(ppt->inst,"SUBIB")==0) regB = regB - strtol(ppt->tar,0,10); 
    	else if(strcmp(ppt->inst,"ANDA")==0) regA = regA & memory[strtol(ppt->tar,0,16)]; 
    	else if(strcmp(ppt->inst,"ANDIA")==0) regA = regA & strtol(ppt->tar,0,16);
    	else if(strcmp(ppt->inst,"ANDB")==0) regB = regB & memory[strtol(ppt->tar,0,16)];
    	else if(strcmp(ppt->inst,"ANDIB")==0) regB = regB & strtol(ppt->tar,0,16);
    	else if(strcmp(ppt->inst,"ORA")==0) regA = regA | memory[strtol(ppt->tar,0,16)];
    	else if(strcmp(ppt->inst,"ORIA")==0) regA = regA | strtol(ppt->tar,0,16);
    	else if(strcmp(ppt->inst,"ORB")==0) regB = regB | memory[strtol(ppt->tar,0,16)];
    	else if(strcmp(ppt->inst,"ORIB")==0) regB = regB | strtol(ppt->tar,0,16);  	 
    	else if(strcmp(ppt->label,"JMP")==0) jump_flag = 1; 
    	else if(strcmp(ppt->inst,"JBZ")==0) {
    		if(regB==0) jump_flag = 2;
   		} 
    	else if(strcmp(ppt->inst,"JBNZ")==0) {
		if(regB!=0) jump_flag = 2;
		}
	else printf("Error: %s is not a valid instruction\n\n", ppt->inst);
		
	if(jump_flag==1) strcpy(target_label,ppt->inst);
	if(jump_flag==2) strcpy(target_label,ppt->tar);					
  	
	printf("\n"); 
	printf("                             A:  %d\n", regA);
    	printf("                             B:  %d\n", regB); 	 
   	printf("                             PC: %d\n", PC);	
	printf("\n"); 
	if(jump_flag == 0) { 
   		newline=ppt;
    		ppt=newline->next;
    		if(ppt!=NULL) {
			printf("                             Next instruction: %s %s %s \n",ppt->label,ppt->inst,ppt->tar);
			PC++;	
			printf("\n");
			}
		}	  
	}
   else printf("Error: %s is not a valid command\n\n", cmd);	
}
    printf("End of File\n\n"); 
    printf("                             ----- Options -----\n\n"); 
    printf("                             load: Load a new assembly code file\n");      
    printf("                             display: Displays memory address\n"); 
    printf("                             help: Displays options\n");
    printf("                             exit: Exits the simulator\n\n"); 
    
    while(1) {
    printf("Enter command: ");    
    scanf("%s",cmd);
   
    if(strcmp(cmd,"load")==0) {
		regA = 0;
		regB = 0;
		PC = 0;	
		for(i=0;i<256;i++) memory[i] = 0;	
		i = 0;
		j = 0;
		r = 0;	
		size = 0;	
		break;
 		}
   else if(strcmp(cmd,"help")==0) {
    	printf("                             ----- Options -----\n\n"); 
    	printf("                             load: Load a new assembly code file\n");      
    	printf("                             display: Displays memory address\n"); 
    	printf("                             help: Displays options\n");
    	printf("                             exit: Exits the simulator\n\n"); 
  	}  
   else if(strcmp(cmd,"display")==0) {
	printf("Enter memory address in hexidecimal: ");	
	scanf("%s",add);	
	printf("\n");
	printf("The value stored in address %s is %d\n\n",add,memory[strtol(add,0,16)]);	
	}    
    else if(strcmp(cmd,"exit")==0) exit(0);
   else printf("Error: %s is not a valid command\n\n",cmd);
   }
}
}
