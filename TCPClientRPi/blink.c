// Hola que tal

#include <bcm2835.h>
// TCP BlInk on RPi pin GPIO 17
#define PIN RPI_GPIO_P1_11

int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO
    // Use for testing
//    bcm2835_set_debug(1);
    if (!bcm2835_init())
        return 1;
    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

    


    if (on == 1)
    {
        // Turn it on
        bcm2835_gpio_write(PIN, HIGH);
    else
    {
	// Turn it off
        bcm2835_gpio_write(PIN, LOW);
    }
    return 0;
}
