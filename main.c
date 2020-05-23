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

struct Nodo {
    struct Persona persona;
    struct Nodo *siguiente;
};


int nacimiento(struct Nodo *lista, int year);

int imprimirPersona(struct Persona persona);
int imprmirListaDePersonas(struct Nodo *lista);

int StringIsAlnum(char string[]);

int LeerEnteroPositivo(char mensaje[], int *numero);
int LeerCadena(int lenght, char mensaje[], char cadena[]);

int main() {
    int op;
    int currentYear=2020;
    struct Nodo *lista = NULL;
    while(op!=4) {
        printf("[1] Nuevo nacimiento\n"
               "[2] Avanzar tiempo\n"
               "[3] Consultas\n"
               "[4] Terminar\n"
               "Seleccione una opcion: ");

        scanf("%d", &op);
        switch (op) {
            case 1:
                switch (nacimiento(lista, currentYear)){
                    case -1://codigo NOMBRE VACIO
                    case -2:
                    printf("Nombre no valido\n");
                    break;

                    case -3://codigo PESO NEGATIVO
                    case -4://codigo PESO EXCESIVO
                    printf("Peso no valido\n");
                        break;

                    case -5://codigo ESTATURA NEGATIVA
                    case -6://codigo ALTURA EXCESIVO
                        printf("Estatura no valida");
                        break;

                    case -7://codigo CLAVE VACIA
                    case  -8://codigo CLAVE NO VALIDA
                        printf("Clave no valida");
                        break;
                }
                break;
            case 2:
                break;
            case 3:
                imprmirListaDePersonas(lista);
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

int nacimiento(struct Nodo *lista, int year) {
    struct Persona persona;
    int peso;
    int estatura;
    char id[10];
    char nombre[50];
    int resultado;
    struct Nodo *nuevo;

    if (LeerCadena(50, "Ingrese el nombre de la persona: ", nombre) == -1) {
        return -1;//codigo NOMBRE VACIO
    }
    resultado = StringIsAlnum(nombre);
    if (resultado == 4 || resultado == 1) {

        if (LeerEnteroPositivo("Ingrese el peso en kg: ", &peso) == -1) {
            return -3;//codigo PESO NEGATIVO
        }
        if (peso > 100) {
            return -4;//codigo PESO EXCESIVO
        }

        if (LeerEnteroPositivo("Ingrese al estatura en cm: ", &estatura) == -1) {
            return -5;//codigo ESTATURA NEGATIVA
        }
        if (estatura > 200) {
            return -6;//codigo ALTURA EXCESIVO
        }

        if (LeerCadena(50, "La clave de la persona: ", id) == -1) {
            return -7;//codigo CLAVE VACIA
        }
        resultado = StringIsAlnum(id);
        if (resultado != 3) {//ALFANUMERICA
            return -8;//codigo CLAVE NO VALIDA
        }
        strcpy(persona.id, id);
        strcpy(persona.nombre, nombre);
        persona.yearOfBirth = year;
        persona.peso = peso;
        persona.estatura = estatura;
        persona.edad = 0;

        lista = (struct Nodo *) malloc(sizeof(struct Nodo));
        if(lista==NULL){
            lista->siguiente=NULL;
            lista->persona=persona;
            printf("inicio ID:%s Nombre:%s Edad:%d Estatura:%d Peso:%d Nacimiento:%d\n",persona.id,persona.nombre,persona.edad,persona.estatura,persona.peso,persona.yearOfBirth);
            printf("inicio ID:%s Nombre:%s Edad:%d Estatura:%d Peso:%d Nacimiento:%d\n",lista->persona.id,lista->persona.nombre,lista->persona.edad,lista->persona.estatura,lista->persona.peso,lista->persona.yearOfBirth);

        }else{
            printf("New ID:%s Nombre:%s Edad:%d Estatura:%d Peso:%d Nacimiento:%d\n",persona.id,persona.nombre,persona.edad,persona.estatura,persona.peso,persona.yearOfBirth);
            printf("New ID:%s Nombre:%s Edad:%d Estatura:%d Peso:%d Nacimiento:%d\n",lista->persona.id,lista->persona.nombre,lista->persona.edad,lista->persona.estatura,lista->persona.peso,lista->persona.yearOfBirth);

            nuevo->persona=persona;
            nuevo->siguiente=NULL;
            lista->siguiente= nuevo;}
    } else {
        return -2;//codigo NOMBRE NO VALIDO
    }

}

int imprimirPersona(struct Persona persona){
    printf("ID:%s Nombre:%s Edad:%d Estatura:%d Peso:%d Nacimiento:%d\n",persona.id,persona.nombre,persona.edad,persona.estatura,persona.peso,persona.yearOfBirth);
}

int imprmirListaDePersonas(struct Nodo *lista){
    if(lista!=NULL) {
        // while(lista->siguiente!=NULL){
        imprimirPersona(lista->persona);
        //}
    }
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

int LeerFlotantePositivo(char mensaje[], float *numero) {
    float n = *numero;
    printf("%s ", mensaje);
    scanf("%f", numero);
    if (*numero >= 0) {
        return 1;
    } else {
        *numero = n;
        return 0;
    }
}

//1 alfabetico
//2 numerico
//3 alfanumerico
//4 alfabetico con espacios
//0 otro
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