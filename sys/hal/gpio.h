/**
 * GPIO Programming Interface.
 * Provides methods for reading and writing to digital pins.
 *
 * Author: J. L. Hay
 */

#ifndef SYS_GPIO_H
#define SYS_GPIO_H


#include <stdint.h>


#define GPIO_NUM_BANKS 2


typedef enum {
    GPIOA,
    GPIOB
} gpio_bank_id;

typedef uint8_t gpio_pin_id;
typedef uint8_t gpio_value;

typedef enum {
    GOOD,
    BAD
} gpio_status;


gpio_status gpio_init(gpio_bank_id bank_id);
gpio_status gpio_set(gpio_bank_id bank_id, gpio_pin_id pin_id, gpio_value val);


#endif