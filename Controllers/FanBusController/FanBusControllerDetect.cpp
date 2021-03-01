#include "Detector.h"
#include "FanBusController.h"
#include "FanController_FanBus.h"
#include "RGBController_FanBus.h"

void DetectFanBusControllers(std::vector<RGBController*> &rgb_controllers)
{
    FanBusInterface*    new_interface;
    json                fanbus_settings;

    /*-------------------------------------------------*\
    | Get LED Strip settings from settings manager      |
    \*-------------------------------------------------*/
    fanbus_settings = ResourceManager::get()->GetSettingsManager()->GetSettings("FanBusDevices");

    /*-------------------------------------------------*\
    | If the LEDStrip settings contains devices, process|
    \*-------------------------------------------------*/
    if(fanbus_settings.contains("devices"))
    {
        for(unsigned int device_idx = 0; device_idx < fanbus_settings["devices"].size(); device_idx++)
        {
            if(fanbus_settings["devices"][device_idx].contains("port"))
            {
                std::string port_val = fanbus_settings["devices"][device_idx]["port"];

                new_interface     = new FanBusInterface(port_val.c_str());

                std::vector<unsigned char> detected_controllers = new_interface->DetectControllers();

                for(unsigned int controller_idx = 0; controller_idx < detected_controllers.size(); controller_idx++)
                {
                    FanBusController*     controller     = new FanBusController(new_interface, detected_controllers[controller_idx]);
                    RGBController_FanBus* rgb_controller = new RGBController_FanBus(controller);

                    ResourceManager::get()->RegisterRGBController(new_rgbcontroller);

                    FanController_FanBus* fan_controller = new FanController_FanBus(controller);
                    ResourceManager::get()->RegisterFanController(fan_controller);
                }
            }
        }
    }
}

REGISTER_DETECTOR("FanBus", DetectFanBusControllers);
