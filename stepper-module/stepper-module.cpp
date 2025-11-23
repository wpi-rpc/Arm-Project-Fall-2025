#include <cstdint>
#include <cstdlib>
#include "pico/stdlib.h"

#include "stepper-module.h"


// constructor
StepperMotor::StepperMotor(uint8_t dirPin , uint8_t  stepPin , uint8_t enPin) :
                           dir_pin(dirPin), step_pin(stepPin), en_pin (enPin) {           
    // initialize direction pin
    gpio_init   (dir_pin           );
    gpio_set_dir(dir_pin , GPIO_OUT);

    // initialize step pin
    gpio_init   (step_pin          );
    gpio_set_dir(step_pin, GPIO_OUT);

    // initialize enable pin and disable to start
    gpio_init   (en_pin            );
    gpio_set_dir(en_pin  , GPIO_OUT);
    gpio_put    (en_pin  , true    );
}

//getter method
/**
 * returns true if currently stepping, false otherwise
 */
bool StepperMotor::is_stepping() const { return(to_step != 0); }


//stepper methods
/**
 * val :  enable/disable value
 * 
 * enables the driver if true, disables it otherwise
 */
void StepperMotor::enable(bool val) {
    gpio_put(en_pin, !val);
}

/**
 * steps      :  amount of steps to move in positive or negative direction
 * delay (us) :  delay between steps in us
 * 
 * sets step goal for the specified step amount and interval between steps
 */
void StepperMotor::set_steps(int16_t steps, uint16_t delay) {
    if((enabled) && (steps != 0) && (delay != 0)) {
        to_step        = abs(steps);
        step_delay     = delay;

        bool direction = (steps > 0) ? (true) : (false);
        gpio_put(dir_pin, direction);

        last_time      = time_us_32();
        step_state     = false;
    }
}

/**
 * updates stepper state in main loop
 */
void StepperMotor::update_stepper() {
    if(to_step != 0) {
        current_time = time_us_32();

        if((current_time - last_time) >= (step_delay)) {
            step_state = !step_state;
            gpio_put(step_pin , step_state);

            if((step_state == false) && (to_step > 0)) to_step--;

            last_time  = current_time;
        }
    }
}
