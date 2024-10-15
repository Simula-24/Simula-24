#ifndef UI_DEBUG_CONSOLE_DBG_CONSOLE_H_
#define UI_DEBUG_CONSOLE_DBG_CONSOLE_H_


namespace simula24
{

class DebugConsoleGfx
{
public:
    DebugConsoleGfx();
    void show();
    void setActive(bool e) { m_isActive = e; }
    inline bool isActive() const { return m_isActive; }
private:
    bool m_isActive{ false };
    char m_cmdBuffer[256];
};


} // simula24



#endif // UI_DEBUG_CONSOLE_DBG_CONSOLE_H_