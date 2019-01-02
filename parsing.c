#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include "jsmn.h"

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
        printf("Le document JSON est mal formé: %d\n", r);
        return 1;
    }
    else
    {
        printf("Le document JSON est bien formé\n");
    }
    
    
    return 0;
}


int main(int argc, char *argv[]) 
{
    char *input;
    char *filepath;
    //parsing des arguments 
    if (argc<5 || argc>5) 
    {
        printf("Le nombre de parmètres n'est pas valide, veuillez réessayer!\n");
        return EXIT_SUCCESS;
    }
    
    //Type du fichier: JSON ou XML
    if (strcmp(argv[1], "-i") == 0) 
    {
        
        if (strcmp(argv[2], "xml") == 0) 
        {
            input = "xml";
        }
        else if(strcmp(argv[2], "json") == 0)
        {
            input = "json";
        } 
        else
        {
            printf("Veuillez choisir un input valide(json ou xml)!\n");
            return EXIT_SUCCESS;
        }
        
    }
    else
    {
        printf("L'option doit etre -i!");
        return EXIT_SUCCESS;
    }
    
    //Recuperation du chemin du fichier
    if (strcmp(argv[3], "-f") == 0) 
    {
        filepath = argv[4];
    }
    else
    {
        printf("L'option doit etre -f!");
        return EXIT_SUCCESS;
    }

    //Parsing du document XML ou JSON
    if (input == "xml")
    {
        xmlParserCtxtPtr ctxt;
        // Création du contexte
        if ((ctxt = xmlCreateFileParserCtxt(filepath)) == NULL) 
        {
            fprintf(stderr, "Erreur lors de la création du contexte\n");
            return EXIT_FAILURE;
        }
        // Analyse
        xmlParseDocument(ctxt);
        // Le document est-il bien formé ?
        if (ctxt->wellFormed) 
        {
            printf("Le document XML est bien formé\n");
        } 
        else 
        {
            fprintf(stderr, "Le document XML est mal formé\n");
            xmlFreeParserCtxt(ctxt);
            return EXIT_FAILURE;
        }
        // Libération de la mémoire
        xmlFreeParserCtxt(ctxt);

        return EXIT_SUCCESS;
    }
    else
    {
        parseJSON(filepath);
        return 0;
    }
    

  return 0;  
}