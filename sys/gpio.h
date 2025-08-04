/**
 * GPIO Programming Interface.
 * Provides methods for reading and writing to digital pins.
 *
 * Author: J. L. Hay
 */

#ifndef SYS_GPIO_H
#define SYS_GPIO_H


#define GPIO_NUM_BANKS 2


typedef enum {
    GPIOA,
    GPIOB
} gpio_bank_id;

typedef enum {
    GOOD,
    BAD
} gpio_status;


gpio_status gpio_init(gpio_bank_id bank_id);


#endif