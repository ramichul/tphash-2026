#include "pa2m.h"
#include <stdio.h>
#include <stdlib.h>
#include "../src/diccionario.h"

bool funcion_generica_comparador_enteros(struct diccionario_par *par,
					 void *numero)
{
	return *((int *)par->valor) == *((int *)numero);
}

bool funcion_generica_reemplazar_todos(struct diccionario_par *par,
				       void *numero)
{
	*((int *)par->valor) = *((int *)numero);
	return true;
}

void diccionario_crear_crea_un_diccionario_con_capacidad_valida()
{
	diccionario_t *diccionario = diccionario_crear(10);

	pa2m_afirmar(diccionario != NULL,
		     "diccionario_crear() crea un diccionario exitosamente");

	diccionario_destruir(diccionario);
}

void diccionario_crear_crea_un_diccionario_con_capacidad_debajo_del_minimo()
{
	diccionario_t *diccionario = diccionario_crear(1);

	pa2m_afirmar(
		diccionario != NULL,
		"diccionario_crear() crea un diccionario sin problemas dada una capacidad debajo del mínimo");

	diccionario_destruir(diccionario);
}

void diccionario_crear_crea_un_diccionario_vacio()
{
	diccionario_t *diccionario = diccionario_crear(10);

	pa2m_afirmar(
		diccionario_cantidad(diccionario) == 0,
		"diccionario_crear() se ejecuta exitosamente y el diccionario está vacío");

	diccionario_destruir(diccionario);
}

void diccionario_cantidad_toma_diccionario_nulo_como_vacio()
{
	pa2m_afirmar(
		diccionario_cantidad(NULL) == 0,
		"diccionario_cantidad() recibe un diccionario nulo y lo asume como vacío");
}

void diccionario_cantidad_devuelve_0_con_diccionario_vacio()
{
	diccionario_t *diccionario = diccionario_crear(10);

	pa2m_afirmar(
		diccionario_cantidad(diccionario) == 0,
		"diccionario_cantidad() recibe un diccionario vacío y devuelve 0");

	diccionario_destruir(diccionario);
}

void diccionario_cantidad_devuelve_valor_correcto()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	int valor = 0;

	diccionario_insertar(diccionario, clave, &valor, NULL);

	pa2m_afirmar(
		diccionario_cantidad(diccionario) == 1,
		"diccionario_cantidad() devuelve el valor correspondiente de claves presentes");

	diccionario_destruir(diccionario);
}

void diccionario_insertar_devuelve_null_en_caso_de_error()
{
	pa2m_afirmar(diccionario_insertar(NULL, NULL, NULL, NULL) == NULL,
		     "diccionario_insertar() devuelve NULL en caso de error");
}

void diccionario_insertar_no_intenta_insertar_en_diccionario_nulo()
{
	const char *clave = "Clave";
	int valor = 0;

	pa2m_afirmar(
		diccionario_insertar(NULL, clave, &valor, NULL) == NULL,
		"diccionario_insertar() no intenta insertar en un diccionario nulo");
}

void diccionario_insertar_no_intenta_insertar_par_con_clave_nula()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = NULL;
	int valor = 0;

	pa2m_afirmar(
		diccionario_insertar(diccionario, clave, &valor, NULL) == NULL,
		"diccionario_insertar() no intenta insertar un par con una clave nula");

	diccionario_destruir(diccionario);
}

void diccionario_insertar_devuelve_puntero_al_mismo_diccionario()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	int valor = 0;

	pa2m_afirmar(
		diccionario_insertar(diccionario, clave, &valor, NULL) ==
			diccionario,
		"diccionario_insertar() devuelve un puntero al mismo diccionario al realizarse con éxito");

	diccionario_destruir(diccionario);
}

void diccionario_insertar_logra_insertar_y_el_elemento_esta_presente()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	int valor = 0;
	diccionario_insertar(diccionario, clave, &valor, NULL);

	pa2m_afirmar(
		diccionario_obtener(diccionario, clave) != NULL,
		"diccionario_insertar() inserta una clave con éxito y esta está presente dentro del diccionario");

	diccionario_destruir(diccionario);
}

