#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

// Funkce pro instalaci balíčků
void cloneGitRepository(const char *url) {
    char command[MAX_URL_LENGTH + 20]; // Přidáme místo pro "git clone " a další parametry
    snprintf(command, sizeof(command), "git clone %s", url);
    system(command);
}

int main() {
    // Otevření konfiguračního souboru
    FILE *configFile = fopen("kernel.get", "r");
    if (configFile == NULL) {
        perror("Chyba při otevírání konfiguračního souboru");
        return 1;
    }

    char url[MAX_URL_LENGTH];
    while (fgets(url, sizeof(url), configFile) != NULL) {
        // Odstraníme bílé znaky (mezeru, tabulátor, nový řádek) na začátku a konci řetězce
        char *trimmedUrl = url;
        while (*trimmedUrl != '\0' && (*trimmedUrl == ' ' || *trimmedUrl == '\t' || *trimmedUrl == '\n')) {
            trimmedUrl++;
        }

        // Pokud řádek není prázdný, provedeme git clone
        if (*trimmedUrl != '\0') {
            printf("Provádím git clone pro URL: %s\n", trimmedUrl);
            cloneGitRepository(trimmedUrl);
        }
    }

    // Zavření konfiguračního souboru
    fclose(configFile);

    return 0;
}
