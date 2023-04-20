#pragma once

#include <functional>
#include <string>

#define CB_1(funPtr) \
([this](auto && PH1) { funPtr(std::forward<decltype(PH1)>(PH1)); })

#define CB_2(funPtr) \
([this](auto && PH1, auto && PH2) { funPtr(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2)); })

#define CB_3(funPtr) \
([this](auto && PH1, auto && PH2, auto && PH3) { funPtr(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2), std::forward<decltype(PH3)>(PH3)); })

typedef std::function<void(bool pressed, bool hovered)> ButtonCallback;
typedef std::function<void(bool pressed, bool hovered, int entryIndex)> ListCallback;
typedef std::function<void(std::string content)> ContentCallback;
typedef std::function<void(std::string content, std::string passwordContent)> DContentCallback;
typedef std::function<void(bool dragging, bool hovered, float value)> SliderCallback;

#ifndef DEFAULT_FONT_PATH
#ifdef WIN32
    #define DEFAULT_FONT_PATH "C:/Windows/Fonts/Arial.ttf"
#else
    #define DEFAULT_FONT_PATH "/usr/share/fonts/truetype/freefont/FreeSans.ttf"
#endif
#endif

//SHADER
#ifndef CORNER_SMOOTHNESS
#define CORNER_SMOOTHNESS 0.9
#endif

//UI
#ifndef DEFAULT_WIDTH
#define DEFAULT_WIDTH 140
#endif
#ifndef DEFAULT_HEIGHT
#define DEFAULT_HEIGHT 30
#endif
#ifndef AUTO_HEIGHT
#define AUTO_HEIGHT -1.0f
#endif

//TEXT FIELD
#ifndef CURSOR_WIDTH
#define CURSOR_WIDTH 2.75
#endif
#ifndef CURSOR_PADDING
#define CURSOR_PADDING 2
#endif
#ifndef CURSOR_INTERVAL
#define CURSOR_INTERVAL 500000000
#endif
#ifndef PASSWORD_CHARACTER
#define PASSWORD_CHARACTER '*'
#endif

//KEY MAPPING
#ifndef MOUSE_BUTTON_PRESSED
#define MOUSE_BUTTON_PRESSED 0
#endif
#ifndef INPUT_PRESSED
#define INPUT_PRESSED 1
#endif
#ifndef INPUT_REPEATED
#define INPUT_REPEATED 2
#endif
#ifndef INPUT_RELEASED
#define INPUT_RELEASED 0
#endif
#ifndef KEY_ENTER
#define KEY_ENTER 257
#endif
#ifndef KEY_TAB
#define KEY_TAB 258
#endif
#ifndef KEY_BACKSPACE
#define KEY_BACKSPACE 259
#endif
#ifndef KEY_DELETE
#define KEY_DELETE 261
#endif
#ifndef KEY_RIGHT
#define KEY_RIGHT 262
#endif
#ifndef KEY_LEFT
#define KEY_LEFT 263
#endif
#ifndef KEY_UP
#define KEY_UP 265
#endif
#ifndef KEY_DOWN
#define KEY_DOWN 264
#endif
#ifndef KEY_MOD_CONTROL
#define KEY_MOD_CONTROL 0x0002
#endif