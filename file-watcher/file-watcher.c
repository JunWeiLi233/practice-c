#include <stdio.h>
#include <sys/inotify.h>
#include <stdbool.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s <watch-directionary>\n", argv[0]);
        return -1;
    }

    char *watch_dir = argv[1];
    int fd = inotify_init();
    if (fd < 0){
        perror("inotify_init");
        return -1;
    }

    int wd = inotify_add_watch(fd, watch_dir, IN_CLOSE_WRITE | IN_DELETE);
    if (wd < 0){
        perror("inotify_add_watcher");
        return -1;
    }
    printf("Watching directory %s\n\n", watch_dir);

    char buffer[4096];
    while(true){
        // read events from the file descriptor
        ssize_t len = read(fd, buffer, sizeof(buffer));
        if(len<0)
        {
            perror("Can't read from file");
            return -1;
        }
        
        for(size_t i=0;i<len;)
        {
            struct inotify_event *event= (struct inotify_event *) &buffer[i];

            printf("%s: %s\n", (IN_CLOSE_WRITE & event->mask) == 0? "Deleted": "Created", event->name);

            i += sizeof(struct inotify_event) + event->len;
        }

    }
    return 0;
}