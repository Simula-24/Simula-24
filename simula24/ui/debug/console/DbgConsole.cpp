#include "DbgConsole.h"
#include <imgui.h>
#include <core/log/log.h>

using simula24::DebugConsoleGfx;

DebugConsoleGfx::DebugConsoleGfx()
{
    memset(m_cmdBuffer, 0, sizeof(m_cmdBuffer));
}

void DebugConsoleGfx::show()
{
    if (!m_isActive)
        return;
    ImGui::Begin("Debug Console", &m_isActive);
    if (ImGui::InputText("> ", m_cmdBuffer, sizeof(m_cmdBuffer), ImGuiInputTextFlags_EnterReturnsTrue))
    {
        ENGINE_DEBUG("Got Command: %s", m_cmdBuffer);
    memset(m_cmdBuffer, 0, sizeof(m_cmdBuffer));

    }
    ImGui::End();
}