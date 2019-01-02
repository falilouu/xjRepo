
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jsmn.h"

#define JSON_FILE_PATH "myjson.json"
#define BUFFER_SIZE 5000
#define MAX_TOKEN_COUNT 128

// lecture du fichier json
void readfile(char *filepath, char *fileContent)
{
    FILE *f;
    char c;
    int index;
    f = fopen(filepath, "rt");
    while ((c = fgetc(f)) != EOF)
    {
        fileContent[index] = c;
        index++;
    }
    fileContent[index] = '\0';
}

//verification de la syntaxe du fichier json
int parseJSON(char *filepath)
{

    char JSON_STRING[BUFFER_SIZE];

    readfile(filepath, JSON_STRING);

    int i;
    int r;
    jsmn_parser p;//instanciation d'un parseur
    jsmntok_t t[MAX_TOKEN_COUNT]; //nombre de symbole inferieur a MAX_TOKEN_COUNT
    jsmn_init(&p);//initialisation ou reinitialisation du parseur

    //verifaction du contenu du fichier
    r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t) / (sizeof(t[0])));

    if (r < 0)
    {
        printf("Document JSON mal formé: %d\n", r);
        return 1;
    }
    else
    {
        printf("Document JSON bien formé");
    }
    
    
    return 0;
}

int main()
{
    parseJSON(JSON_FILE_PATH);
    return 0;
}
