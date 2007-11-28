#ifndef PixelPortCardSettingNames_h
#define PixelPortCardSettingNames_h

#include <string>
namespace pos{
  namespace PortCardSettingNames
  {
    // fpix names and addresses
    
    const std::string k_fpix_Delay25_GCR = "Delay25_GCR";
    const std::string k_fpix_Delay25_SCL = "Delay25_SCL";
    const std::string k_fpix_Delay25_TRG = "Delay25_TRG";
    const std::string k_fpix_Delay25_SDA = "Delay25_SDA";
    const std::string k_fpix_Delay25_RCL = "Delay25_RCL";
    const std::string k_fpix_Delay25_RDA = "Delay25_RDA";
    const std::string k_fpix_AOH_Bias1 = "AOH_Bias1";
    const std::string k_fpix_AOH_Bias2 = "AOH_Bias2";
    const std::string k_fpix_AOH_Bias3 = "AOH_Bias3";
    const std::string k_fpix_AOH_Bias4 = "AOH_Bias4";
    const std::string k_fpix_AOH_Bias5 = "AOH_Bias5";
    const std::string k_fpix_AOH_Bias6 = "AOH_Bias6";
    const std::string k_fpix_AOH_Gain123 = "AOH_Gain123";
    const std::string k_fpix_AOH_Gain456 = "AOH_Gain456";
    const std::string k_fpix_AOH_Gain1 = "AOH_Gain1";
    const std::string k_fpix_AOH_Gain2 = "AOH_Gain2";
    const std::string k_fpix_AOH_Gain3 = "AOH_Gain3";
    const std::string k_fpix_AOH_Gain4 = "AOH_Gain4";
    const std::string k_fpix_AOH_Gain5 = "AOH_Gain5";
    const std::string k_fpix_AOH_Gain6 = "AOH_Gain6";
	
    const unsigned int k_fpix_Delay25_GCR_address = 0x35;
    const unsigned int k_fpix_Delay25_SCL_address = 0x34;
    const unsigned int k_fpix_Delay25_TRG_address = 0x33;
    const unsigned int k_fpix_Delay25_SDA_address = 0x32;
    const unsigned int k_fpix_Delay25_RCL_address = 0x31;
    const unsigned int k_fpix_Delay25_RDA_address = 0x30;
    const unsigned int k_fpix_AOH_Bias1_address = 0x10;
    const unsigned int k_fpix_AOH_Bias2_address = 0x11;
    const unsigned int k_fpix_AOH_Bias3_address = 0x12;
    const unsigned int k_fpix_AOH_Bias4_address = 0x14;
    const unsigned int k_fpix_AOH_Bias5_address = 0x15;
    const unsigned int k_fpix_AOH_Bias6_address = 0x16;
    const unsigned int k_fpix_AOH_Gain123_address = 0x13;
    const unsigned int k_fpix_AOH_Gain456_address = 0x17;
    
    
    // bpix names and addresses
    
    const std::string k_bpix_dummy = "dummy";
    
    const unsigned int k_bpix_dummy_address = 0x01;
  }
}
#endif
