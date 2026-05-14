#ifndef __DICCIONARIO_CONSTANTES_H__
#define __DICCIONARIO_CONSTANTES_H__

#define OCURRIO_REEMPLAZO 1
#define NO_HAY_DUPLICADO 0
#define SIN_ERRORES 0
#define ERROR_MEMORIA -1
#define ERR_CONTROL -2
#define ERR_LECTURA -3
#define ERR_COMANDO -4
#define ERR_DICCIONARIO -5
#define ERR_RELLENAR_DICCIONARIO -6

#define SEMILLA_HASH 5381
#define FACTOR_AMPLIFICACION_HASH 33
#define CAPACIDAD_MINIMA 3
#define LIMITE_FACTOR_DE_CARGA 0.75
#define FACTOR_ESCALA_CAPACIDAD 2

#define COMANDO_VALIDO "buscar"
#define CANT_INSTRUCCIONES_VALIDAS 2
#define CANT_MINIMA_ARGUMENTOS 5
#define MAX_TIPOS 8
#define MAX_NOM_TIPO 5

#define MSJ_BIENVENIDA \
	"\033[38;5;222;1m🔴⚪ ¡Bienvenido al diccionario de Pokémon! ⚪🔴\n\n\033[0m"
#define MSJ_INSTRUCCIONES \
	"El modo de uso es \033[38;5;223m./diccionario [archivo] buscar nombre/tipo [parámetro a buscar]\033[0m.\n\nVuelva a correr el programa por terminal, asegurándose de utilizar la estructura indicada.\n\n"
#define MSJ_ERR_COMANDO \
	"\033[38;5;202;1mERROR\033[0m: Nombre inválido de comando: \033[38;5;223m%s\033[0m. "
#define MSJ_ERR_INSTRUCCION \
	"\033[38;5;202;1mERROR\033[0m: Nombre inválido de instrucción: ./diccionario [archivo] buscar \033[38;5;223m%s\033[0m. Por favor, consulte las instrucciones ejecutando el programa por si solo y vuelva a intentar.\n\n"
#define MSJ_ERR_LECTURA \
	"\033[38;5;202;1mERROR\033[0m: Ocurrió un error al leer el archivo. Por favor, vuelva a intentar.\n"
#define MSJ_AVISO_POKEDEX_VACIA \
	"\033[38;5;222;1mAVISO\033[0m: La Pokédex cargada desde el archivo está vacía. Se terminará la ejecución del programa."
#define MSJ_ERR_DICCIONARIO \
	"\033[38;5;202;1mERROR\033[0m: Ocurrió un error al crear el diccionario. Por favor, vuelva a intentar.\n"
#define MSJ_EXITO \
	"\033[38;5;222;1m🔴⚪ Comando realizado con éxito. ¡Hasta luego! ⚪🔴\n\n\033[0m"
#define MSJ_ERR_RELLENAR_DICCIONARIO \
	"\033[38;5;202;1mERROR\033[0m: Ocurrió un error al rellenar el diccionario. Por favor, vuelva a intentar.\n"
#define MSJ_DATOS \
	"\033[38;5;223;1mDATOS DEL POKÉMON: \n\033[0m\033[38;5;223mNOMBRE:\033[0m %s\n\033[38;5;223mTIPO:\033[0m %s\n\033[38;5;223mATAQUE:\033[0m %i\n\033[38;5;223mDEFENSA:\033[0m %i\n\033[38;5;223mVELOCIDAD:\033[0m %i\n\n"
#define MSJ_AVISO_POKEMON_NO_PRESENTE \
	"\033[38;5;222;1mAVISO\033[0m: El Pokémon buscado no está presente en el diccionario.\n\n"
#define MSJ_ERR_PARAMETRO \
	"\033[38;5;202;1mERROR\033[0m: Parámetro inválido para la busqueda por tipo: ./diccionario [archivo] buscar tipo \033[38;5;223m%s\033[0m. Los tipos válidos son: ELEC, FUEG, PLAN, AGUA, NORM, FANT, PSI, LUCH. Por favor vuelva a intentar.\n\n"
#define MSJ_AVISO_TIPO_NO_PRESENTE \
	"\033[38;5;222;1mAVISO\033[0m: No hay Pokémon del tipo buscado en el diccionario.\n\n"

#endif /* __DICCIONARIO_CONSTANTES_H__ */