# font-seer
![font-seer icon](font-seer.png)

A simple GTK3 font preview and metadata viewer for installed fonts.

SPDX-License-Identifier: GPL-2.0-or-later

![font-seer-screenshot](https://github.com/user-attachments/assets/dfb9370e-0610-44c9-85f4-95671e12ecb4)

## Requirements

Build requirements:

- C compiler (`gcc`)
- `make`
- `pkg-config`

Runtime/library requirements:

- gtk3
- fontconfig
- pango

## Arch Packages

Required Arch packages:

- `gtk3`
- `fontconfig`
- `pango`
- `make`
- `pkgconf`
- C compiler toolchain (`gcc` or `clang`)

## Build From Source

```bash
make
```

## Run

```bash
./font_seer
```

or after install:

```bash
font-seer
```

## Behavior

- Shows a GTK font chooser for installed fonts.
- Displays selected font metadata from fontconfig:
- Family
- Style
- File path
- Weight
- Slant
- PostScript name
- Fontconfig name pattern

## Versioning

- `font-seer` uses Semantic Versioning (`MAJOR.MINOR.PATCH`).
- The canonical version is stored in `VERSION`.
- Arch packaging keeps `pkgrel` as a separate package release field.
