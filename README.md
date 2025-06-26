![top_banner](./.github/banner.jpg)

---

### Ageratum
![loc_badge](https://github.com/waterlily-team/ageratum/blob/badges/loc.svg)
![latest_release_badge](https://img.shields.io/github/v/release/waterlily-team/ageratum?include_prereleases&label=Latest%20Version&color=blue)

A small, incredibly specialized [asset library](https://en.wikipedia.org/wiki/Digital_asset_management) for handling things like [tilesets](https://en.wikipedia.org/wiki/Tile-based_video_game#Tile_set), generic images (`JPEG`, `PNG`, `BMP`), music, etcetera. It's built to be performant but incredibly simple, and has but a single file, which acts duly as a header and implementation file. Ageratum depends on nothing but the [C standard library](https://en.wikipedia.org/wiki/C_standard_library).

---

#### Support
Ageratum current supports the following [operating systems](https://en.wikipedia.org/wiki/Operating_system) and [processor architectures](https://en.wikipedia.org/wiki/Instruction_set_architecture).

- [Linux](https://en.wikipedia.org/wiki/Linux): Currently supported. Tested on [`arch`](https://en.wikipedia.org/wiki/Arch_Linux).
    - [x64](https://en.wikipedia.org/wiki/X86-64): Currently supported. Tested on an [`AMD Ryzen™ 5 5600H`](https://en.wikipedia.org/wiki/List_of_AMD_Ryzen_processors#Desktop_processors).
    - [ARM64](https://en.wikipedia.org/wiki/AArch64): **Not yet supported, but planned.**
- [MacOS](https://en.wikipedia.org/wiki/MacOS): **Not yet supported, but planned.**
    - [Apple Silicon](https://en.wikipedia.org/wiki/Apple_silicon): **Not yet supported, but planned.**
- [BSD](https://en.wikipedia.org/wiki/Berkeley_Software_Distribution): **Not yet supported, but planned.**
    - [x64](https://en.wikipedia.org/wiki/X86-64): **Not yet supported, but planned.**
    - [ARM64](https://en.wikipedia.org/wiki/AArch64): **Not yet supported, but planned.**

Ageratum does not plan to support [Microsoft Windows](https://en.wikipedia.org/wiki/Microsoft_Windows), for it is truly development hell in regards to C.

Ageratum supports the following formats of media, alongside "unknown" files which are treated as raw bytes.

- Generic:
    - [EXE](https://en.wikipedia.org/wiki/Executable): Unix executables are currently supported, with flags to dictate how their execution is handled.
    - [GLSL](https://en.wikipedia.org/wiki/OpenGL_Shading_Language): Currently supported, and a [`glslang`](https://github.com/KhronosGroup/glslang)-based compilation workflow to [SPIR-V](https://en.wikipedia.org/wiki/Standard_Portable_Intermediate_Representation) is also implemented.
    - [Text](https://en.wikipedia.org/wiki/Text_file): Currently supported, though they're treated as raw bytes.
    - [YAML](https://en.wikipedia.org/wiki/YAML): **Not yet supported, but planned.**
- Images:
    - [PNG](https://en.wikipedia.org/wiki/PNG): **Not yet supported, but planned.**
    - [JPEG](https://en.wikipedia.org/wiki/JPEG): **Not yet supported, but planned.**
    - [BMP](https://en.wikipedia.org/wiki/Bitmap): **Not yet supported, but planned.**
- Audio:
    - [MP3](https://en.wikipedia.org/wiki/MP3): **Not yet supported, but planned.**

---

#### Usage
You can use Ageratum by including the main header file in any file in your project. However, in **one** of these files, define the `WLASSETS_IMPLEMENTATION` macro to add the implementation as well. An example would be as follows;

```c
#define WLASSETS_IMPLEMENTATION
#include <Ageratum.h>

int main(void) {
    // Do your stuff.
}
```

---

![bottom_banner](./.github/banner.jpg)
