#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gdbm.h>
#include <sys/time.h>

#define DIFF(a, b) ((a) >= (b) ? (a) - (b) : (b) - (a))

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

    key_data.dptr = NULL;

    dbf = gdbm_open("custom_enc_dic", block_size, GDBM_WRCREAT, 00664, NULL);
    if (dbf == NULL)
    {
        perror("DB file open error\n");
        exit(0);
    }

    for (int i = 1; i <= count; i++)
    {
        key_data.dptr = (char *)&i;
        key_data.dsize = sizeof(int);

        return_data = gdbm_fetch(dbf, key_data);
        free(return_data.dptr);
        key_data.dptr = NULL;
    }

    for (int i = 1; i <= count; i++)
    {
        key_data.dptr = (char *)&i;
        key_data.dsize = sizeof(int);

        if (gdbm_delete(dbf, key_data) != 0)
        {
            printf("Item not found or deleted\n");
            return -1;
        }
        key_data.dptr = NULL;
    }

    gettimeofday(&after, NULL);
    printf("time: %0.8f sec\n", (after.tv_sec - before.tv_sec) + 1e-6 * DIFF(after.tv_usec, before.tv_usec));

    return 0;
}