#ifndef PixelTimeFormatter_h
#define PixelTimeFormatter_h
/**
* \file CalibFormats/SiPixelObjects/interface/PixelTimeFormatter.h
* \brief This class provides utility methods to manipulate ASCII formatted timestamps
*
*   A longer explanation will be placed here later
*/

#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <sys/time.h>

namespace pos{
  class PixelTimeFormatter
  {
  public:

    PixelTimeFormatter(std::string source) 
    {
     origin_ = source ;
     std::cout << "[PixelTimeFormatter::PixelTimeFormatter()]\t\t    Time counter started for " << origin_ << std::endl ;
     startTime_ = getImSecTime() ;
    }
    
    void stopTimer(void) 
    {
     endTime_ = getImSecTime() ;
     unsigned int seconds  = (unsigned int)endTime_.tv_sec  - (unsigned int)startTime_.tv_sec  ;
     double useconds = (double)(endTime_.tv_usec - startTime_.tv_usec) / 1000000. ;   
     if( seconds == 0 )
       {
         std::cout << "[PixelTimeFormatter::stopTimer()]\t\t\t    Elapsed time: " << useconds << " seconds for " << origin_ << std::endl ;
       }
     else 
       {
         std::cout << "[PixelTimeFormatter::stopTimer()]\t\t\t    Elapsed time: " <<  seconds << " seconds for " << origin_ << std::endl ;
       } 
  
    }

    static std::string getTime(void) 
    {
      char theDate[20] ;
      struct tm *thisTime;
      time_t aclock;
      std::string date ;
      time( &aclock );		  
      thisTime = localtime( &aclock ); 
       
      sprintf(theDate,
	      "%d-%02d-%02d %02d:%02d:%02d", thisTime->tm_year+1900,
	      thisTime->tm_mon+1,
	      thisTime->tm_mday,
	      thisTime->tm_hour,
	      thisTime->tm_min,
	      thisTime->tm_sec ); 
      date = theDate ;
      //std::cout << "[PixelTimeFormatter::getTime()]\t\t\t\t    Time: " << date << std::endl ;					  
      return date ;
    }

    struct tm * getITime(void) 
    {
      struct tm *thisTime;
      time_t aclock;
      time( &aclock );		  
      thisTime = localtime( &aclock ); 
      return thisTime ;
    }

    static std::string getmSecTime(void) 
    {
      char theDate[20] ;
      struct timeval msecTime;
      gettimeofday(&msecTime, (struct timezone *)0) ;
      
      sprintf(theDate,
	      "%d-%d", 
	      (unsigned int)msecTime.tv_sec,
	      (unsigned int)msecTime.tv_usec ); 
      return std::string(theDate) ;
    }

    struct timeval getImSecTime(void) 
    {
      struct timeval msecTime;
      gettimeofday(&msecTime, (struct timezone *)0) ;
      
      return msecTime ;
    }
    
    //---------------------------------------------------------------
    
    private:
    
     struct timeval startTime_ ;
     struct timeval endTime_   ;
     std::string    origin_    ;
     bool           verbose_   ;
  } ;
}

#endif