void diccionario_insertar_logra_insertar_un_valor_nulo()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	void *valor = NULL;
	diccionario_t *resultado_insertar =
		diccionario_insertar(diccionario, clave, valor, NULL);

	pa2m_afirmar(resultado_insertar == diccionario,
		     "diccionario_insertar() inserta un valor nulo con éxito");

	diccionario_destruir(diccionario);
}

void diccionario_insertar_logra_insertar_y_cambia_cantidad()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	int valor = 0;

	diccionario_insertar(diccionario, clave, &valor, NULL);

	pa2m_afirmar(
		diccionario_cantidad(diccionario) == 1,
		"diccionario_insertar() inserta una clave con éxito y se reflejan los cambios en la cantidad de claves");

	diccionario_destruir(diccionario);
}

void diccionario_insertar_sobreescribe_valor_y_no_cambia_cantidad()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	int valor_1 = 0;
	int valor_2 = 5;

	diccionario_insertar(diccionario, clave, &valor_1, NULL);
	diccionario_insertar(diccionario, clave, &valor_2, NULL);

	pa2m_afirmar(
		diccionario_cantidad(diccionario) == 1,
		"diccionario_insertar() sobreescribe un valor y no cambia la cantidad de claves presentes");

	diccionario_destruir(diccionario);
}

void diccionario_insertar_sobreescribe_valores()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	int valor_1 = 0;
	int valor_2 = 5;

	diccionario_insertar(diccionario, clave, &valor_1, NULL);
	diccionario_insertar(diccionario, clave, &valor_2, NULL);

	int *valor_obtenido = diccionario_obtener(diccionario, clave);

	pa2m_afirmar(*valor_obtenido = valor_2,
		     "diccionario_insertar() sobreescribe el valor de la clave al intentar insertar con claves repetidas");

	diccionario_destruir(diccionario);
}

void diccionario_insertar_modifica_puntero_correctamente_al_insertar()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	int valor = 0;
	void *valor_anterior;

	diccionario_insertar(diccionario, clave, &valor, &valor_anterior);

	pa2m_afirmar(
		valor_anterior == NULL,
		"diccionario_insertar() modifica el puntero de valor anterior a NULL si la clave no estaba presente en el diccionario al momento de insertar");

	diccionario_destruir(diccionario);
}

void diccionario_insertar_devuelve_el_valor_anterior_correcto()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	int valor_1 = 0;
	int valor_2 = 5;
	void *valor_anterior;

	diccionario_insertar(diccionario, clave, &valor_1, NULL);
	diccionario_insertar(diccionario, clave, &valor_2, &valor_anterior);

	pa2m_afirmar(
		*((int *)valor_anterior) == valor_1,
		"diccionario_insertar() devuelve el valor anterior correcto al sobreescribir");

	diccionario_destruir(diccionario);
}

void diccionario_insertar_inserta_claves_sobre_la_capacidad_inicial()
{
	diccionario_t *diccionario = diccionario_crear(8);
	const char *claves[] = { "Clave 1", "Clave 2", "Clave 3", "Clave 4",
				 "Clave 5", "Clave 6", "Clave 7", "Clave 8",
				 "Clave 9", "Clave 10" };
	int valores[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	size_t cantidad_de_claves = sizeof(valores) / sizeof(int);
	bool verificaciones[cantidad_de_claves];
	bool cumple_todas_las_afirmaciones = true;

	for (size_t i = 0; i < cantidad_de_claves; i++) {
		verificaciones[i] = diccionario_insertar(diccionario, claves[i],
							 &valores[i],
							 NULL) == diccionario;
	}
	for (size_t i = 0;
	     i < cantidad_de_claves && cumple_todas_las_afirmaciones; i++) {
		if (!verificaciones[i])
			cumple_todas_las_afirmaciones = false;
	}

	pa2m_afirmar(
		cumple_todas_las_afirmaciones,
		"diccionario_insertar() inserta más claves que la capacidad inicial con éxito");

	diccionario_destruir(diccionario);
}

void diccionario_eliminar_devuelve_null_en_caso_de_error()
{
	pa2m_afirmar(diccionario_eliminar(NULL, NULL) == NULL,
		     "diccionario_eliminar() devuelve NULL en caso de error");
}

void diccionario_eliminar_no_intenta_eliminar_de_diccionario_nulo()
{
	const char *clave = "Clave";

	pa2m_afirmar(
		diccionario_eliminar(NULL, clave) == NULL,
		"diccionario_eliminar() no intenta eliminar de un diccionario nulo");
}

void diccionario_eliminar_no_intenta_eliminar_de_diccionario_vacio()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";

	pa2m_afirmar(
		diccionario_eliminar(diccionario, clave) == NULL,
		"diccionario_eliminar() no intenta eliminar de un diccionario vacío");

	diccionario_destruir(diccionario);
}

