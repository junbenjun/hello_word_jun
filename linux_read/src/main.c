#include <stdio.h>
#include <stdlib.h>
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed short int16;

typedef struct {
    uint8 sdsid_start[24];
    uint8 sds_num_one_port;
    uint8 rsv[3];
    uint32 cdr_type;
    uint32 sds_type;
    uint8 tx_pn[40];
    uint8 rx_pn[40];
} pic_para_file;

pic_para_file g_picParaFile[] = {
    {{0, 4, 10, 24},
    4,
    {0},
    2,
    4,
    {[7] = 1, 0, 1},
    {0, 0, [11] = 1},},
};

int main()
{
    printf("Hello world\n");
    FILE *fp = fopen("pic_para_file", "ab");
    fwrite((void *)g_picParaFile, sizeof(uint8), sizeof(g_picParaFile), fp);
    fclose(fp);

    FILE *fpr = fopen("pic_para_file", "rb");
    pic_para_file *picPara = (pic_para_file*)malloc(sizeof(pic_para_file));
    uint32 ret = fread((void *)picPara, sizeof(uint8), sizeof(pic_para_file), fpr);
    printf("read file ret %u\n", ret);
    fclose(fpr);
    printf("sdsid :\n");
    for (int i = 0; i < 24; i++) {
        printf("%u ", picPara->sdsid_start[i]);
    }
    printf("\n\n");
    printf("tx pn :\n");
    for (int i = 0; i < 40; i++) {
        printf("%u ", picPara->tx_pn[i]);
    }
    printf("\n\n");
    printf("rx pn :\n");
    for (int i = 0; i < 40; i++) {
        printf("%u ", picPara->rx_pn[i]);
    }
    printf("\n\n");
    printf("cdr type %u\n", picPara->cdr_type);
    printf("\n\n");
    return 0;
}
