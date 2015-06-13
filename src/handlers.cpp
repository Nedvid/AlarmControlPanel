#include "main.hpp"
#include "GPIO.hpp"
#include "handlers.hpp"
#include "Leds.hpp"

int button_click_counter = 0;

extern "C" {
    void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName) {
        debug("FATAL EXCEPTION: Stack overflow\n");
        exit(EXIT_FAILURE);
    }

    void SysTick_Handler(void)
    {
        HAL_IncTick();
        xPortSysTickHandler();
    }

    void EXTI9_5_IRQHandler(void)
    {
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
    }

    void EXTI15_10_IRQHandler(void)
    {
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
    }

    void EXTI1_IRQHandler(void)
    {
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
    }

    void HAL_GPIO_EXTI_Callback(uint16_t pin)
    {
        GPIO::Pin gpiopin = static_cast<GPIO::Pin>(pin);
        if( gpiopin == Peripheral::Keyboard::keyboard->GetRowPin(0) ||
            gpiopin == Peripheral::Keyboard::keyboard->GetRowPin(1) ||
            gpiopin == Peripheral::Keyboard::keyboard->GetRowPin(2) ||
            gpiopin == Peripheral::Keyboard::keyboard->GetRowPin(3))
        {
            Peripheral::Keyboard::keyboard->InterruptHandler(gpiopin);
            return;
        }

        switch(pin)
        {
            case GPIO_PIN_1:
                EXTI1_IRQHandlerCpp();
                break;
            case GPIO_PIN_6:
                pPirManager->InterruptHandler(1);
                break;
            case GPIO_PIN_7:
                pPirManager->InterruptHandler(2);
                break;
            case GPIO_PIN_8:
                pPirManager->InterruptHandler(3);
                break;
            case GPIO_PIN_9:
                pPirManager->InterruptHandler(4);
                break;
        }

    }
}

void EXTI1_IRQHandlerCpp()
{
    static Leds diody({GreenLed});
    static uint32_t tickstart = 0;
    static int click_counter = 0;
    if((HAL_GetTick() - tickstart) > 50) {
        click_counter++;
        diody.set_state(click_counter % 2 == 0);
        tickstart = HAL_GetTick();
    }
}
