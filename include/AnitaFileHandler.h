////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////// Simple Class to unzip and write telemetered files           /////////
//////                                                             /////////
////// rjn@hep.ucl.ac.uk --- September 2006                        /////////
////////////////////////////////////////////////////////////////////////////

#ifndef ANITAFILEHANDLER_H
#define ANITAFILEHANDLER_H


#include <string>

#include "simpleStructs.h"

class AnitaFileHandler 
{   
public:
  AnitaFileHandler(std::string rawDir,std::string awareDir);
    ~AnitaFileHandler() {;}
    
    void processFile(ZippedFile_t *zfPtr,int run);
    
private:
    void getOutputName(char *outputFilename,char *linkName,ZippedFile_t *zfPtr,int useSegment,int fRun);
    int getAwareName(char *awareName,ZippedFile_t *zfPtr);
    std::string fAwareDir;
    std::string fRawDir;

};

#endif //ANITAFILEHANDLER_H


