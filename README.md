# My RPI Pico APP

## Setup the SDK

Manual \
<https://datasheets.raspberrypi.org/pico/raspberry-pi-pico-c-sdk.pdf> \
<https://raspberrypi.github.io/pico-sdk-doxygen/>

### Install toolchain (Debian/Ubuntu)

```sh
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi
```

### Install Doxygen

```sh
sudo apt install doxygen
```

### Clone the SDK

```sh
 git clone -b master https://github.com/raspberrypi/pico-sdk.git
 cd pico-sdk
 git submodule update --init
```

## Build the SDK

```sh
mkdir build
cd build
cmake ..
make
make docs
```

### Export PICO_SDK_PATH

```sh
export PICO_SDK_PATH=/<SOME PATH>/pico-sdk
```

## Build this app

```sh
mkdir build
cd build
cmake ..
make
```

## Upload uf2 file to RPi Pico

```sh
cp build/*.uf2 /media/$USER/RPI-RP2
```
