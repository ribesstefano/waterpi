#ifndef WATERPI_GPIO_H_
#define WATERPI_GPIO_H_

#include <cstring>
#include <map>

#ifndef HIGH_GPIO
#define HIGH_GPIO 1
#endif

#ifndef LOW_GPIO
#define LOW_GPIO 0
#endif

namespace waterpi {

typedef std::map<std::string, unsigned int> GPIO_Map;

} // waterpi

#endif // end WATERPI_GPIO_H_