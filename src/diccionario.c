#include "diccionario.h"
#include "diccionario_constantes.h"
#include "lista.h"
#include "string.h"
#include "strings.h"
#include <ctype.h>

struct diccionario {
	lista_t **contenedores;
	size_t cantidad_elementos;
	size_t capacidad_actual;
};

struct paquete_rehash {
	lista_t **nuevos_contenedores;
	size_t nueva_capacidad;
};

struct paquete_edicion {
	struct diccionario_par par_de_reemplazo;
	void *valor_anterior;
	bool ocurrio_reemplazo;
};

size_t obtener_hash(size_t capacidad, const char *clave)
{
	size_t hash = SEMILLA_HASH;
	char caracter_actual = clave[0];
	int i = 1;

	while ((caracter_actual != '\0')) {
		hash = hash * FACTOR_AMPLIFICACION_HASH +
		       (size_t)tolower(caracter_actual);
		caracter_actual = clave[i];
		i++;
	}

	return hash % capacidad;
}

lista_t **crear_contenedores(size_t capacidad)
{
	lista_t **contenedores = calloc(capacidad, sizeof(lista_t *));
	if (contenedores == NULL)
		return NULL;

	size_t i = 0;
	bool flag_fallo_memoria = false;
	while (i < capacidad && !flag_fallo_memoria) {
		contenedores[i] = lista_crear();
		if (contenedores[i] == NULL)
			flag_fallo_memoria = true;

		i++;
	}
	if (flag_fallo_memoria) {
		for (int j = 0; j < i; j++) {
			lista_destruir(contenedores[j]);
		}
		free(contenedores);
		return NULL;
	}

	return contenedores;
}

struct diccionario_par *crear_par_nuevo(const char *clave, void *valor)
{
	struct diccionario_par *par_nuevo =
		calloc(1, sizeof(struct diccionario_par));
	if (par_nuevo == NULL)
		return NULL;
	par_nuevo->clave = calloc(strlen(clave) + 1, sizeof(char));
	if (par_nuevo->clave == NULL) {
		free(par_nuevo);
		return NULL;
	}
	strcpy((char *)par_nuevo->clave, clave);
	par_nuevo->valor = valor;

	return par_nuevo;
}

diccionario_t *diccionario_crear(size_t capacidad_inicial)
{
	size_t capacidad = capacidad_inicial;
	if (capacidad_inicial < CAPACIDAD_MINIMA)
		capacidad = CAPACIDAD_MINIMA;

	diccionario_t *nuevo_diccionario = calloc(1, sizeof(diccionario_t));
	if (nuevo_diccionario == NULL)
		return NULL;
	nuevo_diccionario->contenedores = crear_contenedores(capacidad);
	if (nuevo_diccionario->contenedores == NULL) {
		free(nuevo_diccionario);
		return NULL;
	}
	nuevo_diccionario->capacidad_actual = capacidad;

	return nuevo_diccionario;
}

int buscar_clave(const void *_elemento_actual_lista, const void *_clave_buscada)
{
	struct diccionario_par *elemento_actual_lista =
		(struct diccionario_par *)_elemento_actual_lista;
	const char *clave_buscada = (const char *)_clave_buscada;

	return strcmp(elemento_actual_lista->clave, clave_buscada);
}

bool buscar_y_editar_valor(void *_par_actual, void *_paquete_edicion)
{
	struct diccionario_par *par_actual =
		(struct diccionario_par *)_par_actual;
	struct paquete_edicion *paquete_edicion =
		(struct paquete_edicion *)_paquete_edicion;

	if (strcmp(par_actual->clave,
		   paquete_edicion->par_de_reemplazo.clave) == 0) {
		paquete_edicion->valor_anterior = (void *)par_actual->valor;
		par_actual->valor = paquete_edicion->par_de_reemplazo.valor;
		paquete_edicion->ocurrio_reemplazo = true;
		return false;
	}

	return true;
}

int reemplazar_valor_de_clave_duplicada(diccionario_t *d, size_t hash,
					struct diccionario_par *par_nuevo,
					void **valor_anterior)
{
	struct paquete_edicion paquete_edicion;
	paquete_edicion.par_de_reemplazo.clave = par_nuevo->clave;
	paquete_edicion.par_de_reemplazo.valor = par_nuevo->valor;
	paquete_edicion.ocurrio_reemplazo = false;

	lista_con_cada_elemento(d->contenedores[hash], buscar_y_editar_valor,
				&paquete_edicion);

	if (paquete_edicion.ocurrio_reemplazo) {
		if (valor_anterior != NULL)
			*valor_anterior = paquete_edicion.valor_anterior;
		return OCURRIO_REEMPLAZO;
	}
	if (valor_anterior != NULL)
		*valor_anterior = NULL;

	return NO_HAY_DUPLICADO;
}

bool rehashear_elemento(struct diccionario_par *par_actual,
			void *_paquete_rehash)
{
	struct paquete_rehash *paquete_rehash =
		(struct paquete_rehash *)_paquete_rehash;

	size_t rehash = obtener_hash(paquete_rehash->nueva_capacidad,
				     par_actual->clave);

	if (lista_insertar(paquete_rehash->nuevos_contenedores[rehash],
			   par_actual) == NULL)
		return false;

	return true;
}

