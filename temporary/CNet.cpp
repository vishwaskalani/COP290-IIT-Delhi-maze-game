#include "CNet.h"
 
bool CNet::Init() {
    if (SDLNet_Init() < 0) {
        std::cerr << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
          return false;
        }
        else
            return true;
}
 
void CNet::Quit() {
    SDLNet_Quit();
}
 
// --------------------------------------------------------------------------------------------------------------------------------------

CNetMessage::CNetMessage() {
    reset();
}
 
void CNetMessage::reset() {
    for (int i =0; i < 256; i++)
        buffer [i] = 0;
    state = EMPTY;
}
 
void CNetMessage::finish() {
    if (state == READING)
        state = FULL;
}
 
int CNetMessage::NumToLoad() {
    if (state == EMPTY)
        return 255;
    else
        return 0;
}
 
int CNetMessage::NumToUnLoad() {
    if (state == FULL)
        return strlen(buffer) + 1;
    else
        return 0;
}
 
void CNetMessage::LoadBytes(charbuf& inputbuffer, int n) {
    for (int i = 0; i < n; i++)
        buffer[i] = inputbuffer[i];
    state = READING;
}
 
void CNetMessage::UnLoadBytes(charbuf& destbuffer) {
    for (int i=0; i < this->NumToUnLoad(); i++)
        destbuffer[i] = buffer[i];
    reset();
}

// --------------------------------------------------------------------------------------------------------------------------------------

CIpAddress::CIpAddress (Uint16 port) {
    if (SDLNet_ResolveHost(&m_Ip, NULL, port) < 0){
        std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
        m_Ip.host = 0;
        m_Ip.port = 0;
    }
}
 
 
CIpAddress::CIpAddress (std::string host, Uint16 port) {
    if (SDLNet_ResolveHost(&m_Ip, host.c_str(), port) < 0) {
        std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
        m_Ip.host = 0;
        m_Ip.port = 0;
    }
}
 
CIpAddress::CIpAddress() {
    m_Ip.host = 0;
    m_Ip.port = 0;
}
 
bool CIpAddress::Ok() const {
    return !(m_Ip.port == 0);
}
 
void CIpAddress::SetIp (IPaddress sdl_ip) { //sets a CTcpSocket object from a existing SDL socket
    m_Ip = sdl_ip;
}
 
IPaddress CIpAddress::GetIpAddress() const {
    return m_Ip;
}
 
Uint32 CIpAddress::GetHost() const {
    return m_Ip.host;
}
 
Uint16 CIpAddress::GetPort() const {
    return m_Ip.port;
}

// --------------------------------------------------------------------------------------------------------------------------------------

