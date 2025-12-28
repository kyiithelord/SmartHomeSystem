# Smart Home System (Qt 6 + Qt Quick)

A simple Smart Home dashboard built with Qt Quick (QML) and a small C++ backend. It includes a device manager, list model, and a QML UI with a room filter and device tiles for lights, thermostats, plugs, and cameras.

## Prerequisites
- Qt 6.2+ with components:
  - Qt Quick
  - Qt Qml
  - Qt Quick Controls 2
- CMake 3.16+
- A C++17 compiler (gcc/clang/MSVC)

If you installed Qt via the Qt Online Installer, note your Qt path (example):
- Linux: /path/to/Qt/6.6.3/gcc_64
- Windows (MSVC): C:/Qt/6.6.3/msvc2019_64
- macOS (Clang): /Users/<you>/Qt/6.6.3/macos

## Build
```bash
# From the project root
mkdir -p build
cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/<qt_kit>
cmake --build build -j
```

Tips:
- If Qt is installed via your distro packages (e.g., Arch, Fedora, Ubuntu), you may omit `-DCMAKE_PREFIX_PATH`.
- On Windows with the Qt Developer Command Prompt, `CMAKE_PREFIX_PATH` is optional.

## Run
```bash
./build/smarthome
```

## Project layout
- C++ backend
  - `src/devicemanager.{h,cpp}`: In-memory devices with simulated updates; ops: `togglePower`, `setBrightness`, `setTemperature`.
  - `src/devicesmodel.{h,cpp}`: `QAbstractListModel` exposing devices to QML. Roles and `roomFilter`, plus `get(int row)`.
  - `src/main.cpp`: Wires backend to QML context and loads `Main.qml`.
- QML UI
  - `qml/Main.qml`: App window with toolbar, room filter, summary, and grid of device tiles.
  - `qml/DeviceTile.qml`: Reusable tile: power switch, brightness (light), temperature (thermostat).
- Resources
  - `qml.qrc`: Bundles QML into the executable.
- Build system
  - `CMakeLists.txt`: Qt 6 Quick/Qml/QuickControls2 setup.

## Common issues
- “Could not find a package configuration file provided by Qt6…”
  - Ensure Qt 6 is installed and pass the correct `CMAKE_PREFIX_PATH` to your Qt kit directory.
- “module "QtQuick.Controls" is not installed” at runtime
  - Install Qt Quick Controls 2 for your kit, or install distro package (e.g., `qt6-quickcontrols2`).
- Blank window or crash on load
  - Check the console for QML errors. Since QML is embedded via `qml.qrc`, ensure the files exist and were compiled.

## Next steps
- Persist devices to disk or a database.
- Replace simulation with real device APIs (MQTT/HTTP).
- Add scenes/automation and more device types.
