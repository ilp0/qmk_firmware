# MCU name
MCU = atmega32u4

#     software delays.
F_CPU = 8000000

BOOTLOADER = caterina

BLUETOOTH = AdafruitBLE

EXTRAFLAGS += -flto

DEBUG_ENABLE = yes
BOOTMAGIC_ENABLE ?= no	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE ?= yes	# Audio control and System control(+450)
CONSOLE_ENABLE ?= yes	# Console for debug(+400)
COMMAND_ENABLE ?= no    # Commands for debug and configuration
SLEEP_LED_ENABLE ?= no  # Breathing sleep LED during USB suspend
NKRO_ENABLE ?= no		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE ?= no  # Enable keyboard backlight functionality
AUDIO_ENABLE ?= no
RGBLIGHT_ENABLE ?= no
MOUSE_SHARED_EP = no
#KEY_LOCK_ENABLE = yes
MOUSE_ENABLE = yes

SPLIT_KEYBOARD = no

OLED_ENABLE = no
OLED_DRIVER_ENABLE = no
WPM_ENABLE = no
ENCODER_ENABLE = yes

SRC = trackpad.c IQS5xx.c i2c_fns.c

POINTING_DEVICE_ENABLE = yes