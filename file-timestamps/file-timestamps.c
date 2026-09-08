#include <stdio.h>
#include <utime.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc !=2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }

    char *filename = argv[1];

    time_t current_time = time(NULL);
    struct tm * parsed_time = localtime(&current_time);

    parsed_time->tm_year = 100; //to year 2000
    time_t modified_time = mktime(parsed_time);
    struct utimbuf updated_times= {modified_time, modified_time};
    int res = utime(filename, &updated_times);

    if(res != 0)
    {
        perror("Failed updating access and modification times");
        return -1;
    }

    printf("filename: %s\n", filename);
    return 0;
}