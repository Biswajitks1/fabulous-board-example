#include <global_defs.h>
#include <upload_bitstream.h>

#define PIN_SCLK GPIO_10
#define PIN_SDATA GPIO_11

#define CTRL_WORD_DISABLE_BITBANG 0x0000FAB0u
#define CTRL_WORD_ENABLE_BITBANG 0x0000FAB1u

/**
 * @brief Use bitbanging to upload the bitstream to the FPGA.
 * @param bitstream_data The bitstream data to be transmitted to the FPGA.
 * @param bitream_size The bitstream size in bytes.
 * @param ctrl_word The control word used to control the bitbang module.
 */

void upload_bitstream(uint8_t const *const bitstream_data,
        uint32_t bitream_size)
{
    for (uint32_t byte_pos = 0u; byte_pos < bitream_size; byte_pos++) {
        for (uint32_t bit_pos = 0u; bit_pos < BITS_IN_BYTE; bit_pos++) {
            bool set;
            set = (bool)(bitstream_data[byte_pos] >> (MSB_IN_BYTE - bit_pos) & 1u);
            set_or_clear_pin(PIN_SDATA, set);
            set_pin(PIN_SCLK);
            set = (bool)(CTRL_WORD_ENABLE_BITBANG >>
                    (MSB_IN_WORD - (BYTES_IN_WORD * (byte_pos % BYTES_IN_WORD) + bit_pos)) &
                    1u);
            set_or_clear_pin(PIN_SDATA, set);
            clear_pin(PIN_SCLK);
        }
    }
}
