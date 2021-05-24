/*
 * main.cpp
 *
 *  Created on: Mar 6, 2020
 *      Author: Guido
 */
#include <unistd.h>
#include <cstdlib>

#include "Quadrati.h"
#include "Decomposizione.h"
#include "spdlog/spdlog.h"

#define DEFAULT_START_VAL 1
#define DEFAULT_MAX_VAL 10

void sleepNow(unsigned millis) {
    usleep(millis * 1000);
}

/*
 * Inizializza il logging
 */
void initLogger() {
	spdlog::set_level(spdlog::level::trace);
	// spdlog::set_pattern("[%H:%M:%S.%e] [%l] %v");
}

/*
 * Stampa la situazione attuale della decomposiione.
 */
void stampaTesto(quadrati::Decomposizione& deco, long verifica) {
    if (verifica == 0) {
		spdlog::info("*** OK: Per {0} ho: ({1}, {2}, {3}, {4}) in {5} iterazioni.",
				deco.getObiettivo(),
				deco.getAddendi()[0],
				deco.getAddendi()[1],
				deco.getAddendi()[2],
				deco.getAddendi()[3],
				deco.getIterazione());

    } else {
		spdlog::error("Per {0} ho: ({1}, {2}, {3}, {4}) in {5} iterazioni.",
				deco.getObiettivo(),
				deco.getAddendi()[0],
				deco.getAddendi()[1],
				deco.getAddendi()[2],
				deco.getAddendi()[3],
				deco.getIterazione());
    }
}

string stampaCsv(quadrati::Decomposizione& deco, long verifica) {
    char out[80];

    const char* check = (verifica == 0 ? "OK" : "ERRORE!");
    sprintf(out, "%ld, %ld, %ld, %ld, %ld, %ld, %s\n",
            deco.getObiettivo(),
            deco.getAddendi()[0],
            deco.getAddendi()[1],
            deco.getAddendi()[2],
            deco.getAddendi()[3],
            deco.getIterazione(),
            check
            );

    return out;
}

/*
 * Stampa un messaggio di progresso
 */
void updateProgress(long done, long tot) {
    float perc = ((float) done) * 100.0 / tot;
    printf("\r%9ld / %ld (%3.1f%%) \n", done, tot, perc);
    fflush(stdout);
    //sleepNow(1000);
}

/*
 * Main
 */
int main(int argc, char **argv)
{
    using quadrati::Quadrati;
    using quadrati::Decomposizione;

    long valoreIniziale = DEFAULT_START_VAL;
    long valoreFinale = DEFAULT_MAX_VAL;

    initLogger();

    // Controlla i parametri in ingresso
    if (argc > 3) {
    	cerr << "Uso: quadrati [[valore_iniziale] valore_finale]\n\t"
    		 << "Con valore_iniziale intero positivo e minore di valore_finale";
    	exit(-99);

    } else if (argc == 2) {
    	valoreIniziale = 0;
    	valoreFinale = atol(argv[1]);

    } else if (argc == 3) {
    	valoreIniziale = atol(argv[1]);
    	valoreFinale = atol(argv[2]);
    }
    if (valoreIniziale > valoreFinale) {
    	spdlog::error("Il valore iniziale ({0}) non può essere maggiore del valore finale ({1})!", valoreIniziale, valoreFinale);
    	exit(-99);
    }

    // Classe per il calcolo
    Quadrati quad = Quadrati();

    // Inizio
    spdlog::info("Quadrati per l'intervallo [{0}, {1}]", valoreIniziale, valoreFinale);

    for (long i = valoreIniziale; i <= valoreFinale; i++) {
    	// Crea decomposizione con obiettivo il valore di i
    	Decomposizione deco = quadrati::Decomposizione(i);

        deco = quad.addendi(deco);
        spdlog::info("Deco completata per {0} in {1} iterazioni.", deco.getObiettivo(), deco.getIterazione());

	    // updateProgress(i + 1, MAX_VAL);
	    long verifica = i - deco.sommaQuadratiAddendi();

	    // Verifica
        spdlog::info("Verifica:");
        stampaTesto(deco, verifica);
        cout << stampaCsv(deco, verifica);
	}

    return 0;
}
