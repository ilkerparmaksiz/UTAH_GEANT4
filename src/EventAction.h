// -----------------------------------------------------------------------------
//  G4_QPIX | EventAction.h
//
//
//   * Author: Everybody is an author!
//   * Creation date: 15 Aug 2019
// -----------------------------------------------------------------------------

#ifndef EVENT_ACTION_H
#define EVENT_ACTION_H

#include <G4UserEventAction.hh>
#include "G4String.hh"

class G4GenericMessenger;
class EventAction: public G4UserEventAction
{
public:
  EventAction();
  virtual ~EventAction();
  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);

private:
    G4GenericMessenger * msg_;
    bool runRTDCode_;
};

#endif
