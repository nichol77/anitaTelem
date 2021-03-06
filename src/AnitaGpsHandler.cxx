////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////// Simple Class to handle telemetered AnitaEventHk_t       /////////
//////                                                             /////////
////// r.nichol@ucl.ac.uk --- July 2014                            /////////
////////////////////////////////////////////////////////////////////////////

#include "AnitaGpsHandler.h"

#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "RawHk.h"
#include "simpleStructs.h"
#include "AwareRunDatabase.h"

#define HACK_FOR_ROOT

#define C3PO_AVG 20

#define EVENTS_PER_FILE 100
#define EVENT_FILES_PER_DIR 100
#define HK_PER_FILE 1000

AnitaGpsHandler::AnitaGpsHandler(std::string rawDir)
  :fRawDir(rawDir)
{


}

AnitaGpsHandler::~AnitaGpsHandler()
{


}
   
  
void AnitaGpsHandler::addG12Pos(GpsG12PosStruct_t *gpsPtr, int run)
{
  std::map<UInt_t,std::map<UInt_t, GpsG12PosStruct_t> >::iterator it=fG12PosMap.find(run);
  if(it!=fG12PosMap.end()) {
    it->second.insert(std::pair<UInt_t,GpsG12PosStruct_t>(gpsPtr->unixTime,*gpsPtr));
  }
  else {
    std::map<UInt_t, GpsG12PosStruct_t> runMap;
    runMap.insert(std::pair<UInt_t,GpsG12PosStruct_t>(gpsPtr->unixTime,*gpsPtr));
    fG12PosMap.insert(std::pair<UInt_t,std::map<UInt_t, GpsG12PosStruct_t> >(run,runMap));
  }
   
}

void AnitaGpsHandler::addG12Sat(GpsG12SatStruct_t *gpsPtr, int run)
{
  std::map<UInt_t,std::map<UInt_t, GpsG12SatStruct_t> >::iterator it=fG12SatMap.find(run);
  if(it!=fG12SatMap.end()) {
    it->second.insert(std::pair<UInt_t,GpsG12SatStruct_t>(gpsPtr->unixTime,*gpsPtr));
  }
  else {
    std::map<UInt_t, GpsG12SatStruct_t> runMap;
    runMap.insert(std::pair<UInt_t,GpsG12SatStruct_t>(gpsPtr->unixTime,*gpsPtr));
    fG12SatMap.insert(std::pair<UInt_t,std::map<UInt_t, GpsG12SatStruct_t> >(run,runMap));
  }
   
}

void AnitaGpsHandler::addGpsGga(GpsGgaStruct_t *gpsPtr, int run)
{
  if(whichGps(gpsPtr->gHdr.code)<0 || whichGps(gpsPtr->gHdr.code)>2) return;
  std::map<UInt_t,std::map<UInt_t, GpsGgaStruct_t> >::iterator it=fGpsGgaMap[whichGps(gpsPtr->gHdr.code)].find(run);
  if(it!=fGpsGgaMap[whichGps(gpsPtr->gHdr.code)].end()) {
    it->second.insert(std::pair<UInt_t,GpsGgaStruct_t>(gpsPtr->unixTime,*gpsPtr));
  }
  else {
    std::map<UInt_t, GpsGgaStruct_t> runMap;
    runMap.insert(std::pair<UInt_t,GpsGgaStruct_t>(gpsPtr->unixTime,*gpsPtr));
    fGpsGgaMap[whichGps(gpsPtr->gHdr.code)].insert(std::pair<UInt_t,std::map<UInt_t, GpsGgaStruct_t> >(run,runMap));
  }
   
}

void AnitaGpsHandler::addAdu5Pat(GpsAdu5PatStruct_t *gpsPtr, int run)
{
  if(whichGps(gpsPtr->gHdr.code)<0 || whichGps(gpsPtr->gHdr.code)>1) return;
  std::map<UInt_t,std::map<UInt_t, GpsAdu5PatStruct_t> >::iterator it=fAdu5PatMap[whichGps(gpsPtr->gHdr.code)].find(run);
  if(it!=fAdu5PatMap[whichGps(gpsPtr->gHdr.code)].end()) {
    it->second.insert(std::pair<UInt_t,GpsAdu5PatStruct_t>(gpsPtr->unixTime,*gpsPtr));
  }
  else {
    std::map<UInt_t, GpsAdu5PatStruct_t> runMap;
    runMap.insert(std::pair<UInt_t,GpsAdu5PatStruct_t>(gpsPtr->unixTime,*gpsPtr));
    fAdu5PatMap[whichGps(gpsPtr->gHdr.code)].insert(std::pair<UInt_t,std::map<UInt_t, GpsAdu5PatStruct_t> >(run,runMap));
  }
   
}


