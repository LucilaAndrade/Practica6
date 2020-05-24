#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Persona {
    char nombre[50];
    char id[10];
    int edad;
    int yearOfBirth;
    int estatura;
    int peso;
};

struct Lista {
    struct Persona persona;
    struct Lista *siguiente;
};

struct Lista *nacimiento(struct Lista *lista, int year);

struct Lista *insertar(struct Lista *lista, struct Persona persona);

int consultaGeneral(struct Lista *lista);

int consultaPorID(struct Lista *lista, char id[10], int mostrar);
int consultaPromedios(struct Lista *lista,double *promEdad,double *promEstatura,
                      double *promPeso,int edad, int estatura, double peso,int *i);
int imprimirPersona(struct Persona persona);

int StringIsAlnum(char string[]);

int LeerEnteroPositivo(char mensaje[], int *numero);

int LeerCadena(int lenght, char mensaje[], char cadena[]);

int main() {
    int op, op2;
    int currentYear = 2020;
    struct Lista *lista;
   
    lista = NULL;
    int index;
    char clave[10];

    double promEdad=0,promEstatura=0,promPeso=0;
    int edad=0, estatura=0,peso=0,i=0;

    while (op != 4) {
        printf("[1] Nuevo nacimiento\n"
               "[2] Avanzar tiempo\n"
               "[3] Consultas\n"
               "[4] Terminar\n"
               "Seleccione una opcion: ");

        scanf("%d", &op);
        switch (op) {
            case 1:
                lista = nacimiento(lista, currentYear);
                break;
            case 2:
                break;
            case 3:
                printf("[1]... Consulta General.\n"
                       "[2]... Consulta por clave de identificación.\n"
                       "[3]... Mostrar el promedio de edad, estatura y peso.\n"
                       "[4]... Consulta general de personas eliminadas.");
                scanf("%d", &op2);
                switch (op2) {
                    case 1:
                        consultaGeneral(lista);
                        break;
                    case 2:
                        if (LeerCadena(10, "Ingrese la clave de identificacion: ", clave) == -1) {
                            printf("Clave no valida\n");
                        } else if (consultaPorID(lista, clave, 1) == -1) {
                            printf("La clave de identificacion no ha sido registrada\n");
                        }
                        break;
                    case 3:
                        promEdad=promEstatura=promPeso=edad=estatura=peso=0;
                        i=0;
                        consultaPromedios(lista,&promEdad,&promEstatura,&promPeso, edad, estatura,peso,&i);
                        printf("Peso:%.2f,Estatura:%.2f,Edad:%.2f\n",promPeso,promEstatura,promEdad);
                        break;
                }
                break;
            case 4:
                free(lista);
                exit(1);
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }
    }
    free(lista);
    return 0;
}

struct Lista *nacimiento(struct Lista *lista, int year) {
    struct Persona persona;
    int peso;
    int estatura;
    char id[10];
    char nombre[50];
    int resultado;
    struct Lista *nuevo = NULL;
    int error = 0;
    if (LeerCadena(50, "Ingrese el nombre de la persona: ", nombre) == -1) {
        error = -1;//codigo NOMBRE VACIO
        printf("Nombre no valido\n");
    }
    resultado = StringIsAlnum(nombre);
    if (resultado == 4 || resultado == 1) {

        if (LeerEnteroPositivo("Ingrese el peso en kg: ", &peso) == -1) {
            error = -3;//codigo PESO NEGATIVO
            printf("Peso no valido\n");
        }
        if (peso > 100) {
            error = -4;//codigo PESO EXCESIVO
            printf("Peso no valido\n");
        }

        if (LeerEnteroPositivo("Ingrese al estatura en cm: ", &estatura) == -1) {
            error = -5;//codigo ESTATURA NEGATIVA
            printf("Estatura no valida\n");
        }
        if (estatura > 200) {
            error = -6;//codigo ALTURA EXCESIVO
            printf("Estatura no valida\n");
        }

        if (LeerCadena(50, "La clave de la persona: ", id) == -1) {
            error = -7;//codigo CLAVE VACIA
            printf("Clave no valida\n");
        } else if (consultaPorID(lista, id, 0) != -1) {
            printf("Clave registrada con anterioridad\n");
            error =-9;
        }
        resultado = StringIsAlnum(id);
        if (resultado != 3) {//ALFANUMERICA
            error = -8;//codigo CLAVE NO VALIDA
            printf("Clave no valida\n");
        }
    } else {
        error = -2;//codigo NOMBRE NO VALIDO
        printf("Nombre no valido\n");
    }
    if (error == 0) {
        strcpy(persona.id, id);
        strcpy(persona.nombre, nombre);
        persona.yearOfBirth = year;
        persona.peso = peso;
        persona.estatura = estatura;
        persona.edad = 0;
        return insertar(lista, persona);
    }
    return lista;
}

