#!/bin/bash

stty -F /dev/ttyACM0 9600 && cat < /dev/ttyACM0 >> serial.log
