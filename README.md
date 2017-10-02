# What is qtCannelloniCanBus ?

qtCannelloniCanBus is a qtCanBus plugin that can communicate through Cannelloni (https://github.com/mguentner/cannelloni) protocol.

# What are the requirements ?

To compile qtCannelloni you need a recent Qt 5 library, cmake and a compiler that supports C++14.

# How to use qtCannelloniCanBus?

## Compilation

Go to project directory and type:

```bash
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH="PATH_TO_QT_INSTALLATION_DIR" ../
make
```

Now library file `libqtCannelloniCanBusPlugin.so` was created. Copy this file to your Qt CanBus plugins directory (e.g. `PATH_TO_QT_INSTALLATION_DIR/plugins/canbus/libqtCannelloniCanBusPlugin.so`).

Now you should be able to load the plugin through standard Qt CanBus facilities:
```cpp
QCanBus::instance()->createDevice(plugin, interfaceName)
```
where `plugin` is a string `cannelloni` and interfaceName is a string of format `local_port,remote_ip,remote_port`.