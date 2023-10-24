#pragma once

class IApplication
{
private:
    /* data */
public:
    IApplication(/* args */);
    virtual ~IApplication() = 0;

    virtual void Initialize() = 0;
    virtual void Update() = 0;
};
