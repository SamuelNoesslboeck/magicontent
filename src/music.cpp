# include <Arduino.h>
# include <inttypes.h>

# include <sylo/music/notes.hpp>

# include "magicontent/defines.hpp"
# include "magicontent/music.hpp"

namespace magicbox {
    namespace music {
        const Melody* active_melody = nullptr;
        uint16_t note_idx = 0;
        uint32_t note_stamp = 0;

        void start_playing(const Melody* melody) {
            active_melody = melody;
            note_idx = 0;
            note_stamp = millis();

            if (active_melody->notes[note_idx].freq > 0.0) {
                tone(MAGICBOX_PIN_BUZZER, (uint32_t)active_melody->notes[note_idx].freq, active_melody->notes[note_idx].duration);
            } else {
                noTone(MAGICBOX_PIN_BUZZER);
            }
        }

        void loop() {
            if (active_melody) {
                uint32_t note_playtime = millis() - note_stamp;

                // Note ran out
                if (note_playtime > active_melody->notes[note_idx].duration) {
                    note_idx++;

                    if (note_idx >= active_melody->count) {
                        active_melody = nullptr;
                        noTone(MAGICBOX_PIN_BUZZER);

                    } else {
                        note_stamp = millis();

                        if (active_melody->notes[note_idx].freq > 0.0) {
                            tone(MAGICBOX_PIN_BUZZER, (uint32_t)active_melody->notes[note_idx].freq, active_melody->notes[note_idx].duration);
                        } else {
                            noTone(MAGICBOX_PIN_BUZZER);
                        }
                    }
                }
            }
        }

        namespace melodies {
            const Note STARTUP_NOTES[] = {
                { 100, NOTE_C5 }, { 50, NOTE_BREAK }, { 100, NOTE_E5 }, { 50, NOTE_BREAK }, { 100, NOTE_G5 }
            };

            const Melody STARTUP = {
                sizeof(STARTUP_NOTES) / sizeof(Note),
                STARTUP_NOTES
            };


            const Note BUTTON_A1_NOTES[] = {
                { 100, NOTE_C5 }
            };

            const Melody BUTTON_A1 = {
                sizeof(BUTTON_A1_NOTES) / sizeof(Note),
                BUTTON_A1_NOTES
            }; 


            const Note BUTTON_A2_NOTES[] = {
                { 100, NOTE_C5 }, { 50, NOTE_BREAK }, { 100, NOTE_E5 }
            };

            const Melody BUTTON_A2 = {
                sizeof(BUTTON_A2_NOTES) / sizeof(Note),
                BUTTON_A2_NOTES
            }; 


            const Note BUTTON_A3_NOTES[] = {
                { 100, NOTE_C5 }, { 50, NOTE_BREAK }, { 100, NOTE_E5 }, { 50, NOTE_BREAK }, { 100, NOTE_G5 }
            };

            const Melody BUTTON_A3 = {
                sizeof(BUTTON_A3_NOTES) / sizeof(Note),
                BUTTON_A3_NOTES
            }; 


            const Note BUTTON_ULT_NOTES[] = {
                { 100, NOTE_A5 }, { 50, NOTE_BREAK }, { 100, NOTE_A5 }, { 50, NOTE_BREAK }, { 100, NOTE_A5 }
            };

            const Melody BUTTON_ULT = {
                sizeof(BUTTON_ULT_NOTES) / sizeof(Note),
                BUTTON_ULT_NOTES
            }; 
        }
    }
}