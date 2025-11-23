#pragma once

#include <cstdint>

class StepperMotor {
    private:
        // pins
        const uint8_t  dir_pin;              // direction pin
        const uint8_t  step_pin;             // step pin
        const uint8_t  en_pin;               // enable pin
              // state variables  
               bool    enabled      = false; // on/off state
               bool    step_state   = false; // step state
              uint16_t to_step      = 0;     // stepping goal
              uint16_t step_delay   = 0;     // (us) delay between steps
              uint32_t last_time    = 0;     // (us) last step time
              uint32_t current_time = 0;     // (us) current time

    public:
        // constructor
        StepperMotor       (uint8_t dirPin, uint8_t stepPin, uint8_t enPin);

        // getter method
        bool is_stepping   () const;

        // stepper methods
        void enable        (bool val);
        void set_steps     (int16_t steps, uint16_t delay);
        void update_stepper();
};
