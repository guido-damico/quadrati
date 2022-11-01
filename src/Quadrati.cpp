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

        // Check max iterazioni
        if (deco.getIterazione() > MAX_ITERAZIONI){
            spdlog::critical("Troppe iterazioni per {0}: {1} oltre il limite, rinuncio!", deco.getObiettivo(), deco.getIterazione());
            deco.setCompleta(true);
            deco.outputCurrentStatus();

            return deco;
        }

        // Nuova iterazione
        deco.setIterazione(deco.getIterazione() + 1);
        spdlog::debug("Inizio iterazione {0}, livello {1}, obiettivo {2}.", deco.getIterazione(), deco.getLivello(), deco.getObiettivo());
        //deco.outputCurrentStatus();

        // Il livello a cui opero
        int livelloAttuale = deco.getLivello();

        // Calcola il nuovo valore di questo livello e il corrispondente nuovo resto
        long nuovoAddendo = stimaNuovoAddendo(deco);
        deco.setAddendo(livelloAttuale, nuovoAddendo);

        long nuovoResto = deco.getResto();
        spdlog::debug("Nuovo addendo: {0}, nuovo resto: {1}.", deco.getAddendi()[livelloAttuale], deco.getResto());

        // Calcola il limite minimo per il prossimo addendo
        long limite = (long) sqrt(deco.getResto());
        if (limite > deco.getLimiti()[livelloAttuale]) {
            deco.setLimite(deco.getLivello(), limite);
            spdlog::trace("Limite per Livello {0}, Iterazione {1}, nuovo addendo {2}, resto {3}: {4}",
                    deco.getLivello(),
                    deco.getIterazione(),
                    nuovoAddendo,
                    deco.getResto(),
                    limite);
        }

        // Controlla dove siamo arrivati
        if (nuovoResto == 0) {
            // finito!
            deco.setCompleta(true);
            spdlog::info("Completata decomposizione di {0}.", deco.getObiettivo());

            // Azzera i livelli rimanenti
            for (int i = deco.getLivello() + 1; i < 4; i++) {
                deco.setAddendo(i, 0);
            }
            spdlog::debug("Azzerato i termini rimasti:");
            deco.outputCurrentStatus();

        } else {
            // Resto non nullo: altro giro
            switch (deco.getLivello()) {
                case 3:
                    // ultimo livello e decomposizione ancor invalida:
                    // azzera questo livello
                    deco.setAddendo(livelloAttuale, 0);

                    // riprova usando un nuovo addendo al livello superiore
                    deco.setLivello(livelloAttuale - 1);
                    deco.outputCurrentStatus();
                    break;

                case 2:
                case 1:
                case 0:
                    /*
                     * Partendo dal valore attuale e scendendo fino a 1
                     *     ricorri,
                     *          se non completa, cala di uno
                     *          se non puoi calare di uno metti a zero e ritorna
                     */
                    for (long valoreAttuale = nuovoAddendo; (!deco.getCompleta()) && valoreAttuale > 0 && valoreAttuale >= limite; valoreAttuale--) {
                        // Memorizza il valore più recente al livello attuale
                        deco.getAddendi()[livelloAttuale] = valoreAttuale;

                        // Proviamo a calcolare gli altri addendi dal livello più giù di uno
                        deco.setLivello(livelloAttuale + 1);

                        // Ricorsivamente calcola gli altri addendi
                        deco.outputCurrentStatus();
                        deco = addendi(deco);
                    }

                    // se il ciclo precendete non ha risolto: azzera il corrente valore e riitorna ad un livello più sù
                    if (!deco.getCompleta()) {
                        deco.getAddendi()[livelloAttuale] = 0;

                        // su di un livello
                        deco.setLivello(livelloAttuale - 1);
                    }
                    //deco.outputCurrentStatus();
                    break;

                default:
                    spdlog::critical("ERRORE: Livello invalido: {0}.", deco.getLivello());
                    throw 10;
            }
        }
        return deco;
    }

    // Private methods

    long Quadrati::stimaNuovoAddendo(Decomposizione& deco){
        return ((long) sqrt(deco.getResto()));
    }

    void Quadrati::azzeraAddendiDalLivello(Decomposizione& deco, int livello) {
        for (int i = livello + 1; i <= 3; i++) {
            deco.getAddendi()[i] = 0;
        }
        return;
    }

} /* namespace quadrati */
