#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef DOLOG
#define LOG(...) fprintf(log, __VA_ARGS__);
#else
#define LOG(...)
#endif

struct array
{
    int *pdata;
    int size;
};

void initArray(struct array *);
void getArray(struct array *);
void arrayCommon(struct array *, struct array *, struct array *);
void printArray(struct array *);
void freeMemory(struct array *, struct array *, struct array *);

void initArray(struct array *arr){
    arr->pdata = NULL;
    arr->size = -1;
}

void printArray(struct array *parr)
{
    for (int i = 0; i < parr->size; i++)
    {
        printf("%d ", parr->pdata[i]);
    }
    printf("\n");
}

void getArray(struct array *parr) //Lo primero que debemos hacer es dar las longitudes de los arreglos, primero del arreglo 1, luego sus datos, luego 
                                //repetimos con el arreglo 2
{
    
char valor1[16];
    char valor2[16];

    if(fgets(valor1, 5, stdin) != NULL)
    {
        valor1[strlen(valor1) -1 ] = 0;

        int cambio = sscanf(valor1,"%d",&parr->size);


        parr->pdata = malloc(sizeof(int)*parr->size);


        for(int i = 0;i<parr->size;i++){
            if(fgets(valor2, 5, stdin) != NULL)
            {
                int cambio2 = sscanf(valor2,"%d",parr->pdata + i);
            }
        }
    }

}

void arrayCommon(struct array *arrIn1, struct array *arrIn2, struct array *arrOut)
{
 int size;
    arrOut->size = 0;                       //aquì viene crear el arreglo de salida, que no sabemos que tamaño tiene,
                                            //lo que sì sabemos es que su largo no puede ser mayor al arreglo de entrada màs corto.
                                            //os comparamos y colocamos en la variable size el valor del tamaño del arreglo màs corto
    if(arrIn1->size>arrIn2->size)
    {
        size = arrIn2->size;
    }
    else if(arrIn2->size>=arrIn1->size)
    {
        size = arrIn1->size;
    }

    

    int iguales[size];                      //ya que si un valor no es inicializado en este lenguaje, toma valores aleatorios, inicializamos todos
                                            //los valores del vector que usaremos para guardar los nùmeros iguales en -1
                                            //ya que los inputs seràn solo valores enteros positivos
    for (int i = 0; i < size; i++){
        iguales[i]=-1;
    }

    

    int contador=0;

    for(int i=0; i<arrIn1->size;i++){
        for(int j=0; j<arrIn2->size;j++){               //aquì llega la comparaciòn, recorremos los arreglos con un ciclo for doble, y comparamos los valores
                                                        //si la comparaciòn de valores da igual, el valor de cualquiera de los 2 arreglos se guarda en el 
                                                        //arreglo
            if(arrIn1->pdata[i]==arrIn2->pdata[j]) 
            {
                int boolean = 0;
                for (int k = 0; k < size; k++){
                    if(arrIn1->pdata[i] == iguales[k])
                    {
                        k = size;
                        boolean = 1;
                    }
                }
                if (boolean == 0)
                {
                    iguales[contador] = arrIn2->pdata[j];
                    contador++;                             //aquì el arreglo de salida va aumentando su tamaño cada vez que hay un valor igual
                    arrOut->size ++;
                }
            }
        }
    }  
    
    arrOut->pdata = malloc(sizeof(int)*arrOut->size); 

    for (int i = 0; i < arrOut->size; i++)
    {
        *(arrOut->pdata+i) = iguales[i];                //le damos los valores del vector que guardaba los iguales al vector de salida
                                                        //no corremos el riesgo de pasarnos ya que el contador llegarà hasta el valor del tamaño del arreglo de salida
                                                        //que fue subiendo segùn tenìamos valores iguales en el ciclo de màs arriba
    }
}

void freeMemory(struct array *arr1, struct array *arr2, struct array *arr3)
{
    free(arr1->pdata);
    free(arr1);

    free(arr2->pdata);
    free(arr2);

    free(arr3->pdata);
    free(arr3);
}

int main(void)
{

#ifdef DOLOG
    FILE *log = fopen("log", "w");
    if (log == NULL)
    {
        perror("log file creation fails: ");
        return EXIT_FAILURE;
    }
#endif

    char commandBuf[64];

    LOG("creating an object for each array\n");

    struct array *arr1 = malloc(sizeof(struct array) * 1);
    initArray(arr1);
    struct array *arr2 = malloc(sizeof(struct array) * 1);
    initArray(arr2);    
    struct array *arr3 = malloc(sizeof(struct array) * 1);
    initArray(arr3);


    LOG("Init command loop\n");

    while (fgets(commandBuf, sizeof(commandBuf), stdin) != NULL)
    {
        commandBuf[strlen(commandBuf) - 1] = 0;

        if (strncmp(commandBuf, "arr1", strlen("arr1")) == 0)
        {
            LOG("getting array1\n");
            getArray(arr1);
        }
        else if (strncmp(commandBuf, "arr2", strlen("arr2")) == 0)
        {
            LOG("getting array2\n");
            getArray(arr2);
        }
        else if (strncmp(commandBuf, "printArr1", strlen("printArr1")) == 0)
        {
            LOG("printing arr1\n");
            printArray(arr1);
        }
        else if (strncmp(commandBuf, "printArr2", strlen("printArr2")) == 0)
        {
            LOG("printing arr2\n");
            printArray(arr2);
        }
        else if (strncmp(commandBuf, "compare", strlen("compare")) == 0)
        {
            LOG("Compare arrays\n");
            arrayCommon(arr1, arr2, arr3);
        }
        else if (strncmp(commandBuf, "printResult", strlen("printResult")) == 0)
        {
            LOG("printing compare result\n");
            printf("%d\n", arr3->size);
            if (arr3->size != 0)
            {
                printArray(arr3);
            }
        }
        else if (strncmp(commandBuf, "exit", strlen("exit")) == 0)
        {
            LOG("running exit command\n");
            freeMemory(arr1,arr2,arr3);
            break;
        }
    }

    return EXIT_SUCCESS;
}
