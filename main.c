#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct datos //Todo lo que se guardara en los arreglos
{
    int numeroEmpleado;
    char nombreEmpleado[50];
    char rfc[20];
    int diasTrabajados;
    int localidad;
    int sueldoBase;
    float sueldoNeto;
    float deducciones;
    float percepciones;
    float sueldoFinal;
};

struct datos empleados[10];//Declaracion del arreglo
int totalEmpleados = 0;
int opc;
char archivoNombre[]= "empleados.txt";//Nombre del archivo de texto

void crearArchivo();//declaracion para crear el archivo
void menu();//declaracion para el menú
void agregarEmpleados(); //declaracion para agregar a los empleados
void mostrarEmpleados();//declaracion para mostrar a los empleados
void buscarEmpleado();//declaracion para buscar a cirto empleado
void modificarEmpleados();//declaracion para modificar empleado
void eliminarEmpleados();//declaracion para eliminar empleados
void ordenar();//decalracion para ordenr empleados
void ordenarPorNumeroEmpleado();//declaracion para pordenarlos por numero de empleaado
void ordenarEmpleadoLocalidad();//declaracion para ordenarlos por localidad
void ordenarEmpleadoPorSueldoFinal();//declaracion [ara ordenar por sueldo final
void cargarEmpleadosDesdeArchivo();//declaracion para cargar los empleados desde el archivo
void guardarEmpleadosEnArchivo(); //declaracion para guardar a los empleados
const char* obtenerNombreLocalidad(int codigo);//declaracion para mostrar la localidad en lugar de solo el numero
void mostrarEmpleado(struct datos empleados);//declaracion para mostrar los empleados guardados
void buscarPorNumero();//declaracion para buscar por numero de empleado
void buscarPorLocalidad();//declaracion para buscar por localidad

void crearArchivo()//creacion del archivo .txt
{
    FILE *archivo = fopen(archivoNombre,"a");
    if (!archivo)
    {
        printf("Error. No se creo el archivo");
    }
    fclose(archivo);
}

void menu()//menu principal
{
    cargarEmpleadosDesdeArchivo();
    if (totalEmpleados == 0) {
        printf("Debe agregar al menos un empleado, para las otras funciones\n");
        agregarEmpleados();
    }

    do {
        printf("\n___**MENU PRINCIPAL*___\n");
        printf("1. Agregar Empleado\n");
        printf("2. Modificar Empleado\n");
        printf("3. Buscar Empleado\n");
        printf("4. Ordenar empleados\n");
        printf("5. Mostrar empleados\n");
        printf("6. Eliminar empleados\n");
        printf("7. salir\n");
        scanf("%i", &opc);
        getchar();
        system("pause");
        system("cls");

        switch (opc)
        {
            case 1: agregarEmpleados();
                break;
            case 2: modificarEmpleados();
                break;
            case 3: buscarEmpleado();
                break;
            case 4: ordenar();
                break;
            case 5: mostrarEmpleados();
                break;
            case 6: eliminarEmpleados();
                break;
            case 7: printf("Saliendo del programa. Vuelva Pronto\n");
                break;
            default:printf("Opcion no valida\n");
        }
    }while (opc!=7);
}

