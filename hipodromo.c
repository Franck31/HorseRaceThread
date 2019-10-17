#include "funciones.h"
#include "definiciones.h"

int main(int argc, char *argv[])
{
	int cntcaballos;
	int id_cola_mensajes;
	int i;
	int Salida = 0;
	int count;
	char *token;
	char palabra[100];
	mensaje msg;
	int id_semaforo;
	int metros_al_disco;
	int recorrido;
	//no se me ocurrio como, pero asi lo hice andar
	int id_aux;

//inicializamos
  mcaballo *aux = NULL;
	id_semaforo = creo_semaforo(CANT_SEMAFORO);
	inicio_semaforo(id_semaforo, 0, 1);
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
	borrar_mensajes(id_cola_mensajes);

	//oparmetros mayor a 1
	if (argc>1)
		cntcaballos = atoi(argv[1]);

	printf("Cant. de caballos es :%d\n", cntcaballos);

	srand(time(NULL));
	//no se me ocurrio como, pero asi lo hice andar, mala mia
	id_aux = creo_id_memoria(sizeof(mcaballo)*cntcaballos, CLAVE_BASE);
	aux = (mcaballo*) creo_memoria(id_aux);

	metros_al_disco = rand()%(HASTA_METROS_CARRERA-DESDE_METROS_CARRERA+1)+DESDE_METROS_CARRERA;
	printf("La carrera a correr es de %d mts\n",metros_al_disco);

	sprintf(palabra, "%d", metros_al_disco);
	for(i=0;i<cntcaballos;i++)
	{
		enviar_mensaje(id_cola_mensajes , MSG_CABALLO+i, MSG_HIPODROMO, EVT_INICIO, palabra);
	}

	while(Salida == 0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_HIPODROMO, &msg);
		switch (msg.int_evento)
		{
			case EVT_METROS:
				recorrido = atoi(msg.char_mensaje);
				if (recorrido >= metros_al_disco)
				{
					sprintf(palabra, "%d", msg.int_rte-MSG_CABALLO+1);
			    	for(i=0;i<cntcaballos;i++)
			    	{
			    		enviar_mensaje(id_cola_mensajes , MSG_CABALLO+i, MSG_HIPODROMO, EVT_CRUZARON_EL_DISCO, palabra);
			    	}
			    	printf("\nEvt cruzaron  caballo %d\n",msg.int_rte-MSG_CABALLO+1);
			    	Salida = 1;
				}
				else
				{
					sprintf(palabra, "%s", "EVTSIGA");
					enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_HIPODROMO, EVT_SIGA, palabra);
				}

				printf("Caballo %d Mts. recorridos: %d\n",msg.int_rte-MSG_CABALLO+1,recorrido);
				break;

			default:
			//va por las duasd
				break;
		}
	};
  	shmdt ((char *)aux);
  	shmctl (id_aux, IPC_RMID, (struct shmid_ds *)NULL);
	return 0;
}
