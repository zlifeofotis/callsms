/*
 * Copyright (C) Chesley Diao
 */

#include <string.h>
#include <error.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


 extern char **environ;
 extern int opterr;
 void msg_proc(char *,char *);


 int main(int argc,char ** argv)
 {
 	int ch;
 	pid_t pid;
 	opterr = 0;	

 	while((ch = getopt(argc,argv,"h")) != -1){
 		switch(ch){
 			case 'h':
 			printf("usage:\n        %s <telnum> <the msg of utf format>\n",argv[0]);
 			exit(1);
 			default:
 			continue;
 		}
 	}

 	if(argc != 3){
 		printf("usage:\n	%s <telnum> <the msg of utf format>\n",argv[0]);
 		exit(1);
 	}	
 	pid = fork(); 
 	switch(pid){
 		case -1:
 		perror("fork: ");
 		exit(1);
 		case 0:
 		printf("child process\n");
 		msg_proc(argv[1],argv[2]);
 		break;
 		default:
 		printf("parent process\n");
 		exit(0);	
 	}

 }

 void msg_proc(char *telnum,char *msg){

 	char *comm_file = "/data/bin/send_sms";
 	char tmp1[1024];
 	char tmp2[1024];
 	int rval;

 	sprintf(tmp1,"--to=%s",telnum);
 	tmp1[1023] = '\0';
 	sprintf(tmp2,"--msg-utf8='%s'",msg);
 	tmp2[1023] = '\0';

 	char *str[] = {"send_sms","--mobile=18868812941","--pwd='i,for.you*88('",tmp1,tmp2,(char *)0};
 	char *env[] = {"LD_LIBRARY_PATH=/usr/local/smslib",(char *)0};
 	
 	printf("%s\n",str[0]);
 	printf("%s\n",str[1]);
 	printf("%s\n",str[2]);
 	printf("%s\n",str[3]);
 	printf("%s\n",str[4]);
 	printf("%s\n",env[0]);
 	printf("%s\n",comm_file);
 	rval = execve(comm_file,str,env);	
 	perror("EXEC-------"); 

 	}



