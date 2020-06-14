find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
find_path(WIRINGPI_INCLUDE_DIRS NAMES wiringPi.h)

# NOTE: It handles the REQUIRED, QUIET and version-related arguments of find_package.
# It also sets the <PackageName>_FOUND variable. The package is considered found
# if all variables listed contain valid results, e.g. valid filepaths.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(wiringPi DEFAULT_MSG WIRINGPI_LIBRARIES WIRINGPI_INCLUDE_DIRS)