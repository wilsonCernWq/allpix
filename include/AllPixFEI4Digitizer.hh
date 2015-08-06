/**
 * Author:
 *    francesco.armando.di.bello@cern.ch
 *
 *  allpix Authors:
 *   John Idarraga <idarraga@cern.ch>
 *   Mathieu Benoit <Mathieu.Benoit@cern.ch>
 */

#ifndef AllPixFEI4Digitizer_h
#define AllPixFEI4Digitizer_h 1

// allpix Interface
#include "AllPixDigitizerInterface.hh"
// digits for this digitizer
#include "AllPixFEI4Digit.hh"
#include "G4PrimaryVertex.hh"

#include <map>
#include <vector>

using namespace std;

/**
 *  Digitizer AllPixFEI4 implementation
 */
class AllPixFEI4Digitizer : public  AllPixDigitizerInterface {

public:

  AllPixFEI4Digitizer(G4String, G4String, G4String);
  virtual ~AllPixFEI4Digitizer();

  void SetPrimaryVertex(G4PrimaryVertex * pv) {m_primaryVertex = pv;};
  void Digitize ();
  void SetDetectorDigitInputs(G4double){};

private:

  // digitInput typedef is defined in AllPixDigitizerInterface.hh
  digitInput m_digitIn;

  AllPixFEI4DigitsCollection * m_digitsCollection;
  vector<G4String> m_hitsColName;
  G4PrimaryVertex * m_primaryVertex; // information from EventAction

  // guess from Qi Wu
  int total_iter = 0;
  vector<G4double> X, Y;
  vector<G4double> X1, Y1;
};

#endif
