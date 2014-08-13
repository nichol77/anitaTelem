////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////// Simple Class to handle telemetered SurfHkDataStruct_t      /////////
//////                                                             /////////
////// r.nichol@ucl.ac.uk --- July 2014                            /////////
////////////////////////////////////////////////////////////////////////////

#ifndef ANITASURFHKHANDLER_H
#define ANITASURFHKHANDLER_H

#include <map>
#include <string>


#include "simpleStructs.h"
#include "plotUtils.h"    


class AnitaSurfHkHandler 
{   
public:
  AnitaSurfHkHandler(std::string rawDir,int run);
    ~AnitaSurfHkHandler();
    
    void addSurfHk(FullSurfHkStruct_t *hkPtr);
    void loopMap();


private:
    std::string fRawDir;
    int fRun;
    std::map<UInt_t,FullSurfHkStruct_t> fSurfHkMap;


};

#endif //ANITASURFHKHANDLER_H


