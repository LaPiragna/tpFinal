#include <stdio.h>
#include <stdlib.h>
#define stock "stockingredientes.bin"
#define demanda "demanda.bin"
#define recetas "recetas.bin"
#define preparadosVenta "stockventa.bin"
#define precios "precios.bin"
#define ventas "ventas.bin"
#define max 30

///-----------------------------Estructuras
typedef struct
{
    char nombre_ingrediente[20];
    float cantidad; //en kg o en litro segun el tipo de ingrediente
    char tipo[20]; /// "liquido" "solido"
    float costo; ///costo por kg o por litro seg n corresponda
} StockIngrediente;

typedef struct
{
    char nombre_ingrediente[20];
    float cantidad; ///puede ser en litro o en kg
} IngredienteXReceta;

typedef struct
{
    char nombre_preparacion[20];
    IngredienteXReceta ingredientes[20]; ///Puede tener hasta 20 ingredientes. Estructura dentro de una estructura
    int cantIngredientes; ///los validos de ingredientes
} Receta;

typedef struct
{
    char nombre_preparacion[20];
    int cantidad; ///por unidad, no hay por peso
} Preparacion;

typedef struct
{
    char nombre_preparacion[20];
    int cantidad; ///por unidad, no hay por peso
} PreparacionVenta;

typedef struct
{
    char nombre_preparacion[20];
    float precio_venta; ///precio por unidad
} PrecioPreparacion;

typedef struct
{
    char nombre_preparacion[20];
    int cantidad;
} PedidoPreparacion;

typedef struct
{
    int idVenta;
    PedidoPreparacion items_pedido[20]; ///puedo pedir hasta 20 items
    int cantItems; ///los validos del arreglo de items_pedido
    float valor_total; ///valor total a pagar
    int bajaLogica;
} Venta;

///-----------------------------Prototipos
//Stock
void despersistenciaStock(StockIngrediente[max], int*);
void mostrarIngredienteStock(StockIngrediente);
void mostrarStock(StockIngrediente[max], int);
void persistenciaStock(StockIngrediente[max], int);
//Preparado
void despersistenciaRecetas(Receta[max], int*);
void mostrarIngredienteReceta(IngredienteXReceta, StockIngrediente[max], int);
void mostrarReceta(Receta, StockIngrediente[max], int);
void mostrarRecetas(Receta[max], int, StockIngrediente[max], int);
void despersistenciaDemanda(Preparacion[max], int*);
void mostrarDemanda(Preparacion);
void mostrarDemandas(Preparacion[max], int);
void usarIngredientes(Receta[max], StockIngrediente[max], Preparacion[max], PreparacionVenta[max], int, int, int, int*);
int disponibilidadIngredientes(StockIngrediente[max], Receta[max], int, int);
void consumoIngredientes(StockIngrediente[max], Preparacion[max], Receta[max], int, int, int);
int finElaboracion(int[max], int);
void ingredientesRestantes(StockIngrediente[max], int);
//Venta
void mostrarPreparadosParaLaVenta(PreparacionVenta[max], int);
void persistenciaPreparados(PreparacionVenta[max], int);
void despersistenciaPreaprados(PreparacionVenta[max], int*);