void AnitaGpsHandler::addAdu5Sat(GpsAdu5SatStruct_t *gpsPtr, int run)
{
  if(whichGps(gpsPtr->gHdr.code)<0 || whichGps(gpsPtr->gHdr.code)>1) return;
  std::map<UInt_t,std::map<UInt_t, GpsAdu5SatStruct_t> >::iterator it=fAdu5SatMap[whichGps(gpsPtr->gHdr.code)].find(run);
  if(it!=fAdu5SatMap[whichGps(gpsPtr->gHdr.code)].end()) {
    it->second.insert(std::pair<UInt_t,GpsAdu5SatStruct_t>(gpsPtr->unixTime,*gpsPtr));
  }
  else {
    std::map<UInt_t, GpsAdu5SatStruct_t> runMap;
    runMap.insert(std::pair<UInt_t,GpsAdu5SatStruct_t>(gpsPtr->unixTime,*gpsPtr));
    fAdu5SatMap[whichGps(gpsPtr->gHdr.code)].insert(std::pair<UInt_t,std::map<UInt_t, GpsAdu5SatStruct_t> >(run,runMap));
  }
   
}

void AnitaGpsHandler::addAdu5Vtg(GpsAdu5VtgStruct_t *gpsPtr, int run)
{
  if(whichGps(gpsPtr->gHdr.code)<0 || whichGps(gpsPtr->gHdr.code)>1) return;
  //  std::cerr << run << "\t" << gpsPtr->unixTime << "\t" << whichGps(gpsPtr->gHdr.code) << "\t" << fAdu5VtgMap[whichGps(gpsPtr->gHdr.code)].size() << "\n";
  std::map<UInt_t,std::map<UInt_t, GpsAdu5VtgStruct_t> >::iterator it=fAdu5VtgMap[whichGps(gpsPtr->gHdr.code)].find(run);
  //  std::cerr << "Done find run\n";
  if(it!=fAdu5VtgMap[whichGps(gpsPtr->gHdr.code)].end()) {
    //    std::cerr << "Found map trying to insert\n";
    it->second.insert(std::pair<UInt_t,GpsAdu5VtgStruct_t>(gpsPtr->unixTime,*gpsPtr));
  }
  else {
    //    std::cerr << "No map have to make one\n";
    std::map<UInt_t, GpsAdu5VtgStruct_t> runMap;
    //    std::cerr << "Inserting into run map\n";
    runMap.insert(std::pair<UInt_t,GpsAdu5VtgStruct_t>(gpsPtr->unixTime,*gpsPtr));
    //    std::cerr << "Inserting into map of maps\n";
    fAdu5VtgMap[whichGps(gpsPtr->gHdr.code)].insert(std::pair<UInt_t,std::map<UInt_t, GpsAdu5VtgStruct_t> >(run,runMap));
  }
   
}




void AnitaGpsHandler::loopG12PosMap() 
{
  char fileName[FILENAME_MAX];

  std::map<UInt_t,std::map<UInt_t, GpsG12PosStruct_t> >::iterator runIt;
  for(runIt=fG12PosMap.begin();runIt!=fG12PosMap.end();runIt++) {
    int fRun=runIt->first;

    
    int fileCount=0;
    std::map<UInt_t,GpsG12PosStruct_t>::iterator it;
    FILE *outFile=NULL;
    for(it=runIt->second.begin();it!=runIt->second.end();it++) {
      GpsG12PosStruct_t *gpsPtr=&(it->second);
      //    std::cout << gpsPtr->unixTime << "\t" << gpsPtr->unixTime << "\t" << 100*(gpsPtr->unixTime/100) << "\n";    
      
      //    processHk(gpsPtr);
      
      if(outFile==NULL) {
      //      std::cout << "Here\n";
      //Create a file
	if(outFile) fclose(outFile);
	outFile=NULL;
	
	sprintf(fileName,"%s/run%d/house/gps/g12/pos/sub_%d/sub_%d/",fRawDir.c_str(),fRun,gpsPtr->unixTime,gpsPtr->unixTime);       
	gSystem->mkdir(fileName,kTRUE);
	sprintf(fileName,"%s/run%d/house/gps/last",fRawDir.c_str(),fRun);
	AwareRunDatabase::touchFile(fileName);
	sprintf(fileName,"%s/run%d/house/gps/g12/pos/sub_%d/sub_%d/pos_%d.dat.gz",fRawDir.c_str(),fRun,gpsPtr->unixTime,gpsPtr->unixTime,gpsPtr->unixTime);
	std::cout << fileName << "\n";
	outFile=fopen(fileName,"ab");
	if(!outFile ) {
	printf("Couldn't open: %s\n",fileName);
	return;
	}
      }
      fwrite(gpsPtr,sizeof(GpsG12PosStruct_t),1,outFile);
      fileCount++;
      if(fileCount>=HK_PER_FILE) {
	fileCount=0;
	fclose(outFile);
	outFile=NULL;
      }
    }
    
    if(outFile) fclose(outFile);
    outFile=NULL;
  }

}



