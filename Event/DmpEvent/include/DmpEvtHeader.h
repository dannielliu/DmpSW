/*
 *  $Id: DmpEvtHeader.h, 2014-03-20 19:42:44 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpEvtHeader_H
#define DmpEvtHeader_H

#include "TObject.h"

#include "DmpDetectorID.h"
#include "DmpRunMode.h"

class DmpEvtHeader : public TObject{
/*
 * DmpEvtHeader
 *
 * Anywhere could use this singleton
 *
*/
public:
  DmpEvtHeader();
  ~DmpEvtHeader();

  void  SetTime(const short&,const short&);
  void  PrintTime()const;       // only Rdc use it
  void  CountThisEvent()        {++fEventID;}
  long  GetEventID() const      {return fEventID;}
  void  SetParticlePdgCode(const int &i)    {fPdgCode = i;}
  int   GetParticlePdgCode() const {return fPdgCode;}
  void  GenerateTriggerStatus();
  short GetTriggerStatus() const {return fTrgStatus;}
  void  SetTrigger(const DmpDetector::DmpEDetectorID &id, const short &v) {fTriggers[id] = v;}
  short GetTrigger(const DmpDetector::DmpEDetectorID &id)   {return fTriggers[id];}
  void  SetRunMode(const DmpDetector::DmpEDetectorID &id, const short &m) {fRunMode[id] = (DmpDetector::DmpERunMode)m;}
  DmpDetector::DmpERunMode GetRunMode(const DmpDetector::DmpEDetectorID &id) const {return fRunMode[id];}
  void  Initialize() {fEventID = -1;}   // prepare for the next data file

private:
  long      fSec;           // second
  short     fMillisec;      // millisecond
  long      fEventID;       // valid event count
  int       fPdgCode;       // particle pdg code
  short     fTrgStatus;     // trigger status
    /*
     * all match
     *      0
     * one subDet not match the others (>0)
     *      subDetID*1000 + |trigger_right - trigger_wrong|
     * many subDet are not match, recored their ID only (<0)
     *      0-(sbuDetID_1*100 + subDetID_2*10 + subDetID_3)
     *
     */
  DmpDetector::DmpERunMode fRunMode[DmpDetector::gSubDetNo];  // run modes of 4 subDet

private:    // variables below will not save into root file
  short     fTime[8];       //! not save
  /*
   *    8 bytes from satellite
   *    fTime[0~5] = second
   *    fTime[6~7] = millisecond
   *
   */
  short     fTriggers[DmpDetector::gSubDetNo];      //! trigger of 4 subDet and trigger of satellite

  ClassDef(DmpEvtHeader,1)
};

#endif