void despersistenciaPrecios(PrecioPreparacion[max], int*);
float precioPreparado(Receta[max], StockIngrediente[max], int, int);
void establecerListaPrecios(StockIngrediente[max], Receta[max], Preparacion[max], PrecioPreparacion[max], int, int, int, int*);
void mostrarListaPrecios(PreparacionVenta [max], PrecioPreparacion[max], int, int);
void PersistenciaPrecios (PrecioPreparacion[max], int);
void mostrarPedidos(PedidoPreparacion[max], int);
float precioPedido(PrecioPreparacion[max], PedidoPreparacion[max], int, int, int);
float armarPedidos(PreparacionVenta[max], PrecioPreparacion[max], PedidoPreparacion[max], int, int, int*);
void venta(PreparacionVenta[max], PrecioPreparacion[max], PedidoPreparacion[max], Venta[max], int, int, int*);
void mostrarVentas(Venta[max], int);
void PersistenciaVentas (Venta[max], int);
void despersistenciaVenta (Venta[max], int*);
void bajaLogicaVentaPorId(Venta[max], int);
void mantenimientoArchivoVentas(Venta[max], int*);
void reintegrarProductos(PreparacionVenta[max], Venta[max], int, int, int);
int ingresarIdVenta(int);
//Paso4
char mostrarPaso4Menu();
float consultaCaja(Venta[max], int);
float consultaCostos(StockIngrediente[max], Receta[max], Venta[max], int, int, int);
void consultaGanancia(float, float);
void paso4Menu(StockIngrediente[max], Receta[max], PreparacionVenta[max], PrecioPreparacion listaPrecios[max], Venta[max], int, int, int,int, int);
///-----------------------------Main
int main()
{

    StockIngrediente listaStock[max]; //(ingredientes)
    Receta listaRecetas[max];
    Preparacion listaPreparacion[max]; //(demanda)
    PreparacionVenta listaPreparados[max]; //(productos para vender)
    PrecioPreparacion listaPrecios[max];
    PedidoPreparacion listaPedidos[max];
    Venta listaVentas[max];
    int validoStock = 0, validoRecetas = 0, validoDemanda = 0, validoPreparados = 0, validoListaPrecios = 0, validoListaPedidos = 0, validoListaVentas = 0;


    int opcion_usuario;

    despersistenciaStock(listaStock, &validoStock);
    despersistenciaRecetas(listaRecetas, &validoRecetas);
    despersistenciaDemanda(listaPreparacion, &validoDemanda);
    despersistenciaPreaprados(listaPreparados, &validoPreparados);
    despersistenciaPrecios(listaPrecios, &validoListaPrecios);

    do
    {
        printf("\n****** MENU PANADERIA ******\n\n");
        printf("\n----------PASO1----------\n\n");
        printf("1. Ver materia prima ingresada\n\n");
        printf("\n----------PASO2----------\n\n");
        printf("2. Ver las recetas de los productos\n\n");
        printf("3. Ver demanda de productos\n\n");
        printf("4. Realizar preparaciones\n\n");
        printf("5. Productos listos para la venta\n\n");
        printf("\n----------PASO3----------\n\n");
        printf("6. Venta al publico\n\n");
        printf("\n----------PASO4----------\n\n");
        printf("7. Resumen del dia\n\n");
        printf("0. Salir\n\n");
        scanf("%i", &opcion_usuario);

        while (opcion_usuario < 0 || opcion_usuario > 7)
        {
            printf("opcion invalida, ingrese nuevamente\n");
            scanf("%i", &opcion_usuario);
        }

        switch (opcion_usuario)
        {

        case 1:
            system("cls");
            printf("----------STOCK ingredientes----------\n");
            mostrarStock(listaStock, validoStock); //Muestra de la info almacenada de "stockingredientes.bin"
            break;

        case 2:
            system("cls");
            printf("----------RECETAS----------\n");
            mostrarRecetas(listaRecetas, validoRecetas, listaStock, validoStock); //Muestra de la info almacenada de "recetas.bin"
            break;

        case 3:
            system("cls");
            printf("----------DEMANDA----------\n");
            mostrarDemandas(listaPreparacion, validoDemanda); //Muestra de la info almacenada de "demanda.bin"
            break;

        case 4:
            system("cls");
            //Fue necesario hacer todas las despersistencias, porque sino era obligatorio tener que realizar los pasos previos del men�.
            if (validoPreparados == 0)
            {
                usarIngredientes(listaRecetas, listaStock, listaPreparacion, listaPreparados, validoStock, validoDemanda, validoRecetas, &validoPreparados);
                mostrarPreparadosParaLaVenta(listaPreparados, validoPreparados);
                persistenciaPreparados(listaPreparados, validoPreparados);
                persistenciaStock(listaStock, validoStock);
            }
            else
            {
                printf("Los preparados ya fueron elaborados.\n");
            }
            break;

        case 5:
            system("cls");
            mostrarPreparadosParaLaVenta(listaPreparados, validoPreparados);
            break;


        case 6:
            system("cls");
            printf("----------VENTA AL PUBLICO----------\n");
            int opcion;
            do
            {
                printf("1. Establecer precios\n\n");
                printf("2. Realizar una venta\n\n");
                printf("3. Cancelar una compra previa\n\n");
                printf("0. Salir\n\n");
                scanf("%i", &opcion);
                while (opcion < 0 || opcion > 3)
                {
                    printf("ingresar una opcion valida: ");
                    scanf("%i", &opcion);
                }
                switch(opcion)
                {
                case 1:
                    establecerListaPrecios(listaStock, listaRecetas, listaPreparados, listaPrecios, validoStock, validoRecetas, validoPreparados, &validoListaPrecios);
                    PersistenciaPrecios(listaPrecios, validoListaPrecios);
                    break;
                case 2:
                    system("cls");
                    if (listaPrecios[2].precio_venta > 0 && validoListaPrecios > 0 )
                    {
                        venta(listaPreparados, listaPrecios, listaPedidos, listaVentas, validoPreparados, validoListaPrecios, &validoListaVentas);
                        PersistenciaVentas(listaVentas, validoListaVentas);
                        system("cls");
                        mostrarVentas(listaVentas, validoListaVentas);
                    }
                    else
                    {
                        printf("Aun no se ha confeccionado una lista de precios.\n");
                        system("pause");
                    }
                    system("cls");
                    break;
                case 3:
                    system("cls");
                    if (validoListaVentas > 0)
                    {
                        mostrarVentas(listaVentas, validoListaVentas);
                        int id = ingresarIdVenta(validoListaVentas);
                        if (id != 0)
                        {
                            reintegrarProductos(listaPreparados, listaVentas, validoPreparados, id, validoListaVentas);
                            bajaLogicaVentaPorId(listaVentas, id);
                            mantenimientoArchivoVentas(listaVentas, &validoListaVentas);
                            system("cls");
                            mostrarVentas(listaVentas, validoListaVentas);
                        }
                    }
                    else
                    {
                        printf("No hay ventas realizadas.\n");
                    }
                    system("pause");
                    system("cls");
                    break;
                case 0:
                    break;
                }
            }
            while (opcion != 0);
            break;

        case 7:
            paso4Menu(listaStock, listaRecetas, listaPreparados, listaPrecios, listaVentas, validoStock, validoRecetas, validoPreparados, validoListaPrecios, validoListaVentas);
            break;
        }

        system("pause");
        system("cls");
    }
    while (opcion_usuario != 0);

    return 0;
}