void AnitaGpsHandler::loopG12SatMap() 
{
  char fileName[FILENAME_MAX];

  std::map<UInt_t,std::map<UInt_t, GpsG12SatStruct_t> >::iterator runIt;
  for(runIt=fG12SatMap.begin();runIt!=fG12SatMap.end();runIt++) {
    int fRun=runIt->first;

    int fileCount=0;
    std::map<UInt_t,GpsG12SatStruct_t>::iterator it;
    FILE *outFile=NULL;
    for(it=runIt->second.begin();it!=runIt->second.end();it++) {
      GpsG12SatStruct_t *gpsPtr=&(it->second);
      //    std::cout << gpsPtr->unixTime << "\t" << gpsPtr->unixTime << "\t" << 100*(gpsPtr->unixTime/100) << "\n";    
      
      //    processHk(gpsPtr);
      
      if(outFile==NULL) {
	//      std::cout << "Here\n";
	//Create a file
	if(outFile) fclose(outFile);
	outFile=NULL;
	
	sprintf(fileName,"%s/run%d/house/gps/g12/sat/sub_%d/sub_%d/",fRawDir.c_str(),fRun,gpsPtr->unixTime,gpsPtr->unixTime);       
	gSystem->mkdir(fileName,kTRUE);
	sprintf(fileName,"%s/run%d/house/gps/last",fRawDir.c_str(),fRun);
	AwareRunDatabase::touchFile(fileName);
	sprintf(fileName,"%s/run%d/house/gps/g12/sat/sub_%d/sub_%d/sat_%d.dat.gz",fRawDir.c_str(),fRun,gpsPtr->unixTime,gpsPtr->unixTime,gpsPtr->unixTime);
	std::cout << fileName << "\n";
	outFile=fopen(fileName,"ab");
	if(!outFile ) {
	  printf("Couldn't open: %s\n",fileName);
	  return;
	}
      }
      fwrite(gpsPtr,sizeof(GpsG12SatStruct_t),1,outFile);
      fileCount++;
      if(fileCount>=HK_PER_FILE) {
	fileCount=0;
	fclose(outFile);
	outFile=NULL;
      }
    }
    
    if(outFile) fclose(outFile);
    outFile=NULL;
  }
}



void AnitaGpsHandler::loopGpsGgaMaps() 
{
  char fileName[FILENAME_MAX];

  for(int gpsId=0;gpsId<3;gpsId++) {

    std::map<UInt_t,std::map<UInt_t, GpsGgaStruct_t> >::iterator runIt;
    for(runIt=fGpsGgaMap[gpsId].begin();runIt!=fGpsGgaMap[gpsId].end();runIt++) {
      int fRun=runIt->first;    
      
      
      int fileCount=0;
      std::map<UInt_t,GpsGgaStruct_t>::iterator it;
      FILE *outFile=NULL;
      for(it=runIt->second.begin();it!=runIt->second.end();it++) {
	GpsGgaStruct_t *gpsPtr=&(it->second);
      //    std::cout << gpsPtr->unixTime << "\t" << gpsPtr->unixTime << "\t" << 100*(gpsPtr->unixTime/100) << "\n";    
      
      //    processHk(gpsPtr);
      
      if(outFile==NULL) {
	//      std::cout << "Here\n";
	//Create a file
	if(outFile) fclose(outFile);
	outFile=NULL;
	
	sprintf(fileName,"%s/run%d/house/gps/%s/gga/sub_%d/sub_%d/",fRawDir.c_str(),fRun,getGpsName(gpsId),gpsPtr->unixTime,gpsPtr->unixTime);       
	gSystem->mkdir(fileName,kTRUE);
	sprintf(fileName,"%s/run%d/house/last",fRawDir.c_str(),fRun);
	AwareRunDatabase::touchFile(fileName);
	sprintf(fileName,"%s/run%d/house/gps/%s/gga/sub_%d/sub_%d/gga_%d.dat.gz",fRawDir.c_str(),fRun,getGpsName(gpsId),gpsPtr->unixTime,gpsPtr->unixTime,gpsPtr->unixTime);
	std::cout << fileName << "\n";
	outFile=fopen(fileName,"ab");
	if(!outFile ) {
	  printf("Couldn't open: %s\n",fileName);
	  return;
      }
      }
      fwrite(gpsPtr,sizeof(GpsGgaStruct_t),1,outFile);
      fileCount++;
      if(fileCount>=HK_PER_FILE) {
	fileCount=0;
	fclose(outFile);
	outFile=NULL;
      }
    }
    
    if(outFile) fclose(outFile);
    outFile=NULL;
    }
  }
}



