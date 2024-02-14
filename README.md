# Modula Replication Engine ☄️

Modula Replication Engine is a file replication engine for system-wide real-time replication implemented in C++ for GNU/Linux operating systems.

How to Run Modula
==========

First, ensure syslog is running on the GNU/Linux system:
```shell
sudo service rsyslog start
```

How to Build Modula from source
==========

For building Modula Replication Engine from source in a GNU/Linux distribution, first ensure that you have a C++ compiler that supports C++20.

After doing so, clone this repository:
```shell
git clone https://github.com/jc-juarez/modula_replication_engine/
```
And finally run the build script:
```shell
chmod +x build.sh && ./build.sh
```
The output `modula` file will be located under the `build` directory.