int realizar_rehash(diccionario_t *d)
{
	size_t nueva_capacidad = d->capacidad_actual * FACTOR_ESCALA_CAPACIDAD;

	lista_t **nuevos_contenedores = crear_contenedores(nueva_capacidad);
	if (nuevos_contenedores == NULL)
		return ERROR_MEMORIA;

	struct paquete_rehash paquete_rehash;
	paquete_rehash.nuevos_contenedores = nuevos_contenedores;
	paquete_rehash.nueva_capacidad = nueva_capacidad;

	size_t cantidad_elementos_rehasheados = diccionario_con_cada_elemento(
		d, rehashear_elemento, &paquete_rehash);
	if (cantidad_elementos_rehasheados != d->cantidad_elementos) {
		for (int j = 0; j < nueva_capacidad; j++) {
			lista_destruir(nuevos_contenedores[j]);
		}
		free(nuevos_contenedores);
		return ERROR_MEMORIA;
	}

	for (int j = 0; j < d->capacidad_actual; j++) {
		lista_destruir(d->contenedores[j]);
	}

	free(d->contenedores);
	d->contenedores = nuevos_contenedores;
	d->capacidad_actual = nueva_capacidad;
	return SIN_ERRORES;
}

diccionario_t *diccionario_insertar(diccionario_t *d, const char *clave,
				    void *valor, void **valor_anterior)
{
	if (d == NULL || clave == NULL)
		return NULL;

	float factor_de_carga =
		(float)(d->cantidad_elementos + 1) / (float)d->capacidad_actual;
	if (factor_de_carga >= LIMITE_FACTOR_DE_CARGA) {
		if (realizar_rehash(d) == ERROR_MEMORIA)
			return NULL;
	}

	struct diccionario_par *par_nuevo = crear_par_nuevo(clave, valor);
	if (par_nuevo == NULL)
		return NULL;

	size_t hash = obtener_hash(d->capacidad_actual, clave);

	if (reemplazar_valor_de_clave_duplicada(
		    d, hash, par_nuevo, valor_anterior) == NO_HAY_DUPLICADO) {
		if (lista_insertar(d->contenedores[hash], par_nuevo) == NULL) {
			free((char *)par_nuevo->clave);
			free(par_nuevo);
			return NULL;
		}
		d->cantidad_elementos++;
	} else {
		free((char *)par_nuevo->clave);
		free(par_nuevo);
	}

	return d;
}

void *diccionario_eliminar(diccionario_t *d, const char *clave)
{
	if (d == NULL || clave == NULL || diccionario_cantidad(d) == 0)
		return NULL;

	size_t hash = obtener_hash(d->capacidad_actual, clave);

	size_t posicion_par = 0;
	if (lista_buscar(d->contenedores[hash], (void *)clave, buscar_clave,
			 &posicion_par)) {
		struct diccionario_par *par_eliminado;

		par_eliminado = lista_eliminar_posicion(d->contenedores[hash],
							posicion_par);

		void *puntero_valor_par_eliminado =
			(void *)par_eliminado->valor;

		free((void *)par_eliminado->clave);
		free(par_eliminado);
		d->cantidad_elementos--;

		return puntero_valor_par_eliminado;
	} else {
		return NULL;
	}
}

void *diccionario_obtener(diccionario_t *d, const char *clave)
{
	if (d == NULL || clave == NULL || diccionario_cantidad(d) == 0)
		return NULL;

	size_t hash = obtener_hash(d->capacidad_actual, clave);

	size_t posicion_par = 0;
	bool clave_buscada_esta_presente =
		lista_buscar(d->contenedores[hash], (void *)clave, buscar_clave,
			     &posicion_par);
	struct diccionario_par *par_buscado =
		lista_obtener_posicion(d->contenedores[hash], posicion_par);

	if (par_buscado != NULL && clave_buscada_esta_presente)
		return (void *)par_buscado->valor;
	return NULL;
}

bool diccionario_existe(diccionario_t *d, const char *clave)
{
	if (d == NULL || clave == NULL || diccionario_cantidad(d) == 0)
		return false;

	size_t hash = obtener_hash(d->capacidad_actual, clave);

	return lista_buscar(d->contenedores[hash], (void *)clave, buscar_clave,
			    NULL);
}

size_t diccionario_cantidad(diccionario_t *d)
{
	if (d == NULL)
		return 0;

	return d->cantidad_elementos;
}

size_t diccionario_con_cada_elemento(diccionario_t *d,
				     bool (*f)(struct diccionario_par *,
					       void *),
				     void *extra)
{
	size_t i = 0;

	if (d == NULL || f == NULL || diccionario_cantidad(d) == 0)
		return i;

	bool iterando = true;
	size_t j = 0;
	while (iterando && j < d->capacidad_actual) {
		lista_iterador_t *iterador =
			lista_iterador_crear(d->contenedores[j]);
		while (lista_iterador_hay_mas_elementos(iterador) && iterando) {
			struct diccionario_par *par_actual =
				lista_iterador_actual(iterador);
			if (!f(par_actual, extra))
				iterando = false;
			i++;
			lista_iterador_avanzar(iterador);
		}
		lista_iterador_destruir(iterador);
		j++;
	}

	return i;
}

void destruir_par(struct diccionario_par *par, void (*destructor)(void *))
{
	free((void *)par->clave);
	if (destructor != NULL)
		destructor((void *)par->valor);
	free(par);
}

void diccionario_destruir_todo(diccionario_t *d, void (*destructor)(void *))
{
	if (d == NULL)
		return;

	for (size_t i = 0; i < d->capacidad_actual; i++) {
		size_t cantidad_contenedor_actual =
			lista_cantidad(d->contenedores[i]);
		for (size_t j = 0; j < cantidad_contenedor_actual; j++) {
			struct diccionario_par *eliminado =
				lista_eliminar(d->contenedores[i]);
			destruir_par(eliminado, destructor);
		}
		lista_destruir(d->contenedores[i]);
	}
	free(d->contenedores);
	free(d);
}

void diccionario_destruir(diccionario_t *d)
{
	diccionario_destruir_todo(d, NULL);
}