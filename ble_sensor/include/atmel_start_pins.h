/*
 * Code generated from START.
 *
 * This file will be overwritten when reconfiguring your START project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <port.h>

/**
 * \brief Set PA0 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PA0_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTA_set_pin_pull_mode(0, pull_mode);
}

/**
 * \brief Set PA0 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PA0_set_dir(const enum port_dir dir)
{
	PORTA_set_pin_dir(0, dir);
}

/**
 * \brief Set PA0 input/sense configuration
 *
 * Enable/disable PA0 digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void PA0_set_isc(const PORT_ISC_t isc)
{
	PORTA_pin_set_isc(0, isc);
}

/**
 * \brief Set PA0 inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on PA0 is inverted
 *                     false = I/O on PA0 is not inverted
 */
static inline void PA0_set_inverted(const bool inverted)
{
	PORTA_pin_set_inverted(0, inverted);
}

/**
 * \brief Set PA0 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PA0_set_level(const bool level)
{
	PORTA_set_pin_level(0, level);
}

/**
 * \brief Toggle output level on PA0
 *
 * Toggle the pin level
 */
static inline void PA0_toggle_level()
{
	PORTA_toggle_pin_level(0);
}

/**
 * \brief Get level on PA0
 *
 * Reads the level on a pin
 */
static inline bool PA0_get_level()
{
	return PORTA_get_pin_level(0);
}

/**
 * \brief Set PA1 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PA1_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTA_set_pin_pull_mode(1, pull_mode);
}

/**
 * \brief Set PA1 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PA1_set_dir(const enum port_dir dir)
{
	PORTA_set_pin_dir(1, dir);
}

/**
 * \brief Set PA1 input/sense configuration
 *
 * Enable/disable PA1 digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void PA1_set_isc(const PORT_ISC_t isc)
{
	PORTA_pin_set_isc(1, isc);
}

/**
 * \brief Set PA1 inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on PA1 is inverted
 *                     false = I/O on PA1 is not inverted
 */
static inline void PA1_set_inverted(const bool inverted)
{
	PORTA_pin_set_inverted(1, inverted);
}

/**
 * \brief Set PA1 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PA1_set_level(const bool level)
{
	PORTA_set_pin_level(1, level);
}

/**
 * \brief Toggle output level on PA1
 *
 * Toggle the pin level
 */
static inline void PA1_toggle_level()
{
	PORTA_toggle_pin_level(1);
}

/**
 * \brief Get level on PA1
 *
 * Reads the level on a pin
 */
static inline bool PA1_get_level()
{
	return PORTA_get_pin_level(1);
}

/**
 * \brief Set PA2 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PA2_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTA_set_pin_pull_mode(2, pull_mode);
}

/**
 * \brief Set PA2 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PA2_set_dir(const enum port_dir dir)
{
	PORTA_set_pin_dir(2, dir);
}

/**
 * \brief Set PA2 input/sense configuration
 *
 * Enable/disable PA2 digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void PA2_set_isc(const PORT_ISC_t isc)
{
	PORTA_pin_set_isc(2, isc);
}

/**
 * \brief Set PA2 inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on PA2 is inverted
 *                     false = I/O on PA2 is not inverted
 */
static inline void PA2_set_inverted(const bool inverted)
{
	PORTA_pin_set_inverted(2, inverted);
}

/**
 * \brief Set PA2 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PA2_set_level(const bool level)
{
	PORTA_set_pin_level(2, level);
}

/**
 * \brief Toggle output level on PA2
 *
 * Toggle the pin level
 */
static inline void PA2_toggle_level()
{
	PORTA_toggle_pin_level(2);
}

/**
 * \brief Get level on PA2
 *
 * Reads the level on a pin
 */
static inline bool PA2_get_level()
{
	return PORTA_get_pin_level(2);
}

/**
 * \brief Set PA3 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PA3_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTA_set_pin_pull_mode(3, pull_mode);
}

/**
 * \brief Set PA3 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PA3_set_dir(const enum port_dir dir)
{
	PORTA_set_pin_dir(3, dir);
}

/**
 * \brief Set PA3 input/sense configuration
 *
 * Enable/disable PA3 digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void PA3_set_isc(const PORT_ISC_t isc)
{
	PORTA_pin_set_isc(3, isc);
}

/**
 * \brief Set PA3 inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on PA3 is inverted
 *                     false = I/O on PA3 is not inverted
 */
static inline void PA3_set_inverted(const bool inverted)
{
	PORTA_pin_set_inverted(3, inverted);
}

/**
 * \brief Set PA3 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PA3_set_level(const bool level)
{
	PORTA_set_pin_level(3, level);
}

/**
 * \brief Toggle output level on PA3
 *
 * Toggle the pin level
 */
static inline void PA3_toggle_level()
{
	PORTA_toggle_pin_level(3);
}

/**
 * \brief Get level on PA3
 *
 * Reads the level on a pin
 */
static inline bool PA3_get_level()
{
	return PORTA_get_pin_level(3);
}

/**
 * \brief Set RN487X_RST pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void RN487X_RST_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTD_set_pin_pull_mode(3, pull_mode);
}

/**
 * \brief Set RN487X_RST data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void RN487X_RST_set_dir(const enum port_dir dir)
{
	PORTD_set_pin_dir(3, dir);
}

/**
 * \brief Set RN487X_RST input/sense configuration
 *
 * Enable/disable RN487X_RST digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void RN487X_RST_set_isc(const PORT_ISC_t isc)
{
	PORTD_pin_set_isc(3, isc);
}

/**
 * \brief Set RN487X_RST inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on RN487X_RST is inverted
 *                     false = I/O on RN487X_RST is not inverted
 */
