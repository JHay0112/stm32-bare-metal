/**
 * GPIO Programming Interface.
 * Provides methods for reading and writing to digital pins.
 *
 * Author: J. L. Hay
 */

#ifndef SYS_GPIO_H
#define SYS_GPIO_H


typedef enum {
    GPIOB
} gpio_bank_id;

typedef enum {
    GOOD,
    BAD
} gpio_status;


gpio_status gpio_init(gpio_bank_id bank_id);


#endif