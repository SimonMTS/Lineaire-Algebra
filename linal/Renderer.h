#pragma once

class Renderer {
public:
    virtual void BeforeEach() = 0;
    virtual void OnKey(int event, int key) = 0;
    virtual void OnMouse(int event) = 0;
    virtual void OnResize(int width, int height) = 0;
};

