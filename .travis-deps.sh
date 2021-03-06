#!/bin/sh

set -e

#if OS is linux or is not set
if [ "$TRAVIS_OS_NAME" = linux -o -z "$TRAVIS_OS_NAME" ]; then
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
    sudo apt-get -qq update
    sudo apt-get -qq install g++-4.8 xorg-dev libglu1-mesa-dev libxcursor-dev
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 90
    (
        git clone https://github.com/glfw/glfw.git --branch 3.0.4 --depth 1
        mkdir glfw/build && cd glfw/build
        cmake .. && make -j2 && sudo make install
    )

    sudo apt-get install lib32stdc++6
    sudo mkdir -p /usr/local
    curl http://www.cmake.org/files/v2.8/cmake-2.8.11-Linux-i386.tar.gz \
        | sudo tar -xz -C /usr/local --strip-components=1
elif [ "$TRAVIS_OS_NAME" = osx ]; then
    brew tap homebrew/versions
    brew install qt5 glfw3 pkgconfig
fi
