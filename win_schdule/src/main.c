#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void SchProcess();

void WriteStrToFile(char* str, char* fileName)
{
    FILE *fp = fopen(fileName, "a+");
    if (fp == NULL) {

        printf("Can't open %s\n", fileName);
        return;
    }
    int ret = fputs(str, fp);
    if (ret == EOF) {
        printf("Write file failed\n");
    }
    fclose(fp);
}

void WriteTimeToFile()
{
    struct tm curTime = { 0 };
    _getsystime(&curTime);
    char timeStr[100] = { 0 };
    sprintf_s(timeStr, sizeof(timeStr), "now:%u-%u-%u %02u:%02u:%02u\n",
        curTime.tm_year+1900, curTime.tm_mon + 1, curTime.tm_mday, curTime.tm_hour, curTime.tm_min, curTime.tm_sec);
    printf("%s\n", timeStr);
    WriteStrToFile(timeStr, "exectime.txt");
}

int main()
{
    printf("********hello world ,this is a c program in win10 for schedule********\n");
    //WriteTimeToFile();
    SchProcess();
    return 0;
}