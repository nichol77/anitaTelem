////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////// Simple Class to handle telemetered MonitorDataStruct_t      /////////
//////                                                             /////////
////// r.nichol@ucl.ac.uk --- July 2014                            /////////
////////////////////////////////////////////////////////////////////////////

#ifndef ANITAMONITORHANDLER_H
#define ANITAMONITORHANDLER_H

#include <map>
#include <string>

#include "simpleStructs.h"
#include "plotUtils.h"    


class AnitaMonitorHandler 
{   
public:
  AnitaMonitorHandler(std::string rawDir,int run);
    ~AnitaMonitorHandler();
    
    void addMonitor(MonitorStruct_t *monitorPtr);
    void addOtherMonitor(OtherMonitorStruct_t *monitorPtr);
    void loopMap();
    void loopOtherMap();


private:
    std::string fRawDir;
    int fRun;
    std::map<UInt_t, MonitorStruct_t> fMonitorMap;
    std::map<UInt_t, OtherMonitorStruct_t> fOtherMonitorMap;


};

#endif //ANITAMONITORHANDLER_H


