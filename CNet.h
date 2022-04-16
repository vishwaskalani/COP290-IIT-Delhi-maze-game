#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cstring>
#include <SDL2/SDL_net.h>
 
typedef char charbuf [256];
 
class CNet{
  public:
    static bool Init(); //Initialize SDL_net
    static void Quit(); //Exit SDL_net
};

// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

class CNetMessage {
  protected:
    charbuf buffer; //message stored in buffer, limited to 256 bytes
    enum bufstates { //message states
    EMPTY,
    READING,
    WRITING,
    FULL };
    bufstates state; //the message state
    void reset(); // reset message: fulfill it with zeroes and change its state to EMPTY
  public:
    CNetMessage(); //constructor
//Virtual member function that indicates how many bytes may have to be loaded into the instance. By default, it works with strings that have a maximum
//of 255 characters.
    virtual int NumToLoad();
 
//Virtual member function that indicates how many bytes may have to be downloaded from the instance.
    virtual int NumToUnLoad();
 
    void LoadBytes(charbuf& inputbuffer, int n); //Load a char set into the message buffer
    void UnLoadBytes(charbuf& destbuffer); //Unload a char set from the buffer
    void finish(); //set the state object to full. No more data to be loaded
};

// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

class CIpAddress {
  private:
    IPaddress m_Ip; //the IPaddress structure
  public:
    CIpAddress(); //constructor
    CIpAddress (Uint16 port); //create and associate a port to the instance
    CIpAddress (std::string host, Uint16 port); //create and associate a port and a host to the instance
    void SetIp (IPaddress sdl_ip); //set a CIpAddress object from an existing SDL IPaddress
    bool Ok() const; //True if the object have a port and a host associated to it
    IPaddress GetIpAddress() const; //return a SDL_net IPaddress structure
    Uint32 GetHost() const; //return the host
    Uint16 GetPort() const; //return the port
};