///----------STOCK----------
void mostrarIngredienteStock(StockIngrediente i)
{
    puts(i.nombre_ingrediente);
    if (strcmpi(i.tipo, "solido")==0)
    {
        if (strcmpi(i.nombre_ingrediente, "huevo")==0)
        {
            printf("Cantidad: %.0f\n", i.cantidad);
        }
        else
            printf("Cantidad: %.0f kg.\n", i.cantidad);
    }
    else if (strcmpi(i.tipo, "liquido")==0)
    {
        printf("Cantidad: %.0f litros.\n", i.cantidad);
    }
    puts(i.tipo);
    printf("Costo: %.1f\n\n", i.costo);
}
void mostrarStock(StockIngrediente listaStock[max], int validos)
{
    int i = 0;
    while (i < validos)
    {
        mostrarIngredienteStock(listaStock[i]);
        i++;
    }
}
void despersistenciaStock(StockIngrediente lista[max], int* validos)
{
    int i = 0;
    FILE* buffer;
    buffer = fopen(stock, "rb");
    if (buffer != NULL)
    {
        while (fread(&lista[i], sizeof(StockIngrediente),1,buffer) > 0)
        {
            i++;
        }
        fclose(buffer);
    }
    *validos = i;
}
void persistenciaStock(StockIngrediente listaStock[max], int validoStock)
{
    FILE* fp;
    fp = fopen(stock, "wb");
    if (fp != NULL)
    {
        fwrite(listaStock, sizeof(StockIngrediente), validoStock, fp);
        fclose(fp);
    }
}
///----------RECETAS----------
void mostrarIngredienteReceta(IngredienteXReceta x, StockIngrediente listaStock[max], int validoStock)
{
    int i = 0;

    puts(x.nombre_ingrediente);

    while (strcmpi(x.nombre_ingrediente, listaStock[i].nombre_ingrediente) != 0) //Busqueda del ingrediente por nombre
    {
        i++;
    }
    //Si i < validos, se encuentra
    if (i < validoStock && strcmpi(listaStock[i].tipo, "liquido") == 0)
    {
        printf("cantidad: %.3f litros.\n", x.cantidad);
    }
    else if (i < validoStock && strcmpi(listaStock[i].tipo, "solido") == 0)
    {
        if (strcmpi(x.nombre_ingrediente, "huevo")==0) //Cuando es huevo, en unidades
        {
            printf("Cantidad: %.f\n", x.cantidad);
        }
        else
            printf("Cantidad: %.3f kg.\n", x.cantidad);
    }
}
void mostrarReceta(Receta r, StockIngrediente listaStock[max], int validoStock)
{
    puts(r.nombre_preparacion);
    for (int i = 0; i < r.cantIngredientes; i++)
    {
        mostrarIngredienteReceta(r.ingredientes[i], listaStock, validoStock);
        printf("\n");
    }
    printf("------------------------------------------\n");
}
void mostrarRecetas(Receta listaRecetas[max], int validoReceta, StockIngrediente listaStock[max], int validoStock)
{
    for (int i = 0; i < validoReceta; i++)
    {
        mostrarReceta(listaRecetas[i], listaStock, validoStock);
    }
}
void despersistenciaRecetas(Receta lista[max], int* validos)
{
    int i = 0;
    FILE* fp;
    fp = fopen (recetas, "rb");
    if (fp != NULL)
    {
        while(fread(&lista[i], sizeof(Receta),1,fp) > 0)
        {
            i++;
        }
        fclose(fp);
    }
    *validos = i;
}
///----------DEMANDA----------
void mostrarDemanda(Preparacion p)
{
    printf("%s: ", p.nombre_preparacion);
    printf("%d\n\n", p.cantidad);
}

