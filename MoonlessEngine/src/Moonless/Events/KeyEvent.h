#pragma once

#include "Event.h"

#include <sstream>

namespace Moonless
{

    class ML_DLL_API KeyEvent : public Event {
    public:
        int GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        KeyEvent(const int keycode)
            : m_KeyCode(keycode) {}

        int m_KeyCode;
    };

    class ML_DLL_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(const int keycode, int repeat_count)
            : KeyEvent(keycode), m_repeat_count(repeat_count) {}
        
        int RepeatCount() const { return m_repeat_count; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (repeat count = " << m_repeat_count << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        int m_repeat_count;
    };

    class ML_DLL_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(const int keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class ML_DLL_API KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(const int keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };

}
