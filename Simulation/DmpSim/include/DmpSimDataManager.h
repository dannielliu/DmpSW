/*
 *  $Id: DmpSimDataManager.h, 2014-03-07 00:00:48 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#ifndef DmpSimDataManager_H
#define DmpSimDataManager_H

#include "DmpVDataManager.h"

class TTree;
class G4Run;
class G4Event;
class DmpEvtSimPrimaryParticle;
class DmpEventRaw;

class DmpSimDataManager : public DmpVDataManager{
/*
 *  DmpSimDataManager
 *
 *  
 */
public:
  static DmpSimDataManager* GetInstance();
  void BookBranch();            // invoked from BeginOfRunAction()
  void FillEvent();             // invoked from EndOfEnventAction()
  void SetOutDataName();        // invoked from EndOfRunAction()
  void SaveOutput();            // invoked from EndOfRunAction()

private:
  DmpSimDataManager();
  ~DmpSimDataManager();

public:
  DmpEvtSimPrimaryParticle* GetPrimaryParticle() const {return fPrimaryParticle;}
  DmpEventRaw*  GetRawEvent() const     {return fEvtRaw;}
  void UpdatePrimaryParticleInformation(const G4Event*);    // invoked from GeneratePrimaries()
  void UpdateEventHeader(const G4Event*); // invoked from BeginOfEventAction()
  void Digitize();                  // invoked from EndOfEventAction(), before FillEvent()

private:
  TTree     *fOutDataTree;

private:
  DmpEvtSimPrimaryParticle  *fPrimaryParticle;
  DmpEventRaw   *fEvtRaw;
};

#endif

