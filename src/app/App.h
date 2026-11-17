#pragma once

class App {
public:
    App() = default;
    ~App() = default;
    void begin();
    void update();
    void loop();
    void sleepUntilNextMinute();
};