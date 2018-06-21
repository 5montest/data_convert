#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <stdio.h>

#define SERIAL_PORT "/dev/ttyUSB0"
#define ID_LEN 9
#define ELEM_NUM 8
#define DATA_LEN 69

void convP(char data[],int value[],int start){
	int i,j;
	j = start;
	for(i = 0;i < ELEM_NUM;i++){
        	value[i] = (((data[j]-0x30)&0x0f)<<12) + (((data[j+1]-0x30)&0x3f)<<6) + ((data[j+2]-0x30)&0x3f);
		j = j + 3;
	}
}
int main(void){
    char data[256];
    int fd,start;
    FILE *fp;

    fd = open(SERIAL_PORT,O_RDWR);

    fp = fopen("/var/www/html/jikken1/file/sample010.csv","w");
    if(fp == NULL){
        puts("ERROR");
        return -1;
    }
    while(1){

        read(fd,data,sizeof(data));

        for(i=0;i<DATA_LEN;i++){
            if(data[i] == ','){
                if(data[i + DATA_LEN] == '.'){

                    start = i;

                    printf("data:%s\n", data);
                    int value[ELEM_NUM];
                    convP(data,value,start);
                    for(i = 0;i < ELEM_NUM;i++){
                        if(i == ELEM_NUM -1){
                            printf("%x\n",value[i]);
                            fprintf(fp,"%x\n",value[i]);
                        }else{
                            printf("%x,",value[i]);
                            fprintf(fp,"%x,",value[i]);
                        }
                    }
                    for(i = 0;i < ELEM_NUM;i++){
                        if(i == ELEM_NUM -1){
                            printf("%d\n",value[i]);
                            fprintf(fp,"%d\n",value[i]);
                        }else{
                            printf("%d,",value[i]);
                            fprintf(fp,"%d,",value[i]);
                        }
                    }
                }
            }
        }
    }
    fclose(fp);
    close(fd);
    return 0;
}
