#ifndef _DEFINICIONES_H
#define _DEFINICIONES_H

#define LARGO_NOMBRE 100

#define DESDE_METROS_CARRERA 800
#define HASTA_METROS_CARRERA 1000

#define DESDE_METROS 10
#define HASTA_METROS 50

#define DESDE_INTERVALO 100
#define HASTA_INTERVALO 200

#define CANT_SEMAFORO 1

typedef enum
{
	MSG_NADIE,
	MSG_HIPODROMO,
	MSG_CABALLO,
}Destinos;

typedef enum
{
	EVT_NINGUNO,
	EVT_INICIO,
	EVT_METROS,
	EVT_SIGA,
	EVT_CRUZARON_EL_DISCO
}Eventos;

typedef struct tipo_thread_postor tcaballo;
struct tipo_thread_postor
{
	int ncaballo;
	int id_cola_mensajes;
	int id_aux;
	int id_semaforo;
	int ccaballos;
	int caballocampeon;
};

//parasaberquuiengabno
typedef struct tpcaballo mcaballo;
struct tpcaballo
{
	int ncaballo;
};


#endif
