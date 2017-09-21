#include "OpenSSD.h"
int main()
{
	FILE *input_file,*input_file2;
	FILE *output_file;
	int i,error_count,fread_num,fread_CMP_num,file_size;
	int page_error_count[250];
	int page_error = 0;
	error_count = 0;
	unsigned char outbuffer[0];
	input_file = fopen("input.bin","rb");
	//input_file2 = fopen("output_t.bin","rb");
	output_file = fopen("outpu.bin","wb");

	if(input_file == NULL)
	{
		printf("can't open the file\n");
		return 0;
	}
	fseek(input_file, 0, SEEK_END);  
    file_size = ftell(input_file);  
    printf("%d\n",file_size);				//file_size
    rewind(input_file);  
	unsigned char *Data_Buffer = (unsigned char*)malloc(sizeof(unsigned char));
	unsigned char *Data_CMP_Buffer = (unsigned char*)malloc(sizeof(unsigned char));
	if(Data_Buffer == NULL || Data_CMP_Buffer == NULL)
	{
		printf("allocate memeory space for data buffer failed\n");
		return 0;
	}
	for(i=0;i<250;i++)
	{
		page_error_count[i] = 0;
	}
	int j=0;
	for(i=0;i<=file_size;i++)
	{
		
		fread_num = fread(Data_Buffer, sizeof(unsigned char), 1, input_file);
		//fread_CMP_num = fread(Data_CMP_Buffer,sizeof(unsigned char), 1, input_file2);
		//printf(" %x",*Data_Buffer);
		//printf(" %x",(unsigned char)*(&Data_Buffer[0]));
		//printf(" %x",(unsigned char)*(&Data_CMP_Buffer[0]));
		/*if((i!=0)&&(i%16==0))
		{
			printf(" \n");
		}
		printf(" %x",*Data_Buffer);*/
		/*&if(memcmp(Data_Buffer,Data_CMP_Buffer,1) != 0)
		{
			error_count++;
			page_error++;
		    printf(" %x--%x |",(unsigned char)*(&Data_Buffer[0]),(unsigned char)*(&Data_CMP_Buffer[0]));	
		}
		
		if((i!=0)&&(i%16384==0))
		{
			page_error_count[j] = page_error;
			j++;
			printf(" %d\n", page_error);
			page_error = 0;
		}
		if((i>3964928)&&(i==file_size))
		{
			page_error_count[j] = page_error;
			printf(" %d", page_error);
		}*/
		if(i>=3378048&&i<3820544)
		{
			memset(Data_Buffer,0xFF,sizeof(unsigned char));
		}
		fwrite(Data_Buffer,sizeof(unsigned char),1,output_file);


		//printf(" %d" , memcmp(Data_Buffer,Data_CMP_Buffer,1));
	}
	/*int sum=0;
	//sprintf(outbuffer,"%d\n", error_count);
	//fwrite(outbuffer,sizeof(char),2,output_file);

	printf("\n------error is---%d-------------\n", error_count);
	for(i=0;i<243;i++)
	{
		sum =sum + page_error_count[i];
		sprintf(outbuffer,"%d\n", page_error_count[i]);
		fwrite(outbuffer,sizeof(int),1,output_file);
		
	}
	printf("%d\n", sum);
	sprintf(outbuffer,"\n%d\n", sum);
	fwrite(outbuffer,sizeof(int),1,output_file);

	//printf(" %c",*Data_Buffer);


	/*printf("fread_num %d\n", fread_num);
	for(i=0;i<4096;i++)
	{
		if((i!=0)&&(i%16==0))
		{
			printf(" \n");
		}
		printf(" %02x",(unsigned char)*(&Data_Buffer[i]));
	}*/
	free(Data_Buffer);
	free(Data_CMP_Buffer);
	fclose(input_file);
	return 0;
}