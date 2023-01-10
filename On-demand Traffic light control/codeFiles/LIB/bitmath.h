#ifndef BITMATH_H
#define BITMATH_H

/* Read -> Modify -> Wirte*/

/* Clear bit by shift left 1 to bit -> invert value -> AND with register */
#define CLR_BIT(reg, bit) (reg &= ~(1 << bit))

/* Set bit by shift left 1 to bit -> OR with register */
#define SET_BIT(reg, bit) (reg |= (1 << bit))

/* Get bit by shift 1 to bit -> AND with register -> shift bit left to first bit */
#define GET_BIT(reg, bit) ((reg & (1 << bit)) >> bit)

#define TOGGLE_PIN(reg, bit) (reg ^= (1 << bit))

#endif