void diccionario_eliminar_no_intenta_eliminar_par_con_clave_nula()
{
	diccionario_t *diccionario = diccionario_crear(10);

	pa2m_afirmar(
		diccionario_eliminar(diccionario, NULL) == NULL,
		"diccionario_eliminar() no intenta eliminar un par con una clave nula");

	diccionario_destruir(diccionario);
}

void diccionario_eliminar_no_intenta_eliminar_elemento_no_presente()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	const char *clave_no_presente = "Clave no presente";
	int valor = 5;

	diccionario_insertar(diccionario, clave, &valor, NULL);
	void *reseultado_eliminar =
		diccionario_eliminar(diccionario, clave_no_presente);

	pa2m_afirmar(
		reseultado_eliminar == NULL,
		"diccionario_eliminar() no intenta eliminar dada una clave que no está presente en el diccionario");

	diccionario_destruir(diccionario);
}

void diccionario_eliminar_elimina_elemento_y_extrae_datos_correctamente()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	int valor = 5;

	diccionario_insertar(diccionario, clave, &valor, NULL);
	int *valor_elemento_eliminado =
		diccionario_eliminar(diccionario, clave);

	pa2m_afirmar(
		*valor_elemento_eliminado == valor,
		"diccionario_eliminar() elimina un elemento y extrae sus datos correctamente");

	diccionario_destruir(diccionario);
}

void diccionario_eliminar_elimina_elemento_y_lo_remueve_del_diccionario()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	int valor = 5;

	diccionario_insertar(diccionario, clave, &valor, NULL);
	diccionario_eliminar(diccionario, clave);

	pa2m_afirmar(
		!diccionario_existe(diccionario, clave),
		"diccionario_eliminar() elimina un elemento y ya no forma parte del diccionario");

	diccionario_destruir(diccionario);
}

void diccionario_eliminar_cambia_cantidad_de_elementos_correctamente()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	int valor = 5;

	diccionario_insertar(diccionario, clave, &valor, NULL);
	diccionario_eliminar(diccionario, clave);

	pa2m_afirmar(
		diccionario_cantidad(diccionario) == 0,
		"diccionario_eliminar() elimina un elemento y los cambios se reflejan en la cantidad de claves presentes");

	diccionario_destruir(diccionario);
}

void diccionario_obtener_ignora_diccionario_nulo()
{
	const char *clave = "Clave";
	void *resultado_obtener = diccionario_obtener(NULL, clave);

	pa2m_afirmar(
		resultado_obtener == NULL,
		"diccionario_obtener() no intenta buscar en un diccionario nulo");
}

void diccionario_obtener_ignora_diccionario_vacio()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";

	void *resultado_obtener = diccionario_obtener(NULL, clave);

	pa2m_afirmar(
		resultado_obtener == NULL,
		"diccionario_obtener() no intenta buscar en un diccionario vacío");

	diccionario_destruir(diccionario);
}

void diccionario_obtener_encuentra_elemento_presente()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	int valor = 0;

	diccionario_insertar(diccionario, clave, &valor, NULL);
	void *resultado_obtener = diccionario_obtener(diccionario, clave);

	pa2m_afirmar(
		resultado_obtener != NULL,
		"diccionario_obtener() logra encontrar una clave presente en el diccionario");

	diccionario_destruir(diccionario);
}