void mostrarDemandas(Preparacion lista[max], int validos)
{
    for (int i = 0; i < validos; i++)
    {
        mostrarDemanda(lista[i]);
    }
}
void despersistenciaDemanda(Preparacion lista[max], int* validos)
{
    int i = 0;
    FILE* fp;
    fp = fopen(demanda, "rb");
    if (fp != NULL)
    {
        while (fread(&lista[i], sizeof(Preparacion), 1, fp) != 0)
        {
            i++;
        }
        fclose(fp);
    }
    *validos = i;
}
///----------PREPARADO----------
void consumoIngredientes(StockIngrediente listaStockIngredientes[max], Preparacion listaDemandas[max], Receta listaRecetas[max], int validoStockIngredientes, int iDemanda, int iReceta)
{
    int i = 0;
    printf("cantidad de INGREDIENTES necesarios para hacer 1 %s: %i\n\n", listaRecetas[iReceta].nombre_preparacion, listaRecetas[iReceta].cantIngredientes);
    system("cls");
    while (i < listaRecetas[iReceta].cantIngredientes)
    {
        for (int j = 0; j < validoStockIngredientes; j++)
        {
            if (strcmpi(listaRecetas[iReceta].ingredientes[i].nombre_ingrediente, listaStockIngredientes[j].nombre_ingrediente)==0)
            {
                listaStockIngredientes[j].cantidad = listaStockIngredientes[j].cantidad - listaRecetas[iReceta].ingredientes[i].cantidad;
                if(strcmpi(listaStockIngredientes[j].tipo, "solido")==0)
                {
                    if (strcmpi(strcmpi(listaStockIngredientes[j].nombre_ingrediente, "huevo")==0))
                    {
                        printf("%s restante: %.0f.\n\n", listaStockIngredientes[j].nombre_ingrediente, listaStockIngredientes[j].cantidad);
                    }
                    else
                    {
                        printf("%s restante: %.3f kilos.\n\n", listaStockIngredientes[j].nombre_ingrediente, listaStockIngredientes[j].cantidad);
                    }
                }
                else if (strcmpi(listaStockIngredientes[j].tipo, "liquido")==0)
                {
                    printf("%s restante: %.3f litros.\n\n", listaStockIngredientes[j].nombre_ingrediente, listaStockIngredientes[j].cantidad);
                }
            }
        }
        i++;
    }
}

int disponibilidadIngredientes(StockIngrediente listaStockIngredientes[max], Receta listaRecetas[max], int validoStock, int iReceta)
{
    int disponibilidad = 1, j = 0;
    for (int i = 0; i < listaRecetas[iReceta].cantIngredientes; i++)
    {
        j = 0;
        while (j < validoStock && strcmpi(listaRecetas[iReceta].ingredientes[i].nombre_ingrediente, listaStockIngredientes[j].nombre_ingrediente)!=0)
        {
            j++;
        }
        if (j < validoStock)
        {
            if ((listaStockIngredientes[j].cantidad - listaRecetas[iReceta].ingredientes[i].cantidad)>=0)
            {
            }
            else if ((listaStockIngredientes[j].cantidad - listaRecetas[iReceta].ingredientes[i].cantidad)<0)
            {
                printf("NO hay disponibilidad de %s para %s.\n", listaStockIngredientes[j].nombre_ingrediente, listaRecetas[iReceta].nombre_preparacion);
                disponibilidad = 0;
            }
        }
    }
    printf("dispo %s: %i\n\n",listaRecetas[iReceta].nombre_preparacion, disponibilidad);
    return disponibilidad;
}

