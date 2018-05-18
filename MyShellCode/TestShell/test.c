#include <stdio.h>
typedef struct _Comp
{
    float real;//real Number
    float img;//image Number
}Comp;



int testFile()
{
    //set Num to data2
    int ver_data1 = 1000,hor_data = 1;
    Comp data2[1000],data3[1000],buf;
    int i = 0,ia = 0;
    FILE *fp_write = NULL;
    for(i = 0;i < ver_data1;i++ )
    {
	data2[i].real = i;
	data2[i].img = i+1;	
    }
    //Write data2 to file
    fp_write = fopen("./data_2.dat","wb");
    for(ia = 0;ia < ver_data1;ia++)
    {
	fwrite(&data2[ia],sizeof(Comp),hor_data,fp_write);
    }
    fclose(fp_write);
    //read data2 to data3
    fp_write = fopen("./data_2.dat","rb");
    for(ia = 0;ia < ver_data1;ia++)
    {
	fread(&data3[ia],sizeof(Comp),hor_data,fp_write);
    }
    fclose(fp_write);
    //Print data3 
    for(ia = 0;ia < ver_data1;ia++)
    {
	printf("%d->data3.real: %f data3.img: %f\n",ia,data3[ia].real,data3[ia].img);
    }

    return 0;
}

int a;
int a;

int main()
{
    char c = '\0';
    printf("Hello World\t!\n");
    printf("\f");
    printf("xiaogongwe\vi\n");
    printf("\110\n");
    printf("%e\n",1000.123);
    printf("%5.2f,%7.2f\n",0.1,0.123);
    do
    {
    c = getchar();
    if(c >= 'A' && c<= 'Z') c+=32;
    putchar(c);
    }while(c != '\n');

    return 0;

}