void agregarEmpleados()
{
    // agrega hasta 10 empleados
    if (totalEmpleados>=10) {
        printf("No se puede agregrar mas empleados\n");
        return;
    }


    struct datos *empleado=&empleados[totalEmpleados];//es un arreglo que lee el archivo con los empleados que tengamos

    printf("Nombre del Empleado: \n");
    fgets(empleado->nombreEmpleado,50,stdin);
    empleado->nombreEmpleado[strcspn(empleado->nombreEmpleado,"\n")]='\0';
    empleado->numeroEmpleado= totalEmpleados + 1;
    printf("RFC: ");
    fgets(empleado->rfc,20,stdin);
    empleado->rfc[strcspn(empleado->rfc,"\n")]='\0';
    do {
        printf("Dias Trabajados: ");
        scanf("%i",&empleado->diasTrabajados);
        getchar();
    }while (empleado->diasTrabajados<0);
    do {
        printf("Localidad: (1.Yucatan, 2. Chiapas, 3. Veracruz, 4. Puebla, 5. Campeche): ");
        scanf("%i",&empleado->localidad);
        getchar();
    }while (empleado->localidad<1 || empleado->localidad>5);

    empleado->sueldoBase = empleado->diasTrabajados*200;
    switch (empleado->localidad)
    {
        case 1: empleado->sueldoNeto=empleado->sueldoBase + (empleado->sueldoBase*0.4);
            break;
        case 2: empleado->sueldoNeto=empleado->sueldoBase + (empleado->sueldoBase*0.1);
            break;
        case 3: empleado->sueldoNeto=empleado->sueldoBase + (empleado->sueldoBase*0.2);
            break;
        case 4: empleado->sueldoNeto=empleado->sueldoBase + (empleado->sueldoBase*0.3);
            break;
        case 5: empleado->sueldoNeto=empleado->sueldoBase + 400;
            break;
        default: printf("Opcion no valida\n");
            break;
    }

    empleado->deducciones=empleado->sueldoNeto*0.22;//2% de seguro + 10% de ISR + 10% fondo de ahorro
    empleado->percepciones=empleado->sueldoNeto*0.2;//20% bono de asistencia
    empleado->sueldoFinal=empleado->sueldoNeto+empleado->percepciones-empleado->deducciones;

    totalEmpleados++;
    ordenarPorNumeroEmpleado();//para mantener el arreglo ordenado
    guardarEmpleadosEnArchivo();//para guardarlo en el archivo
    printf("\nEmpleado agregado exitosamente\n");
    system("pause");
}

void cargarEmpleadosDesdeArchivo()
{
    FILE *archivo = fopen(archivoNombre,"r");
    totalEmpleados = 0;
    if (archivo) {
        while (fscanf(archivo, "\n%d\n%[^,]\n%[^,]\n%d\n%d\n%d\n%f\n%f\n%f\n%f\n", &empleados[totalEmpleados].numeroEmpleado, empleados[totalEmpleados].nombreEmpleado, empleados[totalEmpleados].rfc,
                      &empleados[totalEmpleados].diasTrabajados, &empleados[totalEmpleados].localidad, &empleados[totalEmpleados].sueldoBase,
                      &empleados[totalEmpleados].sueldoNeto, &empleados[totalEmpleados].deducciones, &empleados[totalEmpleados].percepciones,
                      &empleados[totalEmpleados].sueldoFinal) == 10) {
            totalEmpleados++;
                      }
        fclose(archivo);
    }
}

void guardarEmpleadosEnArchivo()
{
    FILE *archivo = fopen(archivoNombre,"w");
    fprintf(archivo, "\n___*LISTA DE EMPLEADOS*___\n");
    fprintf(archivo, "\n");
    for (int i =0; i<totalEmpleados; i++) {
        //reasigna los numeros consecutivamente
        empleados[i].numeroEmpleado= i+1;
        fprintf(archivo, "- Número de empleado: %i\n", empleados[i].numeroEmpleado);
        fprintf(archivo, "- Nombre del Empleado: %s\n", empleados[i].nombreEmpleado);
        fprintf(archivo, "- RFC: %s\n", empleados[i].rfc);
        fprintf(archivo, "- Dias Trabajados: %i\n", empleados[i].diasTrabajados);
        fprintf(archivo, "- Localidad: %i\n", empleados[i].localidad);
        fprintf(archivo, "- Sueldo base: %i\n", empleados[i].sueldoBase);
        fprintf(archivo, "- Sueldo Neto: %0.2f\n", empleados[i].sueldoNeto);
        fprintf(archivo, "- Deducciones: %0.2f\n", empleados[i].deducciones);
        fprintf(archivo, "- Percepciones: %0.2f\n", empleados[i].percepciones);
        fprintf(archivo, "- Sueldo Final: %0.2f\n", empleados[i].sueldoFinal);
        fprintf(archivo, "\n");
    }
    fclose(archivo);
}

