#include <stdlib.h>   
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

void ShowCatalogContent(char *path)
{
    DIR *dir;
    struct dirent *d;
    
    dir = opendir(path);
    if (dir == NULL) 
    {
    	printf("An error occured while opening the catalog.\n");
        
        exit(1);
    }

    while ((d = readdir(dir)) != NULL)
    {
        printf("%s\n", d->d_name);
    }

    closedir(dir);
}

int main(int argc, char *argv[])
{
    printf("Root catalog: \n");
    ShowCatalogContent("/");
    
    char path[255];
    getcwd(path, 255);
    
    printf("\nCurrent catalog's path: %s\n", path);
    ShowCatalogContent(path);
    
    exit(0);
}

