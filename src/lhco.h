/* Copyright (c) 2015, 2017, Chan Beom Park <cbpark@gmail.com> */

#ifndef SRC_LHCO_H_
#define SRC_LHCO_H_

#include <string>
#include "event.h"
#include "object.h"
#include "parser.h"
#include "particle.h"

namespace lhco {
std::string openingLine() {
    std::string line = "  #  ";
    line += "typ      eta    phi      pt    jmas  ntrk  btag   had/em";
    line += "  dum1  dum2";
    return line;
}

int numPhoton(const Event &ev);

int numPhoton(const Pt &pt, const Eta &eta, const Event &ev);

int numElectron(const Event &ev);

int numElectron(const Pt &pt, const Eta &eta, const Event &ev);

int numMuon(const Event &ev);

int numMuon(const Pt &pt, const Eta &eta, const Event &ev);

int numTau(const Event &ev);

int numTau(const Pt &pt, const Eta &eta, const Event &ev);

int numNormalJet(const Event &ev);

int numNormalJet(const Pt &pt, const Eta &eta, const Event &ev);

int numBjet(const Event &ev);

int numBjet(const Pt &pt, const Eta &eta, const Event &ev);

int numAllJet(const Event &ev);

int numAllJet(const Pt &pt, const Eta &eta, const Event &ev);

double missingET(const Event &ev);

double invariantMass(const Visibles &ps);
}  // namespace lhco

#endif  // SRC_LHCO_H_
