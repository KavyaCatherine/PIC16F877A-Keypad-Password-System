# PIC16F877A-Keypad-Password-System

A Keypad Password Based Door Lock System developed using the PIC16F877A microcontroller and simulated in Proteus.

## Features

- 4x4 matrix keypad for password entry
- 16x2 LCD for user interaction
- 4-digit password verification
- Password displayed as `****` while entering
- Correct password activates the motor
- Motor rotates clockwise to open the door
- Motor rotates anticlockwise to close the door
- Incorrect password displays an error message
- Developed and tested using MPLAB X IDE, XC8 and Proteus

## Hardware / Components

- PIC16F877A
- 4x4 Matrix Keypad
- 16x2 LCD
- L293D Motor Driver
- DC Motor
- 20 MHz Crystal
- Potentiometer
- Resistors and capacitors
- 5V power supply

## Software

- MPLAB X IDE
- XC8 Compiler
- Proteus Design Suite

## Working

1. The LCD displays `Enter Password`.
2. The user enters a 4-digit password using the keypad.
3. The entered digits are displayed as `****`.
4. The entered password is compared with the predefined password.
5. If the password is correct:
   - `Password Correct` is displayed.
   - The motor rotates clockwise to open the door.
   - After a delay, the motor rotates anticlockwise to close the door.
6. If the password is incorrect:
   - `Password Incorrect` is displayed.
   - The user can try again.

## Microcontroller Pin Connections

### LCD

| LCD | PIC16F877A |
|---|---|
| RS | RC0 |
| EN | RC2 |
| D4 | RD4 |
| D5 | RD5 |
| D6 | RD6 |
| D7 | RD7 |
| RW | GND |

### Keypad

| Keypad | PIC16F877A |
|---|---|
| Row A | RB0 |
| Row B | RB1 |
| Row C | RB2 |
| Row D | RB3 |
| Column 1 | RB4 |
| Column 2 | RB5 |
| Column 3 | RB6 |
| Column 4 | RB7 |

### Motor Driver

| L293D | PIC16F877A |
|---|---|
| IN1 | RC4 |
| IN2 | RC5 |

## Password

The current password used in the program is:
`1234`

## Simulation

The project was implemented and tested in Proteus before hardware implementation.

## Future Improvements

- Allow the user to change the password
- Add password attempt limitation
- Add buzzer for incorrect attempts
- Add EEPROM-based password storage
- Add an automatic door-position sensor
