#include <stdio.h>
#include <locale.h>
const char* FnameIn = "input.txt"; //Файл с входными данными
const char* Encripted = "EncriptedFile.txt"; //Файл с закодированным текстом
const char* Decripted = "DecriptedFile.txt"; //Выходной файл с раскодированным текстом

 
const unsigned char BigKirill[] = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
const unsigned char SmallKirill[] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
 
 
int Encryption(int shift); //Функция кодирования текста
int Decryption(int shift); //Функция декодирования текста
 
int main()
{
 setlocale(LC_ALL, "Rus");
 int shift; //Переменная сдвига
 
 printf("Enter how many positions to shift \n");
 //scanf("%d", &shift); //Ввод сдвига
 if (scanf("%d", &shift) == 0)
 {
  printf("Incorrect shift\n");
  return 0;
 }
 if (shift < 0)
 {
  printf("Incorrect shift\n");
  return 0;
 }
 //Провекри на выходные данные функций
 if (Encryption(shift) != 0)
 {
  printf("Error of Encryption!\n");
  return 0;
 }
 printf("Decreption of file \n");
 if (Decryption(shift) != 0)
 {
  printf("Error of Decryption!\n");
  return 0;
 }
 printf("%c", '\n');
 return 0;
}
//Функция кодирования текста
int Encryption(int shift)
{
 FILE* in;
 FILE* out;
 in = fopen(FnameIn, "r");
 out = fopen(Encripted, "w");
 unsigned char* str;
 str = (unsigned char*)malloc(256);
 
 long size;
 int flag;
 int i = 0;
 int j=0;
 if (in != NULL)
 {
  fseek(in, 0, SEEK_END);
  size = ftell(in); //Поиск размера файла
  fseek(in, 0, SEEK_SET);
 
  if (size == 0)
  {
   printf("File is empty\n");
   return 2;
  }
  while (fgets(str, 256, in) != NULL)
  {
    
   i = 0;
    
   while ((str[i] != '\0')) //Чтение по строкам
   {
    flag = 0;
     
     
    for (j=0; j < 33; j++)    //КИРИЛЛИЦА
    {
     if (str[i] == SmallKirill[j])
     {
      str[i] = BigKirill[j];
     }
     if (str[i] == BigKirill[j])
     {
      int NewPos = j + (shift % 33);
    
      if (NewPos>32)
      {
       while (NewPos > 32)
       {
        NewPos -= 32;
       }
       NewPos -= 1;
      }
       str[i] = BigKirill[NewPos];
       fprintf(out, "%c", str[i]);
       flag = 1;
       break;
     }
    }
    if (str[i] >= 'A' && str[i] <= 'Z') /*Проверка на соответсвие прописному символу
    соответствующего диапазона символов с кодами ASCII*/
    {
     str[i] = str[i] + (shift % 26);
     if (str[i] > 'Z')
     {
      str[i] = 'A' + (str[i] - 'Z') - 1;
     }
     // printf("%d " , (int)str[i]);
     fprintf(out, "%c", str[i]);
     flag = 1;
    }
    if (str[i] >= 'a' && str[i] <= 'z') /*Проверка на соответсвие строчному символу
    соответствующего диапазона символов с кодами ASCII*/
    {
     str[i] = str[i] + (shift % 26);
     if (str[i] > 'z')
     {
      str[i] = 'a' + (str[i] - 'z') - 1;
     }
     // printf("%d " , (int)str[i]);
     fprintf(out, "%c", str[i]);
     flag = 1;
    }
    else if (flag == 0)//Если в строке символ - не буква
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
 
int Decryption(int shift) //Функцияя декодирования текста
{
 FILE* in;
 FILE* out;
 in = fopen(Encripted, "r");
 out = fopen(Decripted, "w");
 unsigned char str[256];
 long size;
 int flag;
 int i = 0;
 int j = 0;
 int NewPos;
 printf("%s - дешифрование \n", Encripted);
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
     fprintf(out, "%c",
             str[i]);
                  flag = 1;
                 }
                 else if (str[i] >= 'a' && str[i] <= 'z')
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
                 else
                 {
                  for (j = 0; j < 33; j++)    //КИРИЛЛИЦА
                  {
                   if (str[i] == BigKirill[j])
                   {
                    NewPos = j - (shift % 33);
                    if (NewPos < 0)
                    {
                     while (NewPos < 0)
                     {
                      NewPos += 32;
                     }
                     NewPos += 1;
                    }
                    str[i] = BigKirill[NewPos];
                    printf("%c", str[i]);
                    fprintf(out, "%c", str[i]);
                    flag = 1;
                    break;
                   }
                  }
                 }
                  if (flag == 0)
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