void usarIngredientes(Receta listaRecetas[max], StockIngrediente listaStockIngredientes[max], Preparacion listaDemandas[max], PreparacionVenta listaPreaparados[max], int validoStockIngredientes, int validoDemanda, int validoRecetas, int* validoPreparados)
{
    int validos = 0;
    for (int i = 0; i < validoDemanda; i++)
    {
        validos++;
        strcpy(listaPreaparados[i].nombre_preparacion, listaDemandas[i].nombre_preparacion);
        listaPreaparados[i].cantidad=0;
        for (int j = 0; j < validoRecetas; j++)
        {
            if (strcmpi(listaDemandas[i].nombre_preparacion, listaRecetas[j].nombre_preparacion)==0)
            {
                while (listaDemandas[i].cantidad > 0 && (disponibilidadIngredientes(listaStockIngredientes, listaRecetas, validoStockIngredientes, j)==1))
                {
                    consumoIngredientes(listaStockIngredientes, listaDemandas, listaRecetas, validoStockIngredientes, i, j);
                    listaDemandas[i].cantidad--;
                    listaPreaparados[i].cantidad++;
                    printf("demanda restante de %s: %i\n", listaDemandas[i].nombre_preparacion, listaDemandas[i].cantidad);
                }
            }
        }
    }
    *validoPreparados = validos;
}

void ingredientesRestantes(StockIngrediente listaStockIngredientes[max], int validoStockIngredientes)
{
    printf("ingredientes restantes:\n\n");
    for (int i = 0; i < validoStockIngredientes; i++)
    {
        if (strcmpi(listaStockIngredientes[i].tipo, "solido") == 0)
        {
            if (strcmpi(listaStockIngredientes[i].nombre_ingrediente, "huevo") == 0)
            {
                printf("%s: %.3f\n", listaStockIngredientes[i].nombre_ingrediente, listaStockIngredientes[i].cantidad);
            }
            else
                printf("%s: %.3f kg\n", listaStockIngredientes[i].nombre_ingrediente, listaStockIngredientes[i].cantidad);
        }
        else if (strcmpi(listaStockIngredientes[i].tipo, "liquido") == 0)
        {
            printf("%s: %.3f litros\n", listaStockIngredientes[i].nombre_ingrediente, listaStockIngredientes[i].cantidad);
        }
    }
    printf("\n\n\n");
}
///----------VENTA----------

void mostrarPreparadosParaLaVenta(PreparacionVenta listaPreparados[max], int validoPreparados)
{
    printf("PREPARADOS: \n\n");
    for (int i = 0; i < validoPreparados; i++)
    {
        printf("%s: %i.\n", listaPreparados[i].nombre_preparacion, listaPreparados[i].cantidad);
    }
    printf("\n\n\n");
}

void persistenciaPreparados(PreparacionVenta listaPreparados[max], int validoPreparados)
{
    FILE* fp;
    fp = fopen("stockventa.bin","wb");
    if (fp != NULL)
    {
        fwrite(listaPreparados,sizeof(PreparacionVenta),validoPreparados,fp);
        fclose(fp);
    }

}

void despersistenciaPreaprados(PreparacionVenta listaPreparados[max], int* validoPreparados)
{
    int i = 0;
    FILE* fp;
    fp = fopen(preparadosVenta, "rb");
    if (fp != NULL)
    {
        while(fread(&listaPreparados[i], sizeof(PreparacionVenta), 1, fp)>0)
        {
            i++;
        }
        fclose(fp);
        *validoPreparados = i;
    }
    else
    {
        printf("No habia existencia de tal archivo...\n\n");
    }
}

void despersistenciaPrecios(PrecioPreparacion listaPrecios[max], int* validoPrecios)
{
    int i = 0;
    FILE* fp;
    fp = fopen(preparadosVenta, "rb");
    if (fp != NULL)
    {
        while(fread(&listaPrecios[i], sizeof(PrecioPreparacion), 1, fp)>0)
        {
            i++;
        }
        fclose(fp);
        *validoPrecios = i;
    }
    else
    {
        printf("No habia existencia de tal archivo...\n\n");
    }
}

float precioPreparado(Receta listaRecetas[max], StockIngrediente listaStockIngredientes[max], int iReceta, int validoStockIngredientes)
{
    float precio = 0;
    for (int i = 0; i < listaRecetas[iReceta].cantIngredientes; i++)
    {
        for (int j = 0; j < validoStockIngredientes; j++)
        {
            if (strcmpi(listaRecetas[iReceta].ingredientes[i], listaStockIngredientes[j])==0)
            {
                precio = precio + listaStockIngredientes[j].costo;
            }
        }
    }
    return precio;
}