void diccionario_obtener_encuentra_elemento_y_extrae_dato()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	int valor = 0;

	diccionario_insertar(diccionario, clave, &valor, NULL);
	int *resultado_obtener = diccionario_obtener(diccionario, clave);

	pa2m_afirmar(
		*resultado_obtener == valor,
		"diccionario_obtener() encuentra una clave y extrae su dato correspondiente con éxito");

	diccionario_destruir(diccionario);
}

void diccionario_existe_ignora_diccionario_nulo()
{
	const char *clave = "Clave";

	bool existe_elemento = diccionario_existe(NULL, clave);

	pa2m_afirmar(
		!existe_elemento,
		"diccionario_existe() no intenta buscar en un diccionario nulo");
}

void diccionario_existe_ignora_diccionario_vacio()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";

	bool existe_elemento = diccionario_existe(NULL, clave);

	pa2m_afirmar(
		!existe_elemento,
		"diccionario_existe() no intenta buscar en un diccionario vacío");

	diccionario_destruir(diccionario);
}

void diccionario_existe_encuentra_elemento_presente()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	int valor = 0;

	diccionario_insertar(diccionario, clave, &valor, NULL);
	bool elemento_existe = diccionario_existe(diccionario, clave);

	pa2m_afirmar(
		elemento_existe,
		"diccionario_existe() reconoce una clave presente en el diccionario");

	diccionario_destruir(diccionario);
}

void diccionario_existe_reconoce_clave_con_valor_nulo()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *clave = "Clave";
	int *valor = NULL;

	diccionario_insertar(diccionario, clave, &valor, NULL);
	bool elemento_existe = diccionario_existe(diccionario, clave);

	pa2m_afirmar(
		elemento_existe,
		"diccionario_existe() reconoce una clave con valor nulo como existente");

	diccionario_destruir(diccionario);
}

void diccionario_con_cada_elemento_ignora_diccionario_nulo()
{
	int dato = 5;
	size_t cantidad_comparaciones = diccionario_con_cada_elemento(
		NULL, funcion_generica_comparador_enteros, &dato);

	pa2m_afirmar(
		cantidad_comparaciones == 0,
		"diccionario_con_cada_elemento() no intenta iterar sobre un diccionario nulo");
}

void diccionario_con_cada_elemento_ignora_funcion_nula()
{
	diccionario_t *diccionario = diccionario_crear(10);
	int dato = 5;
	size_t cantidad_comparaciones =
		diccionario_con_cada_elemento(diccionario, NULL, &dato);

	pa2m_afirmar(
		cantidad_comparaciones == 0,
		"diccionario_con_cada_elemento() no intenta iterar sobre un diccionario existente con una función nula");

	diccionario_destruir(diccionario);
}

void diccionario_con_cada_elemento_funciona_sobre_diccionario_vacio()
{
	diccionario_t *diccionario = diccionario_crear(10);
	int dato = 5;
	size_t cantidad_comparaciones = diccionario_con_cada_elemento(
		diccionario, funcion_generica_comparador_enteros, &dato);

	pa2m_afirmar(
		cantidad_comparaciones == 0,
		"diccionario_con_cada_elemento() recibe un diccionario vacío y no intenta iterar sobre él");

	diccionario_destruir(diccionario);
}

void diccionario_con_cada_elemento_devuelve_cantidad_correcta_de_elementos_afectados_iteracion_cortada()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *claves[] = { "A", "B", "C" };
	int valores[] = { 1, 2, 3 };
	int dato = 1;

	for (size_t i = 0; i < 3; i++) {
		diccionario_insertar(diccionario, claves[i], &valores[i], NULL);
	}
	size_t cantidad_elementos_afectados = diccionario_con_cada_elemento(
		diccionario, funcion_generica_comparador_enteros, &dato);

	pa2m_afirmar(
		cantidad_elementos_afectados == 2,
		"diccionario_con_cada_elemento() corta la iteración y devuelve la cantidad correcta de elementos a los cuales se le aplicó la función");
	diccionario_destruir(diccionario);
}

