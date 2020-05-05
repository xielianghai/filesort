#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include "filesort.h"
/**
*函数说明:通过接受用户输入的源文件名以及目标文件名，
*         按文件内容的二进制升序排序
*参数说明：argc 输入的参数个数
*         argv 输入的参数
*/
int main(int argc, char *argv[])
{ 
	int ret = 0;
	
	if (argc < 3)
	{
		printf("input args error!\n");
		return 1;
	}
	if (0 == strcmp(argv[1], argv[2]))
	{
		printf("source file name cannot be equals target file name!\n");
		return 1;
	}
	ret = file_sort(argv[1], argv[2]);
	
	/*ret != 0,sort fail*/
	if (ret)
	{
		printf("sort fail!\n");
		return 1;
	}
	
	return 0;
}
/**
*函数功能：将文件内容按二进制升序排序
*参数说明：sf 源文件名
*          tf 目标文件名 
*/
int file_sort(const char *sf, const char *tf)
{
	FILE *prf = NULL;
	FILE *pwf = NULL;
	int read_bytes = 0;		
	int write_bytes = 0;	
	int idx = 0;
	int flag = 0;
	unsigned long cnt = 0;
	unsigned char buffer[BUFFER_SIZE];
	unsigned long arr[MAX_ARR_SIZE]={0};
	
	assert(NULL != sf);
	assert(NULL != tf);
	
	do
	{
		prf = fopen(sf, "rb");
		if (NULL == prf)
		{
			printf("cannot open the file:%s\n", sf);
			flag = 1; /*flag sort fail*/
			break;
		}
		
		pwf = fopen(tf, "wb");
		if (NULL == pwf)
		{
			printf("cannot create the file:%s\n", tf);
			flag = 1; /*flag sort fail*/
			break;
		}
		
		/*read file and sort chars*/
		while ((read_bytes = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, prf)))
		{
			if ((-1 == read_bytes) && (errno != EINTR))
			{
				break;
			}
			for (idx = 0; idx < read_bytes; idx++)
			{
				arr[buffer[idx]]++;
			}/* end for */
		}/* end while */
			
		/* write target file with sorted chars*/
		for (idx = 0; idx < MAX_ARR_SIZE; idx++)
		{
			for (cnt = 0; cnt < arr[idx]; cnt++)
			{
				buffer[write_bytes++] = idx;
				if ((write_bytes % BUFFER_SIZE) == 0)
				{
					fwrite(buffer, sizeof(unsigned char), BUFFER_SIZE, pwf);
					write_bytes = 0;
				}
			}
		}
		
		if (write_bytes > 0)
		{
			fwrite(buffer, sizeof(unsigned char), write_bytes, pwf);
		}
		flag = 0;       /*flag sort ok*/
	} while(0);
	
	/*close source file and target file stream*/
	fclose(prf);
	fclose(pwf);
	
	return flag;
}
