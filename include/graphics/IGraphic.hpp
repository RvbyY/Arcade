#pragma once

class IGraphic {
public:
    virtual void init() = 0;
    virtual void draw() = 0;
    virtual void stop() = 0;
    virtual ~IGraphic() = default;
};