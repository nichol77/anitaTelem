////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////// Simple Class to handle telemetered HkDataStruct_t      /////////
//////                                                             /////////
////// r.nichol@ucl.ac.uk --- July 2014                            /////////
////////////////////////////////////////////////////////////////////////////

#ifndef ANITAHKHANDLER_H
#define ANITAHKHANDLER_H

#include <map>
#include <string>


#include "simpleStructs.h"
#include "plotUtils.h"    


class AnitaHkHandler 
{   
public:
    AnitaHkHandler(std::string rawDir,int run);
    ~AnitaHkHandler();
    
    void addHk(HkDataStruct_t *hkPtr);
    void addSSHk(SSHkDataStruct_t *hkPtr);
    void loopMap();
    void loopSSMap();


private:
    std::string fRawDir;
    int fRun;
    std::map<UInt_t, HkDataStruct_t> fHkMap;
    std::map<UInt_t, SSHkDataStruct_t> fSSHkMap;


};

#endif //ANITAHKHANDLER_H


