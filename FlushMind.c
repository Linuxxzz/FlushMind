#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Admin{
    char nombre[50];
    char cedula[10];
    char direccion[50];
    char telefono[11];
    char correo[30];
    char login[100];
}Administrador;

typedef struct Med{
    int estado;
    char nombre[50];
    char cedula[9];
    char direccion[50];
    char telefono[11];
    char correo[30];
    char login[100];
}Medico;

typedef struct Pac{
    int estado;
    char medico[50];
    char nombre[50];
    char nss[12];
    char telefono[11];
    char correo[30];
}Paciente;



void registroAdministrador(int, Administrador *);
void loginAdministrador();
void menuAdministrador(Administrador *); 
void gestionarMedico();
void registrarMedico();
void actualizarInformacionMedico();
void cambiarEstatusMedico();
void eliminarMedico();
void generarInformesAdministrador();
void loginMedico();
void loginPaciente();

int main(){
    Administrador admin;
    FILE *registroAdmin;
    int opcion, i, ciclo;
    char opc[100];
    ciclo = 1;
    while (ciclo == 1){
        registroAdmin = fopen("registroAdmin.bin", "rb");
        if(registroAdmin != NULL){
            do{
                opc[0] = '0';
                printf("\n                         Inicio de sesion\n");
                printf("\n(Ingrese el numero de usuario que le corresponde)");
                printf("\n1) Administrador");
                printf("\n2) Medico");
                printf("\n3) Paciente");
                printf("\n4) Salir\n");
                scanf("%[^\n]%*c", opc);
                opcion = atoi(opc);
                if((opcion > 0 && opcion < 5)){
                    for (i = 0; i < (int)strlen(opc); i++){
                        if(!isdigit(opc[i])){
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
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
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
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
    FILE *registroAdmin;
    if(CRUD == 1){
        registroAdmin = fopen("registroAdmin.bin", "wb");
        int opcion, longitud, i;
        char opc[100];
        char negativo[] = ("NO");
        printf("\n                         Registro del administrador\n");
        printf("\nIngrese los datos del administrador:\n");
        do{
            printf("Nombre completo: ");
            scanf("%[^\n]%*c", admin->nombre);  
            do{
                opc[0] = '0';
                printf("¿Continuar con el siguiente nombre [%s]?", admin->nombre);
                printf("\n1)Si          2)No          ");
                fflush(stdin);
                scanf("%[^\n]%*c", opc);
                opcion = atoi(opc);
                fflush(stdin);
                if (opcion != 1 && opcion != 2){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    fflush(stdin);
                }else{
                    for(i = 0; i < (int)strlen(opc); i++){
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
                strcpy(admin->cedula, negativo);
                printf("Cedula profecional(8 caracteres): ");
                scanf("%[^\n]%*c", admin->cedula);
                fflush(stdin);
                longitud = strlen(admin->cedula);
                if (longitud != 8){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                }
            } while (longitud != 8);
            do{
                opc[0] = '0';
                printf("¿Continuar con la siguiente cedula [%s]?", admin->cedula);
                printf("\n1)Si          2)No          ");
                scanf("%[^\n]%*c", opc);
                opcion = atoi(opc);
                fflush(stdin);
                if (opcion != 1 && opcion != 2){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    fflush(stdin);
                }else{
                    for(i = 0; i <(int)strlen(opc); i++){
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
        fflush(stdin);
        scanf("%[^\n]%*c", admin->direccion);
        do{
            printf("Telefono(10 digitos): ");
            fflush(stdin);
            scanf("%[^\n]%*c", admin->telefono);
            if(strlen(admin->telefono) == 10){
                for (i = 0; i < (int)strlen(admin->telefono); i++){
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
        fflush(stdin);
        scanf("%[^\n]%*c", admin->correo);
        fwrite(admin, sizeof(Administrador), 1, registroAdmin);
        fclose(registroAdmin);
        return;
    }
    if(CRUD == 0){
        int opcion, longitud, i;
        char opc[3];
        char contra[100];
        printf("\n              Modificar informacion personal\n");
        printf("\nNombre: %s", admin->nombre);
        printf("\nCedula: %s", admin->cedula);
        printf("\nDireccion: %s", admin->direccion);
        printf("\nTelefono: %s", admin->telefono);
        printf("\nCorreo electronico: %s", admin->correo);
        printf("\nContraseña: %s", admin->login);
        do{
            printf("\nSi desea cambiar su informacion personal presione 1, de lo contrario presione 2: ");
            scanf("%[^\n]%*c", opc);
            opcion = atoi(opc);
            if (opcion != 1 && opcion != 2){
                printf("El dato ingresado no es valido, por favor intentalo nuevamente");
                fflush(stdin);
            }else{
                for(i = 0; i < (int)strlen(opc); i++){
                    if(!isdigit(opc[i])){
                        printf("El dato ingresado no es valido, por favor intentalo nuevamente");
                        opcion = 0;
                        break;
                    }
                }
            }
        } while (opcion != 1 && opcion != 2);
        printf("Si deseas omitir algun dato menos la contraseña solo preciona Enter\n");  
        if (opcion == 1){
            printf("\nIngrese el nuevo nombre completo: ");
            scanf("%[^\n]%*c", admin->nombre);
            fflush(stdin);
            do{
                do{
                    printf("Ingrese la nueva contraseña (Ingrese minimo 5 caracteres): ");
                    scanf("%[^\n]%*c", admin->login);
                    fflush(stdin);
                    longitud = strlen(admin->login);
                    if (longitud < 5){
                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    }
                } while (longitud < 5);
                printf("Vuelva a ingresar la nueva contraseña: ");
                scanf("%[^\n]%*c", contra);
                fflush(stdin);
                if (strcmp(admin->login, contra) != 0){
                    printf("Las contraseñas no coinciden, intentalo nuevamente\n");
                }
            } while (strcmp(admin->login, contra) != 0);
            do{
                printf("Cedula profesional (8 caracteres): ");
                scanf("%[^\n]%*c", admin->cedula);
                fflush(stdin);
                longitud = strlen(admin->cedula);
                if (longitud != 8){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                }
            } while (longitud != 8);
            printf("Direccion: ");
            scanf("%[^\n]%*c", admin->direccion);
            fflush(stdin);
            do{
                printf("Telefono(10 digitos): ");
                scanf("%[^\n]%*c", admin->telefono);
                fflush(stdin);
                if(strlen(admin->telefono) == 10){
                    for (i = 0; i < (int)strlen(admin->telefono); i++){
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
            fflush(stdin);
            printf("Informacion actualizada con exito\n");
            registroAdmin = fopen("registroAdmin.bin", "wb");
            fwrite(admin, sizeof(Administrador), 1, registroAdmin);
            fclose(registroAdmin);
        }
    }
}

//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
void loginAdministrador(){
    printf("\nLogin Administrador\n");

    /*1) El archivo en donde estan guardados los datos del administrador se llama registroAdmin.bin*/

    /*2) Necesito que guardes la informacion del medico en el struck que esta, crea la 
      variable con el nombre que quieras, asi que me pasas el struct a la funcion. */
    Administrador admin;
    FILE *registroAdmin = fopen("registroAdmin.bin", "rb");
    rewind(registroAdmin);
    fread(&admin, sizeof(Administrador), 1, registroAdmin);
    fclose(registroAdmin);
    menuAdministrador(&admin);
}
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder

void menuAdministrador(Administrador *ptradmin){
    int opcion, i;
    char opc[100];
    do{
        opc[0] = '0';
        printf("\n          Bienvenido %s!\n", ptradmin->nombre);
        printf("\n¿Que accion desea realizar? (Seleccione el número de la accion)");
        printf("\n1) Modificar informacion personal");
        printf("\n2) Gestionar Medico");
        printf("\n3) Generar informes");
        printf("\n4) Salir\n");
        scanf("%[^\n]%*c", opc);
        opcion = atoi(opc);
        if((opcion > 0 && opcion < 5)){
            for (i = 0; i < (int)strlen(opc); i++){
                if(!isdigit(opc[i])){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    opcion = 0;
                    break;
                }
            }
            switch (opcion){
                case 1:
                    registroAdministrador(0, ptradmin);
                    break;
                case 2:
                    gestionarMedico();
                    break;
                case 3:
                    generarInformesAdministrador();
                    break;
                case 4:
                    printf("Cerrando sesion.\n");
                    break;
            }
        }else{
            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            fflush(stdin);
            opcion = 0;
        }
    }while (opcion != 4 || opcion == 0);
}

void gestionarMedico(){
    int opcion, i;
    char opc[100];
    do{
        opc[0] = '0';
        printf("\n          Gestionar Medicos\n");
        printf("\n¿Que accion desea realizar? (Seleccione el número de la accion)");
        printf("\n1) Registrar a un nuevo medico");
        printf("\n2) Actualizar informacion de un medico");
        printf("\n3) Habilitar o deshabilitar a un medico");
        printf("\n4) Elminar a un medico");
        printf("\n5) Salir\n");
        fflush(stdin);
        scanf("%[^\n]%*c", opc);
        opcion = atoi(opc);
        if(opcion > 0 && opcion < 6){
            for (i = 0; i < (int)strlen(opc); i++){
                if(!isdigit(opc[i])){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    opcion = 0;
                    break;
                }
            }
            switch (opcion){
                case 1:
                    registrarMedico();
                    break;
                case 2:
                    actualizarInformacionMedico();
                    break;
                case 3:
                    cambiarEstatusMedico();
                    break;
                case 4:
                    eliminarMedico();
                    break;
            }
        }else{
            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            fflush(stdin);
            opcion = 0;
        }
    }while (opcion != 5 || opcion == 0);
}

void registrarMedico(){
    printf("\n              Registrar a un nuevo medico\n");
    Medico med;
    FILE *registrarMedico;
    int opcion, i, longitud;
    char opc[100];
    char negativo[] = ("NO");
    registrarMedico = fopen("registroMedico.bin", "rb");
    if (registrarMedico == NULL){
        fclose(registrarMedico);
        registrarMedico = fopen("registroMedico.bin", "wb");
        fclose(registrarMedico);
    }
    fclose(registrarMedico);
    printf("\nIngrese los datos del medico:\n");
    med.estado = 1;
    do{
        printf("Nombre completo: ");
        scanf("%[^\n]%*c", med.nombre);  
        do{
            opc[0] = '0';
            printf("¿Continuar con el siguiente nombre [%s]?", med.nombre);
            printf("\n1)Si          2)No          ");
            fflush(stdin);
            scanf("%[^\n]%*c", opc);
            opcion = atoi(opc);
            fflush(stdin);
            if (opcion != 1 && opcion != 2){
                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                fflush(stdin);
            }else{
                for(i = 0; i < (int)strlen(opc); i++){
                    if(!isdigit(opc[i])){
                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                        opcion = 0;
                        break;
                    }
                }
            }
        } while (opcion != 1 && opcion != 2);
    } while (opcion == 2);
    do{
        do{
            strcpy(med.cedula, negativo);
            printf("Cedula profecional(8 caracteres): ");
            scanf("%[^\n]%*c", med.cedula);
            fflush(stdin);
            longitud = strlen(med.cedula);
            if (longitud != 8){
                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            }
        } while (longitud != 8);
        do{
            opc[0] = '0';
            printf("¿Continuar con la siguiente cedula [%s]?", med.cedula);
            printf("\n1)Si          2)No          ");
            scanf("%[^\n]%*c", opc);
            opcion = atoi(opc);
            fflush(stdin);
            if (opcion != 1 && opcion != 2){
                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                fflush(stdin);
            }else{
                for(i = 0; i <(int)strlen(opc); i++){
                    if(!isdigit(opc[i])){
                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                        opcion = 0;
                        break;
                    }
                }
            }
        } while (opcion != 1 && opcion != 2);
    } while ((opcion == 2));
    strcpy(med.login, med.cedula);
    printf("Direccion: ");
    fflush(stdin);
    scanf("%[^\n]%*c", med.direccion);
    do{
        printf("Telefono(10 digitos): ");
        fflush(stdin);
        scanf("%[^\n]%*c", med.telefono);
        if(strlen(med.telefono) == 10){
            for (i = 0; i < (int)strlen(med.telefono); i++){
                if(!isdigit(med.telefono[i])){
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
    fflush(stdin);
    scanf("%[^\n]%*c", med.correo);
    registrarMedico = fopen("registroMedico.bin", "ab");
    fseek(registrarMedico, sizeof(Medico), SEEK_END);
    fwrite(&med, sizeof(Medico), 1, registrarMedico);
    fclose(registrarMedico);
}

//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
void actualizarInformacionMedico(){
   
}
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan
//Alan

void cambiarEstatusMedico(){
    Medico med;
    FILE *ptrmedicos = fopen("registroMedico.bin", "rb");
    int opcion, i;
    char respuesta[100];
    char opc[100];
    char negativo[] = ("Salir");
    if (ptrmedicos == NULL){
        printf("\nNo hay medicos registrados por el momento, regrese cuando alla registrado a algun medico\n");
        fclose(ptrmedicos);
    }else{
        fclose(ptrmedicos);
        printf("\n                     Habilitar o deshabilitar\n");
        printf("\n¿Que medico desea habilitar o deshabilitar?");
        printf("\n(Escriba el nombre del medico)");
        do{
            opc[0] = '0';
            ptrmedicos = fopen("registroMedico.bin", "rb");
            printf("\nLista de medicos:");
            fread(&med, sizeof(Medico), 1, ptrmedicos);
            do{
                printf("\n%s ", med.nombre);
                if (med.estado == 1){
                    printf("(Habilitado)");
                }
                if (med.estado == 0){
                    printf("(Deshabilitado)");
                }
                fread(&med, sizeof(Medico), 1, ptrmedicos);
            } while (feof(ptrmedicos) == 0);
            fclose(ptrmedicos);
            printf("\n(Si desea detener esta accion escriba 'Salir')\n");
            fflush(stdin);
            scanf("%[^\n]%*c", opc);
            if (strcmp(opc, negativo) != 0){
                ptrmedicos = fopen("registroMedico.bin", "r+b");
                fread(&med, sizeof(Medico), 1, ptrmedicos);
                do{
                    if (strcmp(opc, med.nombre) == 0){
                        if (med.estado == 1){
                            do{
                                respuesta[0] = '0';
                                printf("¿Estas seguro de inhabilitar a este medico?");
                                printf("\n[%s]     1)Si    2)No     ", med.nombre);
                                fflush(stdin);
                                scanf("%[^\n]%*c", respuesta);
                                opcion = atoi(respuesta);
                                fflush(stdin);
                                if (opcion != 1 && opcion != 2){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    fflush(stdin);
                                }else{
                                    for (i = 0; i < (int)strlen(respuesta); i++){
                                        if (!isdigit(respuesta[i])){
                                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                            opcion = 0;
                                            break;
                                        }
                                    }
                                }
                            } while (opcion != 1 && opcion != 2);
                            if (opcion == 1){
                                med.estado = 0;
                                fseek(ptrmedicos,-(long)sizeof(Medico),SEEK_CUR);
                                fwrite(&med, sizeof(Medico), 1, ptrmedicos);
                                printf("Deshabilitado!\n");
                            }
                        }else{
                            if (med.estado == 0){
                                do{
                                    respuesta[0] = '0';
                                    printf("¿Estas seguro de habilitar a este medico?");
                                    printf("\n[%s]     1)Si    2)No     ", med.nombre);
                                    fflush(stdin);
                                    scanf("%[^\n]%*c", respuesta);
                                    opcion = atoi(respuesta);
                                    fflush(stdin);
                                    if (opcion != 1 && opcion != 2){
                                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                        fflush(stdin);
                                    }else{
                                        for (i = 0; i < (int)strlen(respuesta); i++){
                                            if (!isdigit(respuesta[i])){
                                                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                                opcion = 0;
                                                break;
                                            }
                                        }
                                    }
                                } while (opcion != 1 && opcion != 2);
                                if (opcion == 1){
                                    med.estado = 1;
                                    fseek(ptrmedicos,-(long)sizeof(Medico),SEEK_CUR);
                                    fwrite(&med, sizeof(Medico), 1, ptrmedicos);
                                    printf("Habilitado!\n");
                                }
                            }
                        }
                        break;
                    }else{
                        fread(&med, sizeof(Medico), 1, ptrmedicos);
                        opcion = 0;
                    }
                } while (feof(ptrmedicos) == 0);
                if (opcion == 0){
                    printf("Medico no encontrado, intentelo nuevamente");
                }
            }else{
                opcion = 1;
            }
            fclose(ptrmedicos);
        } while (opcion == 0 || opcion == 2);
        printf("Saliendo al menu Gestionar medicos\n");
    }
}

void eliminarMedico(){
    Medico medicos, copiaMedicos;
    FILE *ptrmedicos = fopen("registroMedico.bin", "rb");
    int opcion, i, check, contador;
    char respuesta[100];
    char opc[100];
    char negativo[] = ("Salir");
    if (ptrmedicos == NULL){
        printf("\nNo hay medicos registrados por el momento, regrese cuando alla registrado a algun medico\n");
        fclose(ptrmedicos);
    }else{
        fclose(ptrmedicos);
        printf("\n                     Eliminar medico\n");
        printf("\nPara eliminar un medico primero debe deshabilitarlo y tampoco debe tener pacientes registrados a su nombre");
        printf("\n¿Que medico desea eliminar?");
        printf("\n(Escriba el nombre del medico)");
        do{
            opc[0] = '0';
            ptrmedicos = fopen("registroMedico.bin", "rb");
            printf("\nLista de medicos deshabilitados:");
            fread(&medicos, sizeof(Medico), 1, ptrmedicos);
            do{
                if (medicos.estado == 0){
                    printf("\n%s ", medicos.nombre);
                }
                fread(&medicos, sizeof(Medico), 1, ptrmedicos);
            } while (feof(ptrmedicos) == 0);
            fclose(ptrmedicos);
            printf("\n(Si desea detener esta accion escriba 'Salir')\n");
            fflush(stdin);
            scanf("%[^\n]%*c", opc);
            if (strcmp(opc, negativo) != 0){
                ptrmedicos = fopen("registroMedico.bin", "r+b");
                fread(&copiaMedicos, sizeof(Medico), 1, ptrmedicos);
                contador = 1;
                do{
                    if (strcmp(opc, copiaMedicos.nombre) == 0){
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        check = 1;
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        if (check == 1){
                            do{
                                respuesta[0] = '0';
                                printf("¿Estas seguro de eliminar a este medico?");
                                printf("\n[%s]     1)Si    2)No     ", copiaMedicos.nombre);
                                fflush(stdin);
                                scanf("%[^\n]%*c", respuesta);
                                opcion = atoi(respuesta);
                                fflush(stdin);
                                if (opcion != 1 && opcion != 2){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    fflush(stdin);
                                }else{
                                    for (i = 0; i < (int)strlen(respuesta); i++){
                                        if (!isdigit(respuesta[i])){
                                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                            opcion = 0;
                                            break;
                                        }
                                    }
                                }
                            } while (opcion != 1 && opcion != 2);
                            if (opcion == 1){
                                FILE *copiaptrMedicos = fopen("registroMedicoCopia.bin", "wb");;
                                fseek(ptrmedicos, contador * -(long)sizeof(Medico), SEEK_CUR);
                                fread(&medicos, sizeof(Medico), 1, ptrmedicos);
                                do{
                                    if(strcmp(copiaMedicos.nombre, medicos.nombre) != 0){
                                        fwrite(&medicos, sizeof(Medico), 1, copiaptrMedicos);
                                    }
                                    fread(&medicos, sizeof(Medico), 1, ptrmedicos);
                                } while (feof(ptrmedicos) == 0);
                                fclose(ptrmedicos);
                                fclose(copiaptrMedicos);
                                remove("registroMedico.bin");
                                rename("registroMedicoCopia.bin", "registroMedico.bin");
                            }
                        }else{
                            printf("El medico ingresado tiene pacientes registrados, por lo tanto no fue posible eliminarlo");
                        }
                        break;
                    }else{
                        fread(&copiaMedicos, sizeof(Medico), 1, ptrmedicos);
                        opcion = 0;
                        contador++;
                    }
                } while (feof(ptrmedicos) == 0);
                if (opcion == 0){
                    printf("Medico no encontrado, intentelo nuevamente");
                }
            }else{
                opcion = 1;
            }
            fclose(ptrmedicos);
        } while (opcion == 0 || opcion == 2);
        printf("Saliendo al menu Gestionar medicos\n");
    }
}

void generarInformesAdministrador(){
    /*Cuando puedas me dices que necesitas para generar los informes*/
    printf("\nSeleccionado Generar Informes\n");
}

//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
void loginMedico(){
    printf("Login Medico");
}

void loginPaciente(){
    printf("Login Paciente");
}
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder