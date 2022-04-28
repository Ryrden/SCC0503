#include "./fileHandler/fileHandler.h"
#include "./uspDatabase/uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10

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

long int getDataSize(FILE *);

int main() {
    NUSP nusp;
    NAME name;
    COURSE course;
    GRADE grade;

    // Leitura na ordem
    //[Numero USP][Nome][Curso][Nota]]

    FILE *dataFile = fopen("datafile.bin", "wb+");
    if (dataFile == NULL) {
        perror("Error to open Archive");
        exit(EXIT_FAILURE);
    }

    char *line = (char *)malloc(sizeof(char) * 256);
    while (fgets(line, sizeof(char) * 256, stdin)) {
        char *token = strtok(line, ",");
        nusp = atoi(token);
        token = strtok(NULL, ",");
        if (!token)
            break;
        strcpy(name, token);
        token = strtok(NULL, ",");
        strcpy(course, token);
        token = strtok(NULL, ",");
        grade = atof(token);

        STUDENT *student = create_student(nusp, name, course, grade);
        writeStudentDataInFile(student, dataFile);
    }
    free(line);

    long dataSize = getDataSize(dataFile);
    long studentSize = get_student_data_size();
    for (int i = dataSize - TAM; i < dataSize; i += studentSize) {
        STUDENT *student = readStudentDataInFile(dataFile);
        print_student(student);
    }

    return EXIT_SUCCESS;
}

long int getDataSize(FILE *file) {
    long int fileSize, structSize, dataSize;

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    structSize = get_student_data_size();
    dataSize = (fileSize / structSize); // key on the struct

    return dataSize;
}
