# smart_platform

## Usage

Place this library in the same directory as your `lvgl` library.

Then, add the following lines to your `CMakeLists.txt`:

```diff
+file(GLOB SMART_PLATFORM_SRC smart_platform/src/*.c)
+set(SMART_PLATFORM_INC smart_platform/src)
+
+add_library(smart_platform STATIC ${SMART_PLATFORM_SRC})
+target_include_directories(smart_platform PUBLIC ${SMART_PLATFORM_INC})
+
-target_link_libraries(your_project lvgl)
+target_link_libraries(your_project lvgl smart_platform)

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
