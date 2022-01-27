#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void RecordTime()
{
    time_t now;
    time(&now);
    struct tm *lt;
    lt = localtime(&now);

    char cfgFile[20] = "record.log";
    FILE *fp = fopen(cfgFile, "a+");
    if (fp == NULL) {
        printf("read cfg file '%s' failed\n", cfgFile);
        return;
    }
    char str[100] = { 0 };
    sprintf(str, "now is %04u-%02u-%02u %02u:%02u:%02u\n",
        lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
    fputs(str, fp);

    fclose(fp);
}
int main()
{
    //printf("Hello world\n");
    RecordTime();
    return 0;
}
