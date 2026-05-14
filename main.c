#include "src/diccionario.h"
#include "src/diccionario_constantes.h"
#include "src/tp1.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int reconocer_comando_o_instruccion(const char *comando, int cantidad_validos,
				    char *listado_validos[])
{
	int id = -1;
	int i = 0;
	bool es_valido = false;

	while (i < cantidad_validos && !es_valido) {
		if (strcmp(listado_validos[i], comando) == 0) {
			es_valido = true;
			id = i;
		}
		i++;
	}

	return id;
}

int controlar_argumentos_iniciales(int argc, const char *argv[])
{
	char *instrucciones_validas[CANT_INSTRUCCIONES_VALIDAS] = { "nombre",
								    "tipo" };
	char *tipos_validos[MAX_TIPOS] = { "ELEC", "FUEG", "PLAN", "AGUA",
					   "NORM", "FANT", "PSI",  "LUCH" };

	if (argc < CANT_MINIMA_ARGUMENTOS)
		return ERR_CONTROL;
	if (strcmp(argv[2], COMANDO_VALIDO) != 0) {
		printf(MSJ_ERR_COMANDO, argv[2]);
		return ERR_CONTROL;
	}

	int id_instruccion = reconocer_comando_o_instruccion(
		argv[3], CANT_INSTRUCCIONES_VALIDAS, instrucciones_validas);

	if (id_instruccion == -1) {
		printf(MSJ_ERR_INSTRUCCION, argv[3]);
		return ERR_CONTROL;
	}
	if (id_instruccion == 1 &&
	    reconocer_comando_o_instruccion(argv[4], MAX_TIPOS,
					    tipos_validos) == -1) {
		printf(MSJ_ERR_PARAMETRO, argv[4]);
		return ERR_CONTROL;
	}

	return SIN_ERRORES;
}

void imprimir_pokemon(struct pokemon *pokemon)
{
	char *nombres_completos_tipos[] = { "⚡Eléctrico",
					    "🔥Fuego",
					    "🌿Planta",
					    "💧Agua",
					    "⬜Normal",
					    "👻Fantasma",
					    "👁️‍🗨️Psíquico",
					    "✊Lucha" };

	printf(MSJ_DATOS, pokemon->nombre,
	       nombres_completos_tipos[pokemon->tipo], pokemon->ataque,
	       pokemon->defensa, pokemon->velocidad);
}

int ejecutar_comando_buscar_nombre(const char *argv[],
				   diccionario_t *diccionario)
{
	struct pokemon *pokemon_buscado =
		diccionario_obtener(diccionario, argv[4]);

	if (pokemon_buscado != NULL)
		imprimir_pokemon(pokemon_buscado);
	else
		printf(MSJ_AVISO_POKEMON_NO_PRESENTE);

	return SIN_ERRORES;
}

int identificar_id_tipo(const char *tipo)
{
	char tipos_validos[MAX_TIPOS][MAX_NOM_TIPO] = { "ELEC", "FUEG", "PLAN",
							"AGUA", "NORM", "FANT",
							"PSI",	"LUCH" };

	int i = 0;
	int id_tipo = -1;
	bool buscando = true;

	while (buscando && i < MAX_TIPOS) {
		if (strcmp(tipos_validos[i], tipo) == 0) {
			id_tipo = i;
			buscando = false;
		}
		i++;
	}

	return id_tipo;
}

bool mostrar_pokemon_por_tipo(struct diccionario_par *par_actual,
			      void *_tipo_buscado)
{
	struct pokemon *pokemon_actual = (struct pokemon *)par_actual->valor;
	enum tipo_pokemon *tipo_buscado = (enum tipo_pokemon *)_tipo_buscado;

	if (pokemon_actual->tipo == *tipo_buscado)
		imprimir_pokemon(pokemon_actual);
	return true;
}

int ejecutar_comando_buscar_tipo(const char *argv[], diccionario_t *diccionario)
{
	int tipo_buscado = identificar_id_tipo(argv[4]);

	size_t cantidad_de_pokemon_mostrados = diccionario_con_cada_elemento(
		diccionario, mostrar_pokemon_por_tipo, &tipo_buscado);

	if (cantidad_de_pokemon_mostrados == 0)
		printf(MSJ_AVISO_TIPO_NO_PRESENTE);

	return SIN_ERRORES;
}

int ejecutar_comando(const char *argv[], diccionario_t *diccionario)
{
	char *instrucciones_validas[CANT_INSTRUCCIONES_VALIDAS] = { "nombre",
								    "tipo" };
	int (*comandos[CANT_INSTRUCCIONES_VALIDAS])(const char **,
						    diccionario_t *) = {
		ejecutar_comando_buscar_nombre, ejecutar_comando_buscar_tipo
	};

	for (int i = 0; i < CANT_INSTRUCCIONES_VALIDAS; i++) {
		if (strcmp(argv[3], instrucciones_validas[i]) == 0)
			comandos[i](argv, diccionario);
	}

	printf(MSJ_EXITO);
	return SIN_ERRORES;
}

bool cargar_pokemon_en_diccionario(struct pokemon *pokemon, void *_diccionario)
{
	diccionario_t *diccionario = (diccionario_t *)_diccionario;

	return diccionario_insertar(diccionario, pokemon->nombre, pokemon,
				    NULL) == diccionario;
}

int rellenar_diccionario(tp1_t *tp1, diccionario_t *diccionario)
{
	size_t cantidad_pokemones_insertados = tp1_con_cada_pokemon(
		tp1, cargar_pokemon_en_diccionario, diccionario);

	if (cantidad_pokemones_insertados != tp1_cantidad(tp1))
		return ERR_RELLENAR_DICCIONARIO;
	return SIN_ERRORES;
}

int main(int argc, const char *argv[])
{
	printf(MSJ_BIENVENIDA);
	if (controlar_argumentos_iniciales(argc, argv) == ERR_CONTROL) {
		printf(MSJ_INSTRUCCIONES);
		return ERR_CONTROL;
	}

	tp1_t *tp1 = tp1_leer_archivo(argv[1]);
	if (tp1 == NULL) {
		printf(MSJ_ERR_LECTURA);
		return ERR_LECTURA;
	}
	if (tp1_cantidad(tp1) == 0) {
		printf(MSJ_AVISO_POKEDEX_VACIA);
		tp1_destruir(tp1);
		return SIN_ERRORES;
	}

	diccionario_t *diccionario = diccionario_crear(tp1_cantidad(tp1));
	if (diccionario == NULL) {
		printf(MSJ_ERR_DICCIONARIO);
		tp1_destruir(tp1);
		return ERR_DICCIONARIO;
	}
	if (rellenar_diccionario(tp1, diccionario) ==
	    ERR_RELLENAR_DICCIONARIO) {
		printf(MSJ_ERR_RELLENAR_DICCIONARIO);
		diccionario_destruir(diccionario);
		tp1_destruir(tp1);
		return ERR_RELLENAR_DICCIONARIO;
	}

	ejecutar_comando(argv, diccionario);

	diccionario_destruir(diccionario);
	tp1_destruir(tp1);
	return SIN_ERRORES;
}
