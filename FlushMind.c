#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Admin{
    char nombre[50];
    char cedula[9];
    char direccion[50];
    char telefono[11];
    char correo[30];
    char login[100];
}Administrador;

void registroAdministrador(int, Administrador *);
void loginAdministrador();
void loginMedico();
void loginPaciente();

int main(){
    Administrador admin;
    FILE *registroAdmin;
    int opcion, i, ciclo;
    char opc[3];
    ciclo = 1;
    while (ciclo == 1){
        registroAdmin = fopen("registroAdmin.bin", "rb");
        if(registroAdmin != NULL){
            printf("\n                         Inicio de sesion\n");
            do{
                printf("\n(Ingrese el numero de usuario que le corresponde)");
                printf("\n1) Administrador");
                printf("\n2) Medico");
                printf("\n3) Paciente");
                printf("\n4) Salir\n");
                scanf("%[^\n]%*c", &opc);
                opcion = atoi(opc);
                if((opcion > 0 && opcion < 5)){
                    for (i = 0; i < strlen(opc); i++){
                        if(!isdigit(opc[i])){
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente");
                            opcion = 0;
                            break;
                        }
                    }
                    switch (opcion){
                        case 1:
                            loginAdministrador();
                            break;
                        case 2:
                            loginMedico();
                            break;
                        case 3:
                            loginPaciente();
                            break;
                        case 4:
                            printf("Cerrando programa.");
                            opcion = 4;
                            break;
                    }
                }else{
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente");
                    fflush(stdin);
                    opcion = 0;
                }
            }while (opcion != 4 || opcion == 0);
            break;
        }else{
            fclose(registroAdmin);
            registroAdministrador(1, &admin);
        }
    }
}

void registroAdministrador(int CRUD, Administrador *admin){
    FILE *registroAdmin = fopen("registroAdmin.bin", "wb");
    if(CRUD == 1){
        int opcion, longitud, i;
        char opc[3];
        printf("\n                         Registro del administrador\n");
        printf("\nIngrese los datos del administrador:\n");
        do{
            printf("Nombre completo: ");
            scanf("%[^\n]%*c", admin->nombre);  
            do{
                printf("¿Continuar con el siguiente nombre [%s]?", admin->nombre);
                printf("\n1)Si          2)No          ");
                scanf("%[^\n]%*c", opc);
                opcion = atoi(opc);
                if (opcion != 1 && opcion != 2){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    fflush(stdin);
                }else{
                    for(i = 0; i < strlen(opc); i++){
                        if(!isdigit(opc[i])){
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            opcion = 0;
                            break;
                        }
                    }
                }
            } while (opcion != 1 && opcion != 2);
        } while ((opcion == 2));
        do{
            do{
                printf("Cedula profecional(8 caracteres): ");
                scanf("%[^\n]%*c", admin->cedula);
                longitud = strlen(admin->cedula);
                if (longitud != 8){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                }
            } while (longitud != 8);
            do
            {
                printf("¿Continuar con la siguiente cedula [%s]?", admin->cedula);
                printf("\n1)Si          2)No          ");
                scanf("%[^\n]%*c", opc);
                opcion = atoi(opc);
                if (opcion != 1 && opcion != 2){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    fflush(stdin);
                }else{
                    for(i = 0; i < strlen(opc); i++){
                        if(!isdigit(opc[i])){
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            opcion = 0;
                            break;
                        }
                    }
                }
            } while (opcion != 1 && opcion != 2);
        } while ((opcion == 2));
        strcpy(admin->login, admin->cedula);
        printf("Direccion: ");
        scanf("%[^\n]%*c", admin->direccion);
        do{
            printf("Telefono(10 digitos): ");
            scanf("%[^\n]%*c", admin->telefono);
            if(strlen(admin->telefono) == 10){
                for (i = 0; i < strlen(admin->telefono); i++){
                    if(!isdigit(admin->telefono[i])){
                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                        opcion = 0;
                        break;
                    }
                    opcion = 1;
                }
            }else{
                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                opcion = 0;
            }
        }while(opcion != 1);
        printf("Correo electronico: ");
        scanf("%[^\n]%*c", admin->correo);
        fwrite(admin, sizeof(Administrador), 1, registroAdmin);
        fclose(registroAdmin);
        return;
    }
    if(CRUD == 0){

    }
}

void loginAdministrador(){
    printf("Login Administrador");
}

void loginMedico(){
    printf("Login Medico");
}

void loginPaciente(){
    printf("Login Paciente");
}