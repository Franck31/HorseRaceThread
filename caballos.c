#include "funciones.h"
#include "definiciones.h"
#include <pthread.h>

void* ThreadCaballo (void* parametro)
{
	int id_cola_mensajes;
	int ncaballo;
	int ccaballos;
	int caballocampeon;
	int salida = 0;
	char *token;

	mensaje msg;
	char palabra[100];
	int pista;
	int recorrido = 0;

	int metros;
	int inte;

	tcaballo *datos_thread = (tcaballo*) parametro;

	id_cola_mensajes = datos_thread->id_cola_mensajes;
	ncaballo = datos_thread->ncaballo;
	ccaballos = datos_thread->ccaballos;
	caballocampeon = datos_thread->caballocampeon;

	while(salida == 0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_CABALLO+ncaballo, &msg);
		switch (msg.int_evento)
		{
			case EVT_INICIO:
			//eventoInicio
				pista = atoi(msg.char_mensaje);
				printf("EVTINI\n");
				printf("metros a correr es de %d\n",pista);
				metros = rand()%(HASTA_METROS-DESDE_METROS+1)+DESDE_METROS;
				recorrido += metros;
				printf("caballo %d va %d mts\n",ncaballo+1,recorrido);
				sprintf(palabra, "%d", recorrido);
				enviar_mensaje(id_cola_mensajes , MSG_HIPODROMO, MSG_CABALLO+ncaballo, EVT_METROS, palabra);
				break;
			case EVT_SIGA:
			//enventosiga
				inte = rand()%(HASTA_INTERVALO+1-DESDE_INTERVALO)+DESDE_INTERVALO;
				usleep(inte*1000);
				metros = rand()%(HASTA_METROS-DESDE_METROS+1)+DESDE_METROS;
				recorrido += metros;
				printf("EVT-SIGA: caballo %d va recotirnfo %d mts\n",ncaballo+1,recorrido);
				sprintf(palabra, "%d", recorrido);
				enviar_mensaje(id_cola_mensajes , MSG_HIPODROMO, MSG_CABALLO+ncaballo, EVT_METROS, palabra);
				break;
			case EVT_CRUZARON_EL_DISCO:
			printf("EVTFIN\n");
			//evento final ganador-> envia al main
				caballocampeon = atoi(msg.char_mensaje);
				datos_thread->caballocampeon = caballocampeon;
				salida = 1;
				break;
			default:
			//lopongoporlasdudas
				break;
		}
	};

	pthread_exit ((void *)"Listo");
}

int main(int argc, char *argv[])
{
	//main
	int ccaballos;
	int id_cola_mensajes;
	int id_semaforo;
	int id_aux;	int i;
	int j;

	tcaballo* datos_thread;

	srand(time(NULL));


	if (argc>1)
		ccaballos = atoi(argv[1]);

	printf("cant caballos :%d\n", ccaballos);
	mcaballo *aux = NULL;
	id_semaforo = creo_semaforo(CANT_SEMAFORO);
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
	id_aux = creo_id_memoria(sizeof(mcaballo)*ccaballos, CLAVE_BASE);
	aux = (mcaballo*) creo_memoria(id_aux);

	for (i=0;i<ccaballos;i++)
	{
		espera_semaforo(id_semaforo, SEMAFORO0);
		aux[i].ncaballo = i;
		levanta_semaforo(id_semaforo, SEMAFORO0);
	}

	pthread_t* idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*ccaballos);
	pthread_attr_t 	atributos;
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);

	datos_thread = (tcaballo*) malloc(sizeof(tcaballo)*ccaballos);

	for(j=0; j<ccaballos; j++)
	{
		datos_thread[j].ncaballo = j;
		datos_thread[j].id_cola_mensajes = id_cola_mensajes;
		datos_thread[j].id_aux = id_aux;
		datos_thread[j].id_semaforo = id_semaforo;
		datos_thread[j].ccaballos = ccaballos;
		datos_thread[j].caballocampeon = 0;
		pthread_create (&idHilo[j], &atributos, ThreadCaballo, &datos_thread[j]);
	}

	for(i=0; i<ccaballos; i++)
	{
		pthread_join (idHilo[i], NULL);
		printf("obtuve -> caballo %d ***** Caballo campeon: %d\n",i+1,datos_thread[i].caballocampeon);
	}

	free(idHilo);
	free(datos_thread);


	return 0;
}
