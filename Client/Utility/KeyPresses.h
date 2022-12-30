#pragma once

class KeyPresses {
public:
    virtual void onKeyUp() {}
    virtual void onKeyDown() {}
    virtual void onKeyLeft() {}
    virtual void onKeyRight() {}
    virtual void onKeyEnter() {}
    virtual ~KeyPresses() = default;
};
