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

int NumPhoton(const Event& ev);

int NumPhoton(const Pt& pt, const Eta& eta, const Event& ev);

int NumElectron(const Event& ev);

int NumElectron(const Pt& pt, const Eta& eta, const Event& ev);

int NumMuon(const Event& ev);

int NumMuon(const Pt& pt, const Eta& eta, const Event& ev);

int NumTau(const Event& ev);

int NumTau(const Pt& pt, const Eta& eta, const Event& ev);

int NumNormalJet(const Event& ev);

int NumNormalJet(const Pt& pt, const Eta& eta, const Event& ev);

int NumBjet(const Event& ev);

int NumBjet(const Pt& pt, const Eta& eta, const Event& ev);

int NumAllJet(const Event& ev);

int NumAllJet(const Pt& pt, const Eta& eta, const Event& ev);

double MissingET(const Event& ev);

double InvariantMass(const Visibles& ps);
}  // namespace lhco

#endif  // SRC_LHCO_H_
