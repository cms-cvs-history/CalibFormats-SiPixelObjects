#ifndef PIXELFECCONFIGINTERFACE_H
#define PIXELFECCONFIGINTERFACE_H
//
// This class intends to define an abstract interface for the
// commands to talk to the PixelFEC.
//
//  ******THIS SHOULD REALLY BE IN A SEPARATE PACKAGE*****
//
//
//
//
//
//
//
//
//

#include <vector>
#include <string>
#include "CalibFormats/SiPixelObjects/interface/PixelHdwAddress.h"


class PixelFECConfigInterface{

 public:
  
  PixelFECConfigInterface(){};
  
  virtual ~PixelFECConfigInterface(){};

  //Generate the commands needed to set the trim and mask bits that
  //are specified by the vector allPixels. 
  //NOT YET IMPLEMENTED 
  //The commands are not executed until method executeCommandStack() is called.
  //NOT YET IMPLEMENTED  

  virtual void setMaskAndTrimAll(const PixelHdwAddress& theROC,
				 const std::vector<unsigned char>& allPixels)=0;

  //Generate the commands needed to set the trim and mask bits for all
  //pixels to the common value specified by maskAndTrim. 
  //NOT YET IMPLEMENTED  
  //The commands are not executed
  //until method executeCommandStack() is called.
  //NOT YET IMPLEMENTED  
  virtual void setMaskAndTrimCommon(const PixelHdwAddress& theROC,
				    unsigned char maskAndTrim)=0;
  
  //Generate the commands needed to set the DAC values for a ROC.
  //NOT YET IMPLEMENTED
  //The commands are not executed
  //until method executeCommandStack() is called.
  //NOT YET IMPLEMENTED
  virtual void setAllDAC(const PixelHdwAddress& theROC, 
			 const std::vector<unsigned int>& dacs)=0;

  //NOT YET IMPLEMENTED
  //This method executes the commands that have been generated, i.e.,
  //sends them via VME to the FEC in chunks for the right size.
  // mode=0 (default) means that commands are combined such that
  //        they are as large as possible without exceeding the 
  //        1 kbyte limit. Also commands are executed in the same
  //        orders as they were generated.
  // mode=-1 means that the commands are sent one at the time as they
  //        were generated.
  //NOT YET IMPLEMENTED
  virtual void executeCommandStack(int mode=0)=0;

  //NOT YET IMPLEMENTED
  //This method cleans the command stack.
  //NOT YET IMPLEMENTED
  virtual void cleanCommandStack()=0;


  virtual int roctrimload(int mfec, int fecchannel, 
			  int hubaddress, int portaddress, int rocid,
			  const std::vector<unsigned char>& allPixels)=0;

  virtual int injectrstroc(const int mfec, const int bitstate)=0;
  virtual int injecttrigger(const int mfec, const int bitstate)=0;
  virtual int injectrsttbm(const int mfec, const int bitstate)=0;
  virtual int injectrstcsr(const int mfec, const int bitstate)=0;
  virtual int enablecallatency(const int mfec, const int bitstate)=0;
  virtual int disableexttrigger(const int mfec, const int bitstate)=0;
  virtual int loopnormtrigger(const int mfec, const int bitstate)=0;
  virtual int loopcaltrigger(const int mfec, const int bitstate)=0;
  virtual int callatencycount(const int mfec, const int latency)=0;
  virtual int getversion(const int mfec, unsigned long *data)=0;
  virtual int getversion(unsigned long *data)=0;

  virtual int progdac(int mfec, int fecchannel, 
		      int hubaddress, int portaddress, int rocid,
		      int dacaddress, int dacvalue,
		      bool buffermode=false)=0;

  virtual int clrcal(int mfec, int fecchannel, 
		     int hubaddress, int portaddress, int rocid,
		     bool buffermode=false)=0;


  virtual int calpix(int mfec, int mfecchannel, int hubaddress, 
		     int portaddress,
		     int rocid,
		     int coladdr, int rowaddress,
		     int caldata,
		     bool buffermode=false)=0;

  virtual int tbmcmd(int mfec, int fecchannel, 
		     int tbmchannel, int hubaddress, int portaddress,
		     int offset, int databyte, int direction)=0;


  virtual int dcolenable(int mfec, int mfecchannel,
			 int hubaddress, int portaddress, int rocid,
			 int dcol, int dcolstate,
			 bool buffermode=false)=0;

  //Need to give this a different name as otherwise ambiguous
  virtual int progpix1(int mfec, int mfecchannel, int hubaddress, int portaddress,
		      int rocid,
		      int coladdr, int rowaddress,
		      int mask, int trim, bool buffermode=false)=0;

  virtual int progpix(int mfec, int mfecchannel, int hubaddress, int portaddress,
		      int rocid,
		      int coladdr, int rowaddress,
		      unsigned char databyte, bool buffermode=false)=0;

  virtual int qbufsend(void)=0;

  virtual void fecDebug(int newstate)=0;

  //virtual void setVCalDAC(std::string ROC, unsigned char dac)=0;
 
  //... maybe some more

};

#endif
