#ifndef PixelFECParameters_h
#define PixelFECParameters_h

#include <iostream>
#include <vector>
#include <string>

class PixelFECParameters {



 public:

  PixelFECParameters();
  ~PixelFECParameters();

  unsigned int getFECNumber() const;
  unsigned int getCrate() const;
  unsigned int getVMEBaseAddress() const;
  void setFECParameters( unsigned int fecnumber , unsigned int crate , unsigned int vmebaseaddress);
  void setFECNumber(unsigned int fecnumber);
  void setCrate(unsigned int crate);
  void setVMEBaseAddress(unsigned int vmebaseaddress) ;
  friend std::ostream& operator <<(std::ostream& s,const PixelFECParameters &pFECp);
 private :

  unsigned int fecnumber_;   
  unsigned int crate_;   
  unsigned int vmebaseaddress_;   

};

#endif
