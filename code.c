#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MASTER_FILE "master.dat"
#define VAULT_FILE  "vault.dat"
#define KEY 'A'

struct Credential {
    char site[50];
    char username[50];
    char password[50];
};

void encrypt(char *data) {
    for (int i = 0; data[i] != '\0'; i++)
        data[i] ^= KEY;
}

void inputPassword(char *password) {
    char ch;
    int i = 0;

    while (1) {
        ch = getch();

        if (ch == 13) {        
            password[i] = '\0';
            printf("\n");
            break;
        } else if (ch == 8 && i > 0) { 
            printf("\b \b");
        } else if (i < 49) {
            password[i++] = ch;
            printf("*");
        }
    }
}


void createMasterPassword() {
    char pass[50];

    printf("Create Master Password: ");
    inputPassword(pass);
    encrypt(pass);

    FILE *fp = fopen(MASTER_FILE, "wb");
    fwrite(pass, sizeof(pass), 1, fp);
    fclose(fp);

    printf("Master password created. Restart program.\n");
}

int checkMasterPassword() {
    char input[50], stored[50];

    printf("Enter Master Password: ");
    inputPassword(input);
    encrypt(input);

    FILE *fp = fopen(MASTER_FILE, "rb");
    fread(stored, sizeof(stored), 1, fp);
    fclose(fp);

    if (strcmp(input, stored) == 0) {
        printf("Access Granted.\n");
        return 1;
    }

    printf("Access Denied.\n");
    return 0;
}


int isSiteDuplicate(const char *site) {
    struct Credential c;
    FILE *fp = fopen(VAULT_FILE, "rb");
    if (!fp) return 0;

    while (fread(&c, sizeof(c), 1, fp)) {
        if (strcmp(c.site, site) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void addCredential() {
    struct Credential c;

    printf("Site: ");
    fgets(c.site, 50, stdin);
    c.site[strcspn(c.site, "\n")] = '\0';

    if (isSiteDuplicate(c.site)) {
        printf("Site already exists.\n");
        return;
    }

    printf("Username: ");
    fgets(c.username, 50, stdin);
    c.username[strcspn(c.username, "\n")] = '\0';

    printf("Password: ");
    inputPassword(c.password);
    encrypt(c.password);

    FILE *fp = fopen(VAULT_FILE, "ab");
    fwrite(&c, sizeof(c), 1, fp);
    fclose(fp);

    printf("Credential saved.\n");
}

void viewCredentials() {
    struct Credential c;
    FILE *fp = fopen(VAULT_FILE, "rb");

    if (!fp) {
        printf("No credentials found.\n");
        return;
    }

    while (fread(&c, sizeof(c), 1, fp)) {
        encrypt(c.site);
        encrypt(c.username);
        encrypt(c.password);
        printf("\nSite: %s\nUsername: %s\nPassword: %s\n",
               c.site, c.username, c.password);
        encrypt(c.password);
    }

    fclose(fp);
}

void deleteCredential() {
    char target[50];
    struct Credential c;
    int found = 0;

    printf("Enter site to delete: ");
    fgets(target, 50, stdin);
    target[strcspn(target, "\n")] = '\0';

    FILE *fp = fopen(VAULT_FILE, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (!fp || !temp) {
        printf("File error.\n");
        return;
    }

    while (fread(&c, sizeof(c), 1, fp)) {
        if (strcmp(c.site, target) != 0)
            fwrite(&c, sizeof(c), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove(VAULT_FILE);
    rename("temp.dat", VAULT_FILE);

    if (found)
        printf("Deleted successfully.\n");
    else
        printf("Site not found.\n");
}


void menu() {
    int choice;

    while (1) {
        printf("\n=== PASSWORD MANAGER ===\n");
        printf("1. Add Credential\n");
        printf("2. View Credentials\n");
        printf("3. Delete Credential\n");
        printf("4. Exit\n");
        printf("Choice: ");

        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1: addCredential(); break;
            case 2: viewCredentials(); break;
            case 3: deleteCredential(); break;
            case 4: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
}


int main() {
    FILE *fp = fopen(MASTER_FILE, "rb");

    if (!fp) {
        createMasterPassword();
        return 0;
    }
    fclose(fp);

    if (!checkMasterPassword())
        return 0;

    menu();
}