struct Lista *insertar(struct Lista *lista, struct Persona persona) {
    struct Lista *aux = malloc(sizeof(struct Lista)); //Crear un nuevo nodo.
    aux->persona = persona; //Asignar el valor al nodo.
    aux->siguiente = lista; //Apuntar el nodo al nodo que apuntaba la lista.
    lista = aux; //Hacer que la lista apunte al nodo nuevo.
    printf("%s registrado con exito\n", persona.id); //Escribir en pantalla que se agregó el valor a la lista.
    return lista;
}

int consultaGeneral(struct Lista *lista) {
    int i = 0;
    if (lista != NULL) {
        i = 1;
        imprimirPersona(lista->persona);
        consultaGeneral(lista->siguiente);
    }
    return i;
}

int consultaPorID(struct Lista *lista, char id[10], int mostrar) {
    int i = 0;
    if (lista != NULL) {
        i = 1;
        if (strcmp(lista->persona.id, id) == 0) {
            if (mostrar == 1) {
                imprimirPersona(lista->persona);
            }
            return i;
        }
        consultaPorID(lista->siguiente,id,mostrar);
    }
    return -1;
}

int consultaPromedios(struct Lista *lista,double *promEdad,double *promEstatura,
        double *promPeso,int edad, int estatura, double peso,int *i) {
    if (lista != NULL) {
        (*i)+=1;
        (*promEdad)+=lista->persona.edad+edad;
        (*promEstatura)+=lista->persona.estatura+estatura;
        (*promPeso)+=lista->persona.peso+peso;
        consultaPromedios(lista->siguiente,promEdad,promEstatura,
        promPeso,edad, estatura,peso,i);
    }else {
        (*promEdad) = (*promEdad) / (*i);
        (*promEstatura) = (*promEstatura) / (*i);
        (*promPeso) = (*promPeso) / (*i);
        return *i;
    }

}


int imprimirPersona(struct Persona persona) {
    printf("ID:%s Nombre:%s Edad:%d Estatura:%d Peso:%d Nacimiento:%d\n", persona.id, persona.nombre, persona.edad,
           persona.estatura, persona.peso, persona.yearOfBirth);
}

int LeerEnteroPositivo(char mensaje[], int *numero) {
    int n = *numero;
    printf("%s ", mensaje);
    scanf("%d", numero);
    if (*numero >= 0) {
        return 1;
    } else {
        *numero = n;
        return 0;
    }
}

int LeerCadena(int lenght, char mensaje[], char cadena[]) {
    char tmp[lenght];
    cadena[0] = tmp[0] = '\0';
    printf("%s", mensaje);
    while ((getchar()) != '\n');
    scanf("%[^\n]", tmp);
    if (strlen(tmp) > 0) {
        strcpy(cadena, tmp);
        return 1;
    } else if (tmp[0] == '\0') { return -1; }
}

int StringIsAlnum(char string[]) {
    int alpha = 0;
    int space = 0;
    int number = 0;
    int other = 0;
    for (int i = 0; i < strlen(string); i++) {
        if (isspace(string[i])) { space++; }
        else if (isalpha(string[i])) { alpha = 1; }
        else if (isdigit(string[i])) { number = 2; }
        else { return 0; }
    }
    if ((alpha + number) == 1 && space > 0) { return 4; }
    return (alpha + number);
}