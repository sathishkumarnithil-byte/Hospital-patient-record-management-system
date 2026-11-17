#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "patients.dat"

typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
} Patient;

void readLine(char *buf, int size) {
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = '\0';
}

int readInt(void) {
    char buf[20];
    fgets(buf, sizeof(buf), stdin);
    return atoi(buf);
}

int idExists(int id) {
    Patient p;
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) return 0;
    while (fread(&p, sizeof(Patient), 1, fp) == 1) {
        if (p.id == id) { fclose(fp); return 1; }
    }
    fclose(fp);
    return 0;
}

void addPatient(void) {
    Patient p;
    printf("Patient ID: ");
    p.id = readInt();
    if (idExists(p.id)) { printf("ID already exists!\n"); return; }
    printf("Name: ");    readLine(p.name, sizeof(p.name));
    printf("Age: ");     p.age = readInt();
    printf("Gender: ");  readLine(p.gender, sizeof(p.gender));
    printf("Disease: "); readLine(p.disease, sizeof(p.disease));

    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) { printf("File error!\n"); return; }
    fwrite(&p, sizeof(Patient), 1, fp);
    fclose(fp);
    printf("Patient added successfully.\n");
}

void viewPatients(void) {
    Patient p;
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { printf("No records found.\n"); return; }
    printf("\n%-6s %-20s %-5s %-8s %-20s\n", "ID", "Name", "Age", "Gender", "Disease");
    printf("--------------------------------------------------------------\n");
    while (fread(&p, sizeof(Patient), 1, fp) == 1)
        printf("%-6d %-20s %-5d %-8s %-20s\n", p.id, p.name, p.age, p.gender, p.disease);
    fclose(fp);
}

void searchPatient(void) {
    Patient p;
    int id, found = 0;
    printf("Enter ID to search: ");
    id = readInt();
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { printf("No records found.\n"); return; }
    while (fread(&p, sizeof(Patient), 1, fp) == 1) {
        if (p.id == id) {
            printf("\nFound -> ID: %d | Name: %s | Age: %d | Gender: %s | Disease: %s\n",
                   p.id, p.name, p.age, p.gender, p.disease);
            found = 1;
            break;
        }
    }
    if (!found) printf("Patient not found.\n");
    fclose(fp);
}

void deletePatient(void) {
    Patient p;
    int id, found = 0;
    printf("Enter ID to delete: ");
    id = readInt();
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { printf("No records found.\n"); return; }
    FILE *temp = fopen("temp.dat", "wb");
    while (fread(&p, sizeof(Patient), 1, fp) == 1) {
        if (p.id == id) found = 1;
        else fwrite(&p, sizeof(Patient), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);
    printf(found ? "Patient deleted.\n" : "Patient not found.\n");
}

int main(void) {
    int choice;
    do {
        printf("\n=== Hospital Patient Record Management System ===\n");
        printf("1. Add Patient\n2. View All Patients\n3. Search Patient\n4. Delete Patient\n5. Exit\n");
        printf("Choice: ");
        choice = readInt();
        switch (choice) {
            case 1: addPatient();    break;
            case 2: viewPatients();  break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
    return 0;
}