# smart_platform

## Usage

Place this library in the same directory as your `lvgl` library.

Then, add the following lines to your `CMakeLists.txt`:

```diff
+file(GLOB SMART_PLATFORM_SRC smart_platform/src/*.c)
+set(SMART_PLATFORM_INC smart_platform/src)
+
+add_library(smart_platform STATIC ${SMART_PLATFORM_SRC})
+target_include_directories(smart_platform PRIVATE ${PROJECT_SOURCE_DIR}/smart_platform)
+
-add_executable(your_project src/main.c)
+add_executable(your_project src/main.c ${SMART_PLATFORM_SRC})

```

Then, use it in your `lvgl` project.

```cpp
#include "smart_platform.h"

void main(int argc, char **argv) {
    // ...
    smart_platform()
    // ...
}
```