void establecerListaPrecios(StockIngrediente listaIngredientesStock[max], Receta listaRecetas[max], Preparacion listaPreparados[max], PrecioPreparacion listaPrecios[max],int validoStock, int validoRecetas, int validoPreparados, int* validoListaPrecios)
{
    int validoVenta = 0;

    float ganancia = 0;
    float precio = 0, precioGanancia = 0;

    system("cls");
    printf("Indicar el porcentaje de ganancia por venta (del 0 al 100):");
    scanf("%f", &ganancia);
    while (ganancia < 0 || ganancia > 100)
    {
        printf("Introducir un porcentaje dentro del rango indicado... (del 1 al 100)");
        scanf("%f", &ganancia);
    }

    printf("Porcentaje de ganancia: %%%.1f\n", ganancia);
    system("cls");

    for (int i = 0; i < validoPreparados; i++)
    {
        precio = 0;
        precioGanancia = 0;
        for (int j = 0; j < validoRecetas; j++)
        {
            if (strcmpi(listaPreparados[i].nombre_preparacion, listaRecetas[j].nombre_preparacion) == 0)
            {
                precio = precioPreparado(listaRecetas, listaIngredientesStock, j, validoStock);
                precioGanancia = precio + (precio*ganancia/100);
                strcpy(listaPrecios[i].nombre_preparacion, listaPreparados[i].nombre_preparacion);
                listaPrecios[i].precio_venta = precioGanancia;
                validoVenta++;
            }
        }
    }
    *validoListaPrecios = validoVenta;
}

void mostrarListaPrecios(PreparacionVenta listaPreparados[max], PrecioPreparacion listaPrecios[max], int validoListaPreparados, int validoListaPrecios)
{
    printf("    \n\nPRECIOS x UNIDAD\n\n");
    for (int i = 0; i < validoListaPreparados; i++)
    {
        for (int j = 0; j < validoListaPrecios; j++)
        {
            if (strcmpi(listaPreparados[i].nombre_preparacion, listaPrecios[j].nombre_preparacion)==0)
            {
                printf("(%i) %s: $%.1f     (%i restantes)\n", i, listaPreparados[i].nombre_preparacion, listaPrecios[i].precio_venta, listaPreparados[i].cantidad);
            }
        }
    }
}

void PersistenciaPrecios (PrecioPreparacion listaPrecios[max], int validoListaPrecios)
{
    FILE* fp;
    fp = fopen(precios, "wb");
    if (fp != NULL)
    {
        fwrite(listaPrecios, sizeof(PrecioPreparacion), validoListaPrecios, fp);
        fclose(fp);
    }
}

void mostrarPedidos(PedidoPreparacion listaPedidos[max], int validoPedidos)
{
    printf("PEDIDOS REALIZADOS:\n");
    for (int i = 0; i < validoPedidos; i++)
    {
        printf("%s: %i\n", listaPedidos[i].nombre_preparacion, listaPedidos[i].cantidad);
    }
}

float precioPedido(PrecioPreparacion listaPrecios[max], PedidoPreparacion listaPedidos[max], int validoListaPrecios, int iPedido, int cantidad)
{
    float costo = 0;
    for (int i = 0; i < validoListaPrecios; i++)
    {
        if (strcmpi(listaPrecios[i].nombre_preparacion, listaPedidos[iPedido].nombre_preparacion)==0)
        {
            costo = listaPrecios[i].precio_venta * listaPedidos[iPedido].cantidad;
        }
    }
    return costo;
}

float armarPedidos(PreparacionVenta listaPreparados[max], PrecioPreparacion listaPrecios[max], PedidoPreparacion listaPedidos[max], int validoPreparados, int validoListaPrecios, int* validoPedidos)
{
    char continuar;
    int i = 0, pedido, cantidad;
    float total=0;

    do
    {
        pedido = 0;
        cantidad = 0;

        mostrarListaPrecios(listaPreparados, listaPrecios, validoPreparados, validoListaPrecios);
        printf("\nPEDIDO %i\n", i);

        printf("\ningresa un numero para seleccionar un producto: ");
        scanf("%i", &pedido);
        while (pedido < 0 || pedido > validoListaPrecios)
        {
            system("cls");
            mostrarListaPrecios(listaPreparados, listaPrecios, validoPreparados, validoListaPrecios);
            printf("Ingresa un numero valido:");
            scanf("%i", &pedido);
        }

        printf("Has seleccionado: %s.\n", listaPreparados[pedido].nombre_preparacion);

        printf("ingresa la cantidad que queres llevar: (%i restantes)", listaPreparados[pedido].cantidad);
        scanf("%i", &cantidad);

        while (cantidad < 0 || cantidad > listaPreparados[pedido].cantidad)
        {
            printf("\ningresar una cantidad valida... (%i restantes)", listaPreparados[pedido].cantidad);
            scanf("%i", &cantidad);
        }

        listaPreparados[pedido].cantidad = listaPreparados[pedido].cantidad - cantidad;
        strcpy(listaPedidos[i].nombre_preparacion, listaPreparados[pedido].nombre_preparacion);
        listaPedidos[i].cantidad = cantidad;
        total = total + precioPedido(listaPrecios, listaPedidos, validoListaPrecios, i, cantidad);

        i++;

        printf("s si quieres realizar otro pedido: ");
        fflush(stdin);
        scanf("%c", &continuar);
        system("cls");
    }
    while (i < 20 && continuar == 's');

    *validoPedidos = i;

    return total;
}

