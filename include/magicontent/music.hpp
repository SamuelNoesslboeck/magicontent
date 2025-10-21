# pragma once

# include <Arduino.h>
# include <inttypes.h>

# include <sylo/music/notes.hpp>

# include "defines.hpp"

namespace magicbox {
    namespace music {
        struct Note {
            uint16_t duration;
            float freq;
        };

        struct Melody {
            uint16_t count;
            const Note* notes;
        };
  
        extern const Melody* active_melody;
        extern uint16_t note_idx;
        extern uint32_t note_stamp;

        void start_playing(const Melody* melody);

        void loop();

        namespace melodies {
            extern const Note STARTUP_NOTES[];
            extern const Melody STARTUP;

            extern const Note BUTTON_A1_NOTES[]; 
            extern const Melody BUTTON_A1;

            extern const Note BUTTON_A2_NOTES[];
            extern const Melody BUTTON_A2;

            extern const Note BUTTON_A3_NOTES[];
            extern const Melody BUTTON_A3; 

            extern const Note BUTTON_ULT_NOTES[];
            extern const Melody BUTTON_ULT;
        }
    }
}