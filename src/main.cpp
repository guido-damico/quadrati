/*
 * main.cpp
 *
 *  Created on: Mar 6, 2020
 *      Author: Guido
 */
#include <unistd.h>

#include "Quadrati.h"
#include "Decomposizione.h"

#define START_VAL 0
#define MAX_VAL 1000

void sleepNow(unsigned millis) {
    usleep(millis * 1000);
}

void stampaTesto(quadrati::Decomposizione& deco, long verifica) {
    const char* check = (verifica == 0 ? "OK" : "ERRORE!");
    cout << "Per " << deco.getObiettivo() << " ho: ("
         << deco.getAddendi()[0] << ", "
         << deco.getAddendi()[1] << ", "
         << deco.getAddendi()[2] << ", "
         << deco.getAddendi()[3] << ")"
         << " in " << deco.getIterazione() << " iterazioni."
         << " (" << check << ")\n";

}

void stampaCsv(quadrati::Decomposizione& deco, long verifica) {
    const char* check = (verifica == 0 ? "OK" : "ERRORE!");
    cout << deco.getObiettivo() << ","
         << deco.getAddendi()[0] << ", "
         << deco.getAddendi()[1] << ", "
         << deco.getAddendi()[2] << ", "
         << deco.getAddendi()[3] << ", "
         << deco.getIterazione() << ","
         << check << "\n";

}

int main()
{
    using quadrati::Quadrati;
    using quadrati::Decomposizione;

    cout << "Running main:\n";

    // Classe per il calcolo
    Quadrati quad;

    for (long i = START_VAL; i < MAX_VAL; i++) {
        Decomposizione deco;
        deco.setObiettivo(i);

        quad.addendi(deco);
	    // quad.updateProgress(i + 1, MAX_VAL);
	    long verifica = i - deco.getAddendi()[0] * deco.getAddendi()[0]
                          - deco.getAddendi()[1] * deco.getAddendi()[1]
                          - deco.getAddendi()[2] * deco.getAddendi()[2]
                          - deco.getAddendi()[3] * deco.getAddendi()[3];

	    // Stampa
	    stampaCsv(deco, verifica);
	}
    cout << "\n";

    return 0;
}
