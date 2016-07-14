/*
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Author: Federico Reghenzani <federico[DOT]dev[AT]reghe[DOT]net>
 */

#include "A20-gpio.hpp"
extern "C" {
#include "gpio_lib.h"
}


#include"Logger.h"
#include <unistd.h>
namespace A20 {
    // Initialize the static list of objects in GPIO class
    std::vector<GPIO_common*> GPIO::registered;f

    /* ************************************************************* */
    /* ********************** GPIO Class *************************** */
    /* ************************************************************* */
    void GPIO::init()  {
        if(sunxi_gpio_init() < 0) {
            LOGD("unable to init sunxi %s\n", "error");
        }
    }

    GPIO_input* GPIO::get_input(uint16_t port, pull_resistor_t pull_resistor) {

        // First of all, search for already registered pin
        for(std::vector<GPIO_common*>::iterator it = registered.begin(); it != registered.end(); ++it) {

            if ( (*it)->get_port() == port ) {
                if ( (*it)->get_type() == 0) {
                    // Ok, already registered has input
                    return (GPIO_input*)(*it);
                } else {
                    LOGD("trying to read a port setted as output or periphery! %s\n", "error");
                    // Oh no, already registered as other type!
                }
            }
        }

        // Ok, we didn't found the pin, let's export them
        GPIO_input* new_input = new GPIO_input(port, pull_resistor);
        registered.push_back(new_input);
        return new_input;
    }

    GPIO_output* GPIO::get_output(uint16_t port)  {

        // First of all, search for already registered pin
        for(std::vector<GPIO_common*>::iterator it = registered.begin(); it != registered.end(); ++it) {

            if ( (*it)->get_port() == port ) {
                if ( (*it)->get_type() == 1) {
                    // Ok, already registered has output
                    return (GPIO_output*)(*it);
                } else {
                    // Oh no, already registered as other type!
                    LOGD("trying to set a port as output but it's already setted as input or periphery! %s\n", "error");
                }
            }
        }

        // Ok, we didn't found the pin, let's export them
        GPIO_output* new_output = new GPIO_output(port);
        registered.push_back(new_output);
        return new_output;
    }

    void GPIO::set_periphery_mode(uint16_t port)  {
        // First of all, search for already registered pin
        for(std::vector<GPIO_common*>::iterator it = registered.begin(); it != registered.end(); ++it) {

            if ( (*it)->get_port() == port ) {
                if ( (*it)->get_type() == 2) {
                    // Ok, already registered has per
                    return;
                } else {
                    // Oh no, already registered as other type!
                    LOGD("trying to set a port as periphery but it's already setted as input or output! %s\n", "error");
                }
            }
        }

        // Ok, we didn't found the pin, let's export them
        GPIO_periphery* new_per = new GPIO_periphery(port);
        registered.push_back(new_per);
    }

    void GPIO::free(uint16_t port) {
        for(std::vector<GPIO_common*>::iterator it = registered.begin(); it != registered.end(); ++it) {
            if ( (*it)->get_port() == port ) {
                delete *it;                // Unexport the pin
                registered.erase(it);    // Remove from exported vector
                return;                    // Ok return
            }
        }
        // I cannot find the pin in registered pins.
        LOGD("unable to free a non previously requested gpio %s\n", "error");
    }

    /* ************************************************************* */
    /* ******************* GPIO_input class ************************ */
    /* ************************************************************* */

    GPIO_input::GPIO_input(uint16_t port, pull_resistor_t pull_resistor) : port(port) {

        int ret;
        ret = sunxi_gpio_set_cfgpin(port, 0);    // as input
        if (ret < 0)
            LOGD("unable to config gpio %s\n", "error");

        ret = sunxi_gpio_pullup(port, pull_resistor);
        if (ret < 0)
            LOGD("unable to set pull resistor %s\n", "error");

#ifndef GPIO_NO_WAIT
        usleep(100);
#endif
    }

    bool GPIO_input::get() const {
        int ret;

        ret = sunxi_gpio_input(port);
        if (ret < 0)
            LOGD("unable to read gpio %s\n", "error");
        return (bool)ret;
    }

    /* ************************************************************* */
    /* ******************* GPIO_output class *********************** */
    /* ************************************************************* */

    GPIO_output::GPIO_output(uint16_t port) : port(port) {

        int ret;
        ret = sunxi_gpio_set_cfgpin(port, 1);    // as output
        if (ret < 0)
            LOGD("unable to config gpio %s\n", "error");
#ifndef GPIO_NO_WAIT
        usleep(100);
#endif

    }

    void GPIO_output::set(bool value) const {
        int ret;

        ret = sunxi_gpio_output(port,value);
        if (ret < 0){

        }
        LOGD("unable to init sunxi %s\n", "error");
    }

    GPIO_output::~GPIO_output() {
#ifndef GPIO_NO_SAFE_RESET_TO_INPUT
        sunxi_gpio_set_cfgpin(port, 0);    // Reset the pin as input for safety
#endif
    }

    /* ************************************************************* */
    /* ***************** GPIO_periphery class ********************** */
    /* ************************************************************* */

    GPIO_periphery::GPIO_periphery(uint16_t port) : port(port) {

        int ret;
        ret = sunxi_gpio_set_cfgpin(port, 2);    // as per
        if (ret < 0)
            LOGD("unable to init sunxi %s\n", "error");
#ifndef GPIO_NO_WAIT
        usleep(100);
#endif

    }

    GPIO_periphery::~GPIO_periphery() {
#ifndef GPIO_NO_SAFE_RESET_TO_INPUT
        sunxi_gpio_set_cfgpin(port, 0);    // Reset the pin as input for safety
#endif

    }

}
