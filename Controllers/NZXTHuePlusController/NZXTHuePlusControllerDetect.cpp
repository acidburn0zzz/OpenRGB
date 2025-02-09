#include "Detector.h"
#include "NZXTHuePlusController.h"
#include "RGBController.h"
#include "RGBController_NZXTHuePlus.h"
#include "find_usb_serial_port.h"
#include <vector>

#define NZXT_HUE_PLUS_VID 0x04D8
#define NZXT_HUE_PLUS_PID 0x00DF

/******************************************************************************************\
*                                                                                          *
*   DetectNZXTHuePlusControllers                                                           *
*                                                                                          *
*       Detect devices supported by the NZXTHuePlus driver                                 *
*                                                                                          *
\******************************************************************************************/

void DetectNZXTHuePlusControllers(std::vector<RGBController*> &rgb_controllers)
{
    std::vector<std::string *> ports = find_usb_serial_port(NZXT_HUE_PLUS_VID, NZXT_HUE_PLUS_PID);

    for(unsigned int i = 0; i < ports.size(); i++)
    {
        if(*ports[i] != "")
        {
            HuePlusController*     controller     = new HuePlusController();
            controller->Initialize((char *)ports[i]->c_str());
            RGBController_HuePlus* rgb_controller = new RGBController_HuePlus(controller);

            ResourceManager::get()->RegisterRGBController(rgb_controller);
        }
    }
}   /* DetectHuePlusControllers() */

REGISTER_DETECTOR("NZXT Hue+", DetectNZXTHuePlusControllers);
