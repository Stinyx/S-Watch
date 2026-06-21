#include <functional>
#include <vector>

class Setting {
private:
    std::function<void()> action;

public:
    Setting(std::function<void()> func,
            const char* desc,
            bool scroll,
            bool toggle,
            int* scrollOptions);

    const char* description;
    bool scrollable;
    bool toggleable;
    int* scrollOptions;

    void apply();
};

void new_setting(const char* description, std::function<void()> function, bool scrollable, int *scrollOptions, bool toggle);
void new_navigation(const char* description, std::function<void()> function);

void scrollable_menu_up();
void scrollable_menu_down();

void scrollable_menu_apply();

extern std::vector<Setting> settingsOptions;
extern std::vector<Setting> navigationOptions;

extern int currentMenuSelected;
extern int currentNavigationSelected;

extern int lastMenuSelected;
extern int lastNavigationSelected;

// Setting initialisation
void settings_init();

void navigation_init();