# A very simple makefile full of shortcuts

# What port the arduino is on
ifndef SERIAL_DEV
	ifneq (,$(wildcard /dev/ttyUSB0))
		SERIAL_DEV = /dev/ttyUSB0
	else ifneq (,$(wildcard /dev/ttyACM0))
		SERIAL_DEV = /dev/ttyACM0
	else
		SERIAL_DEV = unknown
	endif
endif

.PHONY: help

help:	## Prints this help message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

build:	## Invokes pio run
	pio run

# For CI
binaries:	## Builds the binaries
	pio run
	pio run -t .pio/build/uno328/firmware.hex

flash:	## Flashes the code to the processor
	pio run -t upload

deep:	## Flashes the code to processor with fresh EEPROM values
	pio run -t uploadeep

clean:	## Cleans the repo of artefacts
	pio run -t clean
	git clean -fdx

lint:	## De-lints the repo
	pio check

test:	## Run automated tests
	pio test --upload-port $(SERIAL_DEV)

debug: flash monitor	## Flashes then Monitors

monitor:	## Monitors the device serial
	pio device monitor --filter=direct --filter=time
