Never use `auto` keyword in toplevel.

Never define function overloading and implicit type conversion.

Encourage use typealias.

Encourage use global function rather than class member function.

> Various "sanitizer" systems such as Address Sanitizer, Undefined Behavior Sanitizer, Purify, Valgrind, etc., all allow this behavior. On systems with flat address spaces, and even segmented ones, various "pointer games" are common (e.g. converting to integral values and masking off low order bits to find page boundaries, etc). These techniques are so common in C code today that it is very unlikely that such idioms will cease to function on any commonly supported system now or in the future.


[pointer arithmetic](https://stackoverflow.com/a/70417758/22152846)