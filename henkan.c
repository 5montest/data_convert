#include <stdio.h>

#define ID_LEN 9
#define ELEM_NUM 22


void convP(char data[],int value[]){
	int i,j;
	j = ID_LEN;
	for(i = 0;i < ELEM_NUM;i++){
        value[i] = (((data[j]-0x30)&0x0f)<<12) + (((data[j+1]-0x30)&0x3f)<<6) + ((data[j+2]-0x30)&0x3f);
		j = j + 3;
	}
}
int main(void){
    FILE *fp;
    fp = fopen("data.csv","w");
    if(fp == NULL){
        puts("ERROR");
        return -1;
    }

	char data[] = "$DMKee00,00000100200300@00P00`01004S08S0<d0A50EF0lh0N90V[00000@00000@0000000S.";
	printf("data:%s\n", data);
	int i;
    int value[ELEM_NUM];
	convP(data,value);
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
    fclose(fp);
	return 0;
}
