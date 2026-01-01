#ifndef HEADER_KART_CONTROL_HPP
#define HEADER_KART_CONTROL_HPP

#include "utils/types.hpp"

class BareNetworkString;

/**
 * \ingroup controller
 */
class KartControl
{
public:
    enum  SkidControl {SC_NONE, SC_NO_DIRECTION, SC_LEFT, SC_RIGHT};

private:
    int16_t m_steer;
    uint16_t m_accel;
    bool  m_brake;
    bool  m_nitro;
    SkidControl m_skid;
    bool  m_rescue;
    bool  m_fire;
    bool  m_look_back;
    bool m_jump;

public:
    void setSteer(float f);
    void setAccel(float f);
    void setBrake(bool b);
    void setNitro(bool b);
    void setSkidControl(SkidControl sc);
    void setRescue(bool b);
    void setFire(bool b);
    void setLookBack(bool b);
    void setJump(bool b);

    KartControl()
    {
        reset();
    }
    void reset()
    {
        m_steer     = 0;
        m_accel     = 0;
        m_brake     = false;
        m_nitro     = false;
        m_skid      = SC_NONE;
        m_rescue    = false;
        m_fire      = false;
        m_look_back = false;
        m_jump      = false;
    }
    bool operator==(const KartControl &other)
    {
        return m_steer     == other.m_steer   &&
               m_accel     == other.m_accel   &&
               m_brake     == other.m_brake   &&
               m_nitro     == other.m_nitro   &&
               m_skid      == other.m_skid    &&
               m_rescue    == other.m_rescue  &&
               m_fire      == other.m_fire    &&
               m_look_back == other.m_look_back &&
               m_jump      == other.m_jump;
    }

    void saveState(BareNetworkString *buffer) const;
    void rewindTo(BareNetworkString *buffer);
    char getButtonsCompressed() const
    {
        return  (m_brake     ?  1 : 0)
              + (m_nitro     ?  2 : 0)
              + (m_rescue    ?  4 : 0)
              + (m_fire      ?  8 : 0)
              + (m_look_back ? 16 : 0)
              + (m_skid<<5); 
    }
    void setButtonsCompressed(char c)
    {
        m_brake     = (c &  1) != 0;
        m_nitro     = (c &  2) != 0;
        m_rescue    = (c &  4) != 0;
        m_fire      = (c &  8) != 0;
        m_look_back = (c & 16) != 0;
        m_skid      = (SkidControl)((c & 96) >> 5);
        m_jump      = false; 
    }

    float getSteer() const { return (float)m_steer / 32767.0f; }
    float getAccel() const { return (float)m_accel / 65535.0f; }
    bool getBrake() const { return m_brake; }
    bool getNitro() const { return m_nitro; }
    SkidControl getSkidControl() const { return m_skid; }
    bool getRescue() const { return m_rescue; }
    bool getFire() const { return m_fire; }
    bool getLookBack() const { return m_look_back; }
    
    /** Геттер для прыжка */
    bool getJump() const { return m_jump; }
};

#endif
