#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define MAX_NAME_LEN 1000
#define MAX_SCH_TIMES 100
#define SCH_ERROR -1
#define SCH_OK 0

char g_ExecuProgramName[MAX_NAME_LEN] = "writetime.exe";

typedef struct {
    int hour;
    int min;
} SchTime;
SchTime g_SchTimes[MAX_SCH_TIMES] = {0};
unsigned int g_RealSchTimes = 0;

unsigned int g_NextProcessSchIndex = 0;

void ExecuOneProgram(const char *programName)
{
    system(programName);
}

SchTime GetCurTime()
{
    SchTime curTime = {0};
    time_t now;
    time(&now);
    struct tm *lt;
    lt = localtime(&now);
    curTime.hour = lt->tm_hour;
    curTime.min = lt->tm_min;

    return curTime;
}
#define BOOL int
#define TRUE 1
#define FALSE 0
BOOL IsTimeToDoSch(SchTime curTime)
{
    SchTime nextSchTime = g_SchTimes[g_NextProcessSchIndex];
    if ((curTime.hour == nextSchTime.hour)
        && (curTime.min >= nextSchTime.min) && (curTime.min < (nextSchTime.min + 1))) {
        g_NextProcessSchIndex++;
        if (g_NextProcessSchIndex == g_RealSchTimes) {
            g_NextProcessSchIndex = 0;
        }
        return TRUE;
    }
    return FALSE;
}
void PrintSchTimes()
{
    printf("************get all sch times %u ok************\n", g_RealSchTimes);
    for (int j = 0; j < g_RealSchTimes; j++) {
        printf("    schdule %u  %02u:%02u\n", j, g_SchTimes[j].hour, g_SchTimes[j].min);
    }
}

int ReadCfgFromFile()
{
    char cfgFile[20] = "sch.txt";
    FILE *fp = fopen(cfgFile, "r");
    if (fp == NULL) {
        printf("read cfg file '%s' failed\n", cfgFile);
        return SCH_ERROR;
    }
    if (!fgets(g_ExecuProgramName, MAX_NAME_LEN, fp)) {
        printf("get exe program failed\n");
        return SCH_ERROR;
    }
    printf("    exe program is %s\n", g_ExecuProgramName);

    char str[MAX_NAME_LEN] = {0};
    int i = 0;
    while (fgets(str, MAX_NAME_LEN, fp)) {
        /*
        int ret = sscanf(str, "%u:%u", &g_SchTimes[i].hour, &g_SchTimes[i].min);
        printf("read %s ret %d\n", str, ret);
        memset(str, 0, sizeof(str));
        */
        if (sscanf(str, "%u:%u", &g_SchTimes[i].hour, &g_SchTimes[i].min) != 2) {
            printf("get sch time failed\n");
            break;
        }
        if ((g_SchTimes[i].hour > 23) || (g_SchTimes[i].min > 59)) {
            printf("time format is error. %s\n", str);
            break;
        }
        i++;
        if (i >= MAX_SCH_TIMES) {
            printf("get max sch times %u\n", i);
            break;
        }
    }
    fclose(fp);
    g_RealSchTimes = i;
    PrintSchTimes();
    return SCH_OK;
}

int CmpSchTime(const void *a, const void *b)
{
    if (((SchTime *)a)->hour != ((SchTime *)b)->hour)
    {
        return ((SchTime *)a)->hour - ((SchTime *)b)->hour;
    }

    return ((SchTime *)a)->min - ((SchTime *)b)->min;
}

void SortSchTimes()
{
    qsort(g_SchTimes, g_RealSchTimes, sizeof(SchTime), CmpSchTime);
    PrintSchTimes();
}

int InitProcess()
{
    if (ReadCfgFromFile() != SCH_OK) {
        printf("get cfg from file failed\n");
        return SCH_ERROR;
    }
    SortSchTimes();
    SchTime curTime = GetCurTime();
    int i = 0;
    for (; i < g_RealSchTimes; i++) {
        SchTime nextT = g_SchTimes[i];
        if (curTime.hour > nextT.hour) {
            continue;
        }

        if ((curTime.hour == nextT.hour) && (curTime.min > nextT.min)) {
            continue;
        }

        break;
    }
    g_NextProcessSchIndex = (i == g_RealSchTimes) ? 0 : i;
    printf(">>>>>schprocess start success. next schdule index is %u time is %02u:%02u, curtime is %02u:%02u\n",
        g_NextProcessSchIndex, g_SchTimes[g_NextProcessSchIndex].hour, g_SchTimes[g_NextProcessSchIndex].min,
        curTime.hour, curTime.min);
    return SCH_OK;
}

void SchProcess()
{
    if (InitProcess() != SCH_OK) {
        printf("init sch failed>>>>>>>>>>>>>\n");
        getchar();
        return;
    }
    while (1) {
        SchTime curTime = GetCurTime();
        if (IsTimeToDoSch(curTime)) {
            printf("Is time to do schedule>>>>>>>>>>>>\n");
            ExecuOneProgram(g_ExecuProgramName);
            printf("next schdule index is %u time is %02u:%02u, curtime is %02u:%02u\n",
                g_NextProcessSchIndex, g_SchTimes[g_NextProcessSchIndex].hour, g_SchTimes[g_NextProcessSchIndex].min,
                curTime.hour, curTime.min);
        }
        //printf("curtime is %u:%u\n", curTime.hour, curTime.min);
        sleep(30);
    }
}