void mostrarVentas(Venta listaVentas[max], int validoVentas)
{
    for (int i = 0; i < validoVentas; i++)
    {
        printf("\nID VENTA: ---%i---\n", listaVentas[i].idVenta);
        for (int j = 0; j < listaVentas[i].cantItems; j++)
        {
            printf("%s: %i\n", listaVentas[i].items_pedido[j].nombre_preparacion, listaVentas[i].items_pedido[j].cantidad);
        }
        printf("cant. items: %i\n", listaVentas[i].cantItems);
        printf("total: $%.2f\n\n", listaVentas[i].valor_total);
    }
}

void venta(PreparacionVenta listaPreparados[max], PrecioPreparacion listaPrecios[max], PedidoPreparacion listaPedido[max], Venta listaVentas[max], int validoPreparados, int validoListaPrecios, int* validoVentas)
{
    int validoPedidos, i = *validoVentas;
    float costoTotal;
    char continuar;

    do
    {
        costoTotal = 0;
        validoPedidos = 0;
        listaVentas[i].idVenta = (i+1);

        printf("\nID VENTA: ---%i---\n", listaVentas[i].idVenta);

        costoTotal = armarPedidos(listaPreparados, listaPrecios, listaPedido, validoPreparados, validoListaPrecios, &validoPedidos);

        for (int j = 0; j < validoPedidos; j++)
        {
            strcpy(listaVentas[i].items_pedido[j].nombre_preparacion, listaPedido[j].nombre_preparacion);
            listaVentas[i].items_pedido[j].cantidad = listaPedido[j].cantidad;
        }
        listaVentas[i].bajaLogica = 0;
        listaVentas[i].cantItems = validoPedidos;
        listaVentas[i].valor_total = costoTotal;

        i++;

        printf("s para realizar una nueva orden de compra: ");
        fflush(stdin);
        scanf("%c", &continuar);
        system("cls");
    }
    while(continuar == 's');

    *validoVentas = i;
    system("pause");
}

void PersistenciaVentas (Venta listaVentas[max], int validoListaVentas)
{
    FILE* fp;
    fp = fopen(ventas, "wb");
    if (fp != NULL)
    {
        fwrite(listaVentas, sizeof(Venta), validoListaVentas, fp);
        fclose(fp);
    }

}

char mostrarPaso4Menu()
{
    char opcion;
    printf("CONSULTA DE ESTADO\n\n");
    printf("(1) ingredientes restantes: \n");
    printf("(2) lista de preparados restantes: \n");
    printf("(3) consulta de caja: \n");
    printf("(4) calculo de ganancia: \n");
    printf("(0) salir: \n");
    fflush(stdin);
    scanf("%c", &opcion);
    while(opcion < '0' || opcion > '4')
    {
        printf("Ingresa una opcion valida...\n");
        fflush(stdin);
        scanf("%c", &opcion);
    }
    return opcion;
}

float consultaCaja(Venta listaVentas[max], int validoVentas)
{
    float ingreso = 0;
    for (int i = 0; i < validoVentas; i++)
    {
        ingreso = ingreso + listaVentas[i].valor_total;
    }
    printf("Ingresos totales: $%.2f\n", ingreso);
    return ingreso;
}

float consultaCostos(StockIngrediente listaStockIngredientes[max], Receta listaRecetas[max], Venta listaVentas[max], int validoStockIngredientes, int validoRecetas, int validoVentas)
{
    float precio = 0;
    for (int i = 0; i < validoVentas; i++)
    {
        for (int j = 0; j < listaVentas[i].cantItems; j++)
        {
            for (int p = 0; p < validoRecetas; p++)
            {
                if (strcmpi(listaVentas[i].items_pedido[j].nombre_preparacion, listaRecetas[p].nombre_preparacion)==0)
                {
                    precio = precio + precioPreparado(listaRecetas, listaStockIngredientes, p,validoStockIngredientes);
                }
            }
        }
    }
    return precio;
}

