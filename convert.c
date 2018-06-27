#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <stdio.h>

#define SERIAL_PORT "/dev/ttyUSB0"
#define ID_LEN 9
#define ELEM_NUM 3
#define DATA_LEN 69

void convP(char data[],short int value[],int start){
    int i,j;
    j = start + 1;
    for(i = 0;i < ELEM_NUM;i++){
        value[i] = (((data[j]-0x30)&0x0f)<<12) + (((data[j+1]-0x30)&0x3f)<<6) + ((data[j+2]-0x30)&0x3f);
        j = j + 3;
    }
}
int main(void){
    char data[256];
    int fd,start,i,j,cnt,flug;
    flug = 0;
    cnt = 0;
    FILE *fp;
    fd = open(SERIAL_PORT,O_RDWR);

    fp = fopen("/var/www/html/jikken1/file/sample010.csv","w");
    fclose(fp);
    if(fp == NULL){
        puts("ERROR");
        return -1;
    }
    while(1){
        label:
        usleep(200);
        flug  = 0;
        read(fd,data,sizeof(data));
        puts("READ");

        for(i=0;i<DATA_LEN;i++){
            if(data[i] == ',' && data[i + DATA_LEN] == '.'){
                flug = 1;
                start = i;

                printf("data:%s\n", data);
                short int value[ELEM_NUM];
                convP(data,value,start);

                for(j = 0;j < ELEM_NUM;j++){

                    if(value[j] > 1000 || value[j] < -1000){
                        break;
                    }

                    else if(j != 1){

                        fp = fopen("/var/www/html/jikken1/file/sample010.csv","a");

                        if(j == ELEM_NUM -1 ){
                            printf("%d\n",value[j]);
                            fprintf(fp,"%d\n",value[j]);
                            fclose(fp);
                        }else{
                            printf("%d,",value[j]);
                            fprintf(fp,"%d,",cnt);
                            cnt++;
                            fprintf(fp,"%d,",value[j]);
                            fclose(fp);
                        }
                    }
                }
            }
        }
        if(flug == 1){
            goto label;
        }
    }
    close(fd);
    return 0;
}
