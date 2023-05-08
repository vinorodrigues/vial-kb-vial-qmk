# IDOBAO ID67

![id67](https://i.imgur.com/XiEnksSh.png)

A 65% hotswap keyboard from IDOBAO.

## ANSI support:

* Keyboard Maintainer: [Vino Rodrigues](https://github.com/vinorodrigues)
* Hardware Supported: **ID67 Bestype**
* Hardware Availability: [IDOBAO.net](https://idobao.net/products/idobao-id67-bestype-keyboard-kit-aluminum-with-brass-weight)

## Compiling and Flashing

Make example for this keyboard (after setting up your build environment):

    make id67:default

Flashing example for this keyboard:

    make id67:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the `Escape` key and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` (FN+Z).
