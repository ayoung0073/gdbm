#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gdbm.h>
#include <sys/time.h>

struct timeval before, after;

int main(int argc, char **argv)
{
    int count;
    scanf("%d", &count);

    gettimeofday(&before, NULL);

    datum key_data;
    datum value_data;
    datum return_data;

    GDBM_FILE dbf;

    int block_size = 0;

    char key[10];
    char value[20];

    key_data.dptr = NULL;
    value_data.dptr = value;

    dbf = gdbm_open("custom_enc_dic", block_size, GDBM_WRCREAT | GDBM_FAST, 00664, NULL);
    if (dbf == NULL)
    {
        perror("DB file open error\n");
        exit(0);
    }

    for (int i = 1; i <= count; i++) // count 만큼 반복
    {
        sprintf(key, "%d", i);
        sprintf(value, "%d", 30000); // 고정값

        key_data.dptr = key;
        key_data.dsize = strlen(key) + 1;
        value_data.dsize = strlen(value) + 1;
        if (gdbm_store(dbf, key_data, value_data, GDBM_REPLACE) != 0)
        {
            printf("Item no inserted.\n");
            return -1;
        }
        key_data.dptr = NULL;
    }

    gettimeofday(&after, NULL);
    printf("time: %0.8f sec\n", (after.tv_sec - before.tv_sec) + 1e-6 * (after.tv_usec - before.tv_usec));

    return 0;
}