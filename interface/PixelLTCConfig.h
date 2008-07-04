#ifndef PixelLTCConfig_h
#define PixelLTCConfig_h
/**
*   \file CalibFormats/SiPixelObjects/interface/PixelLTCConfig..h
*   \brief This class reads the LTC configuration file
*
*   A longer explanation will be placed here later
*/
 
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <sstream>
#include "CalibFormats/SiPixelObjects/interface/PixelConfigBase.h"


namespace pos{
/*!  \ingroup ConfigurationObjects "Configuration Objects"
*    
*  @{
*
*  \class PixelLTCConfig PixelLTCConfig.h
*  \brief This is the documentation about PixelLTCConfig...
*
*  This class reads the LTC configuration file
*/
  class PixelLTCConfig: public PixelConfigBase{
 
  public:
   
    PixelLTCConfig(std::string filename);
    //std::string getLTCConfigPath() {return ltcConfigPath_;}
    std::stringstream& getLTCConfigStream() {return ltcConfigStream_;}

    virtual void writeASCII(std::string dir) const;
    virtual void writeXML(pos::PixelConfigKey key, std::string path) const {;}

 
  private:
 
    //std::string ltcConfigPath_;
    std::stringstream ltcConfigStream_;

  };
}
/* @} */
#endif
