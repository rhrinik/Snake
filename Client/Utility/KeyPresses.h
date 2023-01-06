#pragma once

class KeyPresses {
public:
    virtual void onKeyUp() {}
    virtual void onKeyDown() {}
    virtual void onKeyLeft() {}
    virtual void onKeyRight() {}
    virtual void onKeyEnter() {}
    virtual void onBackSpace() {}
    virtual void onTextEntered(char c) {}
    virtual ~KeyPresses() = default;
};
