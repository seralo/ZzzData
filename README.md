# ZzzInput
Simple Arduino / C++ library to manage data


The library consist of a single header file (ZzzData.h) containing template classes.
It can be used in combination with ZzzInput. ZzzMovingAvg library use the ZzzData base tempate.


### Constructor

```cpp
ZzzDataValue<int> data;  //Basic data holder
ZzzDataMinMax<int> data; //Data holder with min() and max() functions
ZzzDataHistory<16, int> data; //Data holder which keep history of the last 16 input values

```

### Functions

```cpp
T add(T input); // To add a new value to the data holder
T get();        // Get the current value (last value)

```

### Included examples

- `DataBasic/DataBasic.ino` - Show basic usage


### Simple code example to get min/max values

```cpp
#include <ZzzData.h>

ZzzDataMinMax <int> data;

void setup()
{
    ...
}

void loop()
{
    ...
    data.add(1);
    data.add(2);
    data.add(3);
    ...
    data.min(): //get min value
    data.max(); //get max value
    ...
}
```

