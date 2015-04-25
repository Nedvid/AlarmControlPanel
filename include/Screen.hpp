#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "GPIO.hpp"
#include "debug.hpp"

namespace Screen
{
    class LCD
    {
    private:
        GPIO::GPIOPins * _RS;   // Registry Set ( 0 = Instruction Register (W) Busy Flag: address counter (R), 1 = Data Register (RW) )
        GPIO::GPIOPins * _RW;   // Read/Write ( 0 = W, 1 = R)
        GPIO::GPIOPins * _E;    // Clock, screen starts reading on falling edge

        GPIO::GPIOPins * _D4;
        GPIO::GPIOPins * _D5;
        GPIO::GPIOPins * _D6;
        GPIO::GPIOPins * _D7;

        uint8_t * _charList;

        void WaitForUnblock();
        
        void Write(bool RS, uint8_t data, bool checkForBlockFlag = true);
        void WriteHalf(bool RS, uint8_t data, bool checkForBlockFlag = true);

        uint8_t Read(bool RS);
	public:
		void Init(GPIO::Pin RS = GPIO::Pin::P0, GPIO::Pin RW = GPIO::Pin::P2, GPIO::Pin E = GPIO::Pin::P4, GPIO::Pin D4 = GPIO::Pin::P1, GPIO::Pin D5 = GPIO::Pin::P3, GPIO::Pin D6 = GPIO::Pin::P5, GPIO::Pin D7 = GPIO::Pin::P7);
        ~LCD();

        void WriteString(const char* string);
        void WriteChar(char character);
        void Clear();
        void Home();
        void SetDisplay(bool displayOn, bool cursorOn, bool cursorBlinkOn);
        void FunctionSet(bool lineCount, bool dotCount);
        void EntryMode(bool increment, bool displayShift);
        void SetCursorPosition(bool line, uint8_t pos);
	};

    class Interface
    {
    private:
        const uint8_t _width = 16;
        const uint8_t _height = 2;

        LCD _screen;

        std::string * _menuArray;
        uint8_t _menuArrayLength;

        uint8_t _menuPosition = 0;
    public:
        Interface();
        Interface(LCD screen);

        LCD* GetLCD();

        void SetMenu(std::string * menuArray, uint8_t length);
        void SetMenuPosition(uint8_t position);

        void Redraw();

        void ScrollUp();
        void ScrollDown();
    };
}

#endif // SCREEN_HPP
