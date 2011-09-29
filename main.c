#define F_CPU 1000000

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

int main(void) {
  // Configure pull-ups for buttons
  PORTB |= _BV(PORTB0) | _BV(PORTB1);

  // Configure the LEDS for output
  DDRB = _BV(DDB2) | _BV(DDB3) | _BV(DDB4);

  // Enable the pin change interrupts
  GIMSK = _BV(PCIE);
  PCMSK = _BV(PCINT0) | _BV(PCINT1);

  sei();

  for(;;) {
    uint8_t button1 = !(PINB & _BV(PINB0));
    uint8_t button2 = !(PINB & _BV(PINB1));
    if (button1 && button2) {
      PORTB |= _BV(PORTB2) | _BV(PORTB3) | _BV(PORTB4);
    } else {
      PORTB &= ~(_BV(PORTB2) | _BV(PORTB3) | _BV(PORTB4));
    }

    sleep_enable();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_cpu();
    sleep_disable();
  }
}

ISR(PCINT0_vect) {
  // Do nothing
}
