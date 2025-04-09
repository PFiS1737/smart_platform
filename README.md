# smart_platform

## Usage

Place this library in the same directory as your `lvgl` library.

Then add the following lines to your `CMakeLists.txt`:

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

And make sure you have enabled `LV_USE_FONT_COMPRESSED` in your `lv_conf.h`:

```diff
-#define LV_USE_FONT_COMPRESSED 0
+#define LV_USE_FONT_COMPRESSED 1
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

## References

- [《通用规范汉字表》（2013年）一级字.txt](https://github.com/zispace/hanzi-chars/blob/main/data-charlist/%E3%80%8A%E9%80%9A%E7%94%A8%E8%A7%84%E8%8C%83%E6%B1%89%E5%AD%97%E8%A1%A8%E3%80%8B%EF%BC%882013%E5%B9%B4%EF%BC%89%E4%B8%80%E7%BA%A7%E5%AD%97.txt)
