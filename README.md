# NiDBUploader

This project is for a GUI based program which uploads MRI, EEG, and other binary data to an instance of the Neuroinformatics Database (NiDB). See NiDB project at http://github.com/gbook/nidb.

**Pre-requisites** (Windows and Linux)

* QT open-source, including QT Creator
* GCC, libstd, etc
* cmake

**Setup build environment** (Linux)

    cd ~
    svn export https://github.com/gbook/nidbuploader/trunk NiDBUploader
    cd NiDBUploader
    mkdir gdcmbin
    cd gdcmbin
    cmake -DGDCM_BUILD_SHARED_LIBS=ON ../gdcm
    make
    make install

**Build NiDBUploader** (Linux)

    cd ~
    svn export https://github.com/gbook/nidb/trunk NiDBUploader /* update the code to latest version if necessary */
    cd NiDBUploader
    qtcreator .

Within QTCreator, build and test the project. Make sure it is a Release build.

**Zip the package** (Linux)

QTCreator will create a directory called something like `build-NiDBUploader-Desktop_Qt_5_3_GCC_64bit_release`. The NiDBUploader binaries will be in there.

    cp nidbuploader/NiDBUploader.sh build-NiDBUploader-Desktop_Qt_5_3_GCC_64bit_release
    cd build-NiDBUploader-Desktop_Qt_5_3_GCC_64bit_release
    chmod 777 NiDBUploader.sh
    cp ../NiDBUploader/gdcmbin/bin/* .
    mkdir platforms
    cd platforms
    cp /opt/Qt/5.3/gcc_64/plugins/platforms/* .
    cp /opt/Qt/5.3/gcc_64/lib/libQt5DBus.so.5 .
    cp /opt/Qt/5.3/gcc_64/lib/libQt5Gui.so.5 .
    cp /opt/Qt/5.3/gcc_64/lib/libQt5Core.so.5 .
    zip -r NiDBUploader-<LinuxVer>-<builddate>.zip build-NiDBUploader-Desktop_Qt_5_3_GCC_64bit_release/*
