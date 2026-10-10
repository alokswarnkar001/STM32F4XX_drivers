---
name: stm32-regdef-updater
description: Adds or updates a peripheral's register-definition struct (xxx_Regdef_t) and its peripheral pointer macro in hal_drivers/Inc/stm32f407xx.h, sourced from docs/STM32F4xx_RM.pdf (RM0090). Use this whenever the user wants to "add", "define", "implement", or "fill in" a peripheral's registers in stm32f407xx.h — SPI, I2C, USART/UART, ADC, DAC, TIM, DMA, CAN, RTC, SDIO, CRC, PWR, IWDG/WWDG, or any other STM32F407 peripheral — including when they just point at the existing incomplete SPI_Regdef_t stub and say "finish this" or "do the same for I2C". Also covers adding a missing base-address (_BA) macro for a peripheral. ALSO use this when the user asks to add/complete/update a peripheral's register bit fields (e.g. "update SPI_CR1 bit fields", "add bit fields for all I2C registers", "complete the SPI_CR1 union") — those go in the peripheral-specific header (hal_drivers/Inc/spi.h, i2c.h, ...), never in stm32f407xx.h; see the "Bit-field definitions" section. Do not generate SPI_CR1_SPE-style position/mask #defines.
---

# STM32F407xx Register Definition Updater

Adds a peripheral's register-map struct and base-address-typecast pointer macro
to `hal_drivers/Inc/stm32f407xx.h`, reading the authoritative register layout
from `docs/STM32F4xx_RM.pdf` (RM0090, the STM32F405/415/407/417/427/437/429/439
reference manual — it covers several F4 lines at once, so only trust registers/
bits that this manual documents as present on STM32F407, not lines that don't
apply here).

This skill has two modes, chosen by what the user asks for:

1. **Register map** (Steps 0-6 below): register-map struct + base address +
   pointer macro, all in `hal_drivers/Inc/stm32f407xx.h`.
2. **Bit fields** ("Bit-field definitions" section at the end): per-register
   bit-field unions, written to the **peripheral-specific header**
   (`hal_drivers/Inc/spi.h`, `i2c.h`, ...) — *not* to `stm32f407xx.h`.

Only do the mode the user asked for. The register-map mode does not generate
bit fields; say so when you report back so it isn't mistaken for a finished
driver header. Never generate `SPI_CR1_SPE`-style position/mask `#define`s in
either mode — the user has explicitly rejected that style.

## Step 0 — Ask which peripheral

Before touching anything, ask the user which peripheral(s) to add or update
(e.g. SPI, I2C, USART/UART, ADC, TIM, DMA, CAN, RTC, SDIO, ...). Don't guess —
the existing file already has an incomplete `SPI_Regdef_t` stub, but that
doesn't mean SPI is what they want right now.

If they point at the stub and say "finish this," that's your answer — no
need to ask again.

## Step 1 — Learn the file's own conventions before writing anything

Read `hal_drivers/Inc/stm32f407xx.h` in full first. Don't pattern-match from
memory — the conventions below are what's there *today*, and the user may
have changed things since this skill was written. Confirm against the live
file. As of this skill's authoring:

- **Base address macros** are grouped under bus-domain comment banners:
  `//base Address for AHB1 Peripherals`, `//Base address for APB1 Peripherals`,
  `//Base address for APB2 Peripherals`. Each entry is
  `#define <PERIPH>_BA   (<BUS>_BA + 0x????U)`, columns roughly aligned with
  the existing entries in that block.
- **Register-map structs** live under the banner
  `/****************Peripheral Register Definitions****************/`, each
  preceded by a one-line comment `/*<Peripheral> Peripheral*/`. Fields are
  `volatile uint32_t <REG>;`, one per line, 4-space indented. Multi-register
  gaps use `volatile uint32_t RESERVEDn;` (or `RESERVEDn[count]` for a
  multi-word gap), numbered sequentially per struct. RCC/EXTI/SYSCFG structs
  comment every member with its byte offset (`/* 0x00 */`); GPIO's struct
  predates that habit and has none. Follow the offset-comment style for any
  new struct — it's the convention going forward even though the oldest
  struct in the file doesn't have it.