void diccionario_con_cada_elemento_devuelve_cantidad_correcta_de_elementos_afectados_iteracion_completa()
{
	diccionario_t *diccionario = diccionario_crear(10);
	const char *claves[] = { "A", "B", "C" };
	int valores[] = { 1, 2, 3 };
	int dato = 1;

	for (size_t i = 0; i < 3; i++) {
		diccionario_insertar(diccionario, claves[i], &valores[i], NULL);
	}
	size_t cantidad_elementos_afectados = diccionario_con_cada_elemento(
		diccionario, funcion_generica_reemplazar_todos, &dato);

	pa2m_afirmar(
		cantidad_elementos_afectados == 3,
		"diccionario_con_cada_elemento() completa la iteración y devuelve la cantidad correcta de elementos a los cuales se le aplicó la función");
	diccionario_destruir(diccionario);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de funcionalidades básicas del diccionario");
	diccionario_crear_crea_un_diccionario_con_capacidad_valida();
	diccionario_crear_crea_un_diccionario_con_capacidad_debajo_del_minimo();
	diccionario_crear_crea_un_diccionario_vacio();
	diccionario_cantidad_toma_diccionario_nulo_como_vacio();
	diccionario_cantidad_devuelve_0_con_diccionario_vacio();
	diccionario_cantidad_devuelve_valor_correcto();

	pa2m_nuevo_grupo("Pruebas de inserción");
	diccionario_insertar_devuelve_null_en_caso_de_error();
	diccionario_insertar_no_intenta_insertar_en_diccionario_nulo();
	diccionario_insertar_no_intenta_insertar_par_con_clave_nula();
	diccionario_insertar_devuelve_puntero_al_mismo_diccionario();
	diccionario_insertar_logra_insertar_y_el_elemento_esta_presente();
	diccionario_insertar_logra_insertar_un_valor_nulo();
	diccionario_insertar_logra_insertar_y_cambia_cantidad();
	diccionario_insertar_sobreescribe_valor_y_no_cambia_cantidad();
	diccionario_insertar_sobreescribe_valores();
	diccionario_insertar_modifica_puntero_correctamente_al_insertar();
	diccionario_insertar_devuelve_el_valor_anterior_correcto();
	diccionario_insertar_inserta_claves_sobre_la_capacidad_inicial();

	pa2m_nuevo_grupo("Pruebas de eliminación");
	diccionario_eliminar_devuelve_null_en_caso_de_error();
	diccionario_eliminar_no_intenta_eliminar_de_diccionario_nulo();
	diccionario_eliminar_no_intenta_eliminar_de_diccionario_vacio();
	diccionario_eliminar_no_intenta_eliminar_par_con_clave_nula();
	diccionario_eliminar_no_intenta_eliminar_elemento_no_presente();
	diccionario_eliminar_elimina_elemento_y_extrae_datos_correctamente();
	diccionario_eliminar_elimina_elemento_y_lo_remueve_del_diccionario();
	diccionario_eliminar_cambia_cantidad_de_elementos_correctamente();

	pa2m_nuevo_grupo("Pruebas de obtención y existencia");
	diccionario_obtener_ignora_diccionario_nulo();
	diccionario_obtener_ignora_diccionario_vacio();
	diccionario_obtener_encuentra_elemento_presente();
	diccionario_obtener_encuentra_elemento_y_extrae_dato();
	diccionario_existe_ignora_diccionario_nulo();
	diccionario_existe_ignora_diccionario_vacio();
	diccionario_existe_encuentra_elemento_presente();
	diccionario_existe_reconoce_clave_con_valor_nulo();

	pa2m_nuevo_grupo("Pruebas de iteración");
	diccionario_con_cada_elemento_ignora_diccionario_nulo();
	diccionario_con_cada_elemento_ignora_funcion_nula();
	diccionario_con_cada_elemento_funciona_sobre_diccionario_vacio();
	diccionario_con_cada_elemento_devuelve_cantidad_correcta_de_elementos_afectados_iteracion_cortada();
	diccionario_con_cada_elemento_devuelve_cantidad_correcta_de_elementos_afectados_iteracion_completa();

	return pa2m_mostrar_reporte();
}
