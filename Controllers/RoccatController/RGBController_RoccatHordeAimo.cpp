/*-----------------------------------------*\
|  RGBController_RoccatHordeAimo.cpp        |
|                                           |
|  Generic RGB Interface for OpenRGB        |
|                                           |
|                                           |
|  Morgan Guimard (morg) 2/24/2022          |
\*-----------------------------------------*/

#include "RGBController_RoccatHordeAimo.h"

RGBController_RoccatHordeAimo::RGBController_RoccatHordeAimo(RoccatHordeAimoController* controller_ptr)
{
    controller          = controller_ptr;

    name                = "Roccat Horde Aimo";
    vendor              = "Roccat";
    type                = DEVICE_TYPE_KEYBOARD;
    description         = "Roccat Horde Aimo Keyboard";

    mode Direct;
    Direct.name         = "Direct";
    Direct.value        = 0;
    Direct.flags        = MODE_FLAG_HAS_PER_LED_COLOR;
    Direct.color_mode   = MODE_COLORS_PER_LED;
    modes.push_back(Direct);

    SetupZones();
}

RGBController_RoccatHordeAimo::~RGBController_RoccatHordeAimo()
{
    delete controller;
}

void RGBController_RoccatHordeAimo::SetupZones()
{
    zone new_zone;
    new_zone.name          = "Keyboard";
    new_zone.type          = ZONE_TYPE_LINEAR;
    new_zone.leds_min      = NUMBER_OF_LEDS;
    new_zone.leds_max      = NUMBER_OF_LEDS;
    new_zone.leds_count    = NUMBER_OF_LEDS;
    new_zone.matrix_map    = NULL;
    zones.push_back(new_zone);

    for(unsigned int i = 0; i < NUMBER_OF_LEDS; i++)
    {
        led new_led;
        new_led.name = "LED " + std::to_string(i + 1);
        leds.push_back(new_led);
    }

    SetupColors();
}

void RGBController_RoccatHordeAimo::ResizeZone(int /*zone*/, int /*new_size*/)
{
    /*---------------------------------------------------------*\
    | This device does not support resizing zones               |
    \*---------------------------------------------------------*/
}

void RGBController_RoccatHordeAimo::DeviceUpdateLEDs()
{   
    UpdateZoneLEDs(0);
}

void RGBController_RoccatHordeAimo::UpdateZoneLEDs(int /*zone_idx*/)
{
    controller->SetColors(colors);
}

void RGBController_RoccatHordeAimo::UpdateSingleLED(int /*led_idx*/)
{
    UpdateZoneLEDs(0);
}

void RGBController_RoccatHordeAimo::SetCustomMode()
{
    active_mode = 0;
}

void RGBController_RoccatHordeAimo::DeviceUpdateMode()
{

}
