## Nintendo DS Business Card — O(n) Counting Sort Visualization

This project transforms the Nintendo DS (or 3DS via backward compatibility) into an interactive digital business card that demonstrates a smooth, auto-looping **O(n) Counting Sort visualization** on the top screen while showing contact information on the bottom screen.

Developed in **C** using a Linux terminal environment (WSL on Windows) and the devkitPro toolchain, this project demonstrates low-level graphics rendering, efficient algorithm visualization, and embedded graphics programming for handheld consoles.

---

## Overview

The project integrates algorithmic visualization with Nintendo DS graphics programming using the `libnds` library:

- **Top Screen:** Continuously randomizes and sorts colored bars using Counting Sort (O(n)), showing a smooth animated visualization.
- **Bottom Screen:** Displays a static business card with academic and contact information.

Built and compiled using devkitPro toolchain and tested on melonDS emulator and homebrew-capable hardware.

---

## Features

- Animated sorting bars using Counting Sort (O(n))
- Automatic reshuffle and sorting loop
- Static business card display on lower screen
- Smooth 60 FPS dual-screen rendering
- Built and compiled using Linux terminal commands

---

## Development Environment

- **OS:** Ubuntu (via Windows Subsystem for Linux)
- **Compiler / Toolchain:** devkitARM (from devkitPro)
- **Graphics Library:** libnds
- **Build Tool:** GNU Make
- **Tested on:** melonDS Emulator and Nintendo 3DS XL (homebrew)

---

## Requirements

Before building, ensure the following are installed:

- devkitPro (devkitARM)
- libnds
- ndstool
- GNU Make
- (Optional) melonDS Emulator or a homebrew-enabled Nintendo DS/3DS

Useful links:
- https://devkitpro.org/wiki/Getting_Started
- https://libnds.devkitpro.org/
- https://libnds.devkitpro.org/ndstool.html
- https://melonds.kuribo64.net/

---

## Building the Project

Clone the repository:

```bash
git clone https://github.com/zaidahmad16/DS_Business_Card.git
cd DS_Business_Card
```

Build (example; adjust to your Makefile if different):

```bash
make
```

This should produce a .nds output you can run in melonDS or flash to compatible hardware if you have a homebrew setup.

---

## Notes

- If you previously had a file named `README` (without extension) that used Markdown syntax, GitHub will display it as plain text. Rename it to `README.md` to enable Markdown rendering.
- I removed placeholder ellipses and ensured the clone URL points to this repository.

---

If you want, I can:
- Create a pull request that renames `README` → `README.md` and replaces the content with the version above.
- Or update the file content directly if you prefer to keep the current filename (not recommended — Markdown won't render without .md).

Which would you like me to do?
