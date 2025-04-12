TODO (cameron): README

git submodule update --init
bear -- make all

The Bluetooth module AT command mode only works when battery powered and the internal devices buffer is empty ie uart prints are dangerous and can corrupt the
BT device buffer
^^ It turns out that there just needs to be a small delay added after the uart print statements and then the Bluetooth module seems to respond to AT commands
