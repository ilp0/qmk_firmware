# MCU name
MCU = atmega32u4

#     software delays.
#edit these
#F_CPU = 16000000
F_CPU = 8000000
SRC = trackpad.c IQS5xx.c outputselect.c
BLUETOOTH = AdafruitBLE
WPM_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER_ENABLE = yes

BOOTLOADER = caterina

EXTRAFLAGS += -flto
LTO_ENABLE = yes

DEBUG_ENABLE = no
BOOTMAGIC_ENABLE ?= no	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE ?= yes	# Audio control and System control(+450)
CONSOLE_ENABLE ?= no	# Console for debug(+400)
COMMAND_ENABLE ?= no    # Commands for debug and configuration
SLEEP_LED_ENABLE ?= no  # Breathing sleep LED during USB suspend
NKRO_ENABLE ?= no		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE ?= no  # Enable keyboard backlight functionality
AUDIO_ENABLE ?= no
RGBLIGHT_ENABLE ?= no
MOUSE_SHARED_EP = no
#KEY_LOCK_ENABLE = yes
MOUSE_ENABLE = yes
SPLIT_KEYBOARD = yes
POINTING_DEVICE_ENABLE = yes
#fix
ENCODER_ENABLE = yes

