#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{

    // expiar1 fichero [-p periodo] [orden]

    char *fichero = argv[1]; //"/home/jesuscg/Documents"

    int periodo = 20;
        if (strcmp(argv[2], "-p") != 0)
        {
           
           printf("Parametro %s desconocido\n",argv[2]);
           return 0;
        }

    periodo = atoi(argv[3]); // convertir argv[3] a entero
    char *orden = argv[4];   // mesnaje cuando sea modfificado
    int fd, wd;              // file decripto y watch descriptor
    char buf[200];
    fd = inotify_init();
    wd = inotify_add_watch(fd, fichero, IN_CLOSE_WRITE);

    while (1)
    {
        sleep(periodo);
        read(fd, buf, 200);
        printf("orden:%s . %s\n", orden, ((struct inotify_event *)buf)->name);
    }
    return 0;
}
