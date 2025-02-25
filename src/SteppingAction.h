// -----------------------------------------------------------------------------
//  G4_QPIX | SteppingAction.H
//
//  Definition of detector geometry and materials.
//   * Author: Justo Martin-Albo
//   * Creation date: 14 Aug 2019
// -----------------------------------------------------------------------------

#ifndef STEPPING_ACTION_H
#define STEPPING_ACTION_H

#include <G4UserSteppingAction.hh>
#include "G4GenericMessenger.hh"

class SteppingAction: public G4UserSteppingAction
{
  public:
    SteppingAction();
    virtual ~SteppingAction();
    virtual void UserSteppingAction(const G4Step*);

private:
    G4GenericMessenger * msg_;
};

#endif
