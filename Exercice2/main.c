#include "uspDatabase/uspDatabase.h"
#include "dataHandler/dataHandler.h"
#include "primaryIndex/primaryIndex.h"
#include "list/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10
#define RUN_CODES_PROBLEM 1
#define STRING_SIZE 256

/*INFORMAÇÕES:
    NOME: Ryan Souza Sá Teles
    nUSP: 12822062
    NOME: Silmar Pereira Da Silva Junior
    nUSP: 12623950
    Turma: BSI [021]
    Instituto: Instituto de Ciências Matemáticas e de Computação
    Disciplina: Estrutura de Dados II
    Professor: Leonardo Tórtoro Pereira
*/

int main() {
    FILE *dataFile = fopen("datafile.bin", "wb+");
    if (dataFile == NULL) {
        perror("Error to open Archive");
        exit(EXIT_FAILURE);
    }
    FILE *indexFile = fopen("indexfile.bin", "wb+");
    if (indexFile == NULL) {
        perror("Error to open Archive");
        exit(EXIT_FAILURE);
    }

    LIST *indexList = create_list();

    int RRN = 0;
    long studentSize = get_student_data_size();
    char *line = (char *)malloc(sizeof(char) * STRING_SIZE);
    while (fgets(line, sizeof(char) * STRING_SIZE, stdin)) {
        char *token = strtok(line, " ");
        char *command = token;

        if (select_command(command) == insert_) {
            NUSP nusp;
            NAME name;
            LASTNAME lastName;
            COURSE course;
            GRADE grade;

            token = strtok(NULL, ",");

            nusp = atoi(token);
            strcpy(name, token);

            token = strtok(NULL, ",");
            strcpy(lastName, token);

            token = strtok(NULL, ",");
            strcpy(course, token);

            token = strtok(NULL, ",");
            grade = atof(token);

            STUDENT *student = create_student(nusp, name, lastName, course, grade);
            //Escrevendo Arquivo de Dados
            writeStudentDataInFile(student, dataFile);

            unsigned int studentOffset = RRN * studentSize;
            INDEXFILE *indexData = createIndexData(nusp,studentOffset);
            list_insert(indexList, indexData);
            //Escrever Arquivo de Indice ??? 
            
            erase_student(&student);
        } else if (select_command(command) == search_) {
            unsigned int key;
            scanf("%ud", &key);
            INDEXFILE *registerIndex = sequential_search(indexList, key);


        } else if (select_command(command) == delete_) {
            // delete
        } else if (select_command(command) == exit_) {
            // exit
        } else {
            perror("\n\nCommand not found");
        }
    }
    free(line);

    fclose(dataFile);
    return EXIT_SUCCESS;
}

void readStudentFile(FILE *dataFile, unsigned int studentOffset) {

    fseek(dataFile, studentOffset, SEEK_SET);
    STUDENT *student = readStudentDataInFile(dataFile);

    print_item(student);

    erase_student(&student);
}
