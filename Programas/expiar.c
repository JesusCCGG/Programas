#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 6)
    {
        printf("Uso: %s fichero [-p periodo] [orden]\n", argv[0]);
        return 1;
    }
    char *fichero = argv[1];
    int periodo = 30;
    char *orden = "ls -l";

    // Verificar opciones adicionales
    int i;
    for (i = 2; i < argc; i++)
    {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc)
        {
            periodo = atoi(argv[i + 1]);
            i++;
        }
        else
        {
            orden = argv[i];
        }
    }

    struct stat st;
    time_t ultima_modificacion = 0;

    while (1)
    {
        if (stat(fichero, &st) == 0)
        {
            if (st.st_mtime > ultima_modificacion)
            {
                ultima_modificacion = st.st_mtime;
                system(orden);
            }
        }
        else
        {
            printf("Error al consultar el estado del fichero.\n");
            return 1;
        }

        sleep(periodo);
    }

    return 0;
}