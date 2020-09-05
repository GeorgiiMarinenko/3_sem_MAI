#include <iostream>
#include <stdio.h>




#pragma warning (disable : 4996)


const char* FnameIn = "FileInput.txt";
const char* Encripted = "EncriptedFile.txt";
const char* Decripted = "DecriptedFile.txt";


//const int shift = 26;
int Encryption(int shift);
int Decryption(int shift);

int main()
{
	int shift;
	printf("Enter how many positions to shift \n");
	scanf("%d", &shift);
	/*if ((shift < 0) || (shift > 26))
	{
		printf("Error!Incorrect shift!!!");
		return 0;
	}*/
	while (shift > 16)
	{
		shift -= 26;
	}
	while (shift < 0)
	{
		shift += 26;
	}
	if (Encryption(shift) != 0)
	{
		printf("Error of Encryption!\n");
		return 0;
	}
	printf("Decreption of file: \n");
	if (Decryption(shift) != 0)
	{
		printf("Error of Decryption!\n");
		return 0;
	}
	printf("%c", '\n');
	//Decryption(shift);
	return 0;
}

int Encryption(int shift)
{
	FILE* in;
	FILE* out;
	in = fopen(FnameIn, "r");
	out = fopen(Encripted, "w");
	unsigned char* str;
	long size;
	int flag;
	int i = 0;
	if (in != NULL)
	{
		fseek(in, 0, SEEK_END);
		size = ftell(in);
		fseek(in, 0, SEEK_SET);

		if (size == 0)
		{
			printf("File is empty\n");
			return 2;

		}
		str = (unsigned char*)malloc(256);
		while (fgets((char*)str, 256, in) != NULL)
		{

			i = 0;
			while ((str[i] != '\0'))
			{
				flag = 0;
				if (str[i] >= 'A' && str[i] <= 'Z')
				{
					str[i] = str[i] + (shift % 26);
					if (str[i] > 'Z')
					{
						str[i] = 'A' + (str[i] - 'Z') - 1;
					}
					//printf("%d ", (int)str[i]);
					fprintf(out, "%c", str[i]);
					flag = 1;
				}
				if (str[i] >= 'a' && str[i] <= 'z')
				{
					str[i] = str[i] + (shift % 26);
					if (str[i] > 'z')
					{
						str[i] = 'a' + (str[i] - 'z') - 1;
					}
					//printf("%d ", (int)str[i]);
					fprintf(out, "%c", str[i]);
					flag = 1;
				}
				else if (flag == 0)
				{
					fprintf(out, "%c", str[i]);
				}
				i++;
			}
		}
		fclose(in);
		fclose(out);
	}
	else
	{

		perror("File not found");
		return 1;
	}

	return 0;
}
int Decryption(int shift)
{
	FILE* in;
	FILE* out;
	in = fopen(Encripted, "r");
	out = fopen(Decripted, "w");
	char str[256];
	long size;
	int flag;
	int i = 0;

	printf("%s - Decription\n", Encripted);
	if (in != NULL)
	{
		fseek(in, 0, SEEK_END);
		size = ftell(in);
		fseek(in, 0, SEEK_SET);

		if (size == 0)
		{
			printf("File is empty\n");
			return 2;

		}
		while (fgets(str, 256, in) != NULL)
		{
			i = 0;
			while ((str[i] != '\0'))
			{
				flag = 0;
				if (str[i] >= 'A' && str[i] <= 'Z')
				{
					str[i] = str[i] - (shift % 26);
					if (str[i] < 'A')
					{
						str[i] = 'Z' - ('A' - str[i]) + 1;
					}
					printf("%c", str[i]);
					fprintf(out, "%c", str[i]);
					flag = 1;
				}
				if (str[i] >= 'a' && str[i] <= 'z')
				{
					str[i] = str[i] - (shift % 26);
					if (str[i] < 'a')
					{
						str[i] = 'z' - ('a' - str[i]) + 1;
					}
					printf("%c", str[i]);
					fprintf(out, "%c", str[i]);
					flag = 1;
				}
				else if (flag == 0)
				{

					printf("%c", str[i]);
					fprintf(out, "%c", str[i]);
				}
				i++;
			}
		}
		fclose(in);
		fclose(out);
	}
	else
	{

		printf("File not found\n");
		getchar();
	}
	return 0;
}