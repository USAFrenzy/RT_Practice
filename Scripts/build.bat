@echo off
    cd ../
@echo on
    cmake -B build -S . -DBUILD_SANDBOX="ON"
@echo off
    cd Scripts