static inline void RN487X_RST_set_inverted(const bool inverted)
{
	PORTD_pin_set_inverted(3, inverted);
}

/**
 * \brief Set RN487X_RST level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void RN487X_RST_set_level(const bool level)
{
	PORTD_set_pin_level(3, level);
}

/**
 * \brief Toggle output level on RN487X_RST
 *
 * Toggle the pin level
 */
static inline void RN487X_RST_toggle_level()
{
	PORTD_toggle_pin_level(3);
}

/**
 * \brief Get level on RN487X_RST
 *
 * Reads the level on a pin
 */
static inline bool RN487X_RST_get_level()
{
	return PORTD_get_pin_level(3);
}

/**
 * \brief Set PF0 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PF0_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTF_set_pin_pull_mode(0, pull_mode);
}

/**
 * \brief Set PF0 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PF0_set_dir(const enum port_dir dir)
{
	PORTF_set_pin_dir(0, dir);
}

/**
 * \brief Set PF0 input/sense configuration
 *
 * Enable/disable PF0 digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void PF0_set_isc(const PORT_ISC_t isc)
{
	PORTF_pin_set_isc(0, isc);
}

/**
 * \brief Set PF0 inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on PF0 is inverted
 *                     false = I/O on PF0 is not inverted
 */
static inline void PF0_set_inverted(const bool inverted)
{
	PORTF_pin_set_inverted(0, inverted);
}

/**
 * \brief Set PF0 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PF0_set_level(const bool level)
{
	PORTF_set_pin_level(0, level);
}

/**
 * \brief Toggle output level on PF0
 *
 * Toggle the pin level
 */
static inline void PF0_toggle_level()
{
	PORTF_toggle_pin_level(0);
}

/**
 * \brief Get level on PF0
 *
 * Reads the level on a pin
 */
static inline bool PF0_get_level()
{
	return PORTF_get_pin_level(0);
}

/**
 * \brief Set PF1 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PF1_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTF_set_pin_pull_mode(1, pull_mode);
}

/**
 * \brief Set PF1 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PF1_set_dir(const enum port_dir dir)
{
	PORTF_set_pin_dir(1, dir);
}

/**
 * \brief Set PF1 input/sense configuration
 *
 * Enable/disable PF1 digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void PF1_set_isc(const PORT_ISC_t isc)
{
	PORTF_pin_set_isc(1, isc);
}

/**
 * \brief Set PF1 inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on PF1 is inverted
 *                     false = I/O on PF1 is not inverted
 */
static inline void PF1_set_inverted(const bool inverted)
{
	PORTF_pin_set_inverted(1, inverted);
}

/**
 * \brief Set PF1 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PF1_set_level(const bool level)
{
	PORTF_set_pin_level(1, level);
}

/**
 * \brief Toggle output level on PF1
 *
 * Toggle the pin level
 */
static inline void PF1_toggle_level()
{
	PORTF_toggle_pin_level(1);
}

/**
 * \brief Get level on PF1
 *
 * Reads the level on a pin
 */
static inline bool PF1_get_level()
{
	return PORTF_get_pin_level(1);
}

/**
 * \brief Set Button pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void Button_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTF_set_pin_pull_mode(3, pull_mode);
}

/**
 * \brief Set Button data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void Button_set_dir(const enum port_dir dir)
{
	PORTF_set_pin_dir(3, dir);
}

/**
 * \brief Set Button input/sense configuration
 *
 * Enable/disable Button digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void Button_set_isc(const PORT_ISC_t isc)
{
	PORTF_pin_set_isc(3, isc);
}

/**
 * \brief Set Button inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on Button is inverted
 *                     false = I/O on Button is not inverted
 */
static inline void Button_set_inverted(const bool inverted)
{
	PORTF_pin_set_inverted(3, inverted);
}

/**
 * \brief Set Button level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void Button_set_level(const bool level)
{
	PORTF_set_pin_level(3, level);
}

/**
 * \brief Toggle output level on Button
 *
 * Toggle the pin level
 */
static inline void Button_toggle_level()
{
	PORTF_toggle_pin_level(3);
}

/**
 * \brief Get level on Button
 *
 * Reads the level on a pin
 */
static inline bool Button_get_level()
{
	return PORTF_get_pin_level(3);
}

/**
 * \brief Set PF4 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PF4_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTF_set_pin_pull_mode(4, pull_mode);
}

/**
 * \brief Set PF4 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PF4_set_dir(const enum port_dir dir)
{
	PORTF_set_pin_dir(4, dir);
}

/**
 * \brief Set PF4 input/sense configuration
 *
 * Enable/disable PF4 digital input buffer and pin change interrupt,
 * select pin interrupt edge/level sensing mode
 *
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
static inline void PF4_set_isc(const PORT_ISC_t isc)
{
	PORTF_pin_set_isc(4, isc);
}

/**
 * \brief Set PF4 inverted mode
 *
 * Enable or disable inverted I/O on a pin
 *
 * \param[in] inverted true  = I/O on PF4 is inverted
 *                     false = I/O on PF4 is not inverted
 */
static inline void PF4_set_inverted(const bool inverted)
{
	PORTF_pin_set_inverted(4, inverted);
}

/**
 * \brief Set PF4 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PF4_set_level(const bool level)
{
	PORTF_set_pin_level(4, level);
}

/**
 * \brief Toggle output level on PF4
 *
 * Toggle the pin level
 */
static inline void PF4_toggle_level()
{
	PORTF_toggle_pin_level(4);
}

/**
 * \brief Get level on PF4
 *
 * Reads the level on a pin
 */
static inline bool PF4_get_level()
{
	return PORTF_get_pin_level(4);
}

#endif /* ATMEL_START_PINS_H_INCLUDED */