void mostrarEmpleado(struct datos empleado)
{//muestra lo que esta en el archivo
    printf("\n");
    printf("\nEmpleado #%d\n", empleado.numeroEmpleado);
    printf("Nombre: %s\n", empleado.nombreEmpleado);
    printf("RFC: %s\n", empleado.rfc);
    printf("Dias trabajados: %d\n", empleado.diasTrabajados);
    printf("Localidad: %s\n", obtenerNombreLocalidad(empleado.localidad));
    printf("Sueldo base: %d\n", empleado.sueldoBase);
    printf("Sueldo neto: %.2f\n", empleado.sueldoNeto);
    printf("Deducciones: %.2f\n", empleado.deducciones);
    printf("Percepciones: %.2f\n", empleado.percepciones);
    printf("Sueldo final: %.2f\n", empleado.sueldoFinal);
    printf("\n");
}

const char* obtenerNombreLocalidad(int codigo)
{//muestra el nombre de la localidad
    switch (codigo) {
        case 1: return "Yucatan";
        case 2: return "Chiapas";
        case 3: return "Veracruz";
        case 4: return "Puebla";
        case 5: return "Campeche";
        default: return "Localidad no encontrada";
    }
}

void mostrarEmpleados()
{
    printf("\n___*LISTA DE EMPLEADOS*___\n");
    for (int i=0; i<totalEmpleados; i++) {
        mostrarEmpleado(empleados[i]);
    }
    system("pause");
}

void buscarEmpleado()
{
    int opcion;
    printf("Buscar por: \n1.Numero de Empleado\n2.Localidad:\n");//submenu de buscar
    scanf("%i", &opcion);
    getchar();

    switch (opcion) {
        case 1: buscarPorNumero();//funcion que busca por numero
            break;
        case 2:buscarPorLocalidad();//funcion que busca por localidad
            break;
        default: printf("Opcion no valida\n");
    }
}

 void buscarPorNumero()
{
    int num;
    printf("Numero de Empleado: ");
    scanf("%i", &num);
    for (int i=0; i<totalEmpleados; i++) {
        if (empleados[i].numeroEmpleado==num) {
            mostrarEmpleado(empleados[i]);
            system("pause");
            return;
        }
    }
    printf("Empleado No Emcontrado\n");
    system("pause");
}

