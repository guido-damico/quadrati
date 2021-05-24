/*
 * decomposizione.cpp
 *
 *  Created on: Mar 15, 2020
 *      Author: Guido
 */
#include "Decomposizione.h"

namespace quadrati {

    // Public methods

    Decomposizione::Decomposizione() {
        this->basicInit(0);
    }
    Decomposizione::Decomposizione(long obiettivo = 0) {
        this->basicInit(obiettivo);
    }

    Decomposizione::~Decomposizione() {
        // TODO Auto-generated destructor stub
    }

    long Decomposizione::getObiettivo() {
        return this->obiettivo;
    }
    void Decomposizione::setObiettivo(long obiettivo) {
        if (obiettivo < 0) {
            throw "L'obiettivo deve essere un intero positivo!";
        }
        this->obiettivo = obiettivo;

        return;
    }

    long* Decomposizione::getAddendi() {
        return this->addendi;
    }
    void Decomposizione::setAddendo(int index, long addendo) {
        this->addendi[index] = addendo;
        return;
    }
    void Decomposizione::setAllAddendi(long* addendi) {
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

    long Decomposizione::getResto() {
        return this->obiettivo - this->sommaQuadratiAddendi();
    }

    int Decomposizione::getLivello() {
        return this->livello;
    }
    void Decomposizione::setLivello(int livello) {
        this->livello = livello;
        return;
    }

    long Decomposizione::getIterazione() {
        return this->iterazione;
    }
    void Decomposizione::setIterazione(long iterazione) {
        this->iterazione = iterazione;
        return;
    }

    long Decomposizione::sommaQuadratiAddendi() {
        long* addendi = this->getAddendi();

        long somma = addendi[0] * addendi[0] +
                     addendi[1] * addendi[1] +
                     addendi[2] * addendi[2] +
                     addendi[3] * addendi[3];

        return somma;
    }

    void Decomposizione::outputCurrentStatus() {
    	spdlog::trace("Obiettivo  : {0}\n\t\t\t\tIterazione : {1}\n\t\t\t\tLivello    : {2}\n\t\t\t\tAddendi    :({3}, {4}, {5}, {6}), \n\t\t\t\tResto:     {7}\n\t\t\t\tCompleta    : {8}.",
    			this->getObiettivo(),
				this->getIterazione(),
				this->getLivello(),
				this->getAddendi()[0],
				this->getAddendi()[1],
				this->getAddendi()[2],
				this->getAddendi()[3],
				this->getResto(),
				this->getCompleta()
				);
        return;
    }

    // Private methods

    void Decomposizione::basicInit(long obiettivo) {
        addendi = new long[4]();
		this->iterazione = 0 ;
        this->completa = false;
        this->resto = -1;
        this->livello = 0;
        this->obiettivo = obiettivo;
    }

    bool Decomposizione::controllaInvarianti() {
    	bool decoValida = true;
        long* addendi = this->getAddendi();
        long resto = this->getResto();
        long obiettivo = this->getObiettivo();

        long check = addendi[0] * addendi[0] +
                     addendi[1] * addendi[1] +
                     addendi[2] * addendi[2] +
                     addendi[3] * addendi[3] +
                     resto -
                     obiettivo;

        if (check != 0) {
            spdlog::error("Violata l'iintegrittà della decomposizione: addendi incompatibili!");
            this->outputCurrentStatus();
            decoValida = false;
        }

        if (this->completa && resto != 0) {
        	spdlog::error("Violata l'iintegrittà della decomposizione: decomposizione completa ma resto !=0");
            this->outputCurrentStatus();
            decoValida = false;
        }

        return decoValida;
    }

} /* namespace quadrati */
