# Release Notes

## Unreleased

- Added the `SPI_Regdef_t` register-map struct and `SPI1`-`SPI6` peripheral pointer macros to `stm32f407xx.h`, plus `SPI_Config_t`/`SPI_Handle_t` driver-config structs in `spi.h`.
- Added `hal_drivers/Inc/spi.h` and `hal_drivers/Src/spi.c` SPI driver stubs.
- Removed a redundant `stm32f407xx.h` include from `hal_drivers/Src/gpio.c` (already pulled in via `gpio.h`).
- Added a `stm32-regdef-updater` Claude Code skill (with a `pdf_to_text.py` helper) to generate peripheral register-definition structs and base-address macros in `stm32f407xx.h` from the STM32F4xx reference manual.
- Added reference PDFs under `docs/` (Cortex-M4 generic user guide, STM32F4xx datasheet/programming manual/reference manual, and the F407VGT6 Discovery board schematic).
- Added `.gitattributes` to normalize line endings for git hook and shell scripts, and ignored the skill's generated PDF-text cache in `.gitignore`.
- Added `scripts/git-hooks/pre-commit` (an AI-assisted pre-commit review hook) and `scripts/setup-git-hooks.sh` to enable it.

## b87df46 - Added GPIO driver and GPIO tests

- Added the GPIO peripheral driver and accompanying tests.

## 54d314d - Initial commit

- Initial project setup.
