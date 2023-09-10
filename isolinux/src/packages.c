#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funkce pro instalaci balíčků
void installPackage(const char *package) {
    char command[256];
    snprintf(command, sizeof(command), "git clone %s", package);
    system(command);
}

int main() {
    // Otevření konfiguračního souboru
    FILE *configFile = fopen("pkgconf", "r");
    if (configFile == NULL) {
        perror("Chyba při otevírání konfiguračního souboru");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), configFile) != NULL) {
        // Rozdělení řádku na klíč a hodnotu
        char *key = strtok(line, " \t\n=");
        char *value = strtok(NULL, " \t\n=");

        if (key != NULL && value != NULL) {
            // Pokud je klíč "packages" a hodnota je "true", instaluj balíček
            if (strcmp(key, "packages:") == 0 && strcmp(value, "true") == 0) {
                char *package = strtok(NULL, " \t\n");
                if (package != NULL) {
                    printf("Instaluji balíček: %s\n", package);
                    installPackage(package);
                }
            }
            // Pokud je klíč "git-packages", zpracuj URL balíčku a instaluj
            else if (strcmp(key, "git-packages:") == 0) {
                char *package = strtok(NULL, " \t\n");
                if (package != NULL) {
                    printf("Instaluji balíček z Git: %s\n", package);
                    installPackage(package);
                }
            }
        }
    }

    // Zavření konfiguračního souboru
    fclose(configFile);

    return 0;
}