void consultaGanancia(float ingresos, float costos)
{
    float gananciaNeta = ingresos - costos;
    printf("ganancia NETA del dia $%.2f\n", gananciaNeta);
    printf("\n\n\n");
}

void paso4Menu(StockIngrediente listaStockIngredientes[max], Receta listaRecetas[max], PreparacionVenta listaPreparados[max], PrecioPreparacion listaPrecios[max], Venta listaVentas[max], int validoStockIngredientes, int validoRecetas, int validoListaPreparados, int validoListaPrecios, int validoVentas)
{
    char opcion;
    do
    {
        system("cls");
        opcion = mostrarPaso4Menu();
        switch (opcion)
        {
        case '0':
            system("cls");
            break;
        case '1':
            system("cls");
            ingredientesRestantes(listaStockIngredientes, validoStockIngredientes);
            system("pause");
            break;
        case '2':
            system("cls");
            mostrarPreparadosParaLaVenta(listaPreparados, validoListaPreparados);
            system("pause");
            break;
        case '3':
            system("cls");
            consultaCaja(listaVentas, validoVentas);
            system("pause");
            break;
        case '4':
            system("cls");
            consultaGanancia((consultaCaja(listaVentas, validoVentas)),(consultaCostos(listaStockIngredientes, listaRecetas, listaVentas, validoStockIngredientes, validoRecetas, validoVentas)));
            system("pause");
            break;
        }
    }
    while (opcion != '0');
}

void despersistenciaVenta(Venta listaVentas[max], int* validoVentas)
{
    int i = 0;
    FILE* fp;
    fp = fopen(ventas, "rb");
    if (fp != NULL)
    {
        while(fread(&listaVentas[i], sizeof(Venta), 1, fp)>0)
        {
            if (listaVentas[i].bajaLogica == 0)
            {
                i++;
            }
        }
        fclose(fp);
    }
    *validoVentas = i;
}


int ingresarIdVenta(int validoVentas)
{
    int id;
    printf("Ingresa el id para dar de baja... (o 0 para salir) ");
    scanf("%i", &id);
    while (id < 0 || id > validoVentas)
    {
        printf("Ingresar una opcion valida...\n");
        scanf("%i", &id);
    }
    return id;
}

int cantidadRegistrosVenta()
{
    int cantidad = 0;
    FILE* fp;
    fp = fopen(ventas, "rb");
    if (fp != NULL)
    {
        fseek(fp, 0, SEEK_END);
        cantidad = ftell(fp)/sizeof(Venta);
        fclose(fp);
    }
    return cantidad;
}

void bajaLogicaVentaPorId(Venta listaVentas[max], int id)
{

    int i = 0, cantidadVentas = cantidadRegistrosVenta();
    printf("cantidad ventas: %i\n\n", cantidadVentas);
    FILE* fp;
    fp = fopen(ventas, "r+b");
    if (fp != NULL)
    {
        fread(&listaVentas[i], sizeof(Venta), 1, fp);
        while (i < cantidadVentas && listaVentas[i].idVenta != id)
        {
            i++;
            fread(&listaVentas[i], sizeof(Venta), 1, fp);
        }
    }
    if (i < cantidadVentas)
    {
        listaVentas[i].bajaLogica = 1;
        fseek(fp, (-1)*sizeof(Venta), SEEK_CUR);
        fwrite(&listaVentas[i], sizeof(Venta), 1, fp);
    }
    fclose(fp);
}

void mantenimientoArchivoVentas(Venta listaVentas[max], int* validoVentas)
{
    despersistenciaVenta(listaVentas, validoVentas);
    PersistenciaVentas(listaVentas, *validoVentas);
}

void reintegrarProductos(PreparacionVenta listaPreparados[max], Venta listaVenta[max], int validoPreparados, int id, int validoVentas)
{
    for (int i = 0; i < validoVentas; i++)
    {
        printf("ID DE VENTA: %i\n", listaVenta[i].idVenta);
        if (listaVenta[i].idVenta == id)
        {
            for (int p = 0; p < listaVenta[i].cantItems; p++)
            {
                for (int j = 0; j < validoPreparados; j++)
                {
                    if (strcmpi(listaVenta[i].items_pedido[i].nombre_preparacion, listaPreparados[j].nombre_preparacion)==0)
                    {
                        listaPreparados[j].cantidad = listaPreparados[j].cantidad + listaVenta[i].items_pedido[p].cantidad;
                    }
                }
            }
        }
    }
}
