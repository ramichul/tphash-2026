#include "lista.h"

typedef struct nodo {
	void *contenido;
	struct nodo *siguiente_nodo;
} nodo_t;

struct lista {
	nodo_t *inicio;
	nodo_t *fin;
	size_t cantidad_nodos;
};

struct lista_iterador {
	nodo_t *actual;
};

void *lista_buscar_nodo(lista_t *lista, size_t posicion)
{
	if (lista == NULL || posicion >= lista_cantidad(lista))
		return NULL;
	if (posicion == lista_cantidad(lista) - 1)
		return lista->fin;

	nodo_t *actual = lista->inicio;
	for (size_t i = 0; i < posicion; i++) {
		actual = actual->siguiente_nodo;
	}
	return actual;
}

lista_t *lista_crear()
{
	lista_t *lista = calloc(1, sizeof(lista_t));
	if (lista == NULL)
		return NULL;

	return lista;
}

bool lista_vacia(lista_t *lista)
{
	if (lista == NULL || lista_cantidad(lista) == 0)
		return true;
	return false;
}

size_t lista_cantidad(lista_t *lista)
{
	if (lista == NULL)
		return 0;

	return lista->cantidad_nodos;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (lista == NULL)
		return NULL;

	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
	if (nuevo_nodo == NULL)
		return NULL;
	nuevo_nodo->contenido = elemento;
	nuevo_nodo->siguiente_nodo = NULL;

	if (lista_vacia(lista)) {
		lista->inicio = nuevo_nodo;
		lista->fin = nuevo_nodo;
	} else {
		lista->fin->siguiente_nodo = nuevo_nodo;
		lista->fin = nuevo_nodo;
	}

	lista->cantidad_nodos++;
	return lista;
}

lista_t *lista_insertar_posicion(lista_t *lista, size_t posicion,
				 void *elemento)
{
	if (lista == NULL)
		return NULL;
	if (posicion >= lista_cantidad(lista))
		return lista_insertar(lista, elemento);

	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
	if (nuevo_nodo == NULL)
		return NULL;
	nuevo_nodo->contenido = elemento;
	nuevo_nodo->siguiente_nodo = lista_buscar_nodo(lista, posicion);

	if (posicion == 0) {
		lista->inicio = nuevo_nodo;
	} else {
		nodo_t *nodo_anterior = lista_buscar_nodo(lista, posicion - 1);
		nodo_anterior->siguiente_nodo = nuevo_nodo;
	}

	lista->cantidad_nodos++;
	return lista;
}

void *lista_obtener(lista_t *lista)
{
	if (lista == NULL || lista_vacia(lista))
		return NULL;

	return lista->fin->contenido;
}

void *lista_obtener_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL || posicion >= lista_cantidad(lista))
		return NULL;
	if (posicion == lista_cantidad(lista) - 1)
		return lista_obtener(lista);

	nodo_t *nodo_actual = lista->inicio;
	for (size_t i = 0; i < posicion; i++) {
		nodo_actual = nodo_actual->siguiente_nodo;
	}
	return nodo_actual->contenido;
}

void *lista_eliminar(lista_t *lista)
{
	if (lista == NULL || lista_vacia(lista))
		return NULL;

	nodo_t *nodo_a_eliminar = lista->fin;
	nodo_t *nodo_anterior =
		lista_buscar_nodo(lista, lista_cantidad(lista) - 2);
	void *puntero_contenido = nodo_a_eliminar->contenido;

	lista->fin = nodo_anterior;
	if (lista->fin != NULL) {
		lista->fin->siguiente_nodo = NULL;
	}
	free(nodo_a_eliminar);
	lista->cantidad_nodos--;

	return puntero_contenido;
}

void *lista_eliminar_inicio(lista_t *lista)
{
	nodo_t *nodo_a_eliminar = lista->inicio;
	void *puntero_contenido = nodo_a_eliminar->contenido;

	lista->inicio = nodo_a_eliminar->siguiente_nodo;
	free(nodo_a_eliminar);
	if (lista_cantidad(lista) == 1)
		lista->fin = NULL;
	lista->cantidad_nodos--;

	return puntero_contenido;
}

void *lista_eliminar_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL || posicion >= lista_cantidad(lista))
		return NULL;

	if (posicion == 0)
		return lista_eliminar_inicio(lista);
	else if (posicion == lista_cantidad(lista) - 1)
		return lista_eliminar(lista);

	nodo_t *nodo_a_eliminar = lista_buscar_nodo(lista, posicion);
	nodo_t *nodo_anterior = lista_buscar_nodo(lista, posicion - 1);
	void *puntero_contenido = nodo_a_eliminar->contenido;

	nodo_anterior->siguiente_nodo = nodo_a_eliminar->siguiente_nodo;
	free(nodo_a_eliminar);
	lista->cantidad_nodos--;

	return puntero_contenido;
}

bool lista_buscar(lista_t *lista, void *elemento,
		  int (*comparador)(const void *, const void *),
		  size_t *posicion)
{
	if (lista == NULL || comparador == NULL || lista_vacia(lista))
		return false;

	nodo_t *nodo_actual = lista->inicio;
	size_t posicion_actual = 0;
	bool elemento_encontrado = false;
	while (nodo_actual != NULL && !elemento_encontrado) {
		if (comparador(nodo_actual->contenido, elemento) == 0)
			elemento_encontrado = true;
		else
			posicion_actual++;

		nodo_actual = nodo_actual->siguiente_nodo;
	}

	if (posicion != NULL && elemento_encontrado)
		*posicion = posicion_actual;
	return elemento_encontrado;
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*f)(void *, void *),
			       void *extra)
{
	size_t i = 0;

	if (lista == NULL || f == NULL || lista_vacia(lista))
		return i;

	bool iterando = true;
	nodo_t *nodo_actual = lista->inicio;
	while (i < lista_cantidad(lista) && iterando) {
		if (!f(nodo_actual->contenido, extra))
			iterando = false;
		i++;
		nodo_actual = nodo_actual->siguiente_nodo;
	}

	return i;
}

void lista_destruir_todo(lista_t *lista, void (*destructor)(void *))
{
	if (lista == NULL)
		return;

	nodo_t *nodo_actual = lista->inicio;
	nodo_t *puntero_auxiliar = nodo_actual;

	for (size_t i = 0; i < lista_cantidad(lista); i++) {
		if (destructor != NULL)
			destructor(nodo_actual->contenido);
		puntero_auxiliar = nodo_actual->siguiente_nodo;
		free(nodo_actual);
		nodo_actual = puntero_auxiliar;
	}

	free(lista);
}

void lista_destruir(lista_t *lista)
{
	lista_destruir_todo(lista, NULL);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (lista == NULL)
		return NULL;

	lista_iterador_t *iterador = calloc(1, sizeof(lista_iterador_t));
	if (iterador == NULL)
		return NULL;

	iterador->actual = lista->inicio;

	return iterador;
}

bool lista_iterador_hay_mas_elementos(lista_iterador_t *it)
{
	if (it == NULL)
		return false;

	return it->actual != NULL;
}

void lista_iterador_avanzar(lista_iterador_t *it)
{
	if (it == NULL)
		return;
	if (it->actual == NULL)
		return;

	it->actual = it->actual->siguiente_nodo;
}

void *lista_iterador_actual(lista_iterador_t *it)
{
	if (it == NULL)
		return NULL;
	if (it->actual == NULL)
		return NULL;

	return it->actual->contenido;
}

void lista_iterador_destruir(lista_iterador_t *it)
{
	if (it == NULL)
		return;

	free(it);
}