void buscarPorLocalidad()
{
    int loc;
    printf("Localidad (1.Yucatan, 2. Chiapas, 3. Veracruz, 4. Puebla, 5. Campeche): ");
    scanf("%i", &loc);
    int encontrado = 0;
    for (int i=0; i<totalEmpleados; i++) {
        if (empleados[i].localidad==loc) {
            mostrarEmpleado(empleados[i]);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("No hay empleados en esa Localidad\n");
    }
    system("pause");
}

void modificarEmpleados()
{
    int numero;
    printf("Ingrese el numero de empleado que desea modificar: ");
    scanf("%i", &numero);
    getchar();

    for (int i = 0; i < totalEmpleados; i++){
        if (empleados[i].numeroEmpleado == numero) {
            int campo;
            printf("¿Que desea modificar?\n 1.Nombre\n 2. Dias trabajados\n 3. Localidad\n: ");
            scanf("%i", &campo);
            getchar();

            switch (campo) {
                case 1:
                    printf("Nuevo nombre: ");
                    fgets(empleados[i].nombreEmpleado, 50, stdin);
                    empleados[i].nombreEmpleado[strcspn(empleados[i].nombreEmpleado, "\n")] = '\0';
                    break;
                case 2:
                    printf("Nuevos dias trabajados: ");
                    scanf("%i", &empleados[i].diasTrabajados);
                    getchar();
                    break;
                case 3:
                    do {
                        printf("Nueva localidad: ");
                        scanf("%i", &empleados[i].localidad);
                        getchar();
                    } while (empleados[i].localidad<1 || empleados[i].localidad>5);
                    break;
                default:
                    printf("Opcion no valida\n");
                    return;
            }

            empleados[i].sueldoBase=empleados[i].diasTrabajados*200;

            switch (empleados[i].localidad) {
                case 1: empleados[i].sueldoNeto = empleados[i].sueldoBase + (empleados[i].sueldoBase*0.4);
                    break;
                case 2: empleados[i].sueldoNeto = empleados[i].sueldoBase + (empleados[i].sueldoBase*0.1);
                    break;
                case 3: empleados[i].sueldoNeto = empleados[i].sueldoBase + (empleados[i].sueldoBase*0.2);
                    break;
                case 4: empleados[i].sueldoNeto = empleados[i].sueldoBase + (empleados[i].sueldoBase*0.3);
                    break;
                case 5: empleados[i].sueldoNeto = empleados[i].sueldoBase + 400;
                    break;
            }
            //vuelve a realizar las cuentas
            empleados[i].deducciones=empleados[i].sueldoNeto*0.22;//2% de seguro + 10% de ISR + 10% fondo de ahorro
            empleados[i].percepciones=empleados[i].sueldoNeto*0.2;//20% bono de asistencia
            empleados[i].sueldoFinal=empleados[i].sueldoNeto+empleados[i].percepciones-empleados[i].deducciones;

            guardarEmpleadosEnArchivo();
            printf("Empleado Modificado Exitosamente\n");
            system("pause");
            return;
        }
    }
    printf("Empleado no encontrado\n");
    system("pause");
}

void eliminarEmpleados()
{
    int numero;
    printf("Ingrese el numero de empleado a eliminar: ");
    scanf("%i", &numero);
    getchar();

    int index=-1;
    for (int i = 0; i < totalEmpleados; i++) {
        if (empleados[i].numeroEmpleado == numero) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("No se encontro el numero de empleado\n");
        return;
    }
    for (int i = index; i < totalEmpleados; i++) {
        empleados[i]=empleados[i+1];
    }
    totalEmpleados--;
    ordenarPorNumeroEmpleado();
    guardarEmpleadosEnArchivo();
    printf("Empleado eliminado exitosamente\n");
}

void ordenar()
{
    int subopcion;
    printf("___*SUBMENU DE ORDENAR*___\n");
    printf("1. Ordenar por localidad\n");
    printf("2. Ordenar por sueldo final\n");
    printf("Selecciona una opcion: \n");
    scanf("%i", &subopcion);
    getchar();

    switch (subopcion) {
        case 1: ordenarEmpleadoLocalidad();
            break;
        case 2: ordenarEmpleadoPorSueldoFinal();
            break;
        default: printf("Opcion no valida\n");
            break;
    }
}

void ordenarEmpleadoLocalidad()
{
    struct datos temp;
    for (int i=0;i<totalEmpleados;i++) {//metodo burbuja
        for (int j=0;j<totalEmpleados-i-1;j++) {
            if (empleados[j].localidad > empleados[j+1].localidad) {
                temp = empleados[j];
                empleados[j] = empleados[j+1];
                empleados[j+1] = temp;
            }
        }
    }
    mostrarEmpleados();
}

void ordenarEmpleadoPorSueldoFinal()
{
    struct datos temp;
    for (int i = 0; i < totalEmpleados - 1; i++) {//metodo burbuja
        for (int j = 0; j < totalEmpleados - i - 1; j++) {
            if (empleados[j].sueldoFinal < empleados[j + 1].sueldoFinal) {
                temp = empleados[j];
                empleados[j] = empleados[j + 1];
                empleados[j + 1] = temp;
            }
        }
    }
    mostrarEmpleados();
}

void ordenarPorNumeroEmpleado()
{
   struct datos temp;//auxiliar
    for (int i=0;i<totalEmpleados;i++) {//metodo burbuja
        for (int j=0;j<totalEmpleados-i-1;j++) {
            if (empleados[j].numeroEmpleado>empleados[j+1].numeroEmpleado) {
                temp = empleados[j];
                empleados[j] = empleados[j+1];
                empleados[j+1] = temp;
            }
        }
    }
    //Reasinamos los valores de los empleados de manera consecutiva
    for (int i = 0; i < totalEmpleados; i++) {
        empleados[i].numeroEmpleado=i+1;
    }
}

int main()
{
    printf("Bienvenido al sistema de trabajadores de la empresa\n");
    printf("ENIGMACODE\n");//nombre de nuestra empresa
    crearArchivo();
    menu();
    return 0;
}