void AnitaGpsHandler::loopAdu5PatMaps() 
{
  char fileName[FILENAME_MAX];

  for(int gpsId=0;gpsId<2;gpsId++) {

    std::map<UInt_t,std::map<UInt_t, GpsAdu5PatStruct_t> >::iterator runIt;
    for(runIt=fAdu5PatMap[gpsId].begin();runIt!=fAdu5PatMap[gpsId].end();runIt++) {
      int fRun=runIt->first;    

    
      int fileCount=0;
    std::map<UInt_t,GpsAdu5PatStruct_t>::iterator it;
    FILE *outFile=NULL;
    for(it=runIt->second.begin();it!=runIt->second.end();it++) {
      GpsAdu5PatStruct_t *gpsPtr=&(it->second);
      //    std::cout << gpsPtr->unixTime << "\t" << gpsPtr->unixTime << "\t" << 100*(gpsPtr->unixTime/100) << "\n";    
      
      //    processHk(gpsPtr);
      
      if(outFile==NULL) {
	//      std::cout << "Here\n";
	//Create a file
	if(outFile) fclose(outFile);
	outFile=NULL;
	
	sprintf(fileName,"%s/run%d/house/gps/%s/pat/sub_%d/sub_%d/",fRawDir.c_str(),fRun,getGpsName(gpsId),gpsPtr->unixTime,gpsPtr->unixTime);       
	gSystem->mkdir(fileName,kTRUE);
	sprintf(fileName,"%s/run%d/house/last",fRawDir.c_str(),fRun);
	AwareRunDatabase::touchFile(fileName);
	sprintf(fileName,"%s/run%d/house/gps/%s/pat/sub_%d/sub_%d/pat_%d.dat.gz",fRawDir.c_str(),fRun,getGpsName(gpsId),gpsPtr->unixTime,gpsPtr->unixTime,gpsPtr->unixTime);
	std::cout << fileName << "\n";
	outFile=fopen(fileName,"ab");
	if(!outFile ) {
	  printf("Couldn't open: %s\n",fileName);
	  return;
      }
      }
      fwrite(gpsPtr,sizeof(GpsAdu5PatStruct_t),1,outFile);
      fileCount++;
      if(fileCount>=HK_PER_FILE) {
	fileCount=0;
	fclose(outFile);
	outFile=NULL;
      }
    }
    
    if(outFile) fclose(outFile);
    outFile=NULL;
  }
  }
}


void AnitaGpsHandler::loopAdu5SatMaps() 
{
  char fileName[FILENAME_MAX];

  for(int gpsId=0;gpsId<2;gpsId++) {
    
    std::map<UInt_t,std::map<UInt_t, GpsAdu5SatStruct_t> >::iterator runIt;
    for(runIt=fAdu5SatMap[gpsId].begin();runIt!=fAdu5SatMap[gpsId].end();runIt++) {
      int fRun=runIt->first;    

    int fileCount=0;
    std::map<UInt_t,GpsAdu5SatStruct_t>::iterator it;
    FILE *outFile=NULL;
    for(it=runIt->second.begin();it!=runIt->second.end();it++) {
      GpsAdu5SatStruct_t *gpsPtr=&(it->second);
      //    std::cout << gpsPtr->unixTime << "\t" << gpsPtr->unixTime << "\t" << 100*(gpsPtr->unixTime/100) << "\n";    
      
      //    processHk(gpsPtr);
      
      if(outFile==NULL) {
	//      std::cout << "Here\n";
	//Create a file
	if(outFile) fclose(outFile);
	outFile=NULL;
	
	sprintf(fileName,"%s/run%d/house/gps/%s/sat/sub_%d/sub_%d/",fRawDir.c_str(),fRun,getGpsName(gpsId),gpsPtr->unixTime,gpsPtr->unixTime);       
	gSystem->mkdir(fileName,kTRUE);
	sprintf(fileName,"%s/run%d/house/last",fRawDir.c_str(),fRun);
	AwareRunDatabase::touchFile(fileName);
	sprintf(fileName,"%s/run%d/house/gps/%s/sat/sub_%d/sub_%d/sat_%d.dat.gz",fRawDir.c_str(),fRun,getGpsName(gpsId),gpsPtr->unixTime,gpsPtr->unixTime,gpsPtr->unixTime);
	std::cout << fileName << "\n";
	outFile=fopen(fileName,"ab");
	if(!outFile ) {
	  printf("Couldn't open: %s\n",fileName);
	  return;
      }
      }
      fwrite(gpsPtr,sizeof(GpsAdu5SatStruct_t),1,outFile);
      fileCount++;
      if(fileCount>=HK_PER_FILE) {
	fileCount=0;
	fclose(outFile);
	outFile=NULL;
      }
    }
    
    if(outFile) fclose(outFile);
    outFile=NULL;
  }
  }
}


void AnitaGpsHandler::loopAdu5VtgMaps() 
{
  char fileName[FILENAME_MAX];

  for(int gpsId=0;gpsId<2;gpsId++) {

    std::map<UInt_t,std::map<UInt_t, GpsAdu5VtgStruct_t> >::iterator runIt;
    for(runIt=fAdu5VtgMap[gpsId].begin();runIt!=fAdu5VtgMap[gpsId].end();runIt++) {
      int fRun=runIt->first;       

    int fileCount=0;
    std::map<UInt_t,GpsAdu5VtgStruct_t>::iterator it;
    FILE *outFile=NULL;
    for(it=runIt->second.begin();it!=runIt->second.end();it++) {
      GpsAdu5VtgStruct_t *gpsPtr=&(it->second);
      //    std::cout << gpsPtr->unixTime << "\t" << gpsPtr->unixTime << "\t" << 100*(gpsPtr->unixTime/100) << "\n";    
      
      //    processHk(gpsPtr);
      
      if(outFile==NULL) {
	//      std::cout << "Here\n";
	//Create a file
	if(outFile) fclose(outFile);
	outFile=NULL;
	
	sprintf(fileName,"%s/run%d/house/gps/%s/vtg/sub_%d/sub_%d/",fRawDir.c_str(),fRun,getGpsName(gpsId),gpsPtr->unixTime,gpsPtr->unixTime);       
	gSystem->mkdir(fileName,kTRUE);
	sprintf(fileName,"%s/run%d/house/last",fRawDir.c_str(),fRun);
	AwareRunDatabase::touchFile(fileName);
	sprintf(fileName,"%s/run%d/house/gps/%s/vtg/sub_%d/sub_%d/vtg_%d.dat.gz",fRawDir.c_str(),fRun,getGpsName(gpsId),gpsPtr->unixTime,gpsPtr->unixTime,gpsPtr->unixTime);
	std::cout << fileName << "\n";
	outFile=fopen(fileName,"ab");
	if(!outFile ) {
	  printf("Couldn't open: %s\n",fileName);
	  return;
      }
      }
      fwrite(gpsPtr,sizeof(GpsAdu5VtgStruct_t),1,outFile);
      fileCount++;
      if(fileCount>=HK_PER_FILE) {
	fileCount=0;
	fclose(outFile);
	outFile=NULL;
      }
    }
    
    if(outFile) fclose(outFile);
    outFile=NULL;
  }
  }
}



int AnitaGpsHandler::whichGps(PacketCode_t code) {
  ///< 0 is ADU5A, 1 is ADU5B, 2 is G12
  if(code&PACKET_FROM_ADU5B) {
    return 1;
  }      
  else if(code&PACKET_FROM_G12) {
    return 2;
  }
  else {
    return 0;
  }
}

const char *AnitaGpsHandler::getGpsName(int gpsId) {
  switch(gpsId) {
  case 0: return "adu5a";
  case 1: return "adu5b";
  case 2: return "g12";
  default: return "unknown";
  } 
}
