/*
 * decomposizione.cpp
 *
 *  Created on: Mar 15, 2020
 *      Author: gGuido
 */

#include "Decomposizione.h"

namespace quadrati {

    // Public methods

    Decomposizione::Decomposizione() {
        this->basicInit(0);
    }
    Decomposizione::Decomposizione(long int obiettivo = 0) {
        this->basicInit(obiettivo);
    }

    Decomposizione::~Decomposizione() {
        // TODO Auto-generated destructor stub
    }

    long int Decomposizione::getObiettivo() {
        return this->obiettivo;
    }
    void Decomposizione::setObiettivo(long int obiettivo) {
        if (obiettivo < 0) {
            throw "Target must be a non-negative integer!";
        }

        this->obiettivo = obiettivo;
        return;
    }


    long* Decomposizione::getAddendi() {
        return this->addendi;
    }
    void Decomposizione::setAddendi(long* addendi) {
        this->addendi = addendi;
        return;
    }

    bool Decomposizione::getCompleta() {
        return this->completa;
    }
    void Decomposizione::setCompleta(bool completa) {
        this->completa = completa;
        return;
    }

    long int Decomposizione::getResto() {
        return this->resto;
    }
    void Decomposizione::setResto(long int resto) {
        this->resto = resto;
        return;
    }

    int Decomposizione::getLivello() {
        return this->livello;
    }
    void Decomposizione::setLivello(int livello) {
        this->livello = livello;
        return;
    }

    long int Decomposizione::getIterazione() {
        return this->iterazione;
    }
    void Decomposizione::setIterazione(long int iterazione) {
        this->iterazione = iterazione;
        return;
    }

    // Private methods

    void Decomposizione::basicInit(long int obiettivo) {
        this->setAddendi(new long[4]);
        this->setIterazione(0);
        this->setCompleta(false);
        this->setResto(-1);
        this->setLivello(0);
        this->setObiettivo(obiettivo);
    }

} /* namespace quadrati */