- **Naming casing is inconsistent today**: GPIO/RCC/EXTI/SYSCFG use
  `_Regdef_t`, but the stubbed-out SPI struct near the bottom of the
  "Register Definitions" section uses `_RegDef_t`. Don't try to "fix" this —
  just match whichever casing the peripheral you're touching already uses if
  it has an existing stub or struct; otherwise default to `_RegDef_t` (the
  newer stub's convention). If it's genuinely unclear, ask.
- **Pointer macros** live under
  `/****************Peripheral Definitions (Peripheral base addresses typecasted)****************/`
  as `#define <PERIPH>   ((<PERIPH>_Regdef_t *)<PERIPH>_BA)` (or `_RegDef_t`,
  matching the struct's own name), one blank line between peripheral
  families, matching the struct's actual type name exactly.

Never touch unrelated parts of the file — generic macros, the NVIC block,
include guards, or other peripherals' structs/macros — unless the user
specifically asks about a typo you noticed.

If a stub for the requested peripheral already exists (like the incomplete
SPI struct), replace its body rather than adding a second struct.

## Step 2 — Get the reference manual as searchable text

`docs/STM32F4xx_RM.pdf` is ~1740 pages, and this machine doesn't have
poppler installed, so the `Read` tool's PDF page-rendering won't work here
(`pdftoppm is not installed` — don't waste a round trip rediscovering this).
Instead this skill bundles `scripts/pdf_to_text.py`, which uses `pypdf` (pure
Python, already installed in this environment) to dump the whole manual to
`cache/STM32F4xx_RM.txt`, one page per block marked `===PAGE <n>===` (n =
the page number as printed in a PDF viewer / in the manual's own footers).

Check whether `.claude/skills/stm32-regdef-updater/cache/STM32F4xx_RM.txt`
already exists. If not, generate it once:

```
python .claude/skills/stm32-regdef-updater/scripts/pdf_to_text.py
```

This takes roughly a minute and only needs to happen once per checkout (the
script skips regenerating if the cache is already there). After that, use
the ordinary `Grep` and `Read` tools directly on the cached `.txt` file —
no PDF-specific tooling needed, and page numbers in the text map directly to
the manual's chapter/section numbers so search results are easy to jump from.

## Step 3 — Find the peripheral's chapter and pull the real register layout

`Grep` the cache for the peripheral's chapter, e.g. `"Serial peripheral
interface"` for SPI, `"Inter-integrated circuit"` for I2C, `"register map"`
combined with the peripheral name. RM0090's own table of contents (near the
top of the cache) lists every chapter with its starting page — check there
first if a direct grep is ambiguous.

Two sources exist for each peripheral's registers; **prefer the per-register
subsections over the summary table**:

- **Per-register subsections** (e.g. "28.5.1 SPI control register 1
  (SPI_CR1)") state `Address offset: 0x..` and `Reset value: 0x........`
  right under the heading, in clean, individually-extracted text. `Grep` for
  `"Address offset:"` within the chapter's page range to walk every register
  in order — this is the reliable source for offsets, names, and reserved
  gaps.
- **The chapter's own "<Peripheral> register map" summary table** (a single
  table listing every register's offset and per-bit names) is useful for a
  final sanity check of ordering, but its columnar bit-layout doesn't survive
  text extraction cleanly (bit names run together vertically). Don't rely on
  it as the primary source — cross-check against it, don't parse it as
  ground truth.

Build the offset list yourself: start at 0x00, walk the registers in address
order, and insert `RESERVEDn` (or `RESERVEDn[count]`) for any gap between one
register's offset and the next (registers aren't always contiguous — RCC's
struct in the existing file is a good example of a peripheral with several
reserved gaps).

Only include registers that RM0090 documents as present for
STM32F405xx/07xx — where the manual calls out a register/bit as specific to
STM32F42xxx/43xxx (or another line) and F407 isn't listed, leave it out.

## Step 4 — Base address macro

Check whether `<PERIPH>_BA` already exists in the file (Step 1's read covers
this). If missing, find the peripheral's boundary address in RM0090 section
2.3 "Memory map" (Table "STM32F4xx register boundary addresses", near the
start of the manual, page ~64 onward in the cache) — it lists each
peripheral's address range and which bus (AHB1/AHB2/AHB3/APB1/APB2) it's on.
Add the macro to the matching bus-domain block, following the file's
existing spacing/alignment for that block, as `(<BUS>_BA + 0x????U)` (the
offset from the bus base, not the raw absolute address — that's the pattern
every existing macro in the file already follows).

## Step 5 — Write the struct and pointer macro

Insert (or replace, if a stub exists) the struct in the Peripheral Register
Definitions section, in offset order, matching the formatting rules from
Step 1 exactly — this is a header humans will read and extend by hand, so
formatting consistency matters as much as correctness.

Add the pointer macro to the Peripheral Definitions section, grouped with a
blank line separating peripheral families, same as the existing entries.

## Step 6 — Report back

Summarize what changed: which base address macro(s) were added (or confirmed
already present), the new/replaced struct, and the new pointer macro(s).
Remind the user that register bit fields are a separate request (they go in
the peripheral-specific header, see below) that this pass didn't do, in case
they expected a fully bit-defined driver header from this alone.

## Bit-field definitions (peripheral-specific header)

Use this when the user asks to add, complete, or update a peripheral's
register bit fields, using the reference manual (RM0090) as the source. It
covers **every register** of the peripheral unless the user names specific
ones.

**Where it goes:** the peripheral's own header in `hal_drivers/Inc/` —
`spi.h` for SPI, `i2c.h` for I2C, `usart.h` for USART, etc. Never in
`stm32f407xx.h`. If the peripheral header doesn't exist yet, create it with
an include guard (`_<PERI>_DRIVER_H_`, as `spi.h` does) and
`#include "stm32f407xx.h"`; don't touch other headers.

**Reference example** — the user's own `SPI_CR1` in `spi.h`, which they
started and asked to have completed this way. Look at the live file first
(Step 1 equivalent: read the whole peripheral header, and match what's
there), because the user may have changed the style since this was written.
Everything goes under a banner:

```c
/******************************** SPI Register Fields Def ********************************/
```

with one type per register, named `<PERI>_<REG>` (e.g. `SPI_CR1`, `SPI_SR`,
`SPI_I2SCFGR`) — no `_t` suffix, that's the name the user chose:

```c
typedef union {
    uint32_t val;                 /* whole register, read from / write to pPERIx->REG */
    struct {
        uint32_t CPHA      : 1;   /* bit 0 */
        uint32_t CPOL      : 1;
        uint32_t MSTR      : 1;
        uint32_t BR        : 3;   /* BR[2:0] */
        ...
        uint32_t RESERVED0 : 16;  /* 31:16 */
    }CR1_Bits;
}SPI_CR1;
```

Rules:

- **It must be a `union` of `val` and the bit-field `struct`.** The user's
  first draft nested a *union* of bit-fields plus a separate `val` member —
  that overlays every field on bit 0 and leaves `val` disconnected from the
  bits. Fix that shape if you see it; tell the user you did.
- The inner struct's member is named `<REG>_Bits` (`CR1_Bits`), and the
  whole-register member is `val`. Fields are `uint32_t <NAME> : <width>;`.
- Field names are exactly the manual's names (`BIDIMODE`, `LSBFIRST`,
  `I2SCFG`, ...). Multi-bit fields use their width (`BR : 3`).
- **Order fields from bit 0 upward** (ARM GCC allocates bit-fields LSB
  first), and account for **every bit** so each struct totals exactly 32
  bits. Fill gaps and the unused upper bits with `uint32_t RESERVEDn : <width>;`
  (numbered sequentially per register, starting at 0). Add a short
  `/* bit N */` / `/* 15:8 */` comment on reserved gaps.
- Mind only what RM0090 documents for STM32F405xx/07xx (same rule as Step 3).
  Bits the manual calls "Reserved" or "Forced to 0 by hardware" are
  `RESERVEDn` fields.
- Take names, widths and positions from the per-register subsections' bit
  descriptions ("Bit 9 SSM: ...", "Bits 5:3 BR[2:0]: ..."), with the same
  cache/grep approach as Step 2-3. The register-map summary table's
  column layout doesn't extract cleanly, so use it only to sanity-check.
- Sanity-check each register's widths sum to 32 before finishing.
- Replace an existing stub for a register in place (like the incomplete
  `SPI_CR1`) — don't add a second type. Leave everything else in the header
  (config structs, enums, API prototypes) untouched.
- Put the `Register Fields Def` block once, just above the
  `APIs Supported by Driver` banner if one exists, registers in offset
  order.

When you report back, say which registers now have bit-field unions and
mention any deviation from the user's draft (e.g. the union restructure).
