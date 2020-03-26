/*
 * Quadrati.cpp
 *
 *  Created on: Mar 6, 2020
 *      Author: Guido
 */
#include <stdio.h>
#include <cmath>

#include "Quadrati.h"
#include "Decomposizione.h"

namespace quadrati {

    // Public methods

    Quadrati::Quadrati() {
    }

    Quadrati::~Quadrati() {
    }

    Decomposizione Quadrati::addendi(Decomposizione& deco) {
        using quadrati::Decomposizione;

        // Nuova iterazione
        deco.setIterazione(deco.getIterazione() + 1);

        // Il livello a cui opero
        int livelloAttuale = deco.getLivello();

        // Calcola il nuovo valore di questo livello e il corrispondente nuovo resto
        deco.setResto(deco.getObiettivo() - sommaQuadratiAddendi(deco));

        long nuovoAddendo = ((long) (sqrt(deco.getResto())));
        deco.getAddendi()[livelloAttuale] = nuovoAddendo;

        long nuovoResto = deco.getObiettivo() - sommaQuadratiAddendi(deco);
        deco.setResto(nuovoResto);

        if (nuovoResto == 0) {
            // finito!
            deco.setCompleta(true);
        }

        // outputDebug(deco, nuovoAddendo, nuovoResto);

        switch (deco.getLivello()) {
            case 3:
                if (!deco.getCompleta()) {
                    // decomposizione invalida: azzera questo livello
                    deco.getAddendi()[livelloAttuale] = 0;

                    // sù di un livello
                    deco.setLivello(livelloAttuale - 1);
                }
                break;

            case 2:
            case 1:
            case 0:
                /*
                 * Partendo da currentValue e scendendo fino a 1
                 *     ricorri,
                 *          se non completa, cala di uno
                 *          se non puoi calare di uno metti a zero e ritorna
                 */
                for (long valoreAttuale = nuovoAddendo; (!deco.getCompleta()) && valoreAttuale > 0; valoreAttuale--) {
                    // usa il più recente valore
                    deco.getAddendi()[livelloAttuale] = valoreAttuale;

                    // giù di un livello
                    deco.setLivello(livelloAttuale + 1);

                    // ricorsione un livello più giù
                    deco = addendi(deco);
                }

                // se il ciclo precendete non ha risolto: azzera il corrente valore e riitorna ad un livello più sù
                if (!deco.getCompleta()) {
                    deco.getAddendi()[livelloAttuale] = 0;

                    // sù di un livello
                    deco.setLivello(livelloAttuale - 1);
                }
                break;

            default:
                cout << "\nERRORE: Livello invalido: " << deco.getLivello() << "\n";
                throw 10;
        }

        return deco;
    }

    /*
     * Prints out a string to report the current computation progress.
     */
    void Quadrati::updateProgress(long done, long tot) {
        float perc = ((float) done) * 100.0 / tot;
        printf("\r%9ld / %ld (%3.1f%%)", done, tot, perc);
        fflush(stdout);
    }

    // Private methods

    int Quadrati::sommaQuadratiAddendi(Decomposizione deco) {
        return (
                deco.getAddendi()[0] * deco.getAddendi()[0] +
                deco.getAddendi()[1] * deco.getAddendi()[1] +
                deco.getAddendi()[2] * deco.getAddendi()[2] +
                deco.getAddendi()[3] * deco.getAddendi()[3]
               );
    }

    void Quadrati::azzeraAddendiDalLivello(Decomposizione& deco, int livello) {
        for (int i = livello + 1; i <= 3; i++) {
            deco.getAddendi()[i] = 0;
        }
        return;
    }

    void Quadrati::outputDebug(Decomposizione deco, int nuovoAddendo, int nuovoResto) {
        cout << "\n\tObiettivo  : " << deco.getObiettivo() << "\n"
             << "\tIterazione : " << deco.getIterazione() << "\n"
             << "\t\t livello : " << deco.getLivello() << "\n"
             << "\t\t addendi : (" << deco.getAddendi()[0] << ", "<< deco.getAddendi()[1] << ", "<< deco.getAddendi()[2] << ", "<< deco.getAddendi()[3] << ")\n"
             << "\t\t resto   : " << deco.getResto() << "\n"
             << "\t\t nuovoAd : " << nuovoAddendo << "\n"
             << "\t\t nuovoRe : " << nuovoResto << "\n";
        return;
    }

} /* namespace quadrati */
