#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>


int main() {

    xmlParserCtxtPtr ctxt;
    // Création du contexte
    if ((ctxt = xmlCreateFileParserCtxt("myxml.xml")) == NULL) {
        fprintf(stderr, "Erreur lors de la création du contexte\n");
        return EXIT_FAILURE;
    }
    // Analyse
    xmlParseDocument(ctxt);
    // Le document est-il bien formé ?
    if (ctxt->wellFormed) {
        printf("Document XML bien formé\n");
    } else {
        fprintf(stderr, "Document XML mal formé\n");
        xmlFreeParserCtxt(ctxt);
        return EXIT_FAILURE;
    }
    // Libération de la mémoire
    xmlFreeParserCtxt(ctxt);

    return EXIT_SUCCESS